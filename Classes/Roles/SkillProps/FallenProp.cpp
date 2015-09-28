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
** ���ܣ�		���÷��е�����Ӫ���˺�����
** ���������	Role *owner: �����ͷ���
**				const std::string& strImg: ��Դͼ
**				FlightPropInfo propInfo: ��������
** ����ֵ��		
** �޸ļ�¼��	
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
** ���ܣ�		�����ƶ���������ײ���
** ���������	float duration: �����ƶ�ʱ��
**				Point ptMoveBy: �ƶ�����
** ����ֵ��		��
** �޸ļ�¼��	
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
** ���ܣ�		��ײ���
** ���������	float dt: ��ʱ���ٵ�ʱ��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void FallenProp::PropCollisionDetective(float dt)
{
	if (NULL == _owner)												/* ��ʩ����������δ����ʩ���� */
	{
		releaseCallBack();
		return;
	}

	auto ownerInfo = _owner->getRoleInfo();
	if (RoleStatus_Death == ownerInfo.status)						/* ʩ�������� */
	{
		releaseCallBack();
		return;
	}

	bool bHit = false;
	auto roles = UserData::getInstance()->getRoles();
	auto ptLoc = Point(this->getPositionX(), _fPropYasix);			/* ʵ������ */
	this->setLocalZOrder(_owner->getLocalZOrder());

	for(unsigned int index = 0;index < roles.size();index ++)		/* ���˽�ɫ������ȡ */
	{
		auto role = (Role *)roles[index];
		auto info = role->getRoleInfo();

		if ((RoleStatus_Invincible == info.status) || (ownerInfo.camp == info.camp) ||
			(role->getSceneID() != _owner->getSceneID()))
		{
			continue;												/* �޵С���ͬ������ͬ��Ӫ������������ */
		}

		auto ptOffset = role->getPosition() - ptLoc;
		if ((role->getPosition().getDistance(ptLoc) < m_stPropInfo.skillInfo.yAtkDis) && 
			(abs(role->getPositionY() - this->getPositionY())< m_stPropInfo.skillInfo.xAtkDis))
		{
			bHit = true;											/* ��ײ */
			role->roleHurt(_owner, m_stPropInfo.skillInfo, m_bDown);
		}
	}

	if (true == bHit)
	{
		releaseWithDelay(dt);
	}
}