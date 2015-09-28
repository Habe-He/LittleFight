#include "LianPo.h"
#include "Roles/SkillProps/FallenProp.h"

USING_NS_CC;
using namespace cocostudio;

const Point ptLP_S1FirstArrow = Point(65, 140);	/* ����s1����һ��*/
const int iLP_S1MaxNum = 12;					/* ����s1��������� */
const Size szLP_S1Region = Size(180, 40);		/* ����s1�������Χ */
const float fLP_S1Delay = 0.48f;				/* ����s1�������ʱ */

LianPo::LianPo(void)
{
}

LianPo::~LianPo(void)
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
void LianPo::loadArmature()
{
	m_stRoleInfo.arAnimate = Armature::create(m_strRoleName.c_str());
	if (NULL == m_stRoleInfo.arAnimate)
	{
		return;
	}
	
	this->addChild(m_stRoleInfo.arAnimate);

	/* ע�ᶯ��֡�¼��Ͷ����ص����� */
	m_stRoleInfo.arAnimate->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(LianPo::actionFrameEventCallFunc, this, std::placeholders::_1
		, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	m_stRoleInfo.arAnimate->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(LianPo::actionMovementCallFunc, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

/*********************************************************************
** ���ܣ�		��ʼ�����ܷ��е���
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void LianPo::initFlightPropInfo()
{
	m_stLianPoProp[LianPo_Normal].strPath = getFlightPropPath() + "LianPo_Normal";
	m_stLianPoProp[LianPo_Normal].ptOffset = Point(110, 80) * m_fResScale;
	m_stLianPoProp[LianPo_Normal].iImgNum = 1;

	m_stLianPoProp[LianPo_S2Prop].strPath = getFlightPropPath() + "LianPo_S2Prop";
	m_stLianPoProp[LianPo_S2Prop].ptOffset = Point(110, 80) * m_fResScale;
	m_stLianPoProp[LianPo_S2Prop].iImgNum = 1;

	m_stLianPoProp[LianPo_S4Prop].strPath = getFlightPropPath() + "LianPo_S4Prop";
	m_stLianPoProp[LianPo_S4Prop].ptOffset = Point(110, 80) * m_fResScale;
	m_stLianPoProp[LianPo_S4Prop].iImgNum = 1;
}

/*********************************************************************
** ���ܣ�		�����츳buff
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void LianPo::initTalentEffect()
{
	Role::initTalentEffect();

	if (true == isRoleLearnedTalent(RoleTalent_JianGuFangYu))	/* ���ģ���̷��� */
	{
		auto vec = UserData::getInstance()->getRoles();
		for (unsigned int index = 0;index < vec.size();index ++)
		{
			auto role = (Role *)vec[index];
			auto info = role->getRoleInfo();
			if ((RoleCamp_Red == info.camp) && (RoleRace_Power == info.race))
			{
				info.panel.pDefend += 0.05f;
				info.panel.mDefend += 0.05f;
				role->setRoleInfo(info);
			}
		}
	}
}

/*********************************************************************
** ���ܣ�		�����ص�����
** ���������	
** ����ֵ�� 	
** �޸ļ�¼��	
*********************************************************************/
void LianPo::actionMovementCallFunc(Armature *ar, MovementEventType type, const std::string& str)
{
	movement(str, type, 0.5f);
}

/*********************************************************************
** ���ܣ�		֡�¼�
** ���������	
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
void LianPo::actionFrameEventCallFunc(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
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
			LianPoShot(LianPo_Normal, bDown);
		}

		if (RoleAct_SkillOne == m_stRoleInfo.actSign)
		{
			LianPoS1();
		}

		if (RoleAct_SkillTwo == m_stRoleInfo.actSign)
		{
			LianPoShot(LianPo_S2Prop, bDown);
		}

		if (RoleAct_SkillFour == m_stRoleInfo.actSign)
		{
			LianPoShot(LianPo_S4Prop, bDown);
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
bool LianPo::runActionAttack()
{
	bool bRet = Role::runActionAttack();
	if (true == bRet)
	{
		playEffectOgg("C071");
	}

	return bRet;
}

/*********************************************************************
** ���ܣ�		��ͨ�����ڶ���
** ���������	��
** ����ֵ��		bool:true:����ִ�гɹ�
** �޸ļ�¼��	
*********************************************************************/
bool LianPo::runActionTwiceAtk()
{
	bool bRet = Role::runActionTwiceAtk();
	if (true == bRet)
	{
		playEffectOgg("C071");
	}

	return bRet;
}

/*********************************************************************
** ���ܣ�		��ͨ����������
** ���������	��
** ����ֵ��		bool:true:����ִ�гɹ�
** �޸ļ�¼��	
*********************************************************************/
bool LianPo::runActionThriceAtk()
{
	bool bRet = Role::runActionThriceAtk();
	if (true == bRet)
	{
		playEffectOgg("C071");
	}

	return bRet;
}

/*********************************************************************
** ���ܣ�		ִ�м���һ
** ���������	��
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
bool LianPo::runActionSkillOne()
{
	bool bRet = Role::runActionSkillOne();
	if (true == bRet)
	{
		playEffectOgg("157SJ");
	}

	return bRet;
}

/*********************************************************************
** ���ܣ�		ִ�м��ܶ�
** ���������	��
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
bool LianPo::runActionSkillTwo()
{
	bool bRet = Role::runActionSkillTwo();
	if (true == bRet)
	{
		playEffectOgg("C071");
	}

	return bRet;
}

/*********************************************************************
** ���ܣ�		ִ�м�����
** ���������	��
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
bool LianPo::runActionSkillThree()
{
	bool bRet = Role::runActionSkillThree();
	if (true == bRet)
	{
		playEffectOgg("158DL");
	}

	return bRet;
}

/*********************************************************************
** ���ܣ�		ִ�м�����
** ���������	��
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
bool LianPo::runActionSkillFour()
{
	bool bRet = Role::runActionSkillFour();
	if (true == bRet)
	{
		playEffectOgg("145SJ");
	}

	return bRet;
}
/* ����ִ�� End*/

/*********************************************************************
** ���ܣ�		������ͨ��
** ���������	LPArrow arrow: ������
**				bool bDown:true:����;false:������
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void LianPo::LianPoShot(LianPoArrow arrow, bool bDown)
{
	FlightPropInfo info = {0};
	info.num = m_stLianPoProp[arrow].iImgNum;
	memcpy(&(info.skillInfo), &m_stSkillInfo[m_stRoleInfo.actSign], sizeof(SkillInfo));

	auto lpArrow = CommonProp::create(this, m_stLianPoProp[arrow].strPath, info);

	if (NULL != lpArrow)
	{
		lpArrow->setScaleX(m_stRoleSubInfo.side * m_fResScale);
		lpArrow->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
		lpArrow->setPropPosition(Point(-m_stLianPoProp[arrow].ptOffset.x * m_stRoleSubInfo.side, m_stLianPoProp[arrow].ptOffset.y));
		lpArrow->setPropFlag(bDown);
		this->getParent()->addChild(lpArrow);
		lpArrow->runPropCollisionDetective(0.2f, Point(-m_stSkillInfo[m_stRoleInfo.actSign].xAtkDis * m_stRoleSubInfo.side, 0));
	}
}

/*********************************************************************
** ���ܣ�		���ļ���1������е�һ��
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void LianPo::LianPoS1()
{
	auto lpArrow = Sprite::create(m_stLianPoProp[LianPo_Normal].strPath + "0.png");
	if (NULL != lpArrow)
	{
		lpArrow->setScaleX(m_stRoleSubInfo.side * m_fResScale);
		lpArrow->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
		lpArrow->setRotation(60.0f * m_stRoleSubInfo.side);
		lpArrow->setPosition(Point(-ptLP_S1FirstArrow.x * m_stRoleSubInfo.side * m_fResScale, ptLP_S1FirstArrow.y * m_fResScale) + getPosition());
		this->getParent()->addChild(lpArrow);

		auto offset = (50 + szLP_S1Region.width) * m_fResScale;
		auto move = MoveBy::create(0.1f, Point(-offset * m_stRoleSubInfo.side, offset));
		auto prop = CallFuncN::create(CC_CALLBACK_1(LianPo::s1CallBack1, this));
		auto seq = Sequence::create(move, prop, NULL);
		lpArrow->runAction(seq);
	}
}

/*********************************************************************
** ���ܣ�		���ɼ���
** ���������	
** ����ֵ��		
** �޸ļ�¼��	
*********************************************************************/
void LianPo::s1CallBack1(Node *who)
{
	auto ptWho = who->getPosition() - getPosition();				/* ������佫λ�� */
	who->removeFromParentAndCleanup(true);

	m_mapS1.clear();
	auto ptLoc = Point::ZERO;
	/* ���ξ����ɫ50����180����40 */
	auto rc = Rect(-140 * m_stRoleSubInfo.side - 90, -szLP_S1Region.height / 2, szLP_S1Region.width, szLP_S1Region.height);
	for (auto index = 0;index < iLP_S1MaxNum;index ++)
	{
		ptLoc.x = ToolFunc::calcRandom(rc.getMinX(), rc.getMaxX());
		ptLoc.y = ToolFunc::calcRandom(rc.getMinY(), rc.getMaxY());

		FlightPropInfo info = {0};
		info.num = m_stLianPoProp[LianPo_Normal].iImgNum;
		memcpy(&(info.skillInfo), &m_stSkillInfo[RoleAct_SkillOne], sizeof(SkillInfo));

		auto lpArrow = FallenProp::create(this, m_stLianPoProp[LianPo_Normal].strPath, info);		
		if (NULL != lpArrow)
		{
			lpArrow->setPropYaxis(this->getPositionY());
			lpArrow->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
			lpArrow->setScaleX(-m_fResScale);
			lpArrow->setPropPosition(ptWho);		
			lpArrow->setRotation(-ToolFunc::getAngle(ptLoc, ptWho));
			lpArrow->setVisible(false);
			lpArrow->setPropFlag(true);									/* �����򵹵� */
			this->getParent()->addChild(lpArrow);

			m_mapS1.insert(pair<Sprite*, Point>(lpArrow, ptLoc - ptWho));	
			auto delay = DelayTime::create(ToolFunc::calcRandom(fLP_S1Delay * 100, fLP_S1Delay * 100 * iLP_S1MaxNum / 2) * 0.002f);
			auto drop = CallFuncN::create(CC_CALLBACK_1(LianPo::s1CallBack2, this));
			auto seq = Sequence::create(delay, drop, NULL);
			lpArrow->runAction(seq);		
		}
	}
}

void LianPo::s1CallBack2(Node *who)
{
	auto arrow = (CommonProp *)who;
	arrow->setVisible(true);
	arrow->runPropCollisionDetective(0.25f, m_mapS1.at(arrow));
}
/* protected: End */