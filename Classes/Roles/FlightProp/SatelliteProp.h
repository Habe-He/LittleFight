 /*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名： SatelliteProp
** 日期：   2015:2:13
** 说明：	环绕角色飞行道具基类
** 其它：	
** 历史：2015:2:13 初始版本
*********************************************************************/
#pragma once
#include "Roles/FlightProp/FlightProp.h"

/* skillInfo中yAtkDis为道具高度，FlightPropInfo中height为角度 */
class SatelliteProp : public FlightProp
{
public:
	SatelliteProp(void);
	virtual ~SatelliteProp(void);

	static SatelliteProp* create(Role *, const std::string&, FlightPropInfo);

	void runPropCollisionDetective();
	bool PropCollisionDetective();

protected:
	void update(float);
};

