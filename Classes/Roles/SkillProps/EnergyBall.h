 /*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名： EnergyBall
** 日期：   2015:2:13
** 说明：	能量球，对敌伤害，对己补给
** 其它：	
** 历史：2015:2:13 初始版本
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
	void energyBallAction();				/* 能量球动作 */
	void setSceneID(int );

protected:
	void update(float);
	void PropCollisionDetective();			/* 碰撞检测 */

	void skillCallBack(cocos2d::Node *);
	void energyBallSearchObject();

	void getEnergyBallMovePoint(cocos2d::Rect rc, cocos2d::Point *);

private:
	bool		m_bCollision;				/* 碰撞检测状态 */
	Role		*m_Role;					/* 选中的追踪目标 */
	int			m_iSceneID;
};

