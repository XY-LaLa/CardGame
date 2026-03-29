#include "CardModel.h"

CardModel::CardModel(CardSuitType suit, CardFaceType face, cocos2d::Vec2 position):
	_suit(suit), _face(face), _position(position){}

CardSuitType CardModel::getSuit() const { return _suit; }
CardFaceType CardModel::getFace() const { return _face; }
SlotID CardModel::getSlotID()const { return _slotID; };
cocos2d::Vec2 CardModel::getPosition()const { return _position; }
bool CardModel::getCanClick()const { return _canClick; }

void CardModel::setSlotID(SlotID id) { _slotID = id; }
void CardModel::setSuit(const CardSuitType suit) { _suit = suit; }
void CardModel::setFace(const CardFaceType face) { _face = face; }
void CardModel::setPosition(cocos2d::Vec2 pos) { _position = pos; }
void CardModel::setCanClick(bool canClick) { _canClick = canClick; }
