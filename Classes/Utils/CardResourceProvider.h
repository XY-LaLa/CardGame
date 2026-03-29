#pragma once
#include <string>
#include "Configs/GameConfig.h"
#include "Configs/CardResConfig.h"
#include "cocos2d.h"

/**
 * @class CardResourceProvider
 * @brief 扑克牌资源路径提供者
 * @details 职责包括：
 * 1. 统一管理扑克牌资源（大数字、小数字、花色图标）的路径命名规则。
 * 2. 将强类型枚举（CardSuitType, CardFaceType）转换为对应的字符串标识。
 * 3. 屏蔽底层文件命名细节，为 CardView 提供标准化的资源查找接口。
 */
class CardResourceProvider {
public:
    /**
     * @brief 根据卡牌属性获取所有关联资源的路径
     * @param suit 花色枚举
     * @param face 点数枚举
     * @return CardData 包含大图、小图和花色图标路径的结构体
     */
    static CardData getPathsForCard(CardSuitType suit, CardFaceType face) {
        CardData p;

		std::string colorStr = cardColorToString(suit);//根据花色获取颜色字符串
		std::string faceStr = cardFaceToString(face);//获取数字字符串
		std::string suitStr = cardSuitToString(suit);//获取花色字符串

		//构建资源路径
        p.bigNumPath = cocos2d::StringUtils::format("Assets/number/big_%s_%s.png", colorStr.c_str(), faceStr.c_str());
        p.smallNumPath = cocos2d::StringUtils::format("Assets/number/small_%s_%s.png", colorStr.c_str(), faceStr.c_str());
        p.suitIconPath = cocos2d::StringUtils::format("Assets/suits/%s.png", suitStr.c_str());

        return p;
    }

private:
    /** @brief 将点数枚举转换为文件名字符串（如 CFT_ACE -> "A"） */
    static std::string cardFaceToString(CardFaceType face) {
        std::string faceName = getNumString(face);
        return faceName;
    }
    /** @brief 根据花色判定红黑颜色（红桃/方块为 red，其余为 black） */
    static std::string cardColorToString(CardSuitType suit) {
        std::string result = "black";
        if (suit == CST_DIAMONDS || suit == CST_HEARTS) {
            result = "red";
        }
        return result;
    }
    /** @brief 将花色枚举转换为文件名字符串（如 "heart", "spade"） */
    static std::string cardSuitToString(CardSuitType suit) {
        if (suit < 0 || suit >= CST_NUM_CARD_SUIT_TYPES) return "";
        std::string suitName[] = { "club", "diamond", "heart", "spade" };
        return suitName[suit];
    }

    /** @brief 内部实现：处理 A, J, Q, K 的特殊字符转换及数字转字符串 */
    static std::string getNumString(CardFaceType face) {
        switch (face) {
        case CFT_ACE:   return "A";
        case CFT_JACK:  return "J";
        case CFT_QUEEN: return "Q";
        case CFT_KING:  return "K";
        default:
            return std::to_string((int)face + 1);
        }
    }
};