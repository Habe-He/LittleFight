/*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名： BaiQi
** 日期：   2015:1:30
** 说明：	庞暖
** 其它：	
** 历史：2015:1:30 初始版本
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "Roles/Role/Role.h"
#include "Roles/SkillProps/IcePiton.h"

enum PangNuanS3
{
	PangNuanS3_One = 0,
	PangNuanS3_Two,
	PangNuanS3_Three,
	PangNuanS3_Max
};

enum PangNuanProp
{
	PangNuan_Magic,
	PangNuan_Light,
	PangNuan_Ice,
	PangNuan_Max
};

class PangNuan : public Role
{
public:
	PangNuan(void);
	virtual ~PangNuan(void);

	CREATE_ROLE_FUNC(PangNuan);

protected:
	void loadArmature();											/* 加载动画资源 */
	void initActInherent();											/* 初始化角色技能属性 */
	void initFlightPropInfo();										/* 初始化技能飞行道具 */

	void actionMovementCallFunc(cocostudio::Armature *, cocostudio::MovementEventType, const std::string&);
	void actionFrameEventCallFunc(cocostudio::Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);

	void updateRole();

	/* 执行碰撞检测 */
	void roleCollisionDetective(bool);

	/* 动作执行 Begin */
	bool runActionAttack();
	bool runActionTwiceAtk();
	bool runActionThriceAtk();
	bool runActionSkillOne();
	bool runActionSkillTwo();
	bool runActionSkillThree();
	/* 动作执行 End */

	void NormalAttack(bool);
	void SkillTwo();
	void SkillThree(float , int);

	bool removeIceByID(int);
	void IceSchedule(float);
	
private:
	IcePiton		*m_hIcePiton[PangNuanS3_Max];
	RoleFlightProp	m_stPangNuanProp[PangNuan_Max];
};

