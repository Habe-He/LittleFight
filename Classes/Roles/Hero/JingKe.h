/*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名：   JingKe
** 日  期：   2015:2:3
** 说  明：	荆轲
** 其  它：	
** 历  史：	2015:2:3 初始版本
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "Roles/Role/Role.h"
#include "Roles/SkillProps/CommonProp.h"

enum JingKeProp
{
	JingKe_S1Prop = 0,
	JingKe_S4Prop,
	JingKe_Max
};

class JingKe : public Role
{
public:
	JingKe(void);
	virtual ~JingKe(void);

	CREATE_ROLE_FUNC(JingKe);

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
	RoleFlightProp m_stJingkeProp[JingKe_Max];
};