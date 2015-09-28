 /*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名： EERoleCell
** 日期：   2015:6:17
** 说明：	角色表单元
** 其它：	
** 历史：2015:6:17 初始版本
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "DataManager/DataRecvEntities.h"

class EERoleCell : public cocos2d::Node
{
public:
	EERoleCell(void);
	virtual ~EERoleCell(void);

	static EERoleCell*	Create(GeneralProptyStruct);
	virtual bool init(GeneralProptyStruct);

public:
	GeneralProptyStruct getRoleCellInfo();

private:
	GeneralProptyStruct		_stInfo;
};

