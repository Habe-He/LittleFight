 /*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名： BianQueNpcNpc
** 日期：   2015:1:30
** 说明：	扁鹊
** 其它：	
** 历史：2015:1:30 初始版本
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "Roles/Role/Role.h"

const int MaxTurning = 7;

class BianQueNpc : public Role
{
public:
	BianQueNpc(void);
	virtual ~BianQueNpc(void);

	CREATE_ROLE_FUNC(BianQueNpc);

protected:
	void loadArmature();											/* 加载动画资源 */
	void initActInherent();											/* 初始化角色技能属性 */
	virtual void aiActSequenceBoss();								/* Boss Ai攻击序列 */

	void actionMovementCallFunc(cocostudio::Armature *, cocostudio::MovementEventType, const std::string&);
	void actionFrameEventCallFunc(cocostudio::Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);
	
	/* 执行碰撞检测 */
	void roleCollisionDetective(bool);
	void runRoleAI();
	void roleAiStep();												/* Ai行为选择 */

	/* 动作执行 Begin */
	void runSkill(float);
	bool runActionSkillOne();

	/* 动作执行 End */

private:
	int		_dmgValue[MaxTurning];
	int		_curTurning;
};

