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
    if (_gameModel) delete _gameModel;
}

void GameController::startGame(LevelID id) {
    _undoManager.clear();
    _playFieldManager.clear();
    _stackManager.clear();

    if (id == LevelID::Title) return;
    //加载配置
    LevelConfig config = LevelConfigLoader::loadLevelConfig(id);

    //生成数据模型
    if(_gameModel) delete _gameModel;//清理
    _gameModel = GameModelFromLevelGenerator::generateFromFile(config);

    if (!_gameModel)return;
   
    //创建GameView
    if (_gameView) _gameView->removeFromParent();
    _gameView = GameView::create();
    _rootNode->addChild(_gameView);
    // 绑定按钮回调
    _gameView->onUndoBtnClicked = [this]() {
        _undoManager.undo();
        };

    initCardViews();
}

void GameController::initCardViews() {
    if (!_gameModel) return;
    // 从 Model 获取该堆栈的所有卡牌数据
    auto& cards = _gameModel->getPiles();
    //遍历
    for (auto& pair : cards) {
        SlotID slotId = pair.first;
        std::vector<CardModel*>& cardsModels = pair.second;

        for (auto* cardModel : cardsModels) {
            auto cardView = CardView::createWithModel(cardModel);
            //初始化位置 使用Model
            cardView->setPosition(cardModel->getPosition());
            cardView->onClicked = [this](CardView* cv) {
                //通过中转交给 GameController 处理
                this->onCardClicked(cv);
                };

            _gameView->addChild(cardView);

            if (slotId == HAND_LEFT || slotId == HAND_RIGHT) {
                _stackManager.addToMap(cardModel, cardView);
            }
            else {
                _playFieldManager.addToMap(cardModel, cardView);
            }

        }
    }
}

void GameController::setParentNode(cocos2d::Node* node) { _rootNode = node; }

void GameController::onCardClicked(CardView* cardView) {
    rules(cardView);
}

void GameController::rules(CardView* cardView) {
    auto cardModel = cardView->getModel();
    if (!_gameModel->isCardAtTop(cardModel)) return;

    auto fromId = cardModel->getSlotID();
    if (fromId == HAND_RIGHT) return;

    if (fromId == HAND_LEFT || _gameModel->canMatch(cardModel)) {
        // 调用封装好的移动方法
        executeMove(cardModel, fromId, HAND_RIGHT,false);
    }
}


void GameController::executeMove(CardModel* card, SlotID from, SlotID to, bool isUndo) {
    // 1. 数据模型变更
    _gameModel->moveCard(from, to);

    if (!isUndo) {
        _undoManager.pushStack({ card, from, to });
    }

    auto cardView = _playFieldManager.getCardViewByModel(card);
    if (!cardView) cardView = _stackManager.getCardViewByModel(card);

    if (cardView) {
        // --- 改进的坐标计算逻辑 ---
        cocos2d::Vec2 targetPos;

        if (to == HAND_RIGHT) {
            // 如果是去底牌堆使用固定的起点
            targetPos = slotTable[to].startPosition;
        }
        else {
            //回到牌阵（回退操作）计算偏移    
            int index = (int)_gameModel->getPiles()[to].size() - 1;
            // 基础坐标 + (偏移量 * 索引)
            targetPos = slotTable[to].startPosition + (slotTable[to].offset * index);
        }
        // 视觉层面的移动
        int newZ = (int)_gameModel->getPiles()[to].size();
        cardView->flyTo(targetPos, newZ, nullptr);
    }
}
