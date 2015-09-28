#include "FlightProp.h"

USING_NS_CC;

const std::string	strImgSuffix = ".png";			/* 资源图后缀 */

FlightProp::FlightProp()
{
}

FlightProp::~FlightProp(void)
{
}

void FlightProp::runPropCollisionDetective(float dt, Point offset)
{
}

/*********************************************************************
** 功能：		设置标志为倒地
** 输入参数：	bool bDown: true:倒地;false:不倒地
**				float fStay: 延时时间
** 返回值：		无
** 修改记录：	
*********************************************************************/
void FlightProp::setPropFlag(bool bDown, float fStay)
{
	m_bDown = bDown;
	m_fStay = fStay;
}

/*********************************************************************
** 功能：		设置坐标，获取道具高度
** 输入参数：	Point pt: 相对施放者的坐标
** 返回值：		无
** 修改记录：	
*********************************************************************/
void FlightProp::setPropPosition(Point pt)
{
	setPosition(pt + _owner->getPosition());
	m_fHeight = pt.y;
	m_rcBgRegion.origin.y += m_fHeight;
}

/*********************************************************************
** 功能：		销毁
** 输入参数：	无
** 返回值：		无
** 修改记录：	
*********************************************************************/
void FlightProp::releaseCallBack()
{
	this->removeFromParentAndCleanup(true);
}

/*********************************************************************
** 功能：		延时销毁（攻击到敌人时，不马上消失）
** 输入参数：	float dt: 延时销毁的时间
** 返回值：		无
** 修改记录：	
*********************************************************************/
void FlightProp::releaseWithDelay(float dt)
{
// 	if (NULL != this->getActionByTag(iActionSeqTag))
// 	{
// 		this->stopActionByTag(iActionSeqTag);
// 	}

	this->unscheduleUpdate();

	auto delay = DelayTime::create(dt);
	auto prop = CallFuncN::create(CC_CALLBACK_0(FlightProp::releaseCallBack, this));
	auto seq = Sequence::create(delay, prop, NULL);
	this->runAction(seq);
}

/*********************************************************************
** 功能：		初始化成员参数
** 输入参数：	Role *owner: 技能释放者
**				FlightPropInfo propInfo: 道具数据
**				std::string: 设置图片资源路径
** 返回值：		
** 修改记录：	
*********************************************************************/
void FlightProp::InitParam(Role *owner, FlightPropInfo propInfo, std::string strImg)
{
	m_bDown = false;
	m_fStay = 0.05f;
	m_strImg = strImg;
	m_fHeight = 0.0f;
	_owner = owner;

	memset(&m_stPropInfo, 0, sizeof(FlightPropInfo));
	memcpy(&m_stPropInfo, &propInfo, sizeof(FlightPropInfo));

	m_rcBgRegion = UserData::getInstance()->getBgRegion();
}

/*********************************************************************
** 功能：		碰撞检测
** 输入参数：	float dt: 延时销毁的时间
** 返回值：		无
** 修改记录：	
*********************************************************************/
void FlightProp::PropCollisionDetective(float dt)
{
	if (NULL == _owner)												/* 无施放者死亡或未设置施放者 */
	{
		releaseCallBack();
		return;
	}
		
	auto roles = UserData::getInstance()->getRoles();
	auto rcA = this->getBoundingBox();
	auto ownerInfo = _owner->getRoleInfo();
	if (RoleStatus_Death == ownerInfo.status)						/* 施放者死亡 */
	{
		releaseCallBack();
		return;
	}

	bool bHit = false;
	auto ptLoc = Point(this->getPositionX(), this->getPositionY() - m_fHeight);/* 实际坐标需扣除高度 */
	this->setLocalZOrder(_owner->getLocalZOrder());

	for(unsigned int index = 0;index < roles.size();index ++)		/* 敌人角色遍历获取 */
	{
		auto role = (Role *)roles[index];
		auto info = role->getRoleInfo();

		if ((RoleStatus_Invincible == info.status) || (RoleStatus_Death == info.status) || 
			(ownerInfo.camp == info.camp) || (_owner->getSceneID() != role->getSceneID()))
		{
			continue;												/* 无敌、同阵营、死亡或是自身不处理 */
		}

		auto rcB = Rect(role->getPositionX() - 10, role->getPositionY() + 20, 20, 40); /* 有效区域 */

		if (true == rcB.intersectsRect(rcA))						/* 碰撞 */
		{
			auto ptOffset = role->getPosition() - ptLoc;
			
			if (m_stPropInfo.skillInfo.yAtkDis >= abs(ptOffset.y))	/* 动作有效范围判断 */
			{
				bHit = true;
				role->roleHurt(_owner, m_stPropInfo.skillInfo, m_bDown);
			}
		}
	}

	if (true == bHit)
	{
		releaseWithDelay(dt);
	}
}

/*********************************************************************
** 功能：		获取资源图名称后缀
** 输入参数：	无
** 返回值：		无
** 修改记录：	
*********************************************************************/
std::string	FlightProp::getImgSuffix()
{
	return strImgSuffix;
}

/*********************************************************************
** 功能：		图片动画
** 输入参数：	无:
** 返回值：		无
** 修改记录：	
*********************************************************************/
void FlightProp::imgAnimation()
{
	if (1 >= m_stPropInfo.num)
	{
		return;
	}

	std::stringstream stream;
	auto strImg = stream.str();

	Animation* animation = Animation::create();  
	for(int i = 0; i < m_stPropInfo.num; i ++)  
	{
		stream.str("");
		stream << m_strImg << i << strImgSuffix;
		strImg = stream.str();

		animation->addSpriteFrameWithFile(strImg);
	}  
	animation->setDelayPerUnit(m_stPropInfo.dur);  
	animation->setRestoreOriginalFrame(true);
	animation->setLoops(-1);
	auto animate = Animate::create(animation);
	this->runAction(animate);
}