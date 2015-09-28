#include "QiMaoBian.h"

USING_NS_CC;
using namespace cocostudio;

QiMaoBian::QiMaoBian(void)
{
}

QiMaoBian::~QiMaoBian(void)
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
void QiMaoBian::loadArmature()
{
	m_stRoleInfo.arAnimate = Armature::create(m_strRoleName.c_str());
	if (NULL == m_stRoleInfo.arAnimate)
	{
		return;
	}

	this->addChild(m_stRoleInfo.arAnimate);

	/* 注册动画帧事件和动作回调函数 */
	m_stRoleInfo.arAnimate->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(QiMaoBian::actionFrameEventCallFunc, this, std::placeholders::_1
		, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	m_stRoleInfo.arAnimate->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(QiMaoBian::actionMovementCallFunc, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

/*********************************************************************
** 功能：		初始化技能飞行道具
** 输入参数：	无
** 返回值：		无
** 修改记录：	
*********************************************************************/
void QiMaoBian::initFlightPropInfo()
{
	m_stQiMaoBianProp.strPath = getFlightPropPath() + "QiMaoBian_S2Prop";
	m_stQiMaoBianProp.ptOffset = Point(0, 70) * m_fResScale;
	m_stQiMaoBianProp.iImgNum = 7;
}

/*********************************************************************
** 功能：		动作回调函数
** 输入参数：	
** 返回值： 	
** 修改记录：	
*********************************************************************/
void QiMaoBian::actionMovementCallFunc(Armature *ar, MovementEventType type, const std::string& str)
{
	movement(str, type, 0.5f);
}

/*********************************************************************
** 功能：		帧事件
** 输入参数：	
** 返回值： 	无
** 修改记录：	
*********************************************************************/
void QiMaoBian::actionFrameEventCallFunc(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
{
	frameEvent(evt);

	if ((evt == getFrameEventName(FrameEvent_Shot)) || (evt == getFrameEventName(FrameEvent_Shot_FD)))
	{
// 		if ((RoleAct_Attack == m_stRoleInfo.actInfo.act) || (RoleAct_Twice_Atk == m_stRoleInfo.actInfo.act) || 
// 			(RoleAct_Thrice_Atk == m_stRoleInfo.actInfo.act))
// 		{
// 			NormalAttack(bDown);
// 		}

		if (RoleAct_SkillTwo == m_stRoleInfo.actSign)
		{
			SkillTwo();
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
bool QiMaoBian::runActionAttack()
{
	bool bRet = Role::runActionAttack();
	if (true == bRet)
	{
		playEffectOgg("C97");
	}

	return bRet;
}

/*********************************************************************
** 功能：		普通攻击第二击
** 输入参数：	无
** 返回值：		bool:true:动作执行成功
** 修改记录：	
*********************************************************************/
bool QiMaoBian::runActionTwiceAtk()
{
	bool bRet = Role::runActionTwiceAtk();
	if (true == bRet)
	{
		playEffectOgg("C97");
	}

	return bRet;
}

/*********************************************************************
** 功能：		普通攻击第三击
** 输入参数：	无
** 返回值：		bool:true:动作执行成功
** 修改记录：	
*********************************************************************/
bool QiMaoBian::runActionThriceAtk()
{
	bool bRet = Role::runActionThriceAtk();
	if (true == bRet)
	{
		playEffectOgg("C97");
	}

	return bRet;
}

/*********************************************************************
** 功能：		执行技能一
** 输入参数：	无
** 返回值： 	无
** 修改记录：	
*********************************************************************/
bool QiMaoBian::runActionSkillOne()
{
	bool bRet = Role::runActionSkillOne();
	if (true == bRet)
	{
		playEffectOgg("132JN");
	}

	return bRet;
}

/*********************************************************************
** 功能：		执行技能二
** 输入参数：	无
** 返回值： 	无
** 修改记录：	
*********************************************************************/
bool QiMaoBian::runActionSkillTwo()
{
	bool bRet = Role::runActionSkillTwo();
	if (true == bRet)
	{
		playEffectOgg("LX");
	}

	return bRet;
}
/* 动作执行 End*/

void QiMaoBian::SkillTwo()
{
	FlightPropInfo info = {0};
	info.num = m_stQiMaoBianProp.iImgNum;
	info.dur = 0.2f / m_stQiMaoBianProp.iImgNum;
	memcpy(&(info.skillInfo), &m_stSkillInfo[RoleAct_SkillTwo], sizeof(SkillInfo));

	auto syProp = CommonProp::create(this, m_stQiMaoBianProp.strPath, info);

	if (NULL != syProp)
	{
		syProp->setScale(m_stRoleSubInfo.side * m_fResScale);
		syProp->setAnchorPoint(Point::ANCHOR_MIDDLE);
		syProp->setPropPosition(Point(-m_stRoleSubInfo.side * m_stQiMaoBianProp.ptOffset.x, m_stQiMaoBianProp.ptOffset.y));
		this->getParent()->addChild(syProp);
		syProp->runPropCollisionDetective(0.35f, Point(-m_stSkillInfo[RoleAct_SkillTwo].xAtkDis * m_stRoleSubInfo.side, 0));
	}
}
/* protected: End */