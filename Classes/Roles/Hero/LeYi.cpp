#include "LeYi.h"

USING_NS_CC;
using namespace cocostudio;

const float fYY_S4Delay = 0.75f;				/* 技能4播放时间 */
const float fYY_S4MoveBy = 150.0f;				/* 技能4移动距离 */

LeYi::LeYi(void)
{
}

LeYi::~LeYi(void)
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
void LeYi::loadArmature()
{
	m_stRoleInfo.arAnimate = Armature::create(m_strRoleName.c_str());
	if (NULL == m_stRoleInfo.arAnimate)
	{
		return;
	}

	this->addChild(m_stRoleInfo.arAnimate);

	/* 注册动画帧事件和动作回调函数 */
	m_stRoleInfo.arAnimate->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(LeYi::actionFrameEventCallFunc, this, std::placeholders::_1
		, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	m_stRoleInfo.arAnimate->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(LeYi::actionMovementCallFunc, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

/* 动作执行 Begin */
/*********************************************************************
** 功能：		动作回调函数
** 输入参数：	
** 返回值： 	
** 修改记录：	
*********************************************************************/
void LeYi::actionMovementCallFunc(Armature *ar, MovementEventType type, const std::string& str)
{
	movement(str, type, 0.5f);
}

/*********************************************************************
** 功能：		帧事件
** 输入参数：	
** 返回值： 	无
** 修改记录：	
*********************************************************************/
void LeYi::actionFrameEventCallFunc(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
{
	frameEvent(evt);

	if ((RoleAct_SkillFour == m_stRoleInfo.actSign) && (getFrameEventName(FrameEvent_Begin) == evt))
	{
		if (RoleCreMode_Fighting == m_eRoleCreMode)
		{
			auto move = MoveBy::create(fYY_S4Delay, Point(0 - fYY_S4MoveBy * m_stRoleSubInfo.side, 0));
			this->runAction(move);
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
bool LeYi::runActionAttack()
{
	bool bRet = Role::runActionAttack();
	if (true == bRet)
	{
		playEffectOgg("C072");
	}

	return bRet;
}

/*********************************************************************
** 功能：		普通攻击第二击
** 输入参数：	无
** 返回值：		bool:true:动作执行成功
** 修改记录：	
*********************************************************************/
bool LeYi::runActionTwiceAtk()
{
	bool bRet = Role::runActionTwiceAtk();
	if (true == bRet)
	{
		playEffectOgg("C072");
	}

	return bRet;
}

/*********************************************************************
** 功能：		普通攻击第三击
** 输入参数：	无
** 返回值：		bool:true:动作执行成功
** 修改记录：	
*********************************************************************/
bool LeYi::runActionThriceAtk()
{
	bool bRet = Role::runActionThriceAtk();
	if (true == bRet)
	{
		playEffectOgg("C072");
	}

	return bRet;
}

/*********************************************************************
** 功能：		执行技能一
** 输入参数：	无
** 返回值： 	无
** 修改记录：	
*********************************************************************/
bool LeYi::runActionSkillOne()
{
	bool bRet = Role::runActionSkillOne();
	if (true == bRet)
	{
		playEffectOgg("JN1");
	}

	return bRet;
}

/*********************************************************************
** 功能：		执行技能二
** 输入参数：	无
** 返回值： 	无
** 修改记录：	
*********************************************************************/
bool LeYi::runActionSkillTwo()
{
	bool bRet = Role::runActionSkillTwo();
	if (true == bRet)
	{
		playEffectOgg("016Q");
	}

	return bRet;
}

/*********************************************************************
** 功能：		执行技能三
** 输入参数：	无
** 返回值： 	无
** 修改记录：	
*********************************************************************/
bool LeYi::runActionSkillThree()
{
	bool bRet = Role::runActionSkillThree();
	if (true == bRet)
	{
		playEffectOgg("014ZH");
	}

	return bRet;
}

/*********************************************************************
** 功能：		执行技能四
** 输入参数：	无
** 返回值： 	无
** 修改记录：	
*********************************************************************/
bool LeYi::runActionSkillFour()
{
	bool bRet = Role::runActionSkillFour();
	if (true == bRet)
	{
		playEffectOgg("014ZH");
	}

	return bRet;
}
/* 动作执行 End*/
/* protected: End */