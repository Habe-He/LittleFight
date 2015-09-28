/*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ�����   StoreB
** ��  �ڣ�   2015:7:9
** ˵  ����	
** ��  ����	������Ʒ����
** ��  ʷ��	2015:7:9 ��ʼ�汾
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
	int goodsID;			// ��Ʒ����
	int goodsNum;			// ��Ʒ��Ŀ
	int goodsPrice;			// ��Ʒ�۸�
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

	void closeButton(Ref* pSender, TouchEventType type);						// �ر�

	void comfirmButton(Ref* pSender, TouchEventType type);						// ȷ��

	void cancleButton(Ref* pSender, TouchEventType type);						// ȡ��

	void dButton(Ref* pSender, TouchEventType type);							// ����

	void initData();														// ��Ʒ��ʼ��

	vector<SellGoods > sellGoodsVector;										// ������Ʒ����

	CREATE_FUNC(StoreB);

	virtual void onEnter();
	virtual void onExit();
	bool onTouchBegan(Touch *touch, Event *unused_event);

private:
	EventListenerTouchOneByOne* listener;									// ����
	StPanel stPanel;													// ����״̬
	FontChina* mpFontChina;												// ��������
	vector<PlayerInfoRecvStruct > interPlayerVector;								// �����Ϣ

	NewComer	*_comer;
};
