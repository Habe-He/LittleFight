/*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ����� BaiQi
** ���ڣ�   2015:1:30
** ˵����	��ů
** ������	
** ��ʷ��2015:1:30 ��ʼ�汾
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "Roles/Role/Role.h"
#include "Roles/SkillProps/IcePiton.h"

enum PangNuanS3
{
	PangNuanS3_One = 0,
	PangNuanS3_Two,
	PangNuanS3_Three,
	PangNuanS3_Max
};

enum PangNuanProp
{
	PangNuan_Magic,
	PangNuan_Light,
	PangNuan_Ice,
	PangNuan_Max
};

class PangNuan : public Role
{
public:
	PangNuan(void);
	virtual ~PangNuan(void);

	CREATE_ROLE_FUNC(PangNuan);

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
	/* ����ִ�� End */

	void NormalAttack(bool);
	void SkillTwo();
	void SkillThree(float , int);

	bool removeIceByID(int);
	void IceSchedule(float);
	
private:
	IcePiton		*m_hIcePiton[PangNuanS3_Max];
	RoleFlightProp	m_stPangNuanProp[PangNuan_Max];
};

