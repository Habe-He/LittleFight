 /*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名： KeyBoardMonitor
** 日期：   2014:10:24
** 说明：	监听键盘消息
** 其它：	
** 历史：2014:10:24 初始版本
*********************************************************************/
#pragma once
#include "cocos2d.h"

class KeyBoardMonitor : public cocos2d::Layer
{
public:
	KeyBoardMonitor(void);
	virtual ~KeyBoardMonitor(void);

	virtual bool init();
	CREATE_FUNC(KeyBoardMonitor);

public:
	/* 手机按键监听 */
	void keyBoardListenEvent();

	/* 加载手机返回键响应 */
	void mobileRuturn(cocos2d::EventKeyboard::KeyCode, cocos2d::Event *);
};

