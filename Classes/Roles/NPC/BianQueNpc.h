 /*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ����� BianQueNpcNpc
** ���ڣ�   2015:1:30
** ˵����	��ȵ
** ������	
** ��ʷ��2015:1:30 ��ʼ�汾
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "Roles/Role/Role.h"

const int MaxTurning = 7;

class BianQueNpc : public Role
{
public:
	BianQueNpc(void);
	virtual ~BianQueNpc(void);

	CREATE_ROLE_FUNC(BianQueNpc);

protected:
	void loadArmature();											/* ���ض�����Դ */
	void initActInherent();											/* ��ʼ����ɫ�������� */
	virtual void aiActSequenceBoss();								/* Boss Ai�������� */

	void actionMovementCallFunc(cocostudio::Armature *, cocostudio::MovementEventType, const std::string&);
	void actionFrameEventCallFunc(cocostudio::Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);
	
	/* ִ����ײ��� */
	void roleCollisionDetective(bool);
	void runRoleAI();
	void roleAiStep();												/* Ai��Ϊѡ�� */

	/* ����ִ�� Begin */
	void runSkill(float);
	bool runActionSkillOne();

	/* ����ִ�� End */

private:
	int		_dmgValue[MaxTurning];
	int		_curTurning;
};

