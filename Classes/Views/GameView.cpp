#include "GameView.h"
#include "Configs/GameConfig.h"
#include "ui/CocosGUI.h"


// 临时定义一些位置 大小信息

const cocos2d::Vec2 kHandAreaPosition = cocos2d::Vec2(0, 0);
const cocos2d::Size kHandAreaSize = cocos2d::Size(1080.0f, 580.0f);

const cocos2d::Vec2 kMainAreaPosition = cocos2d::Vec2(0, 580.0f);
const cocos2d::Size kMainAreaSize = cocos2d::Size(1080.0f, 1500.0f);

const cocos2d::Vec2 kUndoBtnPosition = cocos2d::Vec2(540, 1900);
const cocos2d::Size kUndoBtnSize = cocos2d::Size(250, 160);
const int kUndoBtnTextSize = 50;

GameView::GameView() {
}


GameView::~GameView() {
}

void GameView::setupUI() {
    //创建按钮
    auto undoBtn = cocos2d::ui::Button::create("Assets/white.png");

    //关闭“忽略自定义尺寸”允许 1x1 图片拉伸
    undoBtn->ignoreContentAdaptWithSize(false);
    undoBtn->setContentSize(kUndoBtnSize);

    //设置位置和外观
    undoBtn->setPosition(kUndoBtnPosition);
    //设置文字
    undoBtn->setTitleText("UNDO");
    undoBtn->setTitleFontSize(kUndoBtnTextSize);
    undoBtn->setTitleColor(cocos2d::Color3B::BLACK);

    //回调
    undoBtn->addClickEventListener([this](cocos2d::Ref* sender) {
        if (onUndoBtnClicked) {
            onUndoBtnClicked();
        }
        });

    this->addChild(undoBtn, 100);
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
    
    addSprite("HandGround", handAreaSprite);

    auto mainAreaSprite = cocos2d::Sprite::create("Assets/white.png");
    mainAreaSprite->setAnchorPoint(cocos2d::Vec2(0, 0));
    mainAreaSprite->setColor(cocos2d::Color3B(0, 255, 0));
    mainAreaSprite->setPosition(kMainAreaPosition);
    mainAreaSprite->setContentSize(kMainAreaSize);
   
    addSprite("MainGround", mainAreaSprite);

    setupUI();
	return true;
}

void GameView::addSprite(const std::string name, cocos2d::Sprite* sprite) {
    if (!sprite) return;
    // 如果 key 已存在，先移除旧的 Sprite
    if (_grounds.find(name) != _grounds.end()) {
        this->removeChild(_grounds[name]);
    }
    _grounds[name] = sprite;
    this->addChild(sprite);
}

cocos2d::Sprite* GameView::getSprite(const std::string& name) {
    auto it = _grounds.find(name);
    return (it != _grounds.end()) ? it->second : nullptr;
}