#include "SatelliteProp.h"

USING_NS_CC;

SatelliteProp::SatelliteProp(void)
{
}

SatelliteProp::~SatelliteProp(void)
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
** 功能：		道具移动及开启碰撞检测
** 输入参数：	无
** 返回值：		无
** 修改记录：	
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
	if (NULL == _owner)												/* 无施放者死亡或未设置施放者 */
	{
		releaseCallBack();
		return;
	}

	auto roles = UserData::getInstance()->getRoles();
	auto ownerInfo = _owner->getRoleInfo();
	if (RoleStatus_Death == ownerInfo.status)						/* 施放者死亡 */
	{
		releaseCallBack();
		return;
	}

	float radians = CC_DEGREES_TO_RADIANS(m_stPropInfo.reserve);
	setPosition(Point(m_stPropInfo.skillInfo.xAtkDis * cosf(radians), m_stPropInfo.skillInfo.yAtkDis * sinf(radians) + m_fHeight) + _owner->getPosition());

	m_stPropInfo.reserve = m_stPropInfo.reserve - 2.5f;				/* 每次刷新，角度变化量 */
	if (0 > m_stPropInfo.reserve)
	{
		m_stPropInfo.reserve += 360;
	}

	auto zorder = _owner->getPositionY() - this->getPositionY() + m_fHeight + _owner->getLocalZOrder();
	this->setLocalZOrder(zorder);
}