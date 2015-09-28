#include "GongSunYan.h"

USING_NS_CC;
using namespace cocostudio;

GongSunYan::GongSunYan(void)
{
}

GongSunYan::~GongSunYan(void)
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
void GongSunYan::loadArmature()
{
	m_stRoleInfo.arAnimate = Armature::create(m_strRoleName.c_str());
	if (NULL == m_stRoleInfo.arAnimate)
	{
		return;
	}

	this->addChild(m_stRoleInfo.arAnimate);

	/* ע�ᶯ��֡�¼��Ͷ����ص����� */
	m_stRoleInfo.arAnimate->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(GongSunYan::actionFrameEventCallFunc, this, std::placeholders::_1
		, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	m_stRoleInfo.arAnimate->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(GongSunYan::actionMovementCallFunc, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

/*********************************************************************
** ���ܣ�		Boss Ai��������
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void GongSunYan::aiActSequenceBoss()
{
	if ((RoleCreMode_XueGong2 == m_eRoleCreMode) && (RoleCamp_Black == m_stRoleInfo.camp))
	{
		/* ���ѧ��ģʽ2���з���ɫ */
		m_vctAiActSeq.clear();

		int sNum = 0;												/* �����ļ����� */
		int skill[4] = {0};											/* �����ļ��� */
		for (int index = RoleAct_SkillOne;index <= RoleAct_SkillFour;index ++)
		{
			if (0 < m_stSkillInfo[index].level)
			{
				skill[sNum ++] = index;
			}
		}

		RoleActSign act = RoleAct_Idle;
		if (0 != sNum)
		{
			act = (RoleActSign)ToolFunc::calcRandom(0, sNum - 1);
			m_vctAiActSeq.push_back((RoleActSign)skill[act]);
		}

		m_vctAiActSeq.push_back(RoleAct_Attack);
		m_vctAiActSeq.push_back(RoleAct_Twice_Atk);
		m_vctAiActSeq.push_back(RoleAct_Thrice_Atk);
	}
	else
	{
		Role::aiActSequenceBoss();
	}
}

/*********************************************************************
** ���ܣ�		�����ص�����
** ���������	
** ����ֵ�� 	
** �޸ļ�¼��	
*********************************************************************/
void GongSunYan::actionMovementCallFunc(Armature *ar, MovementEventType type, const std::string& str)
{
	movement(str, type, 0.5f);
}

/*********************************************************************
** ���ܣ�		֡�¼�
** ���������	
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
void GongSunYan::actionFrameEventCallFunc(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
{
	frameEvent(evt);

	if (RoleAct_SkillOne == m_stRoleInfo.actSign)
	{
		if (RoleCreMode_Fighting == m_eRoleCreMode)
		{
			if (getFrameEventName(FrameEvent_Attack) == evt)
			{
				auto ptX = getPositionX();
				setPositionX(ptX - 150 * m_stRoleSubInfo.side);
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
bool GongSunYan::runActionAttack()
{
	bool bRet = Role::runActionAttack();
	if (true == bRet)
	{
		playEffectOgg("C1");
	}

	return bRet;
}

/*********************************************************************
** ���ܣ�		��ͨ�����ڶ���
** ���������	��
** ����ֵ��		bool:true:����ִ�гɹ�
** �޸ļ�¼��	
*********************************************************************/
bool GongSunYan::runActionTwiceAtk()
{
	bool bRet = Role::runActionTwiceAtk();
	if (true == bRet)
	{
		playEffectOgg("C1");
	}

	return bRet;
}

/*********************************************************************
** ���ܣ�		��ͨ����������
** ���������	��
** ����ֵ��		bool:true:����ִ�гɹ�
** �޸ļ�¼��	
*********************************************************************/
bool GongSunYan::runActionThriceAtk()
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
bool GongSunYan::runActionSkillOne()
{
	bool bRet = Role::runActionSkillOne();
	if (true == bRet)
	{
		playEffectOgg("CJ");
	}

	return bRet;
}

/*********************************************************************
** ���ܣ�		ִ�м��ܶ�
** ���������	��
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
bool GongSunYan::runActionSkillTwo()
{
	bool bRet = Role::runActionSkillTwo();
	if (true == bRet)
	{
		playEffectOgg("012TD");
	}

	return bRet;
}
/* ����ִ�� End*/
/* protected: End */