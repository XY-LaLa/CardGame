#include "PlayFieldManager.h"
#include "Views/CardView.h"
#include "Controllers/GameController.h"

PlayFieldManager::PlayFieldManager() {
}

PlayFieldManager::~PlayFieldManager() {
    clear();
}

void PlayFieldManager::clear() {
    _viewMap.clear();
}

CardView* PlayFieldManager::getCardViewByModel(CardModel* m) { 
    auto it = _viewMap.find(m);
    return (it != _viewMap.end()) ? it->second : nullptr;
}

void PlayFieldManager::addToMap(CardModel* model, CardView* view) {
    _viewMap[model] = view;
}