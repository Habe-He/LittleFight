#include "SatelliteProp.h"

USING_NS_CC;

SatelliteProp::SatelliteProp(void)
{
}

SatelliteProp::~SatelliteProp(void)
{
}

/*********************************************************************
** ���ܣ�		���÷��е�����Ӫ���˺�����
** ���������	Role *owner: �����ͷ���
**				const std::string& strImg: ��Դͼ
**				FlightPropInfo propInfo: ��������
** ����ֵ��		
** �޸ļ�¼��	
*********************************************************************/
SatelliteProp* SatelliteProp::create(Role *owner, const std::string& strImg, FlightPropInfo propInfo)
{
	auto sprite = new SatelliteProp();
	if (sprite && sprite->initWithFile(strImg + "0" + sprite->getImgSuffix()))
	{
		sprite->InitParam(owner, propInfo, strImg);
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

/*********************************************************************
** ���ܣ�		�����ƶ���������ײ���
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void SatelliteProp::runPropCollisionDetective()
{
	this->scheduleUpdate();
	imgAnimation();
}

bool SatelliteProp::PropCollisionDetective()
{
	return false;
}

/* protected: */
void SatelliteProp::update(float dt)
{
	if (NULL == _owner)												/* ��ʩ����������δ����ʩ���� */
	{
		releaseCallBack();
		return;
	}

	auto roles = UserData::getInstance()->getRoles();
	auto ownerInfo = _owner->getRoleInfo();
	if (RoleStatus_Death == ownerInfo.status)						/* ʩ�������� */
	{
		releaseCallBack();
		return;
	}

	float radians = CC_DEGREES_TO_RADIANS(m_stPropInfo.reserve);
	setPosition(Point(m_stPropInfo.skillInfo.xAtkDis * cosf(radians), m_stPropInfo.skillInfo.yAtkDis * sinf(radians) + m_fHeight) + _owner->getPosition());

	m_stPropInfo.reserve = m_stPropInfo.reserve - 2.5f;				/* ÿ��ˢ�£��Ƕȱ仯�� */
	if (0 > m_stPropInfo.reserve)
	{
		m_stPropInfo.reserve += 360;
	}

	auto zorder = _owner->getPositionY() - this->getPositionY() + m_fHeight + _owner->getLocalZOrder();
	this->setLocalZOrder(zorder);
}