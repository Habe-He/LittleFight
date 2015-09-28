 /*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名： GamePause
** 日期：   2015:7:31
** 说明：	战斗暂停UI
** 其它：	
** 历史：2015:7:31 初始版本
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class GamePause : public cocos2d::Layer
{
public:
	GamePause(void);
	virtual ~GamePause(void);

	bool init();
	CREATE_FUNC(GamePause);

public:
	void loadPauseScene();											/* 加载暂停界面 */
	void btnPauseClicked(cocos2d::Ref*, cocos2d::ui::TouchEventType);/* 暂停按钮点击消息响应 */
	void setEnabled(bool);

private:
	cocos2d::ui::Widget		*m_hUIPause;
};

