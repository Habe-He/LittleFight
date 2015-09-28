 /*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ����� LouHuan
** ���ڣ�   2015:2:3
** ˵����	¥��
** ������	
** ��ʷ��2015:2:3 ��ʼ�汾
*********************************************************************/
#pragma once
#include "Roles/Role/Role.h"

class LouHuan : public Role
{
public:
	LouHuan(void);
	virtual ~LouHuan(void);

	CREATE_ROLE_FUNC(LouHuan);

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
	/* ����ִ�� End */
};

