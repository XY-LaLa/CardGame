#pragma once

#include "Models/GameModel.h"
#include "Models/CardModel.h"
#include "Configs/LevelConfig.h"
#include "Configs/CardResConfig.h"
#include "cocos2d.h"
#include "Utils/json.hpp"


/**
 * @class GameModelFromLevelGenerator
 * @brief 游戏数据生成工厂类
 * @details 职责包括：
 * 1. 静态工厂类，负责根据传入的关卡配置（LevelConfig）实例化 GameModel。
 * 2. 负责 CardModel 对象的内存创建。
 * 3. 实现了初始布局逻辑，如根据横坐标判定扑克牌属于左侧还是右侧牌阵。
 */
class GameModelFromLevelGenerator {
public:
    /**
     * @brief 根据配置文件生成游戏模型
     * @param levelConfig 包含牌阵数据和手牌堆数据的配置结构体
     * @return GameModel* 返回创建好的模型指针。
     */
    static GameModel* generateFromFile(LevelConfig levelConfig);

};