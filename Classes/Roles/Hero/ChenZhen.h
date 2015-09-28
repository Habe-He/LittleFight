 /*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ����� ChenZhen
** ���ڣ�   2015:1:31
** ˵����	����
** ������	
** ��ʷ��2015:1:31 ��ʼ�汾
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "Roles/Role/Role.h"

class ChenZhen : public Role
{
public:
	ChenZhen(void);
	virtual ~ChenZhen(void);

	CREATE_ROLE_FUNC(ChenZhen);

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

