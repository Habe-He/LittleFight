#include "EnergyBall.h"

USING_NS_CC;

const float EnergyBallMoveSpeed = 160.0f;		/* �������ƶ��ٶ� */

typedef struct tagBorderSelect
{
	int		range;								/* ��ȡ��ֵ��Χ */
	int		axis;								/* �������,0:����x�� 1:����y�� */
	int		value;								/* ������ֵ */
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
** ���ܣ�		���÷��е�����Ӫ���˺�����
** ���������	Role *owner: �����ͷ���
**				const std::string& strImg: ��Դͼ
**				FlightPropInfo propInfo: ��������
** ����ֵ��		
** �޸ļ�¼��	
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
** ���ܣ�		��������
** ���������	
** ����ֵ��		
** �޸ļ�¼��	
*********************************************************************/
void EnergyBall::energyBallAction()
{
	Rect rc = Rect(0 - m_stPropInfo.skillInfo.xAtkDis / 5, 0 - m_stPropInfo.skillInfo.yAtkDis / 5, 
		m_stPropInfo.skillInfo.xAtkDis / 2.5f, m_stPropInfo.skillInfo.yAtkDis / 2.5f);	/* ����������з�Χ������� */	
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
** ���ܣ�		��ײ���
** ���������	
** ����ֵ��		
** �޸ļ�¼��	
*********************************************************************/
void EnergyBall::PropCollisionDetective()
{
	if (false == m_bCollision)										/* ���������ʱ�� */
	{
		return;
	}

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

	auto roles = UserData::getInstance()->getRoles();
	if (0 == roles.size())											/* û�н�ɫ��Ԥ��ģʽ�� */
	{
		releaseCallBack();
		return;
	}

	if (RoleStatus_Death == m_Role->getRoleInfo().status)			/* ѡ�еĽ�ɫ��������ѡ��ɫ */
	{
		energyBallSearchObject();
	}
	else
	{
		auto ptRole = m_Role->getPosition();
		ptRole.y = ptRole.y + m_fHeight;							/* ����Ŀ���Ϊ��ɫ���� */
		auto ptOffset = ptRole - this->getPosition();
		this->setPosition(this->getPosition() + ptOffset / ptOffset.getLength() * EnergyBallMoveSpeed * 0.4f);
	}

	bool bCollision = false;
	auto rcA = this->getBoundingBox();

	auto rcB = Rect(m_Role->getPositionX() - 10, m_Role->getPositionY() + 20, 20, m_fHeight); /* ��Ч���� */

	if (true == rcB.intersectsRect(rcA))
	{
		bCollision = true;
		auto info = m_Role->getRoleInfo();
		if (ownerInfo.camp == info.camp)						/* �Լ����� */
		{
			m_Role->setRoleHpUp(m_stPropInfo.skillInfo.damage);
		}
		else													/* �Ե��˺� */
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
** ���ܣ�		�������˶���׷���ɫ
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void EnergyBall::energyBallSearchObject()
{
	auto roles = UserData::getInstance()->getRoles();

	auto itr = roles.begin();
	while (itr != roles.end())
	{
		auto role = (Role *)(*itr);
		auto info = role->getRoleInfo();
		if ((RoleStatus_Death == info.status) || (m_iSceneID != role->getSceneID()))/* ��������ͬ���� */
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
	else															/* Ԥ��ģʽ������ */
	{
		this->removeFromParentAndCleanup(true);
	}
}

/*********************************************************************
** ���ܣ�		��ָ����Χ��ѡȡ���Ƶ�
** ���������	Rect rc: ָ���ķ�Χ
**				Point *ptSelected: ѡȡ��3��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void EnergyBall::getEnergyBallMovePoint(Rect rc, Point *ptSelected)
{
	BorderSelect border[4] = {
		{ (int)rc.size.height, 0, (int)rc.getMinX()}, { (int)rc.size.width, 1, (int)rc.getMaxY()},
		{ (int)rc.size.height, 0, (int)rc.getMaxX()}, { (int)rc.size.width, 1, (int)rc.getMinY()}		
	};

	int b[4] = {0, 1, 2, 3};						/* �߽� */
	Point pt[3];
	Point *p = pt;
	auto max = 3;

	for (int i = 0;i < 3;i ++)
	{
		auto index = ToolFunc::calcRandom(0, max);	/* ѡ��ı߽� */
		auto temp = b[max];							/* ѡ�е������һ������ */
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
		max --;										/* ѡ��Χ��1�����һ������ѡȡ */
		p ++;
	}

	memcpy(ptSelected, pt, sizeof(pt));
}