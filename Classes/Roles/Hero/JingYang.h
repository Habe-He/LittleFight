 /*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ����� JingYang
** ���ڣ�   2015:2:3
** ˵����	����
** ������	
** ��ʷ��2015:2:3 ��ʼ�汾
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "Roles/Role/Role.h"
#include "Roles/SkillProps/CommonProp.h"

class JingYang : public Role
{
public:
	JingYang(void);
	virtual ~JingYang(void);

	CREATE_ROLE_FUNC(JingYang);

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

private:
	RoleFlightProp m_stJingYangProp;
};

