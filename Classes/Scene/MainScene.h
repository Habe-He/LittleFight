/*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ����� MainScene
** ���ڣ�   2014:9:19
** ˵����	  ��½��������
** ������	  �������������ʱֻ�ܵ���հ���������ʽ��ʱʹ��CS���� ScrollView�༭
** ��ʷ��	2014:9:19 ��ʼ�汾
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

	void store(Ref* pSender, TouchEventType type);								// �ƹ�

	void smithy(Ref* pSender, TouchEventType type);

	void YiJiDangQian(Ref* pSender, TouchEventType type);

	void JiXiaXueGong(Ref* pSender, TouchEventType type);

	void heroButton(Ref* pSender, TouchEventType type);							// ����ͷ��

	void rewardClick(Ref* pSender, TouchEventType type);							// �ɾ�

	void otherClick(Ref* pSender, TouchEventType type);								// ������Ϸ

	void storebClick(Ref* pSender, TouchEventType type);							// ������Ʒ�̵�

	void challengeClick(Ref* pSender, TouchEventType type);							// ��ս��������

	void createTeach();														// ���������̳�
	void teachCB();

	void update(float dt);

	bool init();

	void initData();

	void playInfoShow();													// ��ʾ�����Ϣ

	virtual void onEnter();
	virtual void onExit();	
	
	CREATE_FUNC(MainScene);

private:
	cocos2d::ui::ScrollView* mianScrollView;									// ������
	vector<TeamInfoStruct > interTeamInfoVector;								// ս�ӵȼ���Ϣ��������
	vector<PlayerInfoRecvStruct > interPlayerInfoVector;							// �����Ϣ
	Layout* buttomPanel;													// �ײ���ť��
};
#endif