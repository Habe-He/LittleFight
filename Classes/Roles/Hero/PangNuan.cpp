#include "PangNuan.h"
#include "Roles/SkillProps/CommonProp.h"
#include "Roles/SkillProps/EnergyBall.h"

USING_NS_CC;
using namespace cocostudio;

const float pn_fIceDuration = 5.0f;					/* 冰持续时间 */

PangNuan::PangNuan(void)
{
}

PangNuan::~PangNuan(void)
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
void PangNuan::loadArmature()
{
	m_stRoleInfo.arAnimate = Armature::create(m_strRoleName.c_str());
	if (NULL == m_stRoleInfo.arAnimate)
	{
		return;
	}

	memset(m_hIcePiton, 0, sizeof(m_hIcePiton));

	this->addChild(m_stRoleInfo.arAnimate);

	/* 注册动画帧事件和动作回调函数 */
	m_stRoleInfo.arAnimate->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(PangNuan::actionFrameEventCallFunc, this, std::placeholders::_1
		, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	m_stRoleInfo.arAnimate->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(PangNuan::actionMovementCallFunc, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

/*********************************************************************
** 功能：		初始化角色技能属性
** 输入参数：	无
** 返回值：		无
** 修改记录：	
*********************************************************************/
void PangNuan::initActInherent()
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
void PangNuan::initFlightPropInfo()
{
	m_stPangNuanProp[PangNuan_Magic].strPath = getFlightPropPath() + "PangNuan_Magic";
	m_stPangNuanProp[PangNuan_Magic].ptOffset = Point(150, 100) * m_fResScale;
	m_stPangNuanProp[PangNuan_Magic].iImgNum = 1;

	m_stPangNuanProp[PangNuan_Light].strPath = getFlightPropPath() + "BianQue_S2Prop";
	m_stPangNuanProp[PangNuan_Light].ptOffset = Point(0, 200) * m_fResScale;
	m_stPangNuanProp[PangNuan_Light].iImgNum = 5;

	m_stPangNuanProp[PangNuan_Ice].strPath = getFlightPropPath() + "BianQue_S3Prop";
	m_stPangNuanProp[PangNuan_Ice].ptOffset = Point(0, 80) * m_fResScale;
	m_stPangNuanProp[PangNuan_Ice].iImgNum = 2;
}

/*********************************************************************
** 功能：		动作回调函数
** 输入参数：	
** 返回值： 	
** 修改记录：	
*********************************************************************/
void PangNuan::actionMovementCallFunc(Armature *ar, MovementEventType type, const std::string& str)
{
	movement(str, type, 0.5f);
}

/*********************************************************************
** 功能：		帧事件
** 输入参数：	
** 返回值： 	无
** 修改记录：	
*********************************************************************/
void PangNuan::actionFrameEventCallFunc(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
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
			SkillTwo();
			SkillTwo();
		}

		if (RoleAct_SkillThree == m_stRoleInfo.actSign)
		{
			this->unschedule(schedule_selector(PangNuan::IceSchedule));
			SkillThree(90.0f, PangNuanS3_One);
			SkillThree(330.0f, PangNuanS3_Two);
			SkillThree(210.0f, PangNuanS3_Three);
			this->scheduleOnce(schedule_selector(PangNuan::IceSchedule), pn_fIceDuration);
		}
	}
}

void PangNuan::updateRole()
{
	for (int index = PangNuanS3_One;index < PangNuanS3_Max;index ++)
	{
		if (NULL != m_hIcePiton[index])
		{
			if (true == m_hIcePiton[index]->PropCollisionDetective())
			{
				removeIceByID(index);
			}
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
void PangNuan::roleCollisionDetective(bool bDown)
{
	auto roles = UserData::getInstance()->getRoles();

	for(unsigned int index = 0;index < roles.size();index ++)		/* 敌人角色遍历获取 */
	{
		auto role = (Role *)roles[index];
		auto info = role->getRoleInfo();

		if ((RoleStatus_Death == info.status) || (RoleStatus_Invincible == info.status) || (m_iSceneID != role->getSceneID()))
		{
			continue;												/* 无敌、同阵营或是自身不处理 *//* 援助不伤主将 */
		}
		auto hitSide = RoleDir_Left;								/* 对方被攻击方向 */
		hitSide = (getPositionX() > role->getPositionX()) ? RoleDir_Left : RoleDir_Right;

		if (-1 != hitSide * m_stRoleSubInfo.atkSide)				/* 确认方向无误 */
		{
			/* 碰撞且角色方向和对方受击方向符合 *//* 在敌人右方曹左攻击、在敌人左方曹右攻击 */
			auto ptOffset = role->getPosition() - getPosition();/* 相对位置 */

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
bool PangNuan::runActionAttack()
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
bool PangNuan::runActionTwiceAtk()
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
bool PangNuan::runActionThriceAtk()
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
bool PangNuan::runActionSkillOne()
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
bool PangNuan::runActionSkillTwo()
{
	bool bRet = Role::runActionSkillTwo();
	if (true == bRet)
	{
		playEffectOgg("094HF");
	}

	return bRet;
}

/*********************************************************************
** 功能：		执行技能三
** 输入参数：	无
** 返回值： 	无
** 修改记录：	
*********************************************************************/
bool PangNuan::runActionSkillThree()
{
	bool bRet = Role::runActionSkillThree();
	if (true == bRet)
	{
		playEffectOgg("C034JN");
	}

	return bRet;
}
/* 动作执行 End*/

/*********************************************************************
** 功能：		普通攻击
** 输入参数：	bool bDown:true:倒地;false:不倒地
** 返回值：		
** 修改记录：	
*********************************************************************/
void PangNuan::NormalAttack(bool bDown)
{
	FlightPropInfo info = {0};
	info.num = m_stPangNuanProp[PangNuan_Magic].iImgNum;
	memcpy(&(info.skillInfo), &m_stSkillInfo[m_stRoleInfo.actSign], sizeof(SkillInfo));

	auto pnMagic = CommonProp::create(this, m_stPangNuanProp[PangNuan_Magic].strPath, info);
	auto pt = m_stPangNuanProp[PangNuan_Magic].ptOffset;

	if (NULL != pnMagic)
	{
		pnMagic->setScaleX(m_stRoleSubInfo.side * m_fResScale);
		pnMagic->setScaleY(m_fResScale);
		pnMagic->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);

		if (RoleAct_Thrice_Atk == m_stRoleInfo.actSign)				/* 第三击坐标偏移修正 */
		{
			pt.x = pt.x / 2;
		}

		pnMagic->setPropPosition(Point(-pt.x * m_stRoleSubInfo.side, pt.y));
		pnMagic->setPropFlag(bDown);
		this->getParent()->addChild(pnMagic);
		pnMagic->runPropCollisionDetective(0.3f, Point(-m_stSkillInfo[m_stRoleInfo.actSign].xAtkDis * m_stRoleSubInfo.side, 0));
	}
}

void PangNuan::SkillTwo()
{
	FlightPropInfo info = {0};
	info.num = m_stPangNuanProp[PangNuan_Light].iImgNum;
	info.dur = 0.5f / m_stPangNuanProp[PangNuan_Light].iImgNum;
	memcpy(&(info.skillInfo), &m_stSkillInfo[m_stRoleInfo.actSign], sizeof(SkillInfo));

	auto energyBall = EnergyBall::create(this, m_stPangNuanProp[PangNuan_Light].strPath, info);

	if (NULL != energyBall)
	{
		energyBall->setPropPosition(m_stPangNuanProp[PangNuan_Light].ptOffset);
		energyBall->setPosition(getPosition() + m_stPangNuanProp[PangNuan_Light].ptOffset);
		energyBall->setScale(m_fResScale);
		energyBall->setAnchorPoint(Point::ANCHOR_MIDDLE);
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
void PangNuan::SkillThree(float angle, int id)
{
	removeIceByID(id);

	FlightPropInfo info = {0};
	info.reserve = angle;											/* 初始角度 */
	info.num = m_stPangNuanProp[PangNuan_Ice].iImgNum;
	info.dur = 0.15f / m_stPangNuanProp[PangNuan_Ice].iImgNum;
	memcpy(&(info.skillInfo), &m_stSkillInfo[RoleAct_SkillThree], sizeof(SkillInfo));

	m_hIcePiton[id] = IcePiton::create(this, m_stPangNuanProp[PangNuan_Ice].strPath, info);

	if (NULL != m_hIcePiton[id])
	{
		m_hIcePiton[id]->setScale(m_fResScale);
		m_hIcePiton[id]->setPropPosition(m_stPangNuanProp[PangNuan_Ice].ptOffset);
		this->getParent()->addChild(m_hIcePiton[id]);
		m_hIcePiton[id]->runPropCollisionDetective();
	}
}

/*********************************************************************
** 功能：		移除冰
** 输入参数：	int id: 冰id
** 返回值：		无
** 修改记录：	
*********************************************************************/
bool PangNuan::removeIceByID(int id)
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
void PangNuan::IceSchedule(float dt)
{
	for (int index = PangNuanS3_One;index < PangNuanS3_Max;index ++)
	{
		removeIceByID(index);
	}
}
/* protected: End */