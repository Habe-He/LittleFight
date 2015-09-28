#include "StateBarNode.h"
#include "ConfirmationBox/ConfirmationBox.h"

const int diamondVaule = 10;
const int coinVaule = 10000;

StateBarNode* StateBarNode::getInstance(StateChange stateChange)
{
	auto stateBar = new StateBarNode();
	if (stateBar)
	{
		stateBar->autorelease();
		stateBar->init(stateChange);
	}
	else
	{
		CC_SAFE_DELETE(stateBar);
		stateBar = NULL;
	}
	return stateBar;
}

bool StateBarNode::init(StateChange stateChange)
{
	i_Flag = 0;					// 未弹出

	localCPVector = DataManager::getInstance()->localBuyCPVector();
	if (localCPVector.size() == 0)
	{
		DataManager::getInstance()->BuyCoinAndPower();
		localCPVector = DataManager::getInstance()->localBuyCPVector();
	}

	stateBarLayout = GUIReader::getInstance()->widgetFromJsonFile("StatusBarPanel.ExportJson");
	this->addChild(stateBarLayout, -2);

	auto bg3 = dynamic_cast<ImageView* >(Helper::seekWidgetByName(stateBarLayout, "Image_3"));
	bg3->setVisible(false);
	auto bg33 = dynamic_cast<ImageView* >(Helper::seekWidgetByName(stateBarLayout, "Power_Image"));
	bg33->setVisible(false);

	auto addCoinButton = dynamic_cast<ImageView *>(Helper::seekWidgetByName(stateBarLayout, "Image_1"));								// 购买金币
	addCoinButton->setTouchEnabled(true);
	addCoinButton->addTouchEventListener(this, toucheventselector(StateBarNode::addCoinClick));	

	auto addDiamondButton = dynamic_cast<ImageView *>(Helper::seekWidgetByName(stateBarLayout, "Image_2"));							// 购买钻石
	addDiamondButton->setTouchEnabled(true);
	addDiamondButton->addTouchEventListener(this, toucheventselector(StateBarNode::addDiamondClick));

	mpFontChina = FontChina::getInstance();
	mpFontChina->initStringXml();

	return true;
}

void StateBarNode::addCoinClick(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		ToolFunc::playEffectFile( Click );
		
		i_Flag = 1;

		auto layerColor = LayerColor::create(Color4B(0, 0, 0, 166));
		layerColor->setPosition(Point( -this->getPositionX(), -this->getPositionY()));
		layerColor->setTag(STLayerColorFlag);
		this->addChild(layerColor, -1);
		auto diamondCoin = GUIReader::getInstance()->widgetFromJsonFile("DiamondtoCoin.ExportJson");
		diamondCoin->setAnchorPoint(Point::ANCHOR_MIDDLE);
		diamondCoin->setPosition(Point(400, 240 ));
		diamondCoin->setTag(STLayerChildFlag);
		diamondCoin->setScale(0.0f);
		layerColor->addChild(diamondCoin, 10);

		auto scm = ScaleTo::create(0.4f, 1.0f, 1.0f, 1.0f);
		diamondCoin->runAction(scm);

		auto diamondString = __String::createWithFormat("%d", diamondVaule);
		auto diamondLabel = dynamic_cast<Text* >(Helper::seekWidgetByName(diamondCoin, "Label_DtPDiamond"));
		diamondLabel->setText(diamondString->getCString());

		auto coinString = __String::createWithFormat("%d", coinVaule);
		auto coinLabel = dynamic_cast<Text* >(Helper::seekWidgetByName(diamondCoin, "Label_DtCoin"));
		coinLabel->setText(coinString->getCString());

		auto exchange = dynamic_cast<Button* >(Helper::seekWidgetByName(diamondCoin, "Button_ConSure"));
		exchange->addTouchEventListener(this, toucheventselector(StateBarNode::exchangeClick));
	}
}

void StateBarNode::addDiamondClick(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		ToolFunc::playEffectFile( Click );
		DataManager::getInstance()->isGetTeamInfo();					/* 当前战队等级 */
		auto teamInfo = DataManager::getInstance()->interTeamInfoVector();
		if (teamInfo[ 0 ].teamLevel <= 5)
		{
			auto label = Label::create();
			label->setPosition(Point(300, 0));
			label->setSystemFontSize(16 + 6);
			label->setColor(Color3B::BLACK);
			label->setTag(901);
			label->setString(FontChina::getInstance()->getComString("LOL")->getCString());
			this->addChild(label, 100);

			auto moveto = MoveTo::create(0.5f, Point(300, -240));
			auto delay = DelayTime::create(0.5f);
			auto fadeout = FadeOut::create(0.5f);
			auto moveto2 = MoveTo::create(0.5f, Point(300, 480));
			auto callBack = CallFunc::create(CC_CALLBACK_0(StateBarNode::showTipsCallBack, this));
			auto se = Sequence::create(moveto, delay, Spawn::create(fadeout, moveto2, NULL), callBack, NULL);
			label->runAction(se);
		}
		else
		{			
			Director::getInstance()->pushScene(VIPPay::create());
		}
	}
}

void StateBarNode::exchangeClick(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{		
		ToolFunc::playEffectFile( Click );
		if ( diamondVaule <= interPlayerInfoVector[ 0 ].diamondValue )
		{
			if (DataManager::getInstance()->isBuyCoin(diamondVaule, coinVaule))
			{
				// 购买成功
				i_Flag = 0;
				this->removeChildByTag(STLayerColorFlag);
				refreshVaule();
			}
		}
		else
		{
			auto notice = PromptBox::getInstance(FontChina::getInstance()->getComString("Loading16")->getCString());
			notice->setFade();
			this->addChild(notice);
			i_Flag = 0;
			this->removeChildByTag(STLayerColorFlag);
		}
	}
}

void StateBarNode::refreshVaule()
{
	if (DataManager::getInstance()->isGetPlayerInfo())
	{
		interPlayerInfoVector.clear();
		interPlayerInfoVector = DataManager::getInstance()->interPlayerInfoVector();
		auto coinString = __String::createWithFormat("%d", interPlayerInfoVector[ 0 ].coinValue);
		auto diamondString = __String::createWithFormat("%d", interPlayerInfoVector[ 0 ].diamondValue);
		auto coinLabel = dynamic_cast<Text* >(Helper::seekWidgetByName(stateBarLayout, "Label_Coin"));
		auto diamondLabel = dynamic_cast<Text* >(Helper::seekWidgetByName(stateBarLayout, "Label_Diamond"));
		auto powerLabel = dynamic_cast<Text* >(Helper::seekWidgetByName(stateBarLayout, "Label_Power"));
		coinLabel->setText(coinString->getCString());
		diamondLabel->setText(diamondString->getCString());
	}
}

void StateBarNode::onEnter()
{
	Node::onEnter();
	listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(false);
	listener->onTouchBegan = CC_CALLBACK_2(StateBarNode::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	refreshVaule();
}

void StateBarNode::onExit()
{
	Node::onExit();
}

bool StateBarNode::onTouchBegan(Touch *touch, Event *unused_event)
{
	if ( i_Flag )
	{
		auto layer = (Layer* )this->getChildByTag(STLayerColorFlag);
		auto layerChild = (Layout* )layer->getChildByTag(STLayerChildFlag);
		auto ss = (ImageView*)layerChild->getChildByName("Image_DtPBG");
		auto size = Rect( ss->getPositionX() - ss->getContentSize().width / 2, ss->getPositionY() - ss->getContentSize().height / 2, ss->getContentSize().width, ss->getContentSize().height);
		if (!size.containsPoint(touch->getLocation()))
		{
			listener->setSwallowTouches(true);
			this->removeChildByTag(STLayerColorFlag);
			i_Flag = 0;
		}
	}	
	else
	{
		listener->setSwallowTouches(false);
	}
	return true;
}

void StateBarNode::showTipsCallBack()
{
	this->removeChildByTag(901);
}