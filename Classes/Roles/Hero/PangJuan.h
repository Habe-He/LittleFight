/*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名：   PangJuan
** 日  期：   2015:2:3
** 说  明：	
** 其  它：	
** 历  史：	2015:2:3 初始版本
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "Roles/Role/Role.h"
#include "Roles/SkillProps/CommonProp.h"

enum PangJuanProp
{
	PangJuan_S1Prop = 0,
	PangJuan_S4Prop,
	PangJuan_Max
};

class PangJuan : public Role
{
public:
	PangJuan(void);
	virtual ~PangJuan(void);

	CREATE_ROLE_FUNC(PangJuan);

protected:
	void loadArmature();											/* 加载动画资源 */
	void initFlightPropInfo();										/* 初始化技能飞行道具 */

	void actionMovementCallFunc(cocostudio::Armature *, cocostudio::MovementEventType, const std::string&);
	void actionFrameEventCallFunc(cocostudio::Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);

	/* 动作执行 Begin */
	bool runActionAttack();
	bool runActionTwiceAtk();
	bool runActionThriceAtk();
	bool runActionSkillOne();
	bool runActionSkillTwo();
	bool runActionSkillThree();
	bool runActionSkillFour();
	/* 动作执行 End */

	void skillOne(int atk, bool bDown);				// 技能二
	void skillFour(); 								// 技能四

private:
	RoleFlightProp m_stPangJuanProp[PangJuan_Max];
};