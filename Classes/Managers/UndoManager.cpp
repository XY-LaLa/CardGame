#include "UndoManager.h"


UndoManager::UndoManager() {

}
UndoManager::~UndoManager() {
    clear();
}

void UndoManager::clear() {
    //清空
    while (!_undoStack.empty()) _undoStack.pop();
}

void UndoManager::undo() {
    if (_undoStack.empty() || !_undoHandler) return;

    //获取最后一次操作
    UndoModel lastModel = _undoStack.top();
    _undoStack.pop();

    //通过回调执行回退
    _undoHandler(lastModel.card, lastModel.toSlot, lastModel.fromSlot, true);
}

void UndoManager::pushStack(UndoModel unModel) {
    _undoStack.push(unModel);
}

void UndoManager::setUndoHandler(UndoCallback handler) { _undoHandler = handler; }