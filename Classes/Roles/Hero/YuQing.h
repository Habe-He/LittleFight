/*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名： BaiQi
** 日期：   2015:1:30
** 说明：	虞卿
** 其它：	
** 历史：2015:1:30 初始版本
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "Roles/Role/Role.h"
#include "Roles/SkillProps/CommonProp.h"

enum YuQingProp
{
	YuQing_Normal = 0,
	YuQing_S2Prop,
	YuQing_Max
};

class YuQing : public Role
{
public:
	YuQing(void);
	virtual ~YuQing(void);

	CREATE_ROLE_FUNC(YuQing);

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

	void NormalAttack(bool);
	void SkillTwo();

private:
	RoleFlightProp m_stYuQingProp[YuQing_Max];
};

