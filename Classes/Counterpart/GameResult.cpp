#include "GameResult.h"
#include "cocostudio/CocoStudio.h"
#include "Counterpart.h"
#include "Train/Maidan.h"
#include "Equipenhance/EquipEnhance.h"
#include "DataManager/DataManager.h"
#include "AppDelegate.h"
#include "UserInfo/UserData.h"
#include "Public/ToolFunc.h"
#include "PromptBox/PromptBox.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;

const int maxStarNumResult = 3;
const int PointIDStartResult = 1000;
const Point ptStar[maxStarNumResult] = {Point(355, 431), Point(420, 431), Point(485, 431)};

enum PointWinButtons
{
	BtnPointWinExit,												/* �ؿ��˳� */
	BtnPointWinMax
};

enum PointLossButtons
{
	BtnPointLossGeneral,											/* �����佫 */
	BtnPointLossEquip,												/* ����װ�� */
	BtnPointLossDrawoff,											/* �鿨 */
	BtnPointLossPreset,												/* Ԥ�� */
	BtnPointLossExit,												/* �ؿ��˳� */
	BtnPointLossResurrection,										/* ���� */
	BtnPointLossMax
};

GameResult::GameResult(void)
	: _iStarLv(2)
	, _iGameMode(0)
	, _iSchedule(5)
	, _spSchedule(NULL)
	, _btnLife(NULL)
{
}

GameResult::~GameResult(void)
{
}

GameResult* GameResult::create(Result result, int time)
{
	auto ret = new GameResult;
	if (ret && ret->init(result, time))
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

bool GameResult::init(Result result, int time)
{
	if (false == Layer::init())
	{
		return false;
	}

	_iTime = time;
	_iPoint = UserData::getInstance()->getPointID();
	_iDiff = UserData::getInstance()->getFightDifficulty();
	_iGameMode = UserData::getInstance()->getRoleCreateModel();

	result = checkResult(result);
	if (Result_Win == result)
	{
		ResultModeWin();
	}
	else
	{
		ResultModeLoss();
	}

	return true;
}

/* ����ģʽ����ʤ�� */
Result GameResult::checkResult(Result result)
{
	auto mode = (RoleCreMode)_iGameMode;
	if (RoleCreMode_Fighting == mode)
	{
		return result;
	}

	_iDiff = 0;
	if ((RoleCreMode_XueGong2 == mode) && (30 < _iTime))			/* ���ѧ��ģʽ2������ʱ�����30s���ж�Ϊ�ɹ� */
	{
		return Result_Win;
	}

	auto grade = UserData::getInstance()->getJxxg3Grade();
	if ((RoleCreMode_XueGong3 == mode) && (0 < grade))				/* ���ѧ��ģʽ3����������1���ж�Ϊ�ɹ� */
	{
		return Result_Win;
	}

	auto dmg = UserData::getInstance()->getJxxg4Grade();
	if ((RoleCreMode_XueGong4 == mode) && (dmg > 20000))			/* ���ѧ��ģʽ4 */
	{
		return Result_Win;
	}

	return Result_Loss;
}

void GameResult::ResultModeWin()
{
	auto mode = (RoleCreMode)_iGameMode;

	loadPointWin();
	switch (mode)
	{
	case RoleCreMode_Fighting:
		{
			auto cpID = _iPoint + (_iDiff + 1) * PointIDStartResult;
			auto curID = UserData::getInstance()->getNewcomerGuide();
			if (cpID > (curID & 0xFFFF))							/* ͨ��ID���ڱ����ID�������������״�� */
			{
				curID = cpID;
				UserData::getInstance()->setGuideStep(0);
				UserData::getInstance()->savaNewcomerGuide(curID);
			}
		}
		break;
	case RoleCreMode_XueGong1:
		loadGameXG1Win();
		break;
	case RoleCreMode_XueGong2:
		loadGameXG2Win();
		break;
	case RoleCreMode_XueGong3:
		loadGameXG3Win();
		break;
	case RoleCreMode_XueGong4:
		loadGameXG4Win();
		break;
	}
}

void GameResult::ResultModeLoss()
{
	auto mode = (RoleCreMode)_iGameMode;

	loadPointLoss();
	switch (mode)
	{
	case RoleCreMode_Fighting:
		getTeamExpImprove();										/* �������ѧ��buff���� */
		getRoleExpImprove();
		break;
	case RoleCreMode_XueGong1:
	case RoleCreMode_XueGong2:
	case RoleCreMode_XueGong3:
	case RoleCreMode_XueGong4:
		loadGameXGLoss(mode - RoleCreMode_XueGong1);
		break;
	}
}

/* �ؿ�ʤ�� */
void GameResult::loadPointWin()
{
	auto app = (AppDelegate *)(Application::getInstance()); 
	app->showSpot();

	auto rc = Director::getInstance()->getOpenGLView()->getVisibleRect();
	_uiPointWin = GUIReader::getInstance()->widgetFromJsonFile("UI/All/Result_Win.ExportJson");
	_uiPointWin->setPosition(Point(rc.getMaxX(), rc.getMinY()));
	this->addChild(_uiPointWin);

	auto move = MoveTo::create(0.6f, Point::ZERO);
	auto seq = Sequence::create(move, DelayTime::create(0.01f), CallFunc::create(CC_CALLBACK_0(GameResult::winCallBack, this)), NULL);
	_uiPointWin->runAction(seq);
	
	auto btnExit = dynamic_cast<Button*>(Helper::seekWidgetByName(_uiPointWin, "Button_Rewards"));
	btnExit->addTouchEventListener(this, toucheventselector(GameResult::btnPointWin));
	btnExit->setTag(BtnPointWinExit);

	ToolFunc::playBackgroundFile("win");

	for (unsigned int index = 0; index < 4; index++)
	{
		auto strLayer = __String::createWithFormat("Panel_RRole%d", index + 1);
		auto layer = dynamic_cast<Layout*>(Helper::seekWidgetByName(_uiPointWin, strLayer->getCString()));
		layer->setVisible(false);									/* �����佫����������ĸ������� */
	}
}

/* �ؿ�ʧ�� */
void GameResult::loadPointLoss()
{
	auto app = (AppDelegate *)(Application::getInstance()); 
	app->showSpot();

	auto uiPointLose = GUIReader::getInstance()->widgetFromJsonFile("UI/All/Result_Lose.ExportJson");
	this->addChild(uiPointLose);

	auto show = FadeIn::create(5.0f);
	uiPointLose->runAction(show);

	auto btn1 = dynamic_cast<Button*>(Helper::seekWidgetByName(uiPointLose, "Button_Fail1"));
	btn1->addTouchEventListener(this, toucheventselector(GameResult::btnPointLoss));
	btn1->setTag(BtnPointLossGeneral);

	auto btn2 = dynamic_cast<Button*>(Helper::seekWidgetByName(uiPointLose, "Button_Fail2"));
	btn2->addTouchEventListener(this, toucheventselector(GameResult::btnPointLoss));
	btn2->setTag(BtnPointLossEquip);

	auto btn3 = dynamic_cast<Button*>(Helper::seekWidgetByName(uiPointLose, "Button_Fail3"));
	btn3->addTouchEventListener(this, toucheventselector(GameResult::btnPointLoss));
	btn3->setTag(BtnPointLossDrawoff);

	auto btn4 = dynamic_cast<Button*>(Helper::seekWidgetByName(uiPointLose, "Button_Fail4"));
	btn4->addTouchEventListener(this, toucheventselector(GameResult::btnPointLoss));
	btn4->setTag(BtnPointLossPreset);
	
	auto btnExit = dynamic_cast<Button*>(Helper::seekWidgetByName(uiPointLose, "Button_Failleft"));
	btnExit->addTouchEventListener(this, toucheventselector(GameResult::btnPointLoss));
	btnExit->setTag(BtnPointLossExit);

	_btnLife = dynamic_cast<Button*>(Helper::seekWidgetByName(uiPointLose, "Button_Resurrection"));
	_btnLife->addTouchEventListener(this, toucheventselector(GameResult::btnPointLoss));
	_btnLife->setTag(BtnPointLossResurrection);

	auto txtLife = dynamic_cast<Text *>(Helper::seekWidgetByName(uiPointLose, "Label_14"));
	DataManager::getInstance()->isSortGoodsNum(93021);
	auto num = DataManager::getInstance()->sortGoodsNum();
	auto strNum = __String::createWithFormat("%d", num);
	txtLife->setText(strNum->getCString());

	auto life = UserData::getInstance()->getPointLive();
	if ((1 == life) || (0 == num))									/* �Ѹ���һ�λ��޸���� */
	{
		_btnLife->setEnabled(false);
		ToolFunc::playBackgroundFile("lose");
	}
	else
	{
		auto number = __String::createWithFormat("res/schedule/%d.png", _iSchedule);
		_spSchedule = Sprite::create(number->getCString());
		_spSchedule->setPosition(130, 260);
		this->addChild(_spSchedule);
		this->schedule(schedule_selector(GameResult::pointLossSchedule), 1.0f);
	}
}

void GameResult::winCallBack()
{
	if (_iGameMode == RoleCreMode_Fighting)
	{
		getPointStarLv();
		loadPointGoods();
	}
	else
	{
		auto panelReward = dynamic_cast<Layout *>(Helper::seekWidgetByName(_uiPointWin, "Panel_Rewards"));
		panelReward->setVisible(false);
	}
	loadFightWarriors();
	loadPointCoinExp();
	fireworks();
}

/* ���ͨ���Ǽ� */
void GameResult::getPointStarLv()
{
	auto curStar = UserData::getInstance()->getCurrentPointStar();	/* ���Ǽ����� */
	auto warriors = DataManager::getInstance()->interPointSetsVector();/* ��ȡ�����佫 */
	auto redCount = UserData::getInstance()->getRedRoleCount();
	auto alive = warriors.size() - redCount;						/* �ҷ������佫�� */

	if (alive == 0)
	{
		if (60 > _iTime)											/* �����ж������κ��佫��������45����ͨ�� */
		{
			_iStarLv = 3;
		}
		else
		{
			if (100 < _iTime)
			{
				_iStarLv = 1;
			}
		}
	}
	else if (2 >= alive)
	{
		if (100 < _iTime)											/* �����ж��������佫���ڵ���2�ˣ���һ����ʮ����ͨ�� */
		{
			_iStarLv = 1;
		}
	}
	else
	{
		_iStarLv = 1;
	}

	_iStarLv = (_iStarLv < curStar) ? curStar : _iStarLv;

	starAnimate(0);

	bool reward = false;
	DataManager::getInstance()->isSetPointStarLv(_iPoint + (_iDiff + 1) * PointIDStartResult, _iStarLv, &reward);
	if (true == reward)
	{
		auto strNotice = FontChina::getInstance()->getComString("MaxStarPoint");
		auto notice = PromptBox::getInstance(strNotice->getCString());
		notice->setFade();
		this->addChild(notice);
	}
}

/* ���������佫 */
void GameResult::loadFightWarriors()
{
	std::vector<CustomsPassGeneral>			cpgs;							/* ������佫 */
	auto warriors = DataManager::getInstance()->interPointSetsVector();		/* ��ȡ�����佫ID */
	auto general = DataManager::getInstance()->localGeneralProptyVector();	/* �����佫���� */
	auto pointGains = DataManager::getInstance()->localPointGainsVector();	/* �ؿ����� */
	auto generalUpgrade = DataManager::getInstance()->localGeneralUpgradeVector();/* �佫������ */
	DataManager::getInstance()->isGetTeamInfo();							/* ��ǰս�ӵȼ� */
	auto teamInfo = DataManager::getInstance()->interTeamInfoVector();
	
	for (unsigned int index = 0; index < warriors.size(); index++)	/* �����佫 */
	{
		auto strLayer = __String::createWithFormat("Panel_RRole%d", index + 1);
		auto layer = dynamic_cast<Layout*>(Helper::seekWidgetByName(_uiPointWin, strLayer->getCString()));
		layer->setVisible(true);
		layer->setScale(0.1f);
		auto scale1 = ScaleTo::create(0.3f, 1.2f);
		auto delay = DelayTime::create(0.1f);
		auto scale2 = ScaleTo::create(0.1f, 1.0f);
		auto seq = Sequence::create(scale1, delay, scale2, NULL);
		layer->runAction(seq);

		auto warrior = warriors[index];
		auto img = dynamic_cast<ImageView*>(Helper::seekWidgetByName(layer, "Image_RRole"));
		auto name = __String::createWithFormat("%s.png", general[warrior.generalID - 10001].chinaSmallName);
		img->loadTexture(name->getCString(), TextureResType::UI_TEX_TYPE_PLIST);
		img->setScale(65.0f / 95.0f);

		DataManager::getInstance()->isGetGeneralProperty(warrior.generalPKID);
		auto property = DataManager::getInstance()->interGeneralVector();/* ��ȡ�佫��Ϣ */

		CustomsPassGeneral cpg = {0};
		cpg.level = warrior.generalLevel;
		cpg.generalPK = warrior.generalPKID;
		cpg.addExp = pointGains[teamInfo[0].teamLevel].exp[_iDiff];	/* �����ѻ�þ��� */
		if (0 == index)												/* ���ѧ����������ӳ� */
		{
			cpg.addExp *= getRoleExpImprove();
		}

		auto expLabel = dynamic_cast<Text*>(Helper::seekWidgetByName(layer, "Label_54"));
		auto strExp = __String::createWithFormat("%d", cpg.addExp);
		expLabel->setText(strExp->getCString());				/* ���� */

		cpg.addExp += property[0].strExp;
		auto tempExp = cpg.addExp;
		unsigned int gLevel = 0;
		for (;gLevel < generalUpgrade.size();gLevel ++)			/* �����佫��ǰ�ȼ����� */
		{
			if (tempExp >= generalUpgrade[gLevel].gNeedExp)
			{
				tempExp -= generalUpgrade[gLevel].gNeedExp;
			}
			else
			{
				break;
			}
		}

		auto lvLabel = dynamic_cast<Text*>(Helper::seekWidgetByName(layer, "Label_RoleLevel"));
		auto strLv = __String::createWithFormat("%d", gLevel);
		lvLabel->setText(strLv->getCString());				/* �ȼ� */

		auto lbExp = dynamic_cast<LoadingBar*>(Helper::seekWidgetByName(layer, "Result_ExpRole"));
		lbExp->setPercent(tempExp * 100.0f / generalUpgrade[gLevel].gNeedExp);
		cpg.level = generalUpgrade[gLevel].gLevel;
		cpgs.push_back(cpg);
	}

	DataManager::getInstance()->isSetPointWarriorsLv(cpgs);
}

/* ���ͨ�ؽ�ҡ����齱�� */
void GameResult::loadPointCoinExp()
{
	auto pointGains = DataManager::getInstance()->localPointGainsVector();	/* �ؿ����� */
	DataManager::getInstance()->isGetTeamInfo();							/* ��ǰս�ӵȼ� */
	auto teamInfo = DataManager::getInstance()->interTeamInfoVector();

	auto coinLabel = dynamic_cast<Text *>(Helper::seekWidgetByName(_uiPointWin, "Label_CoinNum"));
	auto coin = pointGains[teamInfo[0].teamLevel].coin[_iDiff] * ToolFunc::calcRandom(90, 110 + 10 * _iDiff) * 1.0f / 100.0f;
	auto strCoin = __String::createWithFormat("%d", (int)coin);
	coinLabel->setText(strCoin->getCString());

	if (_iGameMode != RoleCreMode_Fighting)							/* �ǹؿ�ģʽ����ȡ��� */
	{
		coin = 0;
	}

	auto expLabel = dynamic_cast<Text *>(Helper::seekWidgetByName(_uiPointWin, "Label_ProAdd"));
	auto exp = (int)(pointGains[teamInfo[0].teamLevel].exp[_iDiff] * getTeamExpImprove());
	auto strExp = __String::createWithFormat("%d", exp);
	expLabel->setText(strExp->getCString());

	DataManager::getInstance()->isCustomsPass(exp, coin);
}

/* ���ͨ����Ʒ���� */
void GameResult::loadPointGoods()
{
	auto pointInfo = DataManager::getInstance()->localCheckPointVector();	/* �ؿ���Ϣ */
	auto pointGains = DataManager::getInstance()->localPointGainsVector();	/* �ؿ����� */
	auto general = DataManager::getInstance()->localGeneralProptyVector();	/* �����佫���� */
	DataManager::getInstance()->propDataParser();
	auto propInfo = DataManager::getInstance()->localPropProptyVector();	/* ���߱� */
	DataManager::getInstance()->equipDataParser();
	auto equipInfo = DataManager::getInstance()->localEquipProptyVector();	/* װ���� */

	auto cellIndex = 1;
	std::vector<CustomsPassGoodsSendStruct> pointGoods;						/* �ؿ���Ʒ���� */
	auto panelGoods = dynamic_cast<Layout*>(Helper::seekWidgetByName(_uiPointWin, "Panel_Rewards"));

	for (int index = 0;index < pointInfo[_iPoint].cThingNum;index ++)
	{
		auto rate = ToolFunc::calcRandom(0, 100);
		if (rate < pointInfo[_iPoint].cThing[index].rate * 100)				/* ��� */
		{
			auto strName = __String::create("");
			auto strPanel = __String::createWithFormat("Panel_Reward%d", cellIndex++);
			auto panel = dynamic_cast<Layout*>(Helper::seekWidgetByName(panelGoods, strPanel->getCString()));
			auto img = dynamic_cast<ImageView*>(Helper::seekWidgetByName(panel, "ResultRewards"));
			auto txt = dynamic_cast<Text*>(Helper::seekWidgetByName(panel, "Label_ReawardName"));

			CustomsPassGoodsSendStruct good;
			good.goodsID = pointInfo[_iPoint].cThing[index].pID;
			good.goodsCount = 1;
			if (93001 > pointInfo[_iPoint].cThing[index].pID)				/* �佫��Ƭ */
			{
				good.goodsType = GoodsChip;
				auto gene = general[pointInfo[_iPoint].cThing[index].pID - 10001];
				strName->appendWithFormat("%s.png", gene.chinaSmallName);
				txt->setText(gene.chinaName);
			}
			else
			{
				if (94000 < pointInfo[_iPoint].cThing[index].pID)			/* װ�� */
				{
					good.goodsType = GoodsEquip;
					auto equip = equipInfo[pointInfo[_iPoint].cThing[index].pID - 94001];
					txt->setText(equip.eChinaName);
				}
				else
				{
					good.goodsType = GoodsProp;
					auto prop = propInfo[pointInfo[_iPoint].cThing[index].pID - 93001];
					txt->setText(prop.pChinaName);
				}
				strName->appendWithFormat("%d.png", pointInfo[_iPoint].cThing[index].pID);
			}
			pointGoods.push_back(good);

			img->loadTexture(strName->getCString(), TextureResType::UI_TEX_TYPE_PLIST);
			goodsAnimate(img, 50.0f / 95.0f);
		}
	}

	if (0 != pointInfo[_iPoint].cBox.pID)									/* ���� */
	{
		CustomsPassGoodsSendStruct good;
		good.goodsID = pointInfo[_iPoint].cBox.pID;
		good.goodsType = GoodsProp;
		good.goodsCount = 1;
		pointGoods.push_back(good);

		auto strPanel = __String::createWithFormat("Panel_Reward%d", cellIndex++);
		auto panel = dynamic_cast<Layout*>(Helper::seekWidgetByName(panelGoods, strPanel->getCString()));
		auto img = dynamic_cast<ImageView*>(Helper::seekWidgetByName(panel, "ResultRewards"));
		auto txt = dynamic_cast<Text*>(Helper::seekWidgetByName(panel, "Label_ReawardName"));

		auto str = __String::createWithFormat("%d.png", pointInfo[_iPoint].cBox.pID);
		img->loadTexture(str->getCString(), TextureResType::UI_TEX_TYPE_PLIST);
		goodsAnimate(img, 50.0f / 95.0f);

		auto prop = propInfo[pointInfo[_iPoint].cBox.pID - 93001];
		txt->setText(prop.pChinaName);
	}

	if (0 < pointInfo[_iPoint].cSoul)								/* ���ʯ */
	{
		CustomsPassGoodsSendStruct good;
		good.goodsID = 93018;
		good.goodsType = GoodsProp;
		good.goodsCount = pointInfo[_iPoint].cSoul;
		pointGoods.push_back(good);

		auto strPanel = __String::createWithFormat("Panel_Reward%d", cellIndex++);
		auto panel = dynamic_cast<Layout*>(Helper::seekWidgetByName(panelGoods, strPanel->getCString()));
		auto img = dynamic_cast<ImageView*>(Helper::seekWidgetByName(panel, "ResultRewards"));
		auto txt = dynamic_cast<Text*>(Helper::seekWidgetByName(panel, "Label_ReawardName"));

		img->loadTexture("93018.png", TextureResType::UI_TEX_TYPE_PLIST);
		goodsAnimate(img, 50.0f / 95.0f);

		auto prop = propInfo[93018 - 93001];
		txt->setText(prop.pChinaName);

		auto numLabel = Label::create();
		auto strNum = __String::createWithFormat("%d", pointInfo[_iPoint].cSoul);
		numLabel->setString(strNum->getCString());
		numLabel->setSystemFontSize(26);
		numLabel->setPosition(10, 50);
		img->addChild(numLabel);
	}

	if (0 < pointInfo[_iPoint].cPill)								/* ������ */
	{
		auto rate = ToolFunc::calcRandom(0, 100);
		if (rate < pointInfo[_iPoint].cPillRate * 100)				/* ��� */
		{
			CustomsPassGoodsSendStruct good;
			good.goodsID = 93019;
			good.goodsType = GoodsProp;
			good.goodsCount = pointInfo[_iPoint].cPill;
			pointGoods.push_back(good);

			auto strPanel = __String::createWithFormat("Panel_Reward%d", cellIndex++);
			auto panel = dynamic_cast<Layout*>(Helper::seekWidgetByName(panelGoods, strPanel->getCString()));
			auto img = dynamic_cast<ImageView*>(Helper::seekWidgetByName(panel, "ResultRewards"));
			auto txt = dynamic_cast<Text*>(Helper::seekWidgetByName(panel, "Label_ReawardName"));

			img->loadTexture("93019.png", TextureResType::UI_TEX_TYPE_PLIST);
			goodsAnimate(img, 50.0f / 95.0f);

			auto prop = propInfo[93019 - 93001];
			txt->setText(prop.pChinaName);

			auto numLabel = Label::create();
			auto strNum = __String::createWithFormat("%d", pointInfo[_iPoint].cPill);
			numLabel->setString(strNum->getCString());
			numLabel->setSystemFontSize(26);
			numLabel->setPosition(10, 50);
			img->addChild(numLabel);
		}
	}

	DataManager::getInstance()->isSetPointGoods(pointGoods);
}

/* ���ѧ��ģʽ1ʤ�� */
void GameResult::loadGameXG1Win()
{
	auto jxxgBuffInfo = DataManager::getInstance()->interJxxgBuffVector();

	auto buffLabel = dynamic_cast<Text *>(Helper::seekWidgetByName(_uiPointWin, "Label_JXReward"));
	auto strBuffLabel = __String::create("");

	jxxgBuffInfo[0].ticket += 1;									/* ���ش�����1 */
	jxxgBuffInfo[0].num = jxxgBuffInfo[0].num * 10 + 5;				/* �ؿ����� */

	if (_iTime < 45)
	{
		jxxgBuffInfo[0].rewar = jxxgBuffInfo[0].rewar * 10 + 1;
		strBuffLabel->appendWithFormat("%s5", FontChina::getInstance()->getComString("JXXG_Buff1_1")->getCString());
	}
	else if (_iTime < 60)
	{
		jxxgBuffInfo[0].rewar = jxxgBuffInfo[0].rewar * 10 + 2;
		strBuffLabel->appendWithFormat("%s5", FontChina::getInstance()->getComString("JXXG_Buff1_2")->getCString());
	}
	else if (_iTime < 90)
	{
		jxxgBuffInfo[0].rewar = jxxgBuffInfo[0].rewar * 10 + 3;
		strBuffLabel->appendWithFormat("%s5", FontChina::getInstance()->getComString("JXXG_Buff1_3")->getCString());
	}
	else if (_iTime < 120)
	{
		jxxgBuffInfo[0].rewar = jxxgBuffInfo[0].rewar * 10 + 4;
		strBuffLabel->appendWithFormat("%s5", FontChina::getInstance()->getComString("JXXG_Buff1_4")->getCString());
	}
	else
	{
		buffLabel->setText(FontChina::getInstance()->getComString("JXXG_Buff1_5")->getCString());
		strBuffLabel->appendWithFormat("%s", FontChina::getInstance()->getComString("JXXG_Buff1_5")->getCString());
		DataManager::getInstance()->isBuyCoin(0, 5000);
	}

	buffLabel->setText(strBuffLabel->getCString());
	auto txtSz = buffLabel->getContentSize();
	buffLabel->ignoreContentAdaptWithSize(true);
	buffLabel->setTextAreaSize(Size(450, 2 * txtSz.height));
	DataManager::getInstance()->isJxxgPassSucceed(0, 0, jxxgBuffInfo);
}

/* ���ѧ��ģʽ2ʤ�� */
void GameResult::loadGameXG2Win()
{
	auto jxxgBuffInfo = DataManager::getInstance()->interJxxgBuffVector();
	auto buffLabel = dynamic_cast<Text *>(Helper::seekWidgetByName(_uiPointWin, "Label_JXReward"));
	auto strBuffLabel = __String::create("");

	jxxgBuffInfo[1].ticket += 1;										/* ���ش�����1 */
	if (_iTime < 60)
	{
		jxxgBuffInfo[1].num = jxxgBuffInfo[1].num * 10 + 3;			/* �ؿ����� */
		jxxgBuffInfo[1].rewar = jxxgBuffInfo[1].rewar * 10 + 1;		/* �������� */
		strBuffLabel->appendWithFormat("%s3", FontChina::getInstance()->getComString("JXXG_Buff2_1")->getCString());
	}
	else if (_iTime < 90)
	{
		jxxgBuffInfo[1].num = jxxgBuffInfo[1].num * 10 + 3;			/* �ؿ����� */
		jxxgBuffInfo[1].rewar = jxxgBuffInfo[1].rewar * 10 + 2;		/* �������� */
		strBuffLabel->appendWithFormat("%s3", FontChina::getInstance()->getComString("JXXG_Buff2_2")->getCString());
	}
	else if (_iTime < 120)
	{
		jxxgBuffInfo[1].num = jxxgBuffInfo[1].num * 10 + 5;			/* �ؿ����� */
		jxxgBuffInfo[1].rewar = jxxgBuffInfo[1].rewar * 10 + 3;		/* �������� */
		strBuffLabel->appendWithFormat("%s5", FontChina::getInstance()->getComString("JXXG_Buff2_3")->getCString());
	}
	else if (_iTime < 150)
	{
		jxxgBuffInfo[1].num = jxxgBuffInfo[1].num * 10 + 5;			/* �ؿ����� */
		jxxgBuffInfo[1].rewar = jxxgBuffInfo[1].rewar * 10 + 4;		/* �������� */
		strBuffLabel->appendWithFormat("%s5", FontChina::getInstance()->getComString("JXXG_Buff2_4")->getCString());
	}
	else
	{
		jxxgBuffInfo[1].num = jxxgBuffInfo[1].num * 10 + 5;			/* �ؿ����� */
		jxxgBuffInfo[1].rewar = jxxgBuffInfo[1].rewar * 10 + 5;		/* �������� */
		strBuffLabel->appendWithFormat("%s5", FontChina::getInstance()->getComString("JXXG_Buff2_5")->getCString());
	}

	buffLabel->setText(strBuffLabel->getCString());
	auto txtSz = buffLabel->getContentSize();
	buffLabel->ignoreContentAdaptWithSize(true);
	buffLabel->setTextAreaSize(Size(450, 2 * txtSz.height));
	DataManager::getInstance()->isJxxgPassSucceed(0, 0, jxxgBuffInfo);
}

/* ���ѧ��ģʽ3ʤ�� */
void GameResult::loadGameXG3Win()
{
	auto jxxgBuffInfo = DataManager::getInstance()->interJxxgBuffVector();
	auto grade = UserData::getInstance()->getJxxg3Grade();
	auto buffLabel = dynamic_cast<Text *>(Helper::seekWidgetByName(_uiPointWin, "Label_JXReward"));
	auto strBuffLabel = __String::create("");

	jxxgBuffInfo[2].ticket += 1;
	jxxgBuffInfo[2].rewar = jxxgBuffInfo[2].rewar * 10 + grade;		/* �������� */
	switch (grade)
	{
	case 1:
		jxxgBuffInfo[2].num = jxxgBuffInfo[2].num * 10 + 1;			/* �ؿ����� */
		strBuffLabel->appendWithFormat("%s1", FontChina::getInstance()->getComString("JXXG_Buff3_1")->getCString());
		break;
	case 2:
		jxxgBuffInfo[2].num = jxxgBuffInfo[2].num * 10 + 2;			/* �ؿ����� */
		strBuffLabel->appendWithFormat("%s2", FontChina::getInstance()->getComString("JXXG_Buff3_2")->getCString());
		break;
	case 3:
		jxxgBuffInfo[2].num = jxxgBuffInfo[2].num * 10 + 3;			/* �ؿ����� */
		strBuffLabel->appendWithFormat("%s3", FontChina::getInstance()->getComString("JXXG_Buff3_3")->getCString());
		break;
	case 4:
		jxxgBuffInfo[2].num = jxxgBuffInfo[2].num * 10 + 5;			/* �ؿ����� */
		strBuffLabel->appendWithFormat("%s5", FontChina::getInstance()->getComString("JXXG_Buff3_4")->getCString());
		break;
	case 5:
		jxxgBuffInfo[2].num = jxxgBuffInfo[2].num * 10 + 5;			/* �ؿ����� */
		strBuffLabel->appendWithFormat("%s5", FontChina::getInstance()->getComString("JXXG_Buff3_5")->getCString());
		break;
	case 6:
		jxxgBuffInfo[2].num = jxxgBuffInfo[2].num * 10 + 5;			/* �ؿ����� */
		strBuffLabel->appendWithFormat("%s5", FontChina::getInstance()->getComString("JXXG_Buff3_6")->getCString());
		break;
	case 7:
		jxxgBuffInfo[2].num = jxxgBuffInfo[2].num * 10 + 5;			/* �ؿ����� */
		strBuffLabel->appendWithFormat("%s5", FontChina::getInstance()->getComString("JXXG_Buff3_7")->getCString());
		break;
	}

	buffLabel->setText(strBuffLabel->getCString());
	auto txtSz = buffLabel->getContentSize();
	buffLabel->ignoreContentAdaptWithSize(true);
	buffLabel->setTextAreaSize(Size(450, 2 * txtSz.height));
	DataManager::getInstance()->isJxxgPassSucceed(0, 0, jxxgBuffInfo);
}

/* ���ѧ��ģʽ4ʤ�� */
void GameResult::loadGameXG4Win()
{
	auto dmg = UserData::getInstance()->getJxxg4Grade();
	auto buffLabel = dynamic_cast<Text *>(Helper::seekWidgetByName(_uiPointWin, "Label_JXReward"));

	int step = 0;
	std::vector<DrawoffGoodsStruct > tempVector;

	if (dmg < 42000)
	{
		step = 1;

		for (int index = 0;index < 2;index++)
		{
			DrawoffGoodsStruct drawoff;
			memset(&drawoff, 0, sizeof(drawoff));
			drawoff.goodsType = GoodsEquip;
			drawoff.goodsID = ToolFunc::calcRandom(90035, 90054);
			tempVector.push_back(drawoff);
		}
	}
	else if (dmg < 60450)
	{
		step = 2;

		for (int index = 0;index < 3;index++)
		{
			DrawoffGoodsStruct drawoff;
			memset(&drawoff, 0, sizeof(drawoff));
			drawoff.goodsType = GoodsEquip;
			drawoff.goodsID = ToolFunc::calcRandom(90035, 90054);
			tempVector.push_back(drawoff);
		}
	}
	else if (dmg < 1119810)
	{
		step = 3;

		for (int index = 0;index < 3;index++)
		{
			DrawoffGoodsStruct drawoff;
			memset(&drawoff, 0, sizeof(drawoff));
			drawoff.goodsType = GoodsEquip;
			drawoff.goodsID = ToolFunc::calcRandom(90035, 90054);
			tempVector.push_back(drawoff);

			if (0 == index)
			{
				DrawoffGoodsStruct drawoff;
				memset(&drawoff, 0, sizeof(drawoff));
				drawoff.goodsType = GoodsEquip;
				drawoff.goodsID = ToolFunc::calcRandom(90055, 90075);
				tempVector.push_back(drawoff);
			}
		}
	}
	else if (dmg < 194261)
	{
		step = 4;

		for (int index = 0;index < 5;index++)
		{
			DrawoffGoodsStruct drawoff;
			memset(&drawoff, 0, sizeof(drawoff));
			drawoff.goodsType = GoodsEquip;
			drawoff.goodsID = ToolFunc::calcRandom(90035, 90054);
			tempVector.push_back(drawoff);

			if (0 == index)
			{
				DrawoffGoodsStruct drawoff;
				memset(&drawoff, 0, sizeof(drawoff));
				drawoff.goodsType = GoodsEquip;
				drawoff.goodsID = ToolFunc::calcRandom(90055, 90075);
				tempVector.push_back(drawoff);
			}
		}
	}
	else if (dmg < 250580)
	{
		step = 5;

		for (int index = 0;index < 5;index++)
		{
			DrawoffGoodsStruct drawoff;
			memset(&drawoff, 0, sizeof(drawoff));
			drawoff.goodsType = GoodsEquip;
			drawoff.goodsID = ToolFunc::calcRandom(90035, 90054);
			tempVector.push_back(drawoff);

			if (index < 3)
			{
				DrawoffGoodsStruct drawoff;
				memset(&drawoff, 0, sizeof(drawoff));
				drawoff.goodsType = GoodsEquip;
				drawoff.goodsID = ToolFunc::calcRandom(90055, 90075);
				tempVector.push_back(drawoff);
			}
		}
	}
	else
	{
		step = 6;

		for (int index = 0;index < 5;index++)
		{
			DrawoffGoodsStruct drawoff;
			memset(&drawoff, 0, sizeof(drawoff));
			drawoff.goodsType = GoodsEquip;
			drawoff.goodsID = ToolFunc::calcRandom(90035, 90054);
			tempVector.push_back(drawoff);

			if (index < 3)
			{
				DrawoffGoodsStruct drawoff;
				memset(&drawoff, 0, sizeof(drawoff));
				drawoff.goodsType = GoodsEquip;
				drawoff.goodsID = ToolFunc::calcRandom(90055, 90075);
				tempVector.push_back(drawoff);
			}

			if (0 == index)
			{
				DrawoffGoodsStruct drawoff;
				memset(&drawoff, 0, sizeof(drawoff));
				drawoff.goodsType = GoodsEquip;
				drawoff.goodsID = ToolFunc::calcRandom(90076, 90092);
				tempVector.push_back(drawoff);
			}
		}
	}

	auto strBuffLabel = __String::createWithFormat("JXXG_Buff4_%d", step);
	buffLabel->setText(strBuffLabel->getCString());
	auto txtSz = buffLabel->getContentSize();
	buffLabel->setTextAreaSize(Size(480, 2 * txtSz.height));
	DataManager::getInstance()->isDrawoffCard(0, 0, 0, 0, tempVector);

	auto jxxgBuffInfo = DataManager::getInstance()->interJxxgBuffVector();
	jxxgBuffInfo[3].ticket += 1;									/* ���ش�����1 */
	DataManager::getInstance()->isJxxgPassSucceed(0, 0, jxxgBuffInfo);
}

/* ���ѧ��ģʽ4ʧ�� */
void GameResult::loadGameXGLoss(int index)
{
	auto jxxgBuffInfo = DataManager::getInstance()->interJxxgBuffVector();
	jxxgBuffInfo[index].ticket += 1;								/* ���ش�����1 */
	DataManager::getInstance()->isJxxgPassSucceed(0, 0, jxxgBuffInfo);
}

/* ��ȡ���ѧ���ʺž���ӳ� */
float GameResult::getTeamExpImprove()
{
	auto fRet = 1.0f;
	if (_iGameMode != RoleCreMode_Fighting)
	{
		return fRet;
	}

	auto jxxgBuffInfo = DataManager::getInstance()->interJxxgBuffVector();
	if (0 >= jxxgBuffInfo.size())
	{
		return fRet;
	}

	auto num = jxxgBuffInfo[1].num%10;								/* ȡ��ǰbuffʣ��ؿ�����: ս�Ӿ��� */
	if (num > 0)
	{
		float expImprove[] =  {1.1f, 1.2f, 1.35f, 1.60f, 2.0f};
		fRet = expImprove[jxxgBuffInfo[1].rewar%10];

		if (1 == num)
		{
			jxxgBuffInfo[1].num = jxxgBuffInfo[1].num/10;
			jxxgBuffInfo[1].rewar = jxxgBuffInfo[1].rewar/10;
		}
		else
		{
			jxxgBuffInfo[1].num = jxxgBuffInfo[1].num/10 * 10 + num - 1;
		}
	}

	DataManager::getInstance()->isJxxgPassSucceed(0, 0, jxxgBuffInfo);

	return fRet;
}

/* ��ȡ���ѧ����������ӳ� */
float GameResult::getRoleExpImprove()
{
	auto fRet = 1.0f;
	if (_iGameMode != RoleCreMode_Fighting)
	{
		return fRet;
	}

	auto jxxgBuffInfo = DataManager::getInstance()->interJxxgBuffVector();
	if (0 >= jxxgBuffInfo.size())
	{
		return fRet;
	}

	auto num = jxxgBuffInfo[2].num%10;									/* ȡ��ǰbuffʣ��ؿ�����: �������� */
	if (num > 0)
	{
		float expImprove[] = {1.3f, 1.3f, 1.3f, 1.3f, 1.35f, 1.6f, 2.0f};
		fRet = expImprove[jxxgBuffInfo[2].rewar%10];		

		if (1 == num)
		{
			jxxgBuffInfo[2].num = jxxgBuffInfo[2].num/10;
			jxxgBuffInfo[2].rewar = jxxgBuffInfo[2].rewar/10;
		}
		else
		{
			jxxgBuffInfo[2].num = jxxgBuffInfo[2].num/10 * 10 + num - 1;
		}
	}

	DataManager::getInstance()->isJxxgPassSucceed(0, 0, jxxgBuffInfo);

	return fRet;
}

/* �ؿ�ʤ���ص� */
void GameResult::btnPointWin(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		auto pst = (Button*)pSender;
		auto tag = pst->getTag();

		switch (tag)
		{
		case BtnPointWinExit:
			Director::getInstance()->replaceScene(MainScene::scene());
			break;
		}
	}
}

/* �ؿ�ʧ�ܻص� */
void GameResult::btnPointLoss(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		auto pst = (Button*)pSender;
		auto tag = (PointLossButtons)pst->getTag();

		switch (tag)
		{
		case BtnPointLossGeneral:
		case BtnPointLossPreset:
			Director::getInstance()->replaceScene(Maidan::scene());
			break;
		case BtnPointLossEquip:
			Director::getInstance()->replaceScene(EquipEnhance::Create());
			break;
		case BtnPointLossDrawoff:
			Director::getInstance()->replaceScene(Store::create());
			break;
		case BtnPointLossExit:
			Director::getInstance()->replaceScene(MainScene::scene());
			break;
		case BtnPointLossResurrection:
			{
				DataManager::getInstance()->goodsCountUpdate(93021, -1);
				this->unschedule(schedule_selector(GameResult::pointLossSchedule));
				auto center = (Counterpart *)(this->getParent());
				center->gameResume();
				this->removeFromParentAndCleanup(true);
			}			
			break;
		}
	}
}

/* �����ʱ */
void GameResult::pointLossSchedule(float dt)
{
	_iSchedule --;
	if (0 <= _iSchedule)
	{
		auto number = __String::createWithFormat("res/schedule/%d.png", _iSchedule);
		_spSchedule->setTexture(number->getCString());
	}
	else
	{
		this->unschedule(schedule_selector(GameResult::pointLossSchedule));
		ToolFunc::playBackgroundFile("lose");
		_btnLife->setEnabled(false);
		_spSchedule->setVisible(false);
	}
}

/* UI�Ǽ���ʾ �Ǽ����� */
void GameResult::starAnimate(int star)
{
	if (star < maxStarNumResult)
	{
		if (star < _iStarLv)
		{
			auto picNum = 13;
			auto spStar = Sprite::create();
			spStar->setPosition(ptStar[star]);
			this->addChild(spStar);

			Animation* animation = Animation::create();  
			for(int index = 0; index < picNum; index ++)  
			{
				auto strStarName = __String::createWithFormat("res/MainFight/star%d.png", index);

				animation->addSpriteFrameWithFile(strStarName->getCString());
			}  
			animation->setDelayPerUnit(0.3f / picNum);
			auto animate = Animate::create(animation);

			spStar->runAction(Sequence::create(animate, CallFuncN::create(std::bind(&GameResult::subStarAnimate, this, star)), NULL));
		}
	}
}

/* �Ǽ����� */
void GameResult::subStarAnimate(int star)
{
	if (star + 1 < maxStarNumResult)
	{
		starAnimate(star + 1);
	}
}

/* ʤ���̻� */
void GameResult::fireworks()
{
	auto animation = Animation::create();

	for (int index = 0;index < 41;index ++)
	{
		auto str = __String::createWithFormat("res/Firworks/%05d.png", index);
		animation->addSpriteFrameWithFile(str->getCString());
	}

	animation->setDelayPerUnit(0.05f);
	animation->setRestoreOriginalFrame(true);
	animation->setLoops(2);

	auto animate = Animate::create(animation);

	auto sp = Sprite::create();
	auto rc = Director::getInstance()->getWinSize();
	sp->setPosition(rc.width/2, rc.height/2);
	sp->runAction(animate);
	this->addChild(sp, 1000);
}

/* �����Ʒ���� */
void GameResult::goodsAnimate(ImageView *img, float scale)
{
	if (NULL == img)
	{
		return;
	}

	img->setScale(0.1f);
	auto rotation = RotateBy::create(0.6f, 1080);
	auto seq = Sequence::create(ScaleTo::create(0.6f, scale * 1.2f), DelayTime::create(0.3f), ScaleTo::create(0.15f, scale), NULL);
	img->runAction(Spawn::createWithTwoActions(rotation, seq));
}