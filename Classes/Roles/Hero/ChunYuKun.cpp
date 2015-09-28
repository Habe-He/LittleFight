#include "ChunYuKun.h"

USING_NS_CC;
using namespace cocostudio;

ChunYuKun::ChunYuKun(void)
{
}

ChunYuKun::~ChunYuKun(void)
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
void ChunYuKun::loadArmature()
{
	m_stRoleInfo.arAnimate = Armature::create(m_strRoleName.c_str());
	if (NULL == m_stRoleInfo.arAnimate)
	{
		return;
	}

	this->addChild(m_stRoleInfo.arAnimate);

	/* 注册动画帧事件和动作回调函数 */
	m_stRoleInfo.arAnimate->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(ChunYuKun::actionFrameEventCallFunc, this, std::placeholders::_1
		, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	m_stRoleInfo.arAnimate->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(ChunYuKun::actionMovementCallFunc, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

/*********************************************************************
** 功能：		初始化技能飞行道具
** 输入参数：	无
** 返回值：		无
** 修改记录：	
*********************************************************************/
void ChunYuKun::initFlightPropInfo()
{
	m_stChunYuKunProp.strPath = getFlightPropPath() + "ChunYuKun_S2Prop";
	m_stChunYuKunProp.ptOffset = Point(100, 0) * m_fResScale;
	m_stChunYuKunProp.iImgNum = 1;
}

/*********************************************************************
** 功能：		动作回调函数
** 输入参数：	
** 返回值： 	
** 修改记录：	
*********************************************************************/
void ChunYuKun::actionMovementCallFunc(Armature *ar, MovementEventType type, const std::string& str)
{
	movement(str, type, 0.5f);
}

/*********************************************************************
** 功能：		帧事件
** 输入参数：	
** 返回值： 	无
** 修改记录：	
*********************************************************************/
void ChunYuKun::actionFrameEventCallFunc(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
{
	frameEvent(evt);

	if (getFrameEventName(FrameEvent_Shot_FD) == evt)
	{
		FlightPropInfo info = {0};
		info.num = m_stChunYuKunProp.iImgNum;
		memcpy(&(info.skillInfo), &m_stSkillInfo[m_stRoleInfo.actSign], sizeof(SkillInfo));

		auto cykRenFont = CommonProp::create(this, m_stChunYuKunProp.strPath, info);
		if (NULL != cykRenFont)
		{
			cykRenFont->setScaleX(m_stRoleSubInfo.side * m_fResScale);
			cykRenFont->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
			cykRenFont->setPropPosition(Point(-m_stChunYuKunProp.ptOffset.x * m_stRoleSubInfo.side, m_stChunYuKunProp.ptOffset.y));
			cykRenFont->setPropFlag(true);
			this->getParent()->addChild(cykRenFont);
			cykRenFont->runPropCollisionDetective(0.7f, Point(-m_stSkillInfo[m_stRoleInfo.actSign].xAtkDis * m_stRoleSubInfo.side, 0));
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
bool ChunYuKun::runActionAttack()
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
bool ChunYuKun::runActionTwiceAtk()
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
bool ChunYuKun::runActionThriceAtk()
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
bool ChunYuKun::runActionSkillOne()
{
	bool bRet = Role::runActionSkillOne();
	if (true == bRet)
	{
		playEffectOgg("108DD");
	}

	return bRet;
}

/*********************************************************************
** 功能：		执行技能二
** 输入参数：	无
** 返回值： 	无
** 修改记录：	
*********************************************************************/
bool ChunYuKun::runActionSkillTwo()
{
	bool bRet = Role::runActionSkillTwo();
	if (true == bRet)
	{
		playEffectOgg("LX");
	}

	return bRet;
}
/* 动作执行 End*/
/* protected: End */

void ChunYuKun::skillTwoCallBack(Node* node)
{
	node->removeFromParentAndCleanup(true);
}