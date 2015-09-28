/*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ����� BaiQi
** ���ڣ�   2015:1:30
** ˵����	ׯ��
** ������	
** ��ʷ��2015:1:30 ��ʼ�汾
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "Roles/Role/Role.h"
#include "Roles/SkillProps/CommonProp.h"

enum ZhuangJiFlight
{
	ZhuangJi_S1Prop = 0,
	ZhuangJi_S2Prop,
	ZhuangJi_Max
};

class ZhuangJi : public Role
{
public:
	ZhuangJi(void);
	virtual ~ZhuangJi(void);

	CREATE_ROLE_FUNC(ZhuangJi);

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
	/* ����ִ�� End */

	void ZhuangJiSkill(ZhuangJiFlight);

private:
	RoleFlightProp m_stZhuangJiProp[ZhuangJi_Max];
};

