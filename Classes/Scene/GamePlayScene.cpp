#include "GamePlayScene.h"
#include "Views/GameView.h"
#include "Views/CardView.h"
#include "Services/GameModelFromLevelGenerator.h"
#include "Configs/GameConfig.h"
USING_NS_CC;

GamePlayScene::GamePlayScene() {

}
GamePlayScene::~GamePlayScene() {
    // 按照单一职责原则，场景销毁时必须清理其拥有的控制器逻辑
    if (_gameController) {
        delete _gameController;
        _gameController = nullptr;
    }
}

Scene* GamePlayScene::createScene() {
    return GamePlayScene::create(); 
}

bool GamePlayScene::init() {
    if (!Scene::init()) {
        return false;
    }
    _gameController = new GameController();
    _gameController->setParentNode(this);//建立视图与控制器的联系
    _gameController->startGame(Level01);//启动关卡

    return true;
}
