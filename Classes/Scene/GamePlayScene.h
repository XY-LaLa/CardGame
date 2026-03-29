#pragma once
#include "cocos2d.h"
#include "Controllers/GameController.h"
class GamePlayScene : public cocos2d::Scene
{
public:
    GamePlayScene();
    ~GamePlayScene();
    static cocos2d::Scene* createScene();

    virtual bool init() override;

    virtual void update(float dt) override;

    CREATE_FUNC(GamePlayScene);
private:
    GameController* _gameController{nullptr};
};