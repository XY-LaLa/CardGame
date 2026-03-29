#include "GameModelFromLevelGenerator.h"
#include "Configs/CardResConfig.h"

USING_NS_CC;
/**
 * @details
 * 该函数遵循单一职责原则，只负责“解析配置并创建对象”。
 * 内部通过循环遍历配置数组，将原始数值转换为强类型枚举，并根据位置分配槽位 ID。
 */
GameModel* GameModelFromLevelGenerator::generateFromFile(LevelConfig levelConfig) {
    // 实例化
    auto model = new GameModel();

    //处理Main牌阵
    for (const auto& data : levelConfig.playfield) {
        auto card = new CardModel(
            static_cast<CardSuitType>(data.suit),
            static_cast<CardFaceType>(data.face),
            data.position
        );
		/** * 槽位分配逻辑：!!!暂时写死，后续可根据实际需求调整
         * 以 540.0f（通常是屏幕中线）为界，将牌分配到左/右主牌阵槽位。
         * 这有助于后期根据不同区域执行不同的动画或遮挡算法。
         */
        SlotID sid = (data.position.x < 540.0f) ? MAIN_LEFT : MAIN_RIGHT;
        model->addCardToPile(sid, card);
    }

    //处理手牌堆
    for (const auto& data : levelConfig.stack) {
        auto card = new CardModel(
            static_cast<CardSuitType>(data.suit),
            static_cast<CardFaceType>(data.face),
            data.position
        );
        // 默认初始化在
        model->addCardToPile(HAND_LEFT, card);
    }

    return model;
}

