#include "FallenProp.h"

USING_NS_CC;

FallenProp::FallenProp(void)
	: _fPropYasix(0)
{
}


FallenProp::~FallenProp(void)
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
FallenProp* FallenProp::create(Role *owner, const std::string& strImg, FlightPropInfo propInfo)
{
	auto sprite = new FallenProp();
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
** 输入参数：	float duration: 道具移动时间
**				Point ptMoveBy: 移动坐标
** 返回值：		无
** 修改记录：	
*********************************************************************/
void FallenProp::runPropCollisionDetective(float duration, Point ptMoveBy)
{
	auto seq = Sequence::create(MoveBy::create(duration, ptMoveBy), 
		CallFuncN::create(CC_CALLBACK_0(FallenProp::skillCallBack, this)), NULL);
	seq->setTag(iActionSeqTag);
	this->runAction(seq);
	this->scheduleUpdate();
	imgAnimation();
}

void FallenProp::setPropYaxis(float axis)
{
	_fPropYasix = axis;
}

/* protected: */
void FallenProp::skillCallBack()
{
	this->unscheduleUpdate();
	auto delay = DelayTime::create(m_fStay / 3);
	auto prop = CallFuncN::create(CC_CALLBACK_0(FlightProp::releaseCallBack, this));
	auto seq = Sequence::create(delay, prop, NULL);
	this->runAction(seq);
}

void FallenProp::update(float)
{
	PropCollisionDetective(m_fStay);
}

/*********************************************************************
** 功能：		碰撞检测
** 输入参数：	float dt: 延时销毁的时间
** 返回值：		无
** 修改记录：	
*********************************************************************/
void FallenProp::PropCollisionDetective(float dt)
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

	bool bHit = false;
	auto roles = UserData::getInstance()->getRoles();
	auto ptLoc = Point(this->getPositionX(), _fPropYasix);			/* 实际坐标 */
	this->setLocalZOrder(_owner->getLocalZOrder());

	for(unsigned int index = 0;index < roles.size();index ++)		/* 敌人角色遍历获取 */
	{
		auto role = (Role *)roles[index];
		auto info = role->getRoleInfo();

		if ((RoleStatus_Invincible == info.status) || (ownerInfo.camp == info.camp) ||
			(role->getSceneID() != _owner->getSceneID()))
		{
			continue;												/* 无敌、不同场景、同阵营或是自身不处理 */
		}

		auto ptOffset = role->getPosition() - ptLoc;
		if ((role->getPosition().getDistance(ptLoc) < m_stPropInfo.skillInfo.yAtkDis) && 
			(abs(role->getPositionY() - this->getPositionY())< m_stPropInfo.skillInfo.xAtkDis))
		{
			bHit = true;											/* 碰撞 */
			role->roleHurt(_owner, m_stPropInfo.skillInfo, m_bDown);
		}
	}

	if (true == bHit)
	{
		releaseWithDelay(dt);
	}
}