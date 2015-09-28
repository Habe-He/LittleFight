/*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ�����   LeYi
** ��  �ڣ�   2015:2:3
** ˵  ����	
** ��  ����	
** ��  ʷ��	2015:2:3 ��ʼ�汾
*********************************************************************/
#pragma once
#include "Roles/Role/Role.h"

class LeYi : public Role
{
public:
	LeYi(void);
	virtual ~LeYi(void);

	CREATE_ROLE_FUNC(LeYi);

protected:
	void loadArmature();											/* ���ض�����Դ */

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
};
