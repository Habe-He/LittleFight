/*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名：   QuGai
** 日  期：   2015:2:3
** 说  明：	  屈匄
** 其  它：	
** 历  史：	2015:2:3 初始版本
*********************************************************************/
#pragma once
#include "Roles/Role/Role.h"

class QuGai : public Role
{
public:
	QuGai(void);
	virtual ~QuGai(void);

	CREATE_ROLE_FUNC(QuGai);

protected:
	void loadArmature();											/* 加载动画资源 */

	void actionMovementCallFunc(cocostudio::Armature *, cocostudio::MovementEventType, const std::string&);
	void actionFrameEventCallFunc(cocostudio::Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);

	/* 动作执行 Begin */
	bool runActionAttack();
	bool runActionTwiceAtk();
	bool runActionThriceAtk();
	bool runActionSkillOne();
	bool runActionSkillTwo();
	/* 动作执行 End */
};