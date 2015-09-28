/*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名： BaiQi
** 日期：   2015:1:30
** 说明：	田单
** 其它：	
** 历史：2015:1:30 初始版本
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "Roles/Role/Role.h"
#include "Roles/FlightProp/SatelliteProp.h"

enum TianDanS3
{
	TianDanS3_One = 0,
	TianDanS3_Two,
	TianDanS3_Three,
	TianDanS3_Max
};

enum TianDanProp
{
	TianDan_Normal = 0,
	TianDan_S2Prop,
	TianDan_S3Prop,
	TianDan_Max
};

class TianDan : public Role
{
public:
	TianDan(void);
	virtual ~TianDan(void);

	CREATE_ROLE_FUNC(TianDan);

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
	/* 动作执行 End */

	int roleHurt(Role*, SkillInfo, bool);

	void NormalAttack(bool);
	void SkillTwo();
	void SkillThree(float , int);

	bool removeFireByID(int);
	void fireSchedule(float);

private:
	SatelliteProp	*m_hTianDanFire[TianDanS3_Max];
	RoleFlightProp	m_stTianDanProp[TianDan_Max];
};

