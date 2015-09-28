#include "SuperImage.h"
#include "Public/ToolFunc.h"

USING_NS_CC;

const float RoleHealthDuration = 2.5f;			/* hp显示检测频率 */

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
** 功能：		创建裁剪模板图
** 输入参数：	std::string strStencil: 遮罩
**				std::string strClip: 原图
**				float scale: 显示倍率
** 返回值：		无
** 修改记录：	
*********************************************************************/
void SuperImage::createClipper(std::string strStencil, std::string strClip, float scale)
{
	auto clip = ClippingNode::create();
	auto sp = Sprite::create(strStencil);
	clip->setStencil(sp);							/* 设置裁剪模板 */
	clip->setAlphaThreshold(0.05f);					/* 设置绘制底板的Alpha值 */

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
** 功能：		进度条
** 输入参数：	std::string strStencil: 遮罩
**				std::string strFrame: 边框
**				float scale: 显示倍率
** 返回值：		无
** 修改记录：	
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
** 功能：		切换角色
** 输入参数：	Role *role: 切换的角色
** 返回值：		无
** 修改记录：	
*********************************************************************/
void SuperImage::resetOwner(Role *role)
{
	_owner = role;
}

/*********************************************************************
** 功能：		cd设置
** 输入参数：	float dt: cd
** 返回值：		无
** 修改记录：	
*********************************************************************/
void SuperImage::setProgressDuration(float dt)
{
	_cd = dt;
}

/*********************************************************************
** 功能：		CD进度显示
** 输入参数：	float percent: 进度范围
**				int times: 次数(0次表示无限重复)
** 返回值：		无
** 修改记录：	
*********************************************************************/
void SuperImage::runSpriteProgressToRadial(float percent, int times)
{
	if ((0 < _cd) && (NULL != _proTimer))
	{
		auto fromTo = ProgressFromTo::create(_cd, percent, 0);

		if (NULL == _label)
		{
			_label = Label::create();								/* cd值显示 */
			auto s = this->getContentSize();
			_label->setSystemFontSize(18.0f);
			_label->setColor(Color3B::YELLOW);
			_label->setPosition(Point(s.width / 2, s.height / 2));
			this->addChild(_label, 2);
		}		

		auto btn = (ui::Button*)this->getParent();					/* 进入cd状态，按钮不可用 */
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
	if ((NULL != _label) && (NULL != _proTimer))					/* 显示技能cd */
	{
		showActionCD();
		return;
	}

	if (NULL == _owner)												/* 无角色 */
	{
		return;
	}

	auto info = _owner->getRoleInfo();
	if (0 == info.panel.hpCurrent)									/* 角色死亡 */
	{
		if (false == _bGrayFlag)
		{
			ToolFunc::graySprite((Sprite*)_spClip);					/* 置灰 */
			_bGrayFlag = true;
		}
	}

	if (RoleMode_Companion == info.mode)							/* 小伙伴 */
	{
		if (NULL == _proTimer)
		{
			this->removeFromParentAndCleanup(true);					/* 未定义hp显示，销毁 */
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

	if (RoleMode_Main == info.mode)									/* 主将 */
	{
		if ((NULL == _mainHp) || (NULL == _subHp))
		{
			this->removeFromParentAndCleanup(true);					/* 未定义hp显示，销毁 */
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