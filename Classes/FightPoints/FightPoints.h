 /*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ����� FightPoints
** ���ڣ�   2015:5:7
** ˵����	�ؿ�ѡ�����
** ������	
** ��ʷ��2015:5:7 ��ʼ�汾
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "PointCell.h"
#include "DataManager/DataRecvEntities.h"

class FightPoints : public cocos2d::Layer
{
public:
	FightPoints(void);
	virtual ~FightPoints(void);

	static cocos2d::Scene* scene();
	virtual bool init();
	CREATE_FUNC(FightPoints);

public:
	void removeGoods();												/* ȡ���ؿ���Ʒ��ʾ */

protected:
	void loadUI();													/* ����UI */
	void loadPointsInfo(PointMode);								/* ���ùؿ� */
	void PointButtonClick(cocos2d::Ref*, cocos2d::ui::TouchEventType);/* �رհ�ť */
	void BattleButtonClick(cocos2d::Ref*, cocos2d::ui::TouchEventType);/* ս����ť */
	void CellButtonClick(cocos2d::Ref*, cocos2d::ui::TouchEventType);/* �ؿ��Ļص� */
	std::vector<CustomsPassRecvStruct > getPointPassInfo(PointMode);/* ��ȡ�ؿ�ͨ����Ϣ */
	void changeBattleSign(BattleSign);
	void showGoods(int );
	void removeGuide();

private:
	BattleSign		_battle;										/* ս��ID */
	PointMode		_mode;											/* �ؿ�ģʽ */

	cocos2d::ui::Widget			*_UIWidget;

	cocos2d::ui::ScrollView		*_scrollViewBattle;					/* ս�������� */
	cocos2d::ui::Button			*_btnCom;							/* ��ͨ�ؿ� */
	cocos2d::ui::Button			*_btnElite;							/* ��Ӣ�ؿ� */
	cocos2d::ui::Button			*_btnBattle[Battle_Max];			/* ս�� */
	cocos2d::ui::ImageView		*_imgGoods[8];						/* �ؿ�������Ʒ */
};

