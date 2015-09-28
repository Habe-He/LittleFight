/*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名： LianPo
** 日期：   2015:1:30
** 说明：	赵括
** 其它：	
** 历史：2015:1:30 初始版本
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "Roles/Role/Role.h"
#include "Roles/SkillProps/CommonProp.h"

enum ZhaoKuoFlight
{
	ZhaoKuo_Normal = 0,
	ZhaoKuo_S1Prop,
	ZhaoKuo_S2Prop,
	ZhaoKuo_Max
};

class ZhaoKuo : public Role
{
public:
	ZhaoKuo(void);
	virtual ~ZhaoKuo(void);

	CREATE_ROLE_FUNC(ZhaoKuo);

protected:
	void loadArmature();											/* 加载动画资源 */
	void initFlightPropInfo();										/* 初始化技能飞行道具 */
	void aiActSequenceBoss();										/* Boss Ai攻击序列 */

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

	void ZhaoKuoArrow(ZhaoKuoFlight, bool, Point);
	void ZhaoKuoS1();
	void s1CallBack1(cocos2d::Node *);
	void s1CallBack2(cocos2d::Node *);

private:
	std::map<cocos2d::Sprite*, cocos2d::Point> m_mapS1;			/* 技能s1，箭雨*/
	RoleFlightProp m_stZhaoKuoProp[ZhaoKuo_Max];
};

