/*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名：   YiJiDangQian
** 日  期：   2015:1:23
** 说  明：	一骑当千
** 其  它：	
** 历  史：	2015:1:23 初始版本
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