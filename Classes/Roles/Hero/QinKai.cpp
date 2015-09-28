#include "QinKai.h"

USING_NS_CC;
using namespace cocostudio;

QinKai::QinKai(void)
{
}

QinKai::~QinKai(void)
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
void QinKai::loadArmature()
{
	m_stRoleInfo.arAnimate = Armature::create(m_strRoleName.c_str());
	if (NULL == m_stRoleInfo.arAnimate)
	{
		return;
	}

	this->addChild(m_stRoleInfo.arAnimate);

	/* ע�ᶯ��֡�¼��Ͷ����ص����� */
	m_stRoleInfo.arAnimate->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(QinKai::actionFrameEventCallFunc, this, std::placeholders::_1
		, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	m_stRoleInfo.arAnimate->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(QinKai::actionMovementCallFunc, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

/*********************************************************************
** ���ܣ�		��ʼ�����ܷ��е���
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void QinKai::initFlightPropInfo()
{
	m_stQinKaiProp.strPath = getFlightPropPath() + "QinKai_Magic";
	m_stQinKaiProp.ptOffset = Point(180, 100) * m_fResScale;
	m_stQinKaiProp.iImgNum = 1;
}

/*********************************************************************
** ���ܣ�		�����ص�����
** ���������	
** ����ֵ�� 	
** �޸ļ�¼��	
*********************************************************************/
void QinKai::actionMovementCallFunc(Armature *ar, MovementEventType type, const std::string& str)
{
	movement(str, type, 0.5f);
}

/*********************************************************************
** ���ܣ�		֡�¼�
** ���������	
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
void QinKai::actionFrameEventCallFunc(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
{
	frameEvent(evt);

	if (RoleAct_SkillOne == m_stRoleInfo.actSign)
	{
		if (getFrameEventName(FrameEvent_Attack_FD) == evt)
		{
			shaky();
		}
	}

	if (getFrameEventName(FrameEvent_Shot) == evt)
	{
		SkillTwo();
	}
}

/* ����ִ�� Begin*/
/*********************************************************************
** ���ܣ�		��ͨ������һ��
** ���������	��
** ����ֵ��		bool:true:����ִ�гɹ�
** �޸ļ�¼��	
*********************************************************************/
bool QinKai::runActionAttack()
{
	bool bRet = Role::runActionAttack();
	if (true == bRet)
	{
		playEffectOgg("C2");
	}

	return bRet;
}

/*********************************************************************
** ���ܣ�		��ͨ�����ڶ���
** ���������	��
** ����ֵ��		bool:true:����ִ�гɹ�
** �޸ļ�¼��	
*********************************************************************/
bool QinKai::runActionTwiceAtk()
{
	bool bRet = Role::runActionTwiceAtk();
	if (true == bRet)
	{
		playEffectOgg("C2");
	}

	return bRet;
}

/*********************************************************************
** ���ܣ�		��ͨ����������
** ���������	��
** ����ֵ��		bool:true:����ִ�гɹ�
** �޸ļ�¼��	
*********************************************************************/
bool QinKai::runActionThriceAtk()
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
bool QinKai::runActionSkillOne()
{
	bool bRet = Role::runActionSkillOne();
	if (true == bRet)
	{
		playEffectOgg("012ZH");
	}

	return bRet;
}

/*********************************************************************
** ���ܣ�		ִ�м��ܶ�
** ���������	��
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
bool QinKai::runActionSkillTwo()
{
	bool bRet = Role::runActionSkillTwo();
	if (true == bRet)
	{
		playEffectOgg("009HY");
	}

	return bRet;
}
/* ����ִ�� End*/

void QinKai::SkillTwo()
{
	FlightPropInfo info = {0};
	info.num = m_stQinKaiProp.iImgNum;
	info.dur = 0.0f;
	memcpy(&(info.skillInfo), &m_stSkillInfo[RoleAct_SkillTwo], sizeof(SkillInfo));

	auto prop = CommonProp::create(this, m_stQinKaiProp.strPath, info);
	if (NULL != prop)
	{
		prop->setScaleX(m_stRoleSubInfo.side * m_fResScale);
		prop->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
		prop->setPropPosition(Point(-m_stQinKaiProp.ptOffset.x * m_stRoleSubInfo.side, m_stQinKaiProp.ptOffset.y));
		this->getParent()->addChild(prop);
		prop->runPropCollisionDetective(0.5f, Point(-m_stSkillInfo[RoleAct_SkillTwo].xAtkDis * m_stRoleSubInfo.side, 0));
	}
}
/* protected: End */