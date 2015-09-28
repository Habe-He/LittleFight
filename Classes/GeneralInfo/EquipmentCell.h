/*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名：   EquipmentCell
** 日  期：   2015:5:8
** 说  明：	单个装备的信息
** 其  它：	
** 历  史：	2015:5:8 初始版本
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;
using namespace std;

class EquipmentCell : public Node
{
public:
	bool init();

	void setImage(string nameString);

	void setSelect();

	CREATE_FUNC(EquipmentCell);

public:
	cocos2d::ui::Widget* equipmentPanel;									// 装备面板
	ImageView* equipment;											// 装备图片
	ImageView* equipBG;												// 装备背景
};