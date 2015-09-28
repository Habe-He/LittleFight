#include "Gamut.h"

USING_NS_CC;

Gamut::Gamut(void)
	: _resIndex(0)
{
}

Gamut::~Gamut(void)
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
Gamut* Gamut::create(Role *owner, const std::string& strImg, FlightPropInfo propInfo)
{
	auto sprite = new Gamut();
	if (sprite && sprite->init())
	{
		sprite->InitParam(owner, propInfo, strImg);
		sprite->loadActionRes();
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
void Gamut::runPropCollisionDetective()
{
	this->schedule(schedule_selector(Gamut::gamutSchedule), m_stPropInfo.dur);
}

void Gamut::loadActionRes()
{
	for (int index = 0;index < m_stPropInfo.num;index ++)
	{
		auto str = __String::createWithFormat("%s%d%s", m_strImg.c_str(), index, getImgSuffix().c_str());
		_vecRes.push_back(str->getCString());
	}
}

void Gamut::gamutSchedule(float dt)
{
	this->setTexture(_vecRes[_resIndex]);
	if (0 == (_resIndex - 1)%3)
	{
		PropCollisionDetective(m_fStay);
	}
	_resIndex = _resIndex + 1;

	if (m_stPropInfo.num == _resIndex)								/* ������� */
	{
		this->unschedule(schedule_selector(Gamut::gamutSchedule));
		releaseWithDelay(m_fStay);
	}
}

/*********************************************************************
** ���ܣ�		��ײ���
** ���������	float dt: ��ʱ���ٵ�ʱ��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void Gamut::PropCollisionDetective(float dt)
{
	if (NULL == _owner)												/* ��ʩ����������δ����ʩ���� */
	{
		releaseCallBack();
		return;
	}

	auto ownerInfo = _owner->getRoleInfo();
	if (RoleStatus_Death == ownerInfo.status)						/* ʩ�������� */
	{
		releaseCallBack();
		return;
	}

	this->setLocalZOrder(m_rcBgRegion.getMaxY());	
	auto roles = UserData::getInstance()->getRoles();

	for(unsigned int index = 0;index < roles.size();index ++)		/* ���˽�ɫ������ȡ */
	{
		auto role = (Role *)roles[index];
		auto info = role->getRoleInfo();

		if ((RoleStatus_Invincible == info.status) || (ownerInfo.camp == info.camp) ||
			(role->getSceneID() != _owner->getSceneID()))
		{
			continue;												/* �޵С���ͬ������ͬ��Ӫ������������ */
		}

		if (m_stPropInfo.num - 2 == _resIndex)						/* ���һ�ι��� */
		{
			m_bDown = true;
		}
		role->roleHurt(_owner, m_stPropInfo.skillInfo, m_bDown);
	}
}