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

CardView* PlayFieldManager::getCardViewByModel(CardModel* m) { return _viewMap[m]; }

void PlayFieldManager::addToMap(CardModel* model, CardView* view) {
    _viewMap[model] = view;
}