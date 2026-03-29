#pragma once
#include "Models/GameModel.h"
#include "Models/GameModel.h"
#include "Views/GameView.h"
#include "Views/CardView.h"

#include <unordered_map>

class CardView;
class GameController;

//创始化创建并加载手牌区Card
//管理手牌区的CardModel与CardView的关系
class PlayFieldManager {
public:
    PlayFieldManager();
    ~PlayFieldManager();
    // 提供映射表查询接口
    CardView* getCardViewByModel(CardModel* m);
    void addToMap(CardModel*, CardView*);
    void clear();
private:
    std::unordered_map<CardModel*, CardView*> _viewMap;
};