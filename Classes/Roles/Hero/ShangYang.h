/*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名： BaiQi
** 日期：   2015:1:30
** 说明：	商鞅
** 其它：	
** 历史：2015:1:30 初始版本
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "Roles/Role/Role.h"
#include "Roles/SkillProps/FontGuard.h"

enum ShangYangS3
{
	ShangYangS3_One = 0,
	ShangYangS3_Two,
	ShangYangS3_Three,
	ShangYangS3_Max
};

enum ShangYangProp
{
	ShangYang_Magic = 0,
	ShangYang_S2Prop,
	ShangYang_S3Prop,
	ShangYang_Max
};

class ShangYang : public Role
{
public:
	ShangYang(void);
	virtual ~ShangYang(void);

	CREATE_ROLE_FUNC(ShangYang);

protected:
	void loadArmature();											/* 加载动画资源 */
	void initActInherent();											/* 初始化角色技能属性 */
	void initFlightPropInfo();										/* 初始化技能飞行道具 */

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

	int roleHurt(Role* , SkillInfo , bool);

	void NormalAttack(bool);
	void SkillTwo();
	void SkillThree(float , int);

	bool removeFontByID(int);
	void FontSchedule(float);


private:
	FontGuard		*m_hShangYangFont[ShangYangS3_Max];
	RoleFlightProp	m_stShangYangProp[ShangYang_Max];
};

