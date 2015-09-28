 /*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名： SunWu
** 日期：   2015:2:4
** 说明：	孙武
** 其它：	
** 历史：2015:2:4 初始版本
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "Roles/Role/Role.h"
#include "Roles/SkillProps/CommonProp.h"

class SunWu : public Role
{
public:
	SunWu(void);
	virtual ~SunWu(void);

	CREATE_ROLE_FUNC(SunWu);

protected:
	void loadArmature();											/* 加载动画资源 */
	void initFlightPropInfo();										/* 初始化技能飞行道具 */

	void actionMovementCallFunc(cocostudio::Armature *, cocostudio::MovementEventType, const std::string&);
	void actionFrameEventCallFunc(cocostudio::Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);

	void updateRole();										/* 刷新 */

	/* 动作执行 Begin */
	bool runActionAttack();
	bool runActionTwiceAtk();
	bool runActionThriceAtk();
	bool runActionSkillOne();
	bool runActionSkillTwo();
	bool runActionSkillThree();
	bool runActionSkillFour();
	/* 动作执行 End */

	void SkillTwo();

private:
	RoleFlightProp m_stSunWuProp;
};

