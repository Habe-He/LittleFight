/*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名： TrainCell
** 日期：   2014:10:9
** 说明：	练兵长列表单元
** 其它：	
** 历史：	2014:10:9 初始版本
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace cocostudio;
using namespace ui;

class SelectRoleCell : public cocos2d::Node
{
public:
	SelectRoleCell(void);
	virtual ~SelectRoleCell(void);

	bool init();

	CREATE_FUNC(SelectRoleCell);

public:
	void setCellName(const char *name);
	void setCellLevel(const int Level);
	void setCellStar(const int star);
	void setCellImage(const char *imgRoot);
	void setCellNum(const int star);
	int getCellNum();
	void setSelected();
	ImageView* roleImage;

private:
	cocos2d::ui::Widget *m_WidgetTrainCell;
	
	float	m_fRateX;
	float	m_fRateY;
	int strNum;
};
