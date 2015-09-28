/*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名：   DailyQuest
** 日  期：   2015:6:11
** 说  明：	每日任务
** 其  它：	
** 历  史：	2015:6:11 初始版本
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace cocostudio;
using namespace ui;

class DailyQuest : public Scene
{
public:
	bool init();

	void showDailyCell();									// 显示每一单元的信息

	void closeClick(Ref* sender, TouchEventType type);			// 关闭

	CREATE_FUNC(DailyQuest);
private:
	cocos2d::ui::ScrollView* dailyScrollView;					// 滚动层
};