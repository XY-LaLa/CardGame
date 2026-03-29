#include "GameController.h"
#include "Models/GameModel.h"
#include "Services/GameModelFromLevelGenerator.h"
#include "Utils/LevelConfigLoader.h"
#include "Views/CardView.h"


GameController::GameController() {
    _playFieldCtrl = new PlayFieldController(this);
    _stackCtrl = new StackController(this);
}
GameController::~GameController() {
    if (_playFieldCtrl) delete _playFieldCtrl;
    if (_stackCtrl) delete _stackCtrl;
}

void GameController::startGame(LevelID id) {
    if (id == LevelID::Title) return;

    //加载配置
    LevelConfig config = LevelConfigLoader::loadLevelConfig(id);

    //生成数据模型
    _gameModel = GameModelFromLevelGenerator::generateFromFile(config);
    if (!_gameModel)return;
    //初始化各子控制器
    _playFieldCtrl->init(_gameModel);
    _stackCtrl->init(_gameModel);

    //创建GameView
    if (_gameView) _gameView->removeFromParent();
    _gameView = GameView::create();
    _rootNode->addChild(_gameView);

    // 初始化各子控制器的视图
    _playFieldCtrl->initView(_gameView);
    _stackCtrl->initView(_gameView);

}

void GameController::setParentNode(cocos2d::Node* node) { _rootNode = node; }



void GameController::onCardClicked(CardView* cardView) {
    rules(cardView);
    
    
   
}

void GameController::rules(CardView* cardView) {
    auto cardModel = cardView->getModel();
    if (_gameModel->isCardAtTop(cardModel)) {
        auto id = cardModel->getSlotID();
        if (id == HAND_RIGHT)return;
        //点击 备用牌
        else if (id == SlotID::HAND_LEFT) {
            _gameModel->moveCard(id, HAND_RIGHT);
            auto targetPos = slotTable[HAND_RIGHT].startPosition;
            int newZ = (int)_gameModel->getPiles()[HAND_RIGHT].size();
            // 4. 执行动画
            cardView->flyTo(targetPos, newZ, [cardView]() {});
        }
        else{
            if (canCollectCard(cardModel)) {
                _gameModel->moveCard(id, HAND_RIGHT);

                auto targetPos = slotTable[HAND_RIGHT].startPosition;
                int newZ = (int)_gameModel->getPiles()[HAND_RIGHT].size();
                // 4. 执行动画
                cardView->flyTo(targetPos,newZ, [cardView]() {});
            }
        }

    }
}


// 判定规则：比底牌大 1 或小 1
bool GameController::canCollectCard(CardModel* targetModel) {
    // 2. 获取当前底牌
    auto& wastePile = _gameModel->getPiles()[HAND_RIGHT];
    if (wastePile.empty()) return true; // 如果底牌空了，任何牌都能收（通常不会发生）

    CardModel* topWaste = wastePile.back();
    int targetVal = (int)targetModel->getFace();
    int wasteVal = (int)topWaste->getFace();

    // 逻辑判定：±1 或者是 K 与 A 连通
    int diff = std::abs(targetVal - wasteVal);
    return (diff == 1 || diff == 12); // 12 是 A(1) 和 K(13) 的差值
}
