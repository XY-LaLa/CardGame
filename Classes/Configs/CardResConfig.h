#pragma once
#include <string>
#include <cocos2d.h>

/**
 * @struct CardData
 * @brief 单张卡牌的资源路径数据包
 * @details 包含构成一张完整扑克牌所需的全部图片路径信息。
 */
struct CardData
{
    std::string bigNumPath;
    std::string smallNumPath;
    std::string suitIconPath;
    std::string cardBack = "Assets/card_general.png";

	cocos2d::Vec2 kAnchorPoint = cocos2d::Vec2(0.5f, 0.5f);
};

/**
 * @enum CardSuitType
 * @brief 扑克牌花色枚举
 */
enum CardSuitType
{
    CST_NONE = -1,
    CST_CLUBS,      // 梅花
    CST_DIAMONDS,   // 方块
    CST_HEARTS,     // 红桃
    CST_SPADES,     // 黑桃
    CST_NUM_CARD_SUIT_TYPES
};

/**
 * @enum CardFaceType
 * @brief 扑克牌数字点数枚举
 * @details 内部值 0-12 分别对应 A 到 K。
 */
enum CardFaceType
{
    CFT_NONE = -1,
    CFT_ACE,
    CFT_TWO,
    CFT_THREE,
    CFT_FOUR,
    CFT_FIVE,
    CFT_SIX,
    CFT_SEVEN,
    CFT_EIGHT,
    CFT_NINE,
    CFT_TEN,
    CFT_JACK,
    CFT_QUEEN,
    CFT_KING,
    CFT_NUM_CARD_FACE_TYPES
};