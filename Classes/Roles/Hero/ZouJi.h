/*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ����� BaiQi
** ���ڣ�   2015:1:30
** ˵����	�޼�
** ������	
** ��ʷ��2015:1:30 ��ʼ�汾
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "Roles/Role/Role.h"
#include "Roles/SkillProps/CommonProp.h"

class ZouJi : public Role
{
public:
	ZouJi(void);
	virtual ~ZouJi(void);

	CREATE_ROLE_FUNC(ZouJi);
	
public:

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
	/* ����ִ�� End */

	void SkillTwo();
	void SkillThree(float);

	void ShadowSchedule(float);
	void deathEffectCallBack();										/* ������ص� */

private:
	RoleFlightProp	m_stZouJiProp;
};

