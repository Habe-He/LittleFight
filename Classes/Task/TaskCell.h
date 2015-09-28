/*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ����� TrainCell
** ���ڣ�   2014:10:9
** ˵����	�����б�Ԫ
** ������	
** ��ʷ��	2014:10:9 ��ʼ�汾
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

	//��������ֵ,�жϸ������Ƿ����
	void setTaskDone(int num);

	cocos2d::ui::Button* began;
	cocos2d::ui::Button* goToFinish;

protected:
	/* cell�����Ӧ���� */
	void panelTouchCallback(cocos2d::Ref*, cocos2d::ui::TouchEventType);

private:
	cocos2d::Point m_ptOriginleLoc;
	cocos2d::Point m_ptTouchLoc;

	cocos2d::ui::ImageView* finishPic;
};
