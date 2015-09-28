#include "TianDan.h"
#include "Roles/SkillProps/CommonProp.h"

USING_NS_CC;
using namespace cocostudio;

const float fFireDuration = 15.0f;		/* 火焰持续时间 */

TianDan::TianDan(void)
{
}

TianDan::~TianDan(void)
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
void TianDan::loadArmature()
{
	m_stRoleInfo.arAnimate = Armature::create(m_strRoleName.c_str());
	if (NULL == m_stRoleInfo.arAnimate)
	{
		return;
	}

	memset(m_hTianDanFire, 0, sizeof(m_hTianDanFire));

	this->addChild(m_stRoleInfo.arAnimate);

	/* 注册动画帧事件和动作回调函数 */
	m_stRoleInfo.arAnimate->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(TianDan::actionFrameEventCallFunc, this, std::placeholders::_1
		, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	m_stRoleInfo.arAnimate->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(TianDan::actionMovementCallFunc, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

/*********************************************************************
** 功能：		初始化角色技能属性
** 输入参数：	无
** 返回值：		无
** 修改记录：	
*********************************************************************/
void TianDan::initActInherent()
{
	Role::initActInherent();
		
	m_stActMode[RoleAct_SkillThree] = RoleActMode_Guard;			/* 技能三 */
}

/*********************************************************************
** 功能：		初始化技能飞行道具
** 输入参数：	无
** 返回值：		无
** 修改记录：	
*********************************************************************/
void TianDan::initFlightPropInfo()
{
	m_stTianDanProp[TianDan_Normal].strPath = getFlightPropPath() + "TianDan_Normal";
	m_stTianDanProp[TianDan_Normal].ptOffset = Point(100, 80) * m_fResScale;
	m_stTianDanProp[TianDan_Normal].iImgNum = 1;

	m_stTianDanProp[TianDan_S2Prop].strPath = getFlightPropPath() + "TianDan_S2Prop";
	m_stTianDanProp[TianDan_S2Prop].ptOffset = Point(0, 80) * m_fResScale;
	m_stTianDanProp[TianDan_S2Prop].iImgNum = 8;

	m_stTianDanProp[TianDan_S3Prop].strPath = getFlightPropPath() + "TianDan_S3Prop";
	m_stTianDanProp[TianDan_S3Prop].ptOffset = Point(0, 105) * m_fResScale;
	m_stTianDanProp[TianDan_S3Prop].iImgNum = 5;
}

/*********************************************************************
** 功能：		动作回调函数
** 输入参数：	
** 返回值： 	
** 修改记录：	
*********************************************************************/
void TianDan::actionMovementCallFunc(Armature *ar, MovementEventType type, const std::string& str)
{
	movement(str, type, 0.5f);
}

/*********************************************************************
** 功能：		帧事件
** 输入参数：	
** 返回值： 	无
** 修改记录：	
*********************************************************************/
void TianDan::actionFrameEventCallFunc(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
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
			NormalAttack(bDown);
		}

		if (RoleAct_SkillTwo == m_stRoleInfo.actSign)
		{
			SkillTwo();
		}

		if (RoleAct_SkillThree == m_stRoleInfo.actSign)
		{
			this->unschedule(schedule_selector(TianDan::fireSchedule));
			SkillThree(90.0f, TianDanS3_One);
			SkillThree(330.0f, TianDanS3_Two);
			SkillThree(210.0f, TianDanS3_Three);
			this->scheduleOnce(schedule_selector(TianDan::fireSchedule), fFireDuration);
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
bool TianDan::runActionAttack()
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
bool TianDan::runActionTwiceAtk()
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
bool TianDan::runActionThriceAtk()
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
bool TianDan::runActionSkillOne()
{
	bool bRet = Role::runActionSkillOne();
	if (true == bRet)
	{
		playEffectOgg("021DD");
	}

	return bRet;
}

/*********************************************************************
** 功能：		执行技能二
** 输入参数：	无
** 返回值： 	无
** 修改记录：	
*********************************************************************/
bool TianDan::runActionSkillTwo()
{
	bool bRet = Role::runActionSkillTwo();
	if (true == bRet)
	{
		playEffectOgg("020JN");
	}

	return bRet;
}

/*********************************************************************
** 功能：		执行技能三
** 输入参数：	无
** 返回值： 	无
** 修改记录：	
*********************************************************************/
bool TianDan::runActionSkillThree()
{
	bool bRet = Role::runActionSkillThree();
	if (true == bRet)
	{
		playEffectOgg("020JN");
	}

	return bRet;
}
/* 动作执行 End*/

/*********************************************************************
** 功能：		角色被击
** 输入参数：	RoleDirection dir: 攻击方向
**				SkillInfo skillInfo: 技能信息
**				bool bDown:true:倒地;false: 不倒地
** 返回值：		
** 修改记录：	
*********************************************************************/
int TianDan::roleHurt(Role* role, SkillInfo skillInfo, bool bDown)
{
	if (RoleActMode_Magic == skillInfo.model)					/* 技能3可防御技能攻击 */
	{
		for (int index = TianDanS3_One;index < TianDanS3_Max;index ++)
		{
			if (true == removeFireByID(index))
			{
				return m_stRoleInfo.panel.hpCurrent;
			}
		}
	}

	return Role::roleHurt(this, skillInfo, bDown);
}

/*********************************************************************
** 功能：		普通攻击
** 输入参数：	bool bDown : 击中是否倒地
** 返回值：		无
** 修改记录：	
*********************************************************************/
void TianDan::NormalAttack(bool bDown)
{
	FlightPropInfo info = {0};
	info.num = m_stTianDanProp[TianDan_Normal].iImgNum;
	memcpy(&(info.skillInfo), &m_stSkillInfo[m_stRoleInfo.actSign], sizeof(SkillInfo));

	auto tdProp = CommonProp::create(this, m_stTianDanProp[TianDan_Normal].strPath, info);
	if (NULL != tdProp)
	{
		tdProp->setScaleX(m_stRoleSubInfo.side/* * m_fResScale*/);
		//tdProp->setScaleY(m_fResScale);
		tdProp->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
		tdProp->setPropFlag(bDown);
		tdProp->setPropPosition(Point(-m_stTianDanProp[TianDan_Normal].ptOffset.x * m_stRoleSubInfo.side, m_stTianDanProp[TianDan_Normal].ptOffset.y));
		this->getParent()->addChild(tdProp);
		tdProp->runPropCollisionDetective(0.2f, Point(-m_stSkillInfo[m_stRoleInfo.actSign].xAtkDis * m_stRoleSubInfo.side, 0));
	}
}

/*********************************************************************
** 功能：		技能2
** 输入参数：	无
** 返回值：		无
** 修改记录：	
*********************************************************************/
void TianDan::SkillTwo()
{
	FlightPropInfo info = {0};
	info.num = m_stTianDanProp[TianDan_S2Prop].iImgNum;
	info.dur = 0.35f / m_stTianDanProp[TianDan_S2Prop].iImgNum;
	memcpy(&(info.skillInfo), &m_stSkillInfo[RoleAct_SkillTwo], sizeof(SkillInfo));

	auto tdProp = CommonProp::create(this, m_stTianDanProp[TianDan_S2Prop].strPath, info);
	if (NULL != tdProp)
	{
		tdProp->setScale(m_fResScale);
		tdProp->setAnchorPoint(Point::ANCHOR_MIDDLE);
		tdProp->setPropFlag(false, 0.15f);
		tdProp->setPropPosition(Point(-m_stTianDanProp[TianDan_S2Prop].ptOffset.x * m_stRoleSubInfo.side, m_stTianDanProp[TianDan_S2Prop].ptOffset.y));
		this->getParent()->addChild(tdProp);
		tdProp->runPropCollisionDetective(0.2f, Point(-m_stSkillInfo[RoleAct_SkillTwo].xAtkDis * m_stRoleSubInfo.side, 0));
	}
}

/*********************************************************************
** 功能：		技能3
** 输入参数：	float angle: 火焰初始角度
**				int id: 火焰id
** 返回值：		无
** 修改记录：	
*********************************************************************/
void TianDan::SkillThree(float angle, int id)
{
	removeFireByID(id);

	FlightPropInfo info = {0};
	info.reserve = angle;											/* 初始角度 */
	info.num = m_stTianDanProp[TianDan_S3Prop].iImgNum;
	info.dur = 0.25f / m_stTianDanProp[TianDan_S3Prop].iImgNum;
	memcpy(&(info.skillInfo), &m_stSkillInfo[RoleAct_SkillThree], sizeof(SkillInfo));

	m_hTianDanFire[id] = SatelliteProp::create(this, m_stTianDanProp[TianDan_S3Prop].strPath, info);
	if (NULL != m_hTianDanFire[id])
	{
		m_hTianDanFire[id]->setScale(m_fResScale);
		m_hTianDanFire[id]->setPropPosition(m_stTianDanProp[TianDan_S3Prop].ptOffset);
		this->getParent()->addChild(m_hTianDanFire[id]);
		m_hTianDanFire[id]->runPropCollisionDetective();
	}
}

/*********************************************************************
** 功能：		移除火焰
** 输入参数：	int id: 火焰id
** 返回值：		无
** 修改记录：	
*********************************************************************/
bool TianDan::removeFireByID(int id)
{
	bool bRet = false;

	if (NULL != m_hTianDanFire[id])
	{
		m_hTianDanFire[id]->removeFromParentAndCleanup(true);
		m_hTianDanFire[id] = NULL;
		bRet = true;
	}

	return bRet;
}

/*********************************************************************
** 功能：		火焰计时器
** 输入参数：	float dt
** 返回值：		无
** 修改记录：	
*********************************************************************/
void TianDan::fireSchedule(float dt)
{
	removeFireByID(TianDanS3_One);
	removeFireByID(TianDanS3_Two);
	removeFireByID(TianDanS3_Three);
}
/* protected: End */