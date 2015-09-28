/*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名：   EffectAction
** 日  期：   2015:5:22
** 说  明：	特效类（特别累）
** 其  它：	
** 历  史：	2015:5:22 初始版本
*********************************************************************/
#pragma once
#include "cocos2d.h"
USING_NS_CC;

class EffectAction : public Node
{
public:
	static EffectAction* getInstance();

	void unLockAnim();				// 仓库解锁

	void loadingEffect();				// 加载

	void buttonBack();				// 主界面功能按钮

	void drawoffEffect();				// 抽卡显示特效

	void fbEffect();					// 主界面副本特效

	void tieEffect();					// 主界面副本特效

	void trainEffect();				// 培养界面特效

	void callBack();

	void waitSignInEffect();      // 待 签到动画
};