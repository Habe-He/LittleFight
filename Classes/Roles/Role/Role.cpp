#include "Role.h"
#include "Counterpart/Counterpart_Def.h"
#include "Counterpart/MainFight.h"
#include "DataManager/DataManager.h"

USING_NS_CC;
using namespace cocostudio;

/* ����֡�¼� */
const std::string strFrameEventName[FrameEvent_Max] = 
{
	"begin",										/* ����׼����ϣ���ʼ���壩 */
	"end",											/* ������ʼ���У��������壩 */
	"attack",										/* �����¼��������أ� */
	"attack-fd",									/* �����¼������أ� */
	"shot",											/* �����¼��������أ� */
	"shot-fd",										/* �����¼������أ� */
	"invincible",									/* �޵��¼� */
	"interrupt",									/* �ж϶����¼� */
	"left",											/* ��������: ǰ */
	"middle",										/* ��������: ǰ��˫���� */
	"right",										/* ��������: �� */
};

/* ���ܶ������� */
const std::string strRoleSkillName[RoleAct_Max] =
{
	"loading",
	"attack",
	"twice-atk",									/* ������ */
	"thrice-atk",									/* ������ */
	"run",
	"sa",
	"sb",
	"sc",
	"sd",
	"smitten",										/* ���� */
	"down",											/* ���� */
	"down"
};

const std::string strFlightPropPath = "Roles/FlightProps/";	/* ��Դ·�� */
const float RaceFactor[RoleRace_Max] = {0.0f, 1.2f, 1.0f, 0.8f};	/* ְҵӰ�켼�ܱ��� */

Role::Role()
{
}

Role::~Role(void)
{
}

/*********************************************************************
** ���ܣ�		��ʼ����ɫ����
** ���������	std::string strName: ��ɫ����
**				RoleCreMode mode: ��ɫ����ģʽ
**				float resScale: ��Դ���ű���
** ����ֵ��		bool
** �޸ļ�¼��	
*********************************************************************/
bool Role::init(std::string strName, RoleCreMode mode, float resScale)
{
	m_iRolePkID = 0;
	m_iRoleID = 0;
	m_iRoleStarLv = 0;
	m_strRoleName = strName;
	m_eRoleCreMode = mode;
	m_fResScale = resScale;

	m_iSceneID = 0;
	m_iRoleCombo = 0;
	m_ptMoveDir = ptInvalid;
	m_ptMoveDir = ptInvalid;
	m_eRoleWarMsg = RoleWarMsg_None;
	m_eRoleActAi = RoleActAi_None;
	m_ehealthSign = RoleHealth_RedNormal;
	m_iAiActSeqIndex = m_vctAiActSeq.size();
	m_bRoleActBreak = false;
	m_bShadow = false;
	_roleHealth = NULL;
	m_nHealth = NULL;
	m_iShadowOwner = 0;

	m_nAureoleEffect = Node::create();
	
	memset(&m_stRoleInfo, 0, sizeof(RoleInfo));
	memset(m_fActCD, 0, sizeof(m_fActCD));
	memset(&m_stRoleBuff, 0, sizeof(RoleBuff));

	initActInherent();												/* ��ʼ����ɫ�������� */
	initFlightPropInfo();											/* ��ʼ�����ܷ��е��� */
	loadArmature();
	runActionIdle();	
	initSubInfo();
	initSkillRegion();

	if (RoleCreMode_Preview == m_eRoleCreMode)						/* Ԥ��ģʽ */
	{
		setRoleTurnedDirInfo(RoleDir_Right);
	}
	else
	{
		setRoleTurnedDirInfo(RoleDir_Left);
	}

	return true;
}

/*********************************************************************
** ���ܣ�		ִ�н�ɫ����
** ���������	RoleActSign act������
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
bool Role::runRoleAction(RoleActSign act)
{
	bool bRet = false;

	switch ( act)
	{
	case RoleAct_Idle:												/* ���� */
		bRet = runActionIdle();
		break;
	case RoleAct_Move:												/* �ƶ� */
		bRet = runActionMove();
		break;
	case RoleAct_Attack:											/* ���� */
	case RoleAct_Twice_Atk:
	case RoleAct_Thrice_Atk:
		bRet = runActionAtkCtrl();
		break;
	case RoleAct_Smitten:											/* ���� */
		bRet = runActionSmitten();
		break;
	case RoleAct_Down:												/* ���� */
		bRet = runActionDown();
		break;
	case RoleAct_Death:												/* ���� */
		bRet = runActionDeath();
		break;
	case RoleAct_SkillOne:											/* ����һ */
		bRet = runActionSkillOne();
		break;
	case RoleAct_SkillTwo:											/* ���ܶ� */
		bRet = runActionSkillTwo();
		break;
	case RoleAct_SkillThree:										/* ������ */
		bRet = runActionSkillThree();
		break;
	case RoleAct_SkillFour:											/* ������ */
		bRet = runActionSkillFour();
		break;
	}

	return bRet;
}

/*********************************************************************
** ���ܣ�		ִ�ж��������������ӿڣ�
** ���������	RoleCmdSign cmd��ָ��ID
**				Point ptMove: �ƶ�Ŀ�ĵ�
** ����ֵ��		bool
** �޸ļ�¼��	
*********************************************************************/
bool Role::runLordlAction(RoleCmdSign cmd, Point ptMove)
{
	if ((RoleCondition_Normal != m_stRoleInfo.condition) ||			/* �쳣״̬������ */
		(0 == UserData::getInstance()->getBlackRoleCount(m_iSceneID)))
	{
		return false;
	}

	RoleActSign act = RoleAct_Max;
	switch (cmd)
	{
	case RoleCmdSign_Move:											/* �ƶ� */
		setMoveVector(ptMove);
		m_ptMoveDes = ptMove;
		act = RoleAct_Move;
		break;
	case RoleCmdSign_Attack:										/* ���� */
		act = RoleAct_Attack;
		break;
	case RoleCmdSign_SkillOne:										/* ����һ */
		act = RoleAct_SkillOne;
		break;
	case RoleCmdSign_SkillTwo:										/* ���ܶ� */
		act = RoleAct_SkillTwo;
		break;
	case RoleCmdSign_SkillThree:									/* ������ */
		act = RoleAct_SkillThree;
		break;
	case RoleCmdSign_SkillFour:										/* ������ */
		act = RoleAct_SkillFour;
		break;
	case RoleCmdSign_Release:
		act = RoleAct_Idle;
		break;
	}

	return runRoleAction(act);
}

/*********************************************************************
** ���ܣ�		��ʼ����ɫ��Ϣ
** ���������	role_camp camp:��Ӫ
**				RoleModel mode:����
**				RoleRace race: ��ɫְҵ
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
void Role::initRoleInfo(RoleCamp camp, RoleMode mode, RoleRace race)
{
	m_stRoleInfo.actSign = RoleAct_Idle;
	m_stRoleInfo.condition = RoleCondition_Normal;
	m_stRoleInfo.camp = camp;
	m_stRoleInfo.mode = mode;
	m_stRoleInfo.race = race;
	m_stRoleInfo.status = RoleStatus_Normal;

	initActAiLimit();												/* ����Ai��Ϊ�ĸ��� */

	if (RoleCamp_Red == camp)										/* �ҷ����� */
	{
		setRoleTurnedDirInfo(RoleDir_Right);
	}
	else
	{
		initHealthBar();
	}

	setAiActionSequence();

	if (RoleCreMode_Preview != m_eRoleCreMode)
	{
		playAureoleEffect();
	}	
}

/*********************************************************************
** ���ܣ�		�����츳buff
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void Role::initTalentEffect()
{
	DataManager::getInstance()->isGetTalentDate(m_iRolePkID);	/* ��ȡ�츳 */
	auto talent = DataManager::getInstance()->interTalentVectors();
	for (unsigned int index = 0;index < talent.size();index++)
	{
		m_stRoleInfo.panel.talent = (m_stRoleInfo.panel.talent << 8) | (talent[index] - 70000);
	}

	if (0 == m_stRoleInfo.panel.talent)							/* ���츳 */
	{
		return;
	}

	if (true == isRoleLearnedTalent(RoleTalent_ShiHua))			/* ʯ�� */
	{
		m_stRoleInfo.panel.pDefend *= 1.04f;
		m_stRoleInfo.panel.mDefend *= 1.04f;
	}
	if (true == isRoleLearnedTalent(RoleTalent_FuSuZhiFeng))	/* ����֮�� */
	{
		m_stRoleInfo.panel.hpBack += 12;
	}
	if (true == isRoleLearnedTalent(RoleTalent_GeDang))			/* �� */
	{
		m_stRoleInfo.panel.lowerHarm += 0.03f;
	}
	if (true == isRoleLearnedTalent(RoleTalent_XueYeFeiTeng))	/* ѪҺ���� */
	{
		m_stRoleInfo.panel.hpTotal *= 1.06f;
	}
	if (true == isRoleLearnedTalent(RoleTalent_JuRen))			/* ���� */
	{
		auto vec = UserData::getInstance()->getRoles();
		for (unsigned int index = 0;index < vec.size();index ++)
		{
			auto role = (Role *)vec[index];
			auto info = role->getRoleInfo();
			if ((RoleCamp_Red == info.camp) && (RoleRace_Power == info.race))
			{
				info.panel.allHarm += 0.08f;
				role->setRoleInfo(info);
			}
		}
	}
	if (true == isRoleLearnedTalent(RoleTalent_QianFeng))		/* ǰ�� */
	{
		m_stRoleInfo.panel.atk *= 1.04f;
	}
	if (true == isRoleLearnedTalent(RoleTalent_ZhengMianDuiJue))/* ����Ծ� */
	{
		m_stRoleInfo.panel.speedHarm += 0.06f;
	}
	if (true == isRoleLearnedTalent(RoleTalent_PoZaiMeiJie))	/* ����ü�� */
	{
		this->schedule(schedule_selector(Role::buffHarmGrow), 20.0f);
	}
	if (true == isRoleLearnedTalent(RoleTalent_LiLiangBaoFa))	/* �������� */
	{
		m_stRoleInfo.panel.atk += 75;
	}
	if (true == isRoleLearnedTalent(RoleTalent_FuWenHuDun))		/* ���Ļ��� */
	{
		m_stRoleInfo.panel.shield = m_stRoleInfo.panel.hpTotal * 0.1f;
	}
	if (true == isRoleLearnedTalent(RoleTalent_PoMoZhiRen))		/* ��ħ֮�� */
	{
		auto vec = UserData::getInstance()->getRoles();
		for (unsigned int index = 0;index < vec.size();index ++)
		{
			auto role = (Role *)vec[index];
			auto info = role->getRoleInfo();
			if ((RoleCamp_Red == info.camp) && (RoleRace_Speed == info.race))
			{
				info.panel.allHarm += 0.05f;
				role->setRoleInfo(info);
			}
		}
	}
	if (true == isRoleLearnedTalent(RoleTalent_DunQiang))		/* ��ǽ */
	{
		m_stRoleInfo.panel.lowerHarm += 0.05f;
	}
	if (true == isRoleLearnedTalent(RoleTalent_WuShiLieRen))	/* ��ʦ���� */
	{
		m_stRoleInfo.panel.wizardHarm += 0.06f;
	}
	if (true == isRoleLearnedTalent(RoleTalent_KuangNu))		/* ��ŭ */
	{
		m_stRoleInfo.panel.atk *= 1.05f;
	}
	if (true == isRoleLearnedTalent(RoleTalent_GongFaJianBei))	/* �����汸 */
	{
		auto vec = UserData::getInstance()->getRoles();
		for (unsigned int index = 0;index < vec.size();index ++)
		{
			auto role = (Role *)vec[index];
			auto info = role->getRoleInfo();
			if ((RoleCamp_Red == info.camp) && (RoleRace_Wizard == info.race))
			{
				info.panel.atk += 0.05f;
				role->setRoleInfo(info);
			}
		}
	}
	if (true == isRoleLearnedTalent(RoleTalent_CaoYaoZhuanJia))	/* ��ҩר�� */
	{
		this->schedule(schedule_selector(Role::buffHpBack), 25.0f);
	}
	if (true == isRoleLearnedTalent(RoleTalent_ZhiYu))			/* ���� */
	{
		m_stRoleInfo.panel.hpBack += m_stRoleInfo.panel.hpTotal * 0.01f;
	}
	if (true == isRoleLearnedTalent(RoleTalent_YinMouJia))		/* ��ı�� */
	{
		m_stRoleInfo.panel.powerHarm += 0.06f;
	}
}

/*********************************************************************
** ���ܣ�		���ý�ɫ��Ϣ
** ���������	RoleInfo info: ��ɫ��Ϣ
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
void Role::setRoleInfo(RoleInfo info)
{
	memset(&m_stRoleInfo, 0, sizeof(RoleInfo));
	memcpy(&m_stRoleInfo, &info, sizeof(RoleInfo));
}

/*********************************************************************
** ���ܣ�		���ý�ɫbuff
** ���������	RoleBuff buff: ��ɫ��Ϣ
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
void Role::setRoleBuff(RoleBuff buff)
{
	memset(&m_stRoleBuff, 0, sizeof(RoleBuff));
	memcpy(&m_stRoleBuff, &buff, sizeof(RoleBuff));
}

/*********************************************************************
** ���ܣ�		��ɫ��������
** ���������	RolePanel panel: ��ɫ����
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
void Role::setRolePanel(RolePanel panel)
{
	memset(&(m_stRoleInfo.panel), 0, sizeof(RolePanel));
	memcpy(&(m_stRoleInfo.panel), &panel, sizeof(RolePanel));
}

/*********************************************************************
** ���ܣ�		��ɫ��������
** ���������	SkillInfo *info: ��ɫ��������
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
void Role::setRoleSkillInfo(SkillInfo *info)
{
	memset(m_stSkillInfo, 0, sizeof(SkillInfo) * RoleAct_Max);
	memcpy(m_stSkillInfo, info, sizeof(SkillInfo) * RoleAct_Max);
}

/*********************************************************************
** ���ܣ�		hp�ָ�
** ���������	int hp: hp�ظ���
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void Role::setRoleHpUp(int hp)
{
	m_stRoleBuff.hpBack += hp;
	m_ehealthSign = RoleHealth_Up;
	showRoleHealthChange(hp);
}

/*********************************************************************
** ���ܣ�		�쳣״̬����
** ���������	RoleCondition condition: �쳣״̬
**				float dt: �쳣״̬����ʱ��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void Role::setRoleCondition(RoleCondition condition, float dt)
{
	stopArmatureAction();

	if (condition > m_stRoleInfo.condition)						/* �쳣״̬�����ȼ����� */
	{
		roleUnSchedule(RoleSchedule_Condition);
		m_stRoleInfo.condition = condition;
		m_eRoleActAi = RoleActAi_None;
		roleSchedule(dt, RoleSchedule_Condition);
	}
}

/*********************************************************************
** ���ܣ�		�쳣״̬����
** ���������	int damage: �쳣״̬����
**				float dt: �˺�����ʱ��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void Role::setRoleAbnormalDamage(int damage, float dt)
{
	roleUnSchedule(RoleSchedule_Abnormal);
	roleSchedule(dt, RoleSchedule_Abnormal);
}

/*********************************************************************
** ���ܣ�		���ý�ɫ����cd
** ���������	RoleActSign act: ����id
**				float cd: cdֵ
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void Role::setActionCD(RoleActSign act, float cd)
{
	m_fActCD[act] = 0.0f;
}

/*********************************************************************
** ���ܣ�		�佫����ID
** ���������	int pk: �佫����ID
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void Role::setRolePkID(int pk)
{
	m_iRolePkID = pk;
	auto property = DataManager::getInstance()->interGeneralVector();/* ��ȡ�佫��Ϣ */

	/* װ�� */
	DataManager::getInstance()->equipDataParser();
	auto equips = DataManager::getInstance()->localEquipProptyVector();
	auto evoRule = DataManager::getInstance()->localEquipRefineVector();
	
	for (int index = 0;index < 6;index ++)							/* ���� */
	{
		if (0 == property[0].equipID[index])
		{
			continue;
		}

		auto equip = equips[property[0].equipID[index] - 94001];
		if (index < 4)												/* 4���չ�װ�� */
		{
			double add[EquipGradeMax] = {0.1f, 0.2f, 0.2f, 0.3f};
			double factor[EquipGradeMax] = {0.008f, 0.01f, 0.01f, 0.01};

			auto improve = add[equip.eColor] + (property[0].equipLevel[index] - 1) * factor[equip.eColor];
			improve = improve + 1;

			m_stRoleInfo.panel.hpTotal += equip.eHP * improve;
			m_stRoleInfo.panel.hpCurrent = m_stRoleInfo.panel.hpTotal;
			m_stRoleInfo.panel.atk += equip.eAtk * improve;
			m_stRoleInfo.panel.pDefend += equip.ePD * improve;
			m_stRoleInfo.panel.mDefend += equip.eMD * improve;
		}
		else														/* 2�������챦 */
		{
			if (4 == index)
			{
				m_stRoleInfo.panel.critical = m_stRoleInfo.panel.critical + evoRule[property[0].equipLevel[index]].eGrow1[equip.eColor] * 100;
				m_stRoleInfo.panel.criDefend = m_stRoleInfo.panel.criDefend + evoRule[property[0].equipLevel[index]].eGrow1[equip.eColor] * 100;
			}
			else
			{
				m_stRoleInfo.panel.realAtk = m_stRoleInfo.panel.realAtk + evoRule[property[0].equipLevel[index]].eGrow2[equip.eColor] * 100;
				m_stRoleInfo.panel.realAtkDefend = m_stRoleInfo.panel.realAtkDefend + evoRule[property[0].equipLevel[index]].eGrow2[equip.eColor] * 100;
			}
		}
	}
}

/*********************************************************************
** ���ܣ�		�佫����ID
** ���������	��
** ����ֵ��		int pk: �佫����ID
** �޸ļ�¼��	
*********************************************************************/
int Role::getRolePkID()
{
	return m_iRolePkID;
}

/*********************************************************************
** ���ܣ�		�佫ID
** ���������	int id: �佫ID
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void Role::setRoleID(int id)
{
	m_iRoleID = id;
	
	DataManager::getInstance()->SkillNameDataParser();				/* ���ܻ����� */
	auto skills = DataManager::getInstance()->localSkillNameVector();

	initSkillGains();
	initJxxgBuff();

	//������*��1-����/(����+�ȼ�*73+877����+�ȼ�*80*0.8	�˺���ʽ����
	auto panel = m_stRoleInfo.panel;
	auto baseDamage = panel.atk * (1 - panel.mDefend * 1.0f / (panel.mDefend + panel.level * 73 + 877)) + panel.level * 64;

	//DataManager::getInstance()->SkillUpgradeDataParser();			/* ������������ */
	//auto skillRule = DataManager::getInstance()->localSkillUpgradeVector();

	for (unsigned int skillIndex = 0;skillIndex < skills.size();skillIndex++)
	{
		auto skillInfo = skills[skillIndex];
		auto skillName = skillInfo.sANameS;
		if (0 != strstr(skillName, m_strRoleName.c_str()))
		{
			m_stSkillInfo[RoleAct_SkillOne].cd = skillInfo.sACD;
			m_stSkillInfo[RoleAct_SkillOne].damage = baseDamage;
			memcpy(&m_stSkillInfo[RoleAct_SkillOne].name, skillInfo.sANameS, sizeof(skillInfo.sANameS));

			m_stSkillInfo[RoleAct_SkillTwo].cd = skillInfo.sBCD;
			m_stSkillInfo[RoleAct_SkillTwo].damage = baseDamage * 1.1f;
			memcpy(&m_stSkillInfo[RoleAct_SkillTwo].name, skillInfo.sBNameS, sizeof(skillInfo.sBNameS));

			m_stSkillInfo[RoleAct_SkillThree].cd = skillInfo.sCCD;
			m_stSkillInfo[RoleAct_SkillThree].damage = baseDamage * 1.2f;
			memcpy(&m_stSkillInfo[RoleAct_SkillThree].name, skillInfo.sCNameS, sizeof(skillInfo.sCNameS));

			m_stSkillInfo[RoleAct_SkillFour].cd = skillInfo.sDCD;
			m_stSkillInfo[RoleAct_SkillFour].damage = baseDamage * 1.4f;
			memcpy(&m_stSkillInfo[RoleAct_SkillFour].name, skillInfo.sDNameS, sizeof(skillInfo.sDNameS));
			break;
		}
	}

	m_stSkillInfo[RoleAct_Attack].damage = m_stRoleInfo.panel.atk;
	m_stSkillInfo[RoleAct_Twice_Atk].damage = m_stRoleInfo.panel.atk * 1.2f;
	m_stSkillInfo[RoleAct_Thrice_Atk].damage = m_stRoleInfo.panel.atk * 1.5f;
}

/*********************************************************************
** ���ܣ�		�佫ID
** ���������	��
** ����ֵ��		int: �佫ID
** �޸ļ�¼��	
*********************************************************************/
int Role::getRoleID()
{
	return m_iRoleID;
}

/*********************************************************************
** ���ܣ�		��ɫ��Ϣ��ȡ
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
RoleInfo Role::getRoleInfo()
{
	return m_stRoleInfo;
}

/*********************************************************************
** ���ܣ�		��ȡbuff
** ���������	��
** ����ֵ��		RoleBuff:
** �޸ļ�¼��	
*********************************************************************/
RoleBuff Role::getRoleBuff()
{
	return m_stRoleBuff;
}

/*********************************************************************
** ���ܣ�		��ȡ��ɫ��������
** ���������	��
** ����ֵ��		SkillInfo* : ��ɫ��������
** �޸ļ�¼��	
*********************************************************************/
SkillInfo* Role::getRoleSkillInfo()
{
	return m_stSkillInfo;
}

/*********************************************************************
** ���ܣ�		���ý��漼�ܰ�ť���õ�cd
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void Role::resetUISkillBtnCD()
{
	if (RoleMode_Main == m_stRoleInfo.mode)		/* ���� */
	{
		auto roleLayer = this->getParent();			/* ��ȡ��ɫ�� */
		auto fight = (MainFight*)roleLayer->getParent()->getChildByTag(order_MainFight);
		for (int index = MFCtrl_Sa;index <= MFCtrl_Sd;index ++)
		{
			fight->resetActCD(index, m_stSkillInfo[index + RoleAct_SkillOne - MFCtrl_Sa].cd);
		}
	}
}

/*********************************************************************
** ���ܣ�		���ö�������
** ���������	float speed: ����
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void Role::setAnimateSpeed(float speed)
{
	m_stRoleInfo.arAnimate->getAnimation()->setSpeedScale(speed);
}

/*********************************************************************
** ���ܣ�		����
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void Role::backToLife()
{
	if (RoleStatus_Death == m_stRoleInfo.status)
	{
		this->scheduleUpdate();
		this->setVisible(true);
		m_nAureoleEffect->setVisible(true);
		m_stRoleInfo.actSign = RoleAct_Idle;
	}
	m_stRoleInfo.status = RoleStatus_Normal;
	m_stRoleInfo.panel.hpCurrent = m_stRoleInfo.panel.hpTotal;
	UserData::getInstance()->checkRedRolecount(true);

	runActionIdle();
}

/* ���ý�ɫHP��MP��ʾ�ؼ� */
void Role::setHealthCtrl(Node *health)
{
	m_nHealth = health;
}

/* ��ȡ��ɫHP��MP��ʾ�ؼ� */
void Role::removeHealthCtrl()
{
	if (NULL != m_nHealth)
	{
		m_nHealth->removeFromParentAndCleanup(true);
		m_nHealth = NULL;
	}
}

/*********************************************************************
** ���ܣ�		����Ai��������
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void Role::aiActSequenceSoldier()
{
	m_vctAiActSeq.clear();
	m_vctAiActSeq.push_back(RoleAct_Attack);
}

/*********************************************************************
** ���ܣ�		С���Ai��������
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void Role::aiActSequenceCompanion()
{
	m_vctAiActSeq.clear();
	auto random = ToolFunc::calcRandom(minActAiLimit, maxActAiLimit);

	random = ToolFunc::calcRandom(minActAiLimit, maxActAiLimit);
	if (random > maxActAiLimit / 2)
	{
		m_vctAiActSeq.push_back(RoleAct_Attack);
		m_vctAiActSeq.push_back(RoleAct_Twice_Atk);	
	}

	random = ToolFunc::calcRandom(minActAiLimit, maxActAiLimit);
	if (random < maxActAiLimit * 4 / 5)
	{
		m_vctAiActSeq.push_back(RoleAct_Thrice_Atk);
	}

	random = ToolFunc::calcRandom(minActAiLimit, maxActAiLimit);
	if (random > maxActAiLimit * 3 / 4)							/* ȡ1������ */
	{
		int sNum = 0;												/* �����ļ����� */
		int skill[4] = {0};											/* �����ļ��� */
		for (int index = RoleAct_SkillOne;index <= RoleAct_SkillFour;index ++)
		{
			if ((0 < m_stSkillInfo[index].level) && (m_fActCD[index] <= 0))
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
	}
}

/*********************************************************************
** ���ܣ�		Boss Ai��������
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void Role::aiActSequenceBoss()
{
	m_vctAiActSeq.clear();
	auto random = ToolFunc::calcRandom(minActAiLimit, maxActAiLimit);
	if (random > maxActAiLimit / 2)
	{
		m_vctAiActSeq.push_back(RoleAct_Attack);
		m_vctAiActSeq.push_back(RoleAct_Twice_Atk);	
	}

	random = ToolFunc::calcRandom(minActAiLimit, maxActAiLimit);
	if (random < maxActAiLimit / 2)
	{
		int sNum = 0;												/* �����ļ����� */
		int skill[4] = {0};											/* �����ļ��� */
		for (int index = RoleAct_SkillOne;index <= RoleAct_SkillFour;index ++)
		{
			if ((0 < m_stSkillInfo[index].level) && (m_fActCD[index] <= 0))
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
	}
	else
	{
		m_vctAiActSeq.push_back(RoleAct_Thrice_Atk);
	}
}

/*********************************************************************
** ���ܣ�		���� Ai��������
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void Role::aiActSequenceMain()
{
	m_vctAiActSeq.push_back(RoleAct_Attack);
	m_vctAiActSeq.push_back(RoleAct_Twice_Atk);
	m_vctAiActSeq.push_back(RoleAct_Thrice_Atk);
	m_vctAiActSeq.push_back(RoleAct_SkillOne);
	m_vctAiActSeq.push_back(RoleAct_SkillTwo);
	m_vctAiActSeq.push_back(RoleAct_SkillThree);
	m_vctAiActSeq.push_back(RoleAct_SkillFour);
}

/*********************************************************************
** ���ܣ�		���ض�����Դ
** ���������	��
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
void Role::loadArmature()
{
}

/*********************************************************************
** ���ܣ�		��ʼ����ɫ������ʾ��
** ���������	��
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
void Role::initHealthBar()
{
	auto spriteProgress = Sprite::create("res/MainFight/HPBar1.png");
	_roleHealth = ProgressTimer::create(spriteProgress);
	_roleHealth->setType(ProgressTimer::Type::BAR);
	_roleHealth->setMidpoint(Point::ANCHOR_BOTTOM_LEFT);
	_roleHealth->setBarChangeRate(Point::ANCHOR_BOTTOM_RIGHT);
	_roleHealth->setPercentage(100);
	_roleHealth->setScale(0.3f);
	//_roleHealth->setScaleY(0.2f);
	m_stRoleInfo.arAnimate->addChild(_roleHealth, 10);

	auto sz = m_stRoleInfo.arAnimate->getContentSize();
	auto x = sz.width * (m_stRoleSubInfo.anchorPoint.x - 0.5f);
	auto y = sz.height * (m_stRoleSubInfo.anchorPoint.y - 0.5f);
	_roleHealth->setPosition(Point(x, y + 200) * m_fResScale);
}

/*********************************************************************
** ���ܣ�		���ý�ɫ������
** ���������	��
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
void Role::initSubInfo()
{
	auto subInfoMap = DataManager::getInstance()->localSubInfoMap();
	auto subInfo = subInfoMap[m_strRoleName];
	memset(&m_stRoleSubInfo, 0, sizeof(RoleSubInfo));

	m_stRoleSubInfo.anchorPoint = Point(subInfo.anchorX, subInfo.anchorY);
	m_stRoleSubInfo.speed = subInfo.speed * MoveSpeed;
	if (RoleMode_Main == m_stRoleInfo.mode)
	{
		m_stRoleSubInfo.speed *= 1.4f;
	}

	m_stRoleInfo.arAnimate->setAnchorPoint(m_stRoleSubInfo.anchorPoint);
	m_stRoleInfo.arAnimate->setScale(m_fResScale);
	m_stRoleInfo.arAnimate->setPosition(Point::ZERO);
}

/*********************************************************************
** ���ܣ�		����Ai��Ϊ�ĸ���
** ���������	��
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
void Role::initActAiLimit()
{
	memcpy(m_fActAiLimit, roleActAiLimit[m_stRoleInfo.mode], sizeof(int) * RoleActAi_Max);

	if (RoleMode_Soldier == m_stRoleInfo.mode)
	{
		auto mode = UserData::getInstance()->getFightDifficulty();
		if (1 == mode)
		{
			m_fActAiLimit[RoleActAi_Pursuit] = 350;					/* ��Ӣģʽ���������ʶ�λ35% */
			m_fActAiLimit[RoleActAi_ShortMove] = 850;				/* ��Ӣģʽ���ƶ����ʶ�λ50% */
		}
	}
}

/*********************************************************************
** ���ܣ�		���ý�ɫ��������
** ���������	��
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
void Role::initSkillRegion()
{
	auto skillRegionMap = DataManager::getInstance()->localSkillRegionMap();
	auto skillRegion = skillRegionMap[m_strRoleName];
	memset(m_stSkillInfo, 0, sizeof(SkillInfo) * RoleAct_Max);

	m_stSkillInfo[RoleAct_Attack].xAtkDis = skillRegion.atk[0] * m_fResScale;
	m_stSkillInfo[RoleAct_Attack].yAtkDis = skillRegion.atk[1] * m_fResScale;

	m_stSkillInfo[RoleAct_Twice_Atk].xAtkDis = skillRegion.atk2[0] * m_fResScale;
	m_stSkillInfo[RoleAct_Twice_Atk].yAtkDis = skillRegion.atk2[1] * m_fResScale;

	m_stSkillInfo[RoleAct_Thrice_Atk].xAtkDis = skillRegion.atk3[0] * m_fResScale;
	m_stSkillInfo[RoleAct_Thrice_Atk].yAtkDis = skillRegion.atk3[1] * m_fResScale;

	m_stSkillInfo[RoleAct_SkillOne].xAtkDis = skillRegion.s1[0] * m_fResScale;
	m_stSkillInfo[RoleAct_SkillOne].yAtkDis = skillRegion.s1[1] * m_fResScale;

	m_stSkillInfo[RoleAct_SkillTwo].xAtkDis = skillRegion.s2[0] * m_fResScale;
	m_stSkillInfo[RoleAct_SkillTwo].yAtkDis = skillRegion.s2[1] * m_fResScale;

	m_stSkillInfo[RoleAct_SkillThree].xAtkDis = skillRegion.s3[0] * m_fResScale;
	m_stSkillInfo[RoleAct_SkillThree].yAtkDis = skillRegion.s3[1] * m_fResScale;

	m_stSkillInfo[RoleAct_SkillFour].xAtkDis = skillRegion.s4[0] * m_fResScale;
	m_stSkillInfo[RoleAct_SkillFour].yAtkDis = skillRegion.s4[1] * m_fResScale;
}

/*********************************************************************
** ���ܣ�		���ü��ܵȼ�����������
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void Role::initSkillGains()
{
// 	50 + 8 * (lv - 1)
// 	300 + 200 * (lv - 1)
// 	30 + 2 * (lv - 1)
// 	30 + 2 * (lv - 1)
// 
// 	200 + 64 * (lv - 1)
// 	12 +2 * (lv - 1)
// 	12 + 2 * (lv - 1)
// 
// 	5 + 1 * (lv - 1)
// 	5 + 1 * (lv - 1)
//	���� ����ֵ ��� ����

	int add[][4] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 0, 200, 12, 12, 50, 300, 30, 30};
	int factor[][4] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 64, 2, 2, 8, 200, 2, 2};

	if (RoleCamp_Black == m_stRoleInfo.camp)
	{
		m_stSkillInfo[RoleAct_SkillOne].level = m_stRoleInfo.panel.level;
		if ((m_iRoleStarLv >= 3) && (m_stRoleInfo.panel.level >= 3))
		{
			m_stSkillInfo[RoleAct_SkillTwo].level = m_stRoleInfo.panel.level;
		}
		if ((m_iRoleStarLv >= 4) && (m_stRoleInfo.panel.level >= 8))
		{
			m_stSkillInfo[RoleAct_SkillThree].level = m_stRoleInfo.panel.level;
		}
		if ((m_iRoleStarLv >= 5) && (m_stRoleInfo.panel.level >= 15))
		{
			m_stSkillInfo[RoleAct_SkillFour].level = m_stRoleInfo.panel.level;
		}
	}
	else
	{
		auto roleProp = DataManager::getInstance()->interGeneralVector();

		m_stSkillInfo[RoleAct_SkillOne].level = roleProp[0].skillLevel[0];
		m_stSkillInfo[RoleAct_SkillTwo].level = roleProp[0].skillLevel[1];
		m_stSkillInfo[RoleAct_SkillThree].level = roleProp[0].skillLevel[2];
		m_stSkillInfo[RoleAct_SkillFour].level = roleProp[0].skillLevel[3];
	}

	m_stRoleInfo.panel.atk += add[m_iRoleStarLv - 1][0] + factor[m_iRoleStarLv - 1][0] * (m_stSkillInfo[RoleAct_SkillFour].level - 1);
	m_stRoleInfo.panel.hpTotal += add[m_iRoleStarLv - 1][1] + factor[m_iRoleStarLv - 1][1] * (m_stSkillInfo[RoleAct_SkillThree].level - 1);
	m_stRoleInfo.panel.hpCurrent = m_stRoleInfo.panel.hpTotal;
	m_stRoleInfo.panel.pDefend += add[m_iRoleStarLv - 1][2] + factor[m_iRoleStarLv - 1][2] * (m_stSkillInfo[RoleAct_SkillTwo].level - 1);
	m_stRoleInfo.panel.mDefend += add[m_iRoleStarLv - 1][3] + factor[m_iRoleStarLv - 1][3] * (m_stSkillInfo[RoleAct_SkillOne].level - 1);
}

/*********************************************************************
** ���ܣ�		��ʼ�����ѧ��buff
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void Role::initJxxgBuff()
{
	if ((RoleCreMode_Fighting != m_eRoleCreMode) && (RoleCamp_Red == m_stRoleInfo.camp))
	{
		return;														/* �ؿ�ģʽ����Ҫ */
	}

	auto jxxgBuffInfo = DataManager::getInstance()->interJxxgBuffVector();
	if (0 < jxxgBuffInfo.size())
	{
		auto num = jxxgBuffInfo[0].num%10;							/* ȡ��ǰbuffʣ��ؿ����� */
		if (num > 0)
		{
			float buff[3] = {0};
			switch (jxxgBuffInfo[0].rewar%10)
			{
			case 1:
				buff[0] = 1.05f;
				buff[1] = 1.03f;
				buff[2] = 1.06f;
				break;
			case 2:
				buff[0] = 1.05f;
				buff[1] = 1.03f;
				break;
			case 3:
				buff[0] = 1.05f;
				break;
			case 4:
				buff[2] = 1.06f;
				break;
			}

			m_stRoleInfo.panel.hpTotal *= buff[0];
			m_stRoleInfo.panel.hpCurrent = m_stRoleInfo.panel.hpTotal;
			m_stRoleInfo.panel.atk *= buff[1];
			m_stRoleInfo.panel.pDefend *= buff[2];
			m_stRoleInfo.panel.mDefend *= buff[2];

			if (1 == num)
			{
				jxxgBuffInfo[0].num = jxxgBuffInfo[0].num/10;
				jxxgBuffInfo[0].rewar = jxxgBuffInfo[0].rewar/10;
			}
			else
			{
				jxxgBuffInfo[0].num = jxxgBuffInfo[0].num/10 * 10 + num - 1;
			}
			DataManager::getInstance()->isJxxgPassSucceed(0, 0, jxxgBuffInfo);
		}
	}
}

/*********************************************************************
** ���ܣ�		����Ai��������
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void Role::setAiActionSequence()
{
	switch ( m_stRoleInfo.mode)
	{
	case RoleMode_Soldier:											/* ����Ai�������� */
		aiActSequenceSoldier();
		break;
	case RoleMode_Main:												/* ���� Ai�������� */
		aiActSequenceMain();
		break;
	case RoleMode_Companion:										/* С���Ai�������� */
		aiActSequenceCompanion();
		break;
	case RoleMode_Boss:												/* Boss Ai�������� */
		aiActSequenceBoss();
		break;
	default:
		break;
	}

	m_iAiActSeqIndex = 0;
}

/*********************************************************************
** ���ܣ�		��ʼ����ɫ��������
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void Role::initActInherent()
{
	memset(m_stActMode, 0, sizeof(m_stActMode));
	
	m_stActMode[RoleAct_Attack] = RoleActMode_Physical;			/* ���� */
	m_stActMode[RoleAct_Twice_Atk] = RoleActMode_Physical;		/* ������ */
	m_stActMode[RoleAct_Thrice_Atk] = RoleActMode_Physical;		/* ������ */
	m_stActMode[RoleAct_SkillOne] = RoleActMode_Magic;			/* ����һ */
	m_stActMode[RoleAct_SkillTwo] = RoleActMode_Magic;			/* ���ܶ� */
	m_stActMode[RoleAct_SkillThree] = RoleActMode_Magic;			/* ������ */
	m_stActMode[RoleAct_SkillFour] = RoleActMode_Magic;			/* ������ */
}

/*********************************************************************
** ���ܣ�		��ʼ�����ܷ��е���
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void Role::initFlightPropInfo()
{
}

/*********************************************************************
** ���ܣ�		��ȡ�����¼�����
** ���������	RoleFrameEvent evt: �¼���������
** ����ֵ��		std::string���¼�����
** �޸ļ�¼��	
*********************************************************************/
std::string Role::getFrameEventName(RoleFrameEvent evt)
{
	std::string str = "";
	if ((FrameEvent_Begin <= evt) && (FrameEvent_Max > evt))
	{
		str = strFrameEventName[evt];
	}

	return str;
}

/*********************************************************************
** ���ܣ�		��ȡ���е�����Դ·��
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
std::string Role::getFlightPropPath()
{
	return strFlightPropPath;
}

/*********************************************************************
** ���ܣ�		������Ч
** ���������	
** ����ֵ��		
** �޸ļ�¼��	
*********************************************************************/
unsigned int Role::playEffectOgg(const char* pszFilePath, bool bLoop, float pitch, float pan, float gain)
{
	return ToolFunc::playEffectFile(pszFilePath, bLoop, pitch, pan, gain);
}

/*********************************************************************
** ���ܣ�		��ɫ�Ƿ�ϰ���츳
** ���������	RoleTalent talent: �жϵ��츳
** ����ֵ��		bool bDown:true:ϰ��;false:û��
** �޸ļ�¼��	
*********************************************************************/
bool Role::isRoleLearnedTalent(RoleTalent talent)
{
	int n = 0;
	while (n <= 24)
	{
		if (talent == ((m_stRoleInfo.panel.talent >> n) & 0xFF))
		{
			return true;
		}

		n += 8;
	}
	return false;
}

/*********************************************************************
** ���ܣ�		ս����Ϣ����
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void Role::warMsgDecision()
{
	switch (m_eRoleWarMsg)
	{
	case RoleWarMsg_None:
		if (RoleMode_Main == m_stRoleInfo.mode)						/* �����жϵз��Ƿ��ڹ�����Χ�� */
		{
			runRoleMainAI();
		}
		else
		{
			runRoleAI();
		}
		break;
	case RoleWarMsg_Pause:
		m_rcRegion.size.width = 2 * SceneWidth;
		m_rcRegion.origin.x = SceneWidth * m_iSceneID;
		m_eRoleWarMsg = RoleWarMsg_Pass;
		//auto duration = ToolFunc::calcRandom(10, 20) * 1.0f / 10;
		this->runAction(Sequence::create(DelayTime::create(1.0f), 
			CallFunc::create(CC_CALLBACK_0(Role::passRoomByAuto, this)), NULL));
		break;
	case RoleWarMsg_Pass:
		if (getPositionX() >= (m_iSceneID + 1) * SceneWidth + iRegionLimit)
		{
			m_iSceneID ++;
			runActionIdle();
			m_eRoleWarMsg = RoleWarMsg_None;
			m_rcRegion.size.width = SceneWidth - 2 * iRegionLimit;
			m_rcRegion.origin.x = SceneWidth * m_iSceneID + iRegionLimit;
		}
		break;
	case RoleWarMsg_Over:
		if (RoleAct_Idle != m_stRoleInfo.actSign)
		{
			runActionIdle();
			roleUnSchedule(RoleSchedule_AiAction);
		}
		break;
	}
}

/*********************************************************************
** ���ܣ�		Ai�Զ���ͼ
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void Role::passRoomByAuto()
{
	m_ptMoveDir = Point(260, 0);							/* ��ͨ����ǰ����,������ */
	runActionMove();
}

/*********************************************************************
** ���ܣ�		����
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void Role::shaky()
{
	auto sp = this->getParent()->getChildByTag(order_Bkg);
	if (NULL == sp)
	{
		return;
	}

	auto sz = Size(20, 20);
	auto speed = 280.0f;

	FiniteTimeAction *prev = CallFuncN::create(CC_CALLBACK_1(Role::shakyCallBack, this));
	for (int i = 0;i < 7;i++)
	{
		auto rate = (0 == i) ? 0.9 : (1 == i) ? 0.7 : (1.0f / i);
		auto pt = Point(ToolFunc::calcRandom(-sz.width, 0) + m_iSceneID * sz.width, -sz.height * rate);
		auto move = MoveTo::create(pt.getLength()/speed, pt);			/* ���� */
		prev = Sequence::createWithTwoActions(prev, move);

		auto pt1 = Point(ToolFunc::calcRandom(-sz.width, 0) + m_iSceneID * sz.width, 0);
		auto move1 = MoveTo::create(pt.getLength()/speed, pt1);			/* ��� */
		prev = Sequence::createWithTwoActions(prev, move1);
	}
	auto seq = Sequence::create(prev, CallFuncN::create(CC_CALLBACK_1(Role::shakyCallBack, this)), NULL);
	sp->runAction(seq);
}

/*********************************************************************
** ���ܣ�		�ŵ׹⻷��Ч
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void Role::playAureoleEffect()
{
	m_nAureoleEffect->setPosition(this->getPosition());
	m_nAureoleEffect->setLocalZOrder(order_Bkg + 1);
	this->getParent()->addChild(m_nAureoleEffect);

	if (RoleCamp_Red == m_stRoleInfo.camp)
	{
		auto animation1 = Animation::create();						/* ��Ȧ���� */
		for (int index = 0;index < 4;index ++)
		{
			auto strPath = __String::createWithFormat("res/RoleAureole/RedMain%d.png", index);
			animation1->addSpriteFrameWithFile(strPath->getCString());
		}
		animation1->setDelayPerUnit(0.15f);
		animation1->setRestoreOriginalFrame(true);
		animation1->setLoops(-1);

		auto AniMain = Animate::create(animation1);

		auto spMain = Sprite::create();
		m_nAureoleEffect->addChild(spMain);
		m_nAureoleEffect->setScale(0.4f);
		spMain->setLocalZOrder(0);
		spMain->runAction(AniMain);		

		if (RoleMode_Main == m_stRoleInfo.mode)					/* ���� */
		{
			auto animation2 = Animation::create();					/* ��Ȧ���� */
			for (int index = 0;index < 6;index ++)
			{
				auto strPath = __String::createWithFormat("res/RoleAureole/RedSub%d.png", index);
				animation2->addSpriteFrameWithFile(strPath->getCString());
			}
			animation2->setDelayPerUnit(0.13f);
			animation2->setRestoreOriginalFrame(true);
			animation2->setLoops(-1);

			auto AniSub = Animate::create(animation2);

			auto spSub = Sprite::create();
			m_nAureoleEffect->addChild(spSub);
			m_nAureoleEffect->setScale(0.7f);
			spSub->setLocalZOrder(1);
			spSub->runAction(AniSub);
			spSub->setAnchorPoint(Point(0.5f, 0.4f));
			spSub->setScale(0.8f);
		}		
	}
	else
	{
		if (RoleMode_Boss == m_stRoleInfo.mode)					/* Boss */
		{
			auto animation = Animation::create();
			for (int index = 0;index < 8;index ++)
			{
				auto strPath = __String::createWithFormat("res/RoleAureole/Black%d.png", index);
				animation->addSpriteFrameWithFile(strPath->getCString());
			}
			animation->setDelayPerUnit(0.15f);
			animation->setRestoreOriginalFrame(true);
			animation->setLoops(-1);

			auto AniMain = Animate::create(animation);

			auto sp = Sprite::create();
			m_nAureoleEffect->addChild(sp);
			m_nAureoleEffect->setScale(0.6f);
			sp->runAction(AniMain);
			sp->setAnchorPoint(Point(0.5f, 0.32f));
		}
	}
}

/* ������Ч */
void Role::playHitEffect()
{
	auto animation = Animation::create();
	for (int index = 0; index < 8; index++)
	{
		auto strPath = __String::createWithFormat("res/Hit/hit%d.png", index);
		animation->addSpriteFrameWithFile(strPath->getCString());
	}
	animation->setDelayPerUnit(0.3f/8);
	animation->setRestoreOriginalFrame(true);
	animation->setLoops(1);

	auto ani = Animate::create(animation);

	auto sp = Sprite::create();
	sp->setPosition(0, 50);
	this->addChild(sp);
	sp->setScaleY(-1);
	sp->setScaleX(m_stRoleSubInfo.atkSide);
	sp->runAction(Sequence::createWithTwoActions(ani, CallFuncN::create(CC_CALLBACK_1(Role::hitEffectCB, this))));
}

void Role::hitEffectCB(Node* who)
{
	who->removeFromParentAndCleanup(true);
}

/* ������Ч */
void  Role::deathEffect()
{
	auto animation = Animation::create();
	for (int index = 0; index < 5; index++)
	{
		auto strPath = __String::createWithFormat("res/Death/%d.png", index);
		animation->addSpriteFrameWithFile(strPath->getCString());
	}
	animation->setDelayPerUnit(2.5f/5);
	animation->setRestoreOriginalFrame(true);
	animation->setLoops(1);

	auto ani = Animate::create(animation);

	auto sp = Sprite::create();
	auto pt = getPosition();
	sp->setPosition(Point(pt.x, pt.y + 70));
	this->getParent()->addChild(sp);
	sp->setLocalZOrder(order_Bkg + 1);
	sp->runAction(Sequence::createWithTwoActions(ani, CallFuncN::create(CC_CALLBACK_1(Role::deathEffectCB, this))));
}

void Role::deathEffectCB(Node* who)
{
	who->removeFromParentAndCleanup(true);
}

void Role::addTrail(int id)
{
	auto drawNode = DrawNode::create();
	this->getParent()->addChild(drawNode, order_Bkg + 1);

	Point pt[4];

	switch (m_stRoleSubInfo.atkSide)
	{
	case RoleDir_Left:
		pt[0] = Point(getPositionX() - m_stSkillInfo[id].xAtkDis, getPositionY() - m_stSkillInfo[id].yAtkDis/2);
		pt[1] = Point(getPositionX(), getPositionY() - m_stSkillInfo[id].yAtkDis/2);
		pt[2] = Point(getPositionX(), getPositionY() + m_stSkillInfo[id].yAtkDis/2);
		pt[3] = Point(getPositionX() - m_stSkillInfo[id].xAtkDis, getPositionY() + m_stSkillInfo[id].yAtkDis/2);
		break;
	case RoleDir_Right:
		pt[0] = Point(getPositionX(), getPositionY() - m_stSkillInfo[id].yAtkDis/2);
		pt[1] = Point(getPositionX() + m_stSkillInfo[id].xAtkDis, getPositionY() - m_stSkillInfo[id].yAtkDis/2);
		pt[2] = Point(getPositionX() + m_stSkillInfo[id].xAtkDis, getPositionY() + m_stSkillInfo[id].yAtkDis/2);
		pt[3] = Point(getPositionX(), getPositionY() + m_stSkillInfo[id].yAtkDis/2);
		break;
	case RoleDir_Middle:
		pt[0] = Point(getPositionX() - m_stSkillInfo[id].xAtkDis, getPositionY() - m_stSkillInfo[id].yAtkDis/2);
		pt[1] = Point(getPositionX() + m_stSkillInfo[id].xAtkDis, getPositionY() - m_stSkillInfo[id].yAtkDis/2);
		pt[2] = Point(getPositionX() + m_stSkillInfo[id].xAtkDis, getPositionY() + m_stSkillInfo[id].yAtkDis/2);
		pt[3] = Point(getPositionX() - m_stSkillInfo[id].xAtkDis, getPositionY() + m_stSkillInfo[id].yAtkDis/2);
		break;
	}
	drawNode->drawPolygon(pt, 4, Color4F::YELLOW, 1, Color4F::YELLOW);

	drawNode->runAction(Sequence::createWithTwoActions(DelayTime::create(3.0f), 
		CallFuncN::create(CC_CALLBACK_1(Role::removeTrail, this))));
}
void Role::removeTrail(Node* who)
{
	who->removeFromParentAndCleanup(true);
}

/*********************************************************************
** ���ܣ�		ִ����ײ���
** ���������	bool bDown:true:����;false:������
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void Role::roleCollisionDetective(bool bDown)
{
	auto roles = UserData::getInstance()->getRoles();

	for(unsigned int index = 0;index < roles.size();index ++)		/* ���˽�ɫ������ȡ */
	{
		auto role = (Role *)roles[index];
		auto info = role->getRoleInfo();

		if ((RoleStatus_Invincible == info.status) || (RoleStatus_Death == info.status) || 
			(m_stRoleInfo.camp == info.camp) || (m_iSceneID != role->getSceneID()))
		{
			continue;												/* �޵С�ͬ��Ӫ������������������ */
		}

		auto hitSide = RoleDir_Left;								/* �Է����������� */
		hitSide = (getPositionX() > role->getPositionX()) ? RoleDir_Left : RoleDir_Right;

		if (-1 != hitSide * m_stRoleSubInfo.atkSide)				/* ȷ�Ϸ������� */
		{
			/* ��ײ�ҽ�ɫ����ͶԷ��ܻ�������� *//* �ڵ����ҷ����󹥻����ڵ����󷽲��ҹ��� */	
			auto ptOffset = role->getPosition() - getPosition();	/* ���λ�� */

			/* ������Ч��Χ�ж� */
			if ((m_stSkillInfo[m_stRoleInfo.actSign].xAtkDis >= abs(ptOffset.x)) && (m_stSkillInfo[m_stRoleInfo.actSign].yAtkDis >= abs(ptOffset.y)))
			{
				auto life = role->roleHurt(this, m_stSkillInfo[m_stRoleInfo.actSign], bDown);

				if ((RoleActMode_Physical == m_stActMode[m_stRoleInfo.actSign]) && (RoleMode_Soldier != m_stRoleInfo.mode))
				{
					m_bRoleActBreak = true;
				}
			}
		}
	}
}

/*********************************************************************
** ���ܣ�		ִ�ж���
** ���������	role_action action:��������ID
** ����ֵ�� 	bool:true:ִ�гɹ�
** �޸ļ�¼��	
*********************************************************************/
bool Role::runArmatureAction(RoleActSign action)
{
	bool bRet = true;

	if ((RoleAct_Death != m_stRoleInfo.actSign) && (NULL != m_stRoleInfo.arAnimate))
	{
		if (true == checkAnimateExistByName(strRoleSkillName[action]))/* ���������ڣ�*/
		{
			stopArmatureAction();
			if (RoleCreMode_Preview != m_eRoleCreMode)
			{
				if (0 < m_fActCD[action])								/* CD�� */
				{
					action = RoleAct_Idle;
					bRet = false;
				}
				else
				{
					m_fActCD[action] = m_stSkillInfo[action].cd;
				}
			}

			m_stRoleInfo.actSign = action;
			m_stRoleInfo.arAnimate->getAnimation()->play(strRoleSkillName[action]);
			m_bRoleActBreak = false;								/* �ж϶����������жϱ�� */

			if ((RoleActMode_Physical == m_stActMode[action]) && (RoleMode_Soldier != m_stRoleInfo.mode))
			{
				m_iRoleCombo = (m_iRoleCombo + 1)%3;				/* �����һ�չ����� */
				roleUnSchedule(RoleSchedule_Combo);					/* �չ�������ʱ��ȡ�� */
			}

			if ((RoleAct_SkillOne <= m_stRoleInfo.actSign) && (RoleAct_SkillFour >= m_stRoleInfo.actSign))
			{
				m_iRoleCombo = 0;									/* ִ�м��ܣ��չ�����Ϊ��һ�� */
			}

			if ((RoleAct_SkillOne < action) && (RoleAct_SkillFour > action))
			{
				if (true == isRoleLearnedTalent(RoleTalent_NengLiangHua))	/* ������ */
				{
					if (0 == m_stRoleBuff.shield)					/* Ч����һ�δ��� */
					{
						roleSchedule(7.0f, RoleSchedule_Shield);
					}
					m_stRoleBuff.shield += (m_stRoleInfo.panel.hpTotal + m_stRoleBuff.hpLimit) * 0.03f;
				}
			}
		}
	}

	return bRet;
}

/*********************************************************************
** ���ܣ�		ֹͣ����
** ���������	��
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
void Role::stopArmatureAction()
{
	if ((RoleAct_Death != m_stRoleInfo.actSign) && (NULL != m_stRoleInfo.arAnimate))
	{
		m_stRoleInfo.arAnimate->getAnimation()->stop();
	}
}

/*********************************************************************
** ���ܣ�		�������Ƽ�⶯�����ڷ�
** ���������	std::string name����������
** ����ֵ�� 	bool��true�����ڣ�false��������
** �޸ļ�¼��	
*********************************************************************/
bool Role::checkAnimateExistByName(const std::string name)
{
	if (NULL != m_stRoleInfo.arAnimate)
	{
		auto movement = m_stRoleInfo.arAnimate->getAnimation()->getAnimationData()->getMovement(name);
		if (NULL != movement)										/* ���������� */
		{
			return true;
		}
	}

	return false;
}

/*********************************************************************
** ���ܣ�		����ʱ��Ϣ��Ӧ
** ���������	const std::string& str����������
**				MovementEventType type: �����׶�
**				float duration: ��������ʱ��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void Role::movement(const std::string& str, MovementEventType type, float duration)
{
	switch (type)
	{
	case cocostudio::START:
		m_stRoleSubInfo.atkSide = m_stRoleSubInfo.side;		/* ���Ŷ���ǰ�������������ã�Ĭ��ǰ�� */
		if (RoleAct_Down == m_stRoleInfo.actSign)			/* �����޵� */
		{
			this->unschedule(schedule_selector(Role::downResume));
			this->scheduleOnce(schedule_selector(Role::downResume), 0.5f + DownDelay);
		}
		break;
	case cocostudio::COMPLETE:
		movement(str);
		break;
	case cocostudio::LOOP_COMPLETE:
		break;
	default:
		break;
	}
}

/*********************************************************************
** ���ܣ�		����ʱ��Ϣ��Ӧ
** ���������	const std::string& str����������
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void Role::movement(const std::string& str)
{
	if (RoleCreMode_Preview == m_eRoleCreMode)						/* �佫����Ԥ��ģʽ��ִ�� */
	{
		runArmatureAction(RoleAct_Idle);
		return;
	}

	if (RoleActMode_Physical == m_stActMode[m_stRoleInfo.actSign])/* ��ͨ���� */
	{
		roleSchedule(ComboDuration, RoleSchedule_Combo);
	}

// 	if (RoleActMode_Normal != m_stActMode[m_stRoleInfo.actSign])
// 	{
// 		addTrail(m_stRoleInfo.actSign);
// 	}

	if (RoleAct_Down == m_stRoleInfo.actSign)						/* ����״̬ */
	{
		m_stRoleInfo.status = RoleStatus_Invincible;
		//this->scheduleOnce(schedule_selector(Role::downResume), DownDelay);
	}
	else if (RoleAct_Smitten == m_stRoleInfo.actSign)
	{
		this->scheduleOnce(schedule_selector(Role::smittenResume), 0.3f/*m_stRoleSubInfo.smittenDelay*/);
	}
	else if (RoleAct_Death == m_stRoleInfo.actSign)					/* ����״̬ */
	{
		flashEffect();
	}
	else		/* ���ء�Ӳֱ������������action_idle */
	{
		runActionIdle();
	}
}

/*********************************************************************
** ���ܣ�		����ʱ֡�¼�
** ���������	const std::string& evt���¼���
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void Role::frameEvent(const std::string& evt)
{
	if (RoleCreMode_Preview == m_eRoleCreMode)						/* �佫����Ԥ��ģʽ��ִ�� */
	{
		return;
	}

	if (evt == getFrameEventName(FrameEvent_Attack))				/* �����������أ� */
	{
		roleCollisionDetective(false);
	}
	else if (evt == getFrameEventName(FrameEvent_Attack_FD))		/* ���������أ� */
	{
		roleCollisionDetective(true);
	}
	else if ((evt == getFrameEventName(FrameEvent_Begin)) && 
		(RoleStatus_Invincible != m_stRoleInfo.status))				/* ��ʼ���� */
	{
		m_stRoleInfo.status = RoleStatus_Superarmor;
	}
	else if ((evt == getFrameEventName(FrameEvent_End)) &&
		(RoleStatus_Invincible != m_stRoleInfo.status))				/* �������� */
	{
		m_stRoleInfo.status = RoleStatus_Normal;
	}
	else if (evt == getFrameEventName(FrameEvent_Left))				/* ��ǰ���� */
	{
		m_stRoleSubInfo.atkSide = m_stRoleSubInfo.side;
	}
	else if (evt == getFrameEventName(FrameEvent_Right))			/* ���󹥻� */
	{
		m_stRoleSubInfo.atkSide = (RoleDirSign)(RoleDir_Right * m_stRoleSubInfo.side);
	}
	else															/* ǰ��˫������ */
	{
		if (evt == getFrameEventName(FrameEvent_Middle))
		{
			m_stRoleSubInfo.atkSide = RoleDir_Middle;
		}
	}
}

/*********************************************************************
** ���ܣ�		������ʱ��
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void Role::onEnter()
{
	Node::onEnter();

	this->schedule(schedule_selector(Role::hpReture), HealthRetRate);
	this->scheduleUpdate();
}

/*********************************************************************
** ���ܣ�		�رռ�ʱ��
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void Role::onExit()
{
	this->unschedule(schedule_selector(Role::hpReture));
	this->unscheduleUpdate();

	Node::onExit();
}

void Role::update(float dt)
{
	makeRoleMoving(dt);
	actionCDFlag(dt);
	checkRoleInBgRegion();
	updateRole();
}

void Role::updateRole()
{
	if (RoleCreMode_Preview != m_eRoleCreMode)
	{
		warMsgDecision();
		m_nAureoleEffect->setPosition(this->getPosition());
	}
}

/*********************************************************************
** ���ܣ�		hp�ظ�
** ���������	float dt:
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void Role::hpReture(float dt)
{
	m_stRoleInfo.panel.hpCurrent = m_stRoleInfo.panel.hpCurrent + m_stRoleBuff.hpBack + m_stRoleBuff.hpBack;
	m_stRoleBuff.hpBack = 0;									/* ��ʱhp�ָ����� */

	if (m_stRoleInfo.panel.hpTotal + m_stRoleBuff.hpLimit <= m_stRoleInfo.panel.hpCurrent)
	{
		m_stRoleInfo.panel.hpCurrent = m_stRoleInfo.panel.hpTotal + m_stRoleBuff.hpLimit;
	}
}

/*********************************************************************
** ���ܣ�		CD��ʱ
** ���������	float dt:
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void Role::actionCDFlag(float dt)
{
	for (int index = RoleAct_SkillOne;index <= RoleAct_SkillFour;index++)
	{
		if (0 < m_fActCD[index])
		{
			m_fActCD[index] -= dt;
		}
	}
}

/*********************************************************************
** ���ܣ�		��ɫ��ʱ��
** ���������	float dt:��ʱ������ʱ��
**				RoleScheduleType type: ��ʱ������
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void Role::roleSchedule(float dt, RoleScheduleType type)
{
	switch (type)
	{
	case RoleSchedule_Combo:
		this->scheduleOnce(schedule_selector(Role::comboResume), dt);
		break;
	case RoleSchedule_Condition:
		this->scheduleOnce(schedule_selector(Role::conditionResume), dt);
		break;
	case RoleSchedule_AiAction:
		this->scheduleOnce(schedule_selector(Role::aiActionResume), dt);
		break;
	case RoleSchedule_Abnormal:
		this->scheduleOnce(schedule_selector(Role::abnormalResume), dt);
		break;
	case RoleSchedule_Shield:
		this->scheduleOnce(schedule_selector(Role::buffShieldResume), dt);
		break;
	default:
		break;
	}
}

/*********************************************************************
** ���ܣ�		�رս�ɫ��ʱ��
** ���������	RoleScheduleType type: ��ʱ������
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void Role::roleUnSchedule(RoleScheduleType type)
{
	switch (type)
	{
	case RoleSchedule_Combo:
		this->unschedule(schedule_selector(Role::comboResume));
		break;
	case RoleSchedule_Condition:
		this->unschedule(schedule_selector(Role::conditionResume));
		conditionResume(0.0f);
		break;
	case RoleSchedule_AiAction:
		this->unschedule(schedule_selector(Role::aiActionResume));
		aiActionResume(0.0f);
		break;
	case RoleSchedule_Abnormal:
		this->unschedule(schedule_selector(Role::abnormalResume));
		abnormalResume(0.0f);
		break;
	case RoleSchedule_Shield:
		this->unschedule(schedule_selector(Role::buffShieldResume));
		buffShieldResume(0.0f);
		break;
	default:
		break;
	}
}

/*********************************************************************
** ���ܣ�		������Ǹ�λ
** ���������	float dt
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
void Role::comboResume(float dt)
{
	m_iRoleCombo = 0;
}

/*********************************************************************
** ���ܣ�		�쳣״̬�ָ�
** ���������	float dt
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void Role::conditionResume(float dt)
{
	m_stRoleInfo.condition = RoleCondition_Normal;
	runActionIdle();
}

/*********************************************************************
** ���ܣ�		AI��Ϊ����
** ���������	float dt
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void Role::aiActionResume(float dt)
{
	if (RoleActAi_None != m_eRoleActAi)
	{
		m_eRoleActAi = RoleActAi_None;
		runActionIdle();
	}	
}

/*********************************************************************
** ���ܣ�		�쳣�˺�����
** ���������	float dt
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void Role::abnormalResume(float)
{
}

/*********************************************************************
** ���ܣ�		������ʧ
** ���������	float dt
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void Role::buffShieldResume(float dt)
{
	m_stRoleBuff.shield = 0.0f;
}

/*********************************************************************
** ���ܣ�		hp�ָ��츳
** ���������	float dt
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void Role::buffHpBack(float dt)
{
	auto	nearest = -1;
	auto	hpValue = 0.0f;
	auto	vec = UserData::getInstance()->getRoles();
	auto	len = vec.size();
	auto	sz = Director::getInstance()->getWinSize();
	auto	maxValue = 100000;

	for (unsigned int index = 0;index < len;index ++)
	{
		auto role = (Role *)vec[index];
		auto info = role->getRoleInfo();

		if ((m_stRoleInfo.camp == info.camp) && (role->getSceneID() == m_iSceneID))
		{
			hpValue = info.panel.hpCurrent;
			if (maxValue > hpValue)
			{
				maxValue = hpValue;
				nearest = index;
			}
		}
	}

	if (-1 != nearest)	
	{
		auto role = (Role *)vec[nearest];
		if (this != role)											/* �Լ����ظ� */
		{
			auto info = role->getRoleInfo();
			auto buff = role->getRoleBuff();
			role->setRoleHpUp((info.panel.hpTotal + buff.hpLimit) * 0.075f);
		}
	}
}

/*********************************************************************
** ���ܣ�		����ü���츳
** ���������	float dt
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
void Role::buffHarmGrow(float dt)
{
	m_stRoleInfo.panel.allHarm += 2.0f;
}

/*********************************************************************
** ���ܣ�		������buff��λ
** ���������	float dt
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
void Role::buffDenfendLResume(float dt)
{
	m_stRoleBuff.pDefend = 0;
	m_stRoleBuff.mDefend = 0;
}

/*********************************************************************
** ���ܣ�		ȷ����ɫ���ƶ�������������
** ���������	��
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
void Role::checkRoleInBgRegion()
{
	this->setLocalZOrder(m_rcRegion.getMaxY() - getPositionY() + order_Role);

	if (getPositionX() > m_rcRegion.getMaxX())
	{
		setPositionX(m_rcRegion.getMaxX());
	}
	if (getPositionX() < m_rcRegion.getMinX())
	{
		setPositionX(m_rcRegion.getMinX());
	}
	if (getPositionY() > m_rcRegion.getMaxY())
	{
		setPositionY(m_rcRegion.getMaxY());
	}
	if (getPositionY() < m_rcRegion.getMinY())
	{
		setPositionY(m_rcRegion.getMinY());
	}
}

/*********************************************************************
** ���ܣ�		�ƶ���ɫ(����ִ��)
** ���������	float dt: ÿ֡ʱ��
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
void Role::makeRoleMoving(float dt)
{
	if (RoleCreMode_Preview != m_eRoleCreMode)
	{
		if (RoleAct_Move == m_stRoleInfo.actSign)
		{
			setRoleTurnedDirInfo(m_ptMoveDir.x + getPositionX());/* ת�� */
			setPosition(getPosition() + m_ptMoveDir * dt);
		}
	}
}

/*********************************************************************
** ���ܣ�		ȡ��Ӳֱ
** ���������	float dt
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
void Role::downResume(float dt)
{
	flashEffect();													/* ������Ч */
	runActionIdle();
}

/*********************************************************************
** ���ܣ�		��ɫ��˸��Ч
** ���������	��
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
void Role::flashEffect()
{
	Sequence *seqCall = NULL;
	if (RoleStatus_Death == m_stRoleInfo.status)
	{
		if (1 == UserData::getInstance()->getBlackRoleTotalCount())
		{
			Director::getInstance()->setAnimationInterval(1.0f/60);
			auto roles = UserData::getInstance()->getRoles();
			for (unsigned int index = 0;index < roles.size();index++)
			{
				auto role = (Role *)roles[index];
				if (RoleStatus_Death != role->getRoleInfo().status)
				{
					role->setAnimateSpeed(1.0f);
				}
			}
		}
		seqCall = Sequence::create(Blink::create(InvincibleDelay, 4), CallFunc::create(CC_CALLBACK_0(Role::deathEffectCallBack, this)), NULL);
	}
	else
	{
		m_stRoleInfo.arAnimate->setOpacity(150);
		seqCall = Sequence::create(DelayTime::create(InvincibleDelay), CallFunc::create(CC_CALLBACK_0(Role::flashEffectCallBack, this)), NULL);
	}
	m_stRoleInfo.arAnimate->runAction(seqCall);
}

/*********************************************************************
** ���ܣ�		���������״̬�ָ�����
** ���������	��
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
void Role::flashEffectCallBack()
{
	m_stRoleInfo.arAnimate->setOpacity(255);
	m_stRoleInfo.status = RoleStatus_Normal;
}

/*********************************************************************
** ���ܣ�		������ص�
** ���������	��
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
void Role::deathEffectCallBack()
{
	if (RoleCamp_Red == m_stRoleInfo.camp)							/* ˢ�½�ɫ���� */
	{
		UserData::getInstance()->checkRedRolecount();
	}
	else
	{
		UserData::getInstance()->checkBlackRolecount(m_iSceneID);
	}

	this->unscheduleUpdate();
	this->setVisible(false);
	m_nAureoleEffect->setVisible(false);
}

/*********************************************************************
** ���ܣ�		�ܻ��ָ�
** ���������	float dt
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
void Role::smittenResume(float dt)
{
	if (RoleAct_Smitten == m_stRoleInfo.actSign)					/* ȷ����ִ�еĶ������ܻ� */
	{
		runActionIdle();
	}
}

/*********************************************************************
** ���ܣ�		��������
** ���������	Node* who
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
void Role::shakyCallBack(Node* who)
{
	who->setPosition(Point(0, 0));
}

/* ����ִ�� Begin*/
/*********************************************************************
** ���ܣ�		ִ�й�������
** ���������	��
** ����ֵ�� 	bool:true:����ִ�гɹ�
** �޸ļ�¼��	
*********************************************************************/
bool Role::runActionAtkCtrl()
{
	if ((RoleAct_Idle == m_stRoleInfo.actSign) || (RoleAct_Move == m_stRoleInfo.actSign) ||
		((true == m_bRoleActBreak) && (RoleAct_Thrice_Atk != m_stRoleInfo.actSign)))
	{
		if (1 == m_iRoleCombo)
		{
			m_stRoleInfo.actSign = RoleAct_Twice_Atk;				/* ai���Ƶ��չ�ID���ܺ͵�ǰ��������ǲ�һ�� */
			return runActionTwiceAtk();
		}
		else if (2 == m_iRoleCombo)
		{
			m_stRoleInfo.actSign = RoleAct_Thrice_Atk;
			return runActionThriceAtk();
		}
		else
		{
			m_stRoleInfo.actSign = RoleAct_Attack;
			return runActionAttack();
		}
	}

	return false;
}

/*********************************************************************
** ���ܣ�		ִ�п��ж���
** ���������	��
** ����ֵ�� 	bool:true:����ִ�гɹ�
** �޸ļ�¼��	
*********************************************************************/
bool Role::runActionIdle()
{
	return runArmatureAction(RoleAct_Idle);
}

/*********************************************************************
** ���ܣ�		ִ���ƶ�����
** ���������	��
** ����ֵ�� 	bool:true:����ִ�гɹ�
** �޸ļ�¼��	
*********************************************************************/
bool Role::runActionMove()
{
	if (RoleAct_Move > m_stRoleInfo.actSign)						/* �ж϶������� */
	{
		return runArmatureAction(RoleAct_Move);
	}
		
	return true;
}

/*********************************************************************
** ���ܣ�		��ͨ������һ��
** ���������	��
** ����ֵ��		bool:true:����ִ�гɹ�
** �޸ļ�¼��	
*********************************************************************/
bool Role::runActionAttack()
{
	auto bRet = runArmatureAction(RoleAct_Attack);
	if (true == bRet)
	{
		Point ptOffset = ptAtkOffset * m_stRoleSubInfo.side * -0.9f;
		setPosition(getPosition() + ptOffset);
	}

	return bRet;
}

/*********************************************************************
** ���ܣ�		��ͨ�����ڶ���
** ���������	��
** ����ֵ��		bool:true:����ִ�гɹ�
** �޸ļ�¼��	
*********************************************************************/
bool Role::runActionTwiceAtk()
{
	auto bRet = runArmatureAction(RoleAct_Twice_Atk);
	if (true == bRet)
	{
		Point ptOffset = ptAtkOffset * m_stRoleSubInfo.side * -1.3f;
		setPosition(getPosition() + ptOffset);
	}

	return bRet;
}

/*********************************************************************
** ���ܣ�		��ͨ����������
** ���������	��
** ����ֵ��		bool:true:����ִ�гɹ�
** �޸ļ�¼��	
*********************************************************************/
bool Role::runActionThriceAtk()
{
	auto bRet = runArmatureAction(RoleAct_Thrice_Atk);
	if (true == bRet)
	{
		Point ptOffset = ptAtkOffset * m_stRoleSubInfo.side * -1.8f;
		setPosition(getPosition() + ptOffset);
	}

	return bRet;
}

/*********************************************************************
** ���ܣ�		ִ�б�������
** ���������	��
** ����ֵ�� 	bool:true:����ִ�гɹ�
** �޸ļ�¼��	
*********************************************************************/
bool Role::runActionSmitten()
{
	if (RoleAct_Down == m_stRoleInfo.actSign)						/* ��ǰ���ض��� */
	{
		return runActionDown();
	}
	else
	{
		return runArmatureAction(RoleAct_Smitten);
	}

	return false;
}

/*********************************************************************
** ���ܣ�		ִ�е��ض���
** ���������	��
** ����ֵ�� 	bool:true:����ִ�гɹ�
** �޸ļ�¼��	
*********************************************************************/
bool Role::runActionDown()
{
	this->stopAllActions();
	Point ptOffset = Point(ptAtkOffset.x * ToolFunc::calcRandom(80, 120) * m_stRoleSubInfo.hitSide / 10, 0);
	auto move = MoveBy::create(0.61f, ptOffset);
	runAction(move);
	return runArmatureAction(RoleAct_Down);
}

/*********************************************************************
** ���ܣ�		ִ����������
** ���������	��
** ����ֵ�� 	bool:true:����ִ�гɹ�
** �޸ļ�¼��	
*********************************************************************/
bool Role::runActionDeath()
{
	if ((RoleCamp_Black == m_stRoleInfo.camp) && (1 == UserData::getInstance()->getBlackRoleTotalCount()))
	{
		Director::getInstance()->setAnimationInterval(1.0f/10);
		auto roles = UserData::getInstance()->getRoles();
		for (unsigned int index = 0;index < roles.size();index++)
		{
			auto role = (Role *)roles[index];
			if (RoleStatus_Death != role->getRoleInfo().status)
			{
				role->setAnimateSpeed(1.0f/6);
			}
		}
		deathEffect();
	}
	this->unschedule(schedule_selector(Role::downResume));
	m_stRoleInfo.status = RoleStatus_Death;
	return runArmatureAction(RoleAct_Death);
}

/*********************************************************************
** ���ܣ�		����һ
** ���������	��
** ����ֵ�� 	bool:true:����ִ�гɹ�
** �޸ļ�¼��	
*********************************************************************/
bool Role::runActionSkillOne()
{
	if ((RoleAct_Move >= m_stRoleInfo.actSign) || (true == m_bRoleActBreak))
	{
		return  runArmatureAction(RoleAct_SkillOne);
	}

	return false;
}

/*********************************************************************
** ���ܣ�		���ܶ�
** ���������	��
** ����ֵ�� 	bool:true:����ִ�гɹ�
** �޸ļ�¼��	
*********************************************************************/
bool Role::runActionSkillTwo()
{
	if ((RoleAct_Move >= m_stRoleInfo.actSign) || (true == m_bRoleActBreak))
	{
		return  runArmatureAction(RoleAct_SkillTwo);
	}

	return false;
}

/*********************************************************************
** ���ܣ�		������
** ���������	��
** ����ֵ�� 	bool:true:����ִ�гɹ�
** �޸ļ�¼��	
*********************************************************************/
bool Role::runActionSkillThree()
{
	if ((RoleAct_Move >= m_stRoleInfo.actSign) || (true == m_bRoleActBreak))
	{
		return  runArmatureAction(RoleAct_SkillThree);
	}

	return false;
}

/*********************************************************************
** ���ܣ�		������
** ���������	��
** ����ֵ�� 	bool:true:����ִ�гɹ�
** �޸ļ�¼��	
*********************************************************************/
bool Role::runActionSkillFour()
{
	if ((RoleAct_Move >= m_stRoleInfo.actSign) || (true == m_bRoleActBreak))
	{
		return  runArmatureAction(RoleAct_SkillFour);
	}

	return false;
}
/* ����ִ�� End*/

/*********************************************************************
** ���ܣ�		���ý�ɫת������Ϣ
** ���������	RoleDirection dir: ת����
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void Role::setRoleTurnedDirInfo(RoleDirSign dir)
{
	if (dir != m_stRoleInfo.arAnimate->getScaleX())
	{
		m_stRoleInfo.arAnimate->setScaleX(dir * m_fResScale);
		m_stRoleInfo.arAnimate->setScaleY(m_fResScale);
		m_stRoleSubInfo.side = dir;

		/* ������ɣ������������ã�Ĭ��ǰ�� */
		m_stRoleSubInfo.atkSide = m_stRoleSubInfo.side;

		if (NULL != _roleHealth)
		{
			_roleHealth->setScaleX(dir * 0.3f);
		}
	}
}

/*********************************************************************
** ���ܣ�		���ý�ɫת������Ϣ
** ���������	float xOffset: �ο�������
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void Role::setRoleTurnedDirInfo(float xOffset)
{
	auto dir = RoleDir_Left;
	if (xOffset > getPositionX())									/* ���ý�ɫת�� */
	{
		dir = RoleDir_Right;
	}

	if (dir != m_stRoleInfo.arAnimate->getScaleX())
	{
		m_stRoleInfo.arAnimate->setScaleX(dir * m_fResScale);
		m_stRoleSubInfo.side = dir;

		if (NULL != _roleHealth)
		{
			_roleHealth->setScaleX(dir * 0.3f);
		}
	}
}

/*********************************************************************
** ���ܣ�		��ɫ����
** ���������	Role* role: ������
**				SkillInfo skillInfo: ������Ϣ
**				bool bDown:true:����;false: ������
** ����ֵ��		
** �޸ļ�¼��	
*********************************************************************/
int Role::roleHurt(Role* role, SkillInfo skillInfo, bool bDown)
{
	if (RoleStatus_Death == m_stRoleInfo.status)				/* ����״̬������ */
	{
		return 0;
	}

	auto dmg = skillInfo.damage;
	auto extra = getExtraHarm(role);

	if (dmg > m_stRoleBuff.shield)								/* ���ܷ��� */
	{
		dmg -= m_stRoleBuff.shield;
	}
	else
	{
		m_stRoleBuff.shield -= dmg;
		dmg = 0;
	}
	if (dmg >= m_stRoleInfo.panel.shield)
	{
		dmg -= (m_stRoleInfo.panel.shield);
	}
	else
	{
		m_stRoleInfo.panel.shield -= dmg;
		dmg = 0;
	}

	auto defend = (RoleActMode_Physical != skillInfo.model) ? 
		m_stRoleInfo.panel.mDefend + m_stRoleBuff.mDefend :			/* ���ܹ��� */
		m_stRoleInfo.panel.pDefend + m_stRoleBuff.pDefend;			/* �չ� */
	dmg = (dmg < defend) ? dmg * ToolFunc::calcRandom(50, 100) / 1000 : dmg - defend;
	dmg *= extra;

	/* �˺����� */
	dmg = dmg * ToolFunc::calcRandom(maxActAiLimit - DamageOffset, maxActAiLimit + DamageOffset) * 1.0f / maxActAiLimit;
	dmg = dmg + role->getRoleInfo().panel.realAtk - m_stRoleInfo.panel.realAtkDefend;
	
	if (dmg >= m_stRoleInfo.panel.hpCurrent)
	{
		dmg = m_stRoleInfo.panel.hpCurrent;		
	}

	if (role->getPositionX() > this->getPositionX())		/* ���������ұ� */
	{
		m_stRoleSubInfo.hitSide = RoleDir_Right;			/* �Ҳ౻�� */
	}
	else													/* ����������� */
	{
		m_stRoleSubInfo.hitSide = RoleDir_Left;				/* ��౻�� */
	}
	
	dmg = (int)(dmg + 0.5f);								/* �������� */
	setRoleHitAction(dmg, bDown);
	talentEffect(role, dmg);

	if (((RoleCreMode_XueGong2 == m_eRoleCreMode) || (RoleCreMode_XueGong3 == m_eRoleCreMode) || (RoleCreMode_XueGong4 == m_eRoleCreMode))
		&& (RoleCamp_Black == m_stRoleInfo.camp))
	{		
		dmg = 0;											/* ���ѧ��ģʽ2/3���з���ɫ�����˺�,4˫������Ѫ */
	}

	if ((RoleCreMode_XueGong4 == m_eRoleCreMode) && (RoleCamp_Red == m_stRoleInfo.camp))
	{
		dmg = 0;
		UserData::getInstance()->setJxxg4Grade(dmg);
	}

	m_stRoleInfo.panel.hpCurrent -= dmg;
	if (NULL != _roleHealth)
	{
		auto rate = m_stRoleInfo.panel.hpCurrent * 100.0f / m_stRoleInfo.panel.hpTotal;
		_roleHealth->setPercentage(rate);
	}

	//stopActionByTag(skillMoveTag);									/* ֹͣʩ�ż���ʱ���ƶ� */
	comboResume(0.0f);												/* �չ�������� */
	
	return m_stRoleInfo.panel.hpCurrent;
}

/*********************************************************************
** ���ܣ�		�����˺��ӳ�
** ���������	Role* role: ������
** ����ֵ��		int: �˺�ֵ
** �޸ļ�¼��	
*********************************************************************/
float Role::getExtraHarm(Role* role)
{
	auto dmgExtra = 0.0f;
	auto panel = role->getRoleInfo().panel;
	auto buff = role->getRoleBuff();

	auto cri = panel.critical + buff.critical - m_stRoleInfo.panel.criDefend;/* ���� */
	if (cri > ToolFunc::calcRandom(0, maxActAiLimit) * 1.0f / 10)
	{
		m_ehealthSign = RoleHealth_Critical;							/* ������ */
		dmgExtra = dmgExtra + 0.5f * (1 + panel.criExtra + buff.criExtra);
	}

	dmgExtra += panel.allHarm + buff.allHarm - panel.lowerHarm - buff.lowerHarm;

	if (RoleRace_Power == m_stRoleInfo.race)						/* ���������˺��ӳ� */
	{
		dmgExtra += panel.powerHarm + buff.powerHarm;
	}

	if (RoleRace_Wizard == m_stRoleInfo.race)						/* ���������˺��ӳ� */
	{
		dmgExtra += panel.wizardHarm + buff.wizardHarm;
	}

	if (RoleRace_Speed == m_stRoleInfo.race)						/* ���������˺��ӳ� */
	{
		dmgExtra += panel.speedHarm + buff.speedHarm;
	}

	if (true == role->isRoleLearnedTalent(RoleTalent_ZhiSi))		/* �������� */
	{
		if (m_stRoleInfo.panel.hpCurrent * 1.0f / (m_stRoleInfo.panel.hpTotal + m_stRoleBuff.hpLimit) < 0.25f)
		{
			dmgExtra += 0.15f;
		}
	}

	if (true == role->isRoleLearnedTalent(RoleTalent_YaZhi))		/* ������ѹ�� */
	{
		if (m_stRoleInfo.panel.hpCurrent < panel.hpCurrent)
		{
			dmgExtra += 0.15f;
		}
	}

	return 1 + dmgExtra;
}

/*********************************************************************
** ���ܣ�		�츳ЧӦ
** ���������	Role* role: ������
**				float damage: �ܵ����˺�
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void Role::talentEffect(Role* role, float damage)
{
	auto info = role->getRoleInfo();
	auto buff = role->getRoleBuff();

	if (true == role->isRoleLearnedTalent(RoleTalent_XiXueXiXing))	/* ��Ѫϰ�� */
	{
		auto atk = info.actSign;
		if ((RoleAct_Attack <= atk) && (RoleAct_Thrice_Atk >= atk))
		{
			role->setRoleHpUp(damage * 0.06f);
		}
	}

	if (0 == m_stRoleInfo.panel.hpCurrent)							/* �������� */
	{
		if (true == role->isRoleLearnedTalent(RoleTalent_ZhanSha))	/* ��ѧϰնɱ�츳 */
		{
			role->setRoleHpUp((info.panel.hpTotal + buff.hpLimit) * 0.08f);
		}

		if ((RoleAct_SkillOne <= info.actSign) && (RoleAct_SkillFour >= info.actSign) &&
			(true == role->isRoleLearnedTalent(RoleTalent_GangJingJiSha)))/* ��ѧϰ�ɾ���ɱ�츳 */
		{
			role->setActionCD(info.actSign, 0);
		}
	}

	if (true == role->isRoleLearnedTalent(RoleTalent_PoJia))		/* ���������Ƽ� */
	{
		auto atk = info.actSign;
		if ((RoleAct_Attack <= atk) && (RoleAct_Thrice_Atk >= atk))
		{
			if (0 == m_stRoleBuff.pDefend)							/* ��û���� */
			{
				this->scheduleOnce(schedule_selector(Role::buffDenfendLResume), 2.0f);
			}
			m_stRoleBuff.pDefend = -(m_stRoleInfo.panel.pDefend + m_stRoleBuff.pDefend) * info.panel.pDefendL;
			m_stRoleBuff.mDefend = -(m_stRoleInfo.panel.mDefend + m_stRoleBuff.mDefend) * info.panel.mDefendL;
		}
	}

	if (true == role->isRoleLearnedTalent(RoleTalent_XueMoFa))		/* ������Ѫħ�� */
	{
		role->setRoleHpUp(damage * 0.08f);
	}
	
	if (true == role->isRoleLearnedTalent(RoleTalent_MoNvMiXing))	/* �����ޣ�ħŮ���� */
	{
		auto atk = info.actSign;
		if ((RoleAct_Attack <= atk) && (RoleAct_Thrice_Atk >= atk))
		{
			role->setRoleHpUp(damage * 0.08f);
		}
	}
}

/*********************************************************************
** ���ܣ�		��ɫ����ʱ����
** ���������	int damage: �ܵ����˺�ֵ
**				bool bDown:true:����;false:������
** ����ֵ��		
** �޸ļ�¼��	
*********************************************************************/
void Role::setRoleHitAction(int damage, bool bDown)
{
	bool bFlag = false;

	RoleActSign act = ( true == bDown) ? RoleAct_Down : RoleAct_Smitten;
	if (RoleAct_Down == m_stRoleInfo.actSign)						/* ���ض����б��� */
	{
		act = RoleAct_Down;
		bFlag = true;
	}
	if (damage >= m_stRoleInfo.panel.hpCurrent)
	{
		act = RoleAct_Death;
		bFlag = true;
	}
	else
	{
		if (RoleStatus_Normal == m_stRoleInfo.status)				/* ��ͨ״̬ */
		{
			bFlag = true;
		}
	}

	if (true == bFlag)
	{
		roleUnSchedule(RoleSchedule_Condition);
		m_eRoleActAi = RoleActAi_None;
		showRoleHealthChange(damage);
		runRoleAction(act);
		playHitEffect();
	}
}

/*********************************************************************
** ���ܣ�		hp�仯label
** ���������	int damage: hpֵ
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void Role::showRoleHealthChange(int damage)
{
	LabelAtlas *labelTips = NULL;
	if (RoleHealth_Critical == m_ehealthSign)
	{
		labelTips = LabelAtlas::create("", "res/FightPoints/cri.png", 21, 24, '0');
		auto spCri = Sprite::create("res/FightPoints/Critical.png");
		spCri->setPosition(Point(getPositionX() + 30 * m_stRoleSubInfo.hitSide, getPositionY() + 90));
		this->getParent()->addChild(spCri, 1000);
		auto miss = CallFuncN::create(CC_CALLBACK_1(Role::hpLabelCallBack, this));
		auto seq = Sequence::create(ScaleTo::create(0.15f, 1.5f,1.5f), Spawn::createWithTwoActions(ScaleTo::create(0.2f, 0.8f, 0.8f), 
			MoveBy::create(0.2f, Point(0, 20))), DelayTime::create(0.4f), miss, NULL);
		spCri->runAction(seq);
	}
	else
	{
		if (RoleHealth_RedNormal == m_ehealthSign)
		{
			labelTips = LabelAtlas::create("", "res/FightPoints/nor1.png", 21, 24, '0');
		}
		else if (RoleHealth_OppNormal == m_ehealthSign)
		{
			labelTips = LabelAtlas::create("", "res/FightPoints/nor2.png", 21, 24, '0');
		}
		else
		{
			labelTips = LabelAtlas::create("", "res/FightPoints/up.png", 21, 24, '0');
		}
	}

	labelTips->setPosition(Point(getPositionX() + 20 * m_stRoleSubInfo.hitSide, getPositionY() + 90));
	this->getParent()->addChild(labelTips, 1000);
	labelTips->setAnchorPoint(Point::ANCHOR_MIDDLE);
	auto str = __String::createWithFormat("%d", damage);
	labelTips->setString(str->getCString());
	labelTips->setScale(0.2f);

	auto seq1 = Sequence::create(MoveBy::create(0.15f, Point(0, 30)), DelayTime::create(0.3f), 
		MoveBy::create(0.3f, Point(0, 50)), NULL);
	auto seq2 = Sequence::create(ScaleTo::create(0.15f, 1.2f), DelayTime::create(0.3f), FadeOut::create(0.3f), 
		CallFuncN::create(CC_CALLBACK_1(Role::hpLabelCallBack, this)), NULL);
	labelTips->runAction(Spawn::create(seq1, seq2, NULL));
}

/*********************************************************************
** ���ܣ�		��Ѫ��ʾlabel�ص�����
** ���������	Node *who
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void Role::hpLabelCallBack(Node *who)
{
	who->removeFromParent();
}

/*********************************************************************
** ���ܣ�		��ɫAI
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void Role::runRoleAI()
{
	if (false == checkAIAviable())
	{
		return;
	}

	auto role = (Role *)getNearestRole();							/* ѡ������Ķ��� */
	if (NULL != role)												/* δ��ȡ�����֣������� */
	{
		auto bDanger = false;
		auto danger = 0.0f;
		auto info = role->getRoleInfo();
		auto ptRoleLoc = role->getPosition();

		if ((m_iAiActSeqIndex == m_vctAiActSeq.size()) && (RoleAct_Idle == m_stRoleInfo.actSign))
		{
			setAiActionSequence();									/* Ai��������ִ�е����һ������ */
			roleAiShortMove();
		}
		
		if ((RoleStatus_Invincible == info.status) && (RoleActAi_ShortMove != m_eRoleActAi))/* �Է��޵�״̬��������δ�����ȡ���� */
		{
			runActionIdle();
			roleAiShortMove();										/* ���ֵ��� */
		}

		if (RoleCondition_Normal != info.condition)					/* �з������쳣 */
		{
			auto random = ToolFunc::calcRandom(minActAiLimit, maxActAiLimit);
			if ((random > maxActAiLimit / 2) && (RoleActAi_Pursuit != m_eRoleActAi))
			{
				m_eRoleActAi = RoleActAi_Pursuit;					/* 50%���ʲ�ȡ���� */
			}
		}

		switch (m_eRoleActAi)
		{
		case RoleActAi_None:
			roleAiStep();
			break;
		case RoleActAi_Pursuit:										/* AIִ��׷��ʱ */
			roleAiPursuit(ptRoleLoc);
			break;
		case RoleActAi_Sleep:										/* AI����ʱ���ж�Σ�� */
			calcuRoleDangerSignValue(&bDanger, &danger);
			if (true == bDanger)
			{
				if (m_fActAiLimit[RoleActAi_Pursuit] > ToolFunc::calcRandom(minActAiLimit, maxActAiLimit))
				{
					roleUnSchedule(RoleSchedule_AiAction);			/* �ж����߼�ʱ�� */
				}
			}		
			break;
		default:
			break;
		}
	}
}

/*********************************************************************
** ���ܣ�		������ɫAI
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void Role::runRoleMainAI()
{
	if (false == checkAIAviable())
	{
		return;
	}
#if 1
	//(true == m_bRoleActBreak) && (RoleAct_Thrice_Atk != m_stRoleInfo.actSign)
	if ((RoleAct_Idle == m_stRoleInfo.actSign) || (true == m_bRoleActBreak))
	{
		auto role = (Role *)getNearestRole();						/* ѡ������Ķ��� */
		if (NULL != role)
		{
			auto act = (RoleActSign)(m_iRoleCombo + RoleAct_Attack);
			auto ptOffset = this->getPosition() - role->getPosition();

			if ((m_stSkillInfo[act].xAtkDis >= abs(ptOffset.x)) && (m_stSkillInfo[act].yAtkDis >= abs(ptOffset.y)))
			{
				setRoleTurnedDirInfo(role->getPositionX());			/* ��ǰ�ͷŵļ����ܹ���������,���ý�ɫת�� */
				runRoleAction(act);
			}
		}
	}

	if (RoleAct_Move == m_stRoleInfo.actSign)
	{
		auto ptDir = m_ptMoveDes - getPosition();
		if ((abs(ptDir.x) < 1.0f) || (abs(ptDir.y) < 1.0f))				/* ��Χ */
		{
			runActionIdle();
		}
	}
#endif
}

/*********************************************************************
** ���ܣ�		Ai��Ϊѡ��
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void Role::roleAiStep()
{
	if (RoleAct_Idle != m_stRoleInfo.actSign)
	{
		return;
	}

	auto random = ToolFunc::calcRandom(minActAiLimit, maxActAiLimit);
	if (random < m_fActAiLimit[RoleActAi_Pursuit])					/* ׷�� */
	{
		m_eRoleActAi = RoleActAi_Pursuit;
	}
	else if ((random < m_fActAiLimit[RoleActAi_ShortMove])) 		/* ���� */
	{
		roleAiShortMove();
	}
	else															/* ���� */
	{
		if (random < m_fActAiLimit[RoleActAi_Sleep])
		{
			roleAiSleep();
		}
	}
}

/*********************************************************************
** ���ܣ�		Ai��Ϊ���
** ���������	Point ptObj: Ŀ��λ��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void Role::roleAiPursuit(Point ptObj)
{
	if (m_iAiActSeqIndex >= m_vctAiActSeq.size() )
	{
		return;
	}
	
	auto act = m_vctAiActSeq[m_iAiActSeqIndex];
	auto ptOffset = ptObj - getPosition();
	
	if ((m_stSkillInfo[act].xAtkDis >= abs(ptOffset.x)) && (m_stSkillInfo[act].yAtkDis >= abs(ptOffset.y)) 
		|| (RoleActMode_Guard == m_stActMode[act]))
	{
		setRoleTurnedDirInfo(ptObj.x);						/* ��ǰ�ͷŵļ����ܹ���������,���ý�ɫת�� */
		if (true == runRoleAction(act))
		{
			m_iAiActSeqIndex ++;
		}
	}
	else
	{
		setMoveVector(ptObj);
		runRoleAction(RoleAct_Move);
	}
}

/*********************************************************************
** ���ܣ�		Ai��Ϊ�̾����ƶ�
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void Role::roleAiShortMove()
{
	if (RoleActAi_ShortMove != m_eRoleActAi)
	{
		auto center = SceneWidth * (m_iSceneID + 0.5f);				/* ��ͼ�ƶ���������x���� */
		auto delta = (getPositionX() - SceneWidth * m_iSceneID) / SceneWidth + 1;
		if (getPositionX() < center)
		{
			delta = (SceneWidth * (m_iSceneID + 1) - getPositionX()) / SceneWidth + 1;
		}
		/* a1Ϊdelta������Ϊdelta�ĵȲ����� */
		auto sum = int(90 * 181 * delta * 100);						/* ǰ180��ͣ��Ŵ�100�����չ�deltaС�����֣� */
		auto item = 0;												/* ���Ҫȡ�ڼ��� */
		auto oddsItem = 0;											/* �ɹ����� */
		auto temp = 0;
		while (true)
		{
			item = ToolFunc::calcRandom(1, 180);
			temp = (getPositionX() < center) ? 180 - item : item;
			oddsItem = int(temp * delta * 100);
			if (oddsItem > ToolFunc::calcRandom(1, sum))			/* ȡ�� */
			{
				break;
			}
		}

		auto sign = (ToolFunc::calcRandom(1, 100) > 50) ? 1 : -1;	/* ���·������ */
		auto radian = CC_DEGREES_TO_RADIANS(item) * sign;
		m_ptMoveDir.x = cos(radian);
		m_ptMoveDir.y = sin(radian);								/* �ݷ����ٶ�΢�� */
		m_ptMoveDir = m_ptMoveDir * m_stRoleSubInfo.speed;

		auto duration = ToolFunc::calcRandom(MoveDuration * 30, MoveDuration * 50) * 0.02f;
		roleUnSchedule(RoleSchedule_AiAction);
		m_eRoleActAi = RoleActAi_ShortMove;
		roleSchedule(duration, RoleSchedule_AiAction);
		runActionMove();
	}
}

/*********************************************************************
** ���ܣ�		Ai��Ϊ����
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void Role::roleAiSleep()
{
	if (RoleActAi_None == m_eRoleActAi)
	{
		if ((RoleAct_Move == m_stRoleInfo.actSign) || (RoleAct_Idle == m_stRoleInfo.actSign))
		{
			auto duration = ToolFunc::calcRandom(SleepDuration * 40, SleepDuration * 70) * 0.03f;
			roleUnSchedule(RoleSchedule_AiAction);
			m_eRoleActAi = RoleActAi_Sleep;
			roleSchedule(duration, RoleSchedule_AiAction);
		}
	}
}

/* AI�������� Begin */
/*********************************************************************
** ���ܣ�		�ж�AI��Ч��
** ���������	
** ����ֵ��		
** �޸ļ�¼��	
*********************************************************************/
bool Role::checkAIAviable()
{
	bool bRet = true;

	if (RoleCamp_Red == m_stRoleInfo.camp)
	{
		auto total = UserData::getInstance()->getBlackRoleTotalCount();
		if (0 == total)
		{
			roleUnSchedule(RoleSchedule_AiAction);
			m_eRoleWarMsg = RoleWarMsg_Over;
			return false;
		}

		auto black = UserData::getInstance()->getBlackRoleCount(m_iSceneID);
		if (0 == black)
		{
			if ((RoleAct_Move == m_stRoleInfo.actSign) || (RoleAct_Idle == m_stRoleInfo.actSign))/* ��ǰ�����Ѳ������ */
			{
				roleUnSchedule(RoleSchedule_AiAction);
				m_eRoleWarMsg = RoleWarMsg_Pause;
				return false;
			}
		}
	}
	else
	{
		auto red = UserData::getInstance()->getRedRoleCount();
		if (0 == red)
		{
			roleUnSchedule(RoleSchedule_AiAction);
			m_eRoleWarMsg = RoleWarMsg_Over;
			return false;
		}
	}

	if (RoleCondition_Normal != m_stRoleInfo.condition) 			/* �쳣״̬ */
	{
		bRet = false;
	}

	return bRet;
}

/*********************************************************************
** ���ܣ�		���������ɫ�Ƿ���Σ��
** ���������	bool *bDanger: �ý�ɫΣ��ֵ
**				float *dangerDis: �ý�ɫ���Σ�վ���
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void Role::calcuRoleDangerSignValue(bool *bDanger, float *dangerDis)
{
	auto dis = 0.0f;
	auto ptLoc = getPosition();
	auto roles = UserData::getInstance()->getRoles();

	for (unsigned int index = 0;index < roles.size();index ++)
	{
		auto Opponent = (Role *)roles[index];
		auto info = Opponent->getRoleInfo();

		if ((m_stRoleInfo.camp == info.camp) || (RoleCondition_Normal != info.condition))
		{
			continue;												/* ͬ��Ӫ���쳣״̬������ */
		}

		if (true == Opponent->checkRoleCanBeHit(ptLoc))
		{
			*bDanger = true;
			dis = ptLoc.getDistance(getPosition());
			if (dis < *dangerDis)									/* ȡ�����Σ�վ��� */
			{
				*dangerDis = dis;
			}
		}
	}
}

/*********************************************************************
** ���ܣ�		��ȡ�ƶ�����
** ���������	Point ptDes: Ŀ������
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void Role::setMoveVector(Point ptDes)
{
	if (ptDes != m_ptMoveDes)
	{
		m_ptMoveDes = ptDes;
		auto ptOffset = ptDes - getPosition();
		auto radian = ptOffset.getAngle();
		m_ptMoveDir.x = cos(radian);
		m_ptMoveDir.y = sin(radian);									/* �ݷ����ٶ�΢�� */
		m_ptMoveDir = m_ptMoveDir * m_stRoleSubInfo.speed;
	}
}

/*********************************************************************
** ���ܣ�		�ж�ָ����ɫ�Ƿ��ڹ�����Χ
** ���������	Point ptLoc: Ҫ���Ľ�ɫ����
** ����ֵ��		bool:true: ���Լ��Ĺ�����Χ
** �޸ļ�¼��	
*********************************************************************/
bool Role::checkRoleCanBeHit(Point ptLoc)
{
	bool bRet = false;

	if (RoleStatus_Invincible == m_stRoleInfo.status)				/* ûִ�ж���:pass */
	{
		return bRet;
	}

	int index = 0;
	auto ptOffset = ptLoc - getPosition();							/* ���λ�� */

	for (index = 0;(unsigned int)index < m_vctAiActSeq.size();index ++)
	{
		auto act = m_vctAiActSeq[index];
		if ((m_stSkillInfo[act].xAtkDis >= abs(ptOffset.x)) && (m_stSkillInfo[act].yAtkDis >= abs(ptOffset.y)))
		{
			bRet = true;											/* ���㹥������Ĺ������� */
			break;
		}
	}

	return bRet;
}

/*********************************************************************
** ���ܣ�		��ȡ�з�����Ľ�ɫ
** ���������	��
** ����ֵ��		Node������Ľ�ɫ�ڵз���Ӫ�Ľ�ɫ
** �޸ļ�¼��	
*********************************************************************/
Role* Role::getNearestRole()
{
	Role	*node = NULL;
	auto	distance = 0.0f;
	auto	vec = UserData::getInstance()->getRoles();
	auto	len = vec.size();
	auto	sz = Director::getInstance()->getWinSize();
	auto	dis = sz.width + sz.height;

	for (unsigned int index = 0;index < len;index ++)
	{
		auto temp = (Role *)vec[index];
		auto info = temp->getRoleInfo();

		if ((m_stRoleInfo.camp != info.camp) && (temp->getSceneID() == m_iSceneID) && (RoleStatus_Invincible != info.status)
			&& (RoleStatus_Death != info.status))					/* ͬһ��Ӫ����ͬ�����������޵У�pass */
		{
			auto ptLoc = temp->getPosition() - getPosition();		/* ����ǰ���� */
			distance = abs(ptLoc.x) + abs(ptLoc.y);
			if (dis > distance)
			{
				dis = distance;
				node = temp;
			}
		}
	}

	return node;
}

/*********************************************************************
** ���ܣ�		���������㹹�����
** ���������	Point p1������1
**				Point p2������2
** ����ֵ��		Rect
** �޸ļ�¼��	
*********************************************************************/
Rect Role::getRectByTwoPoint(Point p1, Point p2)
{
	auto ptOffset = p1 - p2;
	auto ptDes = ptInvalid;
	ptDes.x = ToolFunc::calcRandom(minActAiLimit, abs(ptOffset.x)) / 2;
	ptDes.y = ToolFunc::calcRandom(minActAiLimit, abs(ptOffset.y)) / 2;

	if ((p1.x > p2.x) && (p1.y > p2.y))							/* p1��p2���Ͻ� */
	{
		return Rect(p1.x - ptDes.x, p1.y - ptDes.y, ptDes.x, ptDes.y);
	}
	if ((p1.x < p2.x) && (p1.y > p2.y))							/* p1��p2���Ͻ� */
	{
		return Rect(p1.x, ptDes.y, ptDes.x, ptDes.y);
	}
	if ((p1.x < p2.x) && (p1.y < p2.y))							/* p1��p2���½� */
	{
		return Rect(p1.x, p1.y, ptDes.x, ptDes.y);
	}
	if ((p1.x > p2.x) && (p1.y < p2.y))							/* p1��p2���½� */
	{
		return Rect(p1.x - ptDes.x, p1.y, ptDes.x, ptDes.y);
	}

	return Rect(0, 0, 0, 0);
}

/*********************************************************************
** ���ܣ�		������λ�úͷ�Χ�������
** ���������	Size sz����Χ
** ����ֵ��		Rect
** �޸ļ�¼��	
*********************************************************************/
Rect Role::getRectBySize(Size sz)
{
	Rect rc(0, 0, 0, 0);

	rc.origin.x = getPositionX() - sz.width / 2;
	rc.origin.y = getPositionY() - sz.height / 2;
	rc.size = sz;

	return rc;
}
/* AI�������� End */