#include "Skull.h"

USING_NS_CC;

Skull::Skull(void)
{
}

Skull::~Skull(void)
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
	if (NULL == _owner)												/* 无施放者死亡或未设置施放者 */
	{
		releaseCallBack();
		return;
	}
	
	auto ownerInfo = _owner->getRoleInfo();
	if (RoleStatus_Death == ownerInfo.status)						/* 施放者死亡 */
	{
		releaseCallBack();
		return;
	}

	bool bCollision = false;
	auto roles = UserData::getInstance()->getRoles();
	auto rcA = this->getBoundingBox();
	auto ptLoc = Point(this->getPositionX(), this->getPositionY() - m_fHeight);/* 实际坐标需扣除高度 */
	this->setLocalZOrder(_owner->getLocalZOrder());

	for(unsigned int index = 0;index < roles.size();index ++)		/* 敌人角色遍历获取 */
	{
		auto role = (Role *)roles[index];
		auto info = role->getRoleInfo();

		if ((RoleStatus_Invincible == info.status) || (ownerInfo.camp == info.camp))
		{
			continue;												/* 无敌、同阵营或是自身不处理 */
		}

		auto rcB = Rect(role->getPositionX() - 10, role->getPositionY(), 20, 80); /* 20, 80 有效区域 */

		if (true == rcB.intersectsRect(rcA))						/* 碰撞且角色方向和对方受击方向符合 */
		{
			auto ptOffset = role->getPosition() - ptLoc;

			/* 动作有效范围判断 */
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