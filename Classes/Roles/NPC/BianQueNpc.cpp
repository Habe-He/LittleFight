#include "BianQueNpc.h"

USING_NS_CC;
using namespace cocostudio;

BianQueNpc::BianQueNpc(void)
	: _curTurning(0)
{
}

BianQueNpc::~BianQueNpc(void)
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
void BianQueNpc::loadArmature()
{
	m_stRoleInfo.arAnimate = Armature::create(m_strRoleName.c_str());
	if (NULL == m_stRoleInfo.arAnimate)
	{
		return;
	}

	this->addChild(m_stRoleInfo.arAnimate);

	/* ע�ᶯ��֡�¼��Ͷ����ص����� */
	m_stRoleInfo.arAnimate->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(BianQueNpc::actionFrameEventCallFunc, this, std::placeholders::_1
		, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	m_stRoleInfo.arAnimate->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(BianQueNpc::actionMovementCallFunc, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

	_dmgValue[0] = 16000;
	_dmgValue[1] = 25000;
	_dmgValue[2] = 30000;
	_dmgValue[3] = 42000;
	_dmgValue[4] = 45000;
	_dmgValue[5] = 50000;
	_dmgValue[6] = 70000;

	this->schedule(schedule_selector(BianQueNpc::runSkill), 10.0f);	/* ÿ10s�ͷż��� */
}

/*********************************************************************
** ���ܣ�		��ʼ����ɫ��������
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void BianQueNpc::initActInherent()
{
	Role::initActInherent();

	m_stActMode[RoleAct_SkillOne] = RoleActMode_Super;			/* ����һ */
	m_stActMode[RoleAct_SkillTwo] = RoleActMode_Super;			/* ���ܶ� */			
	m_stActMode[RoleAct_SkillThree] = RoleActMode_Control;		/* ������ */
}

/*********************************************************************
** ���ܣ�		Boss Ai��������
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void BianQueNpc::aiActSequenceBoss()
{
}

/*********************************************************************
** ���ܣ�		�����ص�����
** ���������	
** ����ֵ�� 	
** �޸ļ�¼��	
*********************************************************************/
void BianQueNpc::actionMovementCallFunc(Armature *ar, MovementEventType type, const std::string& str)
{
	movement(str, type, 0.5f);
}

/*********************************************************************
** ���ܣ�		֡�¼�
** ���������	
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
void BianQueNpc::actionFrameEventCallFunc(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
{
	frameEvent(evt);
}

/*********************************************************************
** ���ܣ�		ִ����ײ���
** ���������	bool bDown:true:����;false:������
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void BianQueNpc::roleCollisionDetective(bool bDown)
{
	bool bFlag = false;
	auto roles = UserData::getInstance()->getRoles();

	for(unsigned int index = 0;index < roles.size();index ++)		/* ���˽�ɫ������ȡ */
	{
		auto role = (Role *)roles[index];
		auto info = role->getRoleInfo();

		if ((RoleStatus_Invincible == info.status) || (m_stRoleInfo.camp == info.camp) || (m_iSceneID != role->getSceneID()))
		{
			continue;												/* �޵С�ͬ��Ӫ������������ *//* С��鲻������ */
		}

		bFlag = true;
		role->roleHurt(this, m_stSkillInfo[RoleAct_SkillOne], bDown);
	}

	if (true == bFlag)
	{
		UserData::getInstance()->setJxxg3Grade(_curTurning);
		m_stSkillInfo[RoleAct_SkillOne].damage = _dmgValue[_curTurning];
	}
}

/*********************************************************************
** ���ܣ�		��ɫAI
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void BianQueNpc::runRoleAI()
{
	if (MaxTurning == _curTurning)									/* ���һ�غ� */
	{
		UserData::getInstance()->removeRole(this);
		runActionDeath();
		return;
	}

	if (0 == UserData::getInstance()->getRedRoleCount())
	{
		this->unscheduleUpdate();
		return;
	}

 	switch (m_eRoleActAi)
 	{
 	case RoleActAi_None:
 		roleAiStep();
 		break;
 	case RoleActAi_ShortMove:										/* AI��Ϊ�̾����ƶ� */
 		roleAiShortMove();
 		break;
 	default:
 		break;
 	}
}

void BianQueNpc::roleAiStep()
{
	if (RoleAct_Idle != m_stRoleInfo.actSign)
	{
		return;
	}

	auto random = ToolFunc::calcRandom(minActAiLimit, m_fActAiLimit[RoleActAi_Sleep]);
	if ((random < m_fActAiLimit[RoleActAi_ShortMove])) 				/* ���� */
	{
		roleAiShortMove();
	}
	else															/* ���� */
	{
		roleAiSleep();
	}
}

/* ����ִ�� Begin*/
void BianQueNpc::runSkill(float dt)
{
	_curTurning++;
	roleUnSchedule(RoleSchedule_AiAction);
	aiActionResume(0.0f);
	runActionSkillOne();
}

/*********************************************************************
** ���ܣ�		ִ�м���һ
** ���������	��
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
bool BianQueNpc::runActionSkillOne()
{
	m_stRoleInfo.status = RoleStatus_Superarmor;					/* �ͷż��ܰ��� */
	bool bRet = Role::runActionSkillOne();
	if (true == bRet)
	{
		playEffectOgg("C035Q");
	}

	return bRet;
}
/* ����ִ�� End*/