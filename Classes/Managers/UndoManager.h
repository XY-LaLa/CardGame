#pragma once
#include <stack>
#include "Models/UndoModel.h"

/**
 * @class UndoManager
 * @brief 撤销系统管理器
 * @details 职责：
 * 1. 使用栈结构记录玩家的合法操作步骤。
 * 2. 通过回调机制解耦，将回退指令传回 GameController 执行。
 */
class UndoManager {
public:
	/** * @brief 回退操作回调定义
	 * 参数含义：CardModel*, 起始槽位ID, 目标槽位ID, 是否为回退执行
	 */
	using UndoCallback = std::function<void(CardModel*, SlotID, SlotID, bool)>;

	UndoManager();
	~UndoManager();
	/**
	 * @brief 执行撤销操作
	 * @details 弹出栈顶记录，并触发注册的回调函数将卡牌移回原位。
	 */
	void undo();
	/**
	 * @brief 将一次操作压入回退栈
	 * @param undoModel 包含操作详情（卡牌、来源、去向）的数据模型
	 */
	void pushStack(UndoModel undoModel);

	/**
	 * @brief 设置回退逻辑处理器
	 * @param handler 为 GameController 中的 executeMove 函数绑定
	 */
	void setUndoHandler(UndoCallback handler);
	/** @brief 清空回退栈 */
	void clear();
private:

	std::stack<UndoModel> _undoStack;///< 操作历史记录栈;
	UndoCallback _undoHandler = nullptr;///< 指向 Controller 处理函数的委托
};