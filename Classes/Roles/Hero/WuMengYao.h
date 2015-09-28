/*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ�����   WuMengYao
** ��  �ڣ�   2015:2:4
** ˵  ����	
** ��  ����	
** ��  ʷ��	2015:2:4 ��ʼ�汾
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "Roles/Role/Role.h"
#include "Roles/SkillProps/CommonProp.h"

enum WuMengYaoFlight
{
	WuMengYao_Arrow = 0,
	WuMengYao_S3Prop,
	WuMengYao_Max
};

class WuMengYao : public Role
{
public:
	WuMengYao(void);
	virtual ~WuMengYao(void);

	CREATE_ROLE_FUNC(WuMengYao);

protected:
	void loadArmature();											/* ���ض�����Դ */
	void initFlightPropInfo();										/* ��ʼ�����ܷ��е��� */
	void initTalentEffect();										/* �����츳buff */

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
	void comArrow(bool fd);
	void skillTwo(bool fd);

	void skillThree(bool fd);

private:
	RoleFlightProp m_stWuMengYaoProp[WuMengYao_Max];
};