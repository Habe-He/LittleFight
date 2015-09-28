#include "IcePiton.h"

USING_NS_CC;

IcePiton::IcePiton(void)
{
}

IcePiton::~IcePiton(void)
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
IcePiton* IcePiton::create(Role *owner, const std::string& strImg, FlightPropInfo propInfo)
{
	auto sprite = new IcePiton();
	if (sprite && sprite->initWithFile(strImg + "0" + sprite->getImgSuffix()))
	{
		sprite->InitParam(owner, propInfo, strImg);
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

bool IcePiton::PropCollisionDetective()
{
	if (NULL == _owner)												/* ��ʩ����������δ����ʩ���� */
	{
		releaseCallBack();
		return false;
	}

	auto ownerInfo = _owner->getRoleInfo();
	if (RoleStatus_Death == ownerInfo.status)						/* ʩ�������� */
	{
		releaseCallBack();
		return false;
	}

	bool bCollision = false;
	auto roles = UserData::getInstance()->getRoles();
	auto rcA = this->getBoundingBox();

	for(unsigned int index = 0;index < roles.size();index ++)		/* ���˽�ɫ������ȡ */
	{
		auto role = (Role *)roles[index];
		auto info = role->getRoleInfo();

		if ((RoleStatus_Invincible == info.status) || (ownerInfo.camp == info.camp) || (RoleCondition_Frozen == info.condition))
		{
			continue;												/* �޵в����� *//* ����״̬ */
		}

		auto rcB = Rect(role->getPositionX() - 10, role->getPositionY(), 20, 80); /* 20, 80 ��Ч���� */

		if (true == rcB.intersectsRect(rcA))						/* ��ײ�ҽ�ɫ����ͶԷ��ܻ�������� */
		{
			auto ptLoc = role->getPosition();
			auto ptIce = Point(this->getPositionX(), this->getPositionY() - m_fHeight);
			
			if (ptLoc.getDistance(_owner->getPosition()) <= ptIce.getDistance(_owner->getPosition()))/* �з����ڱ�׶��Χ�� */
			{
				bCollision = true;
				role->roleHurt(_owner, m_stPropInfo.skillInfo, m_bDown);
				role->setRoleCondition(RoleCondition_Frozen, FrozenDuration);
			}
		}
	}

	return bCollision;
}