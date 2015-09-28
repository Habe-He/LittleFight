 /*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ����� LiMu
** ���ڣ�   2015:2:3
** ˵����	����
** ������	
** ��ʷ��2015:2:3 ��ʼ�汾
*********************************************************************/
#pragma once
#include "Roles/Role/Role.h"

class LiMu : public Role
{
public:
	LiMu(void);
	virtual ~LiMu(void);

	CREATE_ROLE_FUNC(LiMu);

protected:
	void loadArmature();											/* ���ض�����Դ */
	void initTalentEffect();										/* �����츳buff */

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

