/*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名： Wareroom
** 日期：   2014:9:19
** 说明：	  仓库
** 其它：	  
** 历史：	2014:9:19 初始版本
*********************************************************************/
#ifndef __WAREROOM_SCENE__
#define __WAREROOM_SCENE__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace cocostudio;
using namespace ui;

#include "Public/FontChina.h"
#include "Public/ToolFunc.h"
#include "Store/DrawoffDisplay.h"
#include "UserInfo/Define_Info.h"
#include "SimpleAudioEngine.h"
#include "Scene/MainScene.h"
#include "Public/EffectAction.h"
#include "NewComer/NewComer.h"

const int toolTipsTag = 1;
const int StatusBarTag = 2;
const int btnPropTag = 20;
const int btnEquipTag = 21;
const int btnChipTag = 22;

const int RightPanelTag = 32;
const int GridCount = 80;
const float FontSize = 16.0f;
const int Label_1 = 60;
const int Label_2 = 61;
const int LabelTipTag = 100;

enum btnEnum
{
	noneBtn,
	propBtn,
	equipBtn,
	chipBtn,
};

enum propTypeBtn
{
	noneTypeBtn,  // 空
	powerBtn,		// 可增加体力
	expBtn,		// 经验药水
	baoxiangBtn,	// 宝箱
	juanzhouBtn,	// 卷轴
	zaxiang,		// 杂项
};

enum equipType
{
	TypeNone,				// 空
	TypeArmour,			// 铠甲
	TypeHead,				// 头盔
	TypeDecorations,		// 饰品
	TypeWeapons,			// 武器
	TypeQi,				// 奇珍
	TypeYi				// 异宝
};

enum EquipColor
{
	NoneColor,
	WhiteColor,
	GreenColor,
	BlueColor,
	PurPleColor,
};

enum WareroomState
{
	StateNone,
	StateTips,
};

class Wareroom : public Layer
{
public:
	Wareroom();
	virtual ~Wareroom();

	bool init();

	static Scene* scene();
	
	void createProps(Ref* pSender, TouchEventType type);					// 生成道具	
	void createEquip(Ref* pSender, TouchEventType type);					// 创建装备	
	void createChip(Ref* pSender, TouchEventType type);					// 创建碎片	
	void expandBag(Ref* pSender, TouchEventType type);					// 扩展背包	
	void loadFrame(int id);											// 显示装备的格子以及加载物品	
	void closeButton(Ref* pSender, TouchEventType type);					// 关闭	
	void shift(Ref* pSender, TouchEventType type);							// 转换	
	void sell(Ref* pSender, TouchEventType type);							// 卖出 ----	经验药水、杂项、装备	
	void synthetic(Ref* pSender, TouchEventType type);						// 合成 -------  碎片	
	void useClick(Ref* pSender, TouchEventType type);						// 使用  ------- 卷轴、体力、宝箱
	
	void showInfo(int id, int btnID);										// 显示物品信息 ----- 物品的Index，三个按钮的ID	
	void setBrightButton(btnEnum btnIndex);								// 三个按钮明亮和Z轴
	bool onTouchBegan(Touch *touch, Event *unused_event);					
	virtual void onEnter();
	virtual void onExit();

	// 使用宝箱
	DrawoffGoodsStruct muBox(int id, int boxType);

	void createConfirmLayout(int btnIndex);

	void confirmButton(Ref* pSender, TouchEventType type);
	void cancelButton(Ref* pSender, TouchEventType type);

	CREATE_FUNC(Wareroom);

private:
	int diamond;													// 开启格子消耗的钻石
	int sellIndex;													// 点击物品的index
	int buttonIndex;													// 点击的哪个按钮（道具装备碎片）	
	int vectorSubscript;												// 仓库显示物品的数组下标
	int goodsID;													// 点击使用按钮记录使用物品的ID
	WareroomState wareroomState;										// 仓库状态（是否弹出提示）
	FontChina* mpFontChina;
	Layout* sellValuePanel;											// 卖出价格层
	cocos2d::ui::ScrollView* scrollView;									// 物品滚动层
	vector<WareroomCommonRecvStruct > interWareroomData;					// 网络请求到仓库物品信息	
	vector<WareroomCommonRecvStruct > tempWareroomVector;				// 用于处理格子没有物品的状态				
	vector<PropProptyStruct> localWareroomPropData;						// 道具基础属性
	vector<EquipProptyStruct > localWarerommEquipData;						// 装备基础属性
	vector<GeneralProptyStruct > localWarerommGeneralData;					// 碎片 ----- 武将
	vector<GeneralChipRecvStruct > localGeneralChipVector;					// 武将碎片合成规则
	vector<EquipChipRecvStruct > localEquipChipVector;						// 装备碎片合成规则	
	vector<BoxRecvStruct > localBoxVector;								// 宝箱数据解析的Json
	vector<PlayerInfoRecvStruct > interPlayerInfo;							// 玩家信息
	void showTips(string str);
	void showTipsCallBack();

	NewComer		*_comer;
};
#endif