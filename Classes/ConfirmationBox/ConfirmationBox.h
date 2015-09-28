/*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ�����   ConfirmationBox
** ��  �ڣ�   2015:5:19
** ˵  ����	ȷ�Ͽ�
** ��  ����	
** ��  ʷ��	2015:5:19 ��ʼ�汾
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;
using namespace cocostudio;
using namespace ui;
using namespace std;

#include "VIPPay/VIPPay.h"
#include "StateBar/StateBarNode.h"
#include "Public/FontChina.h"

enum BoxState
{
	StateNoCoin,		// ��Ҳ���
	StateNoDiamond,	// ��ʯ����
	StateBuyPropGrid,	// ������߸���
	StateBuyEquipGrid,	// ������߸���
	StateChipGrid,		// ������Ƭ����
	StateMaxCoin,		// �����Ҵ�����������
	StateMaxDiamond,	// ��������������������
};

class ConfirmationBox : public Node
{
public:
	static ConfirmationBox* getInstance(BoxState boxState);							// ����Ϊÿ���������ʾ��λ��Ĭ����Ļ����λ��

	bool init(BoxState boxState);

	void cancelButton(Ref* pSender, TouchEventType type);							// ȡ��
	void confirmButton(Ref* pSender, TouchEventType type);							// ȷ��
	void exchange();														// ����״̬����������ʾ
	void setPromptText(string promptString);										// ������ʾ����

	virtual void onEnter();
	virtual void onExit();
	bool onTouchBegan(Touch *touch, Event *unused_event);

	Text* promptText;														// ��ʾ����
	BoxState eBoxState;														// ö��
	FontChina* mpFontChina;
};