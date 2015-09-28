#include "JingKe.h"

USING_NS_CC;
using namespace cocostudio;

JingKe::JingKe(void)
{
}

JingKe::~JingKe(void)
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
void JingKe::loadArmature()
{
	m_stRoleInfo.arAnimate = Armature::create(m_strRoleName.c_str());
	if (NULL == m_stRoleInfo.arAnimate)
	{
		return;
	}

	this->addChild(m_stRoleInfo.arAnimate);

	/* ע�ᶯ��֡�¼��Ͷ����ص����� */
	m_stRoleInfo.arAnimate->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(JingKe::actionFrameEventCallFunc, this, std::placeholders::_1
		, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	m_stRoleInfo.arAnimate->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(JingKe::actionMovementCallFunc, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

/*********************************************************************
** ���ܣ�		��ʼ�����ܷ��е���
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void JingKe::initFlightPropInfo()
{
	m_stJingkeProp[JingKe_S1Prop].strPath = getFlightPropPath() + "JingKe_S1Prop";
	m_stJingkeProp[JingKe_S1Prop].ptOffset = Point(80, 50) * m_fResScale;
	m_stJingkeProp[JingKe_S1Prop].iImgNum = 1;

	m_stJingkeProp[JingKe_S4Prop].strPath = getFlightPropPath() + "JingKe_S4Prop";
	m_stJingkeProp[JingKe_S4Prop].ptOffset = Point::ZERO * m_fResScale;
	m_stJingkeProp[JingKe_S4Prop].iImgNum = 36;
}

/*********************************************************************
** ���ܣ�		�����ص�����
** ���������	
** ����ֵ�� 	
** �޸ļ�¼��	
*********************************************************************/
void JingKe::actionMovementCallFunc(Armature *ar, MovementEventType type, const std::string& str)
{
	movement(str, type, 0.5f);
}

/*********************************************************************
** ���ܣ�		֡�¼�
** ���������	
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
void JingKe::actionFrameEventCallFunc(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
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
			skillOne(m_stRoleInfo.panel.atk, false);
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
bool JingKe::runActionAttack()
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
bool JingKe::runActionTwiceAtk()
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
bool JingKe::runActionThriceAtk()
{
	bool bRet = Role::runActionThriceAtk();
	if (true == bRet)
	{
		playEffectOgg("C1");
	}

	return bRet;
}

/*********************************************************************
** ���ܣ�		ִ�м���һ
** ���������	��
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
bool JingKe::runActionSkillOne()
{
	bool bRet = Role::runActionSkillOne();
	if (true == bRet)
	{
		playEffectOgg("C2A");
	}

	return bRet;
}

/*********************************************************************
** ���ܣ�		ִ�м��ܶ�
** ���������	��
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
bool JingKe::runActionSkillTwo()
{
	bool bRet = Role::runActionSkillTwo();
	if (true == bRet)
	{
		playEffectOgg("063TQ");
	}

	return bRet;
}

/*********************************************************************
** ���ܣ�		ִ�м�����
** ���������	��
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
bool JingKe::runActionSkillThree()
{
	bool bRet = Role::runActionSkillThree();
	if (true == bRet)
	{
		playEffectOgg("055DD");
	}

	return bRet;
}

/*********************************************************************
** ���ܣ�		ִ�м�����
** ���������	��
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
bool JingKe::runActionSkillFour()
{
	bool bRet = Role::runActionSkillFour();
	if (true == bRet)
	{
		playEffectOgg("061ZH");
	}

	return bRet;
}
/* ����ִ�� End*/

/* protected: End */
void JingKe::skillOne(int atk, bool bDown)
{
	FlightPropInfo info = {0};
	info.num = m_stJingkeProp[JingKe_S1Prop].iImgNum;
	memcpy(&(info.skillInfo), &m_stSkillInfo[m_stRoleInfo.actSign], sizeof(SkillInfo));
	auto jingKeProp = CommonProp::create(this, m_stJingkeProp[JingKe_S1Prop].strPath, info);

	if (NULL != jingKeProp)
	{
		jingKeProp->setScaleX(m_stRoleSubInfo.side);
		jingKeProp->setScaleY(m_fResScale);
		jingKeProp->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
		jingKeProp->setPropPosition(Point(-m_stJingkeProp[JingKe_S1Prop].ptOffset.x * m_stRoleSubInfo.side, m_stJingkeProp[JingKe_S1Prop].ptOffset.y));
		jingKeProp->setPropFlag(bDown);
		this->getParent()->addChild(jingKeProp);
		jingKeProp->runPropCollisionDetective(0.2f, Point(-m_stSkillInfo[m_stRoleInfo.actSign].xAtkDis * m_stRoleSubInfo.side, 0));
	}
}

void JingKe::skillFour()
{
	FlightPropInfo info = {0};
	info.num = m_stJingkeProp[JingKe_S4Prop].iImgNum;
	info.dur = 0.3f / info.num;
	memcpy(&(info.skillInfo), &m_stSkillInfo[RoleAct_SkillFour], sizeof(SkillInfo));

	auto sprite = CommonProp::create(this, m_stJingkeProp[JingKe_S4Prop].strPath, info);
	sprite->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	sprite->setScaleY(0.87f);
	sprite->setPosition(m_stJingkeProp[JingKe_S4Prop].ptOffset);  
	this->getParent()->addChild(sprite); 
	sprite->runPropCollisionDetective(0.3f, Point(0, 0));

// 	auto sprite = CommonProp::create("Roles/FlightProps/JiangYi_SWind0.png", m_stSkillInfo[m_stRoleInfo.actInfo.act], 
// 		Point(getPositionX(), m_stRoleInfo.originY), m_stRoleInfo.camp, m_stRoleInfo.model, m_stRoleInfo.panel.atk);
// 	//Sprite *sprite = Sprite::create("Roles/FlightProps/JiangYi_SWind0.png");  
// 	sprite->setPosition(Point::ANCHOR_MIDDLE_LEFT);
// 	sprite->setScaleX(m_stRoleSubInfo.dir);
// 	sprite->setPropFlag(true);
// 	sprite->setPosition(Point(getPositionX() - m_stRoleSubInfo.dir * 150, m_stRoleInfo.originY + 40));  
// 	this->getParent()->addChild(sprite, 1);  
// 
// 	Animation* animation = Animation::create();  
// 	for( int i = 0; i < 11; i ++)  
// 	{  
// 		auto windString = __String::createWithFormat("Roles/FlightProps/JiangYi_SWind%d.png", i); 
// 		animation->addSpriteFrameWithFile(windString->getCString());
// 	}  
// 	animation->setDelayPerUnit(0.5f / 11.0f);  
// 	animation->setRestoreOriginalFrame(true);  
// 	animation->setLoops(1);
// 	Animate *animate = Animate::create(animation);
// 	//sprite->runAction( Sequence::create(Spawn::createWithTwoActions(animate, MoveBy::create(0.5f, Point(0 - m_stSkillInfo[action_s3].xAtkDis * m_stRoleSubInfo.dir, 0))), CallFuncN::create(CC_CALLBACK_1(JiangYi::skilThreeCallBack, this)), NULL));
// 	sprite->runAction(animate);
// 	sprite->runPropCollisionDetective(0.5f, Point(0 - m_stSkillInfo[action_s3].xAtkDis * m_stRoleSubInfo.dir, 0));
//}
}