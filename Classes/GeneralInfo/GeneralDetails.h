/*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ�����   GeneralDetails
** ��  �ڣ�   2015:4:30
** ˵  ����	
** ��  ����	�佫����
** ��  ʷ��	2015:4:30 ��ʼ�汾
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;
using namespace std;

#include "Counterpart/RoleCreate.h"
#include "DataManager/DataManager.h"
#include "EquipmentInfo.h"
#include "Public/FontChina.h"
#include "PromptBox/PromptBox.h"
#include "StateBar/StateBarNode.h"
#include "NewComer/NewComer.h"


const int EquipCount = 6;				// װ������
const int StarID = 10001;				// �佫��ʼID
const int SkillStarEnum = 4;			// ������ʼö��
const int PanelTrainZ = 2;			// �������츳����Zorder
const int RoleLayerFlag = 3900;		// ��ʾ�����
const int TalentFlag = 4;				// �츳
const int SkillFlag = 5;				// ����
const int TopPanelFlag = 3901;

enum PanelButton
{
	SKILLButton,					// ����
	DETIALButton,					// ����
	EVOButton,					// ����
	TRAINButton,					// ����
	TALENTButton,					// �츳
	MAXButton,					// ���ֵ
};

enum SkillOrder
{
	SkillSA = 10,
	SkillSB,
	SkillSC,
	SkillSD,
};

struct SESCStruct
{
	int sameName;		// ͬ���佫
	int addStar;		// ����
	int addEvo;		// ����
	int level;			// ���ǵȼ�����
	int exp;
	int soul;
	int coin;
};

class GeneralDetails : public Scene
{
public:
	GeneralDetails();
	virtual ~GeneralDetails();
	bool init();

	void closeButton(Ref* pSender, TouchEventType type);				// ����رհ�ť
	void initHeroData();											// ��ǰ�����������ݳ�ʼ��
	void initHeroAnimation(string nameString);							// ��ʼ�����ﶯ��
	void initEquipData();											// װ����ʼ�����Լ����������Ǽ����ͳ�ʼ��
	void initHeroSkill(int heroStarLevel, int heroID);						// ���＼�ܣ�ͼƬ�����ơ��˺����ȼ����������Ľ�ң�
	void showLabel();											// ��ϸ����
	void setButtonBright(PanelButton panelButton);						// ���ð�ť����
	void setBright(int btnID);										// �����Ҳ�������ť����
	void skillPhotoCallBack(Ref* pSender, TouchEventType type);			// ������ܰ�ť�ص�
	void SkillUpgradeCallBack(Ref* pSender, TouchEventType type);			// ���������ص�
	void equipCallBack(Ref* pSender, TouchEventType type);				// ���װ��ͼƬ
	void skillButton(Ref* pSender, TouchEventType type);					// ����		
	void detailButton(Ref* pSender, TouchEventType type);				// ����
	void evolutionButton(Ref* pSender, TouchEventType type);				// ����
	void trainButton(Ref* pSender, TouchEventType type);				// ����
	void skillBasicButton(Ref* pSender, TouchEventType type);				// ���ܣ��������棩
	void talentButton(Ref* pSender, TouchEventType type);				// �츳
	void talentImageButton(Ref* pSender, TouchEventType type);			// �츳ͼƬ
	void skillPanelButton(Ref* pSender, TouchEventType type);				// ������ܿ���ʾ���ܽ���
	void lightTalentButton(Ref* pSender, TouchEventType type);			// �츳ȷ�ϰ�ť
	void cancelTalentButton(Ref* pSender, TouchEventType type);			// �츳���ð�ť
	void topCloseButton(Ref* pSender, TouchEventType type);				// �رյ���ѡ���佫����
	void photoImageCall( Ref* pSender, TouchEventType type );			// ����ѡ������ͷ��ص�
	void panelTouchCallback(Ref* pSender, TouchEventType type);			// ��ʾѡ���佫����
	void evoClick(Ref* pSender, TouchEventType type);					// ������ť
	void trainTypeButton(Ref* pSender, TouchEventType type);				// ����ͨ�ð�ť
	void backButton(Ref* pSender, TouchEventType type);				// ���鷵�ذ�ť
	void trianPillButton(Ref* pSender, TouchEventType type);				// �������Ͱ�ť
	bool isTalentIDValid();										// ��ǰѡ����츳ID�Ƿ���Ч
	int calcGeneralExp(int level, int exp);								// �����佫��ǰʣ�ྭ��ֵ
	void setHeroSkillLevel();										// �������������󣬼���δ����������
	int trainShowLabel( int tag );									// ������ʾ����
	void evoInit();												// ������ʼ��
	void filxCallBack();											// ��෭ת�ص�
	void filxCallBackA();											// ��෭ת�ص�2
	void effectCallBack();											// ������Ч���

	int calcEvoSYExp(int iExp);									// ���ǻ�������ʣ�ྭ��
	SESCStruct calcNeedNum();									// �����Ӧ�� ͬ���佫�����顢���ʯ�����
	void showGeneral();											// ��ʾ�佫
	void onEnter();
	void onExit();	

	void typeButton(Ref* pSender, TouchEventType type);				// ɸѡ�佫��ť

	void showSelectHero();										// ���ر����佫ͷ��

	CREATE_FUNC(GeneralDetails);

	// �����ǵ�������Ĺ���
	void initMaidanData();											// ��ѡ�佫���ݳ�ʼ��
	void initHeroPanel();											// ��ʼ��������ѡ��Ӣ�۽���

private:
	int pillValues[ 5 ];											// �����ṩ������� 
	ImageView* photoImage[ 5 ];									// ����ѡ������ͷ��
	int selectedTalentID;											// ѡ���츳��ID
	FontChina* mpFontChina;										// ��ʾ����
	Role* heroRole;												// ����
	Layout* panelRight;											// �Ҳ����
	Layout* panelDetial;											// �������
	Layout* panelLeft;											// ������
	Layout* panelTrain;											// ��ʾ����
	Layout* panelEvo;											// ������
	int clickPosFlag;												// ���λ�õı�־
	int expCount;												// �����佫���ṩ����
	cocos2d::Point m_ptOriginleLoc;									// ��ʱ����
	cocos2d::Point m_ptTouchLoc;
	cocos2d::ui::ScrollView* topScrollView;								// ѡ�������	
	Layout* skillLayout;											// ���ܲ�
	Layout* talentLayout;											// �츳��
	vector<GeneralProptyStruct > maidanVector;						// ��������ȡ�����佫����
	vector<GeneralProptyStruct > curGeneralVector;						// ��ǰ��������ĵ�ǰ�佫����
	vector<GeneralProptyStruct > localGeneralVector;					// �佫��ԭʼ����ֵ
	vector<EquipProptyStruct > localEquipVector;						// װ����������
	vector<EquipRefineStruct > localEquipRefineRuleVector;				// װ���������ع���
	vector<GeneralDetailRecvStruct > interGeneralVector;					// ��������ȡ�����佫����
	vector<SkillNameStruct > localSkillNameVector;						// ���ܻ�������
	vector<SkillUpgradeStruct > localSkillUpgradeVector;					// ������������
	vector<GeneralUpgradeStruct > localGeneralUpgradeVector;			// �佫������������
	vector<TalentLocalStruct > lcoalTalentVector;						// �����츳
	vector<TalentLocalStruct > meetTalentVector;						// �ʺ��츳
	vector<SkillNameStruct > localTempSkillNameVector;					// ����Ҫ��ļ���
	vector<SkillAddPropty > localSkillAddPropty;						// ���ؼ���������������
	vector<int > interTalentVector;									// �佫�츳
	vector<PlayerInfoRecvStruct > interPlayerInfoVector;					// �������
	vector<GeneralEvoLocalStruct > localGeneralEvoVector;				// �����佫��������
	vector<GeneralProptyStruct > selectedHero;						// ѡ�б��Ե����佫
	vector<MaidanStruct > interMaidanVector;							// ��������ȡ��������������
	vector<GeneralProptyStruct > tempGeneralVector;					// ���ݰ�ťѡ����ʾ�佫��Ϣ
	vector<GeneralProptyStruct > curTempGeneralVector;					// ��ǰ��������ĵ�ǰ�佫����
	vector<GeneralEvoExpLocalStruct > localGeneralEvoExpVector;			// �����佫�����ṩ����

	NewComer	*_comer;
};
