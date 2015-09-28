 /*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名： FontGuard
** 日期：   2015:2:28
** 说明：	商鞅技能3大字守护
** 其它：	
** 历史：2015:2:28 初始版本
*********************************************************************/
#pragma once
#include "Roles/FlightProp/SatelliteProp.h"

class FontGuard : public SatelliteProp
{
public:
	FontGuard(void);
	virtual ~FontGuard(void);
	
	static FontGuard* create(Role *, const std::string&, FlightPropInfo);
	void fontOver();

protected:
	void fontOverCallBack(cocos2d::Node *);	/* 动画播放完毕回调 */
};

