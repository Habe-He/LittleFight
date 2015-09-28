 /*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名： RoleResInfo
** 日期：   2015:4:17
** 说明：	角色结构信息
** 其它：	
** 历史：2015:4:17 初始版本
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include <map>
#include "DataManager/DataRecvEntities.h"

class RoleResInfo : public cocos2d::Ref
{
public:
	RoleResInfo(void);
	virtual ~RoleResInfo(void);

	static void init();
	static int getRoleResNum(std::string);
	static std::vector<std::string> roleInBattle(int);/* 获取上阵角色 */
	static std::vector<std::string> getRoleInBattle();

private:
	static std::map<std::string, int> _map;
	static bool _flag;
	static int _battle;
};

