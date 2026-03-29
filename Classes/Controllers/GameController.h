#pragma once
#include "Configs/GameConfig.h"
#include "Managers/PlayFieldManager.h"
#include "Managers/StackManager.h"
#include "Views/CardView.h"
#include "Managers/UndoManager.h"


class GameController {
public:
    GameController();
    ~GameController();
	void startGame(LevelID id);
    void setParentNode(cocos2d::Node* node);

    void onCardClicked(CardView* cardView);
private:
    void initCardViews();
    void rules(CardView* cardView);
    //移动控制
    void executeMove(CardModel* card, SlotID from, SlotID to, bool isUndo);
private:
    cocos2d::Node* _rootNode{ nullptr };

    //游戏数据
    GameModel* _gameModel{ nullptr };
    //游戏视图
    GameView* _gameView{ nullptr };

    //子控制器
    PlayFieldManager _playFieldManager;
    StackManager _stackManager;

    //回退系统管理
    UndoManager _undoManager;
};