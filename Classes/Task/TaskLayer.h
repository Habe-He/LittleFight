 /*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ����� TaskLayer
** ���ڣ�   2014:12:29
** ˵����	ÿ������
** ������	
** ��ʷ��2014:12:29 ��ʼ�汾
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

	//��ȡÿ������
	void getDailyQuestData();
private:
	cocos2d::ui::ScrollView	*m_ScrollTaskCellList;

	std::vector<int> whichTask;
	std::vector<int> numOfTask;
};