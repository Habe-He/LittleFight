/*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名：   WuMengYao
** 日  期：   2015:2:4
** 说  明：	
** 其  它：	
** 历  史：	2015:2:4 初始版本
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "Roles/Role/Role.h"
#include "Roles/SkillProps/CommonProp.h"

enum WuMengYaoFlight
{
	WuMengYao_Arrow = 0,
	WuMengYao_S3Prop,
	WuMengYao_Max
};

class WuMengYao : public Role
{
public:
	WuMengYao(void);
	virtual ~WuMengYao(void);

	CREATE_ROLE_FUNC(WuMengYao);

protected:
	void loadArmature();											/* 加载动画资源 */
	void initFlightPropInfo();										/* 初始化技能飞行道具 */
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
	void comArrow(bool fd);
	void skillTwo(bool fd);

	void skillThree(bool fd);

private:
	RoleFlightProp m_stWuMengYaoProp[WuMengYao_Max];
};