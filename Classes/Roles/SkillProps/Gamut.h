 /*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ����� Gamut
** ���ڣ�   2015:5:11
** ˵����	ȫ��Χ����
** ������	
** ��ʷ��2015:5:11 ��ʼ�汾
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "CommonProp.h"

class Gamut : public CommonProp
{
public:
	Gamut(void);
	virtual ~Gamut(void);
	
	static Gamut* create(Role *, const std::string&, FlightPropInfo);
	void runPropCollisionDetective();								/* �����ƶ���������ײ��� */
	void loadActionRes();
	void gamutSchedule(float);
	void PropCollisionDetective(float);

private:
	int		_resIndex;												/* ��ǰ������Դ���� */
	std::vector<std::string>	_vecRes;
};

