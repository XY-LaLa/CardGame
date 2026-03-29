#pragma once
#include "Models/GameModel.h"
#include "Models/CardModel.h"
#include "Views/GameView.h"
#include "Views/CardView.h"

class GameController;
//创始化创建并加载主牌区Card
//管理主牌区的CardModel与CardView的关系
class StackManager {
public:
    StackManager();
    ~StackManager();
    CardView* getCardViewByModel(CardModel* m);
    void addToMap(CardModel*, CardView*);
    void clear();
private:

    std::unordered_map<CardModel*, CardView*> _viewMap;
};