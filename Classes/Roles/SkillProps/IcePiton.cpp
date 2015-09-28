#include "IcePiton.h"

USING_NS_CC;

IcePiton::IcePiton(void)
{
}

IcePiton::~IcePiton(void)
{
}

/*********************************************************************
** 功能：		设置飞行道具阵营、伤害属性
** 输入参数：	Role *owner: 技能释放者
**				const std::string& strImg: 资源图
**				FlightPropInfo propInfo: 道具数据
** 返回值：		
** 修改记录：	
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
	if (NULL == _owner)												/* 无施放者死亡或未设置施放者 */
	{
		releaseCallBack();
		return false;
	}

	auto ownerInfo = _owner->getRoleInfo();
	if (RoleStatus_Death == ownerInfo.status)						/* 施放者死亡 */
	{
		releaseCallBack();
		return false;
	}

	bool bCollision = false;
	auto roles = UserData::getInstance()->getRoles();
	auto rcA = this->getBoundingBox();

	for(unsigned int index = 0;index < roles.size();index ++)		/* 敌人角色遍历获取 */
	{
		auto role = (Role *)roles[index];
		auto info = role->getRoleInfo();

		if ((RoleStatus_Invincible == info.status) || (ownerInfo.camp == info.camp) || (RoleCondition_Frozen == info.condition))
		{
			continue;												/* 无敌不处理 *//* 冰冻状态 */
		}

		auto rcB = Rect(role->getPositionX() - 10, role->getPositionY(), 20, 80); /* 20, 80 有效区域 */

		if (true == rcB.intersectsRect(rcA))						/* 碰撞且角色方向和对方受击方向符合 */
		{
			auto ptLoc = role->getPosition();
			auto ptIce = Point(this->getPositionX(), this->getPositionY() - m_fHeight);
			
			if (ptLoc.getDistance(_owner->getPosition()) <= ptIce.getDistance(_owner->getPosition()))/* 敌方处于冰锥范围内 */
			{
				bCollision = true;
				role->roleHurt(_owner, m_stPropInfo.skillInfo, m_bDown);
				role->setRoleCondition(RoleCondition_Frozen, FrozenDuration);
			}
		}
	}

	return bCollision;
}