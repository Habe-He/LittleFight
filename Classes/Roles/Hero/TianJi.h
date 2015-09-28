 /*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ����� TianJi
** ���ڣ�   2015:1:30
** ˵����	���
** ������	
** ��ʷ��2015:1:30 ��ʼ�汾
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "Roles/Role/Role.h"

class Tianji : public Role
{
public:
	Tianji(void);
	virtual ~Tianji(void);

	CREATE_ROLE_FUNC(Tianji);

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

