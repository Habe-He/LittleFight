 /*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名： JingYang
** 日期：   2015:2:3
** 说明：	景阳
** 其它：	
** 历史：2015:2:3 初始版本
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "Roles/Role/Role.h"
#include "Roles/SkillProps/CommonProp.h"

class JingYang : public Role
{
public:
	JingYang(void);
	virtual ~JingYang(void);

	CREATE_ROLE_FUNC(JingYang);

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
	/* 动作执行 End */

	void SkillTwo();

private:
	RoleFlightProp m_stJingYangProp;
};

