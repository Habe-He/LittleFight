 /*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ����� CommonProp
** ���ڣ�   2015:2:3
** ˵����	���е��߹�����
** ������	
** ��ʷ��2015:2:3 ��ʼ�汾
*********************************************************************/
#pragma once
#include "Roles/FlightProp/FlightProp.h"

class CommonProp : public FlightProp
{
public:
	CommonProp(void);
	virtual ~CommonProp(void);

	static CommonProp* create(Role *, const std::string&, FlightPropInfo);
	void runPropCollisionDetective(float, cocos2d::Point);			/* �����ƶ���������ײ��� */

protected:
	void skillCallBack();
	void update(float);
};

