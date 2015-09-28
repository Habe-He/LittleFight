/*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ�����   ChunYuKun
** ��  �ڣ�   2015:1:31
** ˵  ����	������
** ��  ����	
** ��  ʷ��	2015:1:31 ��ʼ�汾
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "Roles/Role/Role.h"
#include "Roles/SkillProps/CommonProp.h"

class ChunYuKun : public Role
{
public:
	ChunYuKun(void);
	virtual ~ChunYuKun(void);

	CREATE_ROLE_FUNC(ChunYuKun);

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

	void skillTwoCallBack(Node* node);

private:
	RoleFlightProp	m_stChunYuKunProp;
};

