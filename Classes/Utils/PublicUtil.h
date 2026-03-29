#pragma once
#include "cocos2d.h"

class PublicUtil {
public:
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