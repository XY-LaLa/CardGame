#pragma once
#include "Configs/GameConfig.h"
#include "PlayFieldController.h"
#include "StackController.h"
#include "Views/CardView.h"


class GameController {
public:
    GameController();
    ~GameController();
	void startGame(LevelID id);
    void setParentNode(cocos2d::Node* node);

    void onCardClicked(CardView* cardView);
    void handleDrawCard(CardView* cardView);
    bool canCollectCard(CardModel* targetModel);
private:
    void rules(CardView* cardView);

private:
    cocos2d::Node* _rootNode{ nullptr };
    GameModel* _gameModel{ nullptr };

    PlayFieldController* _playFieldCtrl{ nullptr };
    StackController* _stackCtrl{ nullptr };

    // 视图
    GameView* _gameView{ nullptr };
};