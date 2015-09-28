#include "StoreB.h"
#include "Scene/MainScene.h"
#include "StateBar/StateBarNode.h"

const int TipsFlag = 10;
const int StFlag = 12;

StoreB::StoreB()
{
	stPanel = NoState;
}

StoreB::~StoreB()
{

}

bool StoreB::init()
{
	auto stateBarNode = StateBarNode::getInstance(StatePower);
	stateBarNode->setAnchorPoint(Point::ANCHOR_MIDDLE);
	stateBarNode->setPosition(Point(140, 420));
	this->addChild(stateBarNode, 20, StFlag);
	
	mpFontChina = FontChina::getInstance();
	mpFontChina->initStringXml();

	auto storeSceneUI = GUIReader::getInstance()->widgetFromJsonFile("Store.ExportJson");
	storeSceneUI->setTag(99);
	this->addChild(storeSceneUI, -1);	

	auto btnClose = dynamic_cast<Button* >(Helper::seekWidgetByName(storeSceneUI, "Button_Close"));							// 关闭按钮
	btnClose->addTouchEventListener(this, toucheventselector(StoreB::closeButton));	

	auto diamondButton = dynamic_cast<Button* >(Helper::seekWidgetByName(storeSceneUI, "Button_ForDiamond"));
	diamondButton->setEnabled(false);

	initData();	

	if (false == NewComer::isGuideDone(1004))
	{
		_comer = NewComer::create(this, 1004, 1);
	}

	return true;
}

void StoreB::initData()
{
	SellGoods sellGoods;
	memset(&sellGoods, 0, sizeof(sellGoods));

	int i_ID[] = { 93021, 93002, 93003, 93004, 93005, 93006, 93007, 93018, 93019 };
	int i_Num[] = { 1, 1, 1, 1, 1, 1, 1, 100, 10 };
	int i_Price[] = { 5, 5, 9, 18, 10, 15, 25, 30, 6 };

	for (int i = 0; i < 9; i ++)
	{
		sellGoods.goodsID = i_ID[ i ];
		sellGoods.goodsNum = i_Num[ i ];
		sellGoods.goodsPrice = i_Price[ i ];
		sellGoodsVector.push_back(sellGoods);
	}

	auto mainPanel = (Layout* )this->getChildByTag( 99 );
	auto sPanel = (cocos2d::ui::ScrollView* )mainPanel->getChildByName("ScrollView_Mys");
	auto dPanel = (Layout* )sPanel->getChildByName("Panel_Mys");

	for (int i = 0; i < 9; i ++)
	{
		auto gString = __String::createWithFormat("Panel_%d", i + 1);
		auto gPanel = dynamic_cast<Layout* >(Helper::seekWidgetByName(dPanel, gString->getCString()));
		gPanel->setTag( i );
		gPanel->addTouchEventListener(this, toucheventselector(StoreB::dButton));

		auto gNameString = __String::createWithFormat("%d.png", sellGoodsVector[ i ].goodsID);
		auto gIM = dynamic_cast<ImageView* >(Helper::seekWidgetByName(gPanel, "Image_Goods"));
		gIM->setScale( 0.8f ); 
		gIM->loadTexture(gNameString->getCString(), UI_TEX_TYPE_PLIST);

		auto gNumString = __String::createWithFormat("%d", sellGoodsVector[ i ].goodsNum);
		auto gNum = dynamic_cast<Text* >(Helper::seekWidgetByName(gPanel, "Label_Num"));
		gNum->setText(gNumString->getCString());

		auto gPriceString = __String::createWithFormat("%d", sellGoodsVector[ i ].goodsPrice);
		auto gPrice = dynamic_cast<Text* >(Helper::seekWidgetByName(gPanel, "Label_Coin"));
		gPrice->setText(gPriceString->getCString());
	}
}

void StoreB::dButton(Ref* pSender, TouchEventType type)
{
	if ( type == TOUCH_EVENT_ENDED )
	{
		ToolFunc::playEffectFile( Click );
		int tagFlag = ((Button*)pSender)->getTag();
		stPanel = TipsState;

		if (1 == tagFlag)
		{
			if (false == NewComer::isGuideDone(1004))
			{
				if (1 == NewComer::getCurGuideStep())
				{
					NewComer::setCurGuideStep();
					_comer->removeFromParentAndCleanup(true);
					_comer = NewComer::create(this, 1004, 2);
				}
			}
		}

		auto confirmTips = GUIReader::getInstance()->widgetFromJsonFile("Confirm.ExportJson");
		confirmTips->setPosition(Point(400 - confirmTips->getContentSize().width / 2, 240 - confirmTips->getContentSize().height / 2));
		confirmTips->setTag(TipsFlag);
		this->addChild(confirmTips, 10);

		auto btnClose = dynamic_cast<Button* >(Helper::seekWidgetByName(confirmTips, "Confirm_Button"));							// 确定
		btnClose->setTag(tagFlag);
		btnClose->addTouchEventListener(this, toucheventselector(StoreB::comfirmButton));	

		auto btnClose2 = dynamic_cast<Button* >(Helper::seekWidgetByName(confirmTips, "Cancel_Button"));							// 取消
		btnClose2->addTouchEventListener(this, toucheventselector(StoreB::cancleButton));	

		// 是否花费
		auto label0 = dynamic_cast< Text* >(Helper::seekWidgetByName(confirmTips, "Des_Label"));
		label0->setColor(Color3B(0, 0, 0));
		label0->setText(mpFontChina->getComString("Plus630")->getCString());
		// X 
		auto label1 = Label::create();
		label1->setAnchorPoint( Point( 0, 1 ) );
		label1->setColor(Color3B(0, 0, 0));
		label1->setSystemFontSize(20.0f);
		label1->setPosition( Point( label0->getPositionX() + label0->getContentSize().width + 5, label0->getPositionY() ) );
		auto string1 = __String::createWithFormat("%d", sellGoodsVector[ tagFlag ].goodsPrice );
		label1->setString(string1->getCString());
		confirmTips->addChild(label1, 10);

		// 钻石
		auto label2 = Label::create();
		label2->setAnchorPoint( Point( 0, 1 ) );
		label2->setSystemFontSize(20.0f);
		label2->setColor(Color3B(0, 0, 0));
		label2->setPosition( Point( label1->getPositionX() + label1->getContentSize().width + 5, label1->getPositionY() ) );
		label2->setString(mpFontChina->getComString("Plus740")->getCString());
		confirmTips->addChild(label2, 10);

		// 购买
		auto label3 = Label::create();
		label3->setAnchorPoint( Point( 0, 1 ) );
		label3->setSystemFontSize(20.0f);
		label3->setColor(Color3B(0, 0, 0));
		label3->setPosition( Point( label0->getPositionX(), label0->getPositionY() - label0->getContentSize().height - 5 ) );
		label3->setString(mpFontChina->getComString("Plus845")->getCString());
		confirmTips->addChild(label3, 10);

		auto localPropVector = DataManager::getInstance()->localPropProptyVector();
		if ( localPropVector.size() == 0 )
		{
			DataManager::getInstance()->propDataParser();
			localPropVector = DataManager::getInstance()->localPropProptyVector();
		}
		// XXXX
		auto label4 = Label::create();
		label4->setSystemFontSize(20.0f);
		label4->setColor(Color3B(0, 0, 0));
		label4->setAnchorPoint( Point( 0, 1 ) );
		label4->setPosition( Point( label3->getPositionX() + label3->getContentSize().width + 5, label3->getPositionY() ) );
		auto string4 = __String::createWithFormat("%s X", localPropVector[ sellGoodsVector[ tagFlag ].goodsID - 93001 ].pChinaName );
		label4->setString(string4->getCString());
		confirmTips->addChild(label4, 10);

		// 数目
		auto label5 = Label::create();
		label5->setSystemFontSize(20.0f);
		label5->setAnchorPoint( Point( 0, 1 ) );
		label5->setColor(Color3B(0, 0, 0));
		label5->setPosition( Point( label4->getPositionX() + label4->getContentSize().width + 5, label4->getPositionY() ) );
		auto string5 = __String::createWithFormat("%d", sellGoodsVector[ tagFlag ].goodsNum );
		label5->setString(string5->getCString());
		confirmTips->addChild(label5, 10);
	}
}

void StoreB::closeButton(Ref* pSender, TouchEventType type)
{
	if ( type == TOUCH_EVENT_ENDED )
	{
		if (false == NewComer::isGuideDone(1004))
		{
			if (1 == NewComer::getCurGuideStep())
			{
				NewComer::setCurGuideStep(-1);
			}
		}

		ToolFunc::playEffectFile( Click );
		Director::getInstance()->replaceScene(MainScene::scene());
	}
}

void StoreB::comfirmButton(Ref* pSender, TouchEventType type)
{
	if ( type == TOUCH_EVENT_ENDED )
	{
		ToolFunc::playEffectFile( Click );
		auto bFlag = ( (Button*)pSender )->getTag();

		if (1 == bFlag)
		{
			if (false == NewComer::isGuideDone(1004))
			{
				if (2 == NewComer::getCurGuideStep())
				{
					NewComer::setCurGuideStep();
					_comer->removeFromParentAndCleanup(true);
				}
			}
		}

		auto starBarNode =  (StateBarNode*)this->getChildByTag(StFlag);
		starBarNode->refreshVaule();
		interPlayerVector = DataManager::getInstance()->interPlayerInfoVector();
		if ( interPlayerVector[ 0 ].diamondValue >= sellGoodsVector[ bFlag ].goodsPrice )
		{
			if ( DataManager::getInstance()->isBuyStoreThing( sellGoodsVector[ bFlag ].goodsID, GoodsProp, sellGoodsVector[ bFlag ].goodsNum, sellGoodsVector[ bFlag ].goodsPrice ) )
			{
				starBarNode->refreshVaule();
				this->removeChildByTag(TipsFlag);
				stPanel = NoState;
				auto pro = PromptBox::getInstance(mpFontChina->getComString("successfulBuy")->getCString());
				pro->setFade();
				this->addChild(pro, 10);
			}
		}
		else
		{
			this->removeChildByTag(TipsFlag);
			auto pro = PromptBox::getInstance(mpFontChina->getComString("Loading16")->getCString());
			pro->setFade();
			this->addChild(pro, 10);
			stPanel = NoState;
		}
	}
}

void StoreB::cancleButton(Ref* pSender, TouchEventType type)
{
	if ( type == TOUCH_EVENT_ENDED )
	{
		if (false == NewComer::isGuideDone(1004))
		{
			if (2 == NewComer::getCurGuideStep())
			{
				NewComer::setCurGuideStep(-1);
				_comer->removeFromParentAndCleanup(true);
				_comer = NewComer::create(this, 1004, 1);
			}
		}

		ToolFunc::playEffectFile( Click );
		this->removeChildByTag(TipsFlag);
		stPanel = NoState;
	}
}

bool StoreB::onTouchBegan(Touch *touch, Event *unused_event)
{
	bool bRef = false;
	if ( stPanel == TipsState )
	{
		listener->setSwallowTouches(true);
		bRef = true;

		auto layerChild = (Layout* )this->getChildByTag(TipsFlag);
		auto size = layerChild->getBoundingBox();
		if (!size.containsPoint(touch->getLocation()))
		{
			this->removeChildByTag(TipsFlag);
			stPanel = NoState;
		}
	}
	else
	{
		listener->setSwallowTouches(false);
		bRef = false;
	}
	return bRef;
}

void StoreB::onEnter()
{
	Scene::onEnter();

	if ( DataManager::getInstance()->isGetPlayerInfo() )
	{
		interPlayerVector = DataManager::getInstance()->interPlayerInfoVector();
	}

	listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(false);
	listener->onTouchBegan = CC_CALLBACK_2(StoreB::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void StoreB::onExit()
{
	if (false == NewComer::isGuideDone(1004))
	{
		if (1 == NewComer::getCurGuideStep())
		{
			NewComer::setCurGuideStep(-1);
		}
	}

	Scene::onExit();
}