#include "PointInfo.h"
#include "cocostudio/CocoStudio.h"
#include "UserInfo/UserData.h"
#include "SimpleAudioEngine.h"
#include "Counterpart/RolePrestrain.h"
#include "DataManager/DataManager.h"
#include "Roles/Role/Role_Def.h"
#include "FightPoints_Def.h"
#include "Counterpart/GameResult.h"
#include "UserInfo/Define_Info.h"
#include "PromptBox/PromptBox.h"
#include "FightPoints.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;

USING_NS_CC;

PointInfo::PointInfo(void)
	: _station(0)
	, _piImg(NULL)
{
}

PointInfo::~PointInfo(void)
{
}

Scene* PointInfo::scene(Point ptLoc, int sign, int star)
{
	auto sc = Scene::create();
	auto layer = PointInfo::create(ptLoc, sign, star);
	sc->addChild(layer);
	return sc;
}

PointInfo* PointInfo::create(Point ptLoc, int sign, int star)
{
	auto ret = new PointInfo();
	if (ret && ret->init(ptLoc, sign, star))
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

bool PointInfo::init(Point ptLoc, int sign, int star)
{
	bool bRet = false;

	do 
	{
		DataManager::getInstance()->checkPointDataParser(UserData::getInstance()->getFightDifficulty());
		pointInfo = DataManager::getInstance()->localCheckPointVector();
		
		_station = sign;
		_star = star;
		showPointInfo(ptLoc);
		//parseJxxgBuff();
		addTouchEventListener();

		bRet = true;
	} while ( 0 );

	return bRet;
}

void PointInfo::onEnter()
{
	Node::onEnter();
}

void PointInfo::onExit()
{
	_eventDispatcher->removeEventListener(listener);
	Node::onExit();
}

void PointInfo::showPointInfo(Point ptLoc)
{
	auto cellIndex = 1;
	auto info = pointInfo[_station];								/* 关卡信息 */

	string str = "";
	if (ptLoc.x > 400)											/* 屏幕右半边的关卡 */
	{
		str = "UI/All/CustomsPass_1.ExportJson";
	}
	else
	{
		str = "UI/All/CustomsPass_0.ExportJson";
	}

	auto cusPass = GUIReader::getInstance()->widgetFromJsonFile(str.c_str());
	this->addChild(cusPass);
	cusPass->setPosition(ptLoc);
	if (ptLoc.x > 400)					/* 屏幕右半边的关卡 */
	{
		cusPass->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
	}
	else
	{
		cusPass->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	}

	_piImg = dynamic_cast<ImageView*>(Helper::seekWidgetByName(cusPass, "Image_CP0BG"));

	//确定
	auto button_Confirm = dynamic_cast<Button*>(Helper::seekWidgetByName(cusPass, "Button_Confirm_0"));
	button_Confirm->addTouchEventListener(this, toucheventselector(PointInfo::confirmButton));

	//扫荡
	auto button_WipeOut = dynamic_cast<Button*>(Helper::seekWidgetByName(cusPass, "Button_WipeOut_0"));
	button_WipeOut->addTouchEventListener(this, toucheventselector(PointInfo::wipeOutButton));

	//标题
	auto label_Title = dynamic_cast<Text*>(Helper::seekWidgetByName(cusPass, "Label_48"));
	label_Title->setText(info.cName);

#if 0
	//关卡介绍
	auto label_Des = dynamic_cast<Text*>(Helper::seekWidgetByName(cusPass, "Label_Des"));
	label_Des->setFontSize(18);
	label_Des->ignoreContentAdaptWithSize(false); 
	label_Des->setSize(Size(250, 60)); 
	label_Des->setTextHorizontalAlignment(TextHAlignment::LEFT);

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
			auto strImg = __String::createWithFormat("Image_%d_0", cellIndex++);
			auto img = dynamic_cast<ImageView*>(Helper::seekWidgetByName(cusPass, strImg->getCString()));
			img->loadTexture(str->getCString(), TextureResType::UI_TEX_TYPE_PLIST);
			img->setScale(60.0f / 95.0f);
		}
		else
		{
			auto str = __String::createWithFormat("%d.png", info.cThing[index].pID);
			auto strImg = __String::createWithFormat("Image_%d_0", cellIndex++);
			auto img = dynamic_cast<ImageView*>(Helper::seekWidgetByName(cusPass, strImg->getCString()));
			img->loadTexture(str->getCString(), TextureResType::UI_TEX_TYPE_PLIST);
			img->setScale(60.0f / 95.0f);
		}
	}

	if (0 != info.cBox.pID)											/* 宝箱 */
	{
		auto str = __String::createWithFormat("%d.png", info.cBox.pID);
		auto strImg = __String::createWithFormat("Image_%d_0", cellIndex++);
		auto img = dynamic_cast<ImageView*>(Helper::seekWidgetByName(cusPass, strImg->getCString()));
		img->loadTexture(str->getCString(), TextureResType::UI_TEX_TYPE_PLIST);
		img->setScale(60.0f / 95.0f);
	}

	if (0 < info.cSoul)												/* 灵魂石 */
	{
		auto strImg = __String::createWithFormat("Image_%d_0", cellIndex++);
		auto img = dynamic_cast<ImageView*>(Helper::seekWidgetByName(cusPass, strImg->getCString()));
		img->loadTexture("93018.png", TextureResType::UI_TEX_TYPE_PLIST);
		img->setScale(60.0f / 90.0f);

		auto numLabel = Label::create();
		auto strNum = __String::createWithFormat("%d", info.cSoul);
		numLabel->setString(strNum->getCString());
		numLabel->setSystemFontSize(26);
		numLabel->setPosition(10, 70);
		img->addChild(numLabel);
	}

	if (0 < info.cPill)												/* 培养丹 */
	{
		auto strImg = __String::createWithFormat("Image_%d_0", cellIndex++);
		auto img = dynamic_cast<ImageView*>(Helper::seekWidgetByName(cusPass, strImg->getCString()));
		img->loadTexture("93019.png", TextureResType::UI_TEX_TYPE_PLIST);
		img->setScale(60.0f / 90.0f);

		auto numLabel = Label::create();
		auto strNum = __String::createWithFormat("%d", info.cPill);
		numLabel->setString(strNum->getCString());
		numLabel->setSystemFontSize(26);
		numLabel->setPosition(10, 70);
		img->addChild(numLabel);
	}
	label_Des->setText(info.cDes);
#endif
}

void PointInfo::confirmButton(Ref* pSender, TouchEventType type)
{
	if ( TouchEventType::TOUCH_EVENT_ENDED == type )
	{
		if (UserData::getInstance()->setupEffect)
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(Click);

		UserData::getInstance()->setRoleCreateModel(RoleCreMode_Fighting);
		RolePrestrain begin;
		begin.loading(_station);
	}
}

void PointInfo::wipeOutButton(Ref* pSender, TouchEventType type)
{
	if ( TouchEventType::TOUCH_EVENT_ENDED == type )
	{
		if (UserData::getInstance()->setupEffect)
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(Click);

		DataManager::getInstance()->isGetTeamInfo();				/* 当前战队等级 */
		auto teamInfo = DataManager::getInstance()->interTeamInfoVector();

		if ((maxStarNum == _star) && (16 <= teamInfo[0].teamLevel))	/* 达到最大星级且战队达到16级 */
		{
			UserData::getInstance()->setRoleCreateModel(RoleCreMode_Fighting);
			auto sce = Scene::create();
			sce->addChild(GameResult::create(Result_Win, 0));
			Director::getInstance()->replaceScene(sce);
		}
		else
		{
			auto notice = PromptBox::getInstance(FontChina::getInstance()->getComString("Mopup")->getCString());
			notice->setFade();
			this->addChild(notice);
		}
	}
}

/* 获取稷下学宫buff */
void PointInfo::parseJxxgBuff()
{
	auto jxxgBuffInfo = DataManager::getInstance()->interJxxgBuffVector();
	auto strBuff = __String::create("");

	if (0 >= jxxgBuffInfo.size())
	{
		return;
	}

	auto num = jxxgBuffInfo[0].num%10;							/* 取当前buff剩余关卡次数: 战队属性 */
	if (num > 0)
	{
		auto strBuffName = __String::createWithFormat("JXXG_Buff1_%d", jxxgBuffInfo[0].rewar%10);
		strBuff->appendWithFormat("%s%d\r\n", FontChina::getInstance()->getComString(strBuffName->getCString())->getCString(), num);
	}

	num = jxxgBuffInfo[1].num%10;								/* 取当前buff剩余关卡次数: 战队经验 */
	if (num > 0)
	{
		auto strBuffName = __String::createWithFormat("JXXG_Buff2_%d", jxxgBuffInfo[1].rewar%10);
		strBuff->appendWithFormat("%s%d\r\n", FontChina::getInstance()->getComString(strBuffName->getCString())->getCString(), num);
	}

	num = jxxgBuffInfo[2].num%10;								/* 取当前buff剩余关卡次数: 主将经验 */
	if (num > 0)
	{
		auto strBuffName = __String::createWithFormat("JXXG_Buff3_%d", jxxgBuffInfo[2].rewar%10);
		strBuff->appendWithFormat("%s%d\r\n", FontChina::getInstance()->getComString(strBuffName->getCString())->getCString(), num);
	}

	if (0 < strBuff->length())
	{
		auto strBuffInfo = __String::createWithFormat("%s\r\n%s", 
			FontChina::getInstance()->getComString("JXXG_Buff_Info")->getCString(), strBuff->getCString());

		auto labelBuff = Label::create();
		labelBuff->setSystemFontSize(18);
		labelBuff->setString(strBuffInfo->getCString());
		labelBuff->setPosition(470, 370);
		labelBuff->setWidth(300);
		labelBuff->setHeight(150);
		labelBuff->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
		this->addChild(labelBuff, 100);
	}
}

void PointInfo::addTouchEventListener()
{
	listener = EventListenerTouchOneByOne::create();				/* 创建一个事件监听器 OneByOne 为单点触摸 */
	listener->setSwallowTouches(false);								/* 设置是否吞没事件，在 onTouchBegan 方法返回 true 时吞没*/

	listener->onTouchBegan = CC_CALLBACK_2(PointInfo::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(PointInfo::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(PointInfo::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

bool PointInfo::onTouchBegan(Touch *touch, Event *unused_event)
{
	if (NULL != _piImg)
	{
		auto pt = touch->getLocation();
		auto rc = _piImg->getBoundingBox();
		if (false == rc.containsPoint(pt))
		{
			((FightPoints *)(this->getParent()))->removeGoods();
			this->removeFromParentAndCleanup(true);
		}
	}
	return true;
}

void PointInfo::onTouchMoved(Touch *touch, Event *unused_event)
{
}

void PointInfo::onTouchEnded(Touch *touch, Event *unused_event)
{
}