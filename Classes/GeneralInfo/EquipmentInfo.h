/*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ�����   EquipmentInfo
** ��  �ڣ�   2015:5:8
** ˵  ����	װ����Ϣ
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

#include "EquipmentCell.h"
#include "DataManager/DataManager.h"
#include "DataManager/DataRecvEntities.h"
#include "Public/FontChina.h"
#include "NewComer/NewComer.h"

enum EquipPosType
{
	PosTypeNone,				// ��
	PosTypeArmour,				// ����
	PosTypeHead,				// ͷ��
	PosTypeDecorations,			// ��Ʒ
	PosTypeWeapons,			// ����
	PosTypeQi,				// ����
	PosTypeYi					// �챦
};

class EquipmentInfo : public Scene
{
public:
	EquipmentInfo();
	virtual ~EquipmentInfo();

	bool init();

	void initEquipmentData();											// ����Ҫ����Ϣ��ʼ��

	void showEquipment();											// ��ʾ�������������Ϣ

	void singleEquipmentInfo(int pkID, int typeClick);						// ��ʾ����װ������Ϣ........1 = Ĭ����ʾ   0 = �����ʾ

	void closeClick(Ref* pSender, TouchEventType type);						// �رհ�ť

	void imageClick(Ref* pSender, TouchEventType type);					// װ��ͼƬ����ص�

	void equipClick(Ref* pSender, TouchEventType type);						// װ����ť
	void unloadClick(Ref* pSender, TouchEventType type);					// ж�°�ť
	void changeClick(Ref* pSender, TouchEventType type);					// ������ť

	CREATE_FUNC(EquipmentInfo);
private:
	bool isFull;													// ���λ���Ƿ���װ��
	// ��ʱ����
	cocos2d::Point m_ptOriginleLoc;
	cocos2d::Point m_ptTouchLoc;
	int equipmentPKID;												// ��װ��������
	FontChina* mpFontChina;											// ����������ʾ
	Layout* equipmentLayer;											// �Ҳ�װ����
	Layout* singleInfo;												// ��൥��װ����Ϣ
	cocos2d::ui::ScrollView* equipmentScrollView;							// �Ҳ�װ��������
	vector<WareroomCommonRecvStruct > interEquipVector;					// �ֿ���װ����������
	vector<EquipProptyStruct > localEquipVector;							// װ����������
	vector<EquipProptyStruct > tempEquipVector;							// װ����������
	vector<GeneralDetailRecvStruct > interGeneralEquipVector;					// �佫װ����������ȡ������Ϣ

	NewComer	*_comer;
};