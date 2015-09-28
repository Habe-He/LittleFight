#include "PangNuan.h"
#include "Roles/SkillProps/CommonProp.h"
#include "Roles/SkillProps/EnergyBall.h"

USING_NS_CC;
using namespace cocostudio;

const float pn_fIceDuration = 5.0f;					/* ������ʱ�� */

PangNuan::PangNuan(void)
{
}

PangNuan::~PangNuan(void)
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
void PangNuan::loadArmature()
{
	m_stRoleInfo.arAnimate = Armature::create(m_strRoleName.c_str());
	if (NULL == m_stRoleInfo.arAnimate)
	{
		return;
	}

	memset(m_hIcePiton, 0, sizeof(m_hIcePiton));

	this->addChild(m_stRoleInfo.arAnimate);

	/* ע�ᶯ��֡�¼��Ͷ����ص����� */
	m_stRoleInfo.arAnimate->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(PangNuan::actionFrameEventCallFunc, this, std::placeholders::_1
		, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	m_stRoleInfo.arAnimate->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(PangNuan::actionMovementCallFunc, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

/*********************************************************************
** ���ܣ�		��ʼ����ɫ��������
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void PangNuan::initActInherent()
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
void PangNuan::initFlightPropInfo()
{
	m_stPangNuanProp[PangNuan_Magic].strPath = getFlightPropPath() + "PangNuan_Magic";
	m_stPangNuanProp[PangNuan_Magic].ptOffset = Point(150, 100) * m_fResScale;
	m_stPangNuanProp[PangNuan_Magic].iImgNum = 1;

	m_stPangNuanProp[PangNuan_Light].strPath = getFlightPropPath() + "BianQue_S2Prop";
	m_stPangNuanProp[PangNuan_Light].ptOffset = Point(0, 200) * m_fResScale;
	m_stPangNuanProp[PangNuan_Light].iImgNum = 5;

	m_stPangNuanProp[PangNuan_Ice].strPath = getFlightPropPath() + "BianQue_S3Prop";
	m_stPangNuanProp[PangNuan_Ice].ptOffset = Point(0, 80) * m_fResScale;
	m_stPangNuanProp[PangNuan_Ice].iImgNum = 2;
}

/*********************************************************************
** ���ܣ�		�����ص�����
** ���������	
** ����ֵ�� 	
** �޸ļ�¼��	
*********************************************************************/
void PangNuan::actionMovementCallFunc(Armature *ar, MovementEventType type, const std::string& str)
{
	movement(str, type, 0.5f);
}

/*********************************************************************
** ���ܣ�		֡�¼�
** ���������	
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
void PangNuan::actionFrameEventCallFunc(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
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
			SkillTwo();
			SkillTwo();
		}

		if (RoleAct_SkillThree == m_stRoleInfo.actSign)
		{
			this->unschedule(schedule_selector(PangNuan::IceSchedule));
			SkillThree(90.0f, PangNuanS3_One);
			SkillThree(330.0f, PangNuanS3_Two);
			SkillThree(210.0f, PangNuanS3_Three);
			this->scheduleOnce(schedule_selector(PangNuan::IceSchedule), pn_fIceDuration);
		}
	}
}

void PangNuan::updateRole()
{
	for (int index = PangNuanS3_One;index < PangNuanS3_Max;index ++)
	{
		if (NULL != m_hIcePiton[index])
		{
			if (true == m_hIcePiton[index]->PropCollisionDetective())
			{
				removeIceByID(index);
			}
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
void PangNuan::roleCollisionDetective(bool bDown)
{
	auto roles = UserData::getInstance()->getRoles();

	for(unsigned int index = 0;index < roles.size();index ++)		/* ���˽�ɫ������ȡ */
	{
		auto role = (Role *)roles[index];
		auto info = role->getRoleInfo();

		if ((RoleStatus_Death == info.status) || (RoleStatus_Invincible == info.status) || (m_iSceneID != role->getSceneID()))
		{
			continue;												/* �޵С�ͬ��Ӫ������������ *//* Ԯ���������� */
		}
		auto hitSide = RoleDir_Left;								/* �Է����������� */
		hitSide = (getPositionX() > role->getPositionX()) ? RoleDir_Left : RoleDir_Right;

		if (-1 != hitSide * m_stRoleSubInfo.atkSide)				/* ȷ�Ϸ������� */
		{
			/* ��ײ�ҽ�ɫ����ͶԷ��ܻ�������� *//* �ڵ����ҷ����󹥻����ڵ����󷽲��ҹ��� */
			auto ptOffset = role->getPosition() - getPosition();/* ���λ�� */

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
bool PangNuan::runActionAttack()
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
bool PangNuan::runActionTwiceAtk()
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
bool PangNuan::runActionThriceAtk()
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
bool PangNuan::runActionSkillOne()
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
bool PangNuan::runActionSkillTwo()
{
	bool bRet = Role::runActionSkillTwo();
	if (true == bRet)
	{
		playEffectOgg("094HF");
	}

	return bRet;
}

/*********************************************************************
** ���ܣ�		ִ�м�����
** ���������	��
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
bool PangNuan::runActionSkillThree()
{
	bool bRet = Role::runActionSkillThree();
	if (true == bRet)
	{
		playEffectOgg("C034JN");
	}

	return bRet;
}
/* ����ִ�� End*/

/*********************************************************************
** ���ܣ�		��ͨ����
** ���������	bool bDown:true:����;false:������
** ����ֵ��		
** �޸ļ�¼��	
*********************************************************************/
void PangNuan::NormalAttack(bool bDown)
{
	FlightPropInfo info = {0};
	info.num = m_stPangNuanProp[PangNuan_Magic].iImgNum;
	memcpy(&(info.skillInfo), &m_stSkillInfo[m_stRoleInfo.actSign], sizeof(SkillInfo));

	auto pnMagic = CommonProp::create(this, m_stPangNuanProp[PangNuan_Magic].strPath, info);
	auto pt = m_stPangNuanProp[PangNuan_Magic].ptOffset;

	if (NULL != pnMagic)
	{
		pnMagic->setScaleX(m_stRoleSubInfo.side * m_fResScale);
		pnMagic->setScaleY(m_fResScale);
		pnMagic->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);

		if (RoleAct_Thrice_Atk == m_stRoleInfo.actSign)				/* ����������ƫ������ */
		{
			pt.x = pt.x / 2;
		}

		pnMagic->setPropPosition(Point(-pt.x * m_stRoleSubInfo.side, pt.y));
		pnMagic->setPropFlag(bDown);
		this->getParent()->addChild(pnMagic);
		pnMagic->runPropCollisionDetective(0.3f, Point(-m_stSkillInfo[m_stRoleInfo.actSign].xAtkDis * m_stRoleSubInfo.side, 0));
	}
}

void PangNuan::SkillTwo()
{
	FlightPropInfo info = {0};
	info.num = m_stPangNuanProp[PangNuan_Light].iImgNum;
	info.dur = 0.5f / m_stPangNuanProp[PangNuan_Light].iImgNum;
	memcpy(&(info.skillInfo), &m_stSkillInfo[m_stRoleInfo.actSign], sizeof(SkillInfo));

	auto energyBall = EnergyBall::create(this, m_stPangNuanProp[PangNuan_Light].strPath, info);

	if (NULL != energyBall)
	{
		energyBall->setPropPosition(m_stPangNuanProp[PangNuan_Light].ptOffset);
		energyBall->setPosition(getPosition() + m_stPangNuanProp[PangNuan_Light].ptOffset);
		energyBall->setScale(m_fResScale);
		energyBall->setAnchorPoint(Point::ANCHOR_MIDDLE);
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
void PangNuan::SkillThree(float angle, int id)
{
	removeIceByID(id);

	FlightPropInfo info = {0};
	info.reserve = angle;											/* ��ʼ�Ƕ� */
	info.num = m_stPangNuanProp[PangNuan_Ice].iImgNum;
	info.dur = 0.15f / m_stPangNuanProp[PangNuan_Ice].iImgNum;
	memcpy(&(info.skillInfo), &m_stSkillInfo[RoleAct_SkillThree], sizeof(SkillInfo));

	m_hIcePiton[id] = IcePiton::create(this, m_stPangNuanProp[PangNuan_Ice].strPath, info);

	if (NULL != m_hIcePiton[id])
	{
		m_hIcePiton[id]->setScale(m_fResScale);
		m_hIcePiton[id]->setPropPosition(m_stPangNuanProp[PangNuan_Ice].ptOffset);
		this->getParent()->addChild(m_hIcePiton[id]);
		m_hIcePiton[id]->runPropCollisionDetective();
	}
}

/*********************************************************************
** ���ܣ�		�Ƴ���
** ���������	int id: ��id
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
bool PangNuan::removeIceByID(int id)
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
void PangNuan::IceSchedule(float dt)
{
	for (int index = PangNuanS3_One;index < PangNuanS3_Max;index ++)
	{
		removeIceByID(index);
	}
}
/* protected: End */