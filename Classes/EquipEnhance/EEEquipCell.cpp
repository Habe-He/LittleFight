#include "EEEquipCell.h"

USING_NS_CC;

const std::string strEEEquipCellRoot = "res/EquipEnhance/";
const std::string strEEEquipCellBg = "EquipCellBg.png";
const std::string strEEEquipCellLight = "EquipCellLight.png";

EEEquipCell::EEEquipCell(void)
	: _bSelectFlag(false)
	, _realExp(0)
{
}

EEEquipCell::~EEEquipCell(void)
{
}

EEEquipCell* EEEquipCell::Create(EquipProptyStruct stInfo)
{
	auto ret = new EEEquipCell;
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

bool EEEquipCell::init(EquipProptyStruct stInfo)
{
	memset(&_stInfo, 0, sizeof(EquipProptyStruct));
	memcpy(&_stInfo, &stInfo, sizeof(EquipProptyStruct));

	if (0 == stInfo.eID)
	{
		return true;
	}

//  auto spBg = Sprite::create(strEEEquipCellRoot + strEEEquipCellBg);
//  this->addChild(spBg);
 
 	auto strName = __String::createWithFormat("%d.png", stInfo.eID);
 	auto spEquip = Sprite::createWithSpriteFrameName(strName->getCString());
 	this->addChild(spEquip);

	spEquip->setScale(98.0f / 120.0f);
	spEquip->setPosition(Point::ZERO);
	spEquip->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
 
 	_spLight = Sprite::create(strEEEquipCellRoot + strEEEquipCellLight);
 	this->addChild(_spLight);
	_spLight->setVisible(_bSelectFlag);
	_spLight->setScale(98.0f / 81.0f);
	_spLight->setPosition(Point::ZERO);
	_spLight->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);

	auto strLevel = __String::createWithFormat("Lv: %d\nExp: %d", stInfo.eLevel, stInfo.eExp);
	auto labelLevel = Label::createWithSystemFont(strLevel->getCString(), "Arial", 13);
	labelLevel->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	labelLevel->setPosition(Point(5.0f, 5.0f));
	labelLevel->setColor(Color3B::WHITE);
	this->addChild(labelLevel);
 
 	this->setTag(stInfo.ePKID);
	setContentSize(Size(98.0f, 98.0f));

	return true;
}

/* 转换选中与非选中状态, 返回转换后的状态 */
bool EEEquipCell::changeStatus()
{
	_bSelectFlag = !_bSelectFlag;
	_spLight->setVisible(_bSelectFlag);

	return _bSelectFlag;
}

EquipProptyStruct EEEquipCell::getEquipCellInfo()
{
	return _stInfo;
}