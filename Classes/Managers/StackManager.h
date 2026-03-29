#pragma once
#include "Models/GameModel.h"
#include "Models/CardModel.h"
#include "Views/GameView.h"
#include "Views/CardView.h"

class GameController;
/**
 * @class StackManager
 * @brief 手牌堆区域管理器
 * @details 职责：
 * 1. 管理 备用牌 和 底牌 的卡牌模型与视图映射。
 * 2. 与 PlayFieldManager 逻辑相似但职责隔离
 */
class StackManager {
public:
    StackManager();
    ~StackManager();
    /**
     * @brief 根据卡牌模型快速索引视图
     * @param m 卡牌模型指针
     * @return CardView* 视图指针
     */
    CardView* getCardViewByModel(CardModel* m);
    /**
     * @brief 建立模型与视图的映射关系
     * @param model 卡牌数据模型
     * @param view 卡牌精灵视图
     */
    void addToMap(CardModel*, CardView*);
    /** @brief 清空 */
    void clear();
private:

    std::unordered_map<CardModel*, CardView*> _viewMap;///< 映射表
};