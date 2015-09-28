 /*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名： Skull
** 日期：   2015:2:13
** 说明：	孙膑技能3道具
** 其它：	
** 历史：2015:2:13 初始版本
*********************************************************************/
#pragma once
#include "Roles/SkillProps/CommonProp.h"

class Skull : public CommonProp
{
public:
	Skull(void);
	virtual ~Skull(void);

	static Skull* create(Role *, const std::string&, FlightPropInfo);

protected:
	void PropCollisionDetective(float);
};

