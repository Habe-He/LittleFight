/*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名： Store
** 日期：   2014:9:19
** 说明：	  商人界面
** 其它：	  
** 历史：	2014:9:19 初始版本
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;
using namespace cocostudio;
using namespace ui;

#include "DrawoffDisplay.h"
#include "StoreProp.h"
#include "UserInfo/Define_Info.h"
#include "SimpleAudioEngine.h"
#include "Scene/MainScene.h"
#include "DataManager/DataSendEntities.h"
#include "ConfirmationBox/ConfirmationBox.h"
#include "DataManager/DataRecvEntities.h"
#include "Public/FontChina.h"
#include "DataManager/DataManager.h"
#include "NewComer/NewComer.h"


const int Store_StatusBarTag = 2;
const int ButtonDrawoff = 10;// 抽卡按钮tag值
const int ButtonMyStore = 11;// 神秘商店按钮tag值
const int StateBarFlag = 12;// UI界面上方金币钻石体力按钮的父类节点的tag值
const int refreshDiamondNum= 5;// 神秘商店刷新一次所需钻石数量

class Store : public cocos2d::Scene
{
public:
	Store();
	virtual ~Store();

	virtual void onEnter();
	virtual void onExit();

	bool init();

	void initData();

	CREATE_FUNC(Store);

	void coinDrawoffTenButton(Ref* pSender, TouchEventType type);						//金币抽卡按钮触发事件

	void diamondDrawoffButton(Ref* pSender, TouchEventType type);						//钻石抽卡按钮触发事件

	void diamondDrawoffTenButton(Ref* pSender, TouchEventType type);						//10倍钻石抽卡按钮触发事件
	
	void closeBtn(cocos2d::Ref* , cocos2d::ui::TouchEventType);							// 关闭按钮 

	void createTeachNode();														// 创建指引

	void refreshButtonEnvent(Ref* pSender, TouchEventType type);							// 刷新按钮触发事件
	void refreshTimeDisplay();														// 刷新时间显示
	void displayGoodsInfo();														// 显示商品信息
	void goodsEnventImage(Ref* pSender, TouchEventType type);							// 商品点击触发事件（购买）


private:
	Button* btnClose;															// 界面关闭按钮
	Button* coinTenButton;														// 金币按钮
	Button* diamondButton;														// 钻石按钮
	Button* diamondTenButton;
	Text* coinLabel;                                                            // 金币数量显示
	Text* diamondLabel;															// 钻石数量显示
	Layout* drawoffPanel;															// 抽卡Panel
	Text* refreshTimeLabel;														// 刷新时间显示
	Button* refreshButton;														// 刷新按钮
	Text* consumeDiamondLabel;													// 刷新消耗钻石显示
	ImageView* goodsImage[8];													// 物品图片
	Text* numLabel[8];															// 物品数量
	Text* coinDiamondNumLabel[8];													// 购买物品需要的金币数或钻石数
	Text* goodsNameLabel[8];														// 物品名称
	ImageView* coinImage[8];														// 金币图片
	ImageView* diamondImage[8];													// 钻石图片
	ImageView* lightedImage[8];													// 点亮图片,表示售罄状态
	 FontChina* mpFontChina;														// 抽卡获取到的信息
	FontChina* pFontChina;														// 中文字体
	DrawoffGoodsStruct _coinDrawoffGoodsVector(int id);
	DrawoffGoodsStruct _diamondDrawoffGoodStruct(int id);
	vector<DrawoffRecvStruct> localDrawoffVector;
	vector<PlayerInfoRecvStruct > interPlayerInfoVector;									// 玩家信息网络数据
	vector<ServiceDayTimeRecvStruct > interServiceDayVector;								// 服务器当前时间
	vector<StoreLocalDataStruct >  localGoodsVector;
	vector<DrawoffIDRecvStruct > localDrawoffIDVector;									// 抽取物品的表
	vector<GeneralProptyStruct > generalProptyVector;									// 武将基础属性		
	vector<StoreListRecvStruct > storeListVector;										// 商品列表信息
	vector<storeBuyGoodsStruct > buyInfoVector;										// 购买商品信息
	vector<WareroomGridRecvStruct > interWareroomGridVector;							// 仓库剩余格子

	NewComer	*_comer;
};