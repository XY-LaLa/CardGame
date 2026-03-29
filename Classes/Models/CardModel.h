#pragma once
#include "cocos2d.h"
#include "Configs/CardResConfig.h"
#include "Configs/LevelConfig.h"
#include "Configs/GameConfig.h"

class CardModel {
public:
	CardModel(CardSuitType suit, CardFaceType _face, cocos2d::Vec2 position);

	
	CardSuitType getSuit() const;
	CardFaceType getFace() const;
	SlotID getSlotID()const;
	cocos2d::Vec2 getPosition()const;
	bool getCanClick()const;

	void setSuit(CardSuitType suit);
	void setFace(CardFaceType face);
	void setSlotID(SlotID id);
	void setPosition(cocos2d::Vec2 pos);
	void setCanClick(bool canClick);


private:
	CardSuitType _suit{ CST_NONE };
	CardFaceType _face{ CFT_NONE };
	SlotID _slotID{ HAND_LEFT };
	cocos2d::Vec2 _position;
	bool _canClick = false;


};