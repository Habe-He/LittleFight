 /*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名： CommonProp
** 日期：   2015:2:3
** 说明：	飞行道具公共类
** 其它：	
** 历史：2015:2:3 初始版本
*********************************************************************/
#pragma once
#include "Roles/FlightProp/FlightProp.h"

class CommonProp : public FlightProp
{
public:
	CommonProp(void);
	virtual ~CommonProp(void);

	static CommonProp* create(Role *, const std::string&, FlightPropInfo);
	void runPropCollisionDetective(float, cocos2d::Point);			/* 道具移动及开启碰撞检测 */

protected:
	void skillCallBack();
	void update(float);
};

