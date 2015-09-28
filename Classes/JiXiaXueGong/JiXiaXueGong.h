/*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名：   JiXiaXueGong
** 日  期：   2015:1:23
** 说  明：	稷下学宫
** 其  它：	
** 历  史：	2015:1:23 初始版本
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