 /*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名： RolePrestrain
** 日期：   2015:4:17
** 说明：	角色预加载
** 其它：	
** 历史：2015:4:17 初始版本
*********************************************************************/
#pragma once
#include "cocos2d.h"

class RolePrestrain : cocos2d::Ref
{
public:
	RolePrestrain(void);
	virtual ~RolePrestrain(void);

public:
	bool loading(int tag);									/* 预加载上阵角色 */

protected:
	void prestrainRoleArmatureRes(std::string , int);		/* 获取上阵角色资源 */

private:
	std::vector<std::string>			_vecPath;			/* 要加载的资源 */
};

