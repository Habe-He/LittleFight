/*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ�����   YiJiDangQian
** ��  �ڣ�   2015:1:23
** ˵  ����	һ�ﵱǧ
** ��  ����	
** ��  ʷ��	2015:1:23 ��ʼ�汾
*********************************************************************/
#ifndef __YiJiDangQian__
#define __YiJiDangQian__
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace cocostudio;
using namespace ui;
#include "Scene/MainScene.h"

class YiJiDangQian : public Scene
{
public:
	bool init();

	void closeButton(Ref* pSender, TouchEventType type);

	CREATE_FUNC(YiJiDangQian);
};
#endif