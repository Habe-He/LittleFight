/*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名： TrainCell
** 日期：   2014:10:9
** 说明：	任务列表单元
** 其它：	
** 历史：	2014:10:9 初始版本
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class TaskCell : public cocos2d::Node
{
public:
	TaskCell(void);
	virtual ~TaskCell(void);

	bool init();
	CREATE_FUNC(TaskCell);

	//根据输入值,判断该任务是否完成
	void setTaskDone(int num);

	cocos2d::ui::Button* began;
	cocos2d::ui::Button* goToFinish;

protected:
	/* cell点击响应函数 */
	void panelTouchCallback(cocos2d::Ref*, cocos2d::ui::TouchEventType);

private:
	cocos2d::Point m_ptOriginleLoc;
	cocos2d::Point m_ptTouchLoc;

	cocos2d::ui::ImageView* finishPic;
};
