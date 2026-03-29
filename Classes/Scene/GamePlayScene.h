#pragma once
#include "cocos2d.h"
#include "Controllers/GameController.h"

/**
 * @class GamePlayScene
 * @brief 游戏主运行场景类
 * @details 职责包括：
 * 1. 作为 Cocos2d-x 渲染树的根节点，承载游戏的所有视觉元素。
 * 2. 负责 GameController 的生命周期管理。
 * 3. 充当游戏启动的入口点，负责初始关卡的加载触发。
 */
class GamePlayScene : public cocos2d::Scene
{
public:
    GamePlayScene();
    ~GamePlayScene();
    /**
     * @brief 静态工厂方法：创建并返回 Scene 实例
     * @return cocos2d::Scene* 指向创建好的场景对象的指针
     */
    static cocos2d::Scene* createScene();
    /**
     * @brief 场景初始化回调
     * @details 在场景创建后立即调用。此处负责实例化控制器、绑定父节点并启动首个关卡。
     * @return bool 成功返回 true，失败返回 false
     */
    virtual bool init() override;

    CREATE_FUNC(GamePlayScene);
private:
    /** * @brief 游戏核心控制器
     * @note 采用手动 new/delete 管理，生命周期与当前 Scene 绑定
     */
    GameController* _gameController{nullptr};
};