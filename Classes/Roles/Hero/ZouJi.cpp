#include "ZouJi.h"
#include "Counterpart/RoleCreate.h"

USING_NS_CC;
using namespace cocostudio;

const float fShadowDuration = 15.0f;				/* 分身持续时间 */

ZouJi::ZouJi(void)
{
}

ZouJi::~ZouJi(void)
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
void ZouJi::loadArmature()
{
	m_stRoleInfo.arAnimate = Armature::create(m_strRoleName.c_str());
	if (NULL == m_stRoleInfo.arAnimate)
	{
		return;
	}

	this->addChild(m_stRoleInfo.arAnimate);

	/* 注册动画帧事件和动作回调函数 */
	m_stRoleInfo.arAnimate->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(ZouJi::actionFrameEventCallFunc, this, std::placeholders::_1
		, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	m_stRoleInfo.arAnimate->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(ZouJi::actionMovementCallFunc, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

/*********************************************************************
** 功能：		初始化技能飞行道具
** 输入参数：	无
** 返回值：		无
** 修改记录：	
*********************************************************************/
void ZouJi::initFlightPropInfo()
{
	m_stZouJiProp.strPath = getFlightPropPath() + "ZouJi_S2Prop";
	m_stZouJiProp.ptOffset = Point(100, 100) * m_fResScale;
	m_stZouJiProp.iImgNum = 4;
}

/*********************************************************************
** 功能：		动作回调函数
** 输入参数：	
** 返回值： 	
** 修改记录：	
*********************************************************************/
void ZouJi::actionMovementCallFunc(Armature *ar, MovementEventType type, const std::string& str)
{
	movement(str, type, 0.5f);
}

/*********************************************************************
** 功能：		帧事件
** 输入参数：	
** 返回值： 	无
** 修改记录：	
*********************************************************************/
void ZouJi::actionFrameEventCallFunc(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
{
	frameEvent(evt);
	
	if ((evt == getFrameEventName(FrameEvent_Shot)) || (evt == getFrameEventName(FrameEvent_Shot_FD)))
	{
		if (RoleAct_SkillTwo == m_stRoleInfo.actSign)
		{
			SkillTwo();
		}

		if (RoleAct_SkillThree == m_stRoleInfo.actSign)
		{
			if (RoleCreMode_Fighting == m_eRoleCreMode)
			{
				this->unschedule(schedule_selector(ZouJi::ShadowSchedule));
				ShadowSchedule(0.0f);
				SkillThree(100);
				SkillThree(-100);
				this->scheduleOnce(schedule_selector(ZouJi::ShadowSchedule), fShadowDuration);
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
bool ZouJi::runActionAttack()
{
	if (true == Role::runActionAttack())
	{
		Point ptOffset = ptAtkOffset * m_stRoleSubInfo.side * -0.5f;
		setPosition(getPosition() + ptOffset);
		playEffectOgg("C97");
	}

	return true;
}

/*********************************************************************
** 功能：		普通攻击第二击
** 输入参数：	无
** 返回值：		bool:true:动作执行成功
** 修改记录：	
*********************************************************************/
bool ZouJi::runActionTwiceAtk()
{
	if (true == Role::runActionTwiceAtk())
	{
		Point ptOffset = ptAtkOffset * m_stRoleSubInfo.side * -0.5f;
		setPosition(getPosition() + ptOffset);
		playEffectOgg("C97");
	}

	return true;
}

/*********************************************************************
** 功能：		普通攻击第三击
** 输入参数：	无
** 返回值：		bool:true:动作执行成功
** 修改记录：	
*********************************************************************/
bool ZouJi::runActionThriceAtk()
{
	if (true == Role::runActionThriceAtk())
	{
		Point ptOffset = ptAtkOffset * m_stRoleSubInfo.side * -1.0f;
		setPosition(getPosition() + ptOffset);
		playEffectOgg("C97");
	}

	return true;
}

/*********************************************************************
** 功能：		执行技能一
** 输入参数：	无
** 返回值： 	无
** 修改记录：	
*********************************************************************/
bool ZouJi::runActionSkillOne()
{
	if (true == Role::runActionSkillOne())
	{
		playEffectOgg("132JN");
	}

	return true;
}

/*********************************************************************
** 功能：		执行技能二
** 输入参数：	无
** 返回值： 	无
** 修改记录：	
*********************************************************************/
bool ZouJi::runActionSkillTwo()
{
	if (true == Role::runActionSkillTwo())
	{
		playEffectOgg("047JN");
	}

	return true;
}

/*********************************************************************
** 功能：		执行技能三
** 输入参数：	无
** 返回值： 	无
** 修改记录：	
*********************************************************************/
bool ZouJi::runActionSkillThree()
{
	if (true == Role::runActionSkillThree())
	{
		playEffectOgg("135");
	}

	return true;
}

/* 动作执行 End*/

/*********************************************************************
** 功能：		邹忌技能2
** 输入参数：	无
** 返回值：		无
** 修改记录：	
*********************************************************************/
void ZouJi::SkillTwo()
{
	FlightPropInfo info = {0};
	info.num = m_stZouJiProp.iImgNum;
	info.dur = 0.1f / m_stZouJiProp.iImgNum;
	memcpy(&(info.skillInfo), &m_stSkillInfo[RoleAct_SkillTwo], sizeof(SkillInfo));

	auto zjProp = CommonProp::create(this, m_stZouJiProp.strPath, info);
	if (NULL != zjProp)
	{
		zjProp->setScaleX(m_stRoleSubInfo.side);
		zjProp->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
		zjProp->setPropPosition(Point(-m_stZouJiProp.ptOffset.x * m_stRoleSubInfo.side, m_stZouJiProp.ptOffset.y));
		this->getParent()->addChild(zjProp);
		zjProp->runPropCollisionDetective(0.5f, Point(-m_stSkillInfo[RoleAct_SkillTwo].xAtkDis * m_stRoleSubInfo.side, 0));
	}
}

/*********************************************************************
** 功能：		邹忌技能3
** 输入参数：	float xOffset: 分身坐标偏移
** 返回值：		无
** 修改记录：	
*********************************************************************/
void ZouJi::SkillThree(float xOffset)
{
	auto shadow = RoleCreate::create("ZouJi", m_eRoleCreMode);
	this->getParent()->addChild(shadow, 500);
	UserData::getInstance()->addRole(shadow);
	shadow->setMoveRegion(m_rcRegion);
	shadow->setShadowFlag(true);
	shadow->setShadowOwner(m_iRolePkID);

	RolePanel panel;
	memset(&panel, 0, sizeof(RolePanel));
	panel.hpTotal = panel.hpCurrent = m_stRoleInfo.panel.hpTotal / 4;
	panel.atk = m_stRoleInfo.panel.atk / 4;
	panel.pDefend = m_stRoleInfo.panel.pDefend / 4;
	panel.mDefend = m_stRoleInfo.panel.mDefend / 4;
	panel.level = m_stRoleInfo.panel.level;

	shadow->setSceneID(getSceneID());
	shadow->setRolePanel(panel);
	shadow->setStarLv(m_iRoleStarLv);
	shadow->setPosition(Point(getPositionX() + xOffset, getPositionY()));

	auto model = RoleMode_Main;
	if (RoleCamp_Red == m_stRoleInfo.camp)
	{
		model = RoleMode_Companion;
		UserData::getInstance()->checkRedRolecount(true);
	}
	else
	{
		model = RoleMode_Soldier;
		UserData::getInstance()->checkBlackRolecount(m_iSceneID, true);
	}
	shadow->initRoleInfo(m_stRoleInfo.camp, model, RoleRace_Wizard);

	SkillInfo skillInfo[RoleAct_Max] = {0};
	memcpy(&skillInfo, &m_stSkillInfo, sizeof(SkillInfo) * RoleAct_Max);
	skillInfo[RoleAct_SkillOne].level = 0;
	skillInfo[RoleAct_SkillTwo].level = 0;
	skillInfo[RoleAct_SkillThree].level = 0;
	skillInfo[RoleAct_SkillFour].level = 0;
	shadow->setRoleSkillInfo(skillInfo);
}

/*********************************************************************
** 功能：		火焰计时器
** 输入参数：	float dt
** 返回值：		无
** 修改记录：	
*********************************************************************/
void ZouJi::ShadowSchedule(float dt)
{
	auto roles = UserData::getInstance()->getRoles();
	for (unsigned index = 0;index < roles.size();index++)
	{
		auto role = (Role *)roles[index];
		if ((true == role->getShadowFlag()) && (m_iRolePkID == role->getShadowOwner()))
		{
			role->runRoleAction(RoleAct_Death);
		}
	}
}

/*********************************************************************
** 功能：		死亡后回调
** 输入参数：	无
** 返回值： 	无
** 修改记录：	
*********************************************************************/
void ZouJi::deathEffectCallBack()
{
	if (true == m_bShadow)											/* 分身 */
	{
		if (RoleCamp_Red == m_stRoleInfo.camp)						/* 刷新角色人数 */
		{
			UserData::getInstance()->checkRedRolecount();
		}
		else
		{
			UserData::getInstance()->checkBlackRolecount(m_iSceneID);
		}
		UserData::getInstance()->removeRole(this);
		m_nAureoleEffect->removeFromParentAndCleanup(true);
		this->removeFromParentAndCleanup(true);
	}
	else
	{
		Role::deathEffectCallBack();
	}
}
/* protected: End */