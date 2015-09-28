#include "SuperImage.h"
#include "Public/ToolFunc.h"

USING_NS_CC;

const float RoleHealthDuration = 2.5f;			/* hp��ʾ���Ƶ�� */

SuperImage::SuperImage(void)
	: _owner(NULL)
	, _mainHp(NULL)
	, _subHp(NULL)
	, _proTimer(NULL)
	, _spClip(NULL)
	, _cd(0)
	, _label(NULL)
	, _bGrayFlag(false)
{
}

SuperImage::~SuperImage(void)
{
}

SuperImage* SuperImage::Create(SpImgModeSign mode)
{
	auto SI = new SuperImage();
	if ((NULL != SI) && (true == SI->init(mode)))
	{
		SI->autorelease();
	}
	else
	{
		delete SI;
		SI = NULL;
	}

	return SI;
}

bool SuperImage::init(SpImgModeSign mode)
{
	return Node::init();
}

bool SuperImage::init()
{
	return Node::init();
}

/*********************************************************************
** ���ܣ�		�����ü�ģ��ͼ
** ���������	std::string strStencil: ����
**				std::string strClip: ԭͼ
**				float scale: ��ʾ����
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void SuperImage::createClipper(std::string strStencil, std::string strClip, float scale)
{
	auto clip = ClippingNode::create();
	auto sp = Sprite::create(strStencil);
	clip->setStencil(sp);							/* ���òü�ģ�� */
	clip->setAlphaThreshold(0.05f);					/* ���û��Ƶװ��Alphaֵ */

	_spClip = Sprite::createWithSpriteFrameName(strClip + ".png");
	if (NULL != _spClip)
	{
		clip->addChild(_spClip, 0);
	}

	clip->setAnchorPoint(Point::ANCHOR_MIDDLE);
	clip->setPosition(Point::ZERO);
	clip->setScaleX(scale);
	clip->setScaleY(abs(scale));
	this->addChild(clip, 0);

	this->scheduleUpdate();
}

void SuperImage::setProgressBar(cocos2d::ui::LoadingBar *mainHp, cocos2d::ui::LoadingBar *subHp)
{
	_mainHp = mainHp;
	_subHp = subHp;
}

/*********************************************************************
** ���ܣ�		������
** ���������	std::string strStencil: ����
**				std::string strFrame: �߿�
**				float scale: ��ʾ����
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void SuperImage::setProgressBar(std::string strStencil, std::string strFrame, float scale)
{
	if ("" != strFrame)
	{
		auto spFrame = Sprite::create(strFrame);
		spFrame->setAnchorPoint(Point::ANCHOR_MIDDLE);
		spFrame->setPosition(Point::ZERO);
		this->addChild(spFrame, 1);
	}

	auto sp = Sprite::create(strStencil);
	_proTimer = ProgressTimer::create(sp);
	_proTimer->setType(ProgressTimer::Type::RADIAL);
	_proTimer->setPercentage(0);
	_proTimer->setAnchorPoint(Point::ANCHOR_MIDDLE);
	_proTimer->setPosition(Point::ZERO);
	_proTimer->setScaleX(scale);
	_proTimer->setScaleY(abs(scale));
	this->addChild(_proTimer, 2);
}

/*********************************************************************
** ���ܣ�		�л���ɫ
** ���������	Role *role: �л��Ľ�ɫ
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void SuperImage::resetOwner(Role *role)
{
	_owner = role;
}

/*********************************************************************
** ���ܣ�		cd����
** ���������	float dt: cd
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void SuperImage::setProgressDuration(float dt)
{
	_cd = dt;
}

/*********************************************************************
** ���ܣ�		CD������ʾ
** ���������	float percent: ���ȷ�Χ
**				int times: ����(0�α�ʾ�����ظ�)
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void SuperImage::runSpriteProgressToRadial(float percent, int times)
{
	if ((0 < _cd) && (NULL != _proTimer))
	{
		auto fromTo = ProgressFromTo::create(_cd, percent, 0);

		if (NULL == _label)
		{
			_label = Label::create();								/* cdֵ��ʾ */
			auto s = this->getContentSize();
			_label->setSystemFontSize(18.0f);
			_label->setColor(Color3B::YELLOW);
			_label->setPosition(Point(s.width / 2, s.height / 2));
			this->addChild(_label, 2);
		}		

		auto btn = (ui::Button*)this->getParent();					/* ����cd״̬����ť������ */
		if (NULL != btn)
		{
			btn->setTouchEnabled(false);
		}

		if (0 == times)
		{
			_proTimer->runAction(RepeatForever::create(fromTo));
		}
		else
		{
			auto seq = Sequence::create(Repeat::create(fromTo, times), CallFuncN::create(CC_CALLBACK_1(SuperImage::progressCDOver, this)), NULL);
			_proTimer->runAction(seq);
		}
	}
}

void SuperImage::update(float dt)
{
	if ((NULL != _label) && (NULL != _proTimer))					/* ��ʾ����cd */
	{
		showActionCD();
		return;
	}

	if (NULL == _owner)												/* �޽�ɫ */
	{
		return;
	}

	auto info = _owner->getRoleInfo();
	if (0 == info.panel.hpCurrent)									/* ��ɫ���� */
	{
		if (false == _bGrayFlag)
		{
			ToolFunc::graySprite((Sprite*)_spClip);					/* �û� */
			_bGrayFlag = true;
		}
	}

	if (RoleMode_Companion == info.mode)							/* С��� */
	{
		if (NULL == _proTimer)
		{
			this->removeFromParentAndCleanup(true);					/* δ����hp��ʾ������ */
			return;
		}

		auto cur = _proTimer->getPercentage();
		auto per = (0 < info.panel.hpCurrent) ? (info.panel.hpTotal - info.panel.hpCurrent) * 100.0f / info.panel.hpTotal : 100;

		if (cur < per)
		{
			_proTimer->setPercentage(cur + 1);
		}
		
		if (100 == cur)
		{
			this->unscheduleUpdate();
		}
	}

	if (RoleMode_Main == info.mode)									/* ���� */
	{
		if ((NULL == _mainHp) || (NULL == _subHp))
		{
			this->removeFromParentAndCleanup(true);					/* δ����hp��ʾ������ */
			return;
		}
		
		auto cur = _subHp->getPercent();
		if (0 < cur)
		{
			auto per = info.panel.hpCurrent * 100.0f / info.panel.hpTotal;
			per = (0 != per) ? (int)(per + 1) : 0;
			_mainHp->setPercent(per);
			if (cur > per)
			{
				_subHp->setPercent(cur - 1);
			}
		}
		else
		{
			this->unscheduleUpdate();
		}
	}
}

void SuperImage::progressCDOver(Node* who)
{
	auto btn = (ui::Button*)this->getParent();
	if (NULL != btn)
	{
		btn->setTouchEnabled(true);
	}
}

void SuperImage::showActionCD()
{
	if (NULL != _proTimer)
	{
		auto per = _proTimer->getPercentage() * 0.01f * _cd;
		auto str = __String::createWithFormat("%.1f", per);
		if (0 == per)
		{
			str = __String::create("");
		}
		_label->setString(str->getCString());
	}
}