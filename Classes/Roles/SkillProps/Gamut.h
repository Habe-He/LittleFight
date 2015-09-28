 /*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名： Gamut
** 日期：   2015:5:11
** 说明：	全范围技能
** 其它：	
** 历史：2015:5:11 初始版本
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "CommonProp.h"

class Gamut : public CommonProp
{
public:
	Gamut(void);
	virtual ~Gamut(void);
	
	static Gamut* create(Role *, const std::string&, FlightPropInfo);
	void runPropCollisionDetective();								/* 道具移动及开启碰撞检测 */
	void loadActionRes();
	void gamutSchedule(float);
	void PropCollisionDetective(float);

private:
	int		_resIndex;												/* 当前播放资源索引 */
	std::vector<std::string>	_vecRes;
};

