#include "GameController.h"
#include "Models/GameModel.h"
#include "Services/GameModelFromLevelGenerator.h"
#include "Utils/LevelConfigLoader.h"
#include "Views/CardView.h"


GameController::GameController(){
    //注册回调函数
    _undoManager.setUndoHandler([this](CardModel* c, SlotID f, SlotID t, bool u) {
        this->executeMove(c, f, t, u);
        });
}
GameController::~GameController() { 
    //删除游戏数据
    if (_gameModel) {
        delete _gameModel; 
        _gameModel = nullptr;
    }
}

void GameController::startGame(LevelID id) {
    //重置子系统状态
    _undoManager.clear();
    _playFieldManager.clear();
    _stackManager.clear();

    if (id == LevelID::Title) return;
    //加载配置 
    LevelConfig config = LevelConfigLoader::loadLevelConfig(id);

    //数据初始化
    if(_gameModel) delete _gameModel;//清理
    _gameModel = GameModelFromLevelGenerator::generateFromFile(config);

    if (!_gameModel)return;
   
    //视图初始化
    if (_gameView) _gameView->removeFromParent();
    _gameView = GameView::create();
    _rootNode->addChild(_gameView);

    // 绑定 UI 撤销按钮回调
    _gameView->onUndoBtnClicked = [this]() {
        _undoManager.undo();
        };

    initCardViews();
}

/**
 * 注意：此函数负责模型到视图的映射绑定
 * 遵循 50 行规范。若后续增加更多装饰逻辑，建议将创建逻辑抽离。
 */
void GameController::initCardViews() {
    if (!_gameModel) return;
    // 从 Model 获取该堆栈的所有卡牌数据
    auto& cards = _gameModel->getPiles();
    //遍历
    for (auto& pair : cards) {
        SlotID slotId = pair.first;
        std::vector<CardModel*>& cardsModels = pair.second;

        for (auto* cardModel : cardsModels) {
            //创建视图并绑定数据模型
            auto cardView = CardView::createWithModel(cardModel);
            cardView->setPosition(cardModel->getPosition());

            //设置交互回调
            cardView->onClicked = [this](CardView* cv) {
                this->onCardClicked(cv);
                };

            _gameView->addChild(cardView);
            //根据槽位类型存入不同的管理器
            if (slotId == HAND_LEFT || slotId == HAND_RIGHT) {
                _stackManager.addToMap(cardModel, cardView);
            }
            else {
                _playFieldManager.addToMap(cardModel, cardView);
            }

        }
    }
	//游戏初始 自动将备用牌堆顶牌移至底牌堆 且不记录撤销操作
    executeMove(_gameModel->getPiles()[HAND_LEFT].back(), HAND_LEFT, HAND_RIGHT, true);
    
}

void GameController::setParentNode(cocos2d::Node* node) { _rootNode = node; }

void GameController::onCardClicked(CardView* cardView) {
    rules(cardView);
}

void GameController::rules(CardView* cardView) {
    //只有顶层牌可以操作
    auto cardModel = cardView->getModel();
    if (!_gameModel->isCardAtTop(cardModel)) return;

    auto fromId = cardModel->getSlotID();
    if (fromId == HAND_RIGHT) return;//底牌不可点击

    //匹配检查
    if (fromId == HAND_LEFT || _gameModel->canMatch(cardModel)) {
        //调用移动方法
        executeMove(cardModel, fromId, HAND_RIGHT,false);
    }
}


void GameController::executeMove(CardModel* card, SlotID from, SlotID to, bool isUndo) {
    //格子变更
    _gameModel->moveCard(from, to);
    //在非撤销操作时记录
    if (!isUndo) {
        _undoManager.pushStack({ card, from, to });
    }
    //查找对应的视图对象
    auto cardView = _playFieldManager.getCardViewByModel(card);
    if (!cardView) cardView = _stackManager.getCardViewByModel(card);

    if (cardView) {
        cocos2d::Vec2 targetPos;
        if (to == HAND_RIGHT) {
            // 如果是去底牌堆使用固定的起点
            targetPos = slotTable[to].startPosition;
        }
        else {
            //计算偏移    
            int index = (int)_gameModel->getPiles()[to].size() - 1;
            // 基础坐标 + (偏移量 * 索引)
            targetPos = slotTable[to].startPosition + (slotTable[to].offset * index);
        }
        // 视觉层面的移动
        int newZ = (int)_gameModel->getPiles()[to].size();
        cardView->flyTo(targetPos, newZ, nullptr);
    }
}
