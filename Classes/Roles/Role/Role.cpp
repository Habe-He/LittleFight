#include "Role.h"
#include "Counterpart/Counterpart_Def.h"
#include "Counterpart/MainFight.h"
#include "DataManager/DataManager.h"

USING_NS_CC;
using namespace cocostudio;

/* 动画帧事件 */
const std::string strFrameEventName[FrameEvent_Max] = 
{
	"begin",										/* 动作准备完毕（开始霸体） */
	"end",											/* 动作开始收招（结束霸体） */
	"attack",										/* 攻击事件（不倒地） */
	"attack-fd",									/* 攻击事件（倒地） */
	"shot",											/* 发射事件（不倒地） */
	"shot-fd",										/* 发射事件（倒地） */
	"invincible",									/* 无敌事件 */
	"interrupt",									/* 中断动作事件 */
	"left",											/* 攻击方向: 前 */
	"middle",										/* 攻击方向: 前后双方向 */
	"right",										/* 攻击方向: 后 */
};

/* 技能动作名称 */
const std::string strRoleSkillName[RoleAct_Max] =
{
	"loading",
	"attack",
	"twice-atk",									/* 二连击 */
	"thrice-atk",									/* 三连击 */
	"run",
	"sa",
	"sb",
	"sc",
	"sd",
	"smitten",										/* 被击 */
	"down",											/* 倒地 */
	"down"
};

const std::string strFlightPropPath = "Roles/FlightProps/";	/* 资源路径 */
const float RaceFactor[RoleRace_Max] = {0.0f, 1.2f, 1.0f, 0.8f};	/* 职业影响技能比率 */

Role::Role()
{
}

Role::~Role(void)
{
}

/*********************************************************************
** 功能：		初始化角色变量
** 输入参数：	std::string strName: 角色名字
**				RoleCreMode mode: 角色创建模式
**				float resScale: 资源缩放比例
** 返回值：		bool
** 修改记录：	
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

	initActInherent();												/* 初始化角色技能属性 */
	initFlightPropInfo();											/* 初始化技能飞行道具 */
	loadArmature();
	runActionIdle();	
	initSubInfo();
	initSkillRegion();

	if (RoleCreMode_Preview == m_eRoleCreMode)						/* 预览模式 */
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
** 功能：		执行角色动作
** 输入参数：	RoleActSign act：动作
** 返回值： 	无
** 修改记录：	
*********************************************************************/
bool Role::runRoleAction(RoleActSign act)
{
	bool bRet = false;

	switch ( act)
	{
	case RoleAct_Idle:												/* 空闲 */
		bRet = runActionIdle();
		break;
	case RoleAct_Move:												/* 移动 */
		bRet = runActionMove();
		break;
	case RoleAct_Attack:											/* 攻击 */
	case RoleAct_Twice_Atk:
	case RoleAct_Thrice_Atk:
		bRet = runActionAtkCtrl();
		break;
	case RoleAct_Smitten:											/* 被击 */
		bRet = runActionSmitten();
		break;
	case RoleAct_Down:												/* 倒地 */
		bRet = runActionDown();
		break;
	case RoleAct_Death:												/* 死亡 */
		bRet = runActionDeath();
		break;
	case RoleAct_SkillOne:											/* 技能一 */
		bRet = runActionSkillOne();
		break;
	case RoleAct_SkillTwo:											/* 技能二 */
		bRet = runActionSkillTwo();
		break;
	case RoleAct_SkillThree:										/* 技能三 */
		bRet = runActionSkillThree();
		break;
	case RoleAct_SkillFour:											/* 技能四 */
		bRet = runActionSkillFour();
		break;
	}

	return bRet;
}

/*********************************************************************
** 功能：		执行动作（主将操作接口）
** 输入参数：	RoleCmdSign cmd：指令ID
**				Point ptMove: 移动目的地
** 返回值：		bool
** 修改记录：	
*********************************************************************/
bool Role::runLordlAction(RoleCmdSign cmd, Point ptMove)
{
	if ((RoleCondition_Normal != m_stRoleInfo.condition) ||			/* 异常状态不处理 */
		(0 == UserData::getInstance()->getBlackRoleCount(m_iSceneID)))
	{
		return false;
	}

	RoleActSign act = RoleAct_Max;
	switch (cmd)
	{
	case RoleCmdSign_Move:											/* 移动 */
		setMoveVector(ptMove);
		m_ptMoveDes = ptMove;
		act = RoleAct_Move;
		break;
	case RoleCmdSign_Attack:										/* 攻击 */
		act = RoleAct_Attack;
		break;
	case RoleCmdSign_SkillOne:										/* 技能一 */
		act = RoleAct_SkillOne;
		break;
	case RoleCmdSign_SkillTwo:										/* 技能二 */
		act = RoleAct_SkillTwo;
		break;
	case RoleCmdSign_SkillThree:									/* 技能三 */
		act = RoleAct_SkillThree;
		break;
	case RoleCmdSign_SkillFour:										/* 技能四 */
		act = RoleAct_SkillFour;
		break;
	case RoleCmdSign_Release:
		act = RoleAct_Idle;
		break;
	}

	return runRoleAction(act);
}

/*********************************************************************
** 功能：		初始化角色信息
** 输入参数：	role_camp camp:阵营
**				RoleModel mode:类型
**				RoleRace race: 角色职业
** 返回值： 	无
** 修改记录：	
*********************************************************************/
void Role::initRoleInfo(RoleCamp camp, RoleMode mode, RoleRace race)
{
	m_stRoleInfo.actSign = RoleAct_Idle;
	m_stRoleInfo.condition = RoleCondition_Normal;
	m_stRoleInfo.camp = camp;
	m_stRoleInfo.mode = mode;
	m_stRoleInfo.race = race;
	m_stRoleInfo.status = RoleStatus_Normal;

	initActAiLimit();												/* 设置Ai行为的概率 */

	if (RoleCamp_Red == camp)										/* 我方朝右 */
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
** 功能：		设置天赋buff
** 输入参数：	无
** 返回值：		无
** 修改记录：	
*********************************************************************/
void Role::initTalentEffect()
{
	DataManager::getInstance()->isGetTalentDate(m_iRolePkID);	/* 获取天赋 */
	auto talent = DataManager::getInstance()->interTalentVectors();
	for (unsigned int index = 0;index < talent.size();index++)
	{
		m_stRoleInfo.panel.talent = (m_stRoleInfo.panel.talent << 8) | (talent[index] - 70000);
	}

	if (0 == m_stRoleInfo.panel.talent)							/* 无天赋 */
	{
		return;
	}

	if (true == isRoleLearnedTalent(RoleTalent_ShiHua))			/* 石化 */
	{
		m_stRoleInfo.panel.pDefend *= 1.04f;
		m_stRoleInfo.panel.mDefend *= 1.04f;
	}
	if (true == isRoleLearnedTalent(RoleTalent_FuSuZhiFeng))	/* 复苏之风 */
	{
		m_stRoleInfo.panel.hpBack += 12;
	}
	if (true == isRoleLearnedTalent(RoleTalent_GeDang))			/* 格挡 */
	{
		m_stRoleInfo.panel.lowerHarm += 0.03f;
	}
	if (true == isRoleLearnedTalent(RoleTalent_XueYeFeiTeng))	/* 血液沸腾 */
	{
		m_stRoleInfo.panel.hpTotal *= 1.06f;
	}
	if (true == isRoleLearnedTalent(RoleTalent_JuRen))			/* 巨人 */
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
	if (true == isRoleLearnedTalent(RoleTalent_QianFeng))		/* 前锋 */
	{
		m_stRoleInfo.panel.atk *= 1.04f;
	}
	if (true == isRoleLearnedTalent(RoleTalent_ZhengMianDuiJue))/* 正面对决 */
	{
		m_stRoleInfo.panel.speedHarm += 0.06f;
	}
	if (true == isRoleLearnedTalent(RoleTalent_PoZaiMeiJie))	/* 迫在眉睫 */
	{
		this->schedule(schedule_selector(Role::buffHarmGrow), 20.0f);
	}
	if (true == isRoleLearnedTalent(RoleTalent_LiLiangBaoFa))	/* 力量爆发 */
	{
		m_stRoleInfo.panel.atk += 75;
	}
	if (true == isRoleLearnedTalent(RoleTalent_FuWenHuDun))		/* 符文护盾 */
	{
		m_stRoleInfo.panel.shield = m_stRoleInfo.panel.hpTotal * 0.1f;
	}
	if (true == isRoleLearnedTalent(RoleTalent_PoMoZhiRen))		/* 破魔之刃 */
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
	if (true == isRoleLearnedTalent(RoleTalent_DunQiang))		/* 盾墙 */
	{
		m_stRoleInfo.panel.lowerHarm += 0.05f;
	}
	if (true == isRoleLearnedTalent(RoleTalent_WuShiLieRen))	/* 巫师猎人 */
	{
		m_stRoleInfo.panel.wizardHarm += 0.06f;
	}
	if (true == isRoleLearnedTalent(RoleTalent_KuangNu))		/* 狂怒 */
	{
		m_stRoleInfo.panel.atk *= 1.05f;
	}
	if (true == isRoleLearnedTalent(RoleTalent_GongFaJianBei))	/* 功法兼备 */
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
	if (true == isRoleLearnedTalent(RoleTalent_CaoYaoZhuanJia))	/* 草药专家 */
	{
		this->schedule(schedule_selector(Role::buffHpBack), 25.0f);
	}
	if (true == isRoleLearnedTalent(RoleTalent_ZhiYu))			/* 治愈 */
	{
		m_stRoleInfo.panel.hpBack += m_stRoleInfo.panel.hpTotal * 0.01f;
	}
	if (true == isRoleLearnedTalent(RoleTalent_YinMouJia))		/* 阴谋家 */
	{
		m_stRoleInfo.panel.powerHarm += 0.06f;
	}
}

/*********************************************************************
** 功能：		设置角色信息
** 输入参数：	RoleInfo info: 角色信息
** 返回值： 	无
** 修改记录：	
*********************************************************************/
void Role::setRoleInfo(RoleInfo info)
{
	memset(&m_stRoleInfo, 0, sizeof(RoleInfo));
	memcpy(&m_stRoleInfo, &info, sizeof(RoleInfo));
}

/*********************************************************************
** 功能：		设置角色buff
** 输入参数：	RoleBuff buff: 角色信息
** 返回值： 	无
** 修改记录：	
*********************************************************************/
void Role::setRoleBuff(RoleBuff buff)
{
	memset(&m_stRoleBuff, 0, sizeof(RoleBuff));
	memcpy(&m_stRoleBuff, &buff, sizeof(RoleBuff));
}

/*********************************************************************
** 功能：		角色属性设置
** 输入参数：	RolePanel panel: 角色属性
** 返回值： 	无
** 修改记录：	
*********************************************************************/
void Role::setRolePanel(RolePanel panel)
{
	memset(&(m_stRoleInfo.panel), 0, sizeof(RolePanel));
	memcpy(&(m_stRoleInfo.panel), &panel, sizeof(RolePanel));
}

/*********************************************************************
** 功能：		角色技能属性
** 输入参数：	SkillInfo *info: 角色技能属性
** 返回值： 	无
** 修改记录：	
*********************************************************************/
void Role::setRoleSkillInfo(SkillInfo *info)
{
	memset(m_stSkillInfo, 0, sizeof(SkillInfo) * RoleAct_Max);
	memcpy(m_stSkillInfo, info, sizeof(SkillInfo) * RoleAct_Max);
}

/*********************************************************************
** 功能：		hp恢复
** 输入参数：	int hp: hp回复量
** 返回值：		无
** 修改记录：	
*********************************************************************/
void Role::setRoleHpUp(int hp)
{
	m_stRoleBuff.hpBack += hp;
	m_ehealthSign = RoleHealth_Up;
	showRoleHealthChange(hp);
}

/*********************************************************************
** 功能：		异常状态设置
** 输入参数：	RoleCondition condition: 异常状态
**				float dt: 异常状态持续时间
** 返回值：		无
** 修改记录：	
*********************************************************************/
void Role::setRoleCondition(RoleCondition condition, float dt)
{
	stopArmatureAction();

	if (condition > m_stRoleInfo.condition)						/* 异常状态按优先级覆盖 */
	{
		roleUnSchedule(RoleSchedule_Condition);
		m_stRoleInfo.condition = condition;
		m_eRoleActAi = RoleActAi_None;
		roleSchedule(dt, RoleSchedule_Condition);
	}
}

/*********************************************************************
** 功能：		异常状态设置
** 输入参数：	int damage: 异常状态秒伤
**				float dt: 伤害持续时间
** 返回值：		无
** 修改记录：	
*********************************************************************/
void Role::setRoleAbnormalDamage(int damage, float dt)
{
	roleUnSchedule(RoleSchedule_Abnormal);
	roleSchedule(dt, RoleSchedule_Abnormal);
}

/*********************************************************************
** 功能：		重置角色动作cd
** 输入参数：	RoleActSign act: 动作id
**				float cd: cd值
** 返回值：		无
** 修改记录：	
*********************************************************************/
void Role::setActionCD(RoleActSign act, float cd)
{
	m_fActCD[act] = 0.0f;
}

/*********************************************************************
** 功能：		武将主键ID
** 输入参数：	int pk: 武将主键ID
** 返回值：		无
** 修改记录：	
*********************************************************************/
void Role::setRolePkID(int pk)
{
	m_iRolePkID = pk;
	auto property = DataManager::getInstance()->interGeneralVector();/* 获取武将信息 */

	/* 装备 */
	DataManager::getInstance()->equipDataParser();
	auto equips = DataManager::getInstance()->localEquipProptyVector();
	auto evoRule = DataManager::getInstance()->localEquipRefineVector();
	
	for (int index = 0;index < 6;index ++)							/* 技能 */
	{
		if (0 == property[0].equipID[index])
		{
			continue;
		}

		auto equip = equips[property[0].equipID[index] - 94001];
		if (index < 4)												/* 4件普攻装备 */
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
		else														/* 2件奇珍异宝 */
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
** 功能：		武将主键ID
** 输入参数：	无
** 返回值：		int pk: 武将主键ID
** 修改记录：	
*********************************************************************/
int Role::getRolePkID()
{
	return m_iRolePkID;
}

/*********************************************************************
** 功能：		武将ID
** 输入参数：	int id: 武将ID
** 返回值：		无
** 修改记录：	
*********************************************************************/
void Role::setRoleID(int id)
{
	m_iRoleID = id;
	
	DataManager::getInstance()->SkillNameDataParser();				/* 技能基础表 */
	auto skills = DataManager::getInstance()->localSkillNameVector();

	initSkillGains();
	initJxxgBuff();

	//攻击力*（1-法防/(法防+等级*73+877））+等级*80*0.8	伤害公式基础
	auto panel = m_stRoleInfo.panel;
	auto baseDamage = panel.atk * (1 - panel.mDefend * 1.0f / (panel.mDefend + panel.level * 73 + 877)) + panel.level * 64;

	//DataManager::getInstance()->SkillUpgradeDataParser();			/* 技能升级规则 */
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
** 功能：		武将ID
** 输入参数：	无
** 返回值：		int: 武将ID
** 修改记录：	
*********************************************************************/
int Role::getRoleID()
{
	return m_iRoleID;
}

/*********************************************************************
** 功能：		角色信息获取
** 输入参数：	无
** 返回值：		无
** 修改记录：	
*********************************************************************/
RoleInfo Role::getRoleInfo()
{
	return m_stRoleInfo;
}

/*********************************************************************
** 功能：		获取buff
** 输入参数：	无
** 返回值：		RoleBuff:
** 修改记录：	
*********************************************************************/
RoleBuff Role::getRoleBuff()
{
	return m_stRoleBuff;
}

/*********************************************************************
** 功能：		获取角色技能数据
** 输入参数：	无
** 返回值：		SkillInfo* : 角色技能数据
** 修改记录：	
*********************************************************************/
SkillInfo* Role::getRoleSkillInfo()
{
	return m_stSkillInfo;
}

/*********************************************************************
** 功能：		重置界面技能按钮设置的cd
** 输入参数：	无
** 返回值：		无
** 修改记录：	
*********************************************************************/
void Role::resetUISkillBtnCD()
{
	if (RoleMode_Main == m_stRoleInfo.mode)		/* 主将 */
	{
		auto roleLayer = this->getParent();			/* 获取角色层 */
		auto fight = (MainFight*)roleLayer->getParent()->getChildByTag(order_MainFight);
		for (int index = MFCtrl_Sa;index <= MFCtrl_Sd;index ++)
		{
			fight->resetActCD(index, m_stSkillInfo[index + RoleAct_SkillOne - MFCtrl_Sa].cd);
		}
	}
}

/*********************************************************************
** 功能：		设置动画速率
** 输入参数：	float speed: 速率
** 返回值：		无
** 修改记录：	
*********************************************************************/
void Role::setAnimateSpeed(float speed)
{
	m_stRoleInfo.arAnimate->getAnimation()->setSpeedScale(speed);
}

/*********************************************************************
** 功能：		复活
** 输入参数：	无
** 返回值：		无
** 修改记录：	
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

/* 设置角色HP、MP显示控件 */
void Role::setHealthCtrl(Node *health)
{
	m_nHealth = health;
}

/* 获取角色HP、MP显示控件 */
void Role::removeHealthCtrl()
{
	if (NULL != m_nHealth)
	{
		m_nHealth->removeFromParentAndCleanup(true);
		m_nHealth = NULL;
	}
}

/*********************************************************************
** 功能：		杂鱼Ai攻击序列
** 输入参数：	无
** 返回值：		无
** 修改记录：	
*********************************************************************/
void Role::aiActSequenceSoldier()
{
	m_vctAiActSeq.clear();
	m_vctAiActSeq.push_back(RoleAct_Attack);
}

/*********************************************************************
** 功能：		小伙伴Ai攻击序列
** 输入参数：	无
** 返回值：		无
** 修改记录：	
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
	if (random > maxActAiLimit * 3 / 4)							/* 取1个技能 */
	{
		int sNum = 0;												/* 开启的技能数 */
		int skill[4] = {0};											/* 开启的技能 */
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
** 功能：		Boss Ai攻击序列
** 输入参数：	无
** 返回值：		无
** 修改记录：	
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
		int sNum = 0;												/* 开启的技能数 */
		int skill[4] = {0};											/* 开启的技能 */
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
** 功能：		主将 Ai攻击序列
** 输入参数：	无
** 返回值：		无
** 修改记录：	
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
** 功能：		加载动画资源
** 输入参数：	无
** 返回值： 	无
** 修改记录：	
*********************************************************************/
void Role::loadArmature()
{
}

/*********************************************************************
** 功能：		初始化角色生命显示条
** 输入参数：	无
** 返回值： 	无
** 修改记录：	
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
** 功能：		设置角色副属性
** 输入参数：	无
** 返回值： 	无
** 修改记录：	
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
** 功能：		设置Ai行为的概率
** 输入参数：	无
** 返回值： 	无
** 修改记录：	
*********************************************************************/
void Role::initActAiLimit()
{
	memcpy(m_fActAiLimit, roleActAiLimit[m_stRoleInfo.mode], sizeof(int) * RoleActAi_Max);

	if (RoleMode_Soldier == m_stRoleInfo.mode)
	{
		auto mode = UserData::getInstance()->getFightDifficulty();
		if (1 == mode)
		{
			m_fActAiLimit[RoleActAi_Pursuit] = 350;					/* 精英模式，攻击几率定位35% */
			m_fActAiLimit[RoleActAi_ShortMove] = 850;				/* 精英模式，移动几率定位50% */
		}
	}
}

/*********************************************************************
** 功能：		设置角色技能属性
** 输入参数：	无
** 返回值： 	无
** 修改记录：	
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
** 功能：		设置技能等级的属性增益
** 输入参数：	无
** 返回值：		无
** 修改记录：	
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
//	攻击 生命值 物防 法防

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
** 功能：		初始化稷下学宫buff
** 输入参数：	无
** 返回值：		无
** 修改记录：	
*********************************************************************/
void Role::initJxxgBuff()
{
	if ((RoleCreMode_Fighting != m_eRoleCreMode) && (RoleCamp_Red == m_stRoleInfo.camp))
	{
		return;														/* 关卡模式才需要 */
	}

	auto jxxgBuffInfo = DataManager::getInstance()->interJxxgBuffVector();
	if (0 < jxxgBuffInfo.size())
	{
		auto num = jxxgBuffInfo[0].num%10;							/* 取当前buff剩余关卡次数 */
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
** 功能：		设置Ai攻击序列
** 输入参数：	无
** 返回值：		无
** 修改记录：	
*********************************************************************/
void Role::setAiActionSequence()
{
	switch ( m_stRoleInfo.mode)
	{
	case RoleMode_Soldier:											/* 杂鱼Ai攻击序列 */
		aiActSequenceSoldier();
		break;
	case RoleMode_Main:												/* 主将 Ai攻击序列 */
		aiActSequenceMain();
		break;
	case RoleMode_Companion:										/* 小伙伴Ai攻击序列 */
		aiActSequenceCompanion();
		break;
	case RoleMode_Boss:												/* Boss Ai攻击序列 */
		aiActSequenceBoss();
		break;
	default:
		break;
	}

	m_iAiActSeqIndex = 0;
}

/*********************************************************************
** 功能：		初始化角色技能属性
** 输入参数：	无
** 返回值：		无
** 修改记录：	
*********************************************************************/
void Role::initActInherent()
{
	memset(m_stActMode, 0, sizeof(m_stActMode));
	
	m_stActMode[RoleAct_Attack] = RoleActMode_Physical;			/* 攻击 */
	m_stActMode[RoleAct_Twice_Atk] = RoleActMode_Physical;		/* 二连击 */
	m_stActMode[RoleAct_Thrice_Atk] = RoleActMode_Physical;		/* 三连击 */
	m_stActMode[RoleAct_SkillOne] = RoleActMode_Magic;			/* 技能一 */
	m_stActMode[RoleAct_SkillTwo] = RoleActMode_Magic;			/* 技能二 */
	m_stActMode[RoleAct_SkillThree] = RoleActMode_Magic;			/* 技能三 */
	m_stActMode[RoleAct_SkillFour] = RoleActMode_Magic;			/* 技能四 */
}

/*********************************************************************
** 功能：		初始化技能飞行道具
** 输入参数：	无
** 返回值：		无
** 修改记录：	
*********************************************************************/
void Role::initFlightPropInfo()
{
}

/*********************************************************************
** 功能：		获取动画事件名称
** 输入参数：	RoleFrameEvent evt: 事件名称索引
** 返回值：		std::string：事件名称
** 修改记录：	
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
** 功能：		获取飞行道具资源路径
** 输入参数：	无
** 返回值：		无
** 修改记录：	
*********************************************************************/
std::string Role::getFlightPropPath()
{
	return strFlightPropPath;
}

/*********************************************************************
** 功能：		播放音效
** 输入参数：	
** 返回值：		
** 修改记录：	
*********************************************************************/
unsigned int Role::playEffectOgg(const char* pszFilePath, bool bLoop, float pitch, float pan, float gain)
{
	return ToolFunc::playEffectFile(pszFilePath, bLoop, pitch, pan, gain);
}

/*********************************************************************
** 功能：		角色是否习得天赋
** 输入参数：	RoleTalent talent: 判断的天赋
** 返回值：		bool bDown:true:习得;false:没有
** 修改记录：	
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
** 功能：		战局消息决策
** 输入参数：	无
** 返回值：		无
** 修改记录：	
*********************************************************************/
void Role::warMsgDecision()
{
	switch (m_eRoleWarMsg)
	{
	case RoleWarMsg_None:
		if (RoleMode_Main == m_stRoleInfo.mode)						/* 主将判断敌方是否在攻击范围内 */
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
** 功能：		Ai自动过图
** 输入参数：	无
** 返回值：		无
** 修改记录：	
*********************************************************************/
void Role::passRoomByAuto()
{
	m_ptMoveDir = Point(260, 0);							/* 可通过当前场景,往右走 */
	runActionMove();
}

/*********************************************************************
** 功能：		抖动
** 输入参数：	无
** 返回值：		无
** 修改记录：	
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
		auto move = MoveTo::create(pt.getLength()/speed, pt);			/* 震起 */
		prev = Sequence::createWithTwoActions(prev, move);

		auto pt1 = Point(ToolFunc::calcRandom(-sz.width, 0) + m_iSceneID * sz.width, 0);
		auto move1 = MoveTo::create(pt.getLength()/speed, pt1);			/* 落地 */
		prev = Sequence::createWithTwoActions(prev, move1);
	}
	auto seq = Sequence::create(prev, CallFuncN::create(CC_CALLBACK_1(Role::shakyCallBack, this)), NULL);
	sp->runAction(seq);
}

/*********************************************************************
** 功能：		脚底光环特效
** 输入参数：	无
** 返回值：		无
** 修改记录：	
*********************************************************************/
void Role::playAureoleEffect()
{
	m_nAureoleEffect->setPosition(this->getPosition());
	m_nAureoleEffect->setLocalZOrder(order_Bkg + 1);
	this->getParent()->addChild(m_nAureoleEffect);

	if (RoleCamp_Red == m_stRoleInfo.camp)
	{
		auto animation1 = Animation::create();						/* 外圈动画 */
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

		if (RoleMode_Main == m_stRoleInfo.mode)					/* 主将 */
		{
			auto animation2 = Animation::create();					/* 内圈动画 */
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

/* 被击特效 */
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

/* 死亡特效 */
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
** 功能：		执行碰撞检测
** 输入参数：	bool bDown:true:倒地;false:不倒地
** 返回值：		无
** 修改记录：	
*********************************************************************/
void Role::roleCollisionDetective(bool bDown)
{
	auto roles = UserData::getInstance()->getRoles();

	for(unsigned int index = 0;index < roles.size();index ++)		/* 敌人角色遍历获取 */
	{
		auto role = (Role *)roles[index];
		auto info = role->getRoleInfo();

		if ((RoleStatus_Invincible == info.status) || (RoleStatus_Death == info.status) || 
			(m_stRoleInfo.camp == info.camp) || (m_iSceneID != role->getSceneID()))
		{
			continue;												/* 无敌、同阵营、死亡或是自身不处理 */
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
** 功能：		执行动作
** 输入参数：	role_action action:动作名称ID
** 返回值： 	bool:true:执行成功
** 修改记录：	
*********************************************************************/
bool Role::runArmatureAction(RoleActSign action)
{
	bool bRet = true;

	if ((RoleAct_Death != m_stRoleInfo.actSign) && (NULL != m_stRoleInfo.arAnimate))
	{
		if (true == checkAnimateExistByName(strRoleSkillName[action]))/* 动作名存在？*/
		{
			stopArmatureAction();
			if (RoleCreMode_Preview != m_eRoleCreMode)
			{
				if (0 < m_fActCD[action])								/* CD中 */
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
			m_bRoleActBreak = false;								/* 中断动作后，重置中断标记 */

			if ((RoleActMode_Physical == m_stActMode[action]) && (RoleMode_Soldier != m_stRoleInfo.mode))
			{
				m_iRoleCombo = (m_iRoleCombo + 1)%3;				/* 标记下一普攻连击 */
				roleUnSchedule(RoleSchedule_Combo);					/* 普攻连击计时器取消 */
			}

			if ((RoleAct_SkillOne <= m_stRoleInfo.actSign) && (RoleAct_SkillFour >= m_stRoleInfo.actSign))
			{
				m_iRoleCombo = 0;									/* 执行技能，普攻重置为第一击 */
			}

			if ((RoleAct_SkillOne < action) && (RoleAct_SkillFour > action))
			{
				if (true == isRoleLearnedTalent(RoleTalent_NengLiangHua))	/* 能量化 */
				{
					if (0 == m_stRoleBuff.shield)					/* 效果第一次触发 */
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
** 功能：		停止动作
** 输入参数：	无
** 返回值： 	无
** 修改记录：	
*********************************************************************/
void Role::stopArmatureAction()
{
	if ((RoleAct_Death != m_stRoleInfo.actSign) && (NULL != m_stRoleInfo.arAnimate))
	{
		m_stRoleInfo.arAnimate->getAnimation()->stop();
	}
}

/*********************************************************************
** 功能：		根据名称检测动作存在否
** 输入参数：	std::string name：动作名称
** 返回值： 	bool：true：存在；false：不存在
** 修改记录：	
*********************************************************************/
bool Role::checkAnimateExistByName(const std::string name)
{
	if (NULL != m_stRoleInfo.arAnimate)
	{
		auto movement = m_stRoleInfo.arAnimate->getAnimation()->getAnimationData()->getMovement(name);
		if (NULL != movement)										/* 动作名存在 */
		{
			return true;
		}
	}

	return false;
}

/*********************************************************************
** 功能：		动作时消息响应
** 输入参数：	const std::string& str：动作名称
**				MovementEventType type: 动作阶段
**				float duration: 辅助动作时间
** 返回值：		无
** 修改记录：	
*********************************************************************/
void Role::movement(const std::string& str, MovementEventType type, float duration)
{
	switch (type)
	{
	case cocostudio::START:
		m_stRoleSubInfo.atkSide = m_stRoleSubInfo.side;		/* 播放动画前，攻击方向重置，默认前方 */
		if (RoleAct_Down == m_stRoleInfo.actSign)			/* 倒地无敌 */
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
** 功能：		动作时消息响应
** 输入参数：	const std::string& str：动作名称
** 返回值：		无
** 修改记录：	
*********************************************************************/
void Role::movement(const std::string& str)
{
	if (RoleCreMode_Preview == m_eRoleCreMode)						/* 武将详情预览模式不执行 */
	{
		runArmatureAction(RoleAct_Idle);
		return;
	}

	if (RoleActMode_Physical == m_stActMode[m_stRoleInfo.actSign])/* 普通攻击 */
	{
		roleSchedule(ComboDuration, RoleSchedule_Combo);
	}

// 	if (RoleActMode_Normal != m_stActMode[m_stRoleInfo.actSign])
// 	{
// 		addTrail(m_stRoleInfo.actSign);
// 	}

	if (RoleAct_Down == m_stRoleInfo.actSign)						/* 倒地状态 */
	{
		m_stRoleInfo.status = RoleStatus_Invincible;
		//this->scheduleOnce(schedule_selector(Role::downResume), DownDelay);
	}
	else if (RoleAct_Smitten == m_stRoleInfo.actSign)
	{
		this->scheduleOnce(schedule_selector(Role::smittenResume), 0.3f/*m_stRoleSubInfo.smittenDelay*/);
	}
	else if (RoleAct_Death == m_stRoleInfo.actSign)					/* 死亡状态 */
	{
		flashEffect();
	}
	else		/* 倒地、硬直不会立即进入action_idle */
	{
		runActionIdle();
	}
}

/*********************************************************************
** 功能：		动作时帧事件
** 输入参数：	const std::string& evt：事件名
** 返回值：		无
** 修改记录：	
*********************************************************************/
void Role::frameEvent(const std::string& evt)
{
	if (RoleCreMode_Preview == m_eRoleCreMode)						/* 武将详情预览模式不执行 */
	{
		return;
	}

	if (evt == getFrameEventName(FrameEvent_Attack))				/* 攻击（不倒地） */
	{
		roleCollisionDetective(false);
	}
	else if (evt == getFrameEventName(FrameEvent_Attack_FD))		/* 攻击（倒地） */
	{
		roleCollisionDetective(true);
	}
	else if ((evt == getFrameEventName(FrameEvent_Begin)) && 
		(RoleStatus_Invincible != m_stRoleInfo.status))				/* 开始霸体 */
	{
		m_stRoleInfo.status = RoleStatus_Superarmor;
	}
	else if ((evt == getFrameEventName(FrameEvent_End)) &&
		(RoleStatus_Invincible != m_stRoleInfo.status))				/* 结束霸体 */
	{
		m_stRoleInfo.status = RoleStatus_Normal;
	}
	else if (evt == getFrameEventName(FrameEvent_Left))				/* 往前攻击 */
	{
		m_stRoleSubInfo.atkSide = m_stRoleSubInfo.side;
	}
	else if (evt == getFrameEventName(FrameEvent_Right))			/* 往后攻击 */
	{
		m_stRoleSubInfo.atkSide = (RoleDirSign)(RoleDir_Right * m_stRoleSubInfo.side);
	}
	else															/* 前后双方攻击 */
	{
		if (evt == getFrameEventName(FrameEvent_Middle))
		{
			m_stRoleSubInfo.atkSide = RoleDir_Middle;
		}
	}
}

/*********************************************************************
** 功能：		开启计时器
** 输入参数：	无
** 返回值：		无
** 修改记录：	
*********************************************************************/
void Role::onEnter()
{
	Node::onEnter();

	this->schedule(schedule_selector(Role::hpReture), HealthRetRate);
	this->scheduleUpdate();
}

/*********************************************************************
** 功能：		关闭计时器
** 输入参数：	无
** 返回值：		无
** 修改记录：	
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
** 功能：		hp回复
** 输入参数：	float dt:
** 返回值：		无
** 修改记录：	
*********************************************************************/
void Role::hpReture(float dt)
{
	m_stRoleInfo.panel.hpCurrent = m_stRoleInfo.panel.hpCurrent + m_stRoleBuff.hpBack + m_stRoleBuff.hpBack;
	m_stRoleBuff.hpBack = 0;									/* 临时hp恢复结束 */

	if (m_stRoleInfo.panel.hpTotal + m_stRoleBuff.hpLimit <= m_stRoleInfo.panel.hpCurrent)
	{
		m_stRoleInfo.panel.hpCurrent = m_stRoleInfo.panel.hpTotal + m_stRoleBuff.hpLimit;
	}
}

/*********************************************************************
** 功能：		CD计时
** 输入参数：	float dt:
** 返回值：		无
** 修改记录：	
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
** 功能：		角色计时器
** 输入参数：	float dt:计时器触发时间
**				RoleScheduleType type: 计时器类型
** 返回值：		无
** 修改记录：	
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
** 功能：		关闭角色计时器
** 输入参数：	RoleScheduleType type: 计时器类型
** 返回值：		无
** 修改记录：	
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
** 功能：		连击标记复位
** 输入参数：	float dt
** 返回值： 	无
** 修改记录：	
*********************************************************************/
void Role::comboResume(float dt)
{
	m_iRoleCombo = 0;
}

/*********************************************************************
** 功能：		异常状态恢复
** 输入参数：	float dt
** 返回值：		无
** 修改记录：	
*********************************************************************/
void Role::conditionResume(float dt)
{
	m_stRoleInfo.condition = RoleCondition_Normal;
	runActionIdle();
}

/*********************************************************************
** 功能：		AI行为重置
** 输入参数：	float dt
** 返回值：		无
** 修改记录：	
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
** 功能：		异常伤害重置
** 输入参数：	float dt
** 返回值：		无
** 修改记录：	
*********************************************************************/
void Role::abnormalResume(float)
{
}

/*********************************************************************
** 功能：		护盾消失
** 输入参数：	float dt
** 返回值：		无
** 修改记录：	
*********************************************************************/
void Role::buffShieldResume(float dt)
{
	m_stRoleBuff.shield = 0.0f;
}

/*********************************************************************
** 功能：		hp恢复天赋
** 输入参数：	float dt
** 返回值：		无
** 修改记录：	
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
		if (this != role)											/* 自己不回复 */
		{
			auto info = role->getRoleInfo();
			auto buff = role->getRoleBuff();
			role->setRoleHpUp((info.panel.hpTotal + buff.hpLimit) * 0.075f);
		}
	}
}

/*********************************************************************
** 功能：		迫在眉睫天赋
** 输入参数：	float dt
** 返回值： 	无
** 修改记录：	
*********************************************************************/
void Role::buffHarmGrow(float dt)
{
	m_stRoleInfo.panel.allHarm += 2.0f;
}

/*********************************************************************
** 功能：		减防负buff复位
** 输入参数：	float dt
** 返回值： 	无
** 修改记录：	
*********************************************************************/
void Role::buffDenfendLResume(float dt)
{
	m_stRoleBuff.pDefend = 0;
	m_stRoleBuff.mDefend = 0;
}

/*********************************************************************
** 功能：		确保角色不移动到背景区域外
** 输入参数：	无
** 返回值： 	无
** 修改记录：	
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
** 功能：		移动角色(主将执行)
** 输入参数：	float dt: 每帧时间
** 返回值： 	无
** 修改记录：	
*********************************************************************/
void Role::makeRoleMoving(float dt)
{
	if (RoleCreMode_Preview != m_eRoleCreMode)
	{
		if (RoleAct_Move == m_stRoleInfo.actSign)
		{
			setRoleTurnedDirInfo(m_ptMoveDir.x + getPositionX());/* 转身 */
			setPosition(getPosition() + m_ptMoveDir * dt);
		}
	}
}

/*********************************************************************
** 功能：		取消硬直
** 输入参数：	float dt
** 返回值： 	无
** 修改记录：	
*********************************************************************/
void Role::downResume(float dt)
{
	flashEffect();													/* 隐身特效 */
	runActionIdle();
}

/*********************************************************************
** 功能：		角色闪烁特效
** 输入参数：	无
** 返回值： 	无
** 修改记录：	
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
** 功能：		倒地起身后，状态恢复正常
** 输入参数：	无
** 返回值： 	无
** 修改记录：	
*********************************************************************/
void Role::flashEffectCallBack()
{
	m_stRoleInfo.arAnimate->setOpacity(255);
	m_stRoleInfo.status = RoleStatus_Normal;
}

/*********************************************************************
** 功能：		死亡后回调
** 输入参数：	无
** 返回值： 	无
** 修改记录：	
*********************************************************************/
void Role::deathEffectCallBack()
{
	if (RoleCamp_Red == m_stRoleInfo.camp)							/* 刷新角色人数 */
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
** 功能：		受击恢复
** 输入参数：	float dt
** 返回值： 	无
** 修改记录：	
*********************************************************************/
void Role::smittenResume(float dt)
{
	if (RoleAct_Smitten == m_stRoleInfo.actSign)					/* 确保正执行的动作是受击 */
	{
		runActionIdle();
	}
}

/*********************************************************************
** 功能：		抖动结束
** 输入参数：	Node* who
** 返回值： 	无
** 修改记录：	
*********************************************************************/
void Role::shakyCallBack(Node* who)
{
	who->setPosition(Point(0, 0));
}

/* 动作执行 Begin*/
/*********************************************************************
** 功能：		执行攻击动作
** 输入参数：	无
** 返回值： 	bool:true:动作执行成功
** 修改记录：	
*********************************************************************/
bool Role::runActionAtkCtrl()
{
	if ((RoleAct_Idle == m_stRoleInfo.actSign) || (RoleAct_Move == m_stRoleInfo.actSign) ||
		((true == m_bRoleActBreak) && (RoleAct_Thrice_Atk != m_stRoleInfo.actSign)))
	{
		if (1 == m_iRoleCombo)
		{
			m_stRoleInfo.actSign = RoleAct_Twice_Atk;				/* ai控制的普攻ID可能和当前的连击标记不一致 */
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
** 功能：		执行空闲动作
** 输入参数：	无
** 返回值： 	bool:true:动作执行成功
** 修改记录：	
*********************************************************************/
bool Role::runActionIdle()
{
	return runArmatureAction(RoleAct_Idle);
}

/*********************************************************************
** 功能：		执行移动动作
** 输入参数：	无
** 返回值： 	bool:true:动作执行成功
** 修改记录：	
*********************************************************************/
bool Role::runActionMove()
{
	if (RoleAct_Move > m_stRoleInfo.actSign)						/* 判断动作可行 */
	{
		return runArmatureAction(RoleAct_Move);
	}
		
	return true;
}

/*********************************************************************
** 功能：		普通攻击第一击
** 输入参数：	无
** 返回值：		bool:true:动作执行成功
** 修改记录：	
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
** 功能：		普通攻击第二击
** 输入参数：	无
** 返回值：		bool:true:动作执行成功
** 修改记录：	
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
** 功能：		普通攻击第三击
** 输入参数：	无
** 返回值：		bool:true:动作执行成功
** 修改记录：	
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
** 功能：		执行被击动作
** 输入参数：	无
** 返回值： 	bool:true:动作执行成功
** 修改记录：	
*********************************************************************/
bool Role::runActionSmitten()
{
	if (RoleAct_Down == m_stRoleInfo.actSign)						/* 当前倒地动作 */
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
** 功能：		执行倒地动作
** 输入参数：	无
** 返回值： 	bool:true:动作执行成功
** 修改记录：	
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
** 功能：		执行死亡动作
** 输入参数：	无
** 返回值： 	bool:true:动作执行成功
** 修改记录：	
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
** 功能：		技能一
** 输入参数：	无
** 返回值： 	bool:true:动作执行成功
** 修改记录：	
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
** 功能：		技能二
** 输入参数：	无
** 返回值： 	bool:true:动作执行成功
** 修改记录：	
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
** 功能：		技能三
** 输入参数：	无
** 返回值： 	bool:true:动作执行成功
** 修改记录：	
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
** 功能：		技能四
** 输入参数：	无
** 返回值： 	bool:true:动作执行成功
** 修改记录：	
*********************************************************************/
bool Role::runActionSkillFour()
{
	if ((RoleAct_Move >= m_stRoleInfo.actSign) || (true == m_bRoleActBreak))
	{
		return  runArmatureAction(RoleAct_SkillFour);
	}

	return false;
}
/* 动作执行 End*/

/*********************************************************************
** 功能：		设置角色转身方向信息
** 输入参数：	RoleDirection dir: 转身方向
** 返回值：		无
** 修改记录：	
*********************************************************************/
void Role::setRoleTurnedDirInfo(RoleDirSign dir)
{
	if (dir != m_stRoleInfo.arAnimate->getScaleX())
	{
		m_stRoleInfo.arAnimate->setScaleX(dir * m_fResScale);
		m_stRoleInfo.arAnimate->setScaleY(m_fResScale);
		m_stRoleSubInfo.side = dir;

		/* 动画完成，攻击方向重置，默认前方 */
		m_stRoleSubInfo.atkSide = m_stRoleSubInfo.side;

		if (NULL != _roleHealth)
		{
			_roleHealth->setScaleX(dir * 0.3f);
		}
	}
}

/*********************************************************************
** 功能：		设置角色转身方向信息
** 输入参数：	float xOffset: 参考横坐标
** 返回值：		无
** 修改记录：	
*********************************************************************/
void Role::setRoleTurnedDirInfo(float xOffset)
{
	auto dir = RoleDir_Left;
	if (xOffset > getPositionX())									/* 设置角色转身 */
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
** 功能：		角色被击
** 输入参数：	Role* role: 攻击者
**				SkillInfo skillInfo: 技能信息
**				bool bDown:true:倒地;false: 不倒地
** 返回值：		
** 修改记录：	
*********************************************************************/
int Role::roleHurt(Role* role, SkillInfo skillInfo, bool bDown)
{
	if (RoleStatus_Death == m_stRoleInfo.status)				/* 死亡状态不考虑 */
	{
		return 0;
	}

	auto dmg = skillInfo.damage;
	auto extra = getExtraHarm(role);

	if (dmg > m_stRoleBuff.shield)								/* 护盾防御 */
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
		m_stRoleInfo.panel.mDefend + m_stRoleBuff.mDefend :			/* 技能攻击 */
		m_stRoleInfo.panel.pDefend + m_stRoleBuff.pDefend;			/* 普攻 */
	dmg = (dmg < defend) ? dmg * ToolFunc::calcRandom(50, 100) / 1000 : dmg - defend;
	dmg *= extra;

	/* 伤害浮动 */
	dmg = dmg * ToolFunc::calcRandom(maxActAiLimit - DamageOffset, maxActAiLimit + DamageOffset) * 1.0f / maxActAiLimit;
	dmg = dmg + role->getRoleInfo().panel.realAtk - m_stRoleInfo.panel.realAtkDefend;
	
	if (dmg >= m_stRoleInfo.panel.hpCurrent)
	{
		dmg = m_stRoleInfo.panel.hpCurrent;		
	}

	if (role->getPositionX() > this->getPositionX())		/* 攻击者在右边 */
	{
		m_stRoleSubInfo.hitSide = RoleDir_Right;			/* 右侧被击 */
	}
	else													/* 攻击者在左边 */
	{
		m_stRoleSubInfo.hitSide = RoleDir_Left;				/* 左侧被击 */
	}
	
	dmg = (int)(dmg + 0.5f);								/* 四舍五入 */
	setRoleHitAction(dmg, bDown);
	talentEffect(role, dmg);

	if (((RoleCreMode_XueGong2 == m_eRoleCreMode) || (RoleCreMode_XueGong3 == m_eRoleCreMode) || (RoleCreMode_XueGong4 == m_eRoleCreMode))
		&& (RoleCamp_Black == m_stRoleInfo.camp))
	{		
		dmg = 0;											/* 稷下学宫模式2/3，敌方角色不受伤害,4双方不掉血 */
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

	//stopActionByTag(skillMoveTag);									/* 停止施放技能时的移动 */
	comboResume(0.0f);												/* 普攻标记重置 */
	
	return m_stRoleInfo.panel.hpCurrent;
}

/*********************************************************************
** 功能：		计算伤害加成
** 输入参数：	Role* role: 攻击者
** 返回值：		int: 伤害值
** 修改记录：	
*********************************************************************/
float Role::getExtraHarm(Role* role)
{
	auto dmgExtra = 0.0f;
	auto panel = role->getRoleInfo().panel;
	auto buff = role->getRoleBuff();

	auto cri = panel.critical + buff.critical - m_stRoleInfo.panel.criDefend;/* 暴击 */
	if (cri > ToolFunc::calcRandom(0, maxActAiLimit) * 1.0f / 10)
	{
		m_ehealthSign = RoleHealth_Critical;							/* 暴击了 */
		dmgExtra = dmgExtra + 0.5f * (1 + panel.criExtra + buff.criExtra);
	}

	dmgExtra += panel.allHarm + buff.allHarm - panel.lowerHarm - buff.lowerHarm;

	if (RoleRace_Power == m_stRoleInfo.race)						/* 对力量型伤害加成 */
	{
		dmgExtra += panel.powerHarm + buff.powerHarm;
	}

	if (RoleRace_Wizard == m_stRoleInfo.race)						/* 对智力型伤害加成 */
	{
		dmgExtra += panel.wizardHarm + buff.wizardHarm;
	}

	if (RoleRace_Speed == m_stRoleInfo.race)						/* 对敏捷型伤害加成 */
	{
		dmgExtra += panel.speedHarm + buff.speedHarm;
	}

	if (true == role->isRoleLearnedTalent(RoleTalent_ZhiSi))		/* 荆轲：致死 */
	{
		if (m_stRoleInfo.panel.hpCurrent * 1.0f / (m_stRoleInfo.panel.hpTotal + m_stRoleBuff.hpLimit) < 0.25f)
		{
			dmgExtra += 0.15f;
		}
	}

	if (true == role->isRoleLearnedTalent(RoleTalent_YaZhi))		/* 孙膑：压制 */
	{
		if (m_stRoleInfo.panel.hpCurrent < panel.hpCurrent)
		{
			dmgExtra += 0.15f;
		}
	}

	return 1 + dmgExtra;
}

/*********************************************************************
** 功能：		天赋效应
** 输入参数：	Role* role: 攻击者
**				float damage: 受到的伤害
** 返回值：		无
** 修改记录：	
*********************************************************************/
void Role::talentEffect(Role* role, float damage)
{
	auto info = role->getRoleInfo();
	auto buff = role->getRoleBuff();

	if (true == role->isRoleLearnedTalent(RoleTalent_XiXueXiXing))	/* 吸血习性 */
	{
		auto atk = info.actSign;
		if ((RoleAct_Attack <= atk) && (RoleAct_Thrice_Atk >= atk))
		{
			role->setRoleHpUp(damage * 0.06f);
		}
	}

	if (0 == m_stRoleInfo.panel.hpCurrent)							/* 对手死亡 */
	{
		if (true == role->isRoleLearnedTalent(RoleTalent_ZhanSha))	/* 已学习斩杀天赋 */
		{
			role->setRoleHpUp((info.panel.hpTotal + buff.hpLimit) * 0.08f);
		}

		if ((RoleAct_SkillOne <= info.actSign) && (RoleAct_SkillFour >= info.actSign) &&
			(true == role->isRoleLearnedTalent(RoleTalent_GangJingJiSha)))/* 已学习干净击杀天赋 */
		{
			role->setActionCD(info.actSign, 0);
		}
	}

	if (true == role->isRoleLearnedTalent(RoleTalent_PoJia))		/* 吴孟瑶：破甲 */
	{
		auto atk = info.actSign;
		if ((RoleAct_Attack <= atk) && (RoleAct_Thrice_Atk >= atk))
		{
			if (0 == m_stRoleBuff.pDefend)							/* 还没减防 */
			{
				this->scheduleOnce(schedule_selector(Role::buffDenfendLResume), 2.0f);
			}
			m_stRoleBuff.pDefend = -(m_stRoleInfo.panel.pDefend + m_stRoleBuff.pDefend) * info.panel.pDefendL;
			m_stRoleBuff.mDefend = -(m_stRoleInfo.panel.mDefend + m_stRoleBuff.mDefend) * info.panel.mDefendL;
		}
	}

	if (true == role->isRoleLearnedTalent(RoleTalent_XueMoFa))		/* 商鞅：血魔法 */
	{
		role->setRoleHpUp(damage * 0.08f);
	}
	
	if (true == role->isRoleLearnedTalent(RoleTalent_MoNvMiXing))	/* 钟无艳：魔女迷行 */
	{
		auto atk = info.actSign;
		if ((RoleAct_Attack <= atk) && (RoleAct_Thrice_Atk >= atk))
		{
			role->setRoleHpUp(damage * 0.08f);
		}
	}
}

/*********************************************************************
** 功能：		角色被击时动作
** 输入参数：	int damage: 受到的伤害值
**				bool bDown:true:倒地;false:不倒地
** 返回值：		
** 修改记录：	
*********************************************************************/
void Role::setRoleHitAction(int damage, bool bDown)
{
	bool bFlag = false;

	RoleActSign act = ( true == bDown) ? RoleAct_Down : RoleAct_Smitten;
	if (RoleAct_Down == m_stRoleInfo.actSign)						/* 倒地动作中被击 */
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
		if (RoleStatus_Normal == m_stRoleInfo.status)				/* 普通状态 */
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
** 功能：		hp变化label
** 输入参数：	int damage: hp值
** 返回值：		无
** 修改记录：	
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
** 功能：		扣血显示label回调函数
** 输入参数：	Node *who
** 返回值：		无
** 修改记录：	
*********************************************************************/
void Role::hpLabelCallBack(Node *who)
{
	who->removeFromParent();
}

/*********************************************************************
** 功能：		角色AI
** 输入参数：	无
** 返回值：		无
** 修改记录：	
*********************************************************************/
void Role::runRoleAI()
{
	if (false == checkAIAviable())
	{
		return;
	}

	auto role = (Role *)getNearestRole();							/* 选择最近的对手 */
	if (NULL != role)												/* 未获取到对手，不处理 */
	{
		auto bDanger = false;
		auto danger = 0.0f;
		auto info = role->getRoleInfo();
		auto ptRoleLoc = role->getPosition();

		if ((m_iAiActSeqIndex == m_vctAiActSeq.size()) && (RoleAct_Idle == m_stRoleInfo.actSign))
		{
			setAiActionSequence();									/* Ai攻击序列执行到最后一个动作 */
			roleAiShortMove();
		}
		
		if ((RoleStatus_Invincible == info.status) && (RoleActAi_ShortMove != m_eRoleActAi))/* 对方无敌状态，并且尚未对其采取动作 */
		{
			runActionIdle();
			roleAiShortMove();										/* 对手倒地 */
		}

		if (RoleCondition_Normal != info.condition)					/* 敌方属性异常 */
		{
			auto random = ToolFunc::calcRandom(minActAiLimit, maxActAiLimit);
			if ((random > maxActAiLimit / 2) && (RoleActAi_Pursuit != m_eRoleActAi))
			{
				m_eRoleActAi = RoleActAi_Pursuit;					/* 50%几率采取攻击 */
			}
		}

		switch (m_eRoleActAi)
		{
		case RoleActAi_None:
			roleAiStep();
			break;
		case RoleActAi_Pursuit:										/* AI执行追击时 */
			roleAiPursuit(ptRoleLoc);
			break;
		case RoleActAi_Sleep:										/* AI休眠时，判断危险 */
			calcuRoleDangerSignValue(&bDanger, &danger);
			if (true == bDanger)
			{
				if (m_fActAiLimit[RoleActAi_Pursuit] > ToolFunc::calcRandom(minActAiLimit, maxActAiLimit))
				{
					roleUnSchedule(RoleSchedule_AiAction);			/* 中断休眠计时器 */
				}
			}		
			break;
		default:
			break;
		}
	}
}

/*********************************************************************
** 功能：		主将角色AI
** 输入参数：	无
** 返回值：		无
** 修改记录：	
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
		auto role = (Role *)getNearestRole();						/* 选择最近的对手 */
		if (NULL != role)
		{
			auto act = (RoleActSign)(m_iRoleCombo + RoleAct_Attack);
			auto ptOffset = this->getPosition() - role->getPosition();

			if ((m_stSkillInfo[act].xAtkDis >= abs(ptOffset.x)) && (m_stSkillInfo[act].yAtkDis >= abs(ptOffset.y)))
			{
				setRoleTurnedDirInfo(role->getPositionX());			/* 当前释放的技能能攻击到对手,设置角色转身 */
				runRoleAction(act);
			}
		}
	}

	if (RoleAct_Move == m_stRoleInfo.actSign)
	{
		auto ptDir = m_ptMoveDes - getPosition();
		if ((abs(ptDir.x) < 1.0f) || (abs(ptDir.y) < 1.0f))				/* 误差范围 */
		{
			runActionIdle();
		}
	}
#endif
}

/*********************************************************************
** 功能：		Ai行为选择
** 输入参数：	无
** 返回值：		无
** 修改记录：	
*********************************************************************/
void Role::roleAiStep()
{
	if (RoleAct_Idle != m_stRoleInfo.actSign)
	{
		return;
	}

	auto random = ToolFunc::calcRandom(minActAiLimit, maxActAiLimit);
	if (random < m_fActAiLimit[RoleActAi_Pursuit])					/* 追击 */
	{
		m_eRoleActAi = RoleActAi_Pursuit;
	}
	else if ((random < m_fActAiLimit[RoleActAi_ShortMove])) 		/* 漫游 */
	{
		roleAiShortMove();
	}
	else															/* 休眠 */
	{
		if (random < m_fActAiLimit[RoleActAi_Sleep])
		{
			roleAiSleep();
		}
	}
}

/*********************************************************************
** 功能：		Ai行为冲锋
** 输入参数：	Point ptObj: 目标位置
** 返回值：		无
** 修改记录：	
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
		setRoleTurnedDirInfo(ptObj.x);						/* 当前释放的技能能攻击到对手,设置角色转身 */
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
** 功能：		Ai行为短距离移动
** 输入参数：	无
** 返回值：		无
** 修改记录：	
*********************************************************************/
void Role::roleAiShortMove()
{
	if (RoleActAi_ShortMove != m_eRoleActAi)
	{
		auto center = SceneWidth * (m_iSceneID + 0.5f);				/* 地图移动区域中心x坐标 */
		auto delta = (getPositionX() - SceneWidth * m_iSceneID) / SceneWidth + 1;
		if (getPositionX() < center)
		{
			delta = (SceneWidth * (m_iSceneID + 1) - getPositionX()) / SceneWidth + 1;
		}
		/* a1为delta，公差为delta的等差数列 */
		auto sum = int(90 * 181 * delta * 100);						/* 前180项和，放大100倍（照顾delta小数部分） */
		auto item = 0;												/* 随机要取第几项 */
		auto oddsItem = 0;											/* 成功几率 */
		auto temp = 0;
		while (true)
		{
			item = ToolFunc::calcRandom(1, 180);
			temp = (getPositionX() < center) ? 180 - item : item;
			oddsItem = int(temp * delta * 100);
			if (oddsItem > ToolFunc::calcRandom(1, sum))			/* 取中 */
			{
				break;
			}
		}

		auto sign = (ToolFunc::calcRandom(1, 100) > 50) ? 1 : -1;	/* 上下方向随机 */
		auto radian = CC_DEGREES_TO_RADIANS(item) * sign;
		m_ptMoveDir.x = cos(radian);
		m_ptMoveDir.y = sin(radian);								/* 纵方向速度微调 */
		m_ptMoveDir = m_ptMoveDir * m_stRoleSubInfo.speed;

		auto duration = ToolFunc::calcRandom(MoveDuration * 30, MoveDuration * 50) * 0.02f;
		roleUnSchedule(RoleSchedule_AiAction);
		m_eRoleActAi = RoleActAi_ShortMove;
		roleSchedule(duration, RoleSchedule_AiAction);
		runActionMove();
	}
}

/*********************************************************************
** 功能：		Ai行为休眠
** 输入参数：	无
** 返回值：		无
** 修改记录：	
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

/* AI辅助函数 Begin */
/*********************************************************************
** 功能：		判断AI有效性
** 输入参数：	
** 返回值：		
** 修改记录：	
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
			if ((RoleAct_Move == m_stRoleInfo.actSign) || (RoleAct_Idle == m_stRoleInfo.actSign))/* 当前动作已播放完毕 */
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

	if (RoleCondition_Normal != m_stRoleInfo.condition) 			/* 异常状态 */
	{
		bRet = false;
	}

	return bRet;
}

/*********************************************************************
** 功能：		计算最近角色是否有危险
** 输入参数：	bool *bDanger: 该角色危险值
**				float *dangerDis: 该角色最近危险距离
** 返回值：		无
** 修改记录：	
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
			continue;												/* 同阵营、异常状态，跳过 */
		}

		if (true == Opponent->checkRoleCanBeHit(ptLoc))
		{
			*bDanger = true;
			dis = ptLoc.getDistance(getPosition());
			if (dis < *dangerDis)									/* 取最近的危险距离 */
			{
				*dangerDis = dis;
			}
		}
	}
}

/*********************************************************************
** 功能：		获取移动方向
** 输入参数：	Point ptDes: 目标坐标
** 返回值：		无
** 修改记录：	
*********************************************************************/
void Role::setMoveVector(Point ptDes)
{
	if (ptDes != m_ptMoveDes)
	{
		m_ptMoveDes = ptDes;
		auto ptOffset = ptDes - getPosition();
		auto radian = ptOffset.getAngle();
		m_ptMoveDir.x = cos(radian);
		m_ptMoveDir.y = sin(radian);									/* 纵方向速度微调 */
		m_ptMoveDir = m_ptMoveDir * m_stRoleSubInfo.speed;
	}
}

/*********************************************************************
** 功能：		判断指定角色是否在攻击范围
** 输入参数：	Point ptLoc: 要检测的角色坐标
** 返回值：		bool:true: 在自己的攻击范围
** 修改记录：	
*********************************************************************/
bool Role::checkRoleCanBeHit(Point ptLoc)
{
	bool bRet = false;

	if (RoleStatus_Invincible == m_stRoleInfo.status)				/* 没执行动作:pass */
	{
		return bRet;
	}

	int index = 0;
	auto ptOffset = ptLoc - getPosition();							/* 相对位置 */

	for (index = 0;(unsigned int)index < m_vctAiActSeq.size();index ++)
	{
		auto act = m_vctAiActSeq[index];
		if ((m_stSkillInfo[act].xAtkDis >= abs(ptOffset.x)) && (m_stSkillInfo[act].yAtkDis >= abs(ptOffset.y)))
		{
			bRet = true;											/* 满足攻击距离的攻击动作 */
			break;
		}
	}

	return bRet;
}

/*********************************************************************
** 功能：		获取敌方最近的角色
** 输入参数：	无
** 返回值：		Node：最近的角色在敌方阵营的角色
** 修改记录：	
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
			&& (RoleStatus_Death != info.status))					/* 同一阵营、不同区域、死亡、无敌：pass */
		{
			auto ptLoc = temp->getPosition() - getPosition();		/* 起跳前坐标 */
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
** 功能：		以两个定点构造矩形
** 输入参数：	Point p1：定点1
**				Point p2：定点2
** 返回值：		Rect
** 修改记录：	
*********************************************************************/
Rect Role::getRectByTwoPoint(Point p1, Point p2)
{
	auto ptOffset = p1 - p2;
	auto ptDes = ptInvalid;
	ptDes.x = ToolFunc::calcRandom(minActAiLimit, abs(ptOffset.x)) / 2;
	ptDes.y = ToolFunc::calcRandom(minActAiLimit, abs(ptOffset.y)) / 2;

	if ((p1.x > p2.x) && (p1.y > p2.y))							/* p1在p2右上角 */
	{
		return Rect(p1.x - ptDes.x, p1.y - ptDes.y, ptDes.x, ptDes.y);
	}
	if ((p1.x < p2.x) && (p1.y > p2.y))							/* p1在p2左上角 */
	{
		return Rect(p1.x, ptDes.y, ptDes.x, ptDes.y);
	}
	if ((p1.x < p2.x) && (p1.y < p2.y))							/* p1在p2左下角 */
	{
		return Rect(p1.x, p1.y, ptDes.x, ptDes.y);
	}
	if ((p1.x > p2.x) && (p1.y < p2.y))							/* p1在p2右下角 */
	{
		return Rect(p1.x - ptDes.x, p1.y, ptDes.x, ptDes.y);
	}

	return Rect(0, 0, 0, 0);
}

/*********************************************************************
** 功能：		以自身位置和范围构造矩形
** 输入参数：	Size sz：范围
** 返回值：		Rect
** 修改记录：	
*********************************************************************/
Rect Role::getRectBySize(Size sz)
{
	Rect rc(0, 0, 0, 0);

	rc.origin.x = getPositionX() - sz.width / 2;
	rc.origin.y = getPositionY() - sz.height / 2;
	rc.size = sz;

	return rc;
}
/* AI辅助函数 End */