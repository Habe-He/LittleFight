#include "JiangYi.h"

USING_NS_CC;
using namespace cocostudio;

JiangYi::JiangYi(void)
{
}

JiangYi::~JiangYi(void)
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
void JiangYi::loadArmature()
{
	m_stRoleInfo.arAnimate = Armature::create(m_strRoleName.c_str());
	if (NULL == m_stRoleInfo.arAnimate)
	{
		return;
	}

	this->addChild(m_stRoleInfo.arAnimate);

	/* 注册动画帧事件和动作回调函数 */
	m_stRoleInfo.arAnimate->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(JiangYi::actionFrameEventCallFunc, this, std::placeholders::_1
		, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	m_stRoleInfo.arAnimate->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(JiangYi::actionMovementCallFunc, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

/*********************************************************************
** 功能：		初始化技能飞行道具
** 输入参数：	无
** 返回值：		无
** 修改记录：	
*********************************************************************/
void JiangYi::initFlightPropInfo()
{
	m_stJiangYiProp[JiangYi_Magic].strPath = getFlightPropPath() + "JiangYi_Magic";
	m_stJiangYiProp[JiangYi_Magic].ptOffset = Point(120, 85) * m_fResScale;
	m_stJiangYiProp[JiangYi_Magic].iImgNum = 1;

	m_stJiangYiProp[JiangYi_S3Prop].strPath = getFlightPropPath() + "JiangYi_S3Prop";
	m_stJiangYiProp[JiangYi_S3Prop].ptOffset = Point(130, 70) * m_fResScale;
	m_stJiangYiProp[JiangYi_S3Prop].iImgNum = 6;

	m_stJiangYiProp[JiangYi_S4Prop].strPath = getFlightPropPath() + "JiangYi_S4Prop";
	m_stJiangYiProp[JiangYi_S4Prop].ptOffset = Point(130, 0) * m_fResScale;
	m_stJiangYiProp[JiangYi_S4Prop].iImgNum = 6;
}

/*********************************************************************
** 功能：		动作回调函数
** 输入参数：	
** 返回值： 	
** 修改记录：	
*********************************************************************/
void JiangYi::actionMovementCallFunc(Armature *ar, MovementEventType type, const std::string& str)
{
	movement(str, type, 0.5f);
}

/*********************************************************************
** 功能：		帧事件
** 输入参数：	
** 返回值： 	无
** 修改记录：	
*********************************************************************/
void JiangYi::actionFrameEventCallFunc(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
{
	frameEvent(evt);

	bool bDown = false;
	if (evt == getFrameEventName(FrameEvent_Shot_FD))
	{
		bDown = true;
	}

	if ((evt == getFrameEventName(FrameEvent_Shot)) || (evt == getFrameEventName(FrameEvent_Shot_FD)))
	{
		if (RoleAct_SkillTwo == m_stRoleInfo.actSign)
		{
			skillTwo(bDown);
		}
		else if (RoleAct_SkillThree == m_stRoleInfo.actSign)
		{
			skillThree();
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
bool JiangYi::runActionAttack()
{
	bool bRet = Role::runActionAttack();
	if (true == bRet)
	{
		playEffectOgg("C147");
	}

	return bRet;
}

/*********************************************************************
** 功能：		普通攻击第二击
** 输入参数：	无
** 返回值：		bool:true:动作执行成功
** 修改记录：	
*********************************************************************/
bool JiangYi::runActionTwiceAtk()
{
	bool bRet = Role::runActionTwiceAtk();
	if (true == bRet)
	{
		playEffectOgg("C147");
	}

	return bRet;
}

/*********************************************************************
** 功能：		普通攻击第三击
** 输入参数：	无
** 返回值：		bool:true:动作执行成功
** 修改记录：	
*********************************************************************/
bool JiangYi::runActionThriceAtk()
{
	bool bRet = Role::runActionThriceAtk();
	if (true == bRet)
	{
		playEffectOgg("C147");
	}

	return bRet;
}

/*********************************************************************
** 功能：		执行技能一
** 输入参数：	无
** 返回值： 	无
** 修改记录：	
*********************************************************************/
bool JiangYi::runActionSkillOne()
{
	bool bRet = Role::runActionSkillOne();
	if (true == bRet)
	{
		playEffectOgg("077JN");
	}

	return bRet;
}

/*********************************************************************
** 功能：		执行技能二
** 输入参数：	无
** 返回值： 	无
** 修改记录：	
*********************************************************************/
bool JiangYi::runActionSkillTwo()
{
	bool bRet = Role::runActionSkillTwo();
	if (true == bRet)
	{
		playEffectOgg("035DC");
	}

	return bRet;
}

/*********************************************************************
** 功能：		执行技能三
** 输入参数：	无
** 返回值： 	无
** 修改记录：	
*********************************************************************/
bool JiangYi::runActionSkillThree()
{
	bool bRet = Role::runActionSkillThree();
	if (true == bRet)
	{
		playEffectOgg("020DS");
	}

	return bRet;
}

/*********************************************************************
** 功能：		执行技能四
** 输入参数：	无
** 返回值： 	无
** 修改记录：	
*********************************************************************/
bool JiangYi::runActionSkillFour()
{
	bool bRet = Role::runActionSkillFour();
	if (true == bRet)
	{
		playEffectOgg("164ZH");
	}

	return bRet;
}
/* 动作执行 End*/
/* protected: End */

void JiangYi::skillTwo(bool bDown)
{
	FlightPropInfo info = {0};
	info.num = m_stJiangYiProp[JiangYi_Magic].iImgNum;
	memcpy(&(info.skillInfo), &m_stSkillInfo[RoleAct_SkillTwo], sizeof(SkillInfo));

	auto jiangYiProp = CommonProp::create(this, m_stJiangYiProp[JiangYi_Magic].strPath, info);

	if (NULL != jiangYiProp)
	{
		jiangYiProp->setScaleX(m_stRoleSubInfo.side * m_fResScale);
		jiangYiProp->setScaleY(m_fResScale);
		jiangYiProp->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);

		jiangYiProp->setPropPosition(Point(-m_stJiangYiProp[JiangYi_Magic].ptOffset.x * m_stRoleSubInfo.side, m_stJiangYiProp[JiangYi_Magic].ptOffset.y));
		jiangYiProp->setPropFlag(bDown);

		this->getParent()->addChild(jiangYiProp);
		jiangYiProp->runPropCollisionDetective(0.25f, Point(-m_stSkillInfo[RoleAct_SkillTwo].xAtkDis * m_stRoleSubInfo.side, 0));
	}
}

void JiangYi::skillThree()
{
	FlightPropInfo info = {0};
	info.num = m_stJiangYiProp[JiangYi_S3Prop].iImgNum;
	info.dur = 0.25f / m_stJiangYiProp[JiangYi_S3Prop].iImgNum;
	memcpy(&(info.skillInfo), &m_stSkillInfo[RoleAct_SkillThree], sizeof(SkillInfo));

	auto sprite = CommonProp::create(this, m_stJiangYiProp[JiangYi_S3Prop].strPath, info);
 
	sprite->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
	sprite->setScaleX(m_stRoleSubInfo.side * m_fResScale);
	sprite->setScaleY(m_fResScale);
	sprite->setPropFlag(true, 0.2f);
	sprite->setPropPosition(Point(-m_stJiangYiProp[JiangYi_S3Prop].ptOffset.x * m_stRoleSubInfo.side, m_stJiangYiProp[JiangYi_S3Prop].ptOffset.y));
	this->getParent()->addChild(sprite);  

	sprite->runPropCollisionDetective(0.25f, Point(-m_stSkillInfo[RoleAct_SkillThree].xAtkDis * m_stRoleSubInfo.side, 0));
}

void JiangYi::skillFour()
{
	FlightPropInfo info = {0};
	info.num = m_stJiangYiProp[JiangYi_S4Prop].iImgNum;
	info.dur = 0.5f / info.num;
	memcpy(&(info.skillInfo), &m_stSkillInfo[RoleAct_SkillFour], sizeof(SkillInfo));
	auto sprite = CommonProp::create(this, m_stJiangYiProp[JiangYi_S4Prop].strPath, info);

	sprite->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	sprite->setScale(m_fResScale);
	sprite->setPropFlag(true, 0.2f);
	sprite->setPropPosition(Point(-m_stJiangYiProp[JiangYi_S4Prop].ptOffset.x * m_stRoleSubInfo.side, m_stJiangYiProp[JiangYi_S4Prop].ptOffset.y));
	this->getParent()->addChild(sprite);  

	sprite->runPropCollisionDetective(0.35f, Point(-m_stSkillInfo[RoleAct_SkillFour].xAtkDis * m_stRoleSubInfo.side, 0));
}