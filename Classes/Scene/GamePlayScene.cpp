#include "GamePlayScene.h"
#include "Views/GameView.h"
#include "Views/CardView.h"
#include "Services/GameModelFromLevelGenerator.h"
#include "Configs/GameConfig.h"
USING_NS_CC;

GamePlayScene::GamePlayScene() {

}
GamePlayScene::~GamePlayScene() {
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
    _gameController->setParentNode(this);
    _gameController->startGame(Level01);

    return true;
}

void GamePlayScene::update(float dt) {
  
}
