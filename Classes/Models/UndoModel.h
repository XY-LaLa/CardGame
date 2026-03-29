#pragma once
#include "Models/CardModel.h"
#include "cocos2d.h"

class UndoModel {
public:
    CardModel* card;
    SlotID fromSlot;
    SlotID toSlot;
    cocos2d::Vec2 fromPosition;
};