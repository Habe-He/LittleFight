#include "EnergyBall.h"

USING_NS_CC;

const float EnergyBallMoveSpeed = 160.0f;		/* 能量球移动速度 */

typedef struct tagBorderSelect
{
	int		range;								/* 可取的值范围 */
	int		axis;								/* 不变的轴,0:保留x轴 1:保留y轴 */
	int		value;								/* 不变轴值 */
} BorderSelect;

EnergyBall::EnergyBall(void)
	: m_bCollision( false)
	, m_Role( NULL)
	, m_iSceneID( 0 )
{
}

EnergyBall::~EnergyBall(void)
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
EnergyBall* EnergyBall::create(Role *owner, const std::string& strImg, FlightPropInfo propInfo)
{
	auto *sprite = new EnergyBall();
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
** 功能：		能量球动作
** 输入参数：	
** 返回值：		
** 修改记录：	
*********************************************************************/
void EnergyBall::energyBallAction()
{
	Rect rc = Rect(0 - m_stPropInfo.skillInfo.xAtkDis / 5, 0 - m_stPropInfo.skillInfo.yAtkDis / 5, 
		m_stPropInfo.skillInfo.xAtkDis / 2.5f, m_stPropInfo.skillInfo.yAtkDis / 2.5f);	/* 已能量球可行范围定义矩形 */	
	Point pt[3];
	getEnergyBallMovePoint(rc, pt);

	auto t1 = (pt[0] - this->getPosition()).getLength() / EnergyBallMoveSpeed;
	auto move1 = MoveTo::create(t1, pt[0]);
	auto t2 = (pt[1] - pt[0]).getLength() / EnergyBallMoveSpeed;
	auto move2 = MoveTo::create(t2, pt[1]);
	auto t3 = (pt[2] - pt[1]).getLength() / EnergyBallMoveSpeed;
	auto move3 = MoveTo::create(t3, pt[2]);
	auto actCallBack = CallFunc::create(CC_CALLBACK_0(EnergyBall::energyBallSearchObject, this));
	auto delay = DelayTime::create(0.05f);
	auto seq = Sequence::create(move1, delay, move2, delay, move3, actCallBack, NULL);
	this->runAction(seq);
	this->scheduleUpdate();
	imgAnimation();
}

void EnergyBall::setSceneID(int id)
{
	m_iSceneID = id;
}

void EnergyBall::update(float dt)
{
	this->setLocalZOrder(m_rcBgRegion.getMaxY() - this->getPositionY() + 500);
	auto pt = this->getPosition();
	if (pt.y > m_rcBgRegion.getMaxY())
	{
		this->setPositionY(m_rcBgRegion.getMaxY());
	}
	if (pt.y < m_rcBgRegion.getMinY())
	{
		this->setPositionY(m_rcBgRegion.getMinY());
	}
	if (pt.x > m_rcBgRegion.getMaxX())
	{
		this->setPositionX(m_rcBgRegion.getMaxX());
	}
	if (pt.x < m_rcBgRegion.getMinX())
	{
		this->setPositionX(m_rcBgRegion.getMinX());
	}
	PropCollisionDetective();
}

/*********************************************************************
** 功能：		碰撞检测
** 输入参数：	
** 返回值：		
** 修改记录：	
*********************************************************************/
void EnergyBall::PropCollisionDetective()
{
	if (false == m_bCollision)										/* 还不到检测时候 */
	{
		return;
	}

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

	auto roles = UserData::getInstance()->getRoles();
	if (0 == roles.size())											/* 没有角色（预览模式） */
	{
		releaseCallBack();
		return;
	}

	if (RoleStatus_Death == m_Role->getRoleInfo().status)			/* 选中的角色死亡，另选角色 */
	{
		energyBallSearchObject();
	}
	else
	{
		auto ptRole = m_Role->getPosition();
		ptRole.y = ptRole.y + m_fHeight;							/* 修正目标点为角色身体 */
		auto ptOffset = ptRole - this->getPosition();
		this->setPosition(this->getPosition() + ptOffset / ptOffset.getLength() * EnergyBallMoveSpeed * 0.4f);
	}

	bool bCollision = false;
	auto rcA = this->getBoundingBox();

	auto rcB = Rect(m_Role->getPositionX() - 10, m_Role->getPositionY() + 20, 20, m_fHeight); /* 有效区域 */

	if (true == rcB.intersectsRect(rcA))
	{
		bCollision = true;
		auto info = m_Role->getRoleInfo();
		if (ownerInfo.camp == info.camp)						/* 对己补给 */
		{
			m_Role->setRoleHpUp(m_stPropInfo.skillInfo.damage);
		}
		else													/* 对敌伤害 */
		{
			m_Role->roleHurt(_owner, m_stPropInfo.skillInfo, m_bDown);
		}
	}
	
	if (true == bCollision)
	{
		releaseWithDelay(m_fStay);
	}
}

void EnergyBall::skillCallBack(Node *who)
{
	this->unscheduleUpdate();
	auto delay = DelayTime::create(m_fStay);
	auto prop = CallFuncN::create(CC_CALLBACK_0(FlightProp::releaseCallBack, this));
	auto seq = Sequence::create(delay, prop, NULL);
	this->runAction(seq);
}

/*********************************************************************
** 功能：		能量球运动后追逐角色
** 输入参数：	无
** 返回值：		无
** 修改记录：	
*********************************************************************/
void EnergyBall::energyBallSearchObject()
{
	auto roles = UserData::getInstance()->getRoles();

	auto itr = roles.begin();
	while (itr != roles.end())
	{
		auto role = (Role *)(*itr);
		auto info = role->getRoleInfo();
		if ((RoleStatus_Death == info.status) || (m_iSceneID != role->getSceneID()))/* 已阵亡或不同区域 */
		{
			itr = roles.erase(itr);
		}
		else
		{
			itr ++;
		}
	}
	auto size = roles.size();

	if (0 < size)
	{
		m_Role = (Role *)roles.at(ToolFunc::calcRandom(0, size - 1));
		m_bCollision = true;
	}
	else															/* 预览模式，销毁 */
	{
		this->removeFromParentAndCleanup(true);
	}
}

/*********************************************************************
** 功能：		在指定范围内选取控制点
** 输入参数：	Rect rc: 指定的范围
**				Point *ptSelected: 选取的3点
** 返回值：		无
** 修改记录：	
*********************************************************************/
void EnergyBall::getEnergyBallMovePoint(Rect rc, Point *ptSelected)
{
	BorderSelect border[4] = {
		{ (int)rc.size.height, 0, (int)rc.getMinX()}, { (int)rc.size.width, 1, (int)rc.getMaxY()},
		{ (int)rc.size.height, 0, (int)rc.getMaxX()}, { (int)rc.size.width, 1, (int)rc.getMinY()}		
	};

	int b[4] = {0, 1, 2, 3};						/* 边界 */
	Point pt[3];
	Point *p = pt;
	auto max = 3;

	for (int i = 0;i < 3;i ++)
	{
		auto index = ToolFunc::calcRandom(0, max);	/* 选择的边界 */
		auto temp = b[max];							/* 选中的与最后一个调换 */
		b[max] = b[index];
		b[index] = temp;

		if (0 == border[b[max]].axis)
		{
			p->x = border[b[max]].value + _owner->getPositionX();
			p->y = ToolFunc::calcRandom(0, border[b[max]].range) + m_fHeight;
		}
		else
		{
			p->y = border[b[max]].value + m_fHeight;
			p->x = ToolFunc::calcRandom(border[b[max - 1]].range, border[b[max]].range) + _owner->getPositionX();
		}
		max --;										/* 选择范围减1，最后一个不再选取 */
		p ++;
	}

	memcpy(ptSelected, pt, sizeof(pt));
}