#pragma once
#include <unordered_map>
#include <deque>
#include "Configs/LevelConfig.h"
#include "Configs/GameConfig.h"

class CardModel;

class GameModel {
public:
	GameModel();
	~GameModel();

	void addCardToPile(SlotID id, CardModel* card);

	CardModel* getTopCard(SlotID type);
	bool isCardAtTop(CardModel* card);
	void moveCard(SlotID from, SlotID to);

	std::unordered_map<SlotID, std::vector<CardModel*>>& getPiles();
private:
	std::unordered_map<SlotID, std::vector<CardModel*>> _piles;
};