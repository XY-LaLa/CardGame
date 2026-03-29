#pragma once
#include "cocos2d.h"
#include "Models/CardModel.h"
#include "Configs/CardResConfig.h"
#include "Configs/GameConfig.h"

class CardView : public cocos2d::Sprite {
public:
    struct CardChild{
    public:
        CardChild(const std::string& p, const cocos2d::Vec2& a)
            : path(p), aspectRatio(a)
        {
        }
        std::string path;
        cocos2d::Vec2 aspectRatio;
        cocos2d::Sprite* node = nullptr;
    };
public:
    CardView();
    virtual ~CardView();

    static CardView* createWithModel(CardModel* model);
    virtual bool initWithModel(CardModel* model);

    std::function<void(CardView*)> onClicked = nullptr;

    // 动画接口：平滑移动到目标位置
    void flyTo(cocos2d::Vec2 targetPos, int newZ, std::function<void()> onComplete = nullptr);

    // 获取对应的 Model
    CardModel* getModel()const;

 
private:
    void initTouch();
    void addChildSprite(CardChild& childSprite);

private:

    CardModel* _model{ nullptr };
	CardData _data;
	std::vector<CardChild> _childSprites;
    cocos2d::Sprite* _background{ nullptr };
};