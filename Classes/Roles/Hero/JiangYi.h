/*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ�����   JiangYi
** ��  �ڣ�   2015:2:2
** ˵  ����	����
** ��  ����	
** ��  ʷ��	2015:2:2 ��ʼ�汾
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "Roles/Role/Role.h"
#include "Roles/SkillProps/CommonProp.h"

enum JiangYiProp
{
	JiangYi_Magic = 0,
	JiangYi_S3Prop,
	JiangYi_S4Prop,
	JiangYi_Max
};

class JiangYi : public Role
{
public:
	JiangYi(void);
	virtual ~JiangYi(void);

	CREATE_ROLE_FUNC(JiangYi);

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
	bool runActionSkillFour();
	/* ����ִ�� End */

	// ���ܶ�
	void skillTwo(bool bDown);
	// ������
	void skillThree();
	// ������
	void skillFour();

private:
	RoleFlightProp m_stJiangYiProp[JiangYi_Max];
};