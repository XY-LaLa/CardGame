#pragma once
#include <unordered_map>
#include <deque>
#include "Configs/LevelConfig.h"
#include "Configs/GameConfig.h"

class CardModel;

/**
 * @class GameModel
 * @brief 游戏全局数据模型管理器
 * @details 核心职责：
 * 1. 管理所有 SlotID 对应的卡牌容器（使用 unordered_map 维护多个 vector 栈）。
 * 2. 处理卡牌在容器间的转移。
 * 3. 核心规则判定（点数连续判定）。
 * 4. 负责所有 CardModel 实例的生命周期管理（内存释放）。
 */
class GameModel {
public:
	GameModel();
	/** @brief 析构函数：负责释放所有动态分配的 CardModel 指针，防止内存泄漏 */
	~GameModel();
	/**
	 * @brief 向指定堆栈添加卡牌
	 * @param id 目标槽位 ID
	 * @param card 卡牌模型指针
	 */
	void addCardToPile(SlotID id, CardModel* card);
	/**
	 * @brief 获取指定槽位顶部的卡牌
	 * @param type 槽位 ID
	 * @return CardModel* 若堆栈为空返回 nullptr
	 */
	CardModel* getTopCard(SlotID type);
	/**
	 * @brief 判定特定卡牌是否处于其所在堆栈的栈顶
	 * @param card 待检测的卡牌
	 * @return bool true 表示该牌可进行交互
	 */
	bool isCardAtTop(CardModel* card);
	/**
	 * @brief 逻辑层移动卡牌
	 * @param from 源槽位 ID
	 * @param to 目标槽位 ID
	 */
	void moveCard(SlotID from, SlotID to);
	/**
	 * @brief 匹配规则判定
	 * @details 判断目标牌是否能接入底牌
	 * 规则：目标牌与回收堆顶牌点数绝对值差 1，或者 A 与 K 循环匹配。
	 * @param targetCard 准备移动的牌
	 * @return bool 是否允许移动
	 */
	bool canMatch(CardModel* targetCard);
	/**
	 * @brief 获取所有堆栈数据的引用
	 * @return std::unordered_map<SlotID, std::vector<CardModel*>>&
	 */
	std::unordered_map<SlotID, std::vector<CardModel*>>& getPiles();
private:
	/** * @brief 数据存储结构
	 * Key: 槽位 ID (如主牌阵各点、手牌堆、回收堆)
	 * Value: 该槽位内按层级排序的卡牌指针列表
	 */
	std::unordered_map<SlotID, std::vector<CardModel*>> _piles;
};