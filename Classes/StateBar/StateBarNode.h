/*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ�����   StateBarNode
** ��  �ڣ�   2015:5:18
** ˵  ����	״̬��
** ��  ����	
** ��  ʷ��	2015:5:18 ��ʼ�汾
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
	StatePower,			// ��ҡ���ʯ������
	StateGS,				// ��ʾ��ѫ
};

class StateBarNode : public Node
{
public:
	static StateBarNode* getInstance(StateChange stateChange);

	bool init(StateChange stateChange);

	void addCoinClick(Ref* pSender, TouchEventType type);							// ������
		
	void addDiamondClick(Ref* pSender, TouchEventType type);						// ��ʯ��ֵ

	void exchangeClick(Ref* pSender, TouchEventType type);							// �һ���ť

	void refreshVaule();														// ��ֵˢ��

	void showTipsCallBack();													// ɾ����ʾ

	virtual void onEnter();
	virtual void onExit();
	bool onTouchBegan(Touch *touch, Event *unused_event);

private:
	int i_Flag;																// �Ƿ񵯳�
	FontChina* mpFontChina;													// ����
	EventListenerTouchOneByOne* listener;										// �����¼�
	cocos2d::ui::Widget* stateBarLayout;											// ״̬��
	vector<BuyCPLocalStruct > localCPVector;										// �����Һ�����
	vector<PlayerInfoRecvStruct > interPlayerInfoVector;								// �����Ϣ��������
};