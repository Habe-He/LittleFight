#include "BianQueNpc.h"

USING_NS_CC;
using namespace cocostudio;

BianQueNpc::BianQueNpc(void)
	: _curTurning(0)
{
}

BianQueNpc::~BianQueNpc(void)
{
}

/* public: Begin*/
/* public: End*/

/* protected: Begin */
/*********************************************************************
** 功能：		加载动画资源
** 输入参数：	无
** 返回值： 	无
** 修改记录：	
*********************************************************************/
void BianQueNpc::loadArmature()
{
	m_stRoleInfo.arAnimate = Armature::create(m_strRoleName.c_str());
	if (NULL == m_stRoleInfo.arAnimate)
	{
		return;
	}

	this->addChild(m_stRoleInfo.arAnimate);

	/* 注册动画帧事件和动作回调函数 */
	m_stRoleInfo.arAnimate->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(BianQueNpc::actionFrameEventCallFunc, this, std::placeholders::_1
		, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	m_stRoleInfo.arAnimate->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(BianQueNpc::actionMovementCallFunc, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

	_dmgValue[0] = 16000;
	_dmgValue[1] = 25000;
	_dmgValue[2] = 30000;
	_dmgValue[3] = 42000;
	_dmgValue[4] = 45000;
	_dmgValue[5] = 50000;
	_dmgValue[6] = 70000;

	this->schedule(schedule_selector(BianQueNpc::runSkill), 10.0f);	/* 每10s释放技能 */
}

/*********************************************************************
** 功能：		初始化角色技能属性
** 输入参数：	无
** 返回值：		无
** 修改记录：	
*********************************************************************/
void BianQueNpc::initActInherent()
{
	Role::initActInherent();

	m_stActMode[RoleAct_SkillOne] = RoleActMode_Super;			/* 技能一 */
	m_stActMode[RoleAct_SkillTwo] = RoleActMode_Super;			/* 技能二 */			
	m_stActMode[RoleAct_SkillThree] = RoleActMode_Control;		/* 技能三 */
}

/*********************************************************************
** 功能：		Boss Ai攻击序列
** 输入参数：	无
** 返回值：		无
** 修改记录：	
*********************************************************************/
void BianQueNpc::aiActSequenceBoss()
{
}

/*********************************************************************
** 功能：		动作回调函数
** 输入参数：	
** 返回值： 	
** 修改记录：	
*********************************************************************/
void BianQueNpc::actionMovementCallFunc(Armature *ar, MovementEventType type, const std::string& str)
{
	movement(str, type, 0.5f);
}

/*********************************************************************
** 功能：		帧事件
** 输入参数：	
** 返回值： 	无
** 修改记录：	
*********************************************************************/
void BianQueNpc::actionFrameEventCallFunc(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
{
	frameEvent(evt);
}

/*********************************************************************
** 功能：		执行碰撞检测
** 输入参数：	bool bDown:true:倒地;false:不倒地
** 返回值：		无
** 修改记录：	
*********************************************************************/
void BianQueNpc::roleCollisionDetective(bool bDown)
{
	bool bFlag = false;
	auto roles = UserData::getInstance()->getRoles();

	for(unsigned int index = 0;index < roles.size();index ++)		/* 敌人角色遍历获取 */
	{
		auto role = (Role *)roles[index];
		auto info = role->getRoleInfo();

		if ((RoleStatus_Invincible == info.status) || (m_stRoleInfo.camp == info.camp) || (m_iSceneID != role->getSceneID()))
		{
			continue;												/* 无敌、同阵营或是自身不处理 *//* 小伙伴不伤主将 */
		}

		bFlag = true;
		role->roleHurt(this, m_stSkillInfo[RoleAct_SkillOne], bDown);
	}

	if (true == bFlag)
	{
		UserData::getInstance()->setJxxg3Grade(_curTurning);
		m_stSkillInfo[RoleAct_SkillOne].damage = _dmgValue[_curTurning];
	}
}

/*********************************************************************
** 功能：		角色AI
** 输入参数：	无
** 返回值：		无
** 修改记录：	
*********************************************************************/
void BianQueNpc::runRoleAI()
{
	if (MaxTurning == _curTurning)									/* 最后一回合 */
	{
		UserData::getInstance()->removeRole(this);
		runActionDeath();
		return;
	}

	if (0 == UserData::getInstance()->getRedRoleCount())
	{
		this->unscheduleUpdate();
		return;
	}

 	switch (m_eRoleActAi)
 	{
 	case RoleActAi_None:
 		roleAiStep();
 		break;
 	case RoleActAi_ShortMove:										/* AI行为短距离移动 */
 		roleAiShortMove();
 		break;
 	default:
 		break;
 	}
}

void BianQueNpc::roleAiStep()
{
	if (RoleAct_Idle != m_stRoleInfo.actSign)
	{
		return;
	}

	auto random = ToolFunc::calcRandom(minActAiLimit, m_fActAiLimit[RoleActAi_Sleep]);
	if ((random < m_fActAiLimit[RoleActAi_ShortMove])) 				/* 漫游 */
	{
		roleAiShortMove();
	}
	else															/* 休眠 */
	{
		roleAiSleep();
	}
}

/* 动作执行 Begin*/
void BianQueNpc::runSkill(float dt)
{
	_curTurning++;
	roleUnSchedule(RoleSchedule_AiAction);
	aiActionResume(0.0f);
	runActionSkillOne();
}

/*********************************************************************
** 功能：		执行技能一
** 输入参数：	无
** 返回值： 	无
** 修改记录：	
*********************************************************************/
bool BianQueNpc::runActionSkillOne()
{
	m_stRoleInfo.status = RoleStatus_Superarmor;					/* 释放技能霸体 */
	bool bRet = Role::runActionSkillOne();
	if (true == bRet)
	{
		playEffectOgg("C035Q");
	}

	return bRet;
}
/* 动作执行 End*/