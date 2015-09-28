#include "YuQing.h"

USING_NS_CC;
using namespace cocostudio;

YuQing::YuQing(void)
{
}

YuQing::~YuQing(void)
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
void YuQing::loadArmature()
{
	m_stRoleInfo.arAnimate = Armature::create(m_strRoleName.c_str());
	if (NULL == m_stRoleInfo.arAnimate)
	{
		return;
	}

	this->addChild(m_stRoleInfo.arAnimate);

	/* ע�ᶯ��֡�¼��Ͷ����ص����� */
	m_stRoleInfo.arAnimate->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(YuQing::actionFrameEventCallFunc, this, std::placeholders::_1
		, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	m_stRoleInfo.arAnimate->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(YuQing::actionMovementCallFunc, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

/*********************************************************************
** ���ܣ�		��ʼ�����ܷ��е���
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void YuQing::initFlightPropInfo()
{
	m_stYuQingProp[YuQing_Normal].strPath = getFlightPropPath() + "YuQing_AtkProp";
	m_stYuQingProp[YuQing_Normal].ptOffset = Point(100, 70) * m_fResScale;
	m_stYuQingProp[YuQing_Normal].iImgNum = 1;

	m_stYuQingProp[YuQing_S2Prop].strPath = getFlightPropPath() + "YuQing_S2Prop";
	m_stYuQingProp[YuQing_S2Prop].ptOffset = Point(0, 80) * m_fResScale;
	m_stYuQingProp[YuQing_S2Prop].iImgNum = 5;
}

/*********************************************************************
** ���ܣ�		�����ص�����
** ���������	
** ����ֵ�� 	
** �޸ļ�¼��	
*********************************************************************/
void YuQing::actionMovementCallFunc(Armature *ar, MovementEventType type, const std::string& str)
{
	movement(str, type, 0.5f);
}

/*********************************************************************
** ���ܣ�		֡�¼�
** ���������	
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
void YuQing::actionFrameEventCallFunc(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
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
			NormalAttack(bDown);
		}

		if (RoleAct_SkillTwo == m_stRoleInfo.actSign)
		{
			SkillTwo();
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
bool YuQing::runActionAttack()
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
bool YuQing::runActionTwiceAtk()
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
bool YuQing::runActionThriceAtk()
{
	bool bRet = Role::runActionThriceAtk();
	if (true == bRet)
	{
		playEffectOgg("C072");
	}

	return bRet;
}

/*********************************************************************
** ���ܣ�		ִ�м���һ
** ���������	��
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
bool YuQing::runActionSkillOne()
{
	bool bRet = Role::runActionSkillOne();
	if (true == bRet)
	{
		playEffectOgg("021DD");
	}

	return bRet;
}

/*********************************************************************
** ���ܣ�		ִ�м��ܶ�
** ���������	��
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
bool YuQing::runActionSkillTwo()
{
	bool bRet = Role::runActionSkillTwo();
	if (true == bRet)
	{
		playEffectOgg("020JN");
	}

	return bRet;
}
/* ����ִ�� End*/

/*********************************************************************
** ���ܣ�		��ͨ����
** ���������	bool bDown : �����Ƿ񵹵�
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void YuQing::NormalAttack(bool bDown)
{
	FlightPropInfo info = {0};
	info.num = m_stYuQingProp[YuQing_Normal].iImgNum;
	memcpy(&(info.skillInfo), &m_stSkillInfo[m_stRoleInfo.actSign], sizeof(SkillInfo));

	auto yqProp = CommonProp::create(this, m_stYuQingProp[YuQing_Normal].strPath, info);
	if (NULL != yqProp)
	{
		yqProp->setScaleX(m_stRoleSubInfo.side/* * m_fResScale*/);
		//yqProp->setScaleY(m_fResScale);
		yqProp->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
		yqProp->setPropFlag(bDown);
		yqProp->setPropPosition(Point(-m_stYuQingProp[YuQing_Normal].ptOffset.x * m_stRoleSubInfo.side, m_stYuQingProp[YuQing_Normal].ptOffset.y));
		this->getParent()->addChild(yqProp);
		yqProp->runPropCollisionDetective(0.2f, Point(-m_stSkillInfo[m_stRoleInfo.actSign].xAtkDis * m_stRoleSubInfo.side, 0));
	}
}

/*********************************************************************
** ���ܣ�		����2
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void YuQing::SkillTwo()
{
	FlightPropInfo info = {0};
	info.num = m_stYuQingProp[YuQing_S2Prop].iImgNum;
	info.dur = 0.35f / m_stYuQingProp[YuQing_S2Prop].iImgNum;
	memcpy(&(info.skillInfo), &m_stSkillInfo[RoleAct_SkillTwo], sizeof(SkillInfo));

	auto yqProp = CommonProp::create(this, m_stYuQingProp[YuQing_S2Prop].strPath, info);
	if (NULL != yqProp)
	{
		yqProp->setScale(m_fResScale);
		yqProp->setAnchorPoint(Point::ANCHOR_MIDDLE);
		yqProp->setPropFlag(false, 0.15f);
		yqProp->setPropPosition(Point(-m_stYuQingProp[YuQing_S2Prop].ptOffset.x * m_stRoleSubInfo.side, m_stYuQingProp[YuQing_S2Prop].ptOffset.y));
		this->getParent()->addChild(yqProp);
		yqProp->runPropCollisionDetective(0.2f, Point(-m_stSkillInfo[RoleAct_SkillTwo].xAtkDis * m_stRoleSubInfo.side, 0));
	}
}
/* protected: End */