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
#include "Roles/SkillProps/FontGuard.h"

enum ShangYangS3
{
	ShangYangS3_One = 0,
	ShangYangS3_Two,
	ShangYangS3_Three,
	ShangYangS3_Max
};

enum ShangYangProp
{
	ShangYang_Magic = 0,
	ShangYang_S2Prop,
	ShangYang_S3Prop,
	ShangYang_Max
};

class ShangYang : public Role
{
public:
	ShangYang(void);
	virtual ~ShangYang(void);

	CREATE_ROLE_FUNC(ShangYang);

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
	bool runActionSkillFour();
	/* ����ִ�� End */

	int roleHurt(Role* , SkillInfo , bool);

	void NormalAttack(bool);
	void SkillTwo();
	void SkillThree(float , int);

	bool removeFontByID(int);
	void FontSchedule(float);


private:
	FontGuard		*m_hShangYangFont[ShangYangS3_Max];
	RoleFlightProp	m_stShangYangProp[ShangYang_Max];
};

