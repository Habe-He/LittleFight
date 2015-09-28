#include "MainFight.h"
#include "UserInfo/UserData.h"
#include "Scene/MainScene.h"
#include "cocostudio/CocoStudio.h"
#include "SuperImage.h"
#include "UserInfo/UserData.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;

/**********************UI控件名******************************/
const char *ControlsNames[MFCtrl_Max] = 
{
	"Button_Sa",
	"Button_Sb",
	"Button_Sc",
	"Button_Sd",
	"Button_X",										/* 按钮“暂停”名 */
	"ProgressBar_MainHp",							/* 主HP进度条 */
	"ProgressBar_SubHp",							/* 副HP进度条 */
	"Panel_82",										/* 主将头像底图 */
};

MainFight::MainFight(void)
	: m_iHelpNum(0)
{
}

MainFight::~MainFight(void)
{
}

bool MainFight::init()
{
	if (false == Layer::init())
	{
		return false;
	}

	loadMainFightScene();

	return true;
}

//public
/*********************************************************************
** 功能：		设置角色HP、MP显示控件
** 输入参数：	无
** 返回值：		无
** 修改记录：	
*********************************************************************/
void MainFight::setRoleHealthCtrl()
{
	auto panelHealth = dynamic_cast<Layout *>(Helper::seekWidgetByName(m_hUIMain, ControlsNames[MFCtrl_Health]));
	auto mainHp = dynamic_cast<LoadingBar *>(Helper::seekWidgetByName(panelHealth, ControlsNames[MFCtrl_MainHP]));
	auto subHp = dynamic_cast<LoadingBar *>(Helper::seekWidgetByName(panelHealth, ControlsNames[MFCtrl_SubHP]));
	
	auto vct = UserData::getInstance()->getRoles();
	m_iHelpNum = 0;
	mainHp->setPercent(100);
	subHp->setPercent(100);

	bool bFlag = false;
	for ( const auto &ref : vct)
	{
		auto role = (Role *)ref;
		auto info = role->getRoleInfo();

		if (RoleMode_Main == info.mode)
		{
			auto si = SuperImage::create();
			si->resetOwner(role);
			si->setProgressBar(mainHp, subHp);
			si->setPosition(Point(93, 74));
			panelHealth->addChild(si, 5);
			si->createClipper("res/MainFight/Mask1.png", role->getStrRoleName(), -68.0f/95.0f);
			role->setHealthCtrl(si);
		}
		if (RoleMode_Companion == info.mode)
		{
			addRoleHelp(role);
		}
	}
}

/*********************************************************************
** 功能：		设置角色攻击按钮
** 输入参数：	无
** 返回值：		无
** 修改记录：	
*********************************************************************/
void MainFight::setRoleActButton()
{
	auto vct = UserData::getInstance()->getRoles();
	auto mainRole = (Role *)vct[0];
	auto info = mainRole->getRoleSkillInfo();

	for (int i = MFCtrl_Sa;i <= MFCtrl_Sd;i ++)
	{
		auto btn = dynamic_cast<Button *>(Helper::seekWidgetByName(m_hUIMain, ControlsNames[i]));
		btn->addTouchEventListener(this, toucheventselector(MainFight::actionBtnClicked));
		btn->setTag(i);

		if (info[i - MFCtrl_Sa + RoleAct_SkillOne].level > 0)
		{
			auto sz = btn->getContentSize();
			auto si = SuperImage::create();
			si->setProgressBar("res/MainFight/Mask2.png", "", -72.0f/80.0f);
			si->setProgressDuration(info[i - MFCtrl_Sa + RoleAct_SkillOne].cd);
			si->createClipper("res/MainFight/Mask2.png", info[i - MFCtrl_Sa + RoleAct_SkillOne].name, 68.0f/80.0f);
			si->setPosition(sz.width / 2, sz.height / 2);
			btn->addChild(si, 0, 0);
		}
		else
		{
			btn->setVisible(false);
			btn->setTouchEnabled(false);
		}
	}
}

/*********************************************************************
** 功能：		重置动作技能cd
** 输入参数：	int tag: 要更改的技能
**				float cd: 更改后的cd
** 返回值：		无
** 修改记录：	
*********************************************************************/
void MainFight::resetActCD(int tag, float cd)
{
	auto btn = dynamic_cast<Button *>(Helper::seekWidgetByName(m_hUIMain, ControlsNames[tag]));

	auto si = (SuperImage*)btn->getChildByTag(0);
	if (NULL == si)
	{
		return;
	}

	si->setProgressDuration(cd);
}

void MainFight::setButtonEventListener(Ref *target, SEL_TouchEvent selector)
{
	m_hBtnPause->addTouchEventListener(target, selector);
}

//protected
/*********************************************************************
** 功能：		战斗界面加载
** 输入参数：	无
** 返回值：		无
** 修改记录：	
*********************************************************************/
void MainFight::loadMainFightScene()
{
	m_hUIMain = GUIReader::getInstance()->widgetFromJsonFile("UI/All/MainFight.ExportJson");
	this->addChild(m_hUIMain, order_MainFight);

	m_hBtnPause = dynamic_cast<Button *>(Helper::seekWidgetByName(m_hUIMain, ControlsNames[MFCtrl_Pause]));
	m_hBtnPause->setTag(MFCtrl_Pause);								/* 暂停 */

	auto autoFight = dynamic_cast<Button *>(Helper::seekWidgetByName(m_hUIMain, "Button_AutoFight"));
	autoFight->setScale(50.0f / 83.0f);
	autoFight->setPosition(Point(30, 30));

	auto count = DataManager::getInstance()->isSortGoodsNum(93021);
	auto lifeNum = __String::createWithFormat("%d", DataManager::getInstance()->sortGoodsNum());
	auto labelLife = Label::createWithSystemFont("", "Arial", 12);
	labelLife->setPosition(Point(353, 460));
	labelLife->setAnchorPoint(Point::ANCHOR_MIDDLE);
	this->addChild(labelLife, order_MainFight);
	labelLife->setString(lifeNum->getCString());
	labelLife->setColor(Color3B(0xFF, 0xF7, 0xD3));
}

/*********************************************************************
** 功能：		添加副将
** 输入参数：	Role *role: 援兵
** 返回值：		无
** 修改记录：	
*********************************************************************/
void MainFight::addRoleHelp(Role *role)
{
	auto si = SuperImage::create();
	si->resetOwner(role);
	si->setProgressBar("res/MainFight/Dark.png", "res/MainFight/Golden.png");
	si->setPosition(Point(140.0f + UNIT_WIDTH * m_iHelpNum, 360.0f));
	this->addChild(si, order_MainFight + 1);
	si->createClipper("res/MainFight/Mask1.png", role->getStrRoleName(), 45.0f/95.0f);
	role->setHealthCtrl(si);
	
	m_iHelpNum ++;
}

void MainFight::actionBtnClicked(Ref *ref, TouchEventType type)
{
	auto vct = UserData::getInstance()->getRoles();
	auto mainRole = (Role *)vct[0];
	auto info = mainRole->getRoleInfo();
	if ((RoleMode_Main != info.mode) || (RoleStatus_Death == info.status))	/* 不是主将或主将死亡 */
	{
		return;
	}

	auto btn = (Button*)ref;
	auto si = (SuperImage*)btn->getChildByTag(0);

	switch (type)
	{
	case TouchEventType::TOUCH_EVENT_BEGAN:
		break;
	case TouchEventType::TOUCH_EVENT_ENDED:
		if (true == mainRole->runLordlAction((RoleCmdSign)(btn->getTag() + RoleCmdSign_SkillOne - MFCtrl_Sa)))
		{
			if (NULL != si)
			{
				si->runSpriteProgressToRadial();
			}
		}
		break;
	default:
		break;
	}
}