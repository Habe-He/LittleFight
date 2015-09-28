/*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名：   StateBarNode
** 日  期：   2015:5:18
** 说  明：	状态栏
** 其  它：	
** 历  史：	2015:5:18 初始版本
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace cocostudio;
using namespace ui;

#include "SimpleAudioEngine.h"
#include "UserInfo/Define_Info.h"
#include "DataManager/DataManager.h"
#include "DataManager/DataRecvEntities.h"
#include "VIPPay/VIPPay.h"

const int STLayerColorFlag = 1;
const int STLayerChildFlag = 2;

enum StateChange
{
	StatePower,			// 金币、钻石、体力
	StateGS,				// 显示功勋
};

class StateBarNode : public Node
{
public:
	static StateBarNode* getInstance(StateChange stateChange);

	bool init(StateChange stateChange);

	void addCoinClick(Ref* pSender, TouchEventType type);							// 购买金币
		
	void addDiamondClick(Ref* pSender, TouchEventType type);						// 钻石充值

	void exchangeClick(Ref* pSender, TouchEventType type);							// 兑换按钮

	void refreshVaule();														// 数值刷新

	void showTipsCallBack();													// 删除提示

	virtual void onEnter();
	virtual void onExit();
	bool onTouchBegan(Touch *touch, Event *unused_event);

private:
	int i_Flag;																// 是否弹出
	FontChina* mpFontChina;													// 中文
	EventListenerTouchOneByOne* listener;										// 触摸事件
	cocos2d::ui::Widget* stateBarLayout;											// 状态栏
	vector<BuyCPLocalStruct > localCPVector;										// 购买金币和体力
	vector<PlayerInfoRecvStruct > interPlayerInfoVector;								// 玩家信息网络数据
};