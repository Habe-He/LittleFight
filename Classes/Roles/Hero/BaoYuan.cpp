#include "BaoYuan.h"

USING_NS_CC;
using namespace cocostudio;

BaoYuan::BaoYuan(void)
{
}

BaoYuan::~BaoYuan(void)
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
void BaoYuan::loadArmature()
{
	m_stRoleInfo.arAnimate = Armature::create(m_strRoleName.c_str());
	if (NULL == m_stRoleInfo.arAnimate)
	{
		return;
	}

	this->addChild(m_stRoleInfo.arAnimate);

	/* 注册动画帧事件和动作回调函数 */
	m_stRoleInfo.arAnimate->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(BaoYuan::actionFrameEventCallFunc, this, std::placeholders::_1
		, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	m_stRoleInfo.arAnimate->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(BaoYuan::actionMovementCallFunc, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

/*********************************************************************
** 功能：		Boss Ai攻击序列
** 输入参数：	无
** 返回值：		无
** 修改记录：	
*********************************************************************/
void BaoYuan::aiActSequenceBoss()
{
	if ((RoleCreMode_XueGong2 == m_eRoleCreMode) && (RoleCamp_Black == m_stRoleInfo.camp))
	{
		/* 稷下学宫模式2，敌方角色 */
		m_vctAiActSeq.clear();

		int sNum = 0;												/* 开启的技能数 */
		int skill[4] = {0};											/* 开启的技能 */
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
** 功能：		动作回调函数
** 输入参数：	
** 返回值： 	
** 修改记录：	
*********************************************************************/
void BaoYuan::actionMovementCallFunc(Armature *ar, MovementEventType type, const std::string& str)
{
	movement(str, type, 0.5f);
}

/*********************************************************************
** 功能：		帧事件
** 输入参数：	
** 返回值： 	无
** 修改记录：	
*********************************************************************/
void BaoYuan::actionFrameEventCallFunc(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
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
}

/* 动作执行 Begin*/
/*********************************************************************
** 功能：		普通攻击第一击
** 输入参数：	无
** 返回值：		bool:true:动作执行成功
** 修改记录：	
*********************************************************************/
bool BaoYuan::runActionAttack()
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
bool BaoYuan::runActionTwiceAtk()
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
bool BaoYuan::runActionThriceAtk()
{
	bool bRet = Role::runActionThriceAtk();
	if (true == bRet)
	{
		playEffectOgg("C272");
	}

	return bRet;
}

/*********************************************************************
** 功能：		执行技能一
** 输入参数：	无
** 返回值： 	无
** 修改记录：	
*********************************************************************/
bool BaoYuan::runActionSkillOne()
{
	bool bRet = Role::runActionSkillOne();
	if (true == bRet)
	{
		playEffectOgg("016Q");
	}

	return bRet;
}

/*********************************************************************
** 功能：		执行技能二
** 输入参数：	无
** 返回值： 	无
** 修改记录：	
*********************************************************************/
bool BaoYuan::runActionSkillTwo()
{
	bool bRet = Role::runActionSkillTwo();
	if (true == bRet)
	{
		playEffectOgg("162ZH");
	}

	return bRet;
}
/* 动作执行 End*/
/* protected: End */