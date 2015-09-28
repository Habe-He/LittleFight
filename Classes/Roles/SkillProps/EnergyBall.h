 /*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ����� EnergyBall
** ���ڣ�   2015:2:13
** ˵����	�����򣬶Ե��˺����Լ�����
** ������	
** ��ʷ��2015:2:13 ��ʼ�汾
*********************************************************************/
#pragma once
#include "CommonProp.h"

class EnergyBall : public CommonProp
{
public:
	EnergyBall(void);
	virtual ~EnergyBall(void);

	static EnergyBall* create(Role *, const std::string&, FlightPropInfo);

public:
	void energyBallAction();				/* �������� */
	void setSceneID(int );

protected:
	void update(float);
	void PropCollisionDetective();			/* ��ײ��� */

	void skillCallBack(cocos2d::Node *);
	void energyBallSearchObject();

	void getEnergyBallMovePoint(cocos2d::Rect rc, cocos2d::Point *);

private:
	bool		m_bCollision;				/* ��ײ���״̬ */
	Role		*m_Role;					/* ѡ�е�׷��Ŀ�� */
	int			m_iSceneID;
};

