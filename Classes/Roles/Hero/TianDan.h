/*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ����� BaiQi
** ���ڣ�   2015:1:30
** ˵����	�ﵥ
** ������	
** ��ʷ��2015:1:30 ��ʼ�汾
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "Roles/Role/Role.h"
#include "Roles/FlightProp/SatelliteProp.h"

enum TianDanS3
{
	TianDanS3_One = 0,
	TianDanS3_Two,
	TianDanS3_Three,
	TianDanS3_Max
};

enum TianDanProp
{
	TianDan_Normal = 0,
	TianDan_S2Prop,
	TianDan_S3Prop,
	TianDan_Max
};

class TianDan : public Role
{
public:
	TianDan(void);
	virtual ~TianDan(void);

	CREATE_ROLE_FUNC(TianDan);

protected:
	void loadArmature();											/* ���ض�����Դ */
	void initActInherent();											/* ��ʼ����ɫ�������� */
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

	int roleHurt(Role*, SkillInfo, bool);

	void NormalAttack(bool);
	void SkillTwo();
	void SkillThree(float , int);

	bool removeFireByID(int);
	void fireSchedule(float);

private:
	SatelliteProp	*m_hTianDanFire[TianDanS3_Max];
	RoleFlightProp	m_stTianDanProp[TianDan_Max];
};

