#include "PangJuan.h"
#include "Roles/SkillProps/Gamut.h"

USING_NS_CC;
using namespace cocostudio;

PangJuan::PangJuan(void)
{
}

PangJuan::~PangJuan(void)
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
void PangJuan::loadArmature()
{
	m_stRoleInfo.arAnimate = Armature::create(m_strRoleName.c_str());
	if (NULL == m_stRoleInfo.arAnimate)
	{
		return;
	}

	this->addChild(m_stRoleInfo.arAnimate);

	/* 注册动画帧事件和动作回调函数 */
	m_stRoleInfo.arAnimate->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(PangJuan::actionFrameEventCallFunc, this, std::placeholders::_1
		, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	m_stRoleInfo.arAnimate->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(PangJuan::actionMovementCallFunc, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

/*********************************************************************
** 功能：		初始化技能飞行道具
** 输入参数：	无
** 返回值：		无
** 修改记录：	
*********************************************************************/
void PangJuan::initFlightPropInfo()
{
	m_stPangJuanProp[PangJuan_S1Prop].strPath = getFlightPropPath() + "PangJuan_S1Prop";
	m_stPangJuanProp[PangJuan_S1Prop].ptOffset = Point(40, 50) * m_fResScale;
	m_stPangJuanProp[PangJuan_S1Prop].iImgNum = 1;

	auto rc = Director::getInstance()->getOpenGLView()->getVisibleRect();
	m_stPangJuanProp[PangJuan_S4Prop].strPath = getFlightPropPath() + "PangJuan_S4Prop";
	m_stPangJuanProp[PangJuan_S4Prop].ptOffset = Point(rc.size.width / 2, rc.size.height / 2);
	m_stPangJuanProp[PangJuan_S4Prop].iImgNum = 12;
}

/* 动作执行 Begin */
/*********************************************************************
** 功能：		动作回调函数
** 输入参数：	
** 返回值： 	
** 修改记录：	
*********************************************************************/
void PangJuan::actionMovementCallFunc(Armature *ar, MovementEventType type, const std::string& str)
{
	movement(str, type, 0.5f);
}

/*********************************************************************
** 功能：		帧事件
** 输入参数：	
** 返回值： 	无
** 修改记录：	
*********************************************************************/
void PangJuan::actionFrameEventCallFunc(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
{
	frameEvent(evt);

	bool bDown = false;
	if (evt == getFrameEventName(FrameEvent_Shot_FD))
	{
		bDown = true;
	}

	if ((evt == getFrameEventName(FrameEvent_Shot)) || (evt == getFrameEventName(FrameEvent_Shot_FD)))
	{
		if (RoleAct_SkillOne == m_stRoleInfo.actSign)
		{
			skillOne(m_stRoleInfo.panel.atk, false);
		}
		else if (RoleAct_SkillFour == m_stRoleInfo.actSign)
		{
			skillFour();
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
bool PangJuan::runActionAttack()
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
bool PangJuan::runActionTwiceAtk()
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
bool PangJuan::runActionThriceAtk()
{
	bool bRet = Role::runActionThriceAtk();
	if (true == bRet)
	{
		playEffectOgg("C1");
	}

	return bRet;
}

/*********************************************************************
** 功能：		执行技能一
** 输入参数：	无
** 返回值： 	无
** 修改记录：	
*********************************************************************/
bool PangJuan::runActionSkillOne()
{
	bool bRet = Role::runActionSkillOne();
	if (true == bRet)
	{
		playEffectOgg("C2");
	}

	return bRet;
}

/*********************************************************************
** 功能：		执行技能二
** 输入参数：	无
** 返回值： 	无
** 修改记录：	
*********************************************************************/
bool PangJuan::runActionSkillTwo()
{
	bool bRet = Role::runActionSkillTwo();
	if (true == bRet)
	{
		playEffectOgg("055DD");
	}

	return bRet;
}

/*********************************************************************
** 功能：		执行技能三
** 输入参数：	无
** 返回值： 	无
** 修改记录：	
*********************************************************************/
bool PangJuan::runActionSkillThree()
{
	bool bRet = Role::runActionSkillThree();
	if (true == bRet)
	{
		playEffectOgg("064");
	}

	return bRet;
}

/*********************************************************************
** 功能：		执行技能四
** 输入参数：	无
** 返回值： 	无
** 修改记录：	
*********************************************************************/
bool PangJuan::runActionSkillFour()
{
	bool bRet = Role::runActionSkillFour();
	if (true == bRet)
	{
		playEffectOgg("061ZH");
	}

	return bRet;
}
/* 动作执行 End*/

/* protected: End */
void PangJuan::skillOne(int atk, bool bDown)
{
	FlightPropInfo info = {0};
	info.num = m_stPangJuanProp[PangJuan_S1Prop].iImgNum;
	memcpy(&(info.skillInfo), &m_stSkillInfo[m_stRoleInfo.actSign], sizeof(SkillInfo));
	auto PangJuanProp = CommonProp::create(this, m_stPangJuanProp[PangJuan_S1Prop].strPath, info);

	if (NULL != PangJuanProp)
	{
		PangJuanProp->setScaleX(m_stRoleSubInfo.side);
		PangJuanProp->setScaleY(m_fResScale);
		PangJuanProp->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
		PangJuanProp->setPropPosition(Point(-m_stPangJuanProp[PangJuan_S1Prop].ptOffset.x * m_stRoleSubInfo.side, m_stPangJuanProp[PangJuan_S1Prop].ptOffset.y));
		PangJuanProp->setPropFlag(bDown);
		this->getParent()->addChild(PangJuanProp);
		PangJuanProp->runPropCollisionDetective(0.2f, Point(-m_stSkillInfo[m_stRoleInfo.actSign].xAtkDis * m_stRoleSubInfo.side, 0));
	}
}

void PangJuan::skillFour()
{
	FlightPropInfo info = {0};
	info.num = m_stPangJuanProp[PangJuan_S4Prop].iImgNum;
	info.dur = 0.5f / info.num;
	memcpy(&(info.skillInfo), &m_stSkillInfo[RoleAct_SkillFour], sizeof(SkillInfo));

	auto sprite = Gamut::create(this, m_stPangJuanProp[PangJuan_S4Prop].strPath, info);
	sprite->setAnchorPoint(Point::ANCHOR_MIDDLE);
	sprite->setPosition(m_stPangJuanProp[PangJuan_S4Prop].ptOffset + Point(m_iSceneID * SceneWidth, 0));  
	this->getParent()->addChild(sprite); 
	sprite->runPropCollisionDetective();
}