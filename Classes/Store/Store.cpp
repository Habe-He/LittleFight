#include "Store.h"
#include "NewComer/NewComer.h"

const int CoinTen = 9000;
const int Diamond = 150;
const int DiamondTen = 1200;

Store::Store()
{
	
}

Store::~Store()
{
}

void Store::onEnter()
{
	Scene::onEnter();
	coinTenButton->setTouchEnabled(true);
	diamondButton->setTouchEnabled(true);
	diamondTenButton->setTouchEnabled(true);
}

void Store::onExit()
{
	Scene::onExit();
}

bool Store::init()
{	
	auto stateBarNode = StateBarNode::getInstance(StatePower);
	stateBarNode->setAnchorPoint(Point::ANCHOR_MIDDLE);
	stateBarNode->setPosition(Point(140, 420));
	this->addChild(stateBarNode, 10, StateBarFlag);

	auto storeSceneUI = GUIReader::getInstance()->widgetFromJsonFile("Drawoff.ExportJson");
	storeSceneUI->setTag(99);
	this->addChild(storeSceneUI);	

	drawoffPanel = dynamic_cast<Layout* >(Helper::seekWidgetByName(storeSceneUI, "Panel_Drawoff"));

	coinLabel = dynamic_cast<Text* >(Helper::seekWidgetByName(drawoffPanel, "Label_StoreTime1"));
	diamondLabel = dynamic_cast<Text* >(Helper::seekWidgetByName(drawoffPanel, "Label_StoreTime2"));
	
	btnClose = dynamic_cast<Button* >(Helper::seekWidgetByName(storeSceneUI, "Button_Close"));							// 关闭按钮
	btnClose->addTouchEventListener(this, toucheventselector(Store::closeBtn));		
	
	coinTenButton = dynamic_cast<Button* >(drawoffPanel->getChildByName("Button_SSbuy1"));								// 金币十抽
	coinTenButton->addTouchEventListener(this, toucheventselector(Store::coinDrawoffTenButton));
	
	diamondButton = dynamic_cast<Button* >(Helper::seekWidgetByName(drawoffPanel, "Button_SSbuy2"));						// 钻石抽
	diamondButton->addTouchEventListener(this, toucheventselector(Store::diamondDrawoffButton));
	
	diamondTenButton = dynamic_cast<Button* >(Helper::seekWidgetByName(drawoffPanel, "Button_SSbuy3"));					// 钻石十抽
	diamondTenButton->addTouchEventListener(this, toucheventselector(Store::diamondDrawoffTenButton));

	initData();

	createTeachNode();
		
	return true;
}

void Store::initData()
{
	if ( DataManager::getInstance()->isGetPlayerInfo() )
	{
		interPlayerInfoVector = DataManager::getInstance()->interPlayerInfoVector();
	}

	pFontChina = FontChina::getInstance();
	pFontChina->initStringXml();

	localDrawoffVector = DataManager::getInstance()->localDrawoffVector();
	if (localDrawoffVector.size() == 0)
	{
		DataManager::getInstance()->DrawoffDataParser();
		localDrawoffVector = DataManager::getInstance()->localDrawoffVector();
	}
}

void Store::createTeachNode()
{
	if (false == NewComer::isGuideDone(1002))						/* 引导ID为2，且未完成 */
	{
		_comer = NewComer::create(this, 1002, 1);
	}
	else
	{
		_comer = NULL;
	}
}

void Store::closeBtn(Ref* pSender, TouchEventType type)
{
	if ( TouchEventType::TOUCH_EVENT_ENDED == type )
	{
		auto button = (Button*)pSender;
		button->setTouchEnabled(false);
		ToolFunc::playEffectFile( Click );

		if (false == NewComer::isGuideDone(1002))					/* 引导ID为0，且未完成 */
		{
			if (2 != NewComer::getCurGuideStep())					/* 值为3，表示已抽卡 */
			{
				NewComer::setCurGuideStep(-1);
			}
		}

		Director::getInstance()->replaceScene(MainScene::scene());
	}
}

void Store::coinDrawoffTenButton(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		ToolFunc::playEffectFile( Click );
		coinTenButton->setTouchEnabled(false);
		if ( DataManager::getInstance()->isGetMaidanCount() >= 30 )
		{
			coinTenButton->setTouchEnabled(true);
			auto promp = PromptBox::getInstance(pFontChina->getComString("Plus1050")->getCString());
			promp->setFade();
			this->addChild(promp, 100);
			return;
		}
		if ( DataManager::getInstance()->isSortWNum() )
		{
			interWareroomGridVector = DataManager::getInstance()->interWareroomVector();
		}
		if ( ( interWareroomGridVector[ 0 ].chipGridNum >= 5 ) && ( interWareroomGridVector[ 0 ].equipGridNum >= 5 ) )
		{
			interPlayerInfoVector = DataManager::getInstance()->interPlayerInfoVector();
			auto starBarNode =  (StateBarNode*)this->getChildByTag(StateBarFlag);
			starBarNode->refreshVaule();
			if (interPlayerInfoVector[ 0 ].coinValue >= CoinTen)
			{
				vector<DrawoffGoodsStruct > tempVector;
				for (int i = 0; i < 10; i ++)
				{		
					tempVector.push_back( _coinDrawoffGoodsVector( ToolFunc::calcRandom(1, 10000) ) );
				}
				if ( DataManager::getInstance()->isDrawoffCard(CoinTen, 0, 1, 0, tempVector) )
				{
					DataManager::getInstance()->drawoffGoodsVectorForDis = tempVector;
					interPlayerInfoVector = DataManager::getInstance()->interPlayerInfoVector();
					starBarNode->refreshVaule();
					Director::getInstance()->pushScene(DrawoffDiaplay::scene());				
				}
			}
			else
			{
				coinTenButton->setTouchEnabled(true);
				auto promp = PromptBox::getInstance(pFontChina->getComString("NoCoin")->getCString());
				promp->setFade();
				this->addChild(promp, 100);
			}
		}
		else
		{
			coinTenButton->setTouchEnabled(true);
			// 仓库的格子不够用了，去购买写鸽子吧。
			auto promp = PromptBox::getInstance(pFontChina->getComString("Plus315")->getCString());
			promp->setFade();
			this->addChild(promp, 100);
		}
	}	
}

void Store::diamondDrawoffButton(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		if (false == NewComer::isGuideDone(1002))					/* 引导ID为0，且未完成 */
		{
			if (1 == NewComer::getCurGuideStep())
			{
				NewComer::setCurGuideStep();
				_comer->removeFromParentAndCleanup(true);

				vector<DrawoffGoodsStruct > tempVector ;
				tempVector.clear();
				interPlayerInfoVector = DataManager::getInstance()->interPlayerInfoVector();
				auto starBarNode =  (StateBarNode*)this->getChildByTag(StateBarFlag);
				starBarNode->refreshVaule();
				
				DrawoffGoodsStruct structDrawoff;
				memset(&structDrawoff, 0, sizeof(structDrawoff));
				structDrawoff.goodsID = 90018;
				structDrawoff.goodsType = GoodsGeneral;
				tempVector.push_back(structDrawoff);
				if ( DataManager::getInstance()->isDrawoffCard(0, 0, 0, 1, tempVector) )
				{
					DataManager::getInstance()->drawoffGoodsVectorForDis = tempVector;
					((StateBarNode*)this->getChildByTag(StateBarFlag))->getInstance(StatePower)->refreshVaule();
					interPlayerInfoVector = DataManager::getInstance()->interPlayerInfoVector();
					starBarNode->refreshVaule();
					Director::getInstance()->pushScene(DrawoffDiaplay::scene());
				}
			}
		}
		else
		{
			// 不是在引导过程
			diamondButton->setTouchEnabled(false);
			if ( DataManager::getInstance()->isGetMaidanCount() >= 40 )
			{
				diamondButton->setTouchEnabled(true);
				auto promp = PromptBox::getInstance(pFontChina->getComString("Plus1050")->getCString());
				promp->setFade();
				this->addChild(promp, 100);
				return;
			}
			if ( DataManager::getInstance()->isSortWNum() )
			{
				interWareroomGridVector = DataManager::getInstance()->interWareroomVector();
			}
			if ( ( interWareroomGridVector[ 0 ].chipGridNum >= 1 ) && ( interWareroomGridVector[ 0 ].equipGridNum >= 1 ) )
			{
				vector<DrawoffGoodsStruct > tempVector ;
				tempVector.clear();
				interPlayerInfoVector = DataManager::getInstance()->interPlayerInfoVector();
				auto starBarNode =  (StateBarNode*)this->getChildByTag(StateBarFlag);
				starBarNode->refreshVaule();
				if (interPlayerInfoVector[ 0 ].diamondValue >= Diamond)
				{
					tempVector.push_back( _diamondDrawoffGoodStruct(ToolFunc::calcRandom(1, 10000) ) );		
					if ( DataManager::getInstance()->isDrawoffCard(0, Diamond, 0, 1, tempVector) )
					{
						DataManager::getInstance()->drawoffGoodsVectorForDis = tempVector;
						((StateBarNode*)this->getChildByTag(StateBarFlag))->getInstance(StatePower)->refreshVaule();
						interPlayerInfoVector = DataManager::getInstance()->interPlayerInfoVector();
						starBarNode->refreshVaule();
						Director::getInstance()->pushScene(DrawoffDiaplay::scene());
					}
				}	
				else
				{
					diamondButton->setTouchEnabled(true);
					auto promptLayer = ConfirmationBox::getInstance(StateNoDiamond);
					this->addChild(promptLayer, 20);
				}
			}
			else
			{
				diamondButton->setTouchEnabled(true);
				// 仓库的格子不够用了，去购买写鸽子吧。
				auto promp = PromptBox::getInstance(pFontChina->getComString("Plus315")->getCString());
				promp->setFade();
				this->addChild(promp, 100);
			}	
		}

		ToolFunc::playEffectFile( Click );		
	}
}

void Store::diamondDrawoffTenButton(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		ToolFunc::playEffectFile( Click );
		diamondTenButton->setTouchEnabled(false);
		if ( DataManager::getInstance()->isGetMaidanCount() >= 30 )
		{
			diamondTenButton->setTouchEnabled(true);
			auto promp = PromptBox::getInstance(pFontChina->getComString("Plus1050")->getCString());
			promp->setFade();
			this->addChild(promp, 100);
			return;
		}
		if ( DataManager::getInstance()->isSortWNum() )
		{
			interWareroomGridVector = DataManager::getInstance()->interWareroomVector();
		}
		if ( ( interWareroomGridVector[ 0 ].chipGridNum >= 5 ) && ( interWareroomGridVector[ 0 ].equipGridNum >= 5 ) )
		{
			vector<DrawoffGoodsStruct > tempVector ;
			tempVector.clear();
			interPlayerInfoVector = DataManager::getInstance()->interPlayerInfoVector();
			auto starBarNode =  (StateBarNode*)this->getChildByTag(StateBarFlag);
			starBarNode->refreshVaule();
			if (interPlayerInfoVector[ 0 ].diamondValue >= DiamondTen)
			{			
				if (UserData::getInstance()->getDiamondDraw() == NULL)					// 第一次钻石十连抽，送五星武将
				{

					for (int i = 0; i < 9; i ++)
					{
						tempVector.push_back( _diamondDrawoffGoodStruct(ToolFunc::calcRandom(1, 10000) ) );
					}
					DrawoffGoodsStruct drawoff;
					memset(&drawoff, 0, sizeof(drawoff));
					drawoff.goodsType = GoodsGeneral;
					drawoff.goodsID = ToolFunc::calcRandom(90001, 90013);
					tempVector.push_back( drawoff );
					if ( DataManager::getInstance()->isDrawoffCard(0, DiamondTen, 0, 1, tempVector) )
					{
						DataManager::getInstance()->drawoffGoodsVectorForDis = tempVector;
						((StateBarNode*)this->getChildByTag(StateBarFlag))->getInstance(StatePower)->refreshVaule();
						interPlayerInfoVector = DataManager::getInstance()->interPlayerInfoVector();
						starBarNode->refreshVaule();
						Director::getInstance()->pushScene(DrawoffDiaplay::scene());

						UserData::getInstance()->saveDiamondDraw(1);
					}
				}
				else
				{
					for (int i = 0; i < 10; i ++)
					{
						tempVector.push_back( _diamondDrawoffGoodStruct(ToolFunc::calcRandom(1, 10000) ) );
					}
					if ( DataManager::getInstance()->isDrawoffCard(0, DiamondTen, 0, 1, tempVector) )
					{
						DataManager::getInstance()->drawoffGoodsVectorForDis = tempVector;
						((StateBarNode*)this->getChildByTag(StateBarFlag))->getInstance(StatePower)->refreshVaule();
						interPlayerInfoVector = DataManager::getInstance()->interPlayerInfoVector();
						starBarNode->refreshVaule();
						Director::getInstance()->pushScene(DrawoffDiaplay::scene());
					}
				}			
			}	
			else
			{
				diamondTenButton->setTouchEnabled(true);
				auto promptLayer = ConfirmationBox::getInstance(StateNoDiamond);
				this->addChild(promptLayer, 20);
			}	
		}	
		else
		{
			diamondTenButton->setTouchEnabled(true);
			// 仓库的格子不够用了，去购买写鸽子吧。
			auto promp = PromptBox::getInstance(pFontChina->getComString("Plus315")->getCString());
			promp->setFade();
			this->addChild(promp, 100);
		}
	}
}

DrawoffGoodsStruct Store::_coinDrawoffGoodsVector(int id)
{
	DrawoffGoodsStruct drawoff;
	memset(&drawoff, 0, sizeof(drawoff));	
	for (unsigned int i = 0; i < localDrawoffVector.size(); i ++)
	{
		vector<string > coinRangeVector = DataManager::getInstance()->splitString(localDrawoffVector.at( i ).coinRange, "-");
		vector<string > idRangeVector = DataManager::getInstance()->splitString(localDrawoffVector.at( i ).idRange, "-");
		if ( ( id >= atoi(coinRangeVector.at( 0 ).c_str()) ) && ( id <= atoi(coinRangeVector.at( 1 ).c_str()) ) )
		{
			drawoff.goodsType = GoodsTypeEnum(localDrawoffVector.at( i ).goodsType);
			drawoff.goodsID = ToolFunc::calcRandom( atoi(idRangeVector.at( 0 ).c_str()), atoi(idRangeVector.at( 1 ).c_str()) );
		}
	}
	return drawoff;
}

DrawoffGoodsStruct Store::_diamondDrawoffGoodStruct(int id)
{
	DrawoffGoodsStruct drawoff;
	memset(&drawoff, 0, sizeof(drawoff));	
	for (unsigned int i = 0; i < localDrawoffVector.size(); i ++)
	{
		vector<string > diamonRangeVector = DataManager::getInstance()->splitString(localDrawoffVector.at( i ).diamonRange, "-");
		vector<string > idRangeVector = DataManager::getInstance()->splitString(localDrawoffVector.at( i ).idRange, "-");
		if ( ( id >= atoi(diamonRangeVector.at( 0 ).c_str()) ) && ( id <= atoi(diamonRangeVector.at( 1 ).c_str()) ) )
		{
			drawoff.goodsType = GoodsTypeEnum(localDrawoffVector.at( i ).goodsType);
			drawoff.goodsID = ToolFunc::calcRandom( atoi(idRangeVector.at( 0 ).c_str()), atoi(idRangeVector.at( 1 ).c_str()) );
		}
	}
	return drawoff;	
}