#include "CardView.h"
#include "Utils/CardResourceProvider.h"
#include "Utils/PublicUtil.h"

USING_NS_CC;

const cocos2d::Vec2 kChildBigNumAR = cocos2d::Vec2(0.5, 0.4);
const cocos2d::Vec2 kChildSmallNumAR = cocos2d::Vec2(0.2, 0.8);
const cocos2d::Vec2 kChildSuitIconAR = cocos2d::Vec2(0.8, 0.8);

CardView::CardView(){
}
CardView::~CardView() {
    if (_model)_model = nullptr; 
   _childSprites.clear();
}

CardView* CardView::createWithModel(CardModel* model) {
    CardView* sprite = new (std::nothrow) CardView();
    if (sprite && sprite->initWithModel(model)) {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

bool CardView::initWithModel(CardModel* model) {
    if (!model) return false;

    _model = model;

    //获取资源路径配置
    _data = CardResourceProvider::getPathsForCard(_model->getSuit(), _model->getFace());

  
    if (!Sprite::initWithFile(_data.cardBack)) {
        return false;
    }
	
    //准备子节点
    _childSprites.push_back({ _data.bigNumPath, kChildBigNumAR });
    _childSprites.push_back({ _data.smallNumPath, kChildSmallNumAR });
    _childSprites.push_back({ _data.suitIconPath, kChildSuitIconAR });
    for (auto& child : _childSprites) {
        addChildSprite(child);
    }

    //初始化触摸监听
    initTouch();
    return true;
}

CardModel* CardView::getModel() const { return _model; }

void CardView::addChildSprite(CardChild& child) {
    auto sprite = Sprite::create(child.path);
    if (sprite) {
        sprite->setAnchorPoint(_data.kAnchorPoint);
        auto pos = PublicUtil::getCardLoaclPositionByFather(*sprite, *this, child.aspectRatio);
        sprite->setPosition(pos);
        this->addChild(sprite);
        child.node = sprite;
    }
}

void CardView::initTouch() {
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = [this](Touch* touch, Event* event) {
        // 转化为本地坐标判断点击
        Vec2 locationInNode = this->convertToNodeSpace(touch->getLocation());
        Rect rect = Rect(0, 0, this->getContentSize().width, this->getContentSize().height);

        if (rect.containsPoint(locationInNode)) {
    
            if (onClicked) {
                onClicked(this); // 触发回调通知 Controller
            }
            return true;
        }
        return false;
        };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void CardView::flyTo(Vec2 targetPos,int newZ, std::function<void()> onComplete) {
    this->setZOrder(999);

    auto move = MoveTo::create(0.4f, targetPos);
    auto easeMove = EaseQuadraticActionOut::create(move);

    auto spawn = Spawn::create(easeMove, nullptr);

    // 3. 动作序列
    auto sequence = Sequence::create(spawn, CallFunc::create([=]() {
        this->setZOrder(newZ);
        if (onComplete) onComplete();
        }), nullptr);

    this->runAction(sequence);
}





