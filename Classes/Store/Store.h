/*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ����� Store
** ���ڣ�   2014:9:19
** ˵����	  ���˽���
** ������	  
** ��ʷ��	2014:9:19 ��ʼ�汾
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;
using namespace cocostudio;
using namespace ui;

#include "DrawoffDisplay.h"
#include "StoreProp.h"
#include "UserInfo/Define_Info.h"
#include "SimpleAudioEngine.h"
#include "Scene/MainScene.h"
#include "DataManager/DataSendEntities.h"
#include "ConfirmationBox/ConfirmationBox.h"
#include "DataManager/DataRecvEntities.h"
#include "Public/FontChina.h"
#include "DataManager/DataManager.h"
#include "NewComer/NewComer.h"


const int Store_StatusBarTag = 2;
const int ButtonDrawoff = 10;// �鿨��ťtagֵ
const int ButtonMyStore = 11;// �����̵갴ťtagֵ
const int StateBarFlag = 12;// UI�����Ϸ������ʯ������ť�ĸ���ڵ��tagֵ
const int refreshDiamondNum= 5;// �����̵�ˢ��һ��������ʯ����

class Store : public cocos2d::Scene
{
public:
	Store();
	virtual ~Store();

	virtual void onEnter();
	virtual void onExit();

	bool init();

	void initData();

	CREATE_FUNC(Store);

	void coinDrawoffTenButton(Ref* pSender, TouchEventType type);						//��ҳ鿨��ť�����¼�

	void diamondDrawoffButton(Ref* pSender, TouchEventType type);						//��ʯ�鿨��ť�����¼�

	void diamondDrawoffTenButton(Ref* pSender, TouchEventType type);						//10����ʯ�鿨��ť�����¼�
	
	void closeBtn(cocos2d::Ref* , cocos2d::ui::TouchEventType);							// �رհ�ť 

	void createTeachNode();														// ����ָ��

	void refreshButtonEnvent(Ref* pSender, TouchEventType type);							// ˢ�°�ť�����¼�
	void refreshTimeDisplay();														// ˢ��ʱ����ʾ
	void displayGoodsInfo();														// ��ʾ��Ʒ��Ϣ
	void goodsEnventImage(Ref* pSender, TouchEventType type);							// ��Ʒ��������¼�������


private:
	Button* btnClose;															// ����رհ�ť
	Button* coinTenButton;														// ��Ұ�ť
	Button* diamondButton;														// ��ʯ��ť
	Button* diamondTenButton;
	Text* coinLabel;                                                            // ���������ʾ
	Text* diamondLabel;															// ��ʯ������ʾ
	Layout* drawoffPanel;															// �鿨Panel
	Text* refreshTimeLabel;														// ˢ��ʱ����ʾ
	Button* refreshButton;														// ˢ�°�ť
	Text* consumeDiamondLabel;													// ˢ��������ʯ��ʾ
	ImageView* goodsImage[8];													// ��ƷͼƬ
	Text* numLabel[8];															// ��Ʒ����
	Text* coinDiamondNumLabel[8];													// ������Ʒ��Ҫ�Ľ��������ʯ��
	Text* goodsNameLabel[8];														// ��Ʒ����
	ImageView* coinImage[8];														// ���ͼƬ
	ImageView* diamondImage[8];													// ��ʯͼƬ
	ImageView* lightedImage[8];													// ����ͼƬ,��ʾ����״̬
	 FontChina* mpFontChina;														// �鿨��ȡ������Ϣ
	FontChina* pFontChina;														// ��������
	DrawoffGoodsStruct _coinDrawoffGoodsVector(int id);
	DrawoffGoodsStruct _diamondDrawoffGoodStruct(int id);
	vector<DrawoffRecvStruct> localDrawoffVector;
	vector<PlayerInfoRecvStruct > interPlayerInfoVector;									// �����Ϣ��������
	vector<ServiceDayTimeRecvStruct > interServiceDayVector;								// ��������ǰʱ��
	vector<StoreLocalDataStruct >  localGoodsVector;
	vector<DrawoffIDRecvStruct > localDrawoffIDVector;									// ��ȡ��Ʒ�ı�
	vector<GeneralProptyStruct > generalProptyVector;									// �佫��������		
	vector<StoreListRecvStruct > storeListVector;										// ��Ʒ�б���Ϣ
	vector<storeBuyGoodsStruct > buyInfoVector;										// ������Ʒ��Ϣ
	vector<WareroomGridRecvStruct > interWareroomGridVector;							// �ֿ�ʣ�����

	NewComer	*_comer;
};