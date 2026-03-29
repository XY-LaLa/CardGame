#include "GameModel.h"
#include "CardModel.h"

GameModel::GameModel() {

}

GameModel::~GameModel() {
    // 遍历哈希表中所有的 vector（每个坑位）
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

bool GameModel::isCardAtTop(CardModel* card) {
    if (!card) return false;

    SlotID slotId = card->getSlotID();
    const auto& pile = _piles[slotId];

    // 1. 找到当前牌在 vector 中的位置
    auto it = std::find(pile.begin(), pile.end(), card);
    if (it == pile.end()) return false;

    // 定义当前牌的矩形区域 (使用 JSON 里的坐标)
    // 假设卡牌尺寸为 kCardWidth, kCardHeight
    cocos2d::Rect targetRect(
        card->getPosition().x - card.get / 2,
        card->getPosition().y - kCardHeight / 2,
        kCardWidth,
        kCardHeight
    );

    // 2. 检查所有排在它之后的牌（视觉上叠在它上面的牌）
    for (auto nextIt = std::next(it); nextIt != pile.end(); ++nextIt) {
        CardModel* upperCard = *nextIt;

        cocos2d::Rect upperRect(
            upperCard->getPosition().x - kCardWidth / 2,
            upperCard->getPosition().y - kCardHeight / 2,
            kCardWidth,
            kCardHeight
        );

        // 3. 判断矩形是否相交
        if (targetRect.intersectsRect(upperRect)) {
            return false; // 被压住了，不是栈顶
        }
    }

    return true; // 没有被任何上层牌压住
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