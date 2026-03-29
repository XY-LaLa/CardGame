#pragma
#include<string>
#include "Configs/LevelConfig.h"
#include "Configs/GameConfig.h"
#include "Utils/json.hpp"
#include "cocos2d.h"

class LevelConfigLoader {
public:
	static LevelConfig loadLevelConfig(LevelID levelId) {
        // ID 找路径
        std::string relativePath = levelTable[static_cast<size_t>(levelId)];
        auto fileUtils = cocos2d::FileUtils::getInstance();
        std::string fullPath = fileUtils->fullPathForFilename(relativePath);
        std::string content = fileUtils->getStringFromFile(fullPath);
        LevelConfig config;
        if (content.empty()) {
            return config;
        }

        //解析JSON填充到LevelConfig结构体
        auto j = nlohmann::json::parse(content);

        for (auto& item : j["Playfield"]) {
            config.playfield.push_back({
                item["CardFace"].get<int>(),
                item["CardSuit"].get<int>(),
                cocos2d::Vec2(item["Position"]["x"], item["Position"]["y"])
                });
        }
        for (auto& item : j["Stack"]) {
            config.stack.push_back({
                item["CardFace"].get<int>(),
                item["CardSuit"].get<int>(),
                cocos2d::Vec2(item["Position"]["x"], item["Position"]["y"])
                });
        }
        return config;
    }
};