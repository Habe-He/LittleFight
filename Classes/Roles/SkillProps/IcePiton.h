 /*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ����� IcePiton
** ���ڣ�   2015:2:13
** ˵����	��׶����ȵ����ů����3
** ������	
** ��ʷ��2015:2:13 ��ʼ�汾
*********************************************************************/
#pragma once
#include "Roles/FlightProp/SatelliteProp.h"

class IcePiton : public SatelliteProp
{
public:
	IcePiton(void);
	virtual ~IcePiton(void);

	static IcePiton* create(Role *, const std::string&, FlightPropInfo);
	
	bool PropCollisionDetective();
};

