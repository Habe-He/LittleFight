/*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ�����   JiXiaXueGong
** ��  �ڣ�   2015:1:23
** ˵  ����	���ѧ��
** ��  ����	
** ��  ʷ��	2015:1:23 ��ʼ�汾
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace cocostudio;
using namespace ui;

class JiXiaXueGong : public Scene
{
public:
	bool init();
	CREATE_FUNC(JiXiaXueGong);

protected:
	void jixiaButtonClick(Ref* pSender, TouchEventType type);

private:
};