#include "ShangYang.h"
#include "Roles/SkillProps/CommonProp.h"

USING_NS_CC;
using namespace cocostudio;


const float fFontDuration = 15.0f;		/* 大字持续时间 */

ShangYang::ShangYang(void)
{
}

ShangYang::~ShangYang(void)
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
void ShangYang::loadArmature()
{
	m_stRoleInfo.arAnimate = Armature::create(m_strRoleName.c_str());
	if (NULL == m_stRoleInfo.arAnimate)
	{
		return;
	}

	memset(m_hShangYangFont, 0, sizeof(m_hShangYangFont));

	this->addChild(m_stRoleInfo.arAnimate);

	/* 注册动画帧事件和动作回调函数 */
	m_stRoleInfo.arAnimate->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(ShangYang::actionFrameEventCallFunc, this, std::placeholders::_1
		, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	m_stRoleInfo.arAnimate->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(ShangYang::actionMovementCallFunc, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

/*********************************************************************
** 功能：		初始化角色技能属性
** 输入参数：	无
** 返回值：		无
** 修改记录：	
*********************************************************************/
void ShangYang::initActInherent()
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
void ShangYang::initFlightPropInfo()
{
	m_stShangYangProp[ShangYang_Magic].strPath = getFlightPropPath() + "ShangYang_Magic";
	m_stShangYangProp[ShangYang_Magic].ptOffset = Point(130, 70) * m_fResScale;
	m_stShangYangProp[ShangYang_Magic].iImgNum = 1;

	m_stShangYangProp[ShangYang_S2Prop].strPath = getFlightPropPath() + "ShangYang_S2Prop";
	m_stShangYangProp[ShangYang_S2Prop].ptOffset = Point(0, 60) * m_fResScale;
	m_stShangYangProp[ShangYang_S2Prop].iImgNum = 8;

	m_stShangYangProp[ShangYang_S3Prop].strPath = getFlightPropPath() + "ShangYang_S3Prop";
	m_stShangYangProp[ShangYang_S3Prop].ptOffset = Point(0, 100) * m_fResScale;
	m_stShangYangProp[ShangYang_S3Prop].iImgNum = 4;
}

/*********************************************************************
** 功能：		动作回调函数
** 输入参数：	
** 返回值： 	
** 修改记录：	
*********************************************************************/
void ShangYang::actionMovementCallFunc(Armature *ar, MovementEventType type, const std::string& str)
{
	movement(str, type, 0.5f);
}

/*********************************************************************
** 功能：		帧事件
** 输入参数：	
** 返回值： 	无
** 修改记录：	
*********************************************************************/
void ShangYang::actionFrameEventCallFunc(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
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
			this->unschedule(schedule_selector(ShangYang::FontSchedule));
			SkillThree(90.0f, ShangYangS3_One);
			SkillThree(330.0f, ShangYangS3_Two);
			SkillThree(210.0f, ShangYangS3_Three);
			this->scheduleOnce(schedule_selector(ShangYang::FontSchedule), fFontDuration);
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
bool ShangYang::runActionAttack()
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
bool ShangYang::runActionTwiceAtk()
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
bool ShangYang::runActionThriceAtk()
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
bool ShangYang::runActionSkillOne()
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
bool ShangYang::runActionSkillTwo()
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
bool ShangYang::runActionSkillThree()
{
	bool bRet = Role::runActionSkillThree();
	if (true == bRet)
	{
		playEffectOgg("020JN");
	}

	return bRet;
}

/*********************************************************************
** 功能：		执行技能四
** 输入参数：	无
** 返回值： 	无
** 修改记录：	
*********************************************************************/
bool ShangYang::runActionSkillFour()
{
	bool bRet = Role::runActionSkillFour();
	if (true == bRet)
	{
		playEffectOgg("033GZ");
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
int ShangYang::roleHurt(Role* role, SkillInfo skillInfo, bool bDown)
{
	if (RoleActMode_Magic == skillInfo.model)				/* 技能3可防御技能攻击 */
	{
		for (int index = ShangYangS3_One;index < ShangYangS3_Max;index ++)
		{
			if (true == removeFontByID(index))
			{
				return m_stRoleInfo.panel.hpCurrent;
			}
		}
	}

	return Role::roleHurt(this, skillInfo, bDown);
}

void ShangYang::NormalAttack(bool bDown)
{
	FlightPropInfo info = {0};
	info.num = m_stShangYangProp[ShangYang_Magic].iImgNum;
	info.dur = 0.2f / m_stShangYangProp[ShangYang_Magic].iImgNum;
	memcpy(&(info.skillInfo), &m_stSkillInfo[m_stRoleInfo.actSign], sizeof(SkillInfo));

	auto syProp = CommonProp::create(this, m_stShangYangProp[ShangYang_Magic].strPath, info);
	if (NULL != syProp)
	{
		syProp->setScale(m_stRoleSubInfo.side * m_fResScale);
		syProp->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
		syProp->setPropFlag(bDown);
		syProp->setPropPosition(Point(-m_stRoleSubInfo.side * m_stShangYangProp[ShangYang_Magic].ptOffset.x, m_stShangYangProp[ShangYang_Magic].ptOffset.y));
		this->getParent()->addChild(syProp);
		syProp->runPropCollisionDetective(0.35f, Point(-m_stSkillInfo[m_stRoleInfo.actSign].xAtkDis * m_stRoleSubInfo.side, 0));
	}
}

void ShangYang::SkillTwo()
{
	FlightPropInfo info = {0};
	info.num = m_stShangYangProp[ShangYang_S2Prop].iImgNum;
	info.dur = 0.2f / m_stShangYangProp[ShangYang_S2Prop].iImgNum;
	memcpy(&(info.skillInfo), &m_stSkillInfo[RoleAct_SkillTwo], sizeof(SkillInfo));

	auto syProp = CommonProp::create(this, m_stShangYangProp[ShangYang_S2Prop].strPath, info);
	if (NULL != syProp)
	{
		syProp->setScaleX(m_stRoleSubInfo.side * m_fResScale);
		syProp->setScaleY(m_fResScale);
		syProp->setAnchorPoint(Point::ANCHOR_MIDDLE);
		syProp->setPropPosition(Point(-m_stRoleSubInfo.side * m_stShangYangProp[ShangYang_S2Prop].ptOffset.x, m_stShangYangProp[ShangYang_S2Prop].ptOffset.y));
		this->getParent()->addChild(syProp);
		syProp->runPropCollisionDetective(0.35f, Point(-m_stSkillInfo[RoleAct_SkillTwo].xAtkDis * m_stRoleSubInfo.side, 0));
	}
}

/*********************************************************************
** 功能：		技能3
** 输入参数：	float angle: 火焰初始角度
**				int id: 火焰id
** 返回值：		无
** 修改记录：	
*********************************************************************/
void ShangYang::SkillThree(float angle, int id)
{
	removeFontByID(id);

	FlightPropInfo info = {0};
	info.reserve = angle;													/* 初始角度 */
	info.num = m_stShangYangProp[ShangYang_S3Prop].iImgNum;
	info.dur = 0.35f / m_stShangYangProp[ShangYang_S3Prop].iImgNum;
	memcpy(&(info.skillInfo), &m_stSkillInfo[RoleAct_SkillThree], sizeof(SkillInfo));

	m_hShangYangFont[id] = FontGuard::create(this, m_stShangYangProp[ShangYang_S3Prop].strPath, info);
	if (NULL != m_hShangYangFont[id])
	{
		m_hShangYangFont[id]->setScale(m_fResScale);
		m_hShangYangFont[id]->setPropPosition(m_stShangYangProp[ShangYang_S3Prop].ptOffset);
		this->getParent()->addChild(m_hShangYangFont[id]);
		m_hShangYangFont[id]->runPropCollisionDetective();
	}
}

/*********************************************************************
** 功能：		移除火焰
** 输入参数：	int id: 火焰id
** 返回值：		无
** 修改记录：	
*********************************************************************/
bool ShangYang::removeFontByID(int id)
{
	bool bRet = false;

	if (NULL != m_hShangYangFont[id])
	{
		m_hShangYangFont[id]->fontOver();
		m_hShangYangFont[id] = NULL;
		bRet = true;
	}

	return bRet;
}

/*********************************************************************
** 功能：		大字计时器
** 输入参数：	float dt
** 返回值：		无
** 修改记录：	
*********************************************************************/
void ShangYang::FontSchedule(float dt)
{
	for (int index = ShangYangS3_One;index < ShangYangS3_Max;index ++)
	{
		removeFontByID(index);
	}
}
/* protected: End */