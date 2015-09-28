/*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名：   Maidan
** 日  期：   2015:4:29
** 说  明：	
** 其  它：	
** 历  史：	2015:4:29 初始版本
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;
using namespace std;

#include "DataManager/DataManager.h"
#include "DataManager/DataRecvEntities.h"
#include "TrainCell.h"
#include "Scene/MainScene.h"
#include "GeneralInfo/GeneralDetails.h"
#include "PromptBox/PromptBox.h"
#include "Public/FontChina.h"
#include "NewComer/NewComer.h"

enum TypeButton
{
	TypeALL,					// 所有
	TypeLI,					// 力
	TypeZhi,					// 智
	TypeMin,					// 敏
	TypeStr,					// 强化
	TypePreset,				// 预设
};

enum CurState
{
	NoneState,					// 显示浏览状态
	EnhanceState,				// 强化状态
	PresetState,				// 选择上阵状态
};

class Maidan : public Layer
{
public:
	Maidan();
	virtual ~Maidan();

	bool init();
	static Scene* scene();

	void closeButton(Ref* pSender, TouchEventType type);				// 界面关闭按钮

	void typeButton(Ref* pSender, TouchEventType type);				// 界面右侧武将属性按钮

	void enhanceButton(Ref* pSender, TouchEventType type);				// 强化

	void preSetButton(Ref* pSender, TouchEventType type);				// 上阵武将预设

	void initGeneralData();										// 初始化武将数据

	void showGeneral();											// 滚动层显示武将信息

	void panelTouchCallback(Ref* pSender, TouchEventType type);			// 武将列表点击响应

	void initEnhanceProp();										// 初始化强化状态  药水

	void initPresetPanel();										// 点将上阵初始化

	void setButtonBirght(TypeButton buttonBright);						// 设置点击按钮的高亮

	void heroPhotoCallBack(Ref* pSender, TouchEventType type);			// 人物头像按钮回调

	void heroCloseCallBack(Ref* pSender, TouchEventType type);			// 人物头像删除回调

	void propIamgeCallBack(Ref* pSender, TouchEventType type);			// 道具回调

	int calcGeneralLevel(int exp);									// 计算武将等级	

	int calcPreFighting(vector<PointSetsRecvStruct > pointVec);				// 计算上阵武将的站斗力

	void onEnter();
	void onExit();	

	CREATE_FUNC(Maidan);

private:
	int i_ButtonFlag;												// 点击按钮的类型
	cocos2d::ui::ScrollView* mainScrollView;							// 界面上唯一的滚动层
	Layout* movePanel;											// 移动的面板
	Layout* rightButtonPanel;										// 右边的按钮
	Layout* presetPanel;											// 预设
	Layout* enhancePanel;										// 强化
	TextAtlas* fightingLabel;										// 战斗力
	FontChina* mpFontChina;										// 中文提示
	vector<MaidanStruct > interMaidanVector;							// 服务器读取到的练兵场数据
	vector<GeneralProptyStruct > selectedHeroVector;					// 选择上阵的武将
	vector<GeneralProptyStruct > curGeneralVector;						// 当前拥有武将属性
	vector<GeneralProptyStruct > tempGeneralVector;					// 根据按钮选择显示武将信息
	vector<GeneralProptyStruct > localGeneralVector;					// 本地武将基础数据
	vector<PropProptyStruct > localPropVectro;							// 本地道具数据
	vector<PointSetsRecvStruct > interPointSetsVector;					// 点将台网络数据
	vector<GeneralUpgradeStruct > localGeneralUpgradeVector;			// 武将技能升级规则
	vector<TeamInfoStruct > interTeamInfoVector;						// 获取战队信息
	vector<EquipProptyStruct > localEquipVector;						// 装备基础属性
	vector<EquipRefineStruct > localEquipRefineRuleVector;				// 装备精炼本地规则

	// 临时变量
	cocos2d::Point m_ptOriginleLoc;
	cocos2d::Point m_ptTouchLoc;
	Button* button_Str;											// 强化按钮
	Button* button_PreSet;										// 预设按钮

	int posIndex;												// 武将位置信息
	int propID;													// 强化使用的物品ID
	int goodsNum;												// 强化时物品数量
	CurState panelState;											// 界面当前状态
	ImageView* roleImage[ 4 ];									// 点将台人物头像四个位置
	ImageView* roleImageSelect[ 4 ];								// 点将台人物头像选中状态
	ImageView* roleButtonSelect[ 4 ];								// 点将台人物头像删除
	ImageView* propImage[ 3 ];									// 强化时三个物品的位置
	Text* propNum[ 3 ];											// 强化时三个物品的数量

	NewComer	*_comer;
};