#pragma once
#include <string>
#include <array>
#include "cocos2d.h"
enum SlotID {
	MAIN_LEFT,//左锋
	MAIN_RIGHT,//右锋
	HAND_LEFT,//备用牌
	HAND_RIGHT,//底牌
	COUNT_SLOT
};

enum LevelID {
	Title = 0,
	Level01,
	Level02,
	Level03,
	COUNT_LEVEL
};

struct SlotData {
	cocos2d::Vec2 startPosition;
	cocos2d::Vec2 offset;
};

const std::array<SlotData, static_cast<size_t>(SlotID::COUNT_SLOT)> slotTable = { {
		{ cocos2d::Vec2(350, 1100), cocos2d::Vec2(-50, 200) },   // MAIN_LEFT
		{ cocos2d::Vec2(750, 1100), cocos2d::Vec2(50, 200) },   // MAIN_RIGHT
		{ cocos2d::Vec2(200, 300),  cocos2d::Vec2(-80, 0) },   // HAND_LEFT
		{ cocos2d::Vec2(600, 300),  cocos2d::Vec2(0, 0) }    // HAND_RIGHT
	} };

constexpr std::array<const char* , static_cast<size_t>(LevelID::COUNT_LEVEL)> levelTable = {
		 "Assets/LevelJSON.json",
		 "Assets/LevelJSON.json",
		 "Assets/LevelJSON.json"
};

