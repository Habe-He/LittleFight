 /*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ����� FontGuard
** ���ڣ�   2015:2:28
** ˵����	��������3�����ػ�
** ������	
** ��ʷ��2015:2:28 ��ʼ�汾
*********************************************************************/
#pragma once
#include "Roles/FlightProp/SatelliteProp.h"

class FontGuard : public SatelliteProp
{
public:
	FontGuard(void);
	virtual ~FontGuard(void);
	
	static FontGuard* create(Role *, const std::string&, FlightPropInfo);
	void fontOver();

protected:
	void fontOverCallBack(cocos2d::Node *);	/* ����������ϻص� */
};

