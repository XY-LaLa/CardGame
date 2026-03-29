#pragma once

#include "Models/GameModel.h"
#include "Models/CardModel.h"
#include "Configs/LevelConfig.h"
#include "Configs/CardResConfig.h"
#include "cocos2d.h"
#include "Utils/json.hpp"

class GameModelFromLevelGenerator {
public:
    static GameModel* generateFromFile(LevelConfig levelConfig);
};