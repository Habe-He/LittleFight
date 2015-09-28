 /*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ����� SatelliteProp
** ���ڣ�   2015:2:13
** ˵����	���ƽ�ɫ���е��߻���
** ������	
** ��ʷ��2015:2:13 ��ʼ�汾
*********************************************************************/
#pragma once
#include "Roles/FlightProp/FlightProp.h"

/* skillInfo��yAtkDisΪ���߸߶ȣ�FlightPropInfo��heightΪ�Ƕ� */
class SatelliteProp : public FlightProp
{
public:
	SatelliteProp(void);
	virtual ~SatelliteProp(void);

	static SatelliteProp* create(Role *, const std::string&, FlightPropInfo);

	void runPropCollisionDetective();
	bool PropCollisionDetective();

protected:
	void update(float);
};

