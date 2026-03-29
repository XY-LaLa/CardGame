#pragma once
#include "Configs/GameConfig.h"
#include "Managers/PlayFieldManager.h"
#include "Managers/StackManager.h"
#include "Views/CardView.h"
#include "Managers/UndoManager.h"

/**
 * @class GameController
 * @brief 游戏核心控制器类
 * @details 职责包括：
 * 1. 协调 GameModel与GameView的同步。
 * 2. 管理游戏生命周期（开始、重置、加载配置）。
 * 3. 处理用户交互逻辑的具体实现（点击扑克牌、点击撤销）。
 * 4. 控制卡牌在不同槽位（Slot）间的移动逻辑及撤销栈管理。
 */
class GameController {
public:
    GameController();
    ~GameController();
    /**
     * @brief 初始化并开始指定关卡
     * @param id 关卡枚举 ID
     */
	void startGame(LevelID id);
    /**
     * @brief 设置游戏场景的根节点(Scene)
     * @param node Cocos2d-x 场景节点指针
     */
    void setParentNode(cocos2d::Node* node);
    /**
     * @brief 响应卡牌被点击后的业务逻辑入口
     * @param cardView 被点击的卡牌视图对象
     */
    void onCardClicked(CardView* cardView);
private:
    /** @brief 遍历模型数据并初始化所有 CardView */
    void initCardViews();
    /** @brief 扑克牌点击的合规性规则检查 */
    void rules(CardView* cardView);
    /**
      * @brief 执行卡牌移动的核心逻辑
      * @param card 涉及的卡牌模型
      * @param from 起始槽位 ID
      * @param to 目标槽位 ID
      * @param isUndo 是否为回退操作
      */
    void executeMove(CardModel* card, SlotID from, SlotID to, bool isUndo);
private:
    cocos2d::Node* _rootNode{ nullptr };///< 挂载游戏视图的父节点

    //游戏数据
    GameModel* _gameModel{ nullptr };///< 游戏逻辑数据模型
    //游戏视图
    GameView* _gameView{ nullptr };///< 游戏主 UI 视图

    //子管理器（遵循单一职责原则）
    PlayFieldManager _playFieldManager;///< 管理主牌区的卡牌映射
    StackManager _stackManager;///< 管理手牌堆区的卡牌映射
    UndoManager _undoManager;///< 管理操作回退栈
};