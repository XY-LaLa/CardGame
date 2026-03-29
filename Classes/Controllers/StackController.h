#pragma once
#include "Models/GameModel.h"
#include "Views/GameView.h"

class GameController;
class StackController {
public:
    StackController(GameController* mainController);
    void init(GameModel* model);
    void initView(GameView* gameView);

private:
    GameModel* _gameModel = nullptr;
    GameController* _mainController;
};