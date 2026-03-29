#include "StackManager.h"
#include "Views/CardView.h"
#include "Controllers/GameController.h"

StackManager::StackManager() {
}

StackManager::~StackManager() {
    clear();
}

void StackManager::clear() {
    _viewMap.clear();
}

CardView* StackManager::getCardViewByModel(CardModel* m) { 
    auto it = _viewMap.find(m);
    return (it != _viewMap.end()) ? it->second : nullptr;
}

void StackManager::addToMap(CardModel* model, CardView* view) {
    _viewMap[model] = view;
}