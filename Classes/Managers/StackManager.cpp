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

CardView* StackManager::getCardViewByModel(CardModel* m) { return _viewMap[m]; }

void StackManager::addToMap(CardModel* model, CardView* view) {
    _viewMap[model] = view;
}