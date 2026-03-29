#pragma once
#include <string>
#include <array>
#include "cocos2d.h"

/**
 * @enum SlotID
 * @brief 游戏场景中的逻辑槽位枚举
 * @details 定义了卡牌可以存放的四个核心区域，用于逻辑判定和 UI 布局。
 */

//用于定义场上4个格子(牌区)的枚举
enum SlotID {
	MAIN_LEFT,//左锋
	MAIN_RIGHT,//右锋
	HAND_LEFT,//备用牌
	HAND_RIGHT,//底牌
	COUNT_SLOT
};

/**
 * @struct SlotData
 * @brief 槽位布局属性
 * @details 存储每个 Slot 的起始渲染坐标及牌与牌之间的层叠偏移量。
 */
struct SlotData {
	cocos2d::Vec2 startPosition;
	cocos2d::Vec2 offset;
};

/**
 * @brief 全局槽位布局静态表
 * @details 预定义了各个 SlotID 对应的物理位置。修改此表可直接改变整个游戏的排版。
 */
const std::array<SlotData, static_cast<size_t>(SlotID::COUNT_SLOT)> slotTable = { {
		{ cocos2d::Vec2(250, 1500), cocos2d::Vec2(50, -200) },   // MAIN_LEFT
		{ cocos2d::Vec2(850, 1500), cocos2d::Vec2(-50, -200) },   // MAIN_RIGHT
		{ cocos2d::Vec2(250, 300),  cocos2d::Vec2(80, 0) },   // HAND_LEFT
		{ cocos2d::Vec2(800, 300),  cocos2d::Vec2(0, 0) }    // HAND_RIGHT
	} };

/**
 * @enum LevelID
 * @brief 关卡索引枚举
 */
enum LevelID {
	Title = 0,
	Level01,
	Level02,
	Level03,
	COUNT_LEVEL
};

/**
 * @brief 关卡资源路径映射表
 * @details 将 LevelID 映射到具体的 JSON 配置文件路径。
 */
constexpr std::array<const char* , static_cast<size_t>(LevelID::COUNT_LEVEL)> levelTable = {
		 "Assets/LevelJSON.json",
		 "Assets/LevelJSON.json",
		 "Assets/LevelJSON.json"
};

