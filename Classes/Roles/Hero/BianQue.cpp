#include "BianQue.h"
#include "Roles/SkillProps/CommonProp.h"
#include "Roles/SkillProps/EnergyBall.h"

USING_NS_CC;
using namespace cocostudio;

const float bq_fIceDuration = 5.0f;		/* ������ʱ�� */

BianQue::BianQue(void)
{
}

BianQue::~BianQue(void)
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
void BianQue::loadArmature()
{
	m_stRoleInfo.arAnimate = Armature::create(m_strRoleName.c_str());
	if (NULL == m_stRoleInfo.arAnimate)
	{
		return;
	}

	memset(m_hIcePiton, 0, sizeof(m_hIcePiton));

	this->addChild(m_stRoleInfo.arAnimate);

	/* ע�ᶯ��֡�¼��Ͷ����ص����� */
	m_stRoleInfo.arAnimate->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(BianQue::actionFrameEventCallFunc, this, std::placeholders::_1
		, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	m_stRoleInfo.arAnimate->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(BianQue::actionMovementCallFunc, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

/*********************************************************************
** ���ܣ�		��ʼ����ɫ��������
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void BianQue::initActInherent()
{
	Role::initActInherent();

	m_stActMode[RoleAct_SkillOne] = RoleActMode_Super;			/* ����һ */
	m_stActMode[RoleAct_SkillTwo] = RoleActMode_Super;			/* ���ܶ� */			
	m_stActMode[RoleAct_SkillThree] = RoleActMode_Control;		/* ������ */
}

/*********************************************************************
** ���ܣ�		��ʼ�����ܷ��е���
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void BianQue::initFlightPropInfo()
{
	/* �չ�ħ���� */
	m_stBianQueProp[BianQue_Magic].strPath = getFlightPropPath() + "BianQue_Magic";
	m_stBianQueProp[BianQue_Magic].ptOffset = Point(0, 0) * m_fResScale;
	m_stBianQueProp[BianQue_Magic].iImgNum = 1;

	/* ��Ѫħ�� */
	m_stBianQueProp[BianQue_Light].strPath = getFlightPropPath() + "BianQue_S2Prop";
	m_stBianQueProp[BianQue_Light].ptOffset = Point(0, 200) * m_fResScale;
	m_stBianQueProp[BianQue_Light].iImgNum = 5;

	/* ��ħ�� */
	m_stBianQueProp[BianQue_Ice].strPath = getFlightPropPath() + "BianQue_S3Prop";
	m_stBianQueProp[BianQue_Ice].ptOffset = Point(0, 80) * m_fResScale;
	m_stBianQueProp[BianQue_Ice].iImgNum = 2;

	/* ��� */
	m_stBianQueProp[BianQue_Phenix].strPath = getFlightPropPath() + "BianQue_S4Prop";
	m_stBianQueProp[BianQue_Phenix].ptOffset = Point(0, 80) * m_fResScale;
	m_stBianQueProp[BianQue_Phenix].iImgNum = 9;
}

/*********************************************************************
** ���ܣ�		�����ص�����
** ���������	
** ����ֵ�� 	
** �޸ļ�¼��	
*********************************************************************/
void BianQue::actionMovementCallFunc(Armature *ar, MovementEventType type, const std::string& str)
{
	movement(str, type, 0.5f);
}

/*********************************************************************
** ���ܣ�		֡�¼�
** ���������	
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
void BianQue::actionFrameEventCallFunc(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
{
	frameEvent(evt);

	bool bDown = false;
	if (evt == getFrameEventName(FrameEvent_Shot_FD))
	{
		bDown = true;
	}

	if ((evt == getFrameEventName(FrameEvent_Shot)) || (evt == getFrameEventName(FrameEvent_Shot_FD)))
	{
		if (RoleAct_Attack == m_stRoleInfo.actSign)
		{
			NormalAttack(Point(100, 90), bDown);
		}

		if (RoleAct_Twice_Atk == m_stRoleInfo.actSign)
		{
			NormalAttack(Point(140, 50), bDown);
		}

		if (RoleAct_Thrice_Atk == m_stRoleInfo.actSign)
		{
			NormalAttack(Point(80, 110), bDown);
		}

		if (RoleAct_SkillTwo == m_stRoleInfo.actSign)
		{
			SkillTwo();
			SkillTwo();
			SkillTwo();
		}

		if (RoleAct_SkillThree == m_stRoleInfo.actSign)
		{
			this->unschedule(schedule_selector(BianQue::IceSchedule));
			SkillThree(90.0f, BianQueS3_One);
			SkillThree(330.0f, BianQueS3_Two);
			SkillThree(210.0f, BianQueS3_Three);
			this->scheduleOnce(schedule_selector(BianQue::IceSchedule), bq_fIceDuration);
		}

		if (RoleAct_SkillFour == m_stRoleInfo.actSign)
		{
			SkillFour();
		}
	}
}

void BianQue::updateRole()
{
	for (int index = BianQueS3_One;index < BianQueS3_Max;index ++)
	{
		if (NULL != m_hIcePiton[index])
		{
			if (true == m_hIcePiton[index]->PropCollisionDetective())
			{
				removeIceByID(index);
			}
		}
	}

	if (true == isRoleLearnedTalent(RoleTalent_ZhangKongZhanChang))	/* �ƿ�ս�� */
	{
		if (m_stRoleInfo.panel.hpCurrent * 1.0f / m_stRoleInfo.panel.hpTotal < 0.35f)
		{
			m_stRoleBuff.atk *= 1.8f;
		}
		else
		{
			m_stRoleBuff.atk = 0;
		}
	}

	Role::updateRole();
}

/*********************************************************************
** ���ܣ�		ִ����ײ���
** ���������	bool bDown:true:����;false:������
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void BianQue::roleCollisionDetective(bool bDown)
{
	auto roles = UserData::getInstance()->getRoles();

	for(unsigned int index = 0;index < roles.size();index ++)		/* ���˽�ɫ������ȡ */
	{
		auto role = (Role *)roles[index];
		auto info = role->getRoleInfo();

		if ((RoleStatus_Death == info.status) || (RoleStatus_Invincible == info.status) || (m_iSceneID != role->getSceneID()))
		{
			continue;												/* �޵С�ͬ��Ӫ������������ *//* С��鲻������ */
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
				if (RoleActMode_Super == m_stActMode[m_stRoleInfo.actSign])
				{
					if (info.camp == m_stRoleInfo.camp)
					{
						role->setRoleHpUp(m_stSkillInfo[m_stRoleInfo.actSign].damage);/* ��ǰͬ��Ӫ������ */
					}
					else
					{
						role->roleHurt(this, m_stSkillInfo[m_stRoleInfo.actSign], bDown);/* ��ǰ��ͬ��Ӫ���˺� */
					}
				}
				else												
				{
					if (info.camp != m_stRoleInfo.camp)
					{
						role->roleHurt(this, m_stSkillInfo[m_stRoleInfo.actSign], bDown);/* ��ǰ��ͬ��Ӫ���˺� */
					}
					if (RoleActMode_Physical == m_stActMode[m_stRoleInfo.actSign])
					{
						m_bRoleActBreak = true;
					}
				}
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
bool BianQue::runActionAttack()
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
bool BianQue::runActionTwiceAtk()
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
bool BianQue::runActionThriceAtk()
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
bool BianQue::runActionSkillOne()
{
	bool bRet = Role::runActionSkillOne();
	if (true == bRet)
	{
		playEffectOgg("C035Q");
	}

	return bRet;
}

/*********************************************************************
** ���ܣ�		ִ�м��ܶ�
** ���������	��
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
bool BianQue::runActionSkillTwo()
{
	bool bRet = Role::runActionSkillTwo();
	if (true == bRet)
	{
		playEffectOgg("C037HF");
	}

	return bRet;
}

/*********************************************************************
** ���ܣ�		ִ�м�����
** ���������	��
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
bool BianQue::runActionSkillThree()
{
	bool bRet = Role::runActionSkillThree();
	if (true == bRet)
	{
		playEffectOgg("C034JN");
	}

	return bRet;
}

/*********************************************************************
** ���ܣ�		ִ�м�����
** ���������	��
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
bool BianQue::runActionSkillFour()
{
	bool bRet = Role::runActionSkillFour();
	if (true == bRet)
	{
		playEffectOgg("033ZH");
	}

	return bRet;
}
/* ����ִ�� End*/

/*********************************************************************
** ���ܣ�		�չ���
** ���������	Point ptLoc: ħ�����ʼλ��
**				bool bDown: ����
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void BianQue::NormalAttack(Point ptLoc, bool bDown)
{
	FlightPropInfo info = {0};
	info.num = m_stBianQueProp[BianQue_Magic].iImgNum;
	memcpy(&(info.skillInfo), &m_stSkillInfo[m_stRoleInfo.actSign], sizeof(SkillInfo));

	auto bqProp = CommonProp::create(this, m_stBianQueProp[BianQue_Magic].strPath, info);

	if (NULL != bqProp)
	{
		bqProp->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
		bqProp->setScaleX(m_stRoleSubInfo.side * m_fResScale);
		bqProp->setPropPosition(Point(-ptLoc.x * m_stRoleSubInfo.side * m_fResScale, ptLoc.y * m_fResScale));
		bqProp->setPropFlag(bDown);

		this->getParent()->addChild(bqProp);
		bqProp->runPropCollisionDetective(0.3f, Point(-m_stSkillInfo[m_stRoleInfo.actSign].xAtkDis * m_stRoleSubInfo.side, 0));
	}
}

/*********************************************************************
** ���ܣ�		����
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void BianQue::SkillTwo()
{
	FlightPropInfo info = {0};
	info.num = m_stBianQueProp[BianQue_Light].iImgNum;
	info.dur = 0.5f / info.num;
	memcpy(&(info.skillInfo), &m_stSkillInfo[m_stRoleInfo.actSign], sizeof(SkillInfo));

	auto energyBall = EnergyBall::create(this, m_stBianQueProp[BianQue_Light].strPath, info);

	if (NULL != energyBall)
	{
		energyBall->setPropPosition(m_stBianQueProp[BianQue_Light].ptOffset);
		energyBall->setScale(m_fResScale);
		energyBall->setAnchorPoint(Point::ANCHOR_MIDDLE);
		energyBall->setSceneID(m_iSceneID);
		this->getParent()->addChild(energyBall);
		energyBall->energyBallAction();
	}
}

/*********************************************************************
** ���ܣ�		����3
** ���������	float angle: ����ʼ�Ƕ�
**				int id: ��id
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void BianQue::SkillThree(float angle, int id)
{
	removeIceByID(id);

	FlightPropInfo info = {0};
	info.reserve = angle;											/* ��ʼ�Ƕ� */
	info.num = m_stBianQueProp[BianQue_Ice].iImgNum;
	info.dur = 0.15f / m_stBianQueProp[BianQue_Ice].iImgNum;
	memcpy(&(info.skillInfo), &m_stSkillInfo[RoleAct_SkillThree], sizeof(SkillInfo));

	m_hIcePiton[id] = IcePiton::create(this, m_stBianQueProp[BianQue_Ice].strPath, info);

	if (NULL != m_hIcePiton[id])
	{
		m_hIcePiton[id]->setScale(m_fResScale);
		m_hIcePiton[id]->setPropPosition(m_stBianQueProp[BianQue_Ice].ptOffset);
		this->getParent()->addChild(m_hIcePiton[id]);
		m_hIcePiton[id]->runPropCollisionDetective();
	}
}

/*********************************************************************
** ���ܣ�		����4
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void BianQue::SkillFour()
{
	FlightPropInfo info = {0};
	info.num = m_stBianQueProp[BianQue_Phenix].iImgNum;
	info.dur = 0.7f / m_stBianQueProp[BianQue_Phenix].iImgNum;
	memcpy(&(info.skillInfo), &m_stSkillInfo[m_stRoleInfo.actSign], sizeof(SkillInfo));

	auto phenix = CommonProp::create(this, m_stBianQueProp[BianQue_Phenix].strPath, info);

	if (NULL != phenix)
	{
		phenix->setScaleX(m_stRoleSubInfo.side * m_fResScale);
		phenix->setScaleY(m_fResScale);
		phenix->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);

		phenix->setPropPosition(Point(-m_stBianQueProp[BianQue_Phenix].ptOffset.x * m_stRoleSubInfo.side, 
			m_stBianQueProp[BianQue_Phenix].ptOffset.y));
		phenix->setPropFlag(true);

		this->getParent()->addChild(phenix);
		phenix->runPropCollisionDetective(2.3f, Point(-m_stSkillInfo[m_stRoleInfo.actSign].xAtkDis * m_stRoleSubInfo.side, 0));
	}
}

/*********************************************************************
** ���ܣ�		�Ƴ���
** ���������	int id: ��id
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
bool BianQue::removeIceByID(int id)
{
	bool bRet = false;

	if (NULL != m_hIcePiton[id])
	{
		m_hIcePiton[id]->removeFromParentAndCleanup(true);
		m_hIcePiton[id] = NULL;
		bRet = true;
	}

	return bRet;
}

/*********************************************************************
** ���ܣ�		����ʱ��
** ���������	float dt
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void BianQue::IceSchedule(float dt)
{
	for (int index = BianQueS3_One;index < BianQueS3_Max;index ++)
	{
		removeIceByID(index);
	}
}
/* protected: End */