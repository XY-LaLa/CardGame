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
        // 从 Model 获取该堆栈的所有卡牌数据
        auto& cards = _gameModel->getPiles()[slotId];

        for (CardModel* cardModel : cards) {
            // 1. 创建视图 (CardView 内部根据 Model 的 Suit/Face 加载图片)
            auto cardView = CardView::createWithModel(cardModel);

            // 2. 设置坐标 (直接使用 JSON 中解析出来的 Position)
            cardView->setPosition(cardModel->getPosition());

            cardView->onClicked = [this](CardView* cv) {
                // 通过中转交给 GameController 处理
                _mainController->onCardClicked(cv);
                };

            // 3. 添加到游戏视图层
            gameView->addChild(cardView);
        }

    }
}