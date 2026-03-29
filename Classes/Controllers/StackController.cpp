#include "StackController.h"
#include "Views/CardView.h"
#include "GameController.h"

StackController::StackController(GameController* mainController) {
    _mainController = mainController;
}

void StackController::init(GameModel* model) {
    _gameModel = model;
}

void StackController::initView(GameView* gameView) {
    if (!_gameModel) return;

    // 牌阵包含左右两个峰
    std::vector<SlotID> slots = { HAND_LEFT, HAND_RIGHT };

    for (auto slotId : slots) {
        //获取堆栈的所有卡牌数据
        auto& cards = _gameModel->getPiles()[slotId];

        for (CardModel* cardModel : cards) {
            //创建视图
            auto cardView = CardView::createWithModel(cardModel);

            //设置从关卡配置中读取的初始坐标
            cardView->setPosition(cardModel->getPosition());

            cardView->onClicked = [this](CardView* cv) {
                //通过中转交给 GameController 处理
                _mainController->onCardClicked(cv);
                };
            //加入映射表
            _viewMap[cardModel] = cardView;
            //添加到游戏视图层
            gameView->addChild(cardView);
        }

    }
}

CardView* StackController::getCardViewByModel(CardModel* m) { return _viewMap[m]; }