 /*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名： LianPo
** 日期：   2015:1:30
** 说明：	廉颇
** 其它：	
** 历史：2015:1:30 初始版本
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "Roles/Role/Role.h"
#include "Roles/SkillProps/CommonProp.h"

enum LianPoArrow
{
	LianPo_Normal = 0,
	LianPo_S2Prop,
	LianPo_S4Prop,
	LianPo_Max
};

class LianPo : public Role
{
public:
	LianPo(void);
	virtual ~LianPo(void);

	CREATE_ROLE_FUNC(LianPo);

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

	void LianPoShot(LianPoArrow,  bool);
	void LianPoS1();
	void s1CallBack1(cocos2d::Node *);
	void s1CallBack2(cocos2d::Node *);

private:
	std::map<cocos2d::Sprite*, cocos2d::Point> m_mapS1;			/* 技能s1，箭雨*/

	RoleFlightProp m_stLianPoProp[LianPo_Max];
};

