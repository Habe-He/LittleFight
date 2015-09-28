/*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名：   JiangYi
** 日  期：   2015:2:2
** 说  明：	江乙
** 其  它：	
** 历  史：	2015:2:2 初始版本
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "Roles/Role/Role.h"
#include "Roles/SkillProps/CommonProp.h"

enum JiangYiProp
{
	JiangYi_Magic = 0,
	JiangYi_S3Prop,
	JiangYi_S4Prop,
	JiangYi_Max
};

class JiangYi : public Role
{
public:
	JiangYi(void);
	virtual ~JiangYi(void);

	CREATE_ROLE_FUNC(JiangYi);

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

	// 技能二
	void skillTwo(bool bDown);
	// 技能三
	void skillThree();
	// 技能四
	void skillFour();

private:
	RoleFlightProp m_stJiangYiProp[JiangYi_Max];
};