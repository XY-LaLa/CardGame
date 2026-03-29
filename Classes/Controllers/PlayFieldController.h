#pragma once
#include "Models/GameModel.h"
#include "Views/GameView.h"
#include <unordered_map>

class CardView;
class GameController;
class PlayFieldController {
public:
    PlayFieldController(GameController* mainController);
    void init(GameModel* model);
    void initView(GameView* gameView);

private:

    GameModel* _gameModel = nullptr;

    GameController* _mainController;
};