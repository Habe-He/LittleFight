 /*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名： RoleCreate
** 日期：   2015:1:31
** 说明：	角色构造器
** 其它：	
** 历史：2015:1:31 初始版本
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "Roles/Role/Role.h"


class RoleCreate : public cocos2d::Ref
{
public:
	RoleCreate(void);
	virtual ~RoleCreate(void);

public:
	static Role* create(std::string, RoleCreMode, float = ResourceScale);

protected:
	static void loadRoleArmatureRes(std::string , int);
};

