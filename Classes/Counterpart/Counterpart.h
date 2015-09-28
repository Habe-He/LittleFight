/*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ����� GameLevel
** ���ڣ�   2014:11:14
** ˵����	�����࣬������Ϸս��ʱ����
** ������	
** ��ʷ��2014:11:14 ��ʼ�汾
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
	void gameResume();												/* ����ָ���Ϸ */
	
protected:
	void loadMainFightScene();										/* ���ؿ��Ʋ� */
	void update(float dt);											/* �����ƶ�ʱ������ͼ�ƶ��ж� */
	void setSceneScroll(Role*);										/* ��������������� */
	void judgeWarSituation();										/* �ж�ս�� */
	void checkRoleInBgRegion();										/* ȷ����ɫ���ƶ������������� */
	void setRoleWarMsg(RoleWarMsg, RoleCamp = RoleCamp_Normal);		/* ���ý�ɫս�ֱ�� */
	void warGuidepost(float);										/* ��ͼʱ��ͷָ�� */
	void showPointGains();											/* ��ʾ�ؿ����� */

	void btnPauseClicked(cocos2d::Ref*, cocos2d::ui::TouchEventType);/* ��ͣ��ť�����Ϣ��Ӧ */
	void addTouchEventListener();
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event); 
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event); 
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	
	void resetGameTime();											/* ���ùؿ�ͨ��ʱ�� */
	void gameWin();													/* ʤ�� */
	void gameLose();												/* ʧ�� */
	void gameTimer(float);											/* ��Ϸ��ʱ�� */
	void gameDoneRate();											/* �ؿ���ɶ� */
	
private:
	int			m_iSceneID;											/* ��ǰ����ID */
	int			maxSceneNum;										/* ÿ���ؿ������� */
	int			m_iGameTime;										/* ��Ϸ����ʱ */
	int			m_iEnemyTotal;										/* �ܵ����� */
	bool		m_bTimeFlag;										/* ����ʱ���� */

	Role		*m_MainRole;										/* ���� */
	MainFight	*m_hMainFight;										/* ս���� */
	RoleLayer	*m_hLayerRole;										/* ��ɫ�� */
	GamePause	*m_hGamePause;										/* ��Ϸ��ͣ */
	RoleWarMsg	m_eSituation;										/* ս�� */

	cocos2d::Rect	m_rcMoveRegion;									/* ���ƶ����� */
	cocos2d::Label	*m_labelTime;									/* ս��ʱ����ʾ */
	cocos2d::Label	*m_labelDone;									/* �ؿ���ɶ���ʾ */
	cocos2d::Sprite	*_spGo;
	cocos2d::Point	_ptMove;										/* �ٿ������ƶ��� */
	cocos2d::EventListenerTouchOneByOne	*m_listener;
};

