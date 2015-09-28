#include "ZhaoKuo.h"
#include "Roles/SkillProps/FallenProp.h"

USING_NS_CC;
using namespace cocostudio;

const Point ptZK_S1FirstArrow = Point(45, 110);		/* ����s1����һ��*/
const int iZK_S1MaxNum = 12;						/* ����s1��������� */
const Size szZK_S1Region = Size(150, 30);			/* ����s1�������Χ */
const float fZK_S1Delay = 0.57f;					/* ����s1�������ʱ */

ZhaoKuo::ZhaoKuo(void)
{
}

ZhaoKuo::~ZhaoKuo(void)
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
void ZhaoKuo::loadArmature()
{
	m_stRoleInfo.arAnimate = Armature::create(m_strRoleName.c_str());
	if (NULL == m_stRoleInfo.arAnimate)
	{
		return;
	}

	this->addChild(m_stRoleInfo.arAnimate);

	/* ע�ᶯ��֡�¼��Ͷ����ص����� */
	m_stRoleInfo.arAnimate->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(ZhaoKuo::actionFrameEventCallFunc, this, std::placeholders::_1
		, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	m_stRoleInfo.arAnimate->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(ZhaoKuo::actionMovementCallFunc, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

/*********************************************************************
** ���ܣ�		��ʼ�����ܷ��е���
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void ZhaoKuo::initFlightPropInfo()
{
	m_stZhaoKuoProp[ZhaoKuo_Normal].strPath = getFlightPropPath() + "ZhaoKuo_Normal";
	m_stZhaoKuoProp[ZhaoKuo_Normal].ptOffset = Point(90, 80) * m_fResScale;
	m_stZhaoKuoProp[ZhaoKuo_Normal].iImgNum = 1;

	m_stZhaoKuoProp[ZhaoKuo_S1Prop].strPath = getFlightPropPath() + "ZhaoKuo_S1Prop";
	m_stZhaoKuoProp[ZhaoKuo_S1Prop].ptOffset = Point(40, 100) * m_fResScale;
	m_stZhaoKuoProp[ZhaoKuo_S1Prop].iImgNum = 1;

	m_stZhaoKuoProp[ZhaoKuo_S2Prop].strPath = getFlightPropPath() + "ZhaoKuo_S2Prop";
	m_stZhaoKuoProp[ZhaoKuo_S2Prop].ptOffset = Point(90, 80) * m_fResScale;
	m_stZhaoKuoProp[ZhaoKuo_S2Prop].iImgNum = 1;
}

/*********************************************************************
** ���ܣ�		Boss Ai��������
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void ZhaoKuo::aiActSequenceBoss()
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
void ZhaoKuo::actionMovementCallFunc(Armature *ar, MovementEventType type, const std::string& str)
{
	movement(str, type, 0.5f);
}

/*********************************************************************
** ���ܣ�		֡�¼�
** ���������	
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
void ZhaoKuo::actionFrameEventCallFunc(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
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
			ZhaoKuoArrow(ZhaoKuo_Normal, bDown, m_stZhaoKuoProp[ZhaoKuo_Normal].ptOffset);
		}

		if (RoleAct_SkillOne == m_stRoleInfo.actSign)
		{
			ZhaoKuoS1();
		}

		if (RoleAct_SkillTwo == m_stRoleInfo.actSign)
		{
			ZhaoKuoArrow(ZhaoKuo_S2Prop, bDown, m_stZhaoKuoProp[ZhaoKuo_S2Prop].ptOffset);
		}
	}

	if (RoleAct_SkillThree == m_stRoleInfo.actSign)
	{
		if (getFrameEventName(FrameEvent_Begin) == evt)
		{
			if (RoleCreMode_Fighting == m_eRoleCreMode)
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
bool ZhaoKuo::runActionAttack()
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
bool ZhaoKuo::runActionTwiceAtk()
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
bool ZhaoKuo::runActionThriceAtk()
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
bool ZhaoKuo::runActionSkillOne()
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
bool ZhaoKuo::runActionSkillTwo()
{
	bool bRet = Role::runActionSkillTwo();
	if (true == bRet)
	{
		playEffectOgg("145ZH");
	}

	return bRet;
}

/*********************************************************************
** ���ܣ�		ִ�м�����
** ���������	��
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
bool ZhaoKuo::runActionSkillThree()
{
	bool bRet = Role::runActionSkillThree();
	if (true == bRet)
	{
		playEffectOgg("158DL");
	}

	return bRet;
}
/* ����ִ�� End*/

/*********************************************************************
** ���ܣ�		������ͨ��
** ���������	ZhaoKuoFlight arrow: ������
**				bool bDown:true:����;false:������
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void ZhaoKuo::ZhaoKuoArrow(ZhaoKuoFlight arrow, bool bDown, Point arrowPoint)
{
	FlightPropInfo info = {0};
	info.num = m_stZhaoKuoProp[arrow].iImgNum;
	memcpy(&(info.skillInfo), &m_stSkillInfo[m_stRoleInfo.actSign], sizeof(SkillInfo));

	auto ZKArrow = CommonProp::create(this, m_stZhaoKuoProp[arrow].strPath, info);
	if (NULL != ZKArrow)
	{
		ZKArrow->setScaleX(m_stRoleSubInfo.side * m_fResScale);
		ZKArrow->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
		ZKArrow->setPropPosition(Point(-arrowPoint.x * m_stRoleSubInfo.side, arrowPoint.y));
		ZKArrow->setPropFlag(bDown);
		this->getParent()->addChild(ZKArrow);
		ZKArrow->runPropCollisionDetective(0.2f, Point(-m_stSkillInfo[m_stRoleInfo.actSign].xAtkDis * m_stRoleSubInfo.side, 0));
	}
}

/*********************************************************************
** ���ܣ�		���ļ���1������е�һ��
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void ZhaoKuo::ZhaoKuoS1()
{
	auto ZKArrow = Sprite::create(m_stZhaoKuoProp[ZhaoKuo_Normal].strPath + "0.png");
	if (NULL != ZKArrow)
	{
		ZKArrow->setScaleX(m_stRoleSubInfo.side * m_fResScale);
		ZKArrow->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
		ZKArrow->setRotation(60.0f * m_stRoleSubInfo.side);
		ZKArrow->setPosition(Point(-ptZK_S1FirstArrow.x * m_fResScale * m_stRoleSubInfo.side, ptZK_S1FirstArrow.y * m_fResScale) + getPosition());
		this->getParent()->addChild(ZKArrow);

		auto offset = (50 + szZK_S1Region.width) * m_fResScale;
		auto move = MoveBy::create(0.15f, Point(0 - offset * m_stRoleSubInfo.side, offset * 1.73));
		auto prop = CallFuncN::create(CC_CALLBACK_1(ZhaoKuo::s1CallBack1, this));
		auto seq = Sequence::create(move, prop, NULL);
		ZKArrow->runAction(seq);
	}
}

/*********************************************************************
** ���ܣ�		���ɼ���
** ���������	
** ����ֵ��		
** �޸ļ�¼��	
*********************************************************************/
void ZhaoKuo::s1CallBack1(Node *who)
{
	auto ptWho = who->getPosition() - getPosition();
	who->removeFromParentAndCleanup(true);

	m_mapS1.clear();
	auto ptLoc = Point::ZERO;
	/* ���ξ����ɫ50����150����30 */
	auto rc = Rect(-125 * m_stRoleSubInfo.side - 75, -szZK_S1Region.height / 2, szZK_S1Region.width, szZK_S1Region.height);
	for (auto index = 0;index < iZK_S1MaxNum;index ++)
	{
		ptLoc.x = ToolFunc::calcRandom(rc.getMinX(), rc.getMaxX());
		ptLoc.y = ToolFunc::calcRandom(rc.getMinY(), rc.getMaxY());

		FlightPropInfo info = {0};
		info.num = m_stZhaoKuoProp[ZhaoKuo_S1Prop].iImgNum;
		memcpy(&(info.skillInfo), &m_stSkillInfo[m_stRoleInfo.actSign], sizeof(SkillInfo));

		auto ZKArrow = FallenProp::create(this, m_stZhaoKuoProp[ZhaoKuo_S1Prop].strPath, info);
		if (NULL != ZKArrow)
		{
			ZKArrow->setPropYaxis(this->getPositionY());
			ZKArrow->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
			ZKArrow->setScaleX(-m_fResScale);
			ZKArrow->setPropPosition(ptWho);		
			ZKArrow->setRotation(-ToolFunc::getAngle(ptLoc, ptWho));
			ZKArrow->setVisible(false);
			ZKArrow->setPropFlag(true);									/* �����򵹵� */
			this->getParent()->addChild(ZKArrow);

			m_mapS1.insert(pair<Sprite*, Point>(ZKArrow, ptLoc - ptWho));	
			auto delay = DelayTime::create(ToolFunc::calcRandom(fZK_S1Delay * 100, fZK_S1Delay * 100 * iZK_S1MaxNum / 2) * 0.002f);
			auto drop = CallFuncN::create(CC_CALLBACK_1(ZhaoKuo::s1CallBack2, this));
			auto seq = Sequence::create(delay, drop, NULL);
			ZKArrow->runAction(seq);		
		}
	}
}

void ZhaoKuo::s1CallBack2(Node *who)
{
	auto arrow = (CommonProp *)who;
	arrow->setVisible(true);
	arrow->runPropCollisionDetective(0.27f, m_mapS1.at(arrow));
}
/* protected: End */