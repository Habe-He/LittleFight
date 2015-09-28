/*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名： BaiQi
** 日期：   2015:1:30
** 说明：	庄姬
** 其它：	
** 历史：2015:1:30 初始版本
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "Roles/Role/Role.h"
#include "Roles/SkillProps/CommonProp.h"

enum ZhuangJiFlight
{
	ZhuangJi_S1Prop = 0,
	ZhuangJi_S2Prop,
	ZhuangJi_Max
};

class ZhuangJi : public Role
{
public:
	ZhuangJi(void);
	virtual ~ZhuangJi(void);

	CREATE_ROLE_FUNC(ZhuangJi);

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
	/* 动作执行 End */

	void ZhuangJiSkill(ZhuangJiFlight);

private:
	RoleFlightProp m_stZhuangJiProp[ZhuangJi_Max];
};

