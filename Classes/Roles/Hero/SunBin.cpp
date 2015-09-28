#include "SunBin.h"

USING_NS_CC;
using namespace cocostudio;

SunBin::SunBin(void)
{
}

SunBin::~SunBin(void)
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
void SunBin::loadArmature()
{
	m_stRoleInfo.arAnimate = Armature::create(m_strRoleName.c_str());
	if (NULL == m_stRoleInfo.arAnimate)
	{
		return;
	}

	this->addChild(m_stRoleInfo.arAnimate);

	/* 注册动画帧事件和动作回调函数 */
	m_stRoleInfo.arAnimate->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(SunBin::actionFrameEventCallFunc, this, std::placeholders::_1
		, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	m_stRoleInfo.arAnimate->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(SunBin::actionMovementCallFunc, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

/*********************************************************************
** 功能：		初始化角色技能属性
** 输入参数：	无
** 返回值：		无
** 修改记录：	
*********************************************************************/
void SunBin::initActInherent()
{
	Role::initActInherent();
			
	m_stActMode[RoleAct_SkillThree] = RoleActMode_Control;		/* 技能三 */
}

/*********************************************************************
** 功能：		初始化技能飞行道具
** 输入参数：	无
** 返回值：		无
** 修改记录：	
*********************************************************************/
void SunBin::initFlightPropInfo()
{
	m_stSunBinProp.strPath = getFlightPropPath() + "SunBin_S3Prop";
	m_stSunBinProp.ptOffset = Point(0, 70) * m_fResScale;
	m_stSunBinProp.iImgNum = 6;
}

/*********************************************************************
** 功能：		动作回调函数
** 输入参数：	
** 返回值： 	
** 修改记录：	
*********************************************************************/
void SunBin::actionMovementCallFunc(Armature *ar, MovementEventType type, const std::string& str)
{
	movement(str, type, 0.5f);
}

/*********************************************************************
** 功能：		帧事件
** 输入参数：	
** 返回值： 	无
** 修改记录：	
*********************************************************************/
void SunBin::actionFrameEventCallFunc(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
{
	frameEvent(evt);

	if ((evt == getFrameEventName(FrameEvent_Shot)) || (evt == getFrameEventName(FrameEvent_Shot_FD)))
	{
// 		if ((RoleAct_Attack == m_stRoleInfo.actInfo.act) || (RoleAct_Twice_Atk == m_stRoleInfo.actInfo.act) || 
// 			(RoleAct_Thrice_Atk == m_stRoleInfo.actInfo.act))
// 		{
// 		}

		if (RoleAct_SkillThree == m_stRoleInfo.actSign)
		{
			SkillThree();
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
bool SunBin::runActionAttack()
{
	bool bRet = Role::runActionAttack();
	if (true == bRet)
	{
		playEffectOgg("C109");
	}

	return bRet;
}

/*********************************************************************
** 功能：		普通攻击第二击
** 输入参数：	无
** 返回值：		bool:true:动作执行成功
** 修改记录：	
*********************************************************************/
bool SunBin::runActionTwiceAtk()
{
	bool bRet = Role::runActionTwiceAtk();
	if (true == bRet)
	{
		playEffectOgg("C109");
	}

	return bRet;
}

/*********************************************************************
** 功能：		普通攻击第三击
** 输入参数：	无
** 返回值：		bool:true:动作执行成功
** 修改记录：	
*********************************************************************/
bool SunBin::runActionThriceAtk()
{
	bool bRet = Role::runActionThriceAtk();
	if (true == bRet)
	{
		playEffectOgg("C109");
	}

	return bRet;
}

/*********************************************************************
** 功能：		执行技能一
** 输入参数：	无
** 返回值： 	无
** 修改记录：	
*********************************************************************/
bool SunBin::runActionSkillOne()
{
	bool bRet = Role::runActionSkillOne();
	if (true == bRet)
	{
		playEffectOgg("094HF");
	}

	return bRet;
}

/*********************************************************************
** 功能：		执行技能二
** 输入参数：	无
** 返回值： 	无
** 修改记录：	
*********************************************************************/
bool SunBin::runActionSkillTwo()
{
	bool bRet = Role::runActionSkillTwo();
	if (true == bRet)
	{
		playEffectOgg("037HF");
	}

	return bRet;
}

/*********************************************************************
** 功能：		执行技能三
** 输入参数：	无
** 返回值： 	无
** 修改记录：	
*********************************************************************/
bool SunBin::runActionSkillThree()
{
	bool bRet = Role::runActionSkillThree();
	if (true == bRet)
	{
		playEffectOgg("LX");
	}

	return bRet;
}

/*********************************************************************
** 功能：		执行技能四
** 输入参数：	无
** 返回值： 	无
** 修改记录：	
*********************************************************************/
bool SunBin::runActionSkillFour()
{
	bool bRet = Role::runActionSkillFour();
	if (true == bRet)
	{
		playEffectOgg("094HF");
	}

	return bRet;
}
/* 动作执行 End*/

void SunBin::SkillThree()
{
	FlightPropInfo info = {0};
	info.num = m_stSunBinProp.iImgNum;
	info.dur = 0.2f / m_stSunBinProp.iImgNum;
	memcpy(&(info.skillInfo), &m_stSkillInfo[RoleAct_SkillThree], sizeof(SkillInfo));

	auto sbProp = Skull::create(this, m_stSunBinProp.strPath, info);
	if (NULL != sbProp)
	{
		sbProp->setScale(m_stRoleSubInfo.side * m_fResScale);
		sbProp->setAnchorPoint(Point::ANCHOR_MIDDLE);
		sbProp->setPropPosition(Point(-m_stRoleSubInfo.side * m_stSunBinProp.ptOffset.x, m_stSunBinProp.ptOffset.y));
		this->getParent()->addChild(sbProp);
		sbProp->runPropCollisionDetective(0.35f, Point(-m_stSkillInfo[RoleAct_SkillThree].xAtkDis * m_stRoleSubInfo.side, 0));
	}
}
/* protected: End */