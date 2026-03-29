#pragma once
#include "cocos2d.h"
#include "Configs/CardResConfig.h"
#include "Configs/LevelConfig.h"
#include "Configs/GameConfig.h"

/**
 * @class CardModel
 * @brief 扑克牌基础数据模型
 * @details 负责存储和管理单张扑克牌的所有属性，包括花色、点数、所属槽位及初始关卡配置坐标。
 * 纯粹作为数据载体。
 */
class CardModel {
public:
	/**
	 * @brief 构造函数
	 * @param suit 花色 (黑桃, 红桃, 梅花, 方块)
	 * @param face 点数 (A, 2-10, J, Q, K)
	 * @param position 初始逻辑坐标
	 */
	CardModel(CardSuitType suit, CardFaceType _face, cocos2d::Vec2 position);

	/** @name Getter 接口 */
	///@{
	CardSuitType getSuit() const;///< 获取花色
	CardFaceType getFace() const;///< 获取点数
	SlotID getSlotID()const;///< 获取当前所属堆栈ID
	cocos2d::Vec2 getPosition()const;///< 获取卡牌逻辑坐标
	bool getCanClick()const;///< 获取是否处于可点击状态
	///@}

	/** @name Setter 接口 */
	///@{
	void setSuit(CardSuitType suit);
	void setFace(CardFaceType face);
	void setSlotID(SlotID id);
	void setPosition(cocos2d::Vec2 pos);
	void setCanClick(bool canClick);
	///@}

private:
	CardSuitType _suit{ CST_NONE };///< 牌面花色
	CardFaceType _face{ CFT_NONE };///< 牌面点数
	SlotID _slotID{ HAND_LEFT };///< 当前卡牌所在的堆栈标识
	cocos2d::Vec2 _position;///< 在场景中的逻辑布局位置
	bool _canClick = false;///< 交互开关


};