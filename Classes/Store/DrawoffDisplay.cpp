#include "DrawoffDisplay.h"
#include "Public/EffectAction.h"
#include "UserInfo/Define_Info.h"

DrawoffDiaplay::DrawoffDiaplay()
{
	index = 0;
	drawState = DrawNone;
}

DrawoffDiaplay::~DrawoffDiaplay()
{

}

Scene* DrawoffDiaplay::scene()
{
	auto scene = Scene::create();
	scene->addChild(DrawoffDiaplay::create());
	return scene;
}

bool DrawoffDiaplay::init()
{
	intFor = 0;

	pFontChina = FontChina::getInstance();
	pFontChina->initStringXml();

	auto generalUI = GUIReader::getInstance()->widgetFromJsonFile("ShowGoods.ExportJson");
	this->addChild(generalUI, -2);

	closeClick = dynamic_cast<Button *>(Helper::seekWidgetByName(generalUI, "Confirm_Button"));
	closeClick->addTouchEventListener(this, toucheventselector(DrawoffDiaplay::close));
	closeClick->setVisible(false);
	closeClick->setTouchEnabled(false);


	drawoffGoodsVector.clear();
	drawoffGoodsVector = DataManager::getInstance()->drawoffGoodsVectorForDis;

	localEquipVector = DataManager::getInstance()->localEquipProptyVector();
	if (localEquipVector.size() == 0)
	{
		DataManager::getInstance()->equipDataParser();
		localEquipVector = DataManager::getInstance()->localEquipProptyVector();
	}

	localDrawoffIDVector = DataManager::getInstance()->localDrawoffIDVector();
	if (localDrawoffIDVector.size() == 0)
	{
		DataManager::getInstance()->DrawoffIDDataParser();
		localDrawoffIDVector = DataManager::getInstance()->localDrawoffIDVector();
	}

	localPropVector = DataManager::getInstance()->localPropProptyVector();
	if (localPropVector.size() == 0)
	{
		DataManager::getInstance()->propDataParser();
		localPropVector = DataManager::getInstance()->localPropProptyVector();
	}

	localGeneralVector = DataManager::getInstance()->localGeneralProptyVector();
	if (localGeneralVector.size() == 0)
	{
		DataManager::getInstance()->generalDataParser();
		localGeneralVector = DataManager::getInstance()->localGeneralProptyVector();
	}	
	
	showSprite();

	DataManager::getInstance()->drawoffGoodsVectorForDis.clear();

	return true;
}

void DrawoffDiaplay::createTeach()
{

}

void DrawoffDiaplay::showSpriteCallBack(Node* pSender, void* targat )
{	
	
}

void DrawoffDiaplay::showSprite()
{
	__String* stringPhotoName;
	intFor = 0;
	
	for (unsigned int i = 0; i < drawoffGoodsVector.size(); i ++)
	{
		if (intFor != 0)							// 当抽卡显示完成后开始下一次循环
			continue;
		intFor ++;		
		if (index >= 10)
		{
			return;
		}
		auto sprite2 = Sprite::create();
		sprite2->setPosition(Point(400, 880));
		this->addChild(sprite2, 10);
		nameLabel = Label::create();		
		sprite2->addChild(nameLabel, 10);
		nameLabel->setSystemFontSize(16.0f);
		nameLabel->setPosition(Point( 50, -15 ));

		if (drawoffGoodsVector[ index ].goodsType == GoodsProp)						// 道具
		{
			stringPhotoName = __String::createWithFormat("%d.png", localPropVector.at( localDrawoffIDVector[ drawoffGoodsVector[ index ].goodsID - 90001 ].wID - 93001 ).pID);
			sprite2->setSpriteFrame( stringPhotoName->getCString() );		
			sprite2->setScale(95.0f / 95.0f);
			nameLabel->setString(localPropVector[ localDrawoffIDVector[ drawoffGoodsVector[ index ].goodsID - 90001 ].wID - 93001 ].pChinaName);
		}
		else if (drawoffGoodsVector[ index ].goodsType == GoodsEquip)				// 装备
		{
			stringPhotoName = __String::createWithFormat("%d.png", localEquipVector.at( localDrawoffIDVector[ drawoffGoodsVector[ index ].goodsID - 90001 ].wID - 94001 ).eID);
			sprite2->setSpriteFrame( stringPhotoName->getCString() );
			sprite2->setScale(95.0f / 140.0f);
			nameLabel->setString(localEquipVector[ localDrawoffIDVector[ drawoffGoodsVector[ index ].goodsID - 90001 ].wID - 94001 ].eChinaName);
		}
		else if (drawoffGoodsVector[ index ].goodsType == GoodsChip)
		{
			if (drawoffGoodsVector[ index ].goodsID >= 90035)						// 装备碎片		
			{
				stringPhotoName = __String::createWithFormat("%d.png", localEquipVector.at( localDrawoffIDVector[ drawoffGoodsVector[ index ].goodsID - 90001 ].wID - 94001 ).eID);
				sprite2->setSpriteFrame( stringPhotoName->getCString() );
				sprite2->setScale(95.0f / 140.0f);
				auto nameString = __String::createWithFormat("%s%s", localEquipVector[ localDrawoffIDVector[ drawoffGoodsVector[ index ].goodsID - 90001 ].wID - 94001 ].eChinaName, 
					pFontChina->getComString("ChipPrompt")->getCString());
				nameLabel->setString(nameString->getCString());
			}
			else
			{
				// 武将碎片
				stringPhotoName = __String::createWithFormat("%s.png", localGeneralVector.at( localDrawoffIDVector[ drawoffGoodsVector[ index ].goodsID - 90001 ].wID - 10001 ).chinaSmallName);
				sprite2->setSpriteFrame( stringPhotoName->getCString() );
				sprite2->setScale(95.0f / 95.0f);
				auto nameString = __String::createWithFormat("%s%s", localGeneralVector[ localDrawoffIDVector[ drawoffGoodsVector[ index ].goodsID - 90001 ].wID - 10001 ].chinaName, 
					pFontChina->getComString("ChipPrompt")->getCString());
				nameLabel->setString(nameString->getCString());
			}
		}
		else
		{
			// 武将
			stringPhotoName = __String::createWithFormat("%s.png", localGeneralVector.at( localDrawoffIDVector[ drawoffGoodsVector[ index ].goodsID - 90001 ].wID - 10001 ).chinaSmallName);
			sprite2->setSpriteFrame( stringPhotoName->getCString() );
			sprite2->setScale(95.0f / 95.0f);
			nameLabel->setString(localGeneralVector[ localDrawoffIDVector[ drawoffGoodsVector[ index ].goodsID - 90001 ].wID - 10001 ].chinaName);
		}

		

		if (drawoffGoodsVector.size() == 1)
		{
			closeClick->setVisible(true);
			closeClick->setTouchEnabled(true);
			if (drawoffGoodsVector[ index ].goodsType == GoodsGeneral)
			{
				auto heroRole = RoleCreate::create(localGeneralVector.at( localDrawoffIDVector[ drawoffGoodsVector[ index ].goodsID - 90001 ].wID - 10001 ).chinaSmallName, RoleCreMode_Preview, 1.0f);
				
				auto layer = Layer::create();	
				layer->setPosition(Point(400, 140));
				layer->setTag(DRoleLayerFlag);
				layer->addChild(heroRole, 20);
				this->addChild(layer, 20);

				int countStar = localGeneralVector.at( localDrawoffIDVector[ drawoffGoodsVector[ index ].goodsID - 90001 ].wID - 10001 ).maxStar;
				for (int i = 0; i < countStar; i ++)
				{
					auto starDarkImage = Sprite::createWithSpriteFrameName("GeneralDetails/G_Star.png");
					starDarkImage->setPosition(Point(350 - 400 + i * 40, 110 - 140));
					layer->addChild(starDarkImage, 10);
				}

// 				auto nameLabel = Label::create();
// 				nameLabel->setString(localGeneralVector.at( localDrawoffIDVector[ drawoffGoodsVector[ index ].goodsID - 90001 ].wID - 10001 ).chinaName);
// 				nameLabel->setPosition(Point(390 - 400, 140 - 140));
// 				nameLabel->setSystemFontSize(18.0f);
// 				layer->addChild(nameLabel, 20);

				auto ef = EffectAction::getInstance();
				ef->drawoffEffect();
				ef->setPosition( Point( -400, -140 ) );
				layer->addChild(ef, 18);
			}
			else
			{
				auto moveto = MoveTo::create(0.1f, Point(400, 240));
				auto roteBy = RotateBy::create(0.2f, 360.0f);
				auto ss = ScaleTo::create(0.1f, 1.2f, 1.2f, 1.0f);
				auto sss = ScaleTo::create(0.1f, 0.8f, 0.8f, 1.0f);
				auto sequence1 = Sequence::create(moveto, roteBy, ss, sss, NULL);
				sprite2->runAction(sequence1);
			}			
		}
		else
		{
			auto moveto = MoveTo::create(0.1f, Point(160 + (index % 5) * 120, 320 - (index / 5) * 140));
			auto roteBy = RotateBy::create(0.2f, 360.0f);
			auto ss = ScaleTo::create(0.1f, 1.2f, 1.2f, 1.0f);
			auto sss = ScaleTo::create(0.1f, 1.0f, 1.0f, 1.0f);
			auto sequence1 = Sequence::create(moveto, roteBy, ss, sss, NULL);
			sprite2->runAction(sequence1);

			index ++;
			if (index >= 10)
			{
				closeClick->setVisible(true);
				closeClick->setTouchEnabled(true);
				return;
			}
			if (drawoffGoodsVector[ index ].goodsType == GoodsGeneral)
			{
				showAnim(localGeneralVector.at( localDrawoffIDVector[ drawoffGoodsVector[ index ].goodsID - 90001 ].wID - 10001 ).chinaSmallName);
			}
			else
			{
				auto sequence = Sequence::createWithTwoActions(DelayTime::create(0.6f), CallFunc::create(CC_CALLBACK_0(DrawoffDiaplay::showSprite, this)));
				sequence->setTag(ActionFlag);
				this->runAction(sequence);
			}			
		}
	}
}

void DrawoffDiaplay::showAnim(string nameString)
{	
	drawState = DrawCom;
	auto heroRole = RoleCreate::create(nameString.c_str(), RoleCreMode_Preview, 1.0f);
	
	auto layer = LayerColor::create(Color4B(0, 0, 0, 166));
	layer->setPosition(Point( 400, 140 ));
	layer->setTag(DRoleLayerFlag);
	layer->addChild(heroRole);
	this->addChild(layer, 20);

	auto starImage = Sprite::createWithSpriteFrameName("GeneralDetails/G_Star.png");
	starImage->setPosition(Point(350, 70));
	layer->addChild(starImage, 20);
	int countStar = localGeneralVector.at( localDrawoffIDVector[ drawoffGoodsVector[ index ].goodsID - 90001 ].wID - 10001 ).maxStar;
	for (int i = 0; i < countStar; i ++)
	{
		auto starDarkImage = Sprite::createWithSpriteFrameName("GeneralDetails/G_DarkStar.png");
		starDarkImage->setPosition(Point(350 + i * 40, 70));
		layer->addChild(starDarkImage, 10);
	}

	auto nameLabel = Label::create();
	nameLabel->setString(localGeneralVector.at( localDrawoffIDVector[ drawoffGoodsVector[ index ].goodsID - 90001 ].wID - 10001 ).chinaName);
	nameLabel->setPosition(Point(390, 100));
	nameLabel->setSystemFontSize(18.0f);
	layer->addChild(nameLabel, 20);
	if (drawoffGoodsVector.size() != 1)
	{
		auto sequence = Sequence::createWithTwoActions(DelayTime::create(1.5f), CallFunc::create(CC_CALLBACK_0(DrawoffDiaplay::layerRoleClose, this)));
		sequence->setTag(ActionFlag);
		this->runAction(sequence);
	}	
}

void DrawoffDiaplay::layerRoleClose()
{	
	if (drawState == DrawCom)
	{
		this->stopActionByTag(ActionFlag);
		this->removeChildByTag(DRoleLayerFlag);
		if (drawoffGoodsVector.size() != 1)
		{
			auto sequence = Sequence::createWithTwoActions(DelayTime::create(0.2f), CallFunc::create(CC_CALLBACK_0(DrawoffDiaplay::showSprite, this)));
			sequence->setTag(ActionFlag);
			this->runAction(sequence);
		}
		drawState = DrawNone;
	}	
}

void DrawoffDiaplay::close(Ref* pSender, TouchEventType type)
{
	if ( type == TOUCH_EVENT_ENDED )
	{
		ToolFunc::playEffectFile( Click );
		Director::getInstance()->popScene();
	}
}

void DrawoffDiaplay::onEnter()
{
	Scene::onEnter();
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(false);
	listener->onTouchBegan = CC_CALLBACK_2(DrawoffDiaplay::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void DrawoffDiaplay::onExit()
{
	Scene::onExit();
}

bool DrawoffDiaplay::onTouchBegan(Touch *touch, Event *unused_event)
{
	if (drawState == DrawCom)
	{
		layerRoleClose();
	}
	return true;
}