#include "TianJi.h"

USING_NS_CC;
using namespace cocostudio;

Tianji::Tianji(void)
{
}

Tianji::~Tianji(void)
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
void Tianji::loadArmature()
{
	m_stRoleInfo.arAnimate = Armature::create(m_strRoleName.c_str());
	if (NULL == m_stRoleInfo.arAnimate)
	{
		return;
	}

	this->addChild(m_stRoleInfo.arAnimate);
	
	/* 注册动画帧事件和动作回调函数 */
	m_stRoleInfo.arAnimate->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(Tianji::actionFrameEventCallFunc, this, std::placeholders::_1
		, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	m_stRoleInfo.arAnimate->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(Tianji::actionMovementCallFunc, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

/*********************************************************************
** 功能：		设置天赋buff
** 输入参数：	无
** 返回值：		无
** 修改记录：	
*********************************************************************/
void Tianji::initTalentEffect()
{
	Role::initTalentEffect();

	if (true == isRoleLearnedTalent(RoleTalent_ShiXue))		/* 田忌：嗜血 */
	{
		m_stRoleInfo.panel.hpTotal = m_stRoleInfo.panel.hpTotal * 1.8f;
		m_stRoleInfo.panel.allHarm += 0.12f;
	}
}

/*********************************************************************
** 功能：		动作回调函数
** 输入参数：	
** 返回值： 	
** 修改记录：	
*********************************************************************/
void Tianji::actionMovementCallFunc(Armature *ar, MovementEventType type, const std::string& str)
{
	movement(str, type, 0.5f);
}

/*********************************************************************
** 功能：		帧事件
** 输入参数：	
** 返回值： 	无
** 修改记录：	
*********************************************************************/
void Tianji::actionFrameEventCallFunc(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
{
	frameEvent(evt);

	if (RoleAct_SkillOne == m_stRoleInfo.actSign)
	{
		if (getFrameEventName(FrameEvent_Attack) == evt)
		{
			if (RoleCreMode_Fighting == m_eRoleCreMode)
			{
				auto ptX = getPositionX();
				setPositionX(ptX - 130 * m_stRoleSubInfo.side);
			}
		}
	}

	if (RoleAct_SkillThree == m_stRoleInfo.actSign)
	{
		if (getFrameEventName(FrameEvent_Begin) == evt)
		{
			if (RoleCreMode_Fighting == m_eRoleCreMode)
			{
				auto move = MoveBy::create(14.0f / 36.0f, Point(-180, 0) * m_stRoleSubInfo.side);
				runAction(move);
			}
		}
	}
}

/* 动作执行 Begin*/
/*********************************************************************
** 功能：		普通攻击第一击
** 输入参数：	无
** 返回值：		bool:true:动作执行成功
** 修改记录：	
*********************************************************************/
bool Tianji::runActionAttack()
{
	bool bRet = Role::runActionAttack();
	if (true == bRet)
	{
		playEffectOgg("C1");
	}

	return bRet;
}

/*********************************************************************
** 功能：		普通攻击第二击
** 输入参数：	无
** 返回值：		bool:true:动作执行成功
** 修改记录：	
*********************************************************************/
bool Tianji::runActionTwiceAtk()
{
	bool bRet = Role::runActionTwiceAtk();
	if (true == bRet)
	{
		playEffectOgg("C1");
	}

	return bRet;
}

/*********************************************************************
** 功能：		普通攻击第三击
** 输入参数：	无
** 返回值：		bool:true:动作执行成功
** 修改记录：	
*********************************************************************/
bool Tianji::runActionThriceAtk()
{
	bool bRet = Role::runActionThriceAtk();
	if (true == bRet)
	{
		playEffectOgg("C2");
	}

	return bRet;
}

/*********************************************************************
** 功能：		执行技能一
** 输入参数：	无
** 返回值： 	无
** 修改记录：	
*********************************************************************/
bool Tianji::runActionSkillOne()
{
	bool bRet = Role::runActionSkillOne();
	if (true == bRet)
	{
		playEffectOgg("CJ");
	}

	return bRet;
}

/*********************************************************************
** 功能：		执行技能二
** 输入参数：	无
** 返回值： 	无
** 修改记录：	
*********************************************************************/
bool Tianji::runActionSkillTwo()
{
	bool bRet = Role::runActionSkillTwo();
	if (true == bRet)
	{
		playEffectOgg("SL2");
	}

	return bRet;
}

/*********************************************************************
** 功能：		执行技能三
** 输入参数：	无
** 返回值： 	无
** 修改记录：	
*********************************************************************/
bool Tianji::runActionSkillThree()
{
	bool bRet = Role::runActionSkillThree();
	if (true == bRet)
	{
		playEffectOgg("CJ2");
	}

	return bRet;
}

/*********************************************************************
** 功能：		执行技能四
** 输入参数：	无
** 返回值： 	无
** 修改记录：	
*********************************************************************/
bool Tianji::runActionSkillFour()
{
	bool bRet = Role::runActionSkillFour();
	if (true == bRet)
	{
		playEffectOgg("ZH");
	}

	return bRet;
}
/* 动作执行 End*/
/* protected: End */