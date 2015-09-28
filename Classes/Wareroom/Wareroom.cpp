#include "Wareroom.h"

Scene* Wareroom::scene()
{
	Scene* scene = Scene::create();
	Wareroom* layer = Wareroom::create();
	scene->addChild(layer);
	return scene;
}

Wareroom::Wareroom():buttonIndex(0), sellIndex(0), vectorSubscript(0), wareroomState(StateNone)
{
	goodsID = 0;
}

Wareroom::~Wareroom()
{
	scrollView->removeAllChildrenWithCleanup(true);
}

bool Wareroom::init()
{
	if ( false == Layer::init() )
	{
		return false;
	} 
	mpFontChina = FontChina::getInstance();
	mpFontChina->initStringXml();

	auto wareroomUI = GUIReader::getInstance()->widgetFromJsonFile(WareroomUIRoot);
	wareroomUI->setTag(99);
	this->addChild(wareroomUI, -2);

	auto rightPanel = dynamic_cast<Layout* >(wareroomUI->getChildByName("Panel_Right"));
	rightPanel->setTag(RightPanelTag);

	auto closeButton = dynamic_cast<Button *>(Helper::seekWidgetByName(wareroomUI, "Button_Close"));
	closeButton->addTouchEventListener(this, toucheventselector(Wareroom::closeButton));

	scrollView = dynamic_cast<cocos2d::ui::ScrollView*>(Helper::seekWidgetByName(rightPanel, "WmScrollView"));

 	auto propsImage = dynamic_cast<Button*>( rightPanel->getChildByName("Button_Prop") );
	propsImage->setTag(btnPropTag);
	propsImage->addTouchEventListener(this, toucheventselector(Wareroom::createProps));

 	auto equipImage = dynamic_cast<Button*>(Helper::seekWidgetByName(rightPanel, "Button_Equip"));
	equipImage->setTag(btnEquipTag);
	equipImage->addTouchEventListener(this, toucheventselector(Wareroom::createEquip));

 	auto chipImage = dynamic_cast<Button*>(Helper::seekWidgetByName(rightPanel, "Button_Chip"));
	chipImage->setTag(btnChipTag);
	chipImage->addTouchEventListener(this, toucheventselector(Wareroom::createChip));

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Wareroom::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	sellValuePanel = dynamic_cast<Layout* >(Helper::seekWidgetByName(wareroomUI, "SellPrice"));
	sellValuePanel->setVisible(false);

	if (false == NewComer::isGuideDone(1007))					/* 引导ID为7，且未完成 */
	{
		_comer = NewComer::create(this, 1007, 2);
	}

	return true;	
}

void Wareroom::createProps(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		if (pSender != NULL)
		{
			ToolFunc::playEffectFile( Click );
		}

		if (false == NewComer::isGuideDone(1007))					/* 引导ID为7，且未完成 */
		{
			auto step = NewComer::getCurGuideStep();
			if ((2 < step) && (NULL != _comer))
			{
				_comer->removeFromParentAndCleanup(true);
				NewComer::setCurGuideStep(2 - step);
				_comer = NewComer::create(this, 1007, 2);
			}
		}
		
		if ( DataManager::getInstance()->isGetPropData() )
		{			
			setBrightButton(propBtn);
			buttonIndex = propBtn;
			scrollView->scrollToTop(0.1f, false);	
			loadFrame(propBtn);
			showInfo(0, propBtn);
			sellValuePanel->setVisible(false);
		}
	}
}

void Wareroom::createEquip(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		ToolFunc::playEffectFile( Click );

		if (false == NewComer::isGuideDone(1007))					/* 引导ID为7，且未完成 */
		{
			auto step = NewComer::getCurGuideStep();
			if ((2 < step) && (NULL != _comer))
			{
				_comer->removeFromParentAndCleanup(true);
				NewComer::setCurGuideStep(2 - step);
				_comer = NewComer::create(this, 1007, 2);
			}
		}

		if ( DataManager::getInstance()->isGetEquipData() )
		{			
			setBrightButton(equipBtn);
			scrollView->scrollToTop(0.1f, true);	
			buttonIndex = equipBtn;
			loadFrame(equipBtn);
			showInfo(0, equipBtn);
		}		
	}
}

void Wareroom::createChip(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		ToolFunc::playEffectFile( Click );

		if (false == NewComer::isGuideDone(1007))					/* 引导ID为7，且未完成 */
		{
			if (2 == NewComer::getCurGuideStep())
			{
				_comer->removeFromParentAndCleanup(true);
				NewComer::setCurGuideStep();
				_comer = NewComer::create(this, 1007, 3);
			}
		}

		if ( DataManager::getInstance()->isGetChipData() )
		{			
			setBrightButton(chipBtn);
			buttonIndex = chipBtn;
			scrollView->scrollToTop(0.1f, true);	
			loadFrame(chipBtn);
			showInfo(0, chipBtn);
			sellValuePanel->setVisible(false);
		}
	}
}
	
void Wareroom::loadFrame(int id)
{
	ImageView* imageGoods[ GridCount ];
	ImageView* imageFrame[ GridCount ];
	for (int i = 0; i < GridCount; i ++)
	{
		auto imageFrameString = __String::createWithFormat("Image_%d", i + 1);		// Image_1
		auto imageGoodsString = __String::createWithFormat("Image_%d_0", i + 1);	// Image_1_0

		imageGoods[ i ] = (ImageView*)scrollView->getChildByName(imageGoodsString->getCString());
		imageGoods[ i ]->loadTexture("Wareroom/WmGrid.png", UI_TEX_TYPE_PLIST);
		imageGoods[ i ]->setScale(1.0f);
		imageGoods[ i ]->setTag( i );
		imageGoods[ i ]->setTouchEnabled(true);
		imageGoods[ i ]->setLocalZOrder( 5 );
		imageGoods[ i ]->addTouchEventListener(this, toucheventselector(Wareroom::shift));
		
		imageFrame[ i ] = (ImageView*)scrollView->getChildByName(imageFrameString->getCString());		
		imageFrame[ i ]->loadTexture("Wareroom/WmGrid.png", TextureResType::UI_TEX_TYPE_PLIST);
		imageFrame[ i ]->setTag( i );
		imageFrame[ i ]->setScale(1.0f);		
	}
	// 移除碎片的标记
	interWareroomData = DataManager::getInstance()->interWareroomChipVector();
	for (unsigned int i = 0; i < interWareroomData.size(); i ++)
	{
		scrollView->removeChildByTag(100 + i);
	}
	interWareroomData.clear();
	tempWareroomVector.clear();
	if (id == propBtn)
	{
		interWareroomData = DataManager::getInstance()->interWareroomPropVector();
		localWareroomPropData = DataManager::getInstance()->localPropProptyVector();
		if (localWareroomPropData.size() == 0)																		// 本地道具数据解析
		{
			DataManager::getInstance()->propDataParser();
			localWareroomPropData = DataManager::getInstance()->localPropProptyVector();
		}
		
		for (unsigned int i = 0; i < interWareroomData.size(); i ++)														// 移除不符合的物品
		{
			if (interWareroomData[ i ].itemsID != 0)
			{
				tempWareroomVector.push_back(interWareroomData[ i ]);
			}		
		}
		unsigned int  count = tempWareroomVector.size();
		if (count >= 80)
		{
			count = 80;
		}
		for (unsigned int i = 0; i < count; i ++)
		{
			auto imageString = __String::createWithFormat("%d.png", localWareroomPropData[ tempWareroomVector[ i ].itemsID - 93001 ].pID);
			imageGoods[ i ]->loadTexture(imageString->getCString(), TextureResType::UI_TEX_TYPE_PLIST);	
			imageGoods[ i ]->setScale(45 / 90.0f);
		}
	}
	else if (id == equipBtn)
	{
		interWareroomData = DataManager::getInstance()->interWareroomEquipVector();
		localWarerommEquipData = DataManager::getInstance()->localEquipProptyVector();
		if (localWarerommEquipData.size() == 0)
		{
			DataManager::getInstance()->equipDataParser();
			localWarerommEquipData = DataManager::getInstance()->localEquipProptyVector();
		}
		for (unsigned int i = 0; i < interWareroomData.size(); i ++)
		{
			if ( (interWareroomData[ i ].itemsID != 0) && (interWareroomData[ i ].isSelect != 1) )
			{
				tempWareroomVector.push_back(interWareroomData[ i ]);				
			}
		}	
		for (unsigned int i = 0; i < interWareroomData[ 0 ].itemsNum; i ++)
		{
			// 加载物品的框，加载背景格子
			imageGoods[ i ]->loadTexture("Wareroom/WmGrid.png", TextureResType::UI_TEX_TYPE_PLIST);
		}
		unsigned int  count = tempWareroomVector.size();
		if (count >= 80)
		{
			count = 80;
		}
		for (unsigned int i = 0; i < count; i ++)
		{
			auto imageString = __String::createWithFormat("%d.png", localWarerommEquipData[ tempWareroomVector[ i ].itemsID - 94001 ].eID);
			imageGoods[ i ]->loadTexture(imageString->getCString(), TextureResType::UI_TEX_TYPE_PLIST);	
			imageGoods[ i ]->setScale(45 / 105.0f);
		}
	}
	else if (id == chipBtn)
	{
		interWareroomData = DataManager::getInstance()->interWareroomChipVector();
		localWarerommEquipData = DataManager::getInstance()->localEquipProptyVector();
		localWarerommGeneralData = DataManager::getInstance()->localGeneralProptyVector();
		if (localWarerommGeneralData.size() == 0)
		{
			DataManager::getInstance()->generalDataParser();
			localWarerommGeneralData = DataManager::getInstance()->localGeneralProptyVector();
		}
		if (localWarerommEquipData.size() == 0)
		{
			DataManager::getInstance()->equipDataParser();
			localWarerommEquipData = DataManager::getInstance()->localEquipProptyVector();
		}
		for (unsigned int i = 0; i < interWareroomData.size(); i ++)
		{
			if (interWareroomData[ i ].itemsID != 0)
			{
				tempWareroomVector.push_back(interWareroomData[ i ]);
			}
		}
		unsigned int  count = tempWareroomVector.size();
		if (count >= 80)
		{
			count = 80;
		}
		for (unsigned int i = 0; i < count; i ++)
		{
			auto chipCion = Sprite::create("Chip.png");
			chipCion->setPosition(Point(imageFrame[ i ]->getPosition().x - imageFrame[ i ]->getContentSize().width / 2 + 20, 
				imageFrame[ i ]->getPosition().y + imageFrame[ i ]->getContentSize().height / 2 - 20));
			chipCion->setTag( 100 + i );
			chipCion->setScale(0.8f);
			scrollView->addChild(chipCion, 12);
			if (interWareroomData[ i ].itemsID >= 94001)
			{
				auto imageString = __String::createWithFormat("%d.png", localWarerommEquipData[ tempWareroomVector[ i ].itemsID - 94001 ].eID);
				imageGoods[ i ]->loadTexture(imageString->getCString(), TextureResType::UI_TEX_TYPE_PLIST);	
				imageGoods[ i ]->setScale(45 / 105.0f);
			}
			else
			{
				auto imageString = __String::createWithFormat("%s.png", localWarerommGeneralData[ tempWareroomVector[ i ].itemsID - 10001 ].chinaSmallName);
				imageGoods[ i ]->loadTexture(imageString->getCString(), TextureResType::UI_TEX_TYPE_PLIST);	
				imageGoods[ i ]->setScale(45 / 95.0f);
			}			
		}
	}	
}

void Wareroom::shift(Ref* pSender, TouchEventType type)
{
	if (TOUCH_EVENT_ENDED == type)
	{
		auto buttonTag = (Button*)pSender;
		int tempInt = buttonTag->getTag();

		if (false == NewComer::isGuideDone(1007))					/* 引导ID为7，且未完成 */
		{
			if (3 == NewComer::getCurGuideStep())
			{
				_comer->removeFromParentAndCleanup(true);
				NewComer::setCurGuideStep();
				_comer = NewComer::create(this, 1007, 4);
			}
		}

		if (tempWareroomVector.size() == 0)
		{
			return;
		}
		if ( tempWareroomVector[ 0 ].itemsNum > tempInt)							// 开启的格子数量
		{
			if (tempWareroomVector.size() > tempInt)								// 物品数量
			{			
				vectorSubscript = tempInt;
				showInfo(vectorSubscript, buttonIndex);							// 选择按钮的ID，为初始化图片的位置，即Vector中的顺序
			}
			else
			{
				return;													// 点击的位置没有物品
			}				
		}
	}
}

void Wareroom::showInfo(int id, int btnID)
{
	auto wareroomPanel = (Layout*)this->getChildByTag(99);
	auto leftPanel = dynamic_cast<Layout*>( wareroomPanel->getChildByName("Panel_Left") );
	auto sellPanel = dynamic_cast<Layout*>( wareroomPanel->getChildByName("SellPrice") );
	__String* goodsPhotoString = NULL;															// 图片名称
	__String* goodsnameString = NULL;															// 物品名称
	__String* goodsDesString = NULL;															// 物品介绍
	__String* goodsTypeString = NULL;															// 物品类型

	for (int i = 60; i < 62; i ++)																// 物品属性介绍
	{
		leftPanel->removeChildByTag( i );
	}	
	auto proptyLabel1 = (Text*)leftPanel->getChildByName("Label_Propty_1");								// 物品属性1
	proptyLabel1->setFontSize(FontSize);
	proptyLabel1->setVisible(false);
	auto proptyLabel2 = (Text*)leftPanel->getChildByName("Label_Propty_2");								// 物品属性2
	proptyLabel2->setFontSize(FontSize);
	proptyLabel2->setVisible(false);	
	auto desLabel = (Text*)leftPanel->getChildByName("Label_Des");										// 物品介绍
	desLabel->setVisible(false);	
	auto nameLabel = (Text*)leftPanel->getChildByName("Label_Name");									// 装备名称
	nameLabel->setVisible(false);	
	auto goodsImage = (ImageView*)leftPanel->getChildByName("Image_Equip_0");							// 显示物品的图片
	goodsImage->setVisible(false);	
	auto sellLabel = dynamic_cast<Text*>(Helper::seekWidgetByName(sellPanel, "Label_SellPrice_Num"));			// 卖出价格
	sellLabel->setVisible(false);	
	auto typeLabel = dynamic_cast<Text*>(Helper::seekWidgetByName(leftPanel, "Label_Num"));					// 装备类型
	typeLabel->setVisible(false);	
	auto sellButton = dynamic_cast<Button*>(Helper::seekWidgetByName(leftPanel, "Button_Sell"));				// 卖出按钮
	sellButton->setTouchEnabled(false);
	sellButton->setVisible(false);
	sellButton->addTouchEventListener(this, toucheventselector(Wareroom::sell));
	auto syntheticButton = dynamic_cast<Button*>(Helper::seekWidgetByName(leftPanel, "Button_Synthetic"));		// 合成按钮
	syntheticButton->setTouchEnabled(false);
	syntheticButton->setVisible(false);
	syntheticButton->addTouchEventListener(this, toucheventselector(Wareroom::synthetic));
	auto useButton = dynamic_cast<Button*>(Helper::seekWidgetByName(leftPanel, "Button_Use"));				// 使用按钮
	useButton->setTouchEnabled(false);
	useButton->setVisible(false);
	useButton->addTouchEventListener(this, toucheventselector(Wareroom::useClick));
	auto label1 = Label::create();																// 物品对应属性数值1
	label1->setSystemFontSize(FontSize);
	label1->setTag(Label_1);
	label1->setColor(Color3B(255, 76, 0));
	leftPanel->addChild(label1, 10);
	auto label2 = Label::create();																// 物品对应属性数值2
	label2->setSystemFontSize(FontSize);
	label2->setColor(Color3B(255, 76, 0));
	label2->setTag(Label_2);
	leftPanel->addChild(label2, 10);
	if (tempWareroomVector.size() == 0)
	{
		return;
	}
	if (tempWareroomVector[ id ].itemsID == 0)
	{
		return;
	}

	__String* string1;
	__String* string2;

	if (btnID == propBtn)
	{		
		goodsPhotoString = __String::createWithFormat("%d.png", localWareroomPropData[ tempWareroomVector[ id ].itemsID - 93001 ].pID);
 		goodsDesString = __String::createWithFormat("%s", localWareroomPropData[ tempWareroomVector[ id ].itemsID - 93001 ].pDes);
 		goodsnameString = __String::createWithFormat("%s", localWareroomPropData[ tempWareroomVector[ id ].itemsID - 93001 ].pChinaName);
		typeLabel->setVisible(false);
		desLabel->setVisible(true);
		desLabel->setText(goodsDesString->getCString());

		goodsID = localWareroomPropData[ tempWareroomVector[ id ].itemsID - 93001 ].pID;
		if (localWareroomPropData[ tempWareroomVector[ id ].itemsID - 93001 ].pType == powerBtn)
		{
			sellValuePanel->setVisible(false);
			useButton->setVisible(true);
			useButton->setTouchEnabled(true);
			proptyLabel1->setText(mpFontChina->getComString("AddPower")->getCString());
			proptyLabel1->setVisible(true);
			proptyLabel1->setFontSize(FontSize);
			string1 = __String::createWithFormat("%d", localWareroomPropData[ tempWareroomVector[ id ].itemsID - 93001 ].pPowerAdd);
			label1->setPosition(Point(proptyLabel1->getPosition().x + proptyLabel1->getContentSize().width + 10, proptyLabel1->getPositionY()));
			label1->setString(string1->getCString());

			proptyLabel2->setText(mpFontChina->getComString("CurCount")->getCString());
			proptyLabel2->setVisible(true);
			string2 = __String::createWithFormat("%d", tempWareroomVector[ id ].itemsCount);
			label2->setPosition(Point(proptyLabel2->getPosition().x + proptyLabel2->getContentSize().width + 10, proptyLabel2->getPositionY()));
			label2->setString(string2->getCString());
			sellLabel->setVisible(false);
		}
		else if ( localWareroomPropData[ tempWareroomVector[ id ].itemsID - 93001 ].pType == expBtn )
		{
			sellValuePanel->setVisible(false);
			proptyLabel1->setText(mpFontChina->getComString("Exp")->getCString());
			proptyLabel1->setVisible(true);
			proptyLabel1->setFontSize(FontSize);
			string1 = __String::createWithFormat("%d", localWareroomPropData[ tempWareroomVector[ id ].itemsID - 93001 ].pExpAdd);
			label1->setPosition(Point(proptyLabel1->getPosition().x + proptyLabel1->getContentSize().width + 10, proptyLabel1->getPositionY()));
			label1->setString(string1->getCString());

			proptyLabel2->setText(mpFontChina->getComString("CurCount")->getCString());
			proptyLabel2->setVisible(true);
			string2 = __String::createWithFormat("%d", tempWareroomVector[ id ].itemsCount);
			label2->setPosition(Point(proptyLabel2->getPosition().x + proptyLabel2->getContentSize().width + 10, proptyLabel2->getPositionY()));
			label2->setString(string2->getCString());
			sellLabel->setVisible(false);
		}
		else if ( localWareroomPropData[ tempWareroomVector[ id ].itemsID - 93001 ].pType == baoxiangBtn )
		{
			sellValuePanel->setVisible(false);
			useButton->setVisible(true);
			useButton->setTouchEnabled(true);
			proptyLabel1->setText(mpFontChina->getComString("CurCount")->getCString());
			proptyLabel1->setVisible(true);
			proptyLabel1->setFontSize(FontSize);
			string1 = __String::createWithFormat("%d", tempWareroomVector[ id ].itemsCount);
			label1->setPosition(Point(proptyLabel1->getPosition().x + proptyLabel1->getContentSize().width + 10, proptyLabel1->getPositionY()));
			label1->setString(string1->getCString());
			sellLabel->setVisible(false);
			proptyLabel2->setVisible(false);
		}
		else if ( localWareroomPropData[ tempWareroomVector[ id ].itemsID - 93001 ].pType == juanzhouBtn )
		{
			sellValuePanel->setVisible(false);
			useButton->setVisible(false);
			useButton->setTouchEnabled(false);
			proptyLabel1->setText(mpFontChina->getComString("CurCount")->getCString());
			proptyLabel1->setVisible(true);
			proptyLabel1->setFontSize(FontSize);
			string1 = __String::createWithFormat("%d", tempWareroomVector[ id ].itemsCount);
			label1->setPosition(Point(proptyLabel1->getPosition().x + proptyLabel1->getContentSize().width + 10, proptyLabel1->getPositionY()));
			label1->setString(string1->getCString());
			sellLabel->setVisible(false);
			proptyLabel2->setVisible(false);
		}
		else if ( localWareroomPropData[ tempWareroomVector[ id ].itemsID - 93001 ].pType == zaxiang )
		{
			sellValuePanel->setVisible(true);
			sellButton->setVisible(true);
			sellButton->setTouchEnabled(true);
			proptyLabel1->setText(mpFontChina->getComString("CurCount")->getCString());
			proptyLabel1->setVisible(true);
			proptyLabel1->setFontSize(FontSize);
			string1 = __String::createWithFormat("%d", tempWareroomVector[ id ].itemsCount);
			label1->setPosition(Point(proptyLabel1->getPosition().x + proptyLabel1->getContentSize().width + 10, proptyLabel1->getPositionY()));
			label1->setString(string1->getCString());
			proptyLabel2->setVisible(false);

			sellLabel->setVisible(true);
			auto sellString = __String::createWithFormat("%d", localWareroomPropData[ tempWareroomVector[ id ].itemsID - 93001 ].pSellPrice);
			sellLabel->setText(sellString->getCString());
		}
		else if ( tempWareroomVector[ id ].itemsID == 93018 )			// 灵魂石
		{
			sellValuePanel->setVisible(false);
			sellButton->setVisible(false);
			sellButton->setTouchEnabled(false);
			proptyLabel1->setText(mpFontChina->getComString("CurCount")->getCString());
			proptyLabel1->setVisible(true);
			proptyLabel1->setFontSize(FontSize);
			string1 = __String::createWithFormat("%d", tempWareroomVector[ id ].itemsCount);
			label1->setPosition(Point(proptyLabel1->getPosition().x + proptyLabel1->getContentSize().width + 10, proptyLabel1->getPositionY()));
			label1->setString(string1->getCString());
			proptyLabel2->setVisible(false);
			sellLabel->setVisible(false);
		}
		else if ( tempWareroomVector[ id ].itemsID == 93019 )			// 培养丹
		{
			sellValuePanel->setVisible(false);
			sellButton->setVisible(false);
			sellButton->setTouchEnabled(false);
			proptyLabel1->setText(mpFontChina->getComString("CurCount")->getCString());
			proptyLabel1->setVisible(true);
			proptyLabel1->setFontSize(FontSize);
			string1 = __String::createWithFormat("%d", tempWareroomVector[ id ].itemsCount);
			label1->setPosition(Point(proptyLabel1->getPosition().x + proptyLabel1->getContentSize().width + 10, proptyLabel1->getPositionY()));
			label1->setString(string1->getCString());
			proptyLabel2->setVisible(false);
			sellLabel->setVisible(false);
		}
		else if ( tempWareroomVector[ id ].itemsID == 93020 )			// 功勋
		{
			sellValuePanel->setVisible(false);
			sellButton->setVisible(false);
			sellButton->setTouchEnabled(false);
			proptyLabel1->setText(mpFontChina->getComString("CurCount")->getCString());
			proptyLabel1->setVisible(true);
			proptyLabel1->setFontSize(FontSize);
			string1 = __String::createWithFormat("%d", tempWareroomVector[ id ].itemsCount);
			label1->setPosition(Point(proptyLabel1->getPosition().x + proptyLabel1->getContentSize().width + 10, proptyLabel1->getPositionY()));
			label1->setString(string1->getCString());
			proptyLabel2->setVisible(false);
			sellLabel->setVisible(false);
		}
		else if ( tempWareroomVector[ id ].itemsID == 93021 )			// 复活币
		{
			sellValuePanel->setVisible(false);
			sellButton->setVisible(false);
			sellButton->setTouchEnabled(false);
			proptyLabel1->setText(mpFontChina->getComString("CurCount")->getCString());
			proptyLabel1->setVisible(true);
			proptyLabel1->setFontSize(FontSize);
			string1 = __String::createWithFormat("%d", tempWareroomVector[ id ].itemsCount);
			label1->setPosition(Point(proptyLabel1->getPosition().x + proptyLabel1->getContentSize().width + 10, proptyLabel1->getPositionY()));
			label1->setString(string1->getCString());
			proptyLabel2->setVisible(false);
			sellLabel->setVisible(false);
		}
	}
	else if (btnID == equipBtn)
	{
		sellValuePanel->setVisible(true);
		goodsPhotoString = __String::createWithFormat("%d.png", localWarerommEquipData[ tempWareroomVector[ id ].itemsID - 94001].eID);
		goodsDesString = __String::createWithFormat("%s", localWarerommEquipData[ tempWareroomVector[ id ].itemsID - 94001].eDes);
		goodsnameString = __String::createWithFormat("%s+%d", localWarerommEquipData[ tempWareroomVector[ id ].itemsID - 94001].eChinaName, tempWareroomVector[ id ].itemsLevel);
		goodsTypeString = __String::createWithFormat("%s", localWarerommEquipData[ tempWareroomVector[ id ].itemsID - 94001].ePositionName);
		typeLabel->setVisible(true);
		typeLabel->setText(goodsTypeString->getCString());

		sellLabel->setVisible(true);
		auto sellPrice = __String::createWithFormat("%d", localWarerommEquipData[ tempWareroomVector[ id ].itemsID - 94001 ].eSellOut);
		sellLabel->setText( sellPrice->getCString() );

		sellButton->setVisible(true);
		sellButton->setTouchEnabled(true);

		switch (localWarerommEquipData[ tempWareroomVector[ id ].itemsID - 94001 ].ePositionType)
		{
		case TypeHead:
			{
				proptyLabel1->setVisible(true);
				proptyLabel2->setVisible(false);
				proptyLabel1->setText(mpFontChina->getComString("PD")->getCString());

				auto hpString = __String::createWithFormat("%d", localWarerommEquipData[ tempWareroomVector[ id ].itemsID - 94001 ].ePD);
				label1->setPosition(Point(proptyLabel1->getPositionX() + proptyLabel1->getContentSize().width + 10, proptyLabel1->getPositionY()));
				label1->setString(hpString->getCString());
			}		
			break;
		case TypeArmour:
			{
				proptyLabel1->setVisible(true);
				proptyLabel2->setVisible(false);
				proptyLabel1->setText(mpFontChina->getComString("HP")->getCString());

				auto hpString = __String::createWithFormat("%d", localWarerommEquipData[ tempWareroomVector[ id ].itemsID - 94001 ].eHP);
				label1->setPosition(Point(proptyLabel1->getPositionX() + proptyLabel1->getContentSize().width + 10, proptyLabel1->getPositionY()));
				label1->setString(hpString->getCString());
			}		
			break;
		case TypeDecorations:
			{
				proptyLabel1->setVisible(true);
				proptyLabel1->setText(mpFontChina->getComString("MD")->getCString());
				proptyLabel2->setVisible(false);
				auto attackString = __String::createWithFormat("%d", localWarerommEquipData[ tempWareroomVector[ id ].itemsID - 94001 ].eMD);
				label1->setPosition(Point(proptyLabel1->getPositionX() + proptyLabel1->getContentSize().width + 10, proptyLabel1->getPositionY()));
				label1->setString(attackString->getCString());
			}		
			break;
		case TypeWeapons:
			{
				proptyLabel1->setVisible(true);
				proptyLabel2->setVisible(false);
				proptyLabel1->setText(mpFontChina->getComString("Attack")->getCString());
				label1->setPosition(proptyLabel1->getPosition().x + proptyLabel1->getContentSize().width + 10, proptyLabel1->getPosition().y);
				auto hpString = __String::createWithFormat("%d", localWarerommEquipData[ tempWareroomVector[ id ].itemsID - 94001 ].eAtk);
				label1->setString(hpString->getCString());
			}		
			break;
		case TypeQi:
			{
				proptyLabel1->setVisible(true);
				proptyLabel2->setVisible(true);
				proptyLabel1->setText(mpFontChina->getComString("APR")->getCString());
				label1->setPosition(proptyLabel1->getPosition().x + proptyLabel1->getContentSize().width + 10, proptyLabel1->getPosition().y);
				auto hpString = __String::createWithFormat("%.2f", localWarerommEquipData[ tempWareroomVector[ id ].itemsID - 94001 ].eAddCrit);
				label1->setString(hpString->getCString());

				proptyLabel2->setText(mpFontChina->getComString("RPR")->getCString());
				label2->setPosition(proptyLabel2->getPosition().x + proptyLabel2->getContentSize().width + 10, proptyLabel2->getPosition().y);
				auto hpString2 = __String::createWithFormat("%.2f", localWarerommEquipData[ tempWareroomVector[ id ].itemsID - 94001 ].eReduceCrit);
				label2->setString(hpString2->getCString());
			}
			break;
		case TypeYi:
			{
				proptyLabel1->setVisible(true);
				proptyLabel2->setVisible(true);
				proptyLabel1->setText(mpFontChina->getComString("ARH")->getCString());
				label1->setPosition(proptyLabel1->getPosition().x + proptyLabel1->getContentSize().width + 10, proptyLabel1->getPosition().y);
				auto hpString = __String::createWithFormat("%d", localWarerommEquipData[ tempWareroomVector[ id ].itemsID - 94001 ].eAddRealHurt);
				label1->setString(hpString->getCString());

				proptyLabel2->setText(mpFontChina->getComString("RRH")->getCString());
				label2->setPosition(proptyLabel2->getPosition().x + proptyLabel2->getContentSize().width + 10, proptyLabel2->getPosition().y);
				auto hpString2 = __String::createWithFormat("%d", localWarerommEquipData[ tempWareroomVector[ id ].itemsID - 94001 ].eReduceHurt);
				label2->setString(hpString2->getCString());
			}
			break;
		}
	}
	else if (btnID == chipBtn)
	{
		sellValuePanel->setVisible(false);
		syntheticButton->setVisible(true);
		syntheticButton->setTouchEnabled(true);
		if (interWareroomData[ id ].itemsID >= 94001)												// 装备碎片
		{
			goodsPhotoString = __String::createWithFormat("%d.png", localWarerommEquipData[ tempWareroomVector[ id ].itemsID - 94001].eID);
			goodsDesString = __String::createWithFormat("%s", localWarerommEquipData[ tempWareroomVector[ id ].itemsID - 94001].eDes);
			goodsnameString = __String::createWithFormat("%s", localWarerommEquipData[ tempWareroomVector[ id ].itemsID - 94001].eChinaName);
			goodsTypeString = __String::createWithFormat("%s", localWarerommEquipData[ tempWareroomVector[ id ].itemsID - 94001].ePositionName);
			typeLabel->setVisible(true);
			typeLabel->setText(mpFontChina->getComString(goodsTypeString->getCString())->getCString());

			proptyLabel1->setText(mpFontChina->getComString("CurCount")->getCString());
			proptyLabel1->setVisible(true);
			proptyLabel1->setFontSize(FontSize);
			string1 = __String::createWithFormat("%d", tempWareroomVector[ id ].itemsCount);
			label1->setPosition(Point(proptyLabel1->getPosition().x + proptyLabel1->getContentSize().width + 10, proptyLabel1->getPositionY()));
			label1->setString(string1->getCString());

			proptyLabel2->setText(mpFontChina->getComString("Need")->getCString());
			proptyLabel2->setVisible(true);
			proptyLabel2->setFontSize(FontSize);
			localEquipChipVector = DataManager::getInstance()->localEquipChipVector();
			if (localEquipChipVector.size() == 0)
			{
				DataManager::getInstance()->equipChipDataParser();
				localEquipChipVector = DataManager::getInstance()->localEquipChipVector();
			}

			if (localWarerommEquipData[ tempWareroomVector[ id ].itemsID - 94001 ].eisSuit == 0)			// 不是套装
			{				
				for (unsigned int i = 0; i < localEquipChipVector.size(); i ++)
				{
					// 不是套装
					if ( (localEquipChipVector.at( i ).isSuit == 0) && (localEquipChipVector[ i ].color == localWarerommEquipData[ tempWareroomVector[ id ].itemsID - 94001 ].eColor) )
					{
						string2 = __String::createWithFormat("%d", localEquipChipVector[ i ].num);
					}
				}
			}
			else
			{
				for (unsigned int i = 0; i < localEquipChipVector.size(); i ++)
				{
					// 套装
					if ( (localEquipChipVector.at( i ).isSuit == 1) && (localEquipChipVector[ i ].color == localWarerommEquipData[ tempWareroomVector[ id ].itemsID - 94001 ].eColor) )
					{
						string2 = __String::createWithFormat("%d", localEquipChipVector[ i ].num);
					}
				}
			}
			label2->setPosition(Point(proptyLabel2->getPosition().x + proptyLabel2->getContentSize().width + 10, proptyLabel2->getPositionY()));
			label2->setString(string2->getCString());
		}
		else
		{
			goodsPhotoString = __String::createWithFormat("%s.png", localWarerommGeneralData[ tempWareroomVector[ id ].itemsID - 10001].chinaSmallName);
			goodsnameString = __String::createWithFormat("%s", localWarerommGeneralData[ tempWareroomVector[ id ].itemsID - 10001].chinaName);
			goodsDesString = __String::createWithFormat("%s", localWarerommGeneralData[ tempWareroomVector[ id ].itemsID - 10001].g_des);
			typeLabel->setVisible(false);

			proptyLabel1->setText(mpFontChina->getComString("CurCount")->getCString());
			proptyLabel1->setVisible(true);
			proptyLabel1->setFontSize(FontSize);
			string1 = __String::createWithFormat("%d", tempWareroomVector[ id ].itemsCount);
			label1->setPosition(Point(proptyLabel1->getPosition().x + proptyLabel1->getContentSize().width + 10, proptyLabel1->getPositionY()));
			label1->setString(string1->getCString());

			proptyLabel2->setText(mpFontChina->getComString("Need")->getCString());
			proptyLabel2->setVisible(true);
			proptyLabel2->setFontSize(FontSize);
			localGeneralChipVector = DataManager::getInstance()->localGeneralChipVector();
			if (localGeneralChipVector.size() == 0)
			{
				DataManager::getInstance()->generalChipDataParser();
				localGeneralChipVector = DataManager::getInstance()->localGeneralChipVector();
			}
			for (unsigned int i = 0; i < localGeneralChipVector.size(); i ++)
			{
				if (localWarerommGeneralData[ tempWareroomVector[ id ].itemsID - 10001 ].maxStar == localGeneralChipVector[ i ].starLevel)
				{
					string2 = __String::createWithFormat("%d", localGeneralChipVector[ i ].num);
				}
			}			
			label2->setPosition(Point(proptyLabel2->getPosition().x + proptyLabel2->getContentSize().width + 10, proptyLabel2->getPositionY()));
			label2->setString(string2->getCString());
		}
	}
	// 图片
	goodsImage->setVisible(true);
	if ( (btnID == propBtn) || (btnID == equipBtn) )
	{
		goodsImage->setScale(75 / 95.0f);
	}
	else
	{
		goodsImage->setScale(75 / 120.0f);
	}	
	goodsImage->loadTexture(goodsPhotoString->getCString(), TextureResType::UI_TEX_TYPE_PLIST);
	// 名称
	nameLabel->setVisible(true);	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	nameLabel->setText(mpFontChina->G2U(goodsnameString->getCString()));
#else
	nameLabel->setText(goodsnameString->getCString());
#endif	
 	desLabel->setVisible(true);
	desLabel->ignoreContentAdaptWithSize(false); 
	desLabel->setSize(Size(200, 200)); 
	desLabel->setTextHorizontalAlignment(TextHAlignment::LEFT);
	desLabel->setText(goodsDesString->getCString());	
}

void Wareroom::closeButton(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		if (false == NewComer::isGuideDone(1007))					/* 引导ID为7，且未完成 */
		{
			NewComer::setCurGuideStep(0);							/* 未完成引导 */
			NewComer::setCurGuideStep(1);
		}

		ToolFunc::playEffectFile( Click );
		Director::getInstance()->replaceScene(MainScene::scene());
	}	
}

void Wareroom::setBrightButton(btnEnum btnIndex)
{
	for (int i = 0; i < 3; i ++)
	{
		auto comLayout = (Layout*)this->getChildByTag(99);
		auto rightPanel = (Layout*)comLayout->getChildByTag(RightPanelTag);
		auto comBtn = (Button*)rightPanel->getChildByTag(btnPropTag + i);
		comBtn->setBrightStyle(BrightStyle::BRIGHT_NORMAL);
		if ( i + 1 == btnIndex)
		{
			auto comBtnCopy = (Button*)rightPanel->getChildByTag(btnPropTag + i);
			comBtn->setBrightStyle(BrightStyle::BRIGHT_HIGHLIGHT);
		}
	}
}

bool Wareroom::onTouchBegan(Touch *touch, Event *unused_event)
{
	if (wareroomState == StateTips)
	{
		auto tipsLayer = (Layout*)this->getChildByTag(toolTipsTag);
		auto size = tipsLayer->getBoundingBox();
		if (!size.containsPoint(touch->getLocation()))
		{
			this->removeChildByTag(toolTipsTag);
			wareroomState = StateNone;
		}
	}
	return true;
}

void Wareroom::onEnter()
{
	Layer::onEnter();
	createProps(NULL, TOUCH_EVENT_ENDED);
}

void Wareroom::onExit()
{
	Layer::onExit();
}

void Wareroom::sell(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		ToolFunc::playEffectFile( Click );
		for (unsigned int i = 0; i < interWareroomData.size(); i ++)
		{
			if (interWareroomData[ i ].itemPKID == tempWareroomVector[ vectorSubscript ].itemPKID)
			{
				if (buttonIndex == propBtn)
				{
					if (DataManager::getInstance()->isSelloutEquipScceed(interWareroomData[ i ].itemPKID, localWareroomPropData[ tempWareroomVector[ vectorSubscript ].itemsID - 93001].pSellPrice))
					{
						createProps(pSender, TOUCH_EVENT_ENDED);
						break;
					}
				}
				else if (buttonIndex == equipBtn)
				{
					if (DataManager::getInstance()->isSelloutEquipScceed(interWareroomData[ i ].itemPKID, localWarerommEquipData[ tempWareroomVector[ vectorSubscript ].itemsID - 94001].eSellOut))
					{
						createEquip(pSender, TOUCH_EVENT_ENDED);
						break;
					}
				}
			}
		}								
	}
}

void Wareroom::synthetic(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		ToolFunc::playEffectFile( Click );

		if (false == NewComer::isGuideDone(1007))					/* 引导ID为7，且未完成 */
		{
			if (4 == NewComer::getCurGuideStep())
			{
				_comer->removeFromParentAndCleanup(true);
				auto cpID = NewComer::getCurGuideID();
				cpID = cpID | 0x010000;								/* 完成ID为0的引导 */
				NewComer::setCurGuideID(cpID);
				NewComer::setCurGuideStep(0);						/* 步骤ID重置 */
			}
		}

		if (interWareroomData[ vectorSubscript ].itemsID >= 94001 )	// 合成装备
		{
			if (localWarerommEquipData[ interWareroomData[ vectorSubscript ].itemsID - 94001 ].eisSuit == 0)			// 不是套装
			{				
				for (unsigned int i = 0; i < localEquipChipVector.size(); i ++)
				{
					// 不是套装
					if ( (localEquipChipVector.at( i ).isSuit == 0) && (localEquipChipVector[ i ].color == localWarerommEquipData[ interWareroomData[ vectorSubscript ].itemsID - 94001 ].eColor) )
					{
						if (interWareroomData[ vectorSubscript ].itemsCount >= localEquipChipVector[ i ].num)
						{
							if (DataManager::getInstance()->isChipSynthScceed(interWareroomData[ vectorSubscript ].itemPKID, localEquipChipVector[ i ].num, 
								localWarerommEquipData[ interWareroomData[ vectorSubscript ].itemsID -94001].eID ))
							{
								auto syntheticString = __String::createWithFormat("%s %s",mpFontChina->getComString("Synthetic"), 
									localWarerommEquipData[ interWareroomData[ vectorSubscript ].itemsID - 94001 ].eChinaName);
								showTips(syntheticString->getCString());
							}
						}
						else
						{
							log("%d Fail", localWarerommEquipData[ interWareroomData[ vectorSubscript ].itemsID - 94001 ].eID);
							showTips(mpFontChina->getComString("SyntheticFail")->getCString());
						}
					}
				}
			}
			else
			{
				for (unsigned int i = 0; i < localEquipChipVector.size(); i ++)
				{
					// 套装
					if ( (localEquipChipVector.at( i ).isSuit == 1) && (localEquipChipVector[ i ].color == localWarerommEquipData[ interWareroomData[ vectorSubscript ].itemsID - 94001 ].eColor) )
					{
						if (interWareroomData[ vectorSubscript ].itemsCount >= localEquipChipVector[ i ].num)
						{
							log("%d Success ", localWarerommEquipData[ interWareroomData[ vectorSubscript ].itemsID - 94001 ].eID);
							if (DataManager::getInstance()->isChipSynthScceed(interWareroomData[ vectorSubscript ].itemPKID, localEquipChipVector[ i ].num, 
								localWarerommEquipData[ interWareroomData[ vectorSubscript ].itemsID -94001].eID ))
							{
								auto syntheticString = __String::createWithFormat("%s %s",mpFontChina->getComString("Synthetic"), 
									localWarerommEquipData[ interWareroomData[ vectorSubscript ].itemsID - 94001 ].eChinaName);
								showTips(syntheticString->getCString());
							}
						}
						else
						{
							log("%d", localWarerommEquipData[ interWareroomData[ vectorSubscript ].itemsID - 94001 ].eID);
							showTips(mpFontChina->getComString("SyntheticFail")->getCString());
						}
					}
				}
			}	
		}
		else
		{
			for (unsigned int i = 0; i < localGeneralChipVector.size(); i ++)
			{
				if (localWarerommGeneralData[ interWareroomData[ vectorSubscript ].itemsID - 10001 ].maxStar == localGeneralChipVector[ i ].starLevel)
				{
					if (interWareroomData[ vectorSubscript ].itemsCount >= localGeneralChipVector[ i ].num)
					{
						log("%s Success ", localWarerommGeneralData[ interWareroomData[ vectorSubscript ].itemsID - 10001 ].chinaSmallName);
						if (DataManager::getInstance()->isChipSynthScceed(interWareroomData[ vectorSubscript ].itemPKID, localGeneralChipVector[ i ].num, 
							localWarerommGeneralData[ interWareroomData[ vectorSubscript ].itemsID -10001].roleID ))
						{
							auto syntheticString = __String::createWithFormat("%s %s",mpFontChina->getComString("Synthetic"), 
								localWarerommGeneralData[ interWareroomData[ vectorSubscript ].itemsID - 10001 ].chinaName);
							showTips(syntheticString->getCString());
						}
					}
					else
					{
						log("%s Fail", localWarerommGeneralData[ interWareroomData[ vectorSubscript ].itemsID - 10001 ].chinaSmallName);
						showTips(mpFontChina->getComString("SyntheticFail")->getCString());
					}
				}
			}
		}
		createChip(NULL, TOUCH_EVENT_ENDED);
	}
}

void Wareroom::expandBag(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		if (UserData::getInstance()->setupEffect)
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(Click);
		createConfirmLayout(buttonIndex);
	}	
}

void Wareroom::useClick(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		ToolFunc::playEffectFile( Click );
		if (goodsID != 0)
		{
			if (goodsID == 93001)			// 肉包子
			{
				if (DataManager::getInstance()->isPropUseScceed( interWareroomData[ vectorSubscript ].itemPKID ))
				{
					log("93001 use Success");
				}
			}
			else if (goodsID == 93005)		// 木宝箱
			{
				vector<DrawoffGoodsStruct > tempVector;
				for (int i = 0; i < 1; i ++)
				{		
					tempVector.push_back( muBox( ToolFunc::calcRandom(1, 1000), 1) );
				}
				if ( DataManager::getInstance()->isDrawoffCard(0, 0, 0, 0, tempVector) )
				{
					DataManager::getInstance()->drawoffGoodsVectorForDis = tempVector;
					Director::getInstance()->pushScene(DrawoffDiaplay::scene());

					if (DataManager::getInstance()->isPropUseScceed( interWareroomData[ vectorSubscript ].itemPKID ))
					{
						log("93001 use Success");
					}
				}
			}
			else if (goodsID == 93006)		// 银宝箱
			{
				vector<DrawoffGoodsStruct > tempVector;
				for (int i = 0; i < 1; i ++)
				{		
					tempVector.push_back( muBox( ToolFunc::calcRandom(1, 1000), 2) );
				}
				if ( DataManager::getInstance()->isDrawoffCard(0, 0, 0, 0, tempVector) )
				{
					DataManager::getInstance()->drawoffGoodsVectorForDis = tempVector;
					Director::getInstance()->pushScene(DrawoffDiaplay::scene());

					if (DataManager::getInstance()->isPropUseScceed( interWareroomData[ vectorSubscript ].itemPKID ))
					{
						log("93001 use Success");
					}
				}
			}
			else if (goodsID == 93007)		// 金宝箱
			{
				vector<DrawoffGoodsStruct > tempVector;
				for (int i = 0; i < 1; i ++)
				{		
					tempVector.push_back( muBox( ToolFunc::calcRandom(1, 1000), 3) );
				}
				if ( DataManager::getInstance()->isDrawoffCard(0, 0, 0, 0, tempVector) )
				{
					DataManager::getInstance()->drawoffGoodsVectorForDis = tempVector;
					Director::getInstance()->pushScene(DrawoffDiaplay::scene());

					if (DataManager::getInstance()->isPropUseScceed( interWareroomData[ vectorSubscript ].itemPKID ))
					{
						log("93001 use Success");
					}
				}
			}
		}
	}
}

DrawoffGoodsStruct Wareroom::muBox(int id, int boxType)
{
	DrawoffGoodsStruct drawoff;
	memset(&drawoff, 0, sizeof(drawoff));

	localBoxVector = DataManager::getInstance()->localBoxVector();
	if (localBoxVector.size() == 0)
	{
		DataManager::getInstance()->boxDataParser();
		localBoxVector = DataManager::getInstance()->localBoxVector();
	}
	for (unsigned int i = 0; i < localBoxVector.size(); i ++)
	{
		vector<string > diamonRangeVector;
		if (boxType == 1)							// 木头宝箱
		{
			diamonRangeVector = DataManager::getInstance()->splitString(localBoxVector.at( i ).tong, "-");
		}
		else if (boxType == 2)						// 银宝箱
		{
			diamonRangeVector = DataManager::getInstance()->splitString(localBoxVector.at( i ).yin, "-");
		}
		else
		{
			diamonRangeVector = DataManager::getInstance()->splitString(localBoxVector.at( i ).jin, "-");
		}
		vector<string > idRangeVector = DataManager::getInstance()->splitString(localBoxVector.at( i ).idRange, "-");
		if ( ( id >= atoi(diamonRangeVector.at( 0 ).c_str()) ) && ( id <= atoi(diamonRangeVector.at( 1 ).c_str()) ) )
		{
			drawoff.goodsType = GoodsTypeEnum(localBoxVector.at( i ).goodsType);
			drawoff.goodsID = ToolFunc::calcRandom( atoi(idRangeVector.at( 0 ).c_str()), atoi(idRangeVector.at( 1 ).c_str()) );
		}
	}
	return drawoff;	
}

void Wareroom::createConfirmLayout(int btnIndex)
{
	wareroomState = StateTips;
	this->removeChildByTag(toolTipsTag);
	auto confirmTips = GUIReader::getInstance()->widgetFromJsonFile("Confirm.ExportJson");
	confirmTips->setPosition(Point(400 - confirmTips->getContentSize().width / 2, 240 - confirmTips->getContentSize().height / 2));
	confirmTips->setTag(toolTipsTag);
	this->addChild(confirmTips, 10);

	auto confirm = dynamic_cast<Button*>(Helper::seekWidgetByName(confirmTips, "Confirm_Button"));
	confirm->setTag(btnIndex);
	confirm->addTouchEventListener(this, toucheventselector(Wareroom::confirmButton));
	auto cancel = dynamic_cast<Button*>(Helper::seekWidgetByName(confirmTips, "Cancel_Button"));
	cancel->addTouchEventListener(this, toucheventselector(Wareroom::cancelButton));

	auto desLabel = dynamic_cast<Text*>(Helper::seekWidgetByName(confirmTips, "Des_Label"));
	desLabel->setFontSize(18.0f);
	diamond = ( interWareroomData[ 0 ].itemsNum - 24 ) / 8 * 10 + 10;

	auto numString = __String::createWithFormat("%s %d", mpFontChina->getComString("ExpandGrid")->getCString(), diamond);
// 	auto countString = __String::createWithFormat("%d", diamond);
// 	numString->append(countString->getCString());
	

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	desLabel->setText(FontChina::G2U(numString->getCString()));
#else
	desLabel->setText(numString->getCString());
#endif	
}

void Wareroom::confirmButton(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		if ( DataManager::getInstance()->isGetPlayerInfo() )
		{
			interPlayerInfo = DataManager::getInstance()->interPlayerInfoVector();
		}
		if ( interPlayerInfo[ 0 ].diamondValue >= diamond )
		{
			if (DataManager::getInstance()->isUnlockGridSucceed( WareroomEnum(buttonIndex + 3), 8, diamond))
			{
				// 添加解锁特效
				auto effect = EffectAction::getInstance();
				effect->unLockAnim();
				this->addChild(effect, 10);

				this->removeChildByTag(toolTipsTag);
				wareroomState = StateNone;
				if (buttonIndex == propBtn)
				{
					createProps(NULL, TOUCH_EVENT_ENDED);
				}
				else if (buttonIndex == equipBtn)
				{
					createEquip(NULL, TOUCH_EVENT_ENDED);
				}
				else if (buttonIndex == chipBtn)
				{
					createChip(NULL, TOUCH_EVENT_ENDED);
				}
			}
		}
		else
		{
			// 钻石数量不足
			this->removeChildByTag(toolTipsTag);
			wareroomState = StateNone;
		}
	}
}

void Wareroom::cancelButton(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		this->removeChildByTag(toolTipsTag);
		wareroomState = StateNone;
	}
}

void Wareroom::showTips(string str)
{
	auto label = Label::create();
	label->setPosition(Point(400, 0));
	label->setSystemFontSize(FontSize + 6);
	label->setColor(Color3B::WHITE);
	label->setTag(LabelTipTag);
	label->setString(str.c_str());
	this->addChild(label, 100);

	auto moveto = MoveTo::create(0.5f, Point(400, 240));
	auto delay = DelayTime::create(0.5f);
	auto fadeout = FadeOut::create(0.5f);
	auto moveto2 = MoveTo::create(0.5f, Point(400, 800));
	auto callBack = CallFunc::create(CC_CALLBACK_0(Wareroom::showTipsCallBack, this));
	auto se = Sequence::create(moveto, delay, Spawn::create(fadeout, moveto2, NULL), callBack, NULL);
	label->runAction(se);
}

void Wareroom::showTipsCallBack()
{
	this->removeChildByTag(LabelTipTag);
}