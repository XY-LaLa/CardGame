#pragma once
#include <stack>
#include "Models/UndoModel.h"

//用于管路回退系统
class UndoManager {
public:
	UndoManager();
	~UndoManager();

	void undo();
	void pushStack(UndoModel undoModel);

	//定义回调函数 在主控制器里调用移动函数
	using UndoCallback = std::function<void(CardModel*, SlotID, SlotID, bool)>;
	void setUndoHandler(UndoCallback handler);

	void clear();
private:
	//数据管理容器
	std::stack<UndoModel> _undoStack;
	UndoCallback _undoHandler = nullptr;
};