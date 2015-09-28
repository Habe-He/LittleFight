 /*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名： ChenZhen
** 日期：   2015:1:31
** 说明：	陈轸
** 其它：	
** 历史：2015:1:31 初始版本
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "Roles/Role/Role.h"

class ChenZhen : public Role
{
public:
	ChenZhen(void);
	virtual ~ChenZhen(void);

	CREATE_ROLE_FUNC(ChenZhen);

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

