 /*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ����� PointCell
** ���ڣ�   2015:5:7
** ˵����	�ؿ���ť
** ������	
** ��ʷ��2015:5:7 ��ʼ�汾
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "FightPoints_Def.h"

class PointCell : public cocos2d::Node
{
public:
	PointCell(void);
	virtual ~PointCell(void);

	static PointCell* create(CellInfo, BattleSign);
	virtual bool init(CellInfo, BattleSign);

public:
	/* ����button�ص��¼� */
	void addBtnTouchEvent(cocos2d::Ref* , cocos2d::ui::SEL_TouchEvent);
	void btnPoints(cocos2d::Ref*, cocos2d::ui::TouchEventType);		/* �ؿ��Ļص� */
	void loadFlagAnimate();											/* ����Ʈ�ﶯ�� */
	void loadAureoleAnimate();										/* Boss�ؿ��⻷���� */
	CellInfo getCellInfo();

private:
	CellInfo			_cell;

	int					_battle;									/* ս��ID */

	cocos2d::Sprite		*_spAureole;								/* Boss�ؿ��⻷���� */
	cocos2d::Sprite		*_spCom;									/* ��ť����ͼ */
	cocos2d::Sprite		*_spFlag;									/* boss�ؿ����� */
	cocos2d::ui::Button *_btnCell;
};

