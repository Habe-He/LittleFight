#include "ZhuangJi.h"

USING_NS_CC;
using namespace cocostudio;

ZhuangJi::ZhuangJi(void)
{
}

ZhuangJi::~ZhuangJi(void)
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
void ZhuangJi::loadArmature()
{
	m_stRoleInfo.arAnimate = Armature::create(m_strRoleName.c_str());
	if (NULL == m_stRoleInfo.arAnimate)
	{
		return;
	}

	this->addChild(m_stRoleInfo.arAnimate);

	/* ע�ᶯ��֡�¼��Ͷ����ص����� */
	m_stRoleInfo.arAnimate->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(ZhuangJi::actionFrameEventCallFunc, this, std::placeholders::_1
		, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	m_stRoleInfo.arAnimate->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(ZhuangJi::actionMovementCallFunc, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

/*********************************************************************
** ���ܣ�		��ʼ�����ܷ��е���
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void ZhuangJi::initFlightPropInfo()
{
	m_stZhuangJiProp[ZhuangJi_S1Prop].strPath = getFlightPropPath() + "ZhuangJi_S1Prop";
	m_stZhuangJiProp[ZhuangJi_S1Prop].ptOffset = Point(90, 80) * m_fResScale;
	m_stZhuangJiProp[ZhuangJi_S1Prop].iImgNum = 1;

	m_stZhuangJiProp[ZhuangJi_S2Prop].strPath = getFlightPropPath() + "ZhuangJi_S2Prop";
	m_stZhuangJiProp[ZhuangJi_S2Prop].ptOffset = Point(90, 80) * m_fResScale;
	m_stZhuangJiProp[ZhuangJi_S2Prop].iImgNum = 1;
}

/*********************************************************************
** ���ܣ�		�����ص�����
** ���������	
** ����ֵ�� 	
** �޸ļ�¼��	
*********************************************************************/
void ZhuangJi::actionMovementCallFunc(Armature *ar, MovementEventType type, const std::string& str)
{
	movement(str, type, 0.5f);
}

/*********************************************************************
** ���ܣ�		֡�¼�
** ���������	
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
void ZhuangJi::actionFrameEventCallFunc(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
{
	frameEvent(evt);

	bool bDown = false;
	if (evt == getFrameEventName(FrameEvent_Shot_FD))
	{
		bDown = true;
	}

	if ((evt == getFrameEventName(FrameEvent_Shot)) || (evt == getFrameEventName(FrameEvent_Shot_FD)))
	{
		if (RoleAct_SkillOne == m_stRoleInfo.actSign)
		{
			ZhuangJiSkill(ZhuangJi_S1Prop);
		}

		if (RoleAct_SkillTwo == m_stRoleInfo.actSign)
		{
			ZhuangJiSkill(ZhuangJi_S2Prop);
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
bool ZhuangJi::runActionAttack()
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
bool ZhuangJi::runActionTwiceAtk()
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
bool ZhuangJi::runActionThriceAtk()
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
bool ZhuangJi::runActionSkillOne()
{
	bool bRet = Role::runActionSkillOne();
	if (true == bRet)
	{
		playEffectOgg("073JN");
	}

	return bRet;
}

/*********************************************************************
** ���ܣ�		ִ�м��ܶ�
** ���������	��
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
bool ZhuangJi::runActionSkillTwo()
{
	bool bRet = Role::runActionSkillTwo();
	if (true == bRet)
	{
		playEffectOgg("080JN");
	}

	return bRet;
}

/*********************************************************************
** ���ܣ�		ׯ������1
** ���������	ZJBladeProp blade :���ܵ���ID
** ����ֵ��		
** �޸ļ�¼��	
*********************************************************************/ 
void ZhuangJi::ZhuangJiSkill(ZhuangJiFlight blade)
{
	FlightPropInfo info = {0};
	info.num = m_stZhuangJiProp[blade].iImgNum;
	memcpy(&(info.skillInfo), &m_stSkillInfo[m_stRoleInfo.actSign], sizeof(SkillInfo));

	auto prop = CommonProp::create(this, m_stZhuangJiProp[blade].strPath, info);
	if (NULL != prop)
	{
		prop->setScaleX(m_stRoleSubInfo.side * m_fResScale);
		prop->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
		prop->setPropPosition(Point(-m_stZhuangJiProp[blade].ptOffset.x * m_stRoleSubInfo.side, m_stZhuangJiProp[blade].ptOffset.y));
		this->getParent()->addChild(prop);
		prop->runPropCollisionDetective(0.2f, Point(-m_stSkillInfo[m_stRoleInfo.actSign].xAtkDis * m_stRoleSubInfo.side, 0));
	}
}
/* ����ִ�� End*/
/* protected: End */