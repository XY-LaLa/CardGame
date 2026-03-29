#pragma once
#include "cocos2d.h"



// 对应 JSON 中的单张卡牌配置
struct CardConfigData {
    int face;
    int suit;
    cocos2d::Vec2 position;
};

//关卡配置
struct LevelConfig {
    std::vector<CardConfigData> playfield;
    std::vector<CardConfigData> stack;
};

