#include "GameModel.h"
#include "CardModel.h"

GameModel::GameModel() {

}

GameModel::~GameModel() {
    // 遍历哈希表中所有的 vector
    for (auto& pair : _piles) {
        auto& pile = pair.second;
        // 遍历 vector 里的每一个 CardModel 指针并释放内存
        for (CardModel* card : pile) {
            delete card; // 释放内存
        }
        pile.clear();
    }
    _piles.clear();
}

void GameModel::addCardToPile(SlotID id, CardModel* card) {
    if (card) {
        _piles[id].push_back(card);
        card->setSlotID(id);
    }
}

// 获取某个堆的顶层牌
CardModel* GameModel::getTopCard(SlotID type) {
    auto& pile = _piles[type];
    return pile.empty() ? nullptr : pile.back();
}

// 判定某张牌是否在栈顶（即可点击）
bool GameModel::isCardAtTop(CardModel* card) {
    if (!card) return false;
    auto& pile = _piles[card->getSlotID()];
    return !pile.empty() && pile.back() == card;
}


// 移动牌：从一个堆移动到另一个堆
void GameModel::moveCard(SlotID from, SlotID to) {
    if (_piles[from].empty()) return;
    CardModel* card = _piles[from].back();
    _piles[from].pop_back();
    _piles[to].push_back(card);
    card->setSlotID(to); // 同步更新卡牌持有的类型
}


std::unordered_map<SlotID, std::vector<CardModel*>>& GameModel::getPiles() {
    return _piles;
}
// 核心匹配规则
bool GameModel::canMatch(CardModel * targetCard) {
    CardModel* wasteTop = getTopCard(HAND_RIGHT);
    if (!wasteTop) return true; // 底牌为空，随便放
    // 计算分值差值绝对值
    int diff = abs((int)targetCard->getFace() - (int)wasteTop->getFace());
    /**
     * 判定逻辑：
     * 1. diff == 1: 常规连续数字（如 5 和 6）
     * 2. diff == 12: 循环连续（A 为 1, K 为 13, 13-1=12, 满足 K 和 A 接龙）
     */
    return (diff == 1 || diff == 12);
}