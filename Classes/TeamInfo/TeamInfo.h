/*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名：   TeamInfo
** 日  期：   2015:1:23
** 说  明：	点击头像，队伍信息界面
** 其  它：	
** 历  史：	2015:1:23 初始版本
*********************************************************************/
#ifndef __TeamInfo__
#define __TeamInfo__
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace cocostudio;
using namespace ui;
USING_NS_CC_EXT;

#include "DataManager/DataManager.h"

enum TeamState
{
	TNor,				// 正常显示状态
	TSetup,			// 显示设置
};

class TeamInfo : public Layer
{
public:
	static Scene* scene();

	bool init();

	void closeButton(Ref* pSender, TouchEventType type);

	void closeCall();											// 关闭按钮回调

	int calcExp(int curExp);									// 返回当前剩余经验

	void musicCall(Ref* pSender);								// 音乐开关

	void effectCall(Ref* pSender);								// 音效开关

	void onEnter();
	void onExit();
	bool onTouchBegan(Touch *touch, Event *unused_event);

	CREATE_FUNC(TeamInfo);
private:
	ImageView* spriteView;									// 界面背景图
	cocos2d::ui::Widget* teamInfoUI;	
	vector<PlayerInfoRecvStruct > interPlayerInfoVector;				// 玩家信息网络数据
	vector<TeamUpgradeLocalStrcut > ruleVector;					// 战队升级规则
};
#endif