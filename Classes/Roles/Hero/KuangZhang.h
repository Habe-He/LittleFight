 /*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ����� KuangZhang
** ���ڣ�   2015:2:3
** ˵����	����
** ������	
** ��ʷ��2015:2:3 ��ʼ�汾
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "Roles/Role/Role.h"

class KuangZhang : public Role
{
public:
	KuangZhang(void);
	virtual ~KuangZhang(void);

	CREATE_ROLE_FUNC(KuangZhang);

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
	/* ����ִ�� End */
};

