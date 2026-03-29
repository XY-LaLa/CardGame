#pragma once
#include "Models/CardModel.h"
#include "cocos2d.h"

/**
 * @class UndoModel
 * @brief 撤销操作的数据快照
 * @details 记录单次移动操作的完整上下文。当玩家执行“撤销”时，
 * UndoManager 会读取此模型并通知 Controller 进行反向移动。
 */
class UndoModel {
public:
    CardModel* card;///< 发生移动的卡牌对象指针
    SlotID fromSlot;///< 移动前的原始槽位
    SlotID toSlot;///< 移动后的目标槽位
};