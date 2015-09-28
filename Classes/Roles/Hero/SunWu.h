 /*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ����� SunWu
** ���ڣ�   2015:2:4
** ˵����	����
** ������	
** ��ʷ��2015:2:4 ��ʼ�汾
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "Roles/Role/Role.h"
#include "Roles/SkillProps/CommonProp.h"

class SunWu : public Role
{
public:
	SunWu(void);
	virtual ~SunWu(void);

	CREATE_ROLE_FUNC(SunWu);

protected:
	void loadArmature();											/* ���ض�����Դ */
	void initFlightPropInfo();										/* ��ʼ�����ܷ��е��� */

	void actionMovementCallFunc(cocostudio::Armature *, cocostudio::MovementEventType, const std::string&);
	void actionFrameEventCallFunc(cocostudio::Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);

	void updateRole();										/* ˢ�� */

	/* ����ִ�� Begin */
	bool runActionAttack();
	bool runActionTwiceAtk();
	bool runActionThriceAtk();
	bool runActionSkillOne();
	bool runActionSkillTwo();
	bool runActionSkillThree();
	bool runActionSkillFour();
	/* ����ִ�� End */

	void SkillTwo();

private:
	RoleFlightProp m_stSunWuProp;
};

