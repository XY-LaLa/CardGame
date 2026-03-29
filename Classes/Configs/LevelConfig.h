#pragma once
#include "cocos2d.h"



/**
 * @struct CardConfigData
 * @brief 关卡配置文件中的单张牌快照
 * @details 直接对应 JSON 文件中 "Playfield" 或 "Stack" 数组内的元素。
 */
struct CardConfigData {
    int face;
    int suit;
    cocos2d::Vec2 position;
};

/**
 * @struct LevelConfig
 * @brief 完整关卡的逻辑配置
 * @details 包含初始化一个关卡所需的全部卡牌排列信息，分为牌阵区和备用堆区。
 */
struct LevelConfig {
    std::vector<CardConfigData> playfield;
    std::vector<CardConfigData> stack;
};

