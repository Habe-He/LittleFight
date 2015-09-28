#include "ChuZi.h"
#include "Roles/SkillProps/FallenProp.h"

USING_NS_CC;
using namespace cocostudio;

const Point ptCZ_S1FirstArrow = Point(70, 150);	/* 技能s1，第一箭*/
const int iCZ_S1MaxNum = 9;						/* 技能s1，落箭数量 */
const Size szCZ_S1Region = Size(130, 25);		/* 技能s1，落箭范围 */
const float fCZ_S1Delay = 0.69f;				/* 技能s1，落箭延时 */
const float fCZ_ArrowLength = 107.0f;


ChuZi::ChuZi(void)
{
}

ChuZi::~ChuZi(void)
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
void ChuZi::loadArmature()
{
	m_stRoleInfo.arAnimate = Armature::create(m_strRoleName.c_str());
	if (NULL == m_stRoleInfo.arAnimate)
	{
		return;
	}

	this->addChild(m_stRoleInfo.arAnimate);

	/* 注册动画帧事件和动作回调函数 */
	m_stRoleInfo.arAnimate->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(ChuZi::actionFrameEventCallFunc, this, std::placeholders::_1
		, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	m_stRoleInfo.arAnimate->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(ChuZi::actionMovementCallFunc, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

/*********************************************************************
** 功能：		初始化技能飞行道具
** 输入参数：	无
** 返回值：		无
** 修改记录：	
*********************************************************************/
void ChuZi::initFlightPropInfo()
{
	m_stChuZiShot[ChuZi_Normal].strPath = getFlightPropPath() + "ChuZi_Normal";
	m_stChuZiShot[ChuZi_Normal].ptOffset = Point(70, 80) * m_fResScale;
	m_stChuZiShot[ChuZi_Normal].iImgNum = 1;

	m_stChuZiShot[ChuZi_S2Prop].strPath = getFlightPropPath() + "ChuZi_S2Prop";
	m_stChuZiShot[ChuZi_S2Prop].ptOffset = Point(75, 80) * m_fResScale;
	m_stChuZiShot[ChuZi_S2Prop].iImgNum = 1;
}

/*********************************************************************
** 功能：		动作回调函数
** 输入参数：	
** 返回值： 	
** 修改记录：	
*********************************************************************/
void ChuZi::actionMovementCallFunc(Armature *ar, MovementEventType type, const std::string& str)
{
	movement(str, type, 0.5f);
}

/*********************************************************************
** 功能：		帧事件
** 输入参数：	
** 返回值： 	无
** 修改记录：	
*********************************************************************/
void ChuZi::actionFrameEventCallFunc(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
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
			ChuZiShot(ChuZi_Normal, bDown);
		}

		if (RoleAct_SkillOne == m_stRoleInfo.actSign)
		{
			ChuziS1();
		}

		if (RoleAct_SkillTwo == m_stRoleInfo.actSign)
		{
			ChuZiShot(ChuZi_S2Prop, bDown);
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
bool ChuZi::runActionAttack()
{
	bool bRet = Role::runActionAttack();
	if (true == bRet)
	{
		playEffectOgg("C071");
	}

	return bRet;
}

/*********************************************************************
** 功能：		普通攻击第二击
** 输入参数：	无
** 返回值：		bool:true:动作执行成功
** 修改记录：	
*********************************************************************/
bool ChuZi::runActionTwiceAtk()
{
	bool bRet = Role::runActionTwiceAtk();
	if (true == bRet)
	{
		playEffectOgg("C071");
	}

	return bRet;
}

/*********************************************************************
** 功能：		普通攻击第三击
** 输入参数：	无
** 返回值：		bool:true:动作执行成功
** 修改记录：	
*********************************************************************/
bool ChuZi::runActionThriceAtk()
{
	bool bRet = Role::runActionThriceAtk();
	if (true == bRet)
	{
		playEffectOgg("C071");
	}

	return bRet;
}

/*********************************************************************
** 功能：		执行技能一
** 输入参数：	无
** 返回值： 	无
** 修改记录：	
*********************************************************************/
bool ChuZi::runActionSkillOne()
{
	bool bRet = Role::runActionSkillOne();
	if (true == bRet)
	{
		playEffectOgg("157SJ");
	}

	return bRet;
}

/*********************************************************************
** 功能：		执行技能二
** 输入参数：	无
** 返回值： 	无
** 修改记录：	
*********************************************************************/
bool ChuZi::runActionSkillTwo()
{
	bool bRet = Role::runActionSkillTwo();
	if (true == bRet)
	{
		playEffectOgg("145ZH");
	}

	return bRet;
}
/* 动作执行 End*/

/*********************************************************************
** 功能：		射箭
** 输入参数：	CZArrow arrow: 箭类型
**				bool bDown:true:倒地;false:不倒地
** 返回值：		
** 修改记录：	
*********************************************************************/
void ChuZi::ChuZiShot(ChuZiArrow arrow, bool bDown)
{
 	FlightPropInfo info = {0};
	info.num = m_stChuZiShot[arrow].iImgNum;
 	memcpy(&(info.skillInfo), &m_stSkillInfo[m_stRoleInfo.actSign], sizeof(SkillInfo));
 
 	auto czArrow = CommonProp::create(this, m_stChuZiShot[arrow].strPath, info);
 
 	if (NULL != czArrow)
 	{
 		czArrow->setScaleX(m_stRoleSubInfo.side * m_fResScale);
 		czArrow->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
 
 		czArrow->setPropPosition(Point(-m_stChuZiShot[arrow].ptOffset.x * m_stRoleSubInfo.side, m_stChuZiShot[arrow].ptOffset.y));
 		czArrow->setPropFlag(bDown);
 
 		this->getParent()->addChild(czArrow);
 		czArrow->runPropCollisionDetective(0.3f, Point(-m_stSkillInfo[m_stRoleInfo.actSign].xAtkDis * m_stRoleSubInfo.side, 0));
 	}
}

/*********************************************************************
** 功能：		触子技能2射向空中的一箭
** 输入参数：	无
** 返回值：		无
** 修改记录：	
*********************************************************************/
void ChuZi::ChuziS1()
{
	auto czArrow = Sprite::create(m_stChuZiShot[ChuZi_Normal].strPath + "0.png");
	if (NULL != czArrow)
	{
		czArrow->setScaleX(m_stRoleSubInfo.side * m_fResScale);
		czArrow->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
		czArrow->setRotation(45.0f * m_stRoleSubInfo.side);
		czArrow->setPosition(Point(getPositionX() - ptCZ_S1FirstArrow.x * m_stRoleSubInfo.side * m_fResScale, 
			getPositionY() + ptCZ_S1FirstArrow.y * m_fResScale));
		this->getParent()->addChild(czArrow);

		auto offset = (50 + szCZ_S1Region.width) * m_fResScale;
		auto move = MoveBy::create(0.22f, Point(0 - offset * m_stRoleSubInfo.side, offset));
		auto prop = CallFuncN::create(CC_CALLBACK_1(ChuZi::s1CallBack1, this));
		auto seq = Sequence::create(move, prop, NULL);
		czArrow->runAction(seq);
	}
}

/*********************************************************************
** 功能：		生成箭雨
** 输入参数：	
** 返回值：		
** 修改记录：	
*********************************************************************/
void ChuZi::s1CallBack1(Node *who)
{
	auto ptWho = who->getPosition() - getPosition();				/* 箭相对武将位置 */
	who->removeFromParentAndCleanup(true);

	m_mapS1.clear();
	auto ptLoc = Point::ZERO;
	auto angle = 0.0f;

	/* 矩形距离角色50，宽130，高25 */
	auto rc = Rect(-115 * m_stRoleSubInfo.side - 65, -szCZ_S1Region.height / 2, szCZ_S1Region.width, szCZ_S1Region.height);
	for (auto index = 0;index < iCZ_S1MaxNum;index ++)
	{
		ptLoc.x = ToolFunc::calcRandom(rc.getMinX(), rc.getMaxX());
		ptLoc.y = ToolFunc::calcRandom(rc.getMinY(), rc.getMaxY());

		FlightPropInfo info = {0};
		info.num = m_stChuZiShot[ChuZi_Normal].iImgNum;
		memcpy(&(info.skillInfo), &m_stSkillInfo[m_stRoleInfo.actSign], sizeof(SkillInfo));

		auto czArrow = FallenProp::create(this, m_stChuZiShot[ChuZi_Normal].strPath, info);
		if (NULL != czArrow)
		{
			czArrow->setPropYaxis(this->getPositionY());
			czArrow->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
			czArrow->setScaleX(-m_fResScale);
			czArrow->setPropPosition(ptWho);
			czArrow->setRotation(-ToolFunc::getAngle(ptLoc, ptWho));
			czArrow->setVisible(false);
			czArrow->setPropFlag(true);								/* 命中则倒地 */
			this->getParent()->addChild(czArrow);

			m_mapS1.insert(pair<Sprite*, Point>(czArrow, ptLoc - ptWho));	
			auto delay = DelayTime::create(ToolFunc::calcRandom(fCZ_S1Delay * 100, fCZ_S1Delay * 100 * iCZ_S1MaxNum / 2) * 0.002f);
			auto drop = CallFuncN::create(CC_CALLBACK_1(ChuZi::s1CallBack2, this));
			auto seq = Sequence::create(delay, drop, NULL);
			czArrow->runAction(seq);		
		}
	}
}

void ChuZi::s1CallBack2(Node *who)
{
	auto arrow = (CommonProp *)who;
	arrow->setVisible(true);
	arrow->runPropCollisionDetective(0.3f, m_mapS1.at(arrow));
}
/* protected: End */