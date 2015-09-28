 /*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名： TaskLayer
** 日期：   2014:12:29
** 说明：	每日任务
** 其它：	
** 历史：2014:12:29 初始版本
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"


class TaskLayer : public cocos2d::Layer
{
public:
	TaskLayer();
	~TaskLayer();

	static cocos2d::Scene* scene();

	bool init();
	CREATE_FUNC(TaskLayer);

protected:
	void addDailyQuest();
	void btnCloseClicked(cocos2d::Ref* pSender, cocos2d::ui::TouchEventType type);

	void btnGoTask(cocos2d::Ref* pSender, cocos2d::ui::TouchEventType type);
	void btnGoFinish(cocos2d::Ref* pSender, cocos2d::ui::TouchEventType type);

	//获取每日任务
	void getDailyQuestData();
private:
	cocos2d::ui::ScrollView	*m_ScrollTaskCellList;

	std::vector<int> whichTask;
	std::vector<int> numOfTask;
};