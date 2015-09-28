/*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ�����   DailyCell
** ��  �ڣ�   2015:6:11
** ˵  ����	ÿ������ÿһ��Ԫ
** ��  ����	
** ��  ʷ��	2015:6:11 ��ʼ�汾
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace cocostudio;
using namespace ui;
using namespace std;

#include "FightPoints/FightPoints.h"
#include "DataManager/DataManager.h"

class DailyCell : public Node
{
public:
	DailyCell();
	~DailyCell();

	static DailyCell* getInstance();

	bool init();
	
	void initData();										// �������ݳ�ʼ��

	void gotoClick(Ref* sender, TouchEventType type);			// ǰ��

	void collectClick(Ref* sender, TouchEventType type);			// ��ȡ

	void setCellTitle(const string titleString);					// ���õ�Ԫ�����

	void setCellPro(int iProgress, int maxProgress);				// ���ý��ȣ���ǰ���������Ҫ����

	void setCellSprite(int iGoodsName);						// ����ͼƬ

	void setCellClearn(int bInt);							// ���ô˵�Ԫ���Ƿ����

	void setCellFinish(int bInt);								// �˵�Ԫ���Ƿ�	��ʾ��ȡ״̬	

	void setCellTag(int iTag);								// ���ñ�־

private:
	Text* titleName;										// ����
	Text* goodsNum;									// ��Ʒ����
	Text* finishFlag;										// ���������
	ImageView* finishImage;								// �����
	ImageView* goodsImage;								// ��ƷͼƬ
	Button* gotoButton;									// ǰ����ť
	Button* collectButton;									// ��ȡ
	cocos2d::ui::Widget* dailyCellUI;							// cell�ؼ�
	vector< CustomsPassRecvStruct > interCustomsPassVector;   // �����ȡ�ؿ���Ϣ
};