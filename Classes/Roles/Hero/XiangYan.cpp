#include "XiangYan.h"

USING_NS_CC;
using namespace cocostudio;

const float fXY_S4Delay = 0.83f;				/* 技能4播放时间 */
const float fXY_S4MoveBy = 160.0f;				/* 技能4移动距离 */

XiangYan::XiangYan(void)
{
}

XiangYan::~XiangYan(void)
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
void XiangYan::loadArmature()
{
	m_stRoleInfo.arAnimate = Armature::create(m_strRoleName.c_str());
	if (NULL == m_stRoleInfo.arAnimate)
	{
		return;
	}

	this->addChild(m_stRoleInfo.arAnimate);

	/* 注册动画帧事件和动作回调函数 */
	m_stRoleInfo.arAnimate->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(XiangYan::actionFrameEventCallFunc, this, std::placeholders::_1
		, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	m_stRoleInfo.arAnimate->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(XiangYan::actionMovementCallFunc, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

/*********************************************************************
** 功能：		设置天赋buff
** 输入参数：	无
** 返回值：		无
** 修改记录：	
*********************************************************************/
void XiangYan::initTalentEffect()
{
	Role::initTalentEffect();

	if (true == isRoleLearnedTalent(RoleTalent_ZhongXingWuQi))	/* 项燕：重型武器 */
	{
		m_stRoleInfo.panel.critical += 15.0f;
		m_stRoleInfo.panel.criExtra += 0.2f;
	}
}

/* 动作执行 Begin */
/*********************************************************************
** 功能：		动作回调函数
** 输入参数：	
** 返回值： 	
** 修改记录：	
*********************************************************************/
void XiangYan::actionMovementCallFunc(Armature *ar, MovementEventType type, const std::string& str)
{
	movement(str, type, 0.5f);
}

/*********************************************************************
** 功能：		帧事件
** 输入参数：	
** 返回值： 	无
** 修改记录：	
*********************************************************************/
void XiangYan::actionFrameEventCallFunc(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
{
	frameEvent(evt);

	if ((RoleAct_SkillFour == m_stRoleInfo.actSign) && (getFrameEventName(FrameEvent_Begin) == evt))
	{
		if (RoleCreMode_Fighting == m_eRoleCreMode)
		{
			auto move = MoveBy::create(fXY_S4Delay, Point(0 - fXY_S4MoveBy * m_stRoleSubInfo.side, 0));
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
bool XiangYan::runActionAttack()
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
bool XiangYan::runActionTwiceAtk()
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
bool XiangYan::runActionThriceAtk()
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
bool XiangYan::runActionSkillOne()
{
	bool bRet = Role::runActionSkillOne();
	if (true == bRet)
	{
		playEffectOgg("077Q");
	}

	return bRet;
}

/*********************************************************************
** 功能：		执行技能二
** 输入参数：	无
** 返回值： 	无
** 修改记录：	
*********************************************************************/
bool XiangYan::runActionSkillTwo()
{
	bool bRet = Role::runActionSkillTwo();
	if (true == bRet)
	{
		playEffectOgg("080TD");
	}

	return bRet;
}

/*********************************************************************
** 功能：		执行技能三
** 输入参数：	无
** 返回值： 	无
** 修改记录：	
*********************************************************************/
bool XiangYan::runActionSkillThree()
{
	bool bRet = Role::runActionSkillThree();
	if (true == bRet)
	{
		playEffectOgg("JN1");
	}

	return bRet;
}

/*********************************************************************
** 功能：		执行技能四
** 输入参数：	无
** 返回值： 	无
** 修改记录：	
*********************************************************************/
bool XiangYan::runActionSkillFour()
{
	bool bRet = Role::runActionSkillFour();
	if (true == bRet)
	{
		playEffectOgg("081");
	}

	return bRet;
}
/* 动作执行 End*/
/* protected: End */