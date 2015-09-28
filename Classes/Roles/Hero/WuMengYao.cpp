#include "WuMengYao.h"

USING_NS_CC;
using namespace cocostudio;

WuMengYao::WuMengYao(void)
{
}

WuMengYao::~WuMengYao(void)
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
void WuMengYao::loadArmature()
{
	m_stRoleInfo.arAnimate = Armature::create(m_strRoleName.c_str());
	if (NULL == m_stRoleInfo.arAnimate)
	{
		return;
	}

	this->addChild(m_stRoleInfo.arAnimate);

	/* 注册动画帧事件和动作回调函数 */
	m_stRoleInfo.arAnimate->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(WuMengYao::actionFrameEventCallFunc, this, std::placeholders::_1
		, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	m_stRoleInfo.arAnimate->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(WuMengYao::actionMovementCallFunc, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

/*********************************************************************
** 功能：		初始化技能飞行道具
** 输入参数：	无
** 返回值：		无
** 修改记录：	
*********************************************************************/
void WuMengYao::initFlightPropInfo()
{
	m_stWuMengYaoProp[WuMengYao_Arrow].strPath = getFlightPropPath() + "WuMengYao_Arrow";
	m_stWuMengYaoProp[WuMengYao_Arrow].ptOffset = Point(120, 95) * m_fResScale;
	m_stWuMengYaoProp[WuMengYao_Arrow].iImgNum = 1;

	m_stWuMengYaoProp[WuMengYao_S3Prop].strPath = getFlightPropPath() + "WuMengYao_S3Prop";
	m_stWuMengYaoProp[WuMengYao_S3Prop].ptOffset = Point(0, 95) * m_fResScale;
	m_stWuMengYaoProp[WuMengYao_S3Prop].iImgNum = 1;
}

/*********************************************************************
** 功能：		设置天赋buff
** 输入参数：	无
** 返回值：		无
** 修改记录：	
*********************************************************************/
void WuMengYao::initTalentEffect()
{
	Role::initTalentEffect();

	if (true == isRoleLearnedTalent(RoleTalent_KuangBao))	/* 吴孟瑶：破甲 */
	{
		m_stRoleInfo.panel.pDefendL = 0.15f;
		m_stRoleInfo.panel.mDefendL = 0.15f;
	}
}

/*********************************************************************
** 功能：		动作回调函数
** 输入参数：	
** 返回值： 	
** 修改记录：	
*********************************************************************/
void WuMengYao::actionMovementCallFunc(Armature *ar, MovementEventType type, const std::string& str)
{
	movement(str, type, 0.5f);
}

/*********************************************************************
** 功能：		帧事件
** 输入参数：	
** 返回值： 	无
** 修改记录：	
*********************************************************************/
void WuMengYao::actionFrameEventCallFunc(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
{
	frameEvent(evt);

	bool bDown = false;
	if (evt == getFrameEventName(FrameEvent_Shot_FD))
	{
		bDown = true;
	}

	if ((evt == getFrameEventName(FrameEvent_Shot)) || (evt == getFrameEventName(FrameEvent_Shot_FD)))
	{
		if ((RoleAct_Attack == m_stRoleInfo.actSign) || (RoleAct_Twice_Atk == m_stRoleInfo.actSign) || 
			(RoleAct_Thrice_Atk == m_stRoleInfo.actSign))
		{
			comArrow(bDown);
		}
		if (RoleAct_SkillTwo == m_stRoleInfo.actSign)
		{
			skillTwo(true);			
		}
		else if (RoleAct_SkillThree == m_stRoleInfo.actSign)
		{
			skillThree(true);
		}
	}
	
	if (RoleAct_SkillThree == m_stRoleInfo.actSign)
	{
		if (RoleCreMode_Fighting == m_eRoleCreMode)
		{
			if (getFrameEventName(FrameEvent_Begin) == evt)
			{
				auto move = MoveBy::create(22.0f / 36.0f, Point(180, 0) * m_stRoleSubInfo.side);
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
bool WuMengYao::runActionAttack()
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
bool WuMengYao::runActionTwiceAtk()
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
bool WuMengYao::runActionThriceAtk()
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
bool WuMengYao::runActionSkillOne()
{
	bool bRet = Role::runActionSkillOne();
	if (true == bRet)
	{
		playEffectOgg("077B");
	}

	return bRet;
}

/*********************************************************************
** 功能：		执行技能二
** 输入参数：	无
** 返回值： 	无
** 修改记录：	
*********************************************************************/
bool WuMengYao::runActionSkillTwo()
{
	bool bRet = Role::runActionSkillTwo();
	if (true == bRet)
	{
		playEffectOgg("145S");
	}

	return bRet;
}

/*********************************************************************
** 功能：		执行技能三
** 输入参数：	无
** 返回值： 	无
** 修改记录：	
*********************************************************************/
bool WuMengYao::runActionSkillThree()
{
	bool bRet = Role::runActionSkillThree();
	if (true == bRet)
	{
		playEffectOgg("072SL");
	}

	return bRet;
}

/*********************************************************************
** 功能：		执行技能四
** 输入参数：	无
** 返回值： 	无
** 修改记录：	
*********************************************************************/
bool WuMengYao::runActionSkillFour()
{
	bool bRet = Role::runActionSkillFour();
	if (true == bRet)
	{
		playEffectOgg("");
	}

	return bRet;
}
/* 动作执行 End*/
/* protected: End */

void WuMengYao::comArrow(bool fd)
{
	FlightPropInfo info = {0};
	info.num = m_stWuMengYaoProp[WuMengYao_Arrow].iImgNum;
	memcpy(&(info.skillInfo), &m_stSkillInfo[m_stRoleInfo.actSign], sizeof(SkillInfo));

	auto wmyArrow = CommonProp::create(this, m_stWuMengYaoProp[WuMengYao_Arrow].strPath, info);
	if (NULL != wmyArrow)
	{
		wmyArrow->setScaleX(m_stRoleSubInfo.side * m_fResScale);
		wmyArrow->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
		wmyArrow->setPropPosition(Point(-m_stRoleSubInfo.side * m_stWuMengYaoProp[WuMengYao_Arrow].ptOffset.x, m_stWuMengYaoProp[WuMengYao_Arrow].ptOffset.y));
		wmyArrow->setPropFlag(fd);
		this->getParent()->addChild(wmyArrow);
		wmyArrow->runPropCollisionDetective(0.1f, Point(-m_stSkillInfo[m_stRoleInfo.actSign].xAtkDis * m_stRoleSubInfo.side, 0));
	}
}

void WuMengYao::skillTwo(bool fd)
{
	FlightPropInfo info = {0};
	info.num = m_stWuMengYaoProp[WuMengYao_Arrow].iImgNum;
	memcpy(&(info.skillInfo), &m_stSkillInfo[RoleAct_SkillTwo], sizeof(SkillInfo));

	auto wmyProp = CommonProp::create(this, m_stWuMengYaoProp[WuMengYao_Arrow].strPath, info);
	if (NULL != wmyProp)
	{
		wmyProp->setScaleX(m_stRoleSubInfo.side * m_fResScale);
		wmyProp->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
		wmyProp->setPropPosition(Point(-m_stRoleSubInfo.side * m_stWuMengYaoProp[WuMengYao_Arrow].ptOffset.x, m_stWuMengYaoProp[WuMengYao_Arrow].ptOffset.y));  
		wmyProp->setPropFlag(true);
		this->getParent()->addChild(wmyProp);
		wmyProp->runPropCollisionDetective(0.2f, Point(-m_stSkillInfo[RoleAct_SkillTwo].xAtkDis * m_stRoleSubInfo.side, 0));
	}
}

void WuMengYao::skillThree(bool fd)
{
	FlightPropInfo info = {0};
	info.num = m_stWuMengYaoProp[WuMengYao_S3Prop].iImgNum;
	memcpy(&(info.skillInfo), &m_stSkillInfo[RoleAct_SkillThree], sizeof(SkillInfo));

	auto wmyProp = CommonProp::create(this, m_stWuMengYaoProp[WuMengYao_S3Prop].strPath, info);
	if (NULL != wmyProp)
	{
		wmyProp->setScale(m_stRoleSubInfo.side * m_fResScale);
		wmyProp->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
		wmyProp->setPropPosition(Point(m_stRoleSubInfo.side * m_stWuMengYaoProp[WuMengYao_S3Prop].ptOffset.x, m_stWuMengYaoProp[WuMengYao_S3Prop].ptOffset.y));  
		wmyProp->setPropFlag(fd);
		this->getParent()->addChild(wmyProp);
		wmyProp->runPropCollisionDetective(0.1f, Point(-m_stSkillInfo[RoleAct_SkillThree].xAtkDis * m_stRoleSubInfo.side, 0));
	}
}