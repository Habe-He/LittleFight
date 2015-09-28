#include "BaiQi.h"

USING_NS_CC;
using namespace cocostudio;

BaiQi::BaiQi(void)
{
}

BaiQi::~BaiQi(void)
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
void BaiQi::loadArmature()
{
	m_stRoleInfo.arAnimate = Armature::create(m_strRoleName.c_str());
	if (NULL == m_stRoleInfo.arAnimate)
	{
		return;
	}

	this->addChild(m_stRoleInfo.arAnimate);

	/* ע�ᶯ��֡�¼��Ͷ����ص����� */
	m_stRoleInfo.arAnimate->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(BaiQi::actionFrameEventCallFunc, this, std::placeholders::_1
		, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	m_stRoleInfo.arAnimate->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(BaiQi::actionMovementCallFunc, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

/*********************************************************************
** ���ܣ�		�����츳buff
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void BaiQi::initTalentEffect()
{
	Role::initTalentEffect();

	if (true == isRoleLearnedTalent(RoleTalent_ShuangRenJian))	/* ����˫�н� */
	{
		m_stRoleInfo.panel.allHarm += 0.2f;
		m_stRoleInfo.panel.lowerHarm -= 0.1f;
	}
}

/*********************************************************************
** ���ܣ�		�����ص�����
** ���������	
** ����ֵ�� 	
** �޸ļ�¼��	
*********************************************************************/
void BaiQi::actionMovementCallFunc(Armature *ar, MovementEventType type, const std::string& str)
{
	movement(str, type, 0.5f);
}

/*********************************************************************
** ���ܣ�		֡�¼�
** ���������	
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
void BaiQi::actionFrameEventCallFunc(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
{
	frameEvent(evt);

	if (RoleAct_SkillTwo == m_stRoleInfo.actSign)
	{
		if (RoleCreMode_Fighting == m_eRoleCreMode)
		{
			if (getFrameEventName(FrameEvent_Attack) == evt)
			{
				auto ptX = getPositionX();
				setPositionX(ptX - 25 * m_stRoleSubInfo.side);
			}

			if (getFrameEventName(FrameEvent_Attack_FD) == evt)
			{
				auto ptX = getPositionX();
				setPositionX(ptX - 40 * m_stRoleSubInfo.side);
			}
		}
	}

	if (RoleAct_SkillFour == m_stRoleInfo.actSign)
	{
		if (RoleCreMode_Fighting == m_eRoleCreMode)
		{
			if (getFrameEventName(FrameEvent_Attack) == evt)
			{
				auto ptX = getPositionX();
				setPositionX(ptX - 50 * m_stRoleSubInfo.side);
			}

			if (getFrameEventName(FrameEvent_Attack_FD) == evt)
			{
				auto ptX = getPositionX();
				setPositionX(ptX - 80 * m_stRoleSubInfo.side);
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
bool BaiQi::runActionAttack()
{
	bool bRet = Role::runActionAttack();
	if (true == bRet)
	{
		playEffectOgg("C072");	
	}

	return bRet;
}

/*********************************************************************
** ���ܣ�		��ͨ�����ڶ���
** ���������	��
** ����ֵ��		bool:true:����ִ�гɹ�
** �޸ļ�¼��	
*********************************************************************/
bool BaiQi::runActionTwiceAtk()
{
	bool bRet = Role::runActionTwiceAtk();
	if (true == bRet)
	{
		playEffectOgg("C072");	
	}

	return bRet;
}

/*********************************************************************
** ���ܣ�		��ͨ����������
** ���������	��
** ����ֵ��		bool:true:����ִ�гɹ�
** �޸ļ�¼��	
*********************************************************************/
bool BaiQi::runActionThriceAtk()
{
	bool bRet = Role::runActionThriceAtk();
	if (true == bRet)
	{
		playEffectOgg("C005");	
	}

	return bRet;
}

/*********************************************************************
** ���ܣ�		ִ�м���һ
** ���������	��
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
bool BaiQi::runActionSkillOne()
{
	bool bRet = Role::runActionSkillOne();
	if (true == bRet)
	{
		playEffectOgg("016Q");
	}

	return bRet;
}

/*********************************************************************
** ���ܣ�		ִ�м��ܶ�
** ���������	��
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
bool BaiQi::runActionSkillTwo()
{
	bool bRet = Role::runActionSkillTwo();
	if (true == bRet)
	{
		playEffectOgg("162ZH");
	}

	return bRet;
}

/*********************************************************************
** ���ܣ�		ִ�м�����
** ���������	��
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
bool BaiQi::runActionSkillThree()
{
	bool bRet = Role::runActionSkillThree();
	if (true == bRet)
	{
		playEffectOgg("016Q");
	}

	return bRet;
}

/*********************************************************************
** ���ܣ�		ִ�м�����
** ���������	��
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
bool BaiQi::runActionSkillFour()
{
	bool bRet = Role::runActionSkillFour();
	if (true == bRet)
	{
		playEffectOgg("012ZH");
	}

	return bRet;
}
/* ����ִ�� End*/
/* protected: End */