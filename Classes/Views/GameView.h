#pragma once
#include <unordered_map>
#include "cocos2d.h"

class GameView : public cocos2d::Node
{
public:
	CREATE_FUNC(GameView);
	virtual bool init() override;
	GameView();
	~GameView();
public:
	void addSprite(const std::string name, cocos2d::Sprite*);
	cocos2d::Sprite* getSprite(const std::string& name);

	std::function<void()> onUndoBtnClicked = nullptr;
private:
	void setupUI();
private:
	std::unordered_map<std::string, cocos2d::Sprite*> _grounds;	
};

