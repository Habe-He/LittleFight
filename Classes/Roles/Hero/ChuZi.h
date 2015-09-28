 /*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名： ChuZi
** 日期：   2015:1:31
** 说明：	触子
** 其它：	
** 历史：2015:1:31 初始版本
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "Roles/Role/Role.h"
#include "Roles/SkillProps/CommonProp.h"

enum ChuZiArrow
{
	ChuZi_Normal = 0,
	ChuZi_S2Prop,
	ChuZi_Max
};

class ChuZi : public Role
{
public:
	ChuZi(void);
	virtual ~ChuZi(void);

	CREATE_ROLE_FUNC(ChuZi);

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

	void ChuZiShot(ChuZiArrow, bool);							/* 射箭 */
	void ChuziS1();
	void s1CallBack1(cocos2d::Node *);
	void s1CallBack2(cocos2d::Node *);

private:
	std::map<cocos2d::Sprite*, cocos2d::Point> m_mapS1;			/* 技能s1，箭雨*/

	RoleFlightProp m_stChuZiShot[ChuZi_Max];
};

