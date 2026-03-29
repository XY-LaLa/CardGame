#pragma once
#include "cocos2d.h"

/**
 * @class PublicUtil
 * @brief 场景通用工具类
 * @details 职责包括：
 * 1. 提供跨节点的坐标计算辅助。
 * 2. 处理基于父节点尺寸比例的百分比定位逻辑。
 */
class PublicUtil {
public:
	/**
	 * @brief 计算子节点相对于父节点的百分比布局位置
	 * @param c 子节点 Sprite 引用
	 * @param f 父节点 Sprite 引用
	 * @param aspectRatio 目标位置相对于父节点宽高的比例（0.0f - 1.0f）
	 * @return cocos2d::Vec2 返回计算后的本地坐标
	 */
	static cocos2d::Vec2 getCardLoaclPositionByFather(cocos2d::Sprite& c, cocos2d::Sprite& f, cocos2d::Vec2 aspectRatio) {

		// 父节点尺寸
		cocos2d::Size cSize = c.getContentSize();
		cocos2d::Size fSize = f.getContentSize();
		// 子节点尺寸,锚点
		cocos2d::Vec2 cAnchor = c.getAnchorPoint();

		//父节点中按比例得到目标点（左下角为原点）
		cocos2d::Vec2 target = cocos2d::Vec2(fSize.width * aspectRatio.x,fSize.height * aspectRatio.y);
		//转换为子节点 position
		cocos2d::Vec2 result = cocos2d::Vec2(target.x ,target.y );

		return result;
	}

};