/*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名：   StoreB
** 日  期：   2015:7:9
** 说  明：	
** 其  它：	购买物品界面
** 历  史：	2015:7:9 初始版本
*********************************************************************/
#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;
using namespace cocostudio;
using namespace ui;
using namespace std;

#include "Public/FontChina.h"
#include "DataManager/DataRecvEntities.h"
#include "NewComer/NewComer.h"

struct SellGoods
{
	int goodsID;			// 物品名称
	int goodsNum;			// 物品数目
	int goodsPrice;			// 物品价格
};

enum StPanel
{
	NoState,
	TipsState,
};

class StoreB : public Scene
{
public:
	StoreB();
	virtual ~StoreB();
	
	bool init();

	void closeButton(Ref* pSender, TouchEventType type);						// 关闭

	void comfirmButton(Ref* pSender, TouchEventType type);						// 确定

	void cancleButton(Ref* pSender, TouchEventType type);						// 取消

	void dButton(Ref* pSender, TouchEventType type);							// 详情

	void initData();														// 物品初始化

	vector<SellGoods > sellGoodsVector;										// 卖出物品数组

	CREATE_FUNC(StoreB);

	virtual void onEnter();
	virtual void onExit();
	bool onTouchBegan(Touch *touch, Event *unused_event);

private:
	EventListenerTouchOneByOne* listener;									// 触摸
	StPanel stPanel;													// 界面状态
	FontChina* mpFontChina;												// 中文字体
	vector<PlayerInfoRecvStruct > interPlayerVector;								// 玩家信息

	NewComer	*_comer;
};
