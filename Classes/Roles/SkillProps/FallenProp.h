 /*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名： FallenProp
** 日期：   2015:4:16
** 说明：	下落的飞行道具（廉颇技能1）
** 其它：	
** 历史：2015:4:16 初始版本
*********************************************************************/
#pragma once
#include "Roles/FlightProp/FlightProp.h"

class FallenProp : public FlightProp
{
public:
	FallenProp(void);
	virtual ~FallenProp(void);
	
	static FallenProp* create(Role *, const std::string&, FlightPropInfo);
	void runPropCollisionDetective(float, cocos2d::Point);			/* 道具移动及开启碰撞检测 */
	void setPropYaxis(float);

protected:
	void skillCallBack();
	void update(float);
	void PropCollisionDetective(float);								/* 碰撞检测 */

private:
	float	_fPropYasix;
};

