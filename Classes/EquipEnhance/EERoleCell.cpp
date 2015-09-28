#include "EERoleCell.h"

USING_NS_CC;

const std::string strEERoleCellRoot = "res/EquipEnhance/";
const std::string strEERoleCellBg = "RoleCellBg.png";
const std::string strEERoleCellFrame = "RoleCellFrame.png";

EERoleCell::EERoleCell(void)
{
}

EERoleCell::~EERoleCell(void)
{
}

EERoleCell*	EERoleCell::Create(GeneralProptyStruct stInfo)
{
	auto ret = new EERoleCell();
	if (ret && ret->init(stInfo))
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}

	return ret;
}

bool EERoleCell::init(GeneralProptyStruct stInfo)
{
	memset(&_stInfo, 0, sizeof(GeneralProptyStruct));
	memcpy(&_stInfo, &stInfo, sizeof(GeneralProptyStruct));

// 	auto spBg = Sprite::create(strEERoleCellRoot + strEERoleCellBg);
// 	this->addChild(spBg);

 	auto strPhoto = __String::createWithFormat("%s.png", stInfo.chinaSmallName);
 	auto spRole = Sprite::createWithSpriteFrameName(strPhoto->getCString());
 	this->addChild(spRole);
	spRole->setPosition(Point::ZERO);
 	setContentSize(spRole->getContentSize());
 	spRole->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);

// 	auto spFrame = Sprite::create(strEERoleCellRoot + strEERoleCellFrame);
// 	this->addChild(spFrame);
// 	setContentSize(spFrame->getContentSize());

	this->setTag(stInfo.PKID);

	return true;
}

GeneralProptyStruct EERoleCell::getRoleCellInfo()
{
	return _stInfo;
}