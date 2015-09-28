/*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名：   QuYuan
** 日  期：   2015:2:4
** 说  明：	
** 其  它：	
** 历  史：	2015:2:4 初始版本
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "Roles/Role/Role.h"
#include "Roles/SkillProps/CommonProp.h"

enum QuYuanFlight
{
	QuYuan_Magic = 0,
	QuYuan_S3Prop,
	QuYuan_S4Prop,
	QuYuan_Max
};

class QuYuan : public Role
{
public:
	QuYuan(void);
	virtual ~QuYuan(void);

	CREATE_ROLE_FUNC(QuYuan);

protected:
	void loadArmature();											/* 加载动画资源 */
	void initFlightPropInfo();										/* 初始化技能飞行道具 */
	void aiActSequenceBoss();										/* Boss Ai攻击序列 */

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
	
	void skillTwo(bool bDown);					// 技能二
	void skillThree();							// 技能三
	void skillFour();							// 技能四

private:
	RoleFlightProp m_strQuYuanProp[QuYuan_Max];
};