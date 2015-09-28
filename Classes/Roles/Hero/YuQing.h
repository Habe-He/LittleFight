/*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ����� BaiQi
** ���ڣ�   2015:1:30
** ˵����	����
** ������	
** ��ʷ��2015:1:30 ��ʼ�汾
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "Roles/Role/Role.h"
#include "Roles/SkillProps/CommonProp.h"

enum YuQingProp
{
	YuQing_Normal = 0,
	YuQing_S2Prop,
	YuQing_Max
};

class YuQing : public Role
{
public:
	YuQing(void);
	virtual ~YuQing(void);

	CREATE_ROLE_FUNC(YuQing);

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

	void NormalAttack(bool);
	void SkillTwo();

private:
	RoleFlightProp m_stYuQingProp[YuQing_Max];
};

