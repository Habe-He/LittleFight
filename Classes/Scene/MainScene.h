/*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名： MainScene
** 日期：   2014:9:19
** 说明：	  登陆后主界面
** 其它：	  界面待定，滚动时只能点击空白区域，在正式版时使用CS设置 ScrollView编辑
** 历史：	2014:9:19 初始版本
*********************************************************************/
#ifndef  __MAIN_SCENE__
#define __MAIN_SCENE__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace cocostudio;
using namespace ui;

#include "TeamInfo/TeamInfo.h"
#include "UserInfo/Define_Info.h"
#include "YiJiDangQian/YiJiDangQian.h"
#include "Store/Store.h"
#include "JiXiaXueGong/JiXiaXueGong.h"
#include "VIPPay/VIPPay.h"
#include "Public/Micro_Def.h"
#include "Train/Maidan.h"
#include "UserInfo/UserData.h"
#include "StateBar/StateBarNode.h"
#include "Public/FontChina.h"
#include "Public/EffectAction.h"

const int LayeColorFlag = 10;
const int LayerChildFlag = 11;

enum BtnEnum
{
	EtnJx,
	EtnTrian,
	EtnJiuGuan,
	EtnStore,
	EtnWareroom,
	EtnTie,
	EtnYJ,
	EtnFB,
};

class MainScene : public cocos2d::Layer
{
public:
	MainScene();
	~MainScene();

	static Scene* scene();

	void trainButton(Ref* sender, TouchEventType type);

	void battleCtrl(Ref* pSender, TouchEventType type);

	void wareroom(Ref* pSender, TouchEventType type);

	void store(Ref* pSender, TouchEventType type);								// 酒馆

	void smithy(Ref* pSender, TouchEventType type);

	void YiJiDangQian(Ref* pSender, TouchEventType type);

	void JiXiaXueGong(Ref* pSender, TouchEventType type);

	void heroButton(Ref* pSender, TouchEventType type);							// 人物头像

	void rewardClick(Ref* pSender, TouchEventType type);							// 成就

	void otherClick(Ref* pSender, TouchEventType type);								// 其他游戏

	void storebClick(Ref* pSender, TouchEventType type);							// 购买物品商店

	void challengeClick(Ref* pSender, TouchEventType type);							// 挑战（副本）

	void createTeach();														// 创建引导教程
	void teachCB();

	void update(float dt);

	bool init();

	void initData();

	void playInfoShow();													// 显示玩家信息

	virtual void onEnter();
	virtual void onExit();	
	
	CREATE_FUNC(MainScene);

private:
	cocos2d::ui::ScrollView* mianScrollView;									// 滚动层
	vector<TeamInfoStruct > interTeamInfoVector;								// 战队等级信息网络数据
	vector<PlayerInfoRecvStruct > interPlayerInfoVector;							// 玩家信息
	Layout* buttomPanel;													// 底部按钮层
};
#endif