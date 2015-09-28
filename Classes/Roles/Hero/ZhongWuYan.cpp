#include "ZhongWuYan.h"
#include "UserInfo/UserData.h"

USING_NS_CC;
using namespace cocostudio;

ZhongWuYan::ZhongWuYan(void)
{
}

ZhongWuYan::~ZhongWuYan(void)
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
void ZhongWuYan::loadArmature()
{
	m_stRoleInfo.arAnimate = Armature::create(m_strRoleName.c_str());
	if (NULL == m_stRoleInfo.arAnimate)
	{
		return;
	}

	this->addChild(m_stRoleInfo.arAnimate);

	/* ע�ᶯ��֡�¼��Ͷ����ص����� */
	m_stRoleInfo.arAnimate->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(ZhongWuYan::actionFrameEventCallFunc, this, std::placeholders::_1
		, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	m_stRoleInfo.arAnimate->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(ZhongWuYan::actionMovementCallFunc, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

/*********************************************************************
** ���ܣ�		��ʼ�����ܷ��е���
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void ZhongWuYan::initFlightPropInfo()
{
	m_stZhongWuYanProp.strPath = getFlightPropPath() + "ZhongWuYan_S4Prop";
	m_stZhongWuYanProp.ptOffset = Point(150, 70) * m_fResScale;
	m_stZhongWuYanProp.iImgNum = 11;
}

/*********************************************************************
** ���ܣ�		�����ص�����
** ���������	
** ����ֵ�� 	
** �޸ļ�¼��	
*********************************************************************/
void ZhongWuYan::actionMovementCallFunc(Armature *ar, MovementEventType type, const std::string& str)
{
	movement(str, type, 0.5f);
}

/*********************************************************************
** ���ܣ�		֡�¼�
** ���������	
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
void ZhongWuYan::actionFrameEventCallFunc(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
{
	frameEvent(evt);

	bool bDown = false;
	if (evt == getFrameEventName(FrameEvent_Shot_FD))
	{
		bDown = true;
	}

	if ((evt == getFrameEventName(FrameEvent_Shot)) || (evt == getFrameEventName(FrameEvent_Shot_FD)))
	{
		// 		if ((action_attack == m_stRoleInfo.actInfo.act) || (action_twice_atk == m_stRoleInfo.actInfo.act) || 
		// 			(action_thrice_atk == m_stRoleInfo.actInfo.act))
		// 		{
		// 		}

		if (RoleAct_SkillThree == m_stRoleInfo.actSign)
		{
			SkillThree();
		}

		if (RoleAct_SkillFour == m_stRoleInfo.actSign)
		{
			SkillFour();
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
bool ZhongWuYan::runActionAttack()
{
	bool bRet = Role::runActionAttack();
	if (true == bRet)
	{
		playEffectOgg("C073");
	}

	return bRet;
}

/*********************************************************************
** ���ܣ�		��ͨ�����ڶ���
** ���������	��
** ����ֵ��		bool:true:����ִ�гɹ�
** �޸ļ�¼��	
*********************************************************************/
bool ZhongWuYan::runActionTwiceAtk()
{
	bool bRet = Role::runActionTwiceAtk();
	if (true == bRet)
	{
		playEffectOgg("C073");
	}

	return bRet;
}

/*********************************************************************
** ���ܣ�		��ͨ����������
** ���������	��
** ����ֵ��		bool:true:����ִ�гɹ�
** �޸ļ�¼��	
*********************************************************************/
bool ZhongWuYan::runActionThriceAtk()
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
bool ZhongWuYan::runActionSkillOne()
{
	bool bRet = Role::runActionSkillOne();
	if (true == bRet)
	{
		playEffectOgg("080ZS");
	}

	return bRet;
}

/*********************************************************************
** ���ܣ�		ִ�м��ܶ�
** ���������	��
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
bool ZhongWuYan::runActionSkillTwo()
{
	bool bRet = Role::runActionSkillTwo();
	if (true == bRet)
	{
		playEffectOgg("SLJ");
	}

	return bRet;
}

/*********************************************************************
** ���ܣ�		ִ�м�����
** ���������	��
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
bool ZhongWuYan::runActionSkillThree()
{
	bool bRet = Role::runActionSkillThree();
	if (true == bRet)
	{
		playEffectOgg("165HY");
	}

	return bRet;
}

/*********************************************************************
** ���ܣ�		ִ�м�����
** ���������	��
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
bool ZhongWuYan::runActionSkillFour()
{
	bool bRet = Role::runActionSkillFour();
	if (true == bRet)
	{
		playEffectOgg("166ZH");
	}

	return bRet;
}
/* ����ִ�� End*/

/*********************************************************************
** ���ܣ�		����3
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void ZhongWuYan::SkillThree()
{
	if (RoleCreMode_Preview == m_eRoleCreMode)
	{
		return;
	}

	auto index = 0;
	auto roles = UserData::getInstance()->getRoles();

	auto iter = roles.begin();
	while (iter != roles.end()) 
	{
		auto role = (Role *)*iter;
		if ((m_stRoleInfo.camp == role->getRoleInfo().camp) ||		/* �Ƕ��� */
			(getSceneID() != role->getSceneID()))					/* ����ͬһ���� */
		{
			iter = roles.erase(iter);								/* ɾ������ */
		}
		else 
		{
			++iter;
		}
	}

	if (0 != roles.size())											/* �е��� */
	{
		index = ToolFunc::calcRandom(1, roles.size());
		auto role = (Role *)roles[index - 1];

		auto sz = Size(m_stSkillInfo[RoleAct_SkillThree].xAtkDis, m_stSkillInfo[RoleAct_SkillThree].yAtkDis) * 0.8f;
		auto rc = Rect(0, 0, 0, 0);
		rc.origin.x = role->getPositionX() - m_stSkillInfo[RoleAct_SkillThree].xAtkDis;	/* ����Ŀ�귶Χ */
		rc.origin.y = role->getPositionY() - m_stSkillInfo[RoleAct_SkillThree].yAtkDis;
		rc.size = sz * 2;

		auto ptDes = Point(0, 0);
		ptDes.x = ToolFunc::calcRandom(rc.getMinX(), rc.getMaxX());
		ptDes.y = ToolFunc::calcRandom(rc.getMinY(), rc.getMaxY());
		setPosition(ptDes);
	}
}

/*********************************************************************
** ���ܣ�		����4
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void ZhongWuYan::SkillFour()
{
	FlightPropInfo info = {0};
	info.num = m_stZhongWuYanProp.iImgNum;
	info.dur = 0.2f / m_stZhongWuYanProp.iImgNum;
	memcpy(&(info.skillInfo), &m_stSkillInfo[RoleAct_SkillFour], sizeof(SkillInfo));

	auto zwyProp = CommonProp::create(this, m_stZhongWuYanProp.strPath, info);
	if (NULL != zwyProp)
	{
		zwyProp->setScaleX(m_stRoleSubInfo.side * m_fResScale);
		zwyProp->setScaleY(m_fResScale);
		zwyProp->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
		zwyProp->setPropFlag(true, 0.15f);
		zwyProp->setPropPosition(Point(-m_stZhongWuYanProp.ptOffset.x * m_stRoleSubInfo.side, m_stZhongWuYanProp.ptOffset.y));
		this->getParent()->addChild(zwyProp);
		zwyProp->runPropCollisionDetective(0.5f, Point(-m_stSkillInfo[RoleAct_SkillFour].xAtkDis * m_stRoleSubInfo.side, 0));
	}
}
/* protected: End */