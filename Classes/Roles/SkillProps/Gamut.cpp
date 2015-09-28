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
** 功能：		设置飞行道具阵营、伤害属性
** 输入参数：	Role *owner: 技能释放者
**				const std::string& strImg: 资源图
**				FlightPropInfo propInfo: 道具数据
** 返回值：		
** 修改记录：	
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
** 功能：		道具移动及开启碰撞检测
** 输入参数：	无
** 返回值：		无
** 修改记录：	
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

	if (m_stPropInfo.num == _resIndex)								/* 播放完毕 */
	{
		this->unschedule(schedule_selector(Gamut::gamutSchedule));
		releaseWithDelay(m_fStay);
	}
}

/*********************************************************************
** 功能：		碰撞检测
** 输入参数：	float dt: 延时销毁的时间
** 返回值：		无
** 修改记录：	
*********************************************************************/
void Gamut::PropCollisionDetective(float dt)
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

	this->setLocalZOrder(m_rcBgRegion.getMaxY());	
	auto roles = UserData::getInstance()->getRoles();

	for(unsigned int index = 0;index < roles.size();index ++)		/* 敌人角色遍历获取 */
	{
		auto role = (Role *)roles[index];
		auto info = role->getRoleInfo();

		if ((RoleStatus_Invincible == info.status) || (ownerInfo.camp == info.camp) ||
			(role->getSceneID() != _owner->getSceneID()))
		{
			continue;												/* 无敌、不同场景、同阵营或是自身不处理 */
		}

		if (m_stPropInfo.num - 2 == _resIndex)						/* 最后一次攻击 */
		{
			m_bDown = true;
		}
		role->roleHurt(_owner, m_stPropInfo.skillInfo, m_bDown);
	}
}