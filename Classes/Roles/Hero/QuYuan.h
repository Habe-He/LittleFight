/*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ�����   QuYuan
** ��  �ڣ�   2015:2:4
** ˵  ����	
** ��  ����	
** ��  ʷ��	2015:2:4 ��ʼ�汾
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "Roles/Role/Role.h"
#include "Roles/SkillProps/CommonProp.h"

enum QuYuanFlight
{
	QuYuan_Magic = 0,
	QuYuan_S3Prop,
	QuYuan_S4Prop,
	QuYuan_Max
};

class QuYuan : public Role
{
public:
	QuYuan(void);
	virtual ~QuYuan(void);

	CREATE_ROLE_FUNC(QuYuan);

protected:
	void loadArmature();											/* ���ض�����Դ */
	void initFlightPropInfo();										/* ��ʼ�����ܷ��е��� */
	void aiActSequenceBoss();										/* Boss Ai�������� */

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
	
	void skillTwo(bool bDown);					// ���ܶ�
	void skillThree();							// ������
	void skillFour();							// ������

private:
	RoleFlightProp m_strQuYuanProp[QuYuan_Max];
};