 /*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名： BianQue
** 日期：   2015:1:30
** 说明：	扁鹊
** 其它：	
** 历史：2015:1:30 初始版本
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "Roles/Role/Role.h"
#include "Roles/SkillProps/IcePiton.h"

enum BianQueS3
{
	BianQueS3_One = 0,
	BianQueS3_Two,
	BianQueS3_Three,
	BianQueS3_Max
};

enum BianQueRes
{
	BianQue_Magic = 0,					/* 普攻魔法球 */
	BianQue_Light,						/* 回血魔法 */
	BianQue_Ice,						/* 冰魔法 */
	BianQue_Phenix,						/* 凤凰魔法 */
	BianQue_Max
};

class BianQue : public Role
{
public:
	BianQue(void);
	virtual ~BianQue(void);

	CREATE_ROLE_FUNC(BianQue);

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
	bool runActionSkillFour();

	/* 动作执行 End */

	void NormalAttack(cocos2d::Point , bool);
	void SkillTwo();
	void SkillThree(float , int);
	void SkillFour();

	bool removeIceByID(int);
	void IceSchedule(float);

private:
	IcePiton		*m_hIcePiton[BianQueS3_Max];
	RoleFlightProp	m_stBianQueProp[BianQue_Max];
};

