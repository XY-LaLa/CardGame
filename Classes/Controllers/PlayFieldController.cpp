#include "PlayFieldController.h"
#include "Views/CardView.h"
#include "GameController.h"


PlayFieldController::PlayFieldController(GameController* mainController) {
    _mainController = mainController;
}

void PlayFieldController::init(GameModel* model) {
    _gameModel = model;
}

void PlayFieldController::initView(GameView* gameView) {
    if (!_gameModel) return;
    // 从 Model 获取该堆栈的所有卡牌数据
    auto& cards = _gameModel->getPiles()[MAIN_LEFT];

    for (CardModel* cardModel : cards) {
        //创建视图
        auto cardView = CardView::createWithModel(cardModel);

        //设置坐标 (直接使用 JSON 中解析出来的 Position)
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

CardView* PlayFieldController::getCardViewByModel(CardModel* m) { return _viewMap[m]; }