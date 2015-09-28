#include "ZouJi.h"
#include "Counterpart/RoleCreate.h"

USING_NS_CC;
using namespace cocostudio;

const float fShadowDuration = 15.0f;				/* �������ʱ�� */

ZouJi::ZouJi(void)
{
}

ZouJi::~ZouJi(void)
{
}

/* public: Begin*/
/* public: End*/

/* protected: Begin */
/*********************************************************************
** ���ܣ�		���ض�����Դ
** ���������	��
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
void ZouJi::loadArmature()
{
	m_stRoleInfo.arAnimate = Armature::create(m_strRoleName.c_str());
	if (NULL == m_stRoleInfo.arAnimate)
	{
		return;
	}

	this->addChild(m_stRoleInfo.arAnimate);

	/* ע�ᶯ��֡�¼��Ͷ����ص����� */
	m_stRoleInfo.arAnimate->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(ZouJi::actionFrameEventCallFunc, this, std::placeholders::_1
		, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	m_stRoleInfo.arAnimate->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(ZouJi::actionMovementCallFunc, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

/*********************************************************************
** ���ܣ�		��ʼ�����ܷ��е���
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void ZouJi::initFlightPropInfo()
{
	m_stZouJiProp.strPath = getFlightPropPath() + "ZouJi_S2Prop";
	m_stZouJiProp.ptOffset = Point(100, 100) * m_fResScale;
	m_stZouJiProp.iImgNum = 4;
}

/*********************************************************************
** ���ܣ�		�����ص�����
** ���������	
** ����ֵ�� 	
** �޸ļ�¼��	
*********************************************************************/
void ZouJi::actionMovementCallFunc(Armature *ar, MovementEventType type, const std::string& str)
{
	movement(str, type, 0.5f);
}

/*********************************************************************
** ���ܣ�		֡�¼�
** ���������	
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
void ZouJi::actionFrameEventCallFunc(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
{
	frameEvent(evt);
	
	if ((evt == getFrameEventName(FrameEvent_Shot)) || (evt == getFrameEventName(FrameEvent_Shot_FD)))
	{
		if (RoleAct_SkillTwo == m_stRoleInfo.actSign)
		{
			SkillTwo();
		}

		if (RoleAct_SkillThree == m_stRoleInfo.actSign)
		{
			if (RoleCreMode_Fighting == m_eRoleCreMode)
			{
				this->unschedule(schedule_selector(ZouJi::ShadowSchedule));
				ShadowSchedule(0.0f);
				SkillThree(100);
				SkillThree(-100);
				this->scheduleOnce(schedule_selector(ZouJi::ShadowSchedule), fShadowDuration);
			}
		}
	}
}

/* ����ִ�� Begin*/
/*********************************************************************
** ���ܣ�		��ͨ������һ��
** ���������	��
** ����ֵ��		bool:true:����ִ�гɹ�
** �޸ļ�¼��	
*********************************************************************/
bool ZouJi::runActionAttack()
{
	if (true == Role::runActionAttack())
	{
		Point ptOffset = ptAtkOffset * m_stRoleSubInfo.side * -0.5f;
		setPosition(getPosition() + ptOffset);
		playEffectOgg("C97");
	}

	return true;
}

/*********************************************************************
** ���ܣ�		��ͨ�����ڶ���
** ���������	��
** ����ֵ��		bool:true:����ִ�гɹ�
** �޸ļ�¼��	
*********************************************************************/
bool ZouJi::runActionTwiceAtk()
{
	if (true == Role::runActionTwiceAtk())
	{
		Point ptOffset = ptAtkOffset * m_stRoleSubInfo.side * -0.5f;
		setPosition(getPosition() + ptOffset);
		playEffectOgg("C97");
	}

	return true;
}

/*********************************************************************
** ���ܣ�		��ͨ����������
** ���������	��
** ����ֵ��		bool:true:����ִ�гɹ�
** �޸ļ�¼��	
*********************************************************************/
bool ZouJi::runActionThriceAtk()
{
	if (true == Role::runActionThriceAtk())
	{
		Point ptOffset = ptAtkOffset * m_stRoleSubInfo.side * -1.0f;
		setPosition(getPosition() + ptOffset);
		playEffectOgg("C97");
	}

	return true;
}

/*********************************************************************
** ���ܣ�		ִ�м���һ
** ���������	��
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
bool ZouJi::runActionSkillOne()
{
	if (true == Role::runActionSkillOne())
	{
		playEffectOgg("132JN");
	}

	return true;
}

/*********************************************************************
** ���ܣ�		ִ�м��ܶ�
** ���������	��
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
bool ZouJi::runActionSkillTwo()
{
	if (true == Role::runActionSkillTwo())
	{
		playEffectOgg("047JN");
	}

	return true;
}

/*********************************************************************
** ���ܣ�		ִ�м�����
** ���������	��
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
bool ZouJi::runActionSkillThree()
{
	if (true == Role::runActionSkillThree())
	{
		playEffectOgg("135");
	}

	return true;
}

/* ����ִ�� End*/

/*********************************************************************
** ���ܣ�		�޼ɼ���2
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void ZouJi::SkillTwo()
{
	FlightPropInfo info = {0};
	info.num = m_stZouJiProp.iImgNum;
	info.dur = 0.1f / m_stZouJiProp.iImgNum;
	memcpy(&(info.skillInfo), &m_stSkillInfo[RoleAct_SkillTwo], sizeof(SkillInfo));

	auto zjProp = CommonProp::create(this, m_stZouJiProp.strPath, info);
	if (NULL != zjProp)
	{
		zjProp->setScaleX(m_stRoleSubInfo.side);
		zjProp->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
		zjProp->setPropPosition(Point(-m_stZouJiProp.ptOffset.x * m_stRoleSubInfo.side, m_stZouJiProp.ptOffset.y));
		this->getParent()->addChild(zjProp);
		zjProp->runPropCollisionDetective(0.5f, Point(-m_stSkillInfo[RoleAct_SkillTwo].xAtkDis * m_stRoleSubInfo.side, 0));
	}
}

/*********************************************************************
** ���ܣ�		�޼ɼ���3
** ���������	float xOffset: ��������ƫ��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void ZouJi::SkillThree(float xOffset)
{
	auto shadow = RoleCreate::create("ZouJi", m_eRoleCreMode);
	this->getParent()->addChild(shadow, 500);
	UserData::getInstance()->addRole(shadow);
	shadow->setMoveRegion(m_rcRegion);
	shadow->setShadowFlag(true);
	shadow->setShadowOwner(m_iRolePkID);

	RolePanel panel;
	memset(&panel, 0, sizeof(RolePanel));
	panel.hpTotal = panel.hpCurrent = m_stRoleInfo.panel.hpTotal / 4;
	panel.atk = m_stRoleInfo.panel.atk / 4;
	panel.pDefend = m_stRoleInfo.panel.pDefend / 4;
	panel.mDefend = m_stRoleInfo.panel.mDefend / 4;
	panel.level = m_stRoleInfo.panel.level;

	shadow->setSceneID(getSceneID());
	shadow->setRolePanel(panel);
	shadow->setStarLv(m_iRoleStarLv);
	shadow->setPosition(Point(getPositionX() + xOffset, getPositionY()));

	auto model = RoleMode_Main;
	if (RoleCamp_Red == m_stRoleInfo.camp)
	{
		model = RoleMode_Companion;
		UserData::getInstance()->checkRedRolecount(true);
	}
	else
	{
		model = RoleMode_Soldier;
		UserData::getInstance()->checkBlackRolecount(m_iSceneID, true);
	}
	shadow->initRoleInfo(m_stRoleInfo.camp, model, RoleRace_Wizard);

	SkillInfo skillInfo[RoleAct_Max] = {0};
	memcpy(&skillInfo, &m_stSkillInfo, sizeof(SkillInfo) * RoleAct_Max);
	skillInfo[RoleAct_SkillOne].level = 0;
	skillInfo[RoleAct_SkillTwo].level = 0;
	skillInfo[RoleAct_SkillThree].level = 0;
	skillInfo[RoleAct_SkillFour].level = 0;
	shadow->setRoleSkillInfo(skillInfo);
}

/*********************************************************************
** ���ܣ�		�����ʱ��
** ���������	float dt
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void ZouJi::ShadowSchedule(float dt)
{
	auto roles = UserData::getInstance()->getRoles();
	for (unsigned index = 0;index < roles.size();index++)
	{
		auto role = (Role *)roles[index];
		if ((true == role->getShadowFlag()) && (m_iRolePkID == role->getShadowOwner()))
		{
			role->runRoleAction(RoleAct_Death);
		}
	}
}

/*********************************************************************
** ���ܣ�		������ص�
** ���������	��
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
void ZouJi::deathEffectCallBack()
{
	if (true == m_bShadow)											/* ���� */
	{
		if (RoleCamp_Red == m_stRoleInfo.camp)						/* ˢ�½�ɫ���� */
		{
			UserData::getInstance()->checkRedRolecount();
		}
		else
		{
			UserData::getInstance()->checkBlackRolecount(m_iSceneID);
		}
		UserData::getInstance()->removeRole(this);
		m_nAureoleEffect->removeFromParentAndCleanup(true);
		this->removeFromParentAndCleanup(true);
	}
	else
	{
		Role::deathEffectCallBack();
	}
}
/* protected: End */