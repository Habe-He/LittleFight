/*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ�����   DailyQuest
** ��  �ڣ�   2015:6:11
** ˵  ����	ÿ������
** ��  ����	
** ��  ʷ��	2015:6:11 ��ʼ�汾
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

	void showDailyCell();									// ��ʾÿһ��Ԫ����Ϣ

	void closeClick(Ref* sender, TouchEventType type);			// �ر�

	CREATE_FUNC(DailyQuest);
private:
	cocos2d::ui::ScrollView* dailyScrollView;					// ������
};