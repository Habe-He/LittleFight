 /*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ����� Skull
** ���ڣ�   2015:2:13
** ˵����	��������3����
** ������	
** ��ʷ��2015:2:13 ��ʼ�汾
*********************************************************************/
#pragma once
#include "Roles/SkillProps/CommonProp.h"

class Skull : public CommonProp
{
public:
	Skull(void);
	virtual ~Skull(void);

	static Skull* create(Role *, const std::string&, FlightPropInfo);

protected:
	void PropCollisionDetective(float);
};

