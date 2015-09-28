/*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ�����   Maidan
** ��  �ڣ�   2015:4:29
** ˵  ����	
** ��  ����	
** ��  ʷ��	2015:4:29 ��ʼ�汾
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;
using namespace std;

#include "DataManager/DataManager.h"
#include "DataManager/DataRecvEntities.h"
#include "TrainCell.h"
#include "Scene/MainScene.h"
#include "GeneralInfo/GeneralDetails.h"
#include "PromptBox/PromptBox.h"
#include "Public/FontChina.h"
#include "NewComer/NewComer.h"

enum TypeButton
{
	TypeALL,					// ����
	TypeLI,					// ��
	TypeZhi,					// ��
	TypeMin,					// ��
	TypeStr,					// ǿ��
	TypePreset,				// Ԥ��
};

enum CurState
{
	NoneState,					// ��ʾ���״̬
	EnhanceState,				// ǿ��״̬
	PresetState,				// ѡ������״̬
};

class Maidan : public Layer
{
public:
	Maidan();
	virtual ~Maidan();

	bool init();
	static Scene* scene();

	void closeButton(Ref* pSender, TouchEventType type);				// ����رհ�ť

	void typeButton(Ref* pSender, TouchEventType type);				// �����Ҳ��佫���԰�ť

	void enhanceButton(Ref* pSender, TouchEventType type);				// ǿ��

	void preSetButton(Ref* pSender, TouchEventType type);				// �����佫Ԥ��

	void initGeneralData();										// ��ʼ���佫����

	void showGeneral();											// ��������ʾ�佫��Ϣ

	void panelTouchCallback(Ref* pSender, TouchEventType type);			// �佫�б�����Ӧ

	void initEnhanceProp();										// ��ʼ��ǿ��״̬  ҩˮ

	void initPresetPanel();										// �㽫�����ʼ��

	void setButtonBirght(TypeButton buttonBright);						// ���õ����ť�ĸ���

	void heroPhotoCallBack(Ref* pSender, TouchEventType type);			// ����ͷ��ť�ص�

	void heroCloseCallBack(Ref* pSender, TouchEventType type);			// ����ͷ��ɾ���ص�

	void propIamgeCallBack(Ref* pSender, TouchEventType type);			// ���߻ص�

	int calcGeneralLevel(int exp);									// �����佫�ȼ�	

	int calcPreFighting(vector<PointSetsRecvStruct > pointVec);				// ���������佫��վ����

	void onEnter();
	void onExit();	

	CREATE_FUNC(Maidan);

private:
	int i_ButtonFlag;												// �����ť������
	cocos2d::ui::ScrollView* mainScrollView;							// ������Ψһ�Ĺ�����
	Layout* movePanel;											// �ƶ������
	Layout* rightButtonPanel;										// �ұߵİ�ť
	Layout* presetPanel;											// Ԥ��
	Layout* enhancePanel;										// ǿ��
	TextAtlas* fightingLabel;										// ս����
	FontChina* mpFontChina;										// ������ʾ
	vector<MaidanStruct > interMaidanVector;							// ��������ȡ��������������
	vector<GeneralProptyStruct > selectedHeroVector;					// ѡ��������佫
	vector<GeneralProptyStruct > curGeneralVector;						// ��ǰӵ���佫����
	vector<GeneralProptyStruct > tempGeneralVector;					// ���ݰ�ťѡ����ʾ�佫��Ϣ
	vector<GeneralProptyStruct > localGeneralVector;					// �����佫��������
	vector<PropProptyStruct > localPropVectro;							// ���ص�������
	vector<PointSetsRecvStruct > interPointSetsVector;					// �㽫̨��������
	vector<GeneralUpgradeStruct > localGeneralUpgradeVector;			// �佫������������
	vector<TeamInfoStruct > interTeamInfoVector;						// ��ȡս����Ϣ
	vector<EquipProptyStruct > localEquipVector;						// װ����������
	vector<EquipRefineStruct > localEquipRefineRuleVector;				// װ���������ع���

	// ��ʱ����
	cocos2d::Point m_ptOriginleLoc;
	cocos2d::Point m_ptTouchLoc;
	Button* button_Str;											// ǿ����ť
	Button* button_PreSet;										// Ԥ�谴ť

	int posIndex;												// �佫λ����Ϣ
	int propID;													// ǿ��ʹ�õ���ƷID
	int goodsNum;												// ǿ��ʱ��Ʒ����
	CurState panelState;											// ���浱ǰ״̬
	ImageView* roleImage[ 4 ];									// �㽫̨����ͷ���ĸ�λ��
	ImageView* roleImageSelect[ 4 ];								// �㽫̨����ͷ��ѡ��״̬
	ImageView* roleButtonSelect[ 4 ];								// �㽫̨����ͷ��ɾ��
	ImageView* propImage[ 3 ];									// ǿ��ʱ������Ʒ��λ��
	Text* propNum[ 3 ];											// ǿ��ʱ������Ʒ������

	NewComer	*_comer;
};