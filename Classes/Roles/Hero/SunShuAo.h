 /*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ����� SunShuAo
** ���ڣ�   2015:2:4
** ˵����	���尽
** ������	
** ��ʷ��2015:2:4 ��ʼ�汾
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "Roles/Role/Role.h"

class SunShuAo : public Role
{
public:
	SunShuAo(void);
	virtual ~SunShuAo(void);

	CREATE_ROLE_FUNC(SunShuAo);

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

