 /*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ����� BianQue
** ���ڣ�   2015:1:30
** ˵����	��ȵ
** ������	
** ��ʷ��2015:1:30 ��ʼ�汾
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "Roles/Role/Role.h"
#include "Roles/SkillProps/IcePiton.h"

enum BianQueS3
{
	BianQueS3_One = 0,
	BianQueS3_Two,
	BianQueS3_Three,
	BianQueS3_Max
};

enum BianQueRes
{
	BianQue_Magic = 0,					/* �չ�ħ���� */
	BianQue_Light,						/* ��Ѫħ�� */
	BianQue_Ice,						/* ��ħ�� */
	BianQue_Phenix,						/* ���ħ�� */
	BianQue_Max
};

class BianQue : public Role
{
public:
	BianQue(void);
	virtual ~BianQue(void);

	CREATE_ROLE_FUNC(BianQue);

protected:
	void loadArmature();											/* ���ض�����Դ */
	void initActInherent();											/* ��ʼ����ɫ�������� */
	void initFlightPropInfo();										/* ��ʼ�����ܷ��е��� */

	void actionMovementCallFunc(cocostudio::Armature *, cocostudio::MovementEventType, const std::string&);
	void actionFrameEventCallFunc(cocostudio::Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);

	void updateRole();

	/* ִ����ײ��� */
	void roleCollisionDetective(bool);

	/* ����ִ�� Begin */
	bool runActionAttack();
	bool runActionTwiceAtk();
	bool runActionThriceAtk();
	bool runActionSkillOne();
	bool runActionSkillTwo();
	bool runActionSkillThree();
	bool runActionSkillFour();

	/* ����ִ�� End */

	void NormalAttack(cocos2d::Point , bool);
	void SkillTwo();
	void SkillThree(float , int);
	void SkillFour();

	bool removeIceByID(int);
	void IceSchedule(float);

private:
	IcePiton		*m_hIcePiton[BianQueS3_Max];
	RoleFlightProp	m_stBianQueProp[BianQue_Max];
};

