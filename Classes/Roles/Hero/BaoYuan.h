 /*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ����� BaoYuan
** ���ڣ�   2015:1:30
** ˵����	��ԧ
** ������	
** ��ʷ��2015:1:30 ��ʼ�汾
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "Roles/Role/Role.h"

class BaoYuan : public Role
{
public:
	BaoYuan(void);
	virtual ~BaoYuan(void);

	CREATE_ROLE_FUNC(BaoYuan);

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

