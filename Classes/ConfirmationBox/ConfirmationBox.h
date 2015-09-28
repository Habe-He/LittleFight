/*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名：   ConfirmationBox
** 日  期：   2015:5:19
** 说  明：	确认框
** 其  它：	
** 历  史：	2015:5:19 初始版本
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;
using namespace cocostudio;
using namespace ui;
using namespace std;

#include "VIPPay/VIPPay.h"
#include "StateBar/StateBarNode.h"
#include "Public/FontChina.h"

enum BoxState
{
	StateNoCoin,		// 金币不足
	StateNoDiamond,	// 钻石不足
	StateBuyPropGrid,	// 购买道具格子
	StateBuyEquipGrid,	// 购买道具格子
	StateChipGrid,		// 购买碎片格子
	StateMaxCoin,		// 购买金币次数到达上限
	StateMaxDiamond,	// 购买体力次数到达上限
};

class ConfirmationBox : public Node
{
public:
	static ConfirmationBox* getInstance(BoxState boxState);							// 参数为每个界面的提示，位置默认屏幕中心位置

	bool init(BoxState boxState);

	void cancelButton(Ref* pSender, TouchEventType type);							// 取消
	void confirmButton(Ref* pSender, TouchEventType type);							// 确定
	void exchange();														// 根据状态设置文字显示
	void setPromptText(string promptString);										// 设置提示文字

	virtual void onEnter();
	virtual void onExit();
	bool onTouchBegan(Touch *touch, Event *unused_event);

	Text* promptText;														// 提示文字
	BoxState eBoxState;														// 枚举
	FontChina* mpFontChina;
};