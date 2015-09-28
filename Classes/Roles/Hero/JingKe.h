/*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ�����   JingKe
** ��  �ڣ�   2015:2:3
** ˵  ����	����
** ��  ����	
** ��  ʷ��	2015:2:3 ��ʼ�汾
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "Roles/Role/Role.h"
#include "Roles/SkillProps/CommonProp.h"

enum JingKeProp
{
	JingKe_S1Prop = 0,
	JingKe_S4Prop,
	JingKe_Max
};

class JingKe : public Role
{
public:
	JingKe(void);
	virtual ~JingKe(void);

	CREATE_ROLE_FUNC(JingKe);

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
	RoleFlightProp m_stJingkeProp[JingKe_Max];
};