/*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ�����   PangJuan
** ��  �ڣ�   2015:2:3
** ˵  ����	
** ��  ����	
** ��  ʷ��	2015:2:3 ��ʼ�汾
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "Roles/Role/Role.h"
#include "Roles/SkillProps/CommonProp.h"

enum PangJuanProp
{
	PangJuan_S1Prop = 0,
	PangJuan_S4Prop,
	PangJuan_Max
};

class PangJuan : public Role
{
public:
	PangJuan(void);
	virtual ~PangJuan(void);

	CREATE_ROLE_FUNC(PangJuan);

protected:
	void loadArmature();											/* ���ض�����Դ */
	void initFlightPropInfo();										/* ��ʼ�����ܷ��е��� */

	void actionMovementCallFunc(cocostudio::Armature *, cocostudio::MovementEventType, const std::string&);
	void actionFrameEventCallFunc(cocostudio::Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);

	/* ����ִ�� Begin */
	bool runActionAttack();
	bool runActionTwiceAtk();
	bool runActionThriceAtk();
	bool runActionSkillOne();
	bool runActionSkillTwo();
	bool runActionSkillThree();
	bool runActionSkillFour();
	/* ����ִ�� End */

	void skillOne(int atk, bool bDown);				// ���ܶ�
	void skillFour(); 								// ������

private:
	RoleFlightProp m_stPangJuanProp[PangJuan_Max];
};