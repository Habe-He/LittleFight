#include "SunWu.h"

USING_NS_CC;
using namespace cocostudio;

SunWu::SunWu(void)
{
}

SunWu::~SunWu(void)
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
void SunWu::loadArmature()
{
	m_stRoleInfo.arAnimate = Armature::create(m_strRoleName.c_str());
	if (NULL == m_stRoleInfo.arAnimate)
	{
		return;
	}

	this->addChild(m_stRoleInfo.arAnimate);

	/* ע�ᶯ��֡�¼��Ͷ����ص����� */
	m_stRoleInfo.arAnimate->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(SunWu::actionFrameEventCallFunc, this, std::placeholders::_1
		, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	m_stRoleInfo.arAnimate->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(SunWu::actionMovementCallFunc, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

/*********************************************************************
** ���ܣ�		��ʼ�����ܷ��е���
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void SunWu::initFlightPropInfo()
{
	m_stSunWuProp.strPath = getFlightPropPath() + "SunWu_S2Prop";
	m_stSunWuProp.ptOffset = Point(180, 80) * m_fResScale;
	m_stSunWuProp.iImgNum = 1;
}

/*********************************************************************
** ���ܣ�		�����ص�����
** ���������	
** ����ֵ�� 	
** �޸ļ�¼��	
*********************************************************************/
void SunWu::actionMovementCallFunc(Armature *ar, MovementEventType type, const std::string& str)
{
	movement(str, type, 0.5f);
}

/*********************************************************************
** ���ܣ�		֡�¼�
** ���������	
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
void SunWu::actionFrameEventCallFunc(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
{
	frameEvent(evt);

	if (RoleAct_SkillOne == m_stRoleInfo.actSign)
	{
		if (RoleCreMode_Fighting == m_eRoleCreMode)
		{
			if (getFrameEventName(FrameEvent_Begin) == evt)
			{
				auto move = MoveBy::create(15.0f / 36.0f, Point(-130, 0) * m_stRoleSubInfo.side);
				runAction(move);
			}
		}
	}

	if (RoleAct_SkillThree == m_stRoleInfo.actSign)
	{
		if (RoleCreMode_Fighting == m_eRoleCreMode)
		{
			if (getFrameEventName(FrameEvent_Begin) == evt)
			{
				auto move = MoveBy::create(12.0f / 36.0f, Point(-170, 0) * m_stRoleSubInfo.side);
				runAction(move);
			}
		}
	}


	if (RoleAct_SkillFour == m_stRoleInfo.actSign)
	{
		if (RoleCreMode_Fighting == m_eRoleCreMode)
		{
			if (getFrameEventName(FrameEvent_Begin) == evt)
			{
				auto move = MoveBy::create(21.0f / 36.0f, Point(-220, 0) * m_stRoleSubInfo.side);
				runAction(move);
			}

			if (getFrameEventName(FrameEvent_Attack_FD) == evt)
			{
				shaky();
			}
		}
	}

	if (getFrameEventName(FrameEvent_Shot_FD) == evt)
	{
		SkillTwo();
	}
}

void SunWu::updateRole()
{
	Role::updateRole();
	
	if (true == isRoleLearnedTalent(RoleTalent_BingJiaZhiZhu))	/* ���䣺����֮�� */
	{
		auto count = 0;
		auto vec = UserData::getInstance()->getRoles();
		for (unsigned int index = 0;index < vec.size();index ++)
		{
			auto role = (Role *)vec[index];
			auto info = role->getRoleInfo();
			if (RoleCamp_Red == info.camp)
			{
				count ++;
			}
			else
			{
				break;
			}
		}

		m_stRoleBuff.atk *= (0.03f * count + 1);
		m_stRoleBuff.pDefend = (0.03f * count + 1) * m_stRoleInfo.panel.pDefend;
		m_stRoleBuff.mDefend = (0.03f * count + 1) * m_stRoleInfo.panel.mDefend;
	}
}

/* ����ִ�� Begin*/
/*********************************************************************
** ���ܣ�		��ͨ������һ��
** ���������	��
** ����ֵ��		bool:true:����ִ�гɹ�
** �޸ļ�¼��	
*********************************************************************/
bool SunWu::runActionAttack()
{
	bool bRet = Role::runActionAttack();
	if (true == bRet)
	{
		playEffectOgg("C2");
	}

	return bRet;
}

/*********************************************************************
** ���ܣ�		��ͨ�����ڶ���
** ���������	��
** ����ֵ��		bool:true:����ִ�гɹ�
** �޸ļ�¼��	
*********************************************************************/
bool SunWu::runActionTwiceAtk()
{
	bool bRet = Role::runActionTwiceAtk();
	if (true == bRet)
	{
		playEffectOgg("C2");
	}

	return bRet;
}

/*********************************************************************
** ���ܣ�		��ͨ����������
** ���������	��
** ����ֵ��		bool:true:����ִ�гɹ�
** �޸ļ�¼��	
*********************************************************************/
bool SunWu::runActionThriceAtk()
{
	bool bRet = Role::runActionThriceAtk();
	if (true == bRet)
	{
		playEffectOgg("C2");
	}

	return bRet;
}

/*********************************************************************
** ���ܣ�		ִ�м���һ
** ���������	��
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
bool SunWu::runActionSkillOne()
{
	bool bRet = Role::runActionSkillOne();
	if (true == bRet)
	{
		playEffectOgg("011Q");
	}

	return bRet;
}

/*********************************************************************
** ���ܣ�		ִ�м��ܶ�
** ���������	��
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
bool SunWu::runActionSkillTwo()
{
	bool bRet = Role::runActionSkillTwo();
	if (true == bRet)
	{
		playEffectOgg("009HY");
	}

	return bRet;
}

/*********************************************************************
** ���ܣ�		ִ�м�����
** ���������	��
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
bool SunWu::runActionSkillThree()
{
	bool bRet = Role::runActionSkillThree();
	if (true == bRet)
	{
		playEffectOgg("009HY");
	}

	return bRet;
}

/*********************************************************************
** ���ܣ�		ִ�м�����
** ���������	��
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
bool SunWu::runActionSkillFour()
{
	bool bRet = Role::runActionSkillFour();
	if (true == bRet)
	{
		playEffectOgg("012ZH");
	}

	return bRet;
}
/* ����ִ�� End*/

void SunWu::SkillTwo()
{
	FlightPropInfo info = {0};
	info.num = m_stSunWuProp.iImgNum;
	memcpy(&(info.skillInfo), &m_stSkillInfo[RoleAct_SkillTwo], sizeof(SkillInfo));

	auto prop = CommonProp::create(this, m_stSunWuProp.strPath, info);
	if (NULL != prop)
	{
		prop->setScaleX(m_stRoleSubInfo.side * m_fResScale);
		prop->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
		prop->setPropPosition(Point(-m_stSunWuProp.ptOffset.x * m_stRoleSubInfo.side, m_stSunWuProp.ptOffset.y));
		prop->setPropFlag();
		this->getParent()->addChild(prop);
		prop->runPropCollisionDetective(0.5f, Point(-m_stSkillInfo[RoleAct_SkillTwo].xAtkDis * m_stRoleSubInfo.side, 0));
	}
}
/* protected: End */