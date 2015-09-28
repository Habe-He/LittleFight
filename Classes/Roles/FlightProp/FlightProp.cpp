#include "FlightProp.h"

USING_NS_CC;

const std::string	strImgSuffix = ".png";			/* ��Դͼ��׺ */

FlightProp::FlightProp()
{
}

FlightProp::~FlightProp(void)
{
}

void FlightProp::runPropCollisionDetective(float dt, Point offset)
{
}

/*********************************************************************
** ���ܣ�		���ñ�־Ϊ����
** ���������	bool bDown: true:����;false:������
**				float fStay: ��ʱʱ��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void FlightProp::setPropFlag(bool bDown, float fStay)
{
	m_bDown = bDown;
	m_fStay = fStay;
}

/*********************************************************************
** ���ܣ�		�������꣬��ȡ���߸߶�
** ���������	Point pt: ���ʩ���ߵ�����
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void FlightProp::setPropPosition(Point pt)
{
	setPosition(pt + _owner->getPosition());
	m_fHeight = pt.y;
	m_rcBgRegion.origin.y += m_fHeight;
}

/*********************************************************************
** ���ܣ�		����
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void FlightProp::releaseCallBack()
{
	this->removeFromParentAndCleanup(true);
}

/*********************************************************************
** ���ܣ�		��ʱ���٣�����������ʱ����������ʧ��
** ���������	float dt: ��ʱ���ٵ�ʱ��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void FlightProp::releaseWithDelay(float dt)
{
// 	if (NULL != this->getActionByTag(iActionSeqTag))
// 	{
// 		this->stopActionByTag(iActionSeqTag);
// 	}

	this->unscheduleUpdate();

	auto delay = DelayTime::create(dt);
	auto prop = CallFuncN::create(CC_CALLBACK_0(FlightProp::releaseCallBack, this));
	auto seq = Sequence::create(delay, prop, NULL);
	this->runAction(seq);
}

/*********************************************************************
** ���ܣ�		��ʼ����Ա����
** ���������	Role *owner: �����ͷ���
**				FlightPropInfo propInfo: ��������
**				std::string: ����ͼƬ��Դ·��
** ����ֵ��		
** �޸ļ�¼��	
*********************************************************************/
void FlightProp::InitParam(Role *owner, FlightPropInfo propInfo, std::string strImg)
{
	m_bDown = false;
	m_fStay = 0.05f;
	m_strImg = strImg;
	m_fHeight = 0.0f;
	_owner = owner;

	memset(&m_stPropInfo, 0, sizeof(FlightPropInfo));
	memcpy(&m_stPropInfo, &propInfo, sizeof(FlightPropInfo));

	m_rcBgRegion = UserData::getInstance()->getBgRegion();
}

/*********************************************************************
** ���ܣ�		��ײ���
** ���������	float dt: ��ʱ���ٵ�ʱ��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void FlightProp::PropCollisionDetective(float dt)
{
	if (NULL == _owner)												/* ��ʩ����������δ����ʩ���� */
	{
		releaseCallBack();
		return;
	}
		
	auto roles = UserData::getInstance()->getRoles();
	auto rcA = this->getBoundingBox();
	auto ownerInfo = _owner->getRoleInfo();
	if (RoleStatus_Death == ownerInfo.status)						/* ʩ�������� */
	{
		releaseCallBack();
		return;
	}

	bool bHit = false;
	auto ptLoc = Point(this->getPositionX(), this->getPositionY() - m_fHeight);/* ʵ��������۳��߶� */
	this->setLocalZOrder(_owner->getLocalZOrder());

	for(unsigned int index = 0;index < roles.size();index ++)		/* ���˽�ɫ������ȡ */
	{
		auto role = (Role *)roles[index];
		auto info = role->getRoleInfo();

		if ((RoleStatus_Invincible == info.status) || (RoleStatus_Death == info.status) || 
			(ownerInfo.camp == info.camp) || (_owner->getSceneID() != role->getSceneID()))
		{
			continue;												/* �޵С�ͬ��Ӫ������������������ */
		}

		auto rcB = Rect(role->getPositionX() - 10, role->getPositionY() + 20, 20, 40); /* ��Ч���� */

		if (true == rcB.intersectsRect(rcA))						/* ��ײ */
		{
			auto ptOffset = role->getPosition() - ptLoc;
			
			if (m_stPropInfo.skillInfo.yAtkDis >= abs(ptOffset.y))	/* ������Ч��Χ�ж� */
			{
				bHit = true;
				role->roleHurt(_owner, m_stPropInfo.skillInfo, m_bDown);
			}
		}
	}

	if (true == bHit)
	{
		releaseWithDelay(dt);
	}
}

/*********************************************************************
** ���ܣ�		��ȡ��Դͼ���ƺ�׺
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
std::string	FlightProp::getImgSuffix()
{
	return strImgSuffix;
}

/*********************************************************************
** ���ܣ�		ͼƬ����
** ���������	��:
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void FlightProp::imgAnimation()
{
	if (1 >= m_stPropInfo.num)
	{
		return;
	}

	std::stringstream stream;
	auto strImg = stream.str();

	Animation* animation = Animation::create();  
	for(int i = 0; i < m_stPropInfo.num; i ++)  
	{
		stream.str("");
		stream << m_strImg << i << strImgSuffix;
		strImg = stream.str();

		animation->addSpriteFrameWithFile(strImg);
	}  
	animation->setDelayPerUnit(m_stPropInfo.dur);  
	animation->setRestoreOriginalFrame(true);
	animation->setLoops(-1);
	auto animate = Animate::create(animation);
	this->runAction(animate);
}