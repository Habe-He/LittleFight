/*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ�����   TeamInfo
** ��  �ڣ�   2015:1:23
** ˵  ����	���ͷ�񣬶�����Ϣ����
** ��  ����	
** ��  ʷ��	2015:1:23 ��ʼ�汾
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
	TNor,				// ������ʾ״̬
	TSetup,			// ��ʾ����
};

class TeamInfo : public Layer
{
public:
	static Scene* scene();

	bool init();

	void closeButton(Ref* pSender, TouchEventType type);

	void closeCall();											// �رհ�ť�ص�

	int calcExp(int curExp);									// ���ص�ǰʣ�ྭ��

	void musicCall(Ref* pSender);								// ���ֿ���

	void effectCall(Ref* pSender);								// ��Ч����

	void onEnter();
	void onExit();
	bool onTouchBegan(Touch *touch, Event *unused_event);

	CREATE_FUNC(TeamInfo);
private:
	ImageView* spriteView;									// ���汳��ͼ
	cocos2d::ui::Widget* teamInfoUI;	
	vector<PlayerInfoRecvStruct > interPlayerInfoVector;				// �����Ϣ��������
	vector<TeamUpgradeLocalStrcut > ruleVector;					// ս����������
};
#endif