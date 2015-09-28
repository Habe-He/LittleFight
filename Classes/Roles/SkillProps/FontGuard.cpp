#include "FontGuard.h"

USING_NS_CC;

FontGuard::FontGuard(void)
{
}

FontGuard::~FontGuard(void)
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
FontGuard* FontGuard::create(Role *owner, const std::string& strImg, FlightPropInfo propInfo)
{
	auto sprite = new FontGuard();
	if (sprite && sprite->initWithFile(strImg + "0" + sprite->getImgSuffix()))
	{
		sprite->InitParam(owner, propInfo, strImg);
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

void FontGuard::fontOver()
{
	std::stringstream stream;
	auto strImg = stream.str();

	Animation* animation = Animation::create();  
	for(int i = 4; i < 9; i ++)  
	{
		stream.str("");
		stream << m_strImg << i << getImgSuffix();
		strImg = stream.str();

		animation->addSpriteFrameWithFile(strImg);
	}  
	animation->setDelayPerUnit(m_stPropInfo.dur);  
	animation->setRestoreOriginalFrame(true);  
	auto animate = Animate::create(animation);

	this->runAction(Sequence::create(animate, CallFuncN::create(CC_CALLBACK_1(FontGuard::fontOverCallBack, this)), NULL));
}

/*********************************************************************
** 功能：		动画播放完毕回调
** 输入参数：	Node *who
** 返回值：		无
** 修改记录：	
*********************************************************************/
void FontGuard::fontOverCallBack(Node *who)
{
	who->removeFromParentAndCleanup(true);
}