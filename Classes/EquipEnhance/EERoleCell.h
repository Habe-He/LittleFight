 /*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ����� EERoleCell
** ���ڣ�   2015:6:17
** ˵����	��ɫ��Ԫ
** ������	
** ��ʷ��2015:6:17 ��ʼ�汾
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "DataManager/DataRecvEntities.h"

class EERoleCell : public cocos2d::Node
{
public:
	EERoleCell(void);
	virtual ~EERoleCell(void);

	static EERoleCell*	Create(GeneralProptyStruct);
	virtual bool init(GeneralProptyStruct);

public:
	GeneralProptyStruct getRoleCellInfo();

private:
	GeneralProptyStruct		_stInfo;
};

