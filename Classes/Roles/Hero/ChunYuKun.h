/*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名：   ChunYuKun
** 日  期：   2015:1:31
** 说  明：	淳于髡
** 其  它：	
** 历  史：	2015:1:31 初始版本
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "Roles/Role/Role.h"
#include "Roles/SkillProps/CommonProp.h"

class ChunYuKun : public Role
{
public:
	ChunYuKun(void);
	virtual ~ChunYuKun(void);

	CREATE_ROLE_FUNC(ChunYuKun);

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

	void skillTwoCallBack(Node* node);

private:
	RoleFlightProp	m_stChunYuKunProp;
};

