#pragma once
#include "Models/GameModel.h"
#include "Models/GameModel.h"
#include "Views/GameView.h"
#include "Views/CardView.h"

#include <unordered_map>

class CardView;
class GameController;

/**
 * @class PlayFieldManager
 * @brief 主牌区管理器
 * @details 职责：
 * 1. 维护主牌区（PlayField）中 CardModel 与 CardView 的映射关系。
 * 2. 提供 O(1) 复杂度的快速查询，方便根据逻辑层数据找到对应的视图对象。
 */
class PlayFieldManager {
public:
    PlayFieldManager();
    ~PlayFieldManager();
    /**
     * @brief 根据卡牌模型获取对应的视图
     * @param m 指向 CardModel 的指针
     * @return CardView* 对应的视图指针，若未找到则返回 nullptr
     */
    CardView* getCardViewByModel(CardModel* m);
    /**
     * @brief 建立模型与视图的映射关系
     * @param model 卡牌数据模型
     * @param view 卡牌精灵视图
     */
    void addToMap(CardModel*, CardView*);
    /** @brief 清空映射表 */
    void clear();
private:
    /** @brief 映射容器：Key 为数据模型指针，Value 为视图指针 */
    std::unordered_map<CardModel*, CardView*> _viewMap;
};