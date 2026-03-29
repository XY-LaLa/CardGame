#pragma
#include<string>
#include "Configs/LevelConfig.h"
#include "Configs/GameConfig.h"
#include "Utils/json.hpp"
#include "cocos2d.h"
/**
 * @class LevelConfigLoader
 * @brief 关卡配置加载器
 * @details 职责包括：
 * 1. 使用 Cocos2d-x 的 FileUtils 读取外部存储的 JSON 关卡文件。
 * 2. 封装 nlohmann::json 解析逻辑，将数据填充至 LevelConfig 结构体。
 * 3. 实现关卡 ID 到物理路径的静态映射查询。
 */
class LevelConfigLoader {
public:
    /**
     * @brief 加载并解析指定关卡的配置文件
     * @param levelId 关卡枚举 ID
     * @return LevelConfig 返回解析后的配置结构体，若文件不存在则返回空配置
     */
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