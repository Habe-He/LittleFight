 /*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ����� FallenProp
** ���ڣ�   2015:4:16
** ˵����	����ķ��е��ߣ����ļ���1��
** ������	
** ��ʷ��2015:4:16 ��ʼ�汾
*********************************************************************/
#pragma once
#include "Roles/FlightProp/FlightProp.h"

class FallenProp : public FlightProp
{
public:
	FallenProp(void);
	virtual ~FallenProp(void);
	
	static FallenProp* create(Role *, const std::string&, FlightPropInfo);
	void runPropCollisionDetective(float, cocos2d::Point);			/* �����ƶ���������ײ��� */
	void setPropYaxis(float);

protected:
	void skillCallBack();
	void update(float);
	void PropCollisionDetective(float);								/* ��ײ��� */

private:
	float	_fPropYasix;
};

