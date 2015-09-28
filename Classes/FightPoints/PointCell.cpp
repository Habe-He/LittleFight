#include "PointCell.h"
#include "Public/ToolFunc.h"
#include "UserInfo/UserData.h"
#include "PointInfo.h"

USING_NS_CC;
using namespace ui;

const std::string resRoot = "res/FightPoints/";						/* ��Դ·��Ŀ¼ */
const std::string resPoint[PointModel_Max][PointState_Max] = 
{
	{
		resRoot + "ComSp.png",										/* ��ͨ�ؿ�δ����ʱ���� */
		resRoot + "ComBtnN.png",									/* ��ͨ�ؿ���ť */
		resRoot + "ComBtnB.png"										/* ��ͨBoss�ؿ���ť */
	},
	{
		resRoot + "EliteSp.png",									/* ��Ӣ�ؿ�δ����ʱ���� */
		resRoot + "EliteBtnN.png",									/* ��Ӣ�ؿ���ť */
		resRoot + "EliteBtnB.png"									/* ��ӢBoss�ؿ���ť */
	}
};
const std::string spStarL = resRoot + "StarL.png";					/* ������ */
const std::string spStarD = resRoot + "StarD.png";					/* ������ */
const std::string spFlag = resRoot + "Flag";						/* �ؿ�ͨ������ */
const std::string spAureole = resRoot + "Aureole";					/* Boss�ؿ��⻷ */

const Point	ptStar[maxStarNum] = {									/* ��λ�� */
	Point(-23.0f, -18),
	Point(0.0f, -23.0f),
	Point(23.0f, -18.0f)
};

PointCell::PointCell(void)
	: _spCom(NULL)
	, _spFlag(NULL)
	, _btnCell(NULL)
	, _spAureole(NULL)
	, _battle(0)
{
}

PointCell::~PointCell(void)
{
}

PointCell* PointCell::create(CellInfo info, BattleSign sign)
{
	auto * ret = new PointCell();
	if (ret && ret->init(info, sign))
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

bool PointCell::init(CellInfo info, BattleSign sign)
{
	_battle = sign;
	memset(&_cell, 0, sizeof(CellInfo));
	memcpy(&_cell, &info, sizeof(CellInfo));

	bool bBossFlag = false;
	if (0 == (_cell.station + 1) % 5)								/* boss�ؿ� */
	{
		loadAureoleAnimate();
		bBossFlag = true;
	}

	if (false == _cell.isOn)										/* �ؿ���δ���� */
	{
		_spCom = Sprite::create(resPoint[_cell.model][PointState_Off]);
		this->addChild(_spCom);
		return true;
	}

	_btnCell = Button::create();
	_btnCell->setPosition(Point::ZERO);
	_btnCell->setAnchorPoint(Point::ANCHOR_MIDDLE);
	_btnCell->setTag(_cell.station);
	this->addChild(_btnCell, PointZorder_Button);
	//_btnCell->addTouchEventListener(this, toucheventselector(PointCell::btnPoints));

	if (0 < _cell.stars)											/* ����ͨ����¼ */
	{
		loadFlagAnimate();

		for (int index = 0;index < maxStarNum;index++)				/* �Ǽ���ʾ */
		{
			auto star = (index < _cell.stars) ? spStarL : spStarD;
			auto spStar = Sprite::create(star);
			spStar->setPosition(ptStar[index]);
			this->addChild(spStar, PointZorder_Button);
		}
	}

	auto state = (true == bBossFlag) ? PointState_Boss : PointState_Normal;
	_btnCell->loadTextureNormal(resPoint[_cell.model][state]);

	return true;
}

/*********************************************************************
** ���ܣ�		����button�ص��¼�
** ���������	Ref* target: 
**				SEL_TouchEvent touchevent: ��ӵ��¼�
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void PointCell::addBtnTouchEvent(Ref* target, SEL_TouchEvent touchevent)
{
	if (NULL != _btnCell)
	{
		_btnCell->addTouchEventListener(target, touchevent);
	}
}

void PointCell::btnPoints(Ref* pSender, TouchEventType type)
{
// 	if (type == TOUCH_EVENT_ENDED)
// 	{
// 		auto pst = (Button*)pSender;
// 		auto tag = pst->getTag();
// 
// 		int point = tag - (UserData::getInstance()->getFightDifficulty() + 1) * PointIDStart;
// 		Director::getInstance()->getRunningScene()->addChild(PointInfo::create(point, _cell.stars));
// 		UserData::getInstance()->setPointID(point);
// 		UserData::getInstance()->setCurrentPointStar(_cell.stars);
// 
// 		auto sv = (ui::ScrollView*)this->getParent()->getParent();
// 		UserData::getInstance()->setBattleSVPercent(sv->getPositionPercent().x * 100);	/* ���ù�������� */
// 	}
}

/*********************************************************************
** ���ܣ�		����Ʈ�ﶯ��
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void PointCell::loadFlagAnimate()
{
	_spFlag = Sprite::create();
	_spFlag->setAnchorPoint(Point(0.75f, 0.08f));
	this->addChild(_spFlag, PointZorder_Flag);

	auto animation = Animation::create();

// 	auto random = ToolFunc::calcRandom(3, 6);
// 	for (int index = 0;index < random;index++)
// 	{
// 		auto str1 = __String::createWithFormat("%s0.png", flag.c_str());
// 		animation->addSpriteFrameWithFile(str1->getCString());
// 	}
	for (int index = 0;index < 4;index ++)
	{
		auto str = __String::createWithFormat("%s%d%d.png", spFlag.c_str(), _battle, index);
		animation->addSpriteFrameWithFile(str->getCString());
	}
	
	animation->setDelayPerUnit(ToolFunc::calcRandom(15, 30) * 1.0f / 100);  
	animation->setRestoreOriginalFrame(true);
	animation->setLoops(-1);
	auto animate = Animate::create(animation);
	
	_spFlag->runAction(animate);
}

/*********************************************************************
** ���ܣ�		Boss�ؿ��⻷����
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void PointCell::loadAureoleAnimate()
{
	auto animation = Animation::create();

	for (int index = 0;index < 12;index ++)
	{
		auto str = __String::createWithFormat("%s%d.png", spAureole.c_str(), index);
		animation->addSpriteFrameWithFile(str->getCString());
	}

	animation->setDelayPerUnit(ToolFunc::calcRandom(15, 30) * 1.0f / 100);  
	animation->setRestoreOriginalFrame(true);
	animation->setLoops(-1);
	auto animate = Animate::create(animation);

	_spAureole = Sprite::create();
	_spAureole->runAction(animate);
	this->addChild(_spAureole, PointZorder_Effect);
}

CellInfo PointCell::getCellInfo()
{
	return _cell;
}