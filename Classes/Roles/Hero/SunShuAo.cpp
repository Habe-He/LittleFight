#include "SunShuAo.h"
#include "Counterpart/Counterpart_Def.h"

USING_NS_CC;
using namespace cocostudio;

SunShuAo::SunShuAo(void)
{
}

SunShuAo::~SunShuAo(void)
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
void SunShuAo::loadArmature()
{
	m_stRoleInfo.arAnimate = Armature::create(m_strRoleName.c_str());
	if (NULL == m_stRoleInfo.arAnimate)
	{
		return;
	}

	this->addChild(m_stRoleInfo.arAnimate);

	/* ע�ᶯ��֡�¼��Ͷ����ص����� */
	m_stRoleInfo.arAnimate->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(SunShuAo::actionFrameEventCallFunc, this, std::placeholders::_1
		, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	m_stRoleInfo.arAnimate->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(SunShuAo::actionMovementCallFunc, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

/*********************************************************************
** ���ܣ�		�����츳buff
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void SunShuAo::initTalentEffect()
{
	Role::initTalentEffect();

	if (true == isRoleLearnedTalent(RoleTalent_JiLi))	/* ���尽������ */
	{
		int index = 0;
		for (index = RoleAct_SkillOne;index <= RoleAct_SkillFour;index++)
		{
			m_stSkillInfo[index].cd *= 0.85f;
		}

		resetUISkillBtnCD();
	}
}

/*********************************************************************
** ���ܣ�		�����ص�����
** ���������	
** ����ֵ�� 	
** �޸ļ�¼��	
*********************************************************************/
void SunShuAo::actionMovementCallFunc(Armature *ar, MovementEventType type, const std::string& str)
{
	movement(str, type, 0.5f);
}

/*********************************************************************
** ���ܣ�		֡�¼�
** ���������	
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
void SunShuAo::actionFrameEventCallFunc(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
{
	frameEvent(evt);
	
	if (RoleAct_SkillOne == m_stRoleInfo.actSign)
	{
		if (getFrameEventName(FrameEvent_Begin) == evt)
		{
			auto move = MoveBy::create(6.0f / 36.0f, Point(-100, 0) * m_stRoleSubInfo.side);
			runAction(move);
		}
	}

	if (RoleAct_SkillTwo == m_stRoleInfo.actSign)
	{
		if (getFrameEventName(FrameEvent_Begin) == evt)
		{
			auto move = MoveBy::create(15.0f / 36.0f, Point(-50, 0) * m_stRoleSubInfo.side);
			runAction(move);
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
bool SunShuAo::runActionAttack()
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
bool SunShuAo::runActionTwiceAtk()
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
bool SunShuAo::runActionThriceAtk()
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
bool SunShuAo::runActionSkillOne()
{
	bool bRet = Role::runActionSkillOne();
	if (true == bRet)
	{
		playEffectOgg("009CJ");
	}

	return bRet;
}

/*********************************************************************
** ���ܣ�		ִ�м��ܶ�
** ���������	��
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
bool SunShuAo::runActionSkillTwo()
{
	bool bRet = Role::runActionSkillTwo();
	if (true == bRet)
	{
		playEffectOgg("016HY");
	}

	return bRet;
}

/*********************************************************************
** ���ܣ�		ִ�м�����
** ���������	��
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
bool SunShuAo::runActionSkillThree()
{
	bool bRet = Role::runActionSkillThree();
	if (true == bRet)
	{
		playEffectOgg("004R");
	}

	return bRet;
}

/*********************************************************************
** ���ܣ�		ִ�м�����
** ���������	��
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
bool SunShuAo::runActionSkillFour()
{
	bool bRet = Role::runActionSkillFour();
	if (true == bRet)
	{
		playEffectOgg("014ZH2");
	}

	return bRet;
}
/* ����ִ�� End*/
/* protected: End */