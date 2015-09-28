#include "CommonProp.h"

USING_NS_CC;

CommonProp::CommonProp(void)
{
}

CommonProp::~CommonProp(void)
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
** ���ܣ�		�����ƶ���������ײ���
** ���������	float duration: �����ƶ�ʱ��
**				Point ptMoveBy: �ƶ�����
** ����ֵ��		��
** �޸ļ�¼��	
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