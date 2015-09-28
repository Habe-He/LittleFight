/*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名： GameLevel
** 日期：   2014:11:14
** 说明：	副本类，处理游戏战斗时数据
** 其它：	
** 历史：2014:11:14 初始版本
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "MainFight.h"
#include "RoleLayer.h"
#include "GamePause.h"

class Counterpart : public cocos2d::Layer
{
public:
	Counterpart(void);
	virtual ~Counterpart(void);

	static cocos2d::Scene *scene();
	CREATE_FUNC(Counterpart);

	virtual bool init();
	virtual void onEnter();
	virtual void onExit();

public:
	void gameResume();												/* 复活，恢复游戏 */
	
protected:
	void loadMainFightScene();										/* 加载控制层 */
	void update(float dt);											/* 主将移动时，背景图移动判断 */
	void setSceneScroll(Role*);										/* 开启场景滚动检测 */
	void judgeWarSituation();										/* 判断战局 */
	void checkRoleInBgRegion();										/* 确保角色不移动到背景区域外 */
	void setRoleWarMsg(RoleWarMsg, RoleCamp = RoleCamp_Normal);		/* 设置角色战局标记 */
	void warGuidepost(float);										/* 过图时箭头指向 */
	void showPointGains();											/* 显示关卡收益 */

	void btnPauseClicked(cocos2d::Ref*, cocos2d::ui::TouchEventType);/* 暂停按钮点击消息响应 */
	void addTouchEventListener();
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event); 
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event); 
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	
	void resetGameTime();											/* 重置关卡通关时间 */
	void gameWin();													/* 胜利 */
	void gameLose();												/* 失败 */
	void gameTimer(float);											/* 游戏计时器 */
	void gameDoneRate();											/* 关卡完成度 */
	
private:
	int			m_iSceneID;											/* 当前场景ID */
	int			maxSceneNum;										/* 每个关卡场景数 */
	int			m_iGameTime;										/* 游戏倒计时 */
	int			m_iEnemyTotal;										/* 总敌人数 */
	bool		m_bTimeFlag;										/* 倒计时开关 */

	Role		*m_MainRole;										/* 主将 */
	MainFight	*m_hMainFight;										/* 战斗层 */
	RoleLayer	*m_hLayerRole;										/* 角色层 */
	GamePause	*m_hGamePause;										/* 游戏暂停 */
	RoleWarMsg	m_eSituation;										/* 战局 */

	cocos2d::Rect	m_rcMoveRegion;									/* 可移动区域 */
	cocos2d::Label	*m_labelTime;									/* 战斗时间显示 */
	cocos2d::Label	*m_labelDone;									/* 关卡完成度显示 */
	cocos2d::Sprite	*_spGo;
	cocos2d::Point	_ptMove;										/* 操控主将移动点 */
	cocos2d::EventListenerTouchOneByOne	*m_listener;
};

