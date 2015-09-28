#include "BianQue.h"
#include "Roles/SkillProps/CommonProp.h"
#include "Roles/SkillProps/EnergyBall.h"

USING_NS_CC;
using namespace cocostudio;

const float bq_fIceDuration = 5.0f;		/* 冰持续时间 */

BianQue::BianQue(void)
{
}

BianQue::~BianQue(void)
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
void BianQue::loadArmature()
{
	m_stRoleInfo.arAnimate = Armature::create(m_strRoleName.c_str());
	if (NULL == m_stRoleInfo.arAnimate)
	{
		return;
	}

	memset(m_hIcePiton, 0, sizeof(m_hIcePiton));

	this->addChild(m_stRoleInfo.arAnimate);

	/* 注册动画帧事件和动作回调函数 */
	m_stRoleInfo.arAnimate->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(BianQue::actionFrameEventCallFunc, this, std::placeholders::_1
		, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	m_stRoleInfo.arAnimate->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(BianQue::actionMovementCallFunc, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

/*********************************************************************
** 功能：		初始化角色技能属性
** 输入参数：	无
** 返回值：		无
** 修改记录：	
*********************************************************************/
void BianQue::initActInherent()
{
	Role::initActInherent();

	m_stActMode[RoleAct_SkillOne] = RoleActMode_Super;			/* 技能一 */
	m_stActMode[RoleAct_SkillTwo] = RoleActMode_Super;			/* 技能二 */			
	m_stActMode[RoleAct_SkillThree] = RoleActMode_Control;		/* 技能三 */
}

/*********************************************************************
** 功能：		初始化技能飞行道具
** 输入参数：	无
** 返回值：		无
** 修改记录：	
*********************************************************************/
void BianQue::initFlightPropInfo()
{
	/* 普攻魔法球 */
	m_stBianQueProp[BianQue_Magic].strPath = getFlightPropPath() + "BianQue_Magic";
	m_stBianQueProp[BianQue_Magic].ptOffset = Point(0, 0) * m_fResScale;
	m_stBianQueProp[BianQue_Magic].iImgNum = 1;

	/* 回血魔法 */
	m_stBianQueProp[BianQue_Light].strPath = getFlightPropPath() + "BianQue_S2Prop";
	m_stBianQueProp[BianQue_Light].ptOffset = Point(0, 200) * m_fResScale;
	m_stBianQueProp[BianQue_Light].iImgNum = 5;

	/* 冰魔法 */
	m_stBianQueProp[BianQue_Ice].strPath = getFlightPropPath() + "BianQue_S3Prop";
	m_stBianQueProp[BianQue_Ice].ptOffset = Point(0, 80) * m_fResScale;
	m_stBianQueProp[BianQue_Ice].iImgNum = 2;

	/* 凤凰 */
	m_stBianQueProp[BianQue_Phenix].strPath = getFlightPropPath() + "BianQue_S4Prop";
	m_stBianQueProp[BianQue_Phenix].ptOffset = Point(0, 80) * m_fResScale;
	m_stBianQueProp[BianQue_Phenix].iImgNum = 9;
}

/*********************************************************************
** 功能：		动作回调函数
** 输入参数：	
** 返回值： 	
** 修改记录：	
*********************************************************************/
void BianQue::actionMovementCallFunc(Armature *ar, MovementEventType type, const std::string& str)
{
	movement(str, type, 0.5f);
}

/*********************************************************************
** 功能：		帧事件
** 输入参数：	
** 返回值： 	无
** 修改记录：	
*********************************************************************/
void BianQue::actionFrameEventCallFunc(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
{
	frameEvent(evt);

	bool bDown = false;
	if (evt == getFrameEventName(FrameEvent_Shot_FD))
	{
		bDown = true;
	}

	if ((evt == getFrameEventName(FrameEvent_Shot)) || (evt == getFrameEventName(FrameEvent_Shot_FD)))
	{
		if (RoleAct_Attack == m_stRoleInfo.actSign)
		{
			NormalAttack(Point(100, 90), bDown);
		}

		if (RoleAct_Twice_Atk == m_stRoleInfo.actSign)
		{
			NormalAttack(Point(140, 50), bDown);
		}

		if (RoleAct_Thrice_Atk == m_stRoleInfo.actSign)
		{
			NormalAttack(Point(80, 110), bDown);
		}

		if (RoleAct_SkillTwo == m_stRoleInfo.actSign)
		{
			SkillTwo();
			SkillTwo();
			SkillTwo();
		}

		if (RoleAct_SkillThree == m_stRoleInfo.actSign)
		{
			this->unschedule(schedule_selector(BianQue::IceSchedule));
			SkillThree(90.0f, BianQueS3_One);
			SkillThree(330.0f, BianQueS3_Two);
			SkillThree(210.0f, BianQueS3_Three);
			this->scheduleOnce(schedule_selector(BianQue::IceSchedule), bq_fIceDuration);
		}

		if (RoleAct_SkillFour == m_stRoleInfo.actSign)
		{
			SkillFour();
		}
	}
}

void BianQue::updateRole()
{
	for (int index = BianQueS3_One;index < BianQueS3_Max;index ++)
	{
		if (NULL != m_hIcePiton[index])
		{
			if (true == m_hIcePiton[index]->PropCollisionDetective())
			{
				removeIceByID(index);
			}
		}
	}

	if (true == isRoleLearnedTalent(RoleTalent_ZhangKongZhanChang))	/* 掌控战场 */
	{
		if (m_stRoleInfo.panel.hpCurrent * 1.0f / m_stRoleInfo.panel.hpTotal < 0.35f)
		{
			m_stRoleBuff.atk *= 1.8f;
		}
		else
		{
			m_stRoleBuff.atk = 0;
		}
	}

	Role::updateRole();
}

/*********************************************************************
** 功能：		执行碰撞检测
** 输入参数：	bool bDown:true:倒地;false:不倒地
** 返回值：		无
** 修改记录：	
*********************************************************************/
void BianQue::roleCollisionDetective(bool bDown)
{
	auto roles = UserData::getInstance()->getRoles();

	for(unsigned int index = 0;index < roles.size();index ++)		/* 敌人角色遍历获取 */
	{
		auto role = (Role *)roles[index];
		auto info = role->getRoleInfo();

		if ((RoleStatus_Death == info.status) || (RoleStatus_Invincible == info.status) || (m_iSceneID != role->getSceneID()))
		{
			continue;												/* 无敌、同阵营或是自身不处理 *//* 小伙伴不伤主将 */
		}

		auto hitSide = RoleDir_Left;								/* 对方被攻击方向 */
		hitSide = (getPositionX() > role->getPositionX()) ? RoleDir_Left : RoleDir_Right;

		if (-1 != hitSide * m_stRoleSubInfo.atkSide)				/* 确认方向无误 */
		{
			/* 碰撞且角色方向和对方受击方向符合 *//* 在敌人右方曹左攻击、在敌人左方曹右攻击 */
			auto ptOffset = role->getPosition() - getPosition();	/* 相对位置 */

			/* 动作有效范围判断 */
			if ((m_stSkillInfo[m_stRoleInfo.actSign].xAtkDis >= abs(ptOffset.x)) && (m_stSkillInfo[m_stRoleInfo.actSign].yAtkDis >= abs(ptOffset.y)))
			{
				if (RoleActMode_Super == m_stActMode[m_stRoleInfo.actSign])
				{
					if (info.camp == m_stRoleInfo.camp)
					{
						role->setRoleHpUp(m_stSkillInfo[m_stRoleInfo.actSign].damage);/* 当前同阵营，补给 */
					}
					else
					{
						role->roleHurt(this, m_stSkillInfo[m_stRoleInfo.actSign], bDown);/* 当前非同阵营，伤害 */
					}
				}
				else												
				{
					if (info.camp != m_stRoleInfo.camp)
					{
						role->roleHurt(this, m_stSkillInfo[m_stRoleInfo.actSign], bDown);/* 当前非同阵营，伤害 */
					}
					if (RoleActMode_Physical == m_stActMode[m_stRoleInfo.actSign])
					{
						m_bRoleActBreak = true;
					}
				}
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
bool BianQue::runActionAttack()
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
bool BianQue::runActionTwiceAtk()
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
bool BianQue::runActionThriceAtk()
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
bool BianQue::runActionSkillOne()
{
	bool bRet = Role::runActionSkillOne();
	if (true == bRet)
	{
		playEffectOgg("C035Q");
	}

	return bRet;
}

/*********************************************************************
** 功能：		执行技能二
** 输入参数：	无
** 返回值： 	无
** 修改记录：	
*********************************************************************/
bool BianQue::runActionSkillTwo()
{
	bool bRet = Role::runActionSkillTwo();
	if (true == bRet)
	{
		playEffectOgg("C037HF");
	}

	return bRet;
}

/*********************************************************************
** 功能：		执行技能三
** 输入参数：	无
** 返回值： 	无
** 修改记录：	
*********************************************************************/
bool BianQue::runActionSkillThree()
{
	bool bRet = Role::runActionSkillThree();
	if (true == bRet)
	{
		playEffectOgg("C034JN");
	}

	return bRet;
}

/*********************************************************************
** 功能：		执行技能四
** 输入参数：	无
** 返回值： 	无
** 修改记录：	
*********************************************************************/
bool BianQue::runActionSkillFour()
{
	bool bRet = Role::runActionSkillFour();
	if (true == bRet)
	{
		playEffectOgg("033ZH");
	}

	return bRet;
}
/* 动作执行 End*/

/*********************************************************************
** 功能：		普攻击
** 输入参数：	Point ptLoc: 魔法球初始位置
**				bool bDown: 倒地
** 返回值：		无
** 修改记录：	
*********************************************************************/
void BianQue::NormalAttack(Point ptLoc, bool bDown)
{
	FlightPropInfo info = {0};
	info.num = m_stBianQueProp[BianQue_Magic].iImgNum;
	memcpy(&(info.skillInfo), &m_stSkillInfo[m_stRoleInfo.actSign], sizeof(SkillInfo));

	auto bqProp = CommonProp::create(this, m_stBianQueProp[BianQue_Magic].strPath, info);

	if (NULL != bqProp)
	{
		bqProp->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
		bqProp->setScaleX(m_stRoleSubInfo.side * m_fResScale);
		bqProp->setPropPosition(Point(-ptLoc.x * m_stRoleSubInfo.side * m_fResScale, ptLoc.y * m_fResScale));
		bqProp->setPropFlag(bDown);

		this->getParent()->addChild(bqProp);
		bqProp->runPropCollisionDetective(0.3f, Point(-m_stSkillInfo[m_stRoleInfo.actSign].xAtkDis * m_stRoleSubInfo.side, 0));
	}
}

/*********************************************************************
** 功能：		技能
** 输入参数：	无
** 返回值：		无
** 修改记录：	
*********************************************************************/
void BianQue::SkillTwo()
{
	FlightPropInfo info = {0};
	info.num = m_stBianQueProp[BianQue_Light].iImgNum;
	info.dur = 0.5f / info.num;
	memcpy(&(info.skillInfo), &m_stSkillInfo[m_stRoleInfo.actSign], sizeof(SkillInfo));

	auto energyBall = EnergyBall::create(this, m_stBianQueProp[BianQue_Light].strPath, info);

	if (NULL != energyBall)
	{
		energyBall->setPropPosition(m_stBianQueProp[BianQue_Light].ptOffset);
		energyBall->setScale(m_fResScale);
		energyBall->setAnchorPoint(Point::ANCHOR_MIDDLE);
		energyBall->setSceneID(m_iSceneID);
		this->getParent()->addChild(energyBall);
		energyBall->energyBallAction();
	}
}

/*********************************************************************
** 功能：		技能3
** 输入参数：	float angle: 冰初始角度
**				int id: 冰id
** 返回值：		无
** 修改记录：	
*********************************************************************/
void BianQue::SkillThree(float angle, int id)
{
	removeIceByID(id);

	FlightPropInfo info = {0};
	info.reserve = angle;											/* 初始角度 */
	info.num = m_stBianQueProp[BianQue_Ice].iImgNum;
	info.dur = 0.15f / m_stBianQueProp[BianQue_Ice].iImgNum;
	memcpy(&(info.skillInfo), &m_stSkillInfo[RoleAct_SkillThree], sizeof(SkillInfo));

	m_hIcePiton[id] = IcePiton::create(this, m_stBianQueProp[BianQue_Ice].strPath, info);

	if (NULL != m_hIcePiton[id])
	{
		m_hIcePiton[id]->setScale(m_fResScale);
		m_hIcePiton[id]->setPropPosition(m_stBianQueProp[BianQue_Ice].ptOffset);
		this->getParent()->addChild(m_hIcePiton[id]);
		m_hIcePiton[id]->runPropCollisionDetective();
	}
}

/*********************************************************************
** 功能：		技能4
** 输入参数：	无
** 返回值：		无
** 修改记录：	
*********************************************************************/
void BianQue::SkillFour()
{
	FlightPropInfo info = {0};
	info.num = m_stBianQueProp[BianQue_Phenix].iImgNum;
	info.dur = 0.7f / m_stBianQueProp[BianQue_Phenix].iImgNum;
	memcpy(&(info.skillInfo), &m_stSkillInfo[m_stRoleInfo.actSign], sizeof(SkillInfo));

	auto phenix = CommonProp::create(this, m_stBianQueProp[BianQue_Phenix].strPath, info);

	if (NULL != phenix)
	{
		phenix->setScaleX(m_stRoleSubInfo.side * m_fResScale);
		phenix->setScaleY(m_fResScale);
		phenix->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);

		phenix->setPropPosition(Point(-m_stBianQueProp[BianQue_Phenix].ptOffset.x * m_stRoleSubInfo.side, 
			m_stBianQueProp[BianQue_Phenix].ptOffset.y));
		phenix->setPropFlag(true);

		this->getParent()->addChild(phenix);
		phenix->runPropCollisionDetective(2.3f, Point(-m_stSkillInfo[m_stRoleInfo.actSign].xAtkDis * m_stRoleSubInfo.side, 0));
	}
}

/*********************************************************************
** 功能：		移除冰
** 输入参数：	int id: 冰id
** 返回值：		无
** 修改记录：	
*********************************************************************/
bool BianQue::removeIceByID(int id)
{
	bool bRet = false;

	if (NULL != m_hIcePiton[id])
	{
		m_hIcePiton[id]->removeFromParentAndCleanup(true);
		m_hIcePiton[id] = NULL;
		bRet = true;
	}

	return bRet;
}

/*********************************************************************
** 功能：		冰计时器
** 输入参数：	float dt
** 返回值：		无
** 修改记录：	
*********************************************************************/
void BianQue::IceSchedule(float dt)
{
	for (int index = BianQueS3_One;index < BianQueS3_Max;index ++)
	{
		removeIceByID(index);
	}
}
/* protected: End */