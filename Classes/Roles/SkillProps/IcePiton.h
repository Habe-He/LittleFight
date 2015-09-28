 /*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名： IcePiton
** 日期：   2015:2:13
** 说明：	冰锥，扁鹊、庞暖技能3
** 其它：	
** 历史：2015:2:13 初始版本
*********************************************************************/
#pragma once
#include "Roles/FlightProp/SatelliteProp.h"

class IcePiton : public SatelliteProp
{
public:
	IcePiton(void);
	virtual ~IcePiton(void);

	static IcePiton* create(Role *, const std::string&, FlightPropInfo);
	
	bool PropCollisionDetective();
};

