#include "FightPoints.h"
#include "Scene/MainScene.h"

#include "SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"
#include "PointInfo.h"
#include "NewComer/NewComer.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;

enum PointButton
{
	Point_Com = 0,						/* 普通关卡 */
	Point_Elite,						/* 精英关卡 */
	Point_Close,						/* 关闭 */
	Point_Max
};

enum FPzOrderSign
{
	FPzOrder_UI = 0,
	FPzOrder_Notice,
	FPzOrder_Max
};

FightPoints::FightPoints(void)
	: _scrollViewBattle(NULL)
	, _mode(PointModel_Normal)
{
}

FightPoints::~FightPoints(void)
{
}

Scene* FightPoints::scene()
{
	auto sc = Scene::create();
	auto layer = FightPoints::create();
	sc->addChild(layer);
	return sc;
}

bool FightPoints::init()
{
	if ( false == Layer::init() )
	{
		return false;
	}

	loadUI();
	changeBattleSign((BattleSign)UserData::getInstance()->getBattleID());

	NewComer *comer = NULL;
	if (false == NewComer::isGuideDone(1000))					/* 引导ID为0，且未完成 */
	{
		if (5 == NewComer::getCurGuideStep())					/* 第6步骤 */
		{
			NewComer::setCurGuideStep();
		}
		comer = NewComer::create(_scrollViewBattle, 1000, 6);	/* 引导点击武将 */
	}
	else if (false == NewComer::isGuideDone(1001))				/* 引导ID为1，且未完成 */
	{
		if (1 == NewComer::getCurGuideStep())
		{
			NewComer::setCurGuideStep();
		}
		comer = NewComer::create(_scrollViewBattle, 1001, 2);
	}
	else if (false == NewComer::isGuideDone(1002))
	{
		if (5 == NewComer::getCurGuideStep())					/* 第6步骤 */
		{
			NewComer::setCurGuideStep();
		}
		comer = NewComer::create(_scrollViewBattle, 1002, 6);
	}
	else if (false == NewComer::isGuideDone(1003))
	{
		if (3 == NewComer::getCurGuideStep())					/* 第4步骤 */
		{
			NewComer::setCurGuideStep();
		}
		comer = NewComer::create(_scrollViewBattle, 1003, 4);
	}
	else if (false == NewComer::isGuideDone(1004))
	{
		if (7 == NewComer::getCurGuideStep())					/* 第8步骤 */
		{
			NewComer::setCurGuideStep();
		}
		auto comer = NewComer::create(_scrollViewBattle, 1004, 8);
	}
	else
	{
	}
	
	return true;
}

/*********************************************************************
** 功能：		加载UI
** 输入参数：	无
** 返回值：		无
** 修改记录：	
*********************************************************************/
void FightPoints::loadUI()
{
	FontChina::getInstance()->initStringXml();

	_UIWidget = GUIReader::getInstance()->widgetFromJsonFile("UI/All/CustomsPass.ExportJson");
	this->addChild(_UIWidget, FPzOrder_UI);
	
	/* 关闭按钮 */
	auto closeButton = dynamic_cast<Button*>(Helper::seekWidgetByName(_UIWidget, "Button_Close"));
	closeButton->addTouchEventListener(this, toucheventselector(FightPoints::PointButtonClick));
	closeButton->setTag(Point_Close);

	/* 普通关卡 */
	_btnCom = dynamic_cast<Button*>(Helper::seekWidgetByName(_UIWidget, "Button_Com"));
	_btnCom->addTouchEventListener(this, toucheventselector(FightPoints::PointButtonClick));
	_btnCom->setTag(Point_Com);

	/* 精英关卡 */
	_btnElite = dynamic_cast<Button*>(Helper::seekWidgetByName(_UIWidget, "Button_Elite"));
	_btnElite->addTouchEventListener(this, toucheventselector(FightPoints::PointButtonClick));
	_btnElite->setTag(Point_Elite);

	/* 时代之末按钮 */
	_btnBattle[Battle_One] = dynamic_cast<Button*>(Helper::seekWidgetByName(_UIWidget, "Button_25"));
	_btnBattle[Battle_One]->addTouchEventListener(this, toucheventselector(FightPoints::BattleButtonClick));
	_btnBattle[Battle_One]->setTag(Battle_One);

	/* 三家分晋关卡 */
	_btnBattle[Battle_Two] = dynamic_cast<Button*>(Helper::seekWidgetByName(_UIWidget, "Button_27"));
	_btnBattle[Battle_Two]->addTouchEventListener(this, toucheventselector(FightPoints::BattleButtonClick));
	_btnBattle[Battle_Two]->setTag(Battle_Two);

	/* 变法破立关卡 */
	_btnBattle[Battle_Three] = dynamic_cast<Button*>(Helper::seekWidgetByName(_UIWidget, "Button_28"));
	_btnBattle[Battle_Three]->addTouchEventListener(this, toucheventselector(FightPoints::BattleButtonClick));
	_btnBattle[Battle_Three]->setTag(Battle_Three);

	auto panelGoods = dynamic_cast<Layout *>(Helper::seekWidgetByName(_UIWidget, "Panel_38"));
	for (int index = 0;index < 8;index ++)
	{
		auto strImg = __String::createWithFormat("Image_%d", index + 1);
		_imgGoods[index] = dynamic_cast<ImageView *>(Helper::seekWidgetByName(panelGoods, strImg->getCString()));
		_imgGoods[index]->setVisible(false);
	}
}

/*********************************************************************
** 功能：		加载关卡按钮
** 输入参数：	PointModel diff：关卡难度
** 返回值：		无
** 修改记录：	
*********************************************************************/
void FightPoints::loadPointsInfo(PointMode diff)
{
	if (PointModel_Hard == diff)
	{
		auto temp = getPointPassInfo(PointModel_Normal);
		if ((int)temp.size() < (_battle + 1) * PointsPerBattle)
		{
			auto notice = PromptBox::getInstance(FontChina::getInstance()->getComString("ElitePoint")->getCString());
			notice->setFade();
			this->addChild(notice, FPzOrder_Notice);
			UserData::getInstance()->setFightDifficulty(0);
			return;													/* 本大关未全通过，不可开启精英关卡 */
		}

		_btnCom->setBrightStyle(BrightStyle::BRIGHT_NORMAL);
		_btnElite->setBrightStyle(BrightStyle::BRIGHT_HIGHLIGHT);
	}
	else
	{
		_btnCom->setBrightStyle(BrightStyle::BRIGHT_HIGHLIGHT);
		_btnElite->setBrightStyle(BrightStyle::BRIGHT_NORMAL);
	}

	if (NULL == _scrollViewBattle)
	{
		return;
	}

	auto customsPass = getPointPassInfo(diff);
	auto cellInfo = DataManager::getInstance()->localPointCellInfoVector();

	for (int index = _battle * PointsPerBattle;index < (_battle + 1) * PointsPerBattle;index ++)
	{
		auto node = _scrollViewBattle->getChildByTag(index);
		if (NULL != node)
		{
			_scrollViewBattle->removeChildByTag(index);				/* 移除之前的按钮/图片 */
		}

		if (index <= (int)customsPass.size())						/* 关卡已开启 */
		{
 			CellInfo info = {0};
			if (customsPass.size() == index)
			{
				info.station = index + PointIDStart * (diff + 1);
				info.stars = 0;
				info.model = diff;
				info.isOn = true;
			}
			else
			{
				auto pass = customsPass[index];
				info.station = pass.customsPassID;
				info.stars = pass.customsPassStarCount;
				info.model = diff;
				info.isOn = true;
			}
			auto cell = PointCell::create(info, _battle);
			cell->setPosition(cellInfo[index].xLoc, cellInfo[index].yLoc);
			_scrollViewBattle->addChild(cell, 1, index);
			cell->addBtnTouchEvent(this, toucheventselector(FightPoints::CellButtonClick));
		}
		else
		{
			CellInfo info = {index + PointIDStart * (diff + 1), 0, diff, false};
			auto cell = PointCell::create(info, _battle);
			cell->setPosition(cellInfo[index].xLoc, cellInfo[index].yLoc);
			_scrollViewBattle->addChild(cell, 1, index);
		}
	}
}

void FightPoints::PointButtonClick(Ref* pSender, TouchEventType type)
{
	if ( TouchEventType::TOUCH_EVENT_ENDED == type )
	{
		ToolFunc::playEffectFile(Click);

		auto btn = (Button*)pSender;
		auto tag = (PointButton)btn->getTag();

		switch (tag)
		{
		case Point_Com:
			if (PointModel_Normal != _mode)
			{
				UserData::getInstance()->setBattleSVPercent(0.0f);
				UserData::getInstance()->setFightDifficulty(0);
			}
			loadPointsInfo(PointModel_Normal);
			break;
		case Point_Elite:
			if (PointModel_Hard != _mode)
			{
				UserData::getInstance()->setBattleSVPercent(0.0f);
				UserData::getInstance()->setFightDifficulty(1);
			}
			loadPointsInfo(PointModel_Hard);
			break;
		case Point_Close:
			{
				removeGuide();
				Director::getInstance()->replaceScene(MainScene::scene());
			}
			break;
		}
	}
}

void FightPoints::BattleButtonClick(Ref* pSender, TouchEventType type)
{
	if ( TouchEventType::TOUCH_EVENT_ENDED == type )
	{
		ToolFunc::playEffectFile(Click);

		auto btn = (Button*)pSender;
		auto tag = (BattleSign)btn->getTag();
		UserData::getInstance()->setBattleSVPercent(0);				/* 设置滚动层进度 */
		UserData::getInstance()->setFightDifficulty(0);
		changeBattleSign(tag);
	}
}

/* 关卡的回调 */
void FightPoints::CellButtonClick(Ref* pSender, TouchEventType type)
{
	if ( TouchEventType::TOUCH_EVENT_ENDED == type )
	{
		ToolFunc::playEffectFile(Click);

		auto btn = (Button*)pSender;
		auto cell = (PointCell *)btn->getParent();
		auto info = cell->getCellInfo();
		
		auto cpID = UserData::getInstance()->getNewcomerGuide();
		auto high = cpID >> 16;										/* 完成标记 */
		auto low = cpID & 0x00FFFF;									/* 引导ID */

		if (0 == high)												/* 当前正在执行的引导low未完成 */
		{
			auto step = NewComer::getCurGuideStep();				/* 获取当前执行步骤 */
			if (((6 == step) && (1001 == info.station)) ||
				((2 == step) && (1002 == info.station)) ||
				((6 == step) && (1003 == info.station)) ||
				((4 == step) && (1004 == info.station)) ||
				((8 == step) && (1005 == info.station)))
			{
				auto cpID = NewComer::getCurGuideID();
				cpID = cpID | 0x010000;								/* 完成ID为0的引导 */
				NewComer::setCurGuideID(cpID);
				NewComer::setCurGuideStep(0);						/* 步骤ID重置 */
			}
		}

		auto inner = _scrollViewBattle->getInnerContainer();
		auto pt1 = inner->getPosition();
		auto ptLoc = cell->getPosition() + pt1 + _scrollViewBattle->getPosition();
		int point = info.station - (UserData::getInstance()->getFightDifficulty() + 1) * PointIDStart;
		this->addChild(PointInfo::create(ptLoc, point, info.stars));
		UserData::getInstance()->setPointID(point);
		UserData::getInstance()->setCurrentPointStar(info.stars);

		auto innerSize = _scrollViewBattle->getInnerContainerSize();
		auto frameSize = _scrollViewBattle->getContentSize();
		UserData::getInstance()->setBattleSVPercent((0 - pt1.x) *100.0f /(innerSize.width - frameSize.width));	/* 设置滚动层进度 */

		showGoods(point);
	}
}

/*********************************************************************
** 功能：		根据难度选择获取关卡通关信息
** 输入参数：	PointModel diff：难度
** 返回值：		无
** 修改记录：	
*********************************************************************/
std::vector<CustomsPassRecvStruct > FightPoints::getPointPassInfo(PointMode diff)
{
	DataManager::getInstance()->isGetCustomsPass(diff);				/* 普攻级ID以1000开始，精英级2000开始 */
	return DataManager::getInstance()->interCustomsPassVector();
}

void FightPoints::changeBattleSign(BattleSign sign)
{
	_battle = sign;
	UserData::getInstance()->setBattleID(_battle);

	for (int index = Battle_One;index < Battle_Max;index++)
	{
		auto strName = __String::createWithFormat("ScrollView_%d", index + 1);
		auto svBattle = dynamic_cast<ui::ScrollView *>(Helper::seekWidgetByName(_UIWidget, strName->getCString()));

		auto localZorder = 0;
		if (index == _battle)
		{
			localZorder = 3;
			_scrollViewBattle = svBattle;
		}

		svBattle->setLocalZOrder(localZorder); 
		svBattle->setVisible(true);
		svBattle->setDirection(SCROLLVIEW_DIR_HORIZONTAL);

		_btnBattle[index]->setBrightStyle(BrightStyle::BRIGHT_NORMAL);
	}
	_btnBattle[_battle]->setBrightStyle(BrightStyle::BRIGHT_HIGHLIGHT);

	_mode = (PointMode)UserData::getInstance()->getFightDifficulty();/* 之前是普通模式 */
	if (PointModel_Normal == _mode)
	{
		PointButtonClick(_btnCom, TouchEventType::TOUCH_EVENT_ENDED);
	}
	else
	{
		PointButtonClick(_btnElite, TouchEventType::TOUCH_EVENT_ENDED);
	}

	auto offset = UserData::getInstance()->getBattleSVPercent();
	_scrollViewBattle->scrollToPercentHorizontal(offset, 0.1f, false);
}

/* 取消关卡物品显示 */
void FightPoints::removeGoods()
{
	for (int index = 0;index < 8;index ++)
	{
		if (NULL != _imgGoods[index])
		{
			_imgGoods[index]->removeAllChildrenWithCleanup(true);
			_imgGoods[index]->setVisible(false);
		}
	}
}

void FightPoints::showGoods(int sign)
{
	DataManager::getInstance()->checkPointDataParser(UserData::getInstance()->getFightDifficulty());
	auto pointInfo = DataManager::getInstance()->localCheckPointVector();
	auto info = pointInfo[sign];								/* 关卡信息 */

	removeGoods();

	int goodsIndex = 0;

	//获得物品
	auto general = DataManager::getInstance()->localGeneralProptyVector();/* 所有武将数据 */
	if (general.size() == 0)
	{
		DataManager::getInstance()->generalDataParser();
		general = DataManager::getInstance()->localGeneralProptyVector();
	}

	for (int index = 0;index < info.cThingNum;index ++)
	{
		if (93001 > info.cThing[index].pID)							/* 武将碎片 */
		{
			auto gene = general[info.cThing[index].pID - 10001];
			auto str = __String::createWithFormat("%s.png", gene.chinaSmallName);
			_imgGoods[goodsIndex]->loadTexture(str->getCString(), TextureResType::UI_TEX_TYPE_PLIST);
			_imgGoods[goodsIndex]->setScale(49.0f / 95.0f);
		}
		else
		{
			auto str = __String::createWithFormat("%d.png", info.cThing[index].pID);
			_imgGoods[goodsIndex]->loadTexture(str->getCString(), TextureResType::UI_TEX_TYPE_PLIST);
			_imgGoods[goodsIndex]->setScale(49.0f / 95.0f);
		}
		_imgGoods[goodsIndex]->setVisible(true);
		goodsIndex ++;
	}

	if (0 != info.cBox.pID)											/* 宝箱 */
	{
		auto str = __String::createWithFormat("%d.png", info.cBox.pID);
		_imgGoods[goodsIndex]->loadTexture(str->getCString(), TextureResType::UI_TEX_TYPE_PLIST);
		_imgGoods[goodsIndex]->setScale(49.0f / 95.0f);
		_imgGoods[goodsIndex]->setVisible(true);
		goodsIndex ++;
	}

	if (0 < info.cSoul)												/* 灵魂石 */
	{
		_imgGoods[goodsIndex]->loadTexture("93018.png", TextureResType::UI_TEX_TYPE_PLIST);
		_imgGoods[goodsIndex]->setScale(49.0f / 95.0f);
		_imgGoods[goodsIndex]->setVisible(true);

		auto numLabel = Label::create();
		auto strNum = __String::createWithFormat("%d", info.cSoul);
		numLabel->setString(strNum->getCString());
		numLabel->setSystemFontSize(26);
		numLabel->setPosition(10, 70);
		_imgGoods[goodsIndex]->addChild(numLabel);
		goodsIndex ++;
	}

	if (0 < info.cPill)												/* 培养丹 */
	{
		_imgGoods[goodsIndex]->loadTexture("93019.png", TextureResType::UI_TEX_TYPE_PLIST);
		_imgGoods[goodsIndex]->setScale(49.0f / 95.0f);
		_imgGoods[goodsIndex]->setVisible(true);

		auto numLabel = Label::create();
		auto strNum = __String::createWithFormat("%d", info.cPill);
		numLabel->setString(strNum->getCString());
		numLabel->setSystemFontSize(26);
		numLabel->setPosition(10, 70);
		_imgGoods[goodsIndex]->addChild(numLabel);
		goodsIndex ++;
	}
}

void FightPoints::removeGuide()
{
	auto step = NewComer::getCurGuideStep();
	if (false == NewComer::isGuideDone(1000))					/* 引导ID为0，且未完成 */
	{
		if (6 == step)											/* 第6步骤 */
		{
			NewComer::setCurGuideStep(-1);
		}
	}
	else if (false == NewComer::isGuideDone(1001))				/* 引导ID为1，且未完成 */
	{
		if (0 != step)
		{
			NewComer::setCurGuideStep(-1);
		}
	}
	else if (false == NewComer::isGuideDone(1002))
	{
		if (6 == step)											/* 第6步骤 */
		{
			NewComer::setCurGuideStep(-1);
		}
	}
	else if (false == NewComer::isGuideDone(1003))
	{
		if (4 == step)											/* 第6步骤 */
		{
			NewComer::setCurGuideStep(-1);
		}
	}
	else if (false == NewComer::isGuideDone(1004))
	{
		if (8 == step)											/* 第6步骤 */
		{
			NewComer::setCurGuideStep(-1);
		}
	}
	else
	{
	}
}