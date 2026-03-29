#include "GameView.h"
#include "Configs/GameConfig.h"

const cocos2d::Vec2 kHandAreaPosition = cocos2d::Vec2(0, 0);
const cocos2d::Size kHandAreaSize = cocos2d::Size(1080.0f, 580.0f);

const cocos2d::Vec2 kMainAreaPosition = cocos2d::Vec2(0, 580.0f);
const cocos2d::Size kMainAreaSize = cocos2d::Size(1080.0f, 1500.0f);

GameView::GameView() {
	
}


GameView::~GameView() {

}

bool GameView::init() {
	if (!Node::init()) {
		return false;
	}
    auto handAreaSprite = cocos2d::Sprite::create("Assets/white.png");
    handAreaSprite->setAnchorPoint(cocos2d::Vec2(0, 0));
    handAreaSprite->setColor(cocos2d::Color3B(255, 0, 0));
    handAreaSprite->setPosition(kHandAreaPosition);
    handAreaSprite->setContentSize(kHandAreaSize);
    
    addGround("HandGround", handAreaSprite);

    auto mainAreaSprite = cocos2d::Sprite::create("Assets/white.png");
    mainAreaSprite->setAnchorPoint(cocos2d::Vec2(0, 0));
    mainAreaSprite->setColor(cocos2d::Color3B(0, 255, 0));
    mainAreaSprite->setPosition(kMainAreaPosition);
    mainAreaSprite->setContentSize(kMainAreaSize);
   
    addGround("MainGround", mainAreaSprite);
	return true;
}

void GameView::addGround(const std::string name, cocos2d::Sprite* sprite) {
    if (!sprite) return;

    // 如果 key 已存在，先移除旧的 Sprite
    if (_grounds.find(name) != _grounds.end()) {
        this->removeChild(_grounds[name]);
    }

    _grounds[name] = sprite;

    // 关键：必须 addChild 才能渲染
    this->addChild(sprite);
}

cocos2d::Sprite* GameView::getGround(const std::string& name) {
    auto it = _grounds.find(name);
    return (it != _grounds.end()) ? it->second : nullptr;
}