/*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ����� LianPo
** ���ڣ�   2015:1:30
** ˵����	����
** ������	
** ��ʷ��2015:1:30 ��ʼ�汾
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "Roles/Role/Role.h"
#include "Roles/SkillProps/CommonProp.h"

enum ZhaoKuoFlight
{
	ZhaoKuo_Normal = 0,
	ZhaoKuo_S1Prop,
	ZhaoKuo_S2Prop,
	ZhaoKuo_Max
};

class ZhaoKuo : public Role
{
public:
	ZhaoKuo(void);
	virtual ~ZhaoKuo(void);

	CREATE_ROLE_FUNC(ZhaoKuo);

protected:
	void loadArmature();											/* ���ض�����Դ */
	void initFlightPropInfo();										/* ��ʼ�����ܷ��е��� */
	void aiActSequenceBoss();										/* Boss Ai�������� */

	void actionMovementCallFunc(cocostudio::Armature *, cocostudio::MovementEventType, const std::string&);
	void actionFrameEventCallFunc(cocostudio::Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);

	/* ����ִ�� Begin */
	bool runActionAttack();
	bool runActionTwiceAtk();
	bool runActionThriceAtk();
	bool runActionSkillOne();
	bool runActionSkillTwo();
	bool runActionSkillThree();
	/* ����ִ�� End */

	void ZhaoKuoArrow(ZhaoKuoFlight, bool, Point);
	void ZhaoKuoS1();
	void s1CallBack1(cocos2d::Node *);
	void s1CallBack2(cocos2d::Node *);

private:
	std::map<cocos2d::Sprite*, cocos2d::Point> m_mapS1;			/* ����s1������*/
	RoleFlightProp m_stZhaoKuoProp[ZhaoKuo_Max];
};

