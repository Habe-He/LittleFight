 /*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ����� LianPo
** ���ڣ�   2015:1:30
** ˵����	����
** ������	
** ��ʷ��2015:1:30 ��ʼ�汾
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "Roles/Role/Role.h"
#include "Roles/SkillProps/CommonProp.h"

enum LianPoArrow
{
	LianPo_Normal = 0,
	LianPo_S2Prop,
	LianPo_S4Prop,
	LianPo_Max
};

class LianPo : public Role
{
public:
	LianPo(void);
	virtual ~LianPo(void);

	CREATE_ROLE_FUNC(LianPo);

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

	void LianPoShot(LianPoArrow,  bool);
	void LianPoS1();
	void s1CallBack1(cocos2d::Node *);
	void s1CallBack2(cocos2d::Node *);

private:
	std::map<cocos2d::Sprite*, cocos2d::Point> m_mapS1;			/* ����s1������*/

	RoleFlightProp m_stLianPoProp[LianPo_Max];
};

