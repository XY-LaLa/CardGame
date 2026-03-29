#include "GameModelFromLevelGenerator.h"
#include "Configs/CardResConfig.h"

USING_NS_CC;

GameModel* GameModelFromLevelGenerator::generateFromFile(LevelConfig levelConfig) {
    auto model = new GameModel();

    //处理Main牌阵
    for (const auto& data : levelConfig.playfield) {
        auto card = new CardModel(
            static_cast<CardSuitType>(data.suit),
            static_cast<CardFaceType>(data.face),
            data.position
        );
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
        model->addCardToPile(HAND_LEFT, card);
    }

    return model;
}
