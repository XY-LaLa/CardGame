#pragma once
#include <string>
#include "Configs/GameConfig.h"
#include "Configs/CardResConfig.h"
#include "cocos2d.h"

class CardResourceProvider {
public:
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
	//获取数字部分字符串
    static std::string cardFaceToString(CardFaceType face) {
        std::string faceName = getNumString(face);
        return faceName;
    }
    //获取颜色部分字符串
    static std::string cardColorToString(CardSuitType suit) {
        std::string result = "black";
        if (suit == CST_DIAMONDS || suit == CST_HEARTS) {
            result = "red";
        }
        return result;
    }
    //获取花色部分字符串
    static std::string cardSuitToString(CardSuitType suit) {
        if (suit < 0 || suit >= CST_NUM_CARD_SUIT_TYPES) return "";
        std::string suitName[] = { "club", "diamond", "heart", "spade" };
        return suitName[suit];
    }

	//获取数字字符串具体实现
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