 /*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名： LiMu
** 日期：   2015:2:3
** 说明：	李牧
** 其它：	
** 历史：2015:2:3 初始版本
*********************************************************************/
#pragma once
#include "Roles/Role/Role.h"

class LiMu : public Role
{
public:
	LiMu(void);
	virtual ~LiMu(void);

	CREATE_ROLE_FUNC(LiMu);

protected:
	void loadArmature();											/* 加载动画资源 */
	void initTalentEffect();										/* 设置天赋buff */

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
};

