/*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ����� Wareroom
** ���ڣ�   2014:9:19
** ˵����	  �ֿ�
** ������	  
** ��ʷ��	2014:9:19 ��ʼ�汾
*********************************************************************/
#ifndef __WAREROOM_SCENE__
#define __WAREROOM_SCENE__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace cocostudio;
using namespace ui;

#include "Public/FontChina.h"
#include "Public/ToolFunc.h"
#include "Store/DrawoffDisplay.h"
#include "UserInfo/Define_Info.h"
#include "SimpleAudioEngine.h"
#include "Scene/MainScene.h"
#include "Public/EffectAction.h"
#include "NewComer/NewComer.h"

const int toolTipsTag = 1;
const int StatusBarTag = 2;
const int btnPropTag = 20;
const int btnEquipTag = 21;
const int btnChipTag = 22;

const int RightPanelTag = 32;
const int GridCount = 80;
const float FontSize = 16.0f;
const int Label_1 = 60;
const int Label_2 = 61;
const int LabelTipTag = 100;

enum btnEnum
{
	noneBtn,
	propBtn,
	equipBtn,
	chipBtn,
};

enum propTypeBtn
{
	noneTypeBtn,  // ��
	powerBtn,		// ����������
	expBtn,		// ����ҩˮ
	baoxiangBtn,	// ����
	juanzhouBtn,	// ����
	zaxiang,		// ����
};

enum equipType
{
	TypeNone,				// ��
	TypeArmour,			// ����
	TypeHead,				// ͷ��
	TypeDecorations,		// ��Ʒ
	TypeWeapons,			// ����
	TypeQi,				// ����
	TypeYi				// �챦
};

enum EquipColor
{
	NoneColor,
	WhiteColor,
	GreenColor,
	BlueColor,
	PurPleColor,
};

enum WareroomState
{
	StateNone,
	StateTips,
};

class Wareroom : public Layer
{
public:
	Wareroom();
	virtual ~Wareroom();

	bool init();

	static Scene* scene();
	
	void createProps(Ref* pSender, TouchEventType type);					// ���ɵ���	
	void createEquip(Ref* pSender, TouchEventType type);					// ����װ��	
	void createChip(Ref* pSender, TouchEventType type);					// ������Ƭ	
	void expandBag(Ref* pSender, TouchEventType type);					// ��չ����	
	void loadFrame(int id);											// ��ʾװ���ĸ����Լ�������Ʒ	
	void closeButton(Ref* pSender, TouchEventType type);					// �ر�	
	void shift(Ref* pSender, TouchEventType type);							// ת��	
	void sell(Ref* pSender, TouchEventType type);							// ���� ----	����ҩˮ�����װ��	
	void synthetic(Ref* pSender, TouchEventType type);						// �ϳ� -------  ��Ƭ	
	void useClick(Ref* pSender, TouchEventType type);						// ʹ��  ------- ���ᡢ����������
	
	void showInfo(int id, int btnID);										// ��ʾ��Ʒ��Ϣ ----- ��Ʒ��Index��������ť��ID	
	void setBrightButton(btnEnum btnIndex);								// ������ť������Z��
	bool onTouchBegan(Touch *touch, Event *unused_event);					
	virtual void onEnter();
	virtual void onExit();

	// ʹ�ñ���
	DrawoffGoodsStruct muBox(int id, int boxType);

	void createConfirmLayout(int btnIndex);

	void confirmButton(Ref* pSender, TouchEventType type);
	void cancelButton(Ref* pSender, TouchEventType type);

	CREATE_FUNC(Wareroom);

private:
	int diamond;													// �����������ĵ���ʯ
	int sellIndex;													// �����Ʒ��index
	int buttonIndex;													// ������ĸ���ť������װ����Ƭ��	
	int vectorSubscript;												// �ֿ���ʾ��Ʒ�������±�
	int goodsID;													// ���ʹ�ð�ť��¼ʹ����Ʒ��ID
	WareroomState wareroomState;										// �ֿ�״̬���Ƿ񵯳���ʾ��
	FontChina* mpFontChina;
	Layout* sellValuePanel;											// �����۸��
	cocos2d::ui::ScrollView* scrollView;									// ��Ʒ������
	vector<WareroomCommonRecvStruct > interWareroomData;					// �������󵽲ֿ���Ʒ��Ϣ	
	vector<WareroomCommonRecvStruct > tempWareroomVector;				// ���ڴ������û����Ʒ��״̬				
	vector<PropProptyStruct> localWareroomPropData;						// ���߻�������
	vector<EquipProptyStruct > localWarerommEquipData;						// װ����������
	vector<GeneralProptyStruct > localWarerommGeneralData;					// ��Ƭ ----- �佫
	vector<GeneralChipRecvStruct > localGeneralChipVector;					// �佫��Ƭ�ϳɹ���
	vector<EquipChipRecvStruct > localEquipChipVector;						// װ����Ƭ�ϳɹ���	
	vector<BoxRecvStruct > localBoxVector;								// �������ݽ�����Json
	vector<PlayerInfoRecvStruct > interPlayerInfo;							// �����Ϣ
	void showTips(string str);
	void showTipsCallBack();

	NewComer		*_comer;
};
#endif