#pragma once
#include <unordered_map>
#include "cocos2d.h"

class GameView : public cocos2d::Node
{
public:

public:
	CREATE_FUNC(GameView);
	virtual bool init() override;
	GameView();
	~GameView();



public:
	void addGround(const std::string name, cocos2d::Sprite*);
	cocos2d::Sprite* getGround(const std::string& name);
private:
	std::unordered_map<std::string, cocos2d::Sprite*> _grounds;	
};

