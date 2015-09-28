#include "QuYuan.h"

USING_NS_CC;
using namespace cocostudio;

QuYuan::QuYuan(void)
{
}

QuYuan::~QuYuan(void)
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
void QuYuan::loadArmature()
{
	m_stRoleInfo.arAnimate = Armature::create(m_strRoleName.c_str());
	if (NULL == m_stRoleInfo.arAnimate)
	{
		return;
	}

	this->addChild(m_stRoleInfo.arAnimate);

	/* ע�ᶯ��֡�¼��Ͷ����ص����� */
	m_stRoleInfo.arAnimate->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(QuYuan::actionFrameEventCallFunc, this, std::placeholders::_1
		, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	m_stRoleInfo.arAnimate->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(QuYuan::actionMovementCallFunc, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

/*********************************************************************
** ���ܣ�		��ʼ�����ܷ��е���
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void QuYuan::initFlightPropInfo()
{
	m_strQuYuanProp[QuYuan_Magic].strPath = getFlightPropPath() + "QuYuan_Magic";
	m_strQuYuanProp[QuYuan_Magic].ptOffset = Point(110, 80) * m_fResScale;
	m_strQuYuanProp[QuYuan_Magic].iImgNum = 1;

	m_strQuYuanProp[QuYuan_S3Prop].strPath = getFlightPropPath() + "QuYuan_S3Prop";
	m_strQuYuanProp[QuYuan_S3Prop].ptOffset = Point(180, 85) * m_fResScale;
	m_strQuYuanProp[QuYuan_S3Prop].iImgNum = 6;

	m_strQuYuanProp[QuYuan_S4Prop].strPath = getFlightPropPath() + "QuYuan_S4Prop";
	m_strQuYuanProp[QuYuan_S4Prop].ptOffset = Point(180, 0) * m_fResScale;
	m_strQuYuanProp[QuYuan_S4Prop].iImgNum = 6;
}

/*********************************************************************
** ���ܣ�		Boss Ai��������
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void QuYuan::aiActSequenceBoss()
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
void QuYuan::actionMovementCallFunc(Armature *ar, MovementEventType type, const std::string& str)
{
	movement(str, type, 0.5f);
}

/*********************************************************************
** ���ܣ�		֡�¼�
** ���������	
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
void QuYuan::actionFrameEventCallFunc(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
{
	frameEvent(evt);

	bool bDown = false;
	if (evt == getFrameEventName(FrameEvent_Shot_FD))
	{
		bDown = true;
	}

	if ((evt == getFrameEventName(FrameEvent_Shot)) || (evt == getFrameEventName(FrameEvent_Shot_FD)))
	{
		if (RoleAct_SkillTwo == m_stRoleInfo.actSign)
		{
			skillTwo(bDown);
		}
		else if (RoleAct_SkillThree == m_stRoleInfo.actSign)
		{
			skillThree();
		}
		else if (RoleAct_SkillFour == m_stRoleInfo.actSign)
		{
			skillFour();
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
bool QuYuan::runActionAttack()
{
	bool bRet = Role::runActionAttack();
	if (true == bRet)
	{
		playEffectOgg("C97");
	}

	return bRet;
}

/*********************************************************************
** ���ܣ�		��ͨ�����ڶ���
** ���������	��
** ����ֵ��		bool:true:����ִ�гɹ�
** �޸ļ�¼��	
*********************************************************************/
bool QuYuan::runActionTwiceAtk()
{
	bool bRet = Role::runActionTwiceAtk();
	if (true == bRet)
	{
		playEffectOgg("C97");
	}

	return bRet;
}

/*********************************************************************
** ���ܣ�		��ͨ����������
** ���������	��
** ����ֵ��		bool:true:����ִ�гɹ�
** �޸ļ�¼��	
*********************************************************************/
bool QuYuan::runActionThriceAtk()
{
	bool bRet = Role::runActionThriceAtk();
	if (true == bRet)
	{
		playEffectOgg("C147");
	}

	return bRet;
}

/*********************************************************************
** ���ܣ�		ִ�м���һ
** ���������	��
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
bool QuYuan::runActionSkillOne()
{
	bool bRet = Role::runActionSkillOne();
	if (true == bRet)
	{
		playEffectOgg("035DG");
	}

	return bRet;
}

/*********************************************************************
** ���ܣ�		ִ�м��ܶ�
** ���������	��
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
bool QuYuan::runActionSkillTwo()
{
	bool bRet = Role::runActionSkillTwo();
	if (true == bRet)
	{
		playEffectOgg("035DQ");
	}

	return bRet;
}

/*********************************************************************
** ���ܣ�		ִ�м�����
** ���������	��
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
bool QuYuan::runActionSkillThree()
{
	bool bRet = Role::runActionSkillThree();
	if (true == bRet)
	{
		playEffectOgg("156H");
	}

	return bRet;
}

/*********************************************************************
** ���ܣ�		ִ�м�����
** ���������	��
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
bool QuYuan::runActionSkillFour()
{
	bool bRet = Role::runActionSkillFour();
	if (true == bRet)
	{
		playEffectOgg("164ZH");
	}

	return bRet;
}
/* ����ִ�� End*/

void QuYuan::skillTwo(bool bDown)
{
	FlightPropInfo info = {0};
	info.num = m_strQuYuanProp[QuYuan_Magic].iImgNum;
	memcpy(&(info.skillInfo), &m_stSkillInfo[RoleAct_SkillTwo], sizeof(SkillInfo));

	auto QuYuanProp = CommonProp::create(this, m_strQuYuanProp[QuYuan_Magic].strPath, info);

	if (NULL != QuYuanProp)
	{
		QuYuanProp->setScaleX(m_stRoleSubInfo.side * m_fResScale);
		QuYuanProp->setScaleY(m_fResScale);
		QuYuanProp->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
		QuYuanProp->setPropPosition(Point(-m_strQuYuanProp[QuYuan_Magic].ptOffset.x * m_stRoleSubInfo.side, m_strQuYuanProp[QuYuan_Magic].ptOffset.y));
		QuYuanProp->setPropFlag(bDown);
		this->getParent()->addChild(QuYuanProp);
		QuYuanProp->runPropCollisionDetective(0.3f, Point(-m_stSkillInfo[RoleAct_SkillTwo].xAtkDis * m_stRoleSubInfo.side, 0));
	}
}

void QuYuan::skillThree()
{
	FlightPropInfo info = {0};
	info.num = m_strQuYuanProp[QuYuan_S3Prop].iImgNum;
	info.dur = 0.25f / m_strQuYuanProp[QuYuan_S3Prop].iImgNum;
	memcpy(&(info.skillInfo), &m_stSkillInfo[RoleAct_SkillThree], sizeof(SkillInfo));

	auto sprite = CommonProp::create(this, m_strQuYuanProp[QuYuan_S3Prop].strPath, info);
	if (NULL != sprite)
	{
		sprite->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
		sprite->setScaleX(m_stRoleSubInfo.side * m_fResScale);
		sprite->setPropFlag(true, 0.2f);
		sprite->setPropPosition(Point(-m_stRoleSubInfo.side * m_strQuYuanProp[QuYuan_S3Prop].ptOffset.x, m_strQuYuanProp[QuYuan_S3Prop].ptOffset.y));  
		this->getParent()->addChild(sprite);
		sprite->runPropCollisionDetective(0.3f, Point(-m_stSkillInfo[RoleAct_SkillThree].xAtkDis * m_stRoleSubInfo.side, 0));
	}
}

void QuYuan::skillFour()
{
	FlightPropInfo info = {0};
	info.num = m_strQuYuanProp[QuYuan_S4Prop].iImgNum;
	info.dur = 0.25f / m_strQuYuanProp[QuYuan_S4Prop].iImgNum;
	memcpy(&(info.skillInfo), &m_stSkillInfo[RoleAct_SkillFour], sizeof(SkillInfo));

	auto sprite = CommonProp::create(this, m_strQuYuanProp[QuYuan_S4Prop].strPath, info);
	if (NULL != sprite)
	{
		sprite->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
		sprite->setScaleX(m_stRoleSubInfo.side * m_fResScale);
		sprite->setScaleY(m_fResScale);
		sprite->setPropFlag(true, 0.2f);
		sprite->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
		sprite->setPropPosition(Point(-m_stRoleSubInfo.side * m_strQuYuanProp[QuYuan_S4Prop].ptOffset.x, m_strQuYuanProp[QuYuan_S4Prop].ptOffset.y));    
		this->getParent()->addChild(sprite);
		sprite->runPropCollisionDetective(0.6f, Point(-m_stSkillInfo[RoleAct_SkillFour].xAtkDis * m_stRoleSubInfo.side, 0));
	}
}
/* protected: End */