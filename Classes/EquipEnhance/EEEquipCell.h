/*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ����� EEEquipCell
** ���ڣ�   2015:6:17
** ˵����	װ����Ԫ
** ������	
** ��ʷ��2015:6:17 ��ʼ�汾
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "DataManager/DataRecvEntities.h"

class EEEquipCell : public cocos2d::Node
{
public:
	EEEquipCell(void);
	virtual ~EEEquipCell(void);

	static EEEquipCell*	Create(EquipProptyStruct);
	virtual bool init(EquipProptyStruct);

public:
	bool changeStatus();											/* ת��ѡ�����ѡ��״̬ */
	EquipProptyStruct getEquipCellInfo();

	CC_SYNTHESIZE(int, _realExp, RealExp);							/* �������õľ���ֵ����������ʱ�������ʲ��ܴﵽ��� */

private:
	bool	_bSelectFlag;											/* ѡ�б�� */

	cocos2d::Sprite		*_spLight;									/* ������Դ */

	EquipProptyStruct	_stInfo;
};

