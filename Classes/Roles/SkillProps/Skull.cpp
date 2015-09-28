#include "Skull.h"

USING_NS_CC;

Skull::Skull(void)
{
}

Skull::~Skull(void)
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
Skull* Skull::create(Role *owner, const std::string& strImg, FlightPropInfo propInfo)
{
	auto sprite = new Skull();
	if (sprite && sprite->initWithFile(strImg + "0" + sprite->getImgSuffix()))
	{
		sprite->InitParam(owner, propInfo, strImg);
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

void Skull::PropCollisionDetective(float dt)
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

	bool bCollision = false;
	auto roles = UserData::getInstance()->getRoles();
	auto rcA = this->getBoundingBox();
	auto ptLoc = Point(this->getPositionX(), this->getPositionY() - m_fHeight);/* ʵ��������۳��߶� */
	this->setLocalZOrder(_owner->getLocalZOrder());

	for(unsigned int index = 0;index < roles.size();index ++)		/* ���˽�ɫ������ȡ */
	{
		auto role = (Role *)roles[index];
		auto info = role->getRoleInfo();

		if ((RoleStatus_Invincible == info.status) || (ownerInfo.camp == info.camp))
		{
			continue;												/* �޵С�ͬ��Ӫ������������ */
		}

		auto rcB = Rect(role->getPositionX() - 10, role->getPositionY(), 20, 80); /* 20, 80 ��Ч���� */

		if (true == rcB.intersectsRect(rcA))						/* ��ײ�ҽ�ɫ����ͶԷ��ܻ�������� */
		{
			auto ptOffset = role->getPosition() - ptLoc;

			/* ������Ч��Χ�ж� */
			if (m_stPropInfo.skillInfo.yAtkDis >= abs(ptOffset.y))
			{
				bCollision = true;
				role->roleHurt(_owner, m_stPropInfo.skillInfo, m_bDown);
				role->setRoleCondition(RoleCondition_Confusion, ConfusionDuration);
			}
		}
	}

	if (true == bCollision)
	{
		releaseWithDelay(m_fStay);
	}	
}