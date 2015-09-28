/*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名： EEEquipCell
** 日期：   2015:6:17
** 说明：	装备表单元
** 其它：	
** 历史：2015:6:17 初始版本
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "DataManager/DataRecvEntities.h"

class EEEquipCell : public cocos2d::Node
{
public:
	EEEquipCell(void);
	virtual ~EEEquipCell(void);

	static EEEquipCell*	Create(EquipProptyStruct);
	virtual bool init(EquipProptyStruct);

public:
	bool changeStatus();											/* 转换选中与非选中状态 */
	EquipProptyStruct getEquipCellInfo();

	CC_SYNTHESIZE(int, _realExp, RealExp);							/* 最终利用的经验值（经验条满时，利用率不能达到最大） */

private:
	bool	_bSelectFlag;											/* 选中标记 */

	cocos2d::Sprite		*_spLight;									/* 高亮资源 */

	EquipProptyStruct	_stInfo;
};

