 /*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ����� GongSunYan
** ���ڣ�   2015:2:2
** ˵����	������
** ������	
** ��ʷ��2015:2:2 ��ʼ�汾
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "Roles/Role/Role.h"

class GongSunYan : public Role
{
public:
	GongSunYan(void);
	virtual ~GongSunYan(void);

	CREATE_ROLE_FUNC(GongSunYan);

protected:
	void loadArmature();											/* ���ض�����Դ */
	void aiActSequenceBoss();										/* Boss Ai�������� */

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

