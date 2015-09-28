/*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ�����   EquipmentCell
** ��  �ڣ�   2015:5:8
** ˵  ����	����װ������Ϣ
** ��  ����	
** ��  ʷ��	2015:5:8 ��ʼ�汾
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;
using namespace std;

class EquipmentCell : public Node
{
public:
	bool init();

	void setImage(string nameString);

	void setSelect();

	CREATE_FUNC(EquipmentCell);

public:
	cocos2d::ui::Widget* equipmentPanel;									// װ�����
	ImageView* equipment;											// װ��ͼƬ
	ImageView* equipBG;												// װ������
};