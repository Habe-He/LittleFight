#include "CommonProp.h"

USING_NS_CC;

CommonProp::CommonProp(void)
{
}

CommonProp::~CommonProp(void)
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
CommonProp* CommonProp::create(Role *owner, const std::string& strImg, FlightPropInfo propInfo)
{
	auto sprite = new CommonProp();
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
void CommonProp::runPropCollisionDetective(float duration, Point ptMoveBy)
{
	auto seq = Sequence::create(MoveBy::create(duration, ptMoveBy), 
		CallFuncN::create(CC_CALLBACK_0(CommonProp::skillCallBack, this)), NULL);
	seq->setTag(iActionSeqTag);
	this->runAction(seq);
	this->scheduleUpdate();
	imgAnimation();
}

/* protected: */
void CommonProp::skillCallBack()
{
	this->unscheduleUpdate();
	auto delay = DelayTime::create(m_fStay / 3);
	auto prop = CallFuncN::create(CC_CALLBACK_0(FlightProp::releaseCallBack, this));
	auto seq = Sequence::create(delay, prop, NULL);
	this->runAction(seq);
}

void CommonProp::update(float)
{
	PropCollisionDetective(m_fStay);
}