#include "Maidan.h"

const int cellRow = 5;
const Size cellSize = Size(110.0f, 165.0f);				// 滚动层cell size 
const float cellScale = 0.9f;
const int PresetTag = 10;
const int PanelTag = 99;

const int SlotCount = 4;							// 可上阵武将数量

Maidan::Maidan():panelState(NoneState), posIndex(-1), propID(-1), i_ButtonFlag( 0 )
{
	
}

Maidan::~Maidan()
{

}

Scene* Maidan::scene()
{
	auto scene = Scene::create();
	scene->addChild(Maidan::create());
	return scene;
}

bool Maidan::init()
{
	localPropVectro = DataManager::getInstance()->localPropProptyVector();
	if (localPropVectro.size() == 0)
	{
		DataManager::getInstance()->propDataParser();
		localPropVectro = DataManager::getInstance()->localPropProptyVector();
	}
	localGeneralUpgradeVector = DataManager::getInstance()->localGeneralUpgradeVector();
	if (localGeneralUpgradeVector.size() == 0)
	{
		DataManager::getInstance()->generalUpgradeDataParser();
		localGeneralUpgradeVector = DataManager::getInstance()->localGeneralUpgradeVector();
	}
	localEquipVector = DataManager::getInstance()->localEquipProptyVector();
	if (localEquipVector.size() == 0)
	{
		DataManager::getInstance()->equipDataParser();
		localEquipVector = DataManager::getInstance()->localEquipProptyVector();
	}
	localEquipRefineRuleVector = DataManager::getInstance()->localEquipRefineVector();
	if (localEquipRefineRuleVector.size() == 0)
	{
		DataManager::getInstance()->equipRefineRule();
		localEquipRefineRuleVector = DataManager::getInstance()->localEquipRefineVector();
	}

	mpFontChina = FontChina::getInstance();
	mpFontChina->initStringXml();

	auto trainUI = GUIReader::getInstance()->widgetFromJsonFile("UI/All/Train.ExportJson");	
	trainUI->setTag(PanelTag);
	this->addChild(trainUI);

	mainScrollView = dynamic_cast<cocos2d::ui::ScrollView* >(Helper::seekWidgetByName(trainUI, "T_ScrollView"));

	auto close = dynamic_cast<Button *>(Helper::seekWidgetByName(trainUI, "Button_Close"));
	close->addTouchEventListener(this, toucheventselector(Maidan::closeButton));

	movePanel = dynamic_cast<Layout* >(Helper::seekWidgetByName(trainUI, "Panel_Move"));
	enhancePanel = dynamic_cast<Layout* >(Helper::seekWidgetByName(movePanel, "Panel_Str"));	
	presetPanel = dynamic_cast<Layout* >(Helper::seekWidgetByName(movePanel, "Panel_PreSet"));
	enhancePanel->setVisible(false);
	enhancePanel->setLocalZOrder(30);
	enhancePanel->setTouchEnabled(false);
	presetPanel->setVisible(false);
	presetPanel->setLocalZOrder(30);
	presetPanel->setTouchEnabled(false);

	auto trainSidePanel = dynamic_cast<Layout *>(Helper::seekWidgetByName(movePanel, "Panel_TrainSide"));
	rightButtonPanel = dynamic_cast<Layout* >(Helper::seekWidgetByName(movePanel, "Panel_RSideButton_1"));

	// 左边的按钮
	auto allButton = dynamic_cast<Button *>(Helper::seekWidgetByName(rightButtonPanel, "T_Button_ALL_0"));
	allButton->setTag(TypeALL);
	allButton->addTouchEventListener(this, toucheventselector(Maidan::typeButton));

	auto liButton = dynamic_cast<Button *>(Helper::seekWidgetByName(rightButtonPanel, "T_Button_Li_0"));
	liButton->setTag(TypeLI);
	liButton->addTouchEventListener(this, toucheventselector(Maidan::typeButton));

	auto zhiButton = dynamic_cast<Button *>(Helper::seekWidgetByName(rightButtonPanel, "T_Button_Zhi_0"));
	zhiButton->setTag(TypeZhi);
	zhiButton->addTouchEventListener(this, toucheventselector(Maidan::typeButton));

	auto minButton = dynamic_cast<Button *>(Helper::seekWidgetByName(rightButtonPanel, "T_Button_Min_0"));
	minButton->setTag(TypeMin);
	minButton->addTouchEventListener(this, toucheventselector(Maidan::typeButton));

	// 强化
	button_Str = dynamic_cast<Button *>(Helper::seekWidgetByName(trainSidePanel, "Button_Str"));
	button_Str->addTouchEventListener(this, toucheventselector(Maidan::enhanceButton));

	// 预设
	button_PreSet = dynamic_cast<Button *>(Helper::seekWidgetByName(trainSidePanel, "Button_PreSet"));
	button_PreSet->addTouchEventListener(this, toucheventselector(Maidan::preSetButton));	
	
	return true;
}

void Maidan::initGeneralData()
{
	if (DataManager::getInstance()->isGetMaidan())
	{
		interMaidanVector = DataManager::getInstance()->interMaidanVector();
		localGeneralVector = DataManager::getInstance()->localGeneralProptyVector();
		if (localGeneralVector.size() == 0)
		{
			DataManager::getInstance()->generalDataParser();
			localGeneralVector = DataManager::getInstance()->localGeneralProptyVector();
		}
		GeneralProptyStruct generalStruct;
		memset(&generalStruct, 0, sizeof(generalStruct));
		curGeneralVector.clear();
		for (unsigned int i = 0; i < interMaidanVector.size(); i ++)
		{
			generalStruct.PKID = interMaidanVector[ i ].generalPKID;												// 主键ID
			generalStruct.roleID = localGeneralVector[ interMaidanVector[ i ].generalType - 10001 ].roleID;					// 角色ID
			string strName = localGeneralVector[ interMaidanVector[ i ].generalType - 10001 ].chinaName;					// 中文名称
			memset(generalStruct.chinaName, 0, sizeof(generalStruct.chinaName));
			memcpy(generalStruct.chinaName, strName.c_str(), strName.length());
			string strSmallName = localGeneralVector[ interMaidanVector[ i ].generalType - 10001 ].chinaSmallName;			// 拼音
			memset(generalStruct.chinaSmallName, 0, sizeof(generalStruct.chinaSmallName));
			memcpy(generalStruct.chinaSmallName, strSmallName.c_str(), strSmallName.length());
			generalStruct.curStarLevel = interMaidanVector[ i ].curStar;												// 当前星级	
			generalStruct.maxStar = localGeneralVector[ interMaidanVector[ i ].generalType - 10001 ].maxStar;				// 最大星级
			generalStruct.jobType = localGeneralVector[ interMaidanVector[ i ].generalType - 10001 ].jobType;				// 职业类型
			generalStruct.level = interMaidanVector[ i ].generalLevel;												// 等级
			generalStruct.strongExp = interMaidanVector[ i ].generalExp;											// 强化经验值
			generalStruct.isSelect = interMaidanVector[ i ].isSelected;												// 是否上阵
			generalStruct.evoLevel = interMaidanVector[ i ].evoLevel;												// 进阶等级
			curGeneralVector.push_back(generalStruct);
		}
	}
	if (DataManager::getInstance()->isGetTeamInfo())
	{
		interTeamInfoVector = DataManager::getInstance()->interTeamInfoVector();
	}

	auto curLayer = (Layout* )this->getChildByTag( 99 );
	auto curCount = dynamic_cast<Text* >(Helper::seekWidgetByName(curLayer, "Label_87"));
	auto countString = __String::createWithFormat("%d/40", curGeneralVector.size());
	curCount->setText(countString->getCString());
}

void Maidan::showGeneral()
{
	mainScrollView->removeAllChildrenWithCleanup(true);
	int cellCount = tempGeneralVector.size();
	auto cell_Size = cellSize * cellScale;
	Size szInnerContainer = mainScrollView->getContentSize();
	int cellGap = 10;									// 滚动层宽间隔 
	int cellHeightGap = -10;								// 滚动层高间隔 

	auto columuNum = cellCount / cellRow;
	if ( cellCount % cellRow != 0 )
	{
		columuNum ++;
	}
	auto height = (cellSize.height * cellScale + cellHeightGap) * columuNum ;
	height = (height > szInnerContainer.height) ? height : szInnerContainer.height;
	mainScrollView->setInnerContainerSize(Size(szInnerContainer.width, height));

	for (int i = 0; i < cellCount; i ++)
	{
		auto cell = TrainCell::create();
		cell->setCellImage(tempGeneralVector[ i ].chinaSmallName, tempGeneralVector[ i ].maxStar);
		cell->setCellGeneralIndex(tempGeneralVector[ i ].roleID);
		cell->setCurStar(tempGeneralVector[ i ].curStarLevel, tempGeneralVector[ i ].maxStar);
		cell->setCellLevel(tempGeneralVector[ i ].level);
		cell->setExp(tempGeneralVector[ i ].level, tempGeneralVector[ i ].strongExp);
		cell->setCellName(tempGeneralVector[ i ].chinaName, tempGeneralVector[ i ].evoLevel);
		cell->setType(tempGeneralVector[ i ].jobType);
		cell->setCellUp(tempGeneralVector[ i ].isSelect);
// 		for (int z = 0; z < 6; z ++)
// 		{
// 			if (tempGeneralVector[ i ].equipID[ z ] != 0)
// 			{
// 				cell->setEquip(z , tempGeneralVector[ i ].equipID[ z ]);
// 			}			
// 		}
		cell->setPosition(Point( ( i % cellRow ) * (cellSize.width * cellScale + cellGap) + 37,
			height  - 10 - ( i / cellRow + 1 ) * (cellSize.height * cellScale + cellHeightGap)));
		cell->trainCellUI->setTag( i );
		cell->trainCellUI->addTouchEventListener(this, toucheventselector(Maidan::panelTouchCallback));
		cell->trainCellUI->setTouchEnabled(true);
		cell->setScale( cellScale );
		mainScrollView->addChild(cell);	
	}
}

void Maidan::initEnhanceProp()
{
	for (int i = 0; i < 3; i ++)
	{
		auto propString = __String::createWithFormat("Image_Role_%d_0", i + 1);
		propImage[ i ] = dynamic_cast<ImageView* >(Helper::seekWidgetByName(enhancePanel, propString->getCString()));
		propImage[ i ]->setTag( i );
		auto propImageString = __String::createWithFormat("%d.png", 93002 + i);
		auto propNumString = __String::createWithFormat("Label_%d", i + 1);
		propImage[ i ]->loadTexture(propImageString->getCString(), TextureResType::UI_TEX_TYPE_PLIST);
		propImage[ i ]->setScale(73.0f / 95.0f);
		propNum[ i ] = dynamic_cast<Text* >(Helper::seekWidgetByName(enhancePanel, propNumString->getCString()));
		if (DataManager::getInstance()->isSortGoodsNum(93002 + i))
		{
			goodsNum = DataManager::getInstance()->sortGoodsNum();
			auto numString = __String::createWithFormat("%d", goodsNum);
			propNum[ i ]->setText(numString->getCString());					
			propImage[ i ]->addTouchEventListener(this, toucheventselector(Maidan::propIamgeCallBack)); 
		}
	}
}

void Maidan::initPresetPanel()
{
	for (int i = 0; i < 4; i ++)
	{
		auto imageString = __String::createWithFormat("Image_Role_%d_0", i + 1);												// 人物头像
		roleImage[ i ] = dynamic_cast<ImageView* >(Helper::seekWidgetByName(presetPanel, imageString->getCString()));
		roleImage[ i ]->loadTexture("TempPic/Lock.png");
		roleImage[ i ]->setScale(1.0f);
		roleImage[ i ]->setTag( i );
		roleImage[ i ]->addTouchEventListener(this, toucheventselector(Maidan::heroPhotoCallBack));

		auto selectString = __String::createWithFormat("Image_Role_%d_0_0", i + 1);											// 头像选中状态
		roleImageSelect[ i ] = dynamic_cast<ImageView* >(Helper::seekWidgetByName(presetPanel, selectString->getCString()));
	}

	for (int i = 0; i < 4; i ++)
	{
		auto buttonString = __String::createWithFormat("Image_TrainClose%d", i + 1);											// 下阵
		roleButtonSelect[ i ] = dynamic_cast<ImageView* >(Helper::seekWidgetByName(presetPanel, buttonString->getCString()));
		roleButtonSelect[ i ]->setTag( i );
		roleButtonSelect[ i ]->setVisible(false);
		roleButtonSelect[ i ]->setTouchEnabled(false);
		roleButtonSelect[ i ]->addTouchEventListener(this, toucheventselector(Maidan::heroCloseCallBack));
	}	

	if (DataManager::getInstance()->isGetPointSets())
	{
		interPointSetsVector = DataManager::getInstance()->interPointSetsVector();
	}	
	else
	{
		interPointSetsVector.clear();
	}
	fightingLabel = dynamic_cast<TextAtlas* >(Helper::seekWidgetByName(presetPanel, "AtlasLabel_ATK"));
	int intFight = calcPreFighting(interPointSetsVector);
	auto fightString = __String::createWithFormat("%d", intFight);
	fightingLabel->setStringValue(fightString->getCString());

	
	if (interTeamInfoVector[ 0 ].teamLevel >= 1)
	{
		if ( interPointSetsVector.size() == 0 )
		{
			roleImage[ 0 ]->loadTexture("PointSets/dui-3.png", TextureResType::UI_TEX_TYPE_PLIST);
		}
		else
		{
			for (unsigned int i = 0; i < interPointSetsVector.size(); i ++)
			{
				if ( interPointSetsVector[ i ].generalPos == 1 )
				{
					auto nameString = __String::createWithFormat("%s.png", localGeneralVector[ interPointSetsVector[ i ].generalID - 10001 ].chinaSmallName);
					roleImage[ 0 ]->loadTexture(nameString->getCString(), TextureResType::UI_TEX_TYPE_PLIST);
					roleImage[ 0 ]->setScale(73 / 95.0f);
					break;
				}
				else
				{
					roleImage[ 0 ]->loadTexture("PointSets/dui-3.png", TextureResType::UI_TEX_TYPE_PLIST);
				}
			}			
		}		
	}
	if (interTeamInfoVector[ 0 ].teamLevel >= 3)
	{
		if ( interPointSetsVector.size() == 0 )
		{
			roleImage[ 1 ]->loadTexture("PointSets/dui-3.png", TextureResType::UI_TEX_TYPE_PLIST);
		}
		else
		{
			for (unsigned int i = 0; i < interPointSetsVector.size(); i ++)
			{
				if ( interPointSetsVector[ i ].generalPos == 2 )
				{
					auto nameString = __String::createWithFormat("%s.png", localGeneralVector[ interPointSetsVector[ i ].generalID - 10001 ].chinaSmallName);
					roleImage[ 1 ]->loadTexture(nameString->getCString(), TextureResType::UI_TEX_TYPE_PLIST);
					roleImage[ 1 ]->setScale(73 / 95.0f);
					break;
				}
				else
				{
					roleImage[ 1 ]->loadTexture("PointSets/dui-3.png", TextureResType::UI_TEX_TYPE_PLIST);
				}
			}
		}
	}
	if (interTeamInfoVector[ 0 ].teamLevel >= 6)
	{
		if ( interPointSetsVector.size() == 0 )
		{
			roleImage[ 2 ]->loadTexture("PointSets/dui-3.png", TextureResType::UI_TEX_TYPE_PLIST);
		}
		else
		{
			for (unsigned int i = 0; i < interPointSetsVector.size(); i ++)
			{
				if ( interPointSetsVector[ i ].generalPos == 3 )
				{
					auto nameString = __String::createWithFormat("%s.png", localGeneralVector[ interPointSetsVector[ i ].generalID - 10001 ].chinaSmallName);
					roleImage[ 2 ]->loadTexture(nameString->getCString(), TextureResType::UI_TEX_TYPE_PLIST);
					roleImage[ 2 ]->setScale(73 / 95.0f);
					break;
				}
				else
				{
					roleImage[ 2 ]->loadTexture("PointSets/dui-3.png", TextureResType::UI_TEX_TYPE_PLIST);
				}
			}
		}
	}
	if (interTeamInfoVector[ 0 ].teamLevel >= 12)
	{
		if ( interPointSetsVector.size() == 0 )
		{
			roleImage[ 3 ]->loadTexture("PointSets/dui-3.png", TextureResType::UI_TEX_TYPE_PLIST);
		}
		else
		{
			for (unsigned int i = 0; i < interPointSetsVector.size(); i ++)
			{
				if ( interPointSetsVector[ i ].generalPos == 4 )
				{
					auto nameString = __String::createWithFormat("%s.png", localGeneralVector[ interPointSetsVector[ i ].generalID - 10001 ].chinaSmallName);
					roleImage[ 3 ]->loadTexture(nameString->getCString(), TextureResType::UI_TEX_TYPE_PLIST);
					roleImage[ 3 ]->setScale(73 / 95.0f);
					break;
				}
				else
				{
					roleImage[ 3 ]->loadTexture("PointSets/dui-3.png", TextureResType::UI_TEX_TYPE_PLIST);
				}
			}
		}
	}
}

void Maidan::heroPhotoCallBack(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		ToolFunc::playEffectFile( Click );
		auto button = (ImageView* )pSender;

		if (false == NewComer::isGuideDone(1002))	// 引导2，进入下一步骤
		{
			if ((1 == button->getTag()) && (3 == NewComer::getCurGuideStep()))
			{
				NewComer::setCurGuideStep();
				_comer->removeFromParentAndCleanup(true);
				_comer = NewComer::create(this, 1002, 4);
			}
		}

		int slotCount = 0;
		int i_Level[] = { 1, 3, 6, 12 };
		for (int i = 0; i < 4; i++)
		{
			if ( interTeamInfoVector[ 0 ].teamLevel >= i_Level[ i ] )
			{
				slotCount = i + 1;
			}
		}
		if ( button->getTag() + 1 > slotCount )			// 当点击的上阵武将的格子未开启时
		{
			// 弹出提示：该位置多少等级开启
			__String* promptString ;
			if ( button->getTag() == 1 )
			{
				promptString = __String::createWithFormat("%s", mpFontChina->getComString("SlotB")->getCString());
			}
			else if ( button->getTag() == 2 )
			{
				promptString = __String::createWithFormat("%s", mpFontChina->getComString("SlotC")->getCString());
			}
			else
			{
				promptString = __String::createWithFormat("%s", mpFontChina->getComString("SlotD")->getCString());
			}
			auto prompt = PromptBox::getInstance(promptString->getCString());
			prompt->setFade();
			this->addChild(prompt, 20);
		}
		else
		{
			for (int i = 0; i < slotCount; i ++)
			{
				roleImageSelect[ i ]->setVisible(false);
				roleButtonSelect[ i ]->setVisible(false);
				roleButtonSelect[ i ]->setTouchEnabled(false);
				if ( i == button->getTag() )
				{				
					panelState = PresetState;
					posIndex = i + 1;	
					roleImageSelect[ i ]->setVisible(true);
					if ( interPointSetsVector.size() != 0 )
					{
						for (unsigned int z = 0; z < interPointSetsVector.size(); z ++)
						{
							if ( ( interPointSetsVector[ z ].generalPos == posIndex ) && ( posIndex != 1 ) )
							{
								roleButtonSelect[ i ]->setVisible(true);
								roleButtonSelect[ i ]->setTouchEnabled(true);
							}							
						}						
					}
				}
			}	
		}			
	}
}

void Maidan::heroCloseCallBack(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		ToolFunc::playEffectFile( Click );
		auto button = (Button*)pSender;
		for (unsigned int i = 0; i < interPointSetsVector.size(); i ++)
		{
			if ( interPointSetsVector[ i ].generalPos == button->getTag() + 1 )
			{
				// 下阵逻辑
				if (DataManager::getInstance()->isCancelTheLine( button->getTag() + 1, interPointSetsVector[ i ].generalPKID))
				{
					initGeneralData();
					auto button = Button::create();
					button->setTag( i_ButtonFlag );
					typeButton(button, TOUCH_EVENT_ENDED);
					showGeneral();
					initPresetPanel();
				}
			}
		}
	}
}

void Maidan::propIamgeCallBack(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		ToolFunc::playEffectFile( Click );
		auto button = (Button* )pSender;

		if (false == NewComer::isGuideDone(1004))
		{
			if (0 != button->getTag())
			{
				return;
			}
			if (5 == NewComer::getCurGuideStep())
			{
				NewComer::setCurGuideStep();
				_comer->removeFromParentAndCleanup(true);
				_comer = NewComer::create(this, 1004, 6);
			}
		}

		for (int i = 0; i < 3; i ++)
		{
			auto selectString = __String::createWithFormat("Image_Role_%d_1", i + 1);
			auto label = dynamic_cast<ImageView* >(Helper::seekWidgetByName(enhancePanel, selectString->getCString()));
			label->setVisible(false);
			if ( i == button->getTag())
			{
				label->setVisible(true);
				propID = 93002 + i;
			}
		}
	}
}

void Maidan::setButtonBirght(TypeButton buttonBright)
{
	for (int i = 0; i < 4; i ++)
	{
		auto comBtn = (Button*)rightButtonPanel->getChildByTag( i );
		comBtn->setBrightStyle(BrightStyle::BRIGHT_NORMAL);
		comBtn->setLocalZOrder(0);
		if ( i == buttonBright)
		{
			auto comBtnCopy = (Button*)rightButtonPanel->getChildByTag( i );
			comBtn->setBrightStyle(BrightStyle::BRIGHT_HIGHLIGHT);
			comBtnCopy->setLocalZOrder(99);
		}
	}
}

void Maidan::panelTouchCallback(Ref* pSender, TouchEventType type)
{
	auto ptLoc = Point(0, 0);
	auto task = (Widget *)pSender;
	auto pBar = (LoadingBar *)task->getChildByName("ProgressBar");
	auto tag = task->getTag();
	auto scroll = (cocos2d::ui::ScrollView *)task->getParent()->getParent()->getParent();
	auto inner = scroll->getInnerContainer();
	auto temp = scroll->getContentSize().height - inner->getContentSize().height;

	if ( TouchEventType::TOUCH_EVENT_ENDED == type )
	{
		ptLoc = task->getTouchEndPos();

		if (false == NewComer::isGuideDone(1000))					/* 引导ID为0，且点击的是第一个武将，步骤自增 */
		{
			if (0 != tag)
			{
				return;
			}
			NewComer::setCurGuideStep();
		}
		else if (false == NewComer::isGuideDone(1002))				/* 引导ID为2，且点击的是第2个武将，步骤自增 */
		{
			if (4 == NewComer::getCurGuideStep())					/* 已选中上阵位置 */
			{
				if (1 != tag)
				{
					return;
				}
				NewComer::setCurGuideStep();
				_comer->removeFromParentAndCleanup(true);
				_comer = NULL;
			}
		}
		else if (false == NewComer::isGuideDone(1004))				/* 引导ID为4，且点击的是第2个武将，步骤自增 */
		{
			if (6 == NewComer::getCurGuideStep())
			{
				if (1 != tag)
				{
					return;
				}
				NewComer::setCurGuideStep();
				_comer->removeFromParentAndCleanup(true);
				_comer = NULL;
			}
		}
		else if (false == NewComer::isGuideDone(1005))				/* 引导ID为5，且点击的是第1个武将，步骤自增 */
		{
			if (0 != tag)
			{
				return;
			}
			if (1 == NewComer::getCurGuideStep())
			{
				NewComer::setCurGuideStep();
				_comer->removeFromParentAndCleanup(true);
				_comer = NULL;
			}
		}
		else if ((false == NewComer::isGuideDone(1009)) || 			/* 引导ID为9，且点击的是第1个武将，步骤自增 */
			(false == NewComer::isGuideDone(1010))) 				/* 引导ID为10，且点击的是第1个武将，步骤自增 */
		{
			if (0 != tag)
			{
				return;
			}
			if (1 == NewComer::getCurGuideStep())
			{
				NewComer::setCurGuideStep();
				_comer->removeFromParentAndCleanup(true);
				_comer = NULL;
			}
		}
		else
		{
		}

		if ( (( (ptLoc.x <= m_ptTouchLoc.x + 10) && ( ptLoc.y <= m_ptTouchLoc.y + 10 )) || ( (ptLoc.x >= m_ptTouchLoc.x - 10) && ( ptLoc.y >= m_ptTouchLoc.y - 10 ) ) ) && (panelState == NoneState) )
		{
			for (unsigned int i = 0; i < curGeneralVector.size(); i ++)
			{
				if (curGeneralVector[ i ].PKID == tempGeneralVector[ tag ].PKID)
				{
					ToolFunc::playEffectFile( Click );
					DataManager::getInstance()->reGeneralVector.clear();
					DataManager::getInstance()->reGeneralVector.push_back(curGeneralVector[ i ]);
					Director::getInstance()->pushScene(GeneralDetails::create());
				}
			}
		}
		else if (panelState == PresetState)															// 预设
		{ 
			if ( tempGeneralVector[ tag ].isSelect != 0 )
			{
				for (int i = 0; i < 4; i ++)
				{
					roleImageSelect[ i ]->setVisible(false);
					panelState = NoneState;
				}
				return;
			}			

			if ( posIndex != -1 )																// 没有点击头像框位置
			{
				if ( interPointSetsVector.size() != 0 )
				{
					for (unsigned int i = 0; i < interPointSetsVector.size(); i ++)
					{
						if ( posIndex == interPointSetsVector[ i ].generalPos )							// 如果当前的位置有武将
						{
							// 换
							if (DataManager::getInstance()->isChangeTheLine(posIndex, interPointSetsVector[ i ].generalPKID, tempGeneralVector[ tag ].PKID))
							{
								for (int i = 0; i < 4; i ++)
								{
									roleImageSelect[ i ]->setVisible(false);
									panelState = NoneState;
								}
								initGeneralData();
								auto button = Button::create();
								button->setTag( i_ButtonFlag );
								typeButton(button, TOUCH_EVENT_ENDED);
								initPresetPanel();
								showGeneral();
							}
						}
						else    // 上阵
						{
							if (DataManager::getInstance()->isSelectGeneral(posIndex, tempGeneralVector[ tag ].PKID))
							{
								for (int i = 0; i < 4; i ++)
								{
									roleImageSelect[ i ]->setVisible(false);
									panelState = NoneState;
								}
								initGeneralData();
								auto button = Button::create();
								button->setTag( i_ButtonFlag );
								typeButton(button, TOUCH_EVENT_ENDED);
								initPresetPanel();
								showGeneral();
							}
						}
					}	
				}	
				else
				{
					if (DataManager::getInstance()->isSelectGeneral(posIndex, tempGeneralVector[ tag ].PKID))
					{
						for (int i = 0; i < 4; i ++)
						{
							roleImageSelect[ i ]->setVisible(false);
							panelState = NoneState;
						}
						ToolFunc::playEffectFile( Click );
						initGeneralData();
						auto button = Button::create();
						button->setTag( i_ButtonFlag );
						typeButton(button, TOUCH_EVENT_ENDED);
						initPresetPanel();
						showGeneral();
					}
				}
			}				
		}
		else if (panelState == EnhanceState)														// 强化
		{
			if (propID != -1)
			{
				DataManager::getInstance()->isSortGoodsNum(propID);
				int num = DataManager::getInstance()->sortGoodsNum();
				if ( num == 0 )
				{
					// 弹出提示：物品数量为零
					auto prot = PromptBox::getInstance(mpFontChina->getComString("PropNumZero")->getCString());
					prot->setFade();
					this->addChild(prot, 20);
					return;
				}
				for (unsigned int i = 0; i < curGeneralVector.size(); i ++)
				{
					if (curGeneralVector[ i ].PKID == tempGeneralVector[ tag ].PKID)
					{
						if ( curGeneralVector[ i ].level >= interTeamInfoVector[ 0 ].teamLevel  )
						{
							// 武将等级不能高于战队等级
							auto promp = PromptBox::getInstance(mpFontChina->getComString("Plus1")->getCString());
							promp->setFade();
							this->addChild(promp, 10);
						}
						else if ( curGeneralVector[ i ].level >= 50 )
						{
							// 武将等级达到50级上限
							auto promp = PromptBox::getInstance(mpFontChina->getComString("Plus225")->getCString());
							promp->setFade();
							this->addChild(promp, 10);
						}
						else
						{
							int exp = curGeneralVector[ i ].strongExp + localPropVectro[ propID - 93001 ].pExpAdd;
							if (DataManager::getInstance()->isEnhanceGeneral(tempGeneralVector[ tag ].PKID, exp, calcGeneralLevel(exp), propID))
							{							
								initGeneralData();
								showGeneral();
								auto button = Button::create();
								button->setTag( i_ButtonFlag );
								typeButton(button, TOUCH_EVENT_ENDED);
								initEnhanceProp();
							}
						}						
					}
				}				
			}
		}
	}
	else if ( TouchEventType::TOUCH_EVENT_BEGAN == type )
	{
		m_ptTouchLoc = task->getTouchStartPos();
		m_ptOriginleLoc = inner->getPosition();
	}
	else if ( TouchEventType::TOUCH_EVENT_MOVED == type )
	{
		ptLoc = task->getTouchMovePos();
		auto pt = m_ptOriginleLoc.y + ptLoc.y - m_ptTouchLoc.y;
		pt = (pt > 0) ? 0 : pt;
		pt = (pt < temp) ? temp : pt;
		inner->setPositionY(pt);
	}
}

void Maidan::closeButton(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		if (false == NewComer::isGuideDone(1000))					/* 引导ID为0，且未完成 */
		{
			if (5 != NewComer::getCurGuideStep())					/* 值为5，表示已经穿上装备 */
			{
				NewComer::setCurGuideStep(-1);
			}
		}
		else if (false == NewComer::isGuideDone(1002))				/* 引导ID为2，且未完成 */
		{
			if (4 == NewComer::getCurGuideStep())					/* 值为3，表示未选武将上阵位置 */
			{
				NewComer::setCurGuideStep(-1);
			}
		}
		else if (false == NewComer::isGuideDone(1004))				/* 引导ID为4，且未完成 */
		{
			auto step = NewComer::getCurGuideStep();
			if (7 != step)											/* 选中了药水，没点武将进行升级 */
			{
				NewComer::setCurGuideStep(3 - step);
			}
		}
		else if (false == NewComer::isGuideDone(1005))				/* 引导ID为5，且未完成 */
		{
			auto step = NewComer::getCurGuideStep();
			if (1 == step)											/* 未完成技能升级 */
			{
				NewComer::setCurGuideStep(-1);
			}
		}
		else if ((false == NewComer::isGuideDone(1009)) ||			/* 引导ID为9，且未完成 */
			(false == NewComer::isGuideDone(1010)))					/* 引导ID为10，且未完成 */
		{
			NewComer::setCurGuideStep(0);
		}
		else
		{
		}

		ToolFunc::playEffectFile( Click );
		Director::getInstance()->replaceScene(MainScene::scene());
	}
}

void Maidan::typeButton(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{		
		tempGeneralVector.clear();
		auto button = (Button*)pSender;
		i_ButtonFlag = button->getTag();
		setButtonBirght((TypeButton)button->getTag());
		if (button->getTag() == 0)
		{
			tempGeneralVector = curGeneralVector;
		}
		else
		{
			ToolFunc::playEffectFile( Click );
			for (unsigned int i = 0; i < curGeneralVector.size(); i ++)
			{
				if (curGeneralVector[ i ].jobType == button->getTag())
				{
					tempGeneralVector.push_back(curGeneralVector[ i ]);
				}
			}
		}
		showGeneral();
	}
}

void Maidan::enhanceButton(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		if (false == NewComer::isGuideDone(1004))
		{
			if (4 == NewComer::getCurGuideStep())
			{
				NewComer::setCurGuideStep();
				_comer->removeFromParentAndCleanup(true);
				_comer = NewComer::create(this, 1004, 5);
			}
		}

		panelState = EnhanceState;
		enhancePanel->setVisible(true);
		enhancePanel->setTouchEnabled(true);
		enhancePanel->setLocalZOrder(35);
		presetPanel->setLocalZOrder(0);
		presetPanel->setVisible(false);
		presetPanel->setTouchEnabled(false);
		ToolFunc::playEffectFile( Click );
		initEnhanceProp();
	}
}

void Maidan::preSetButton(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		if ( pSender != NULL )
		{
			ToolFunc::playEffectFile( Click );
		}
		panelState = NoneState;
		enhancePanel->setVisible(false);
		enhancePanel->setTouchEnabled(false);
		enhancePanel->setLocalZOrder(0);
		presetPanel->setLocalZOrder(35);
		presetPanel->setVisible(true);
		presetPanel->setTouchEnabled(true);
		
		initPresetPanel();
	}
}

int Maidan::calcGeneralLevel(int exp)
{
	int resultInt = 0;
	for (unsigned int i = 0; i < localGeneralUpgradeVector.size(); i ++)
	{
		if (localGeneralUpgradeVector[ i ].gNeedExp >= exp)
		{
			resultInt = i;
			break;
		}
		else
		{
			exp -= localGeneralUpgradeVector[ i ].gNeedExp;
		}
	}
	return resultInt + 1;
}

int Maidan::calcPreFighting(vector<PointSetsRecvStruct > pointVec)
{
	int resultInt = 0;
	for (unsigned int i = 0; i < pointVec.size(); i ++)
	{
		if (pointVec[ i ].generalID != 0)													// 有武将上阵
		{
			if ( DataManager::getInstance()->isGetGeneralProperty(pointVec[ i ].generalPKID) )		// 获取上阵武将的详情	
			{
				auto generalDetialVec = DataManager::getInstance()->interGeneralVector();
				int curRoleID = pointVec[ i ].generalID + generalDetialVec[ 0 ].starLevel - 1 - 10001;
				int hpValue = localGeneralVector[ curRoleID ].initHP + localGeneralVector[ curRoleID ].hpGrowing * (generalDetialVec[ 0 ].level - 1);			// 人物相应生命值
				if (generalDetialVec[ 0 ].equipID[ 0 ] != 0)		// 类型1有装备
				{
					int basicHP = localEquipVector[ generalDetialVec[ 0 ].equipID[ 0 ] - 94001 ].eHP;
					float incHP = 0.0f ;
					if ( (localEquipVector[ generalDetialVec[ 0 ].equipID[ 0 ] - 94001 ].eColor == 1) && (generalDetialVec[ 0 ].equipLevel[ 0 ] != 0) )
					{
						incHP += 0.1 + (generalDetialVec[ 0 ].equipLevel[ 0 ] - 1) * 0.008;
					}
					else if ( (localEquipVector[ generalDetialVec[ 0 ].equipID[ 0 ] - 94001 ].eColor == 2) && (generalDetialVec[ 0 ].equipLevel[ 0 ] != 0) )
					{
						incHP += 0.2 + (generalDetialVec[ 0 ].equipLevel[ 0 ] - 1) * 0.01;
					}
					else if ( (localEquipVector[ generalDetialVec[ 0 ].equipID[ 0 ] - 94001 ].eColor == 3) && (generalDetialVec[ 0 ].equipLevel[ 0 ] != 0) )
					{
						incHP += 0.2 + (generalDetialVec[ 0 ].equipLevel[ 0 ] - 1) * 0.01;
					}
					else if ( (localEquipVector[ generalDetialVec[ 0 ].equipID[ 0 ] - 94001 ].eColor == 4) && (generalDetialVec[ 0 ].equipLevel[ 0 ] != 0) )
					{
						incHP += 0.3 + (generalDetialVec[ 0 ].equipLevel[ 0 ] - 1) * 0.01;
					}
					hpValue += basicHP * ( 1 + incHP ) ;
				}
				int atkValue = localGeneralVector[ curRoleID ].initAtk + localGeneralVector[ curRoleID ].atkGrowing * (generalDetialVec[ 0 ].level - 1);
				if (generalDetialVec[ 0 ].equipID[ 3 ] != 0)
				{
					int basicAtk = localEquipVector[ generalDetialVec[ 0 ].equipID[ 3 ] - 94001 ].eAtk;
					float incAtk = 0.0f ;
					if ( (localEquipVector[ generalDetialVec[ 0 ].equipID[ 3 ] - 94001 ].eColor == 1) && (generalDetialVec[ 0 ].equipLevel[ 3 ] != 0) )
					{
						incAtk += 0.1 + (generalDetialVec[ 0 ].equipLevel[ 3 ] - 1) * 0.008;
					}
					else if ( (localEquipVector[ generalDetialVec[ 0 ].equipID[ 3 ] - 94001 ].eColor == 2) && (generalDetialVec[ 0 ].equipLevel[ 3 ] != 0) )
					{
						incAtk += 0.2 + (generalDetialVec[ 0 ].equipLevel[ 3 ] - 1) * 0.01;
					}
					else if ( (localEquipVector[ generalDetialVec[ 0 ].equipID[ 3 ] - 94001 ].eColor == 3) && (generalDetialVec[ 0 ].equipLevel[ 3 ] != 0) )
					{
						incAtk += 0.2 + (generalDetialVec[ 0 ].equipLevel[ 3 ] - 1) * 0.01;
					}
					else if ( (localEquipVector[ generalDetialVec[ 0 ].equipID[ 3 ] - 94001 ].eColor == 4) && (generalDetialVec[ 0 ].equipLevel[ 3 ] != 0) )
					{
						incAtk += 0.3 + (generalDetialVec[ 0 ].equipLevel[ 3 ] - 1) * 0.01;
					}
					atkValue += basicAtk * ( 1 + incAtk ) ;
				}
				int pdValue = localGeneralVector[ curRoleID ].initPD + localGeneralVector[ curRoleID ].pdGrowing * (generalDetialVec[ 0 ].level - 1);
				if (generalDetialVec[ 0 ].equipID[ 1 ] != 0)
				{
					int basicPD = localEquipVector[ generalDetialVec[ 0 ].equipID[ 1 ] - 94001 ].ePD;
					float incPD = 0.0f ;
					if ( (localEquipVector[ generalDetialVec[ 0 ].equipID[ 1 ] - 94001 ].eColor == 1) && (generalDetialVec[ 0 ].equipLevel[ 1 ] != 0) )
					{
						incPD += 0.1 + (generalDetialVec[ 0 ].equipLevel[ 1 ] - 1) * 0.008;
					}
					else if ( (localEquipVector[ generalDetialVec[ 0 ].equipID[ 1 ] - 94001 ].eColor == 2) && (generalDetialVec[ 0 ].equipLevel[ 1 ] != 0) )
					{
						incPD += 0.2 + (generalDetialVec[ 0 ].equipLevel[ 1 ] - 1) * 0.01;
					}
					else if ( (localEquipVector[ generalDetialVec[ 0 ].equipID[ 1 ] - 94001 ].eColor == 3) && (generalDetialVec[ 0 ].equipLevel[ 1 ] != 0) )
					{
						incPD += 0.2 + (generalDetialVec[ 0 ].equipLevel[ 1 ] - 1) * 0.01;
					}
					else if ( (localEquipVector[ generalDetialVec[ 0 ].equipID[ 1 ] - 94001 ].eColor == 4) && (generalDetialVec[ 0 ].equipLevel[ 1 ] != 0) )
					{
						incPD += 0.3 + (generalDetialVec[ 0 ].equipLevel[ 1 ] - 1) * 0.01;
					}
					pdValue += basicPD * ( 1 + incPD ) ;
				}
				int mdValue = localGeneralVector[ curRoleID ].initMD + localGeneralVector[ curRoleID ].mdGrowing * (generalDetialVec[ 0 ].level - 1);
				if (generalDetialVec[ 0 ].equipID[ 2 ] != 0)
				{
					int basicMD = localEquipVector[ generalDetialVec[ 0 ].equipID[ 2 ] - 94001 ].eMD;
					float incMD = 0.0f ;
					if ( (localEquipVector[ generalDetialVec[ 0 ].equipID[ 2 ] - 94001 ].eColor == 1) && (generalDetialVec[ 0 ].equipLevel[ 2 ] != 0) )
					{
						incMD += 0.1 + (generalDetialVec[ 0 ].equipLevel[ 2 ] - 1) * 0.008;
					}
					else if ( (localEquipVector[ generalDetialVec[ 0 ].equipID[ 2 ] - 94001 ].eColor == 2) && (generalDetialVec[ 0 ].equipLevel[ 2 ] != 0) )
					{
						incMD += 0.2 + (generalDetialVec[ 0 ].equipLevel[ 2 ] - 1) * 0.01;
					}
					else if ( (localEquipVector[ generalDetialVec[ 0 ].equipID[ 2 ] - 94001 ].eColor == 3) && (generalDetialVec[ 0 ].equipLevel[ 2 ] != 0) )
					{
						incMD += 0.2 + (generalDetialVec[ 0 ].equipLevel[ 2 ] - 1) * 0.01;
					}
					else if ( (localEquipVector[ generalDetialVec[ 0 ].equipID[ 2 ] - 94001 ].eColor == 4) && (generalDetialVec[ 0 ].equipLevel[ 2 ] != 0) )
					{
						incMD += 0.3 + (generalDetialVec[ 0 ].equipLevel[ 2 ] - 1) * 0.01;
					}
					mdValue += basicMD * ( 1 + incMD ) ;
				}
				auto localSkillAddPropty = DataManager::getInstance()->localSkillAddProptyVec();
				if (localSkillAddPropty.size() == 0)
				{
					DataManager::getInstance()->skillUpgradeProptyAdd();
					localSkillAddPropty = DataManager::getInstance()->localSkillAddProptyVec();
				}
				if (generalDetialVec[ 0 ].skillLevel[ 0 ] != 0)
				{
					if (curGeneralVector[ 0 ].maxStar == 5)
					{
						pdValue += localSkillAddPropty[ 0 ].ePD + generalDetialVec[ 0 ].skillLevel[ 0 ] * localSkillAddPropty[ 0 ].ePDLen;
					}
					else if (curGeneralVector[ 0 ].maxStar == 4)
					{
						pdValue += localSkillAddPropty[ 0 ].dPD + generalDetialVec[ 0 ].skillLevel[ 0 ] * localSkillAddPropty[ 0 ].dPDLen;
					}
					else if (curGeneralVector[ 0 ].maxStar == 3)
					{
						pdValue += localSkillAddPropty[ 0 ].cPD + generalDetialVec[ 0 ].skillLevel[ 0 ] * localSkillAddPropty[ 0 ].cPDLen;
					}
				}
				if (generalDetialVec[ 0 ].skillLevel[ 1 ] != 0)
				{
					if (curGeneralVector[ 0 ].maxStar == 5)
					{
						mdValue += localSkillAddPropty[ 0 ].eMD + generalDetialVec[ 0 ].skillLevel[ 1 ] * localSkillAddPropty[ 0 ].eMDLen;
					}
					else if (curGeneralVector[ 0 ].maxStar == 4)
					{
						mdValue += localSkillAddPropty[ 0 ].dMD + generalDetialVec[ 0 ].skillLevel[ 1 ] * localSkillAddPropty[ 0 ].dMDLen;
					}
					else if (curGeneralVector[ 0 ].maxStar == 3)
					{
						mdValue += localSkillAddPropty[ 0 ].cMD + generalDetialVec[ 0 ].skillLevel[ 1 ] * localSkillAddPropty[ 0 ].cMDLen;
					}
				}
				if (generalDetialVec[ 0 ].skillLevel[ 2 ] != 0)
				{
					if (curGeneralVector[ 0 ].maxStar == 5)
					{
						hpValue += localSkillAddPropty[ 0 ].eHP + generalDetialVec[ 0 ].skillLevel[ 2 ] * localSkillAddPropty[ 0 ].eHPLen;
					}
					else if (curGeneralVector[ 0 ].maxStar == 4)
					{
						hpValue += localSkillAddPropty[ 0 ].dHP + generalDetialVec[ 0 ].skillLevel[ 2 ] * localSkillAddPropty[ 0 ].dHPLen;
					}
				}
				if (generalDetialVec[ 0 ].skillLevel[ 3 ] != 0)
				{
					if (curGeneralVector[ 0 ].maxStar == 5)
					{
						atkValue += localSkillAddPropty[ 0 ].eATK + generalDetialVec[ 0 ].skillLevel[ 3 ] * localSkillAddPropty[ 0 ].eAtkLen;
					}
				}
				vector<int > growthVector;
				if ( DataManager::getInstance()->isGetGeneralGrowth( pointVec[ i ].generalPKID ) )
				{
					growthVector = DataManager::getInstance()->getGeneralGrowthVector();
				}
				resultInt += ( hpValue + growthVector[ 1 ] ) / 5 + atkValue + growthVector[ 0 ] + (pdValue + growthVector[ 2 ] + mdValue + growthVector[ 3 ]) / 2;
			}
		}
	}
	return resultInt;
}

void Maidan::onEnter()
{
	Layer::onEnter();

	initGeneralData();
	auto button = Button::create();
	button->setTag( 0 );
	typeButton(button, TOUCH_EVENT_ENDED);
	preSetButton(NULL, TOUCH_EVENT_ENDED);

	if (false == NewComer::isGuideDone(1000))						/* 引导ID为0，且未完成 */
	{
		_comer = NewComer::create(this, 1000, 2);					/* 引导点击武将 */
	}
	else if (false == NewComer::isGuideDone(1002))					/* 引导ID为2，且未完成 */
	{
		_comer = NewComer::create(this, 1002, 3);
	}
	else if (false == NewComer::isGuideDone(1004))					/* 引导ID为4，且未完成 */
	{
		_comer = NewComer::create(this, 1004, 4);
	}
	else if (false == NewComer::isGuideDone(1005))					/* 引导ID为5，且未完成 */
	{
		_comer = NewComer::create(this, 1005, 1);
	}
	else if (false == NewComer::isGuideDone(1009))					/* 引导ID为9，且未完成 */
	{
		_comer = NewComer::create(this, 1009, 1);
	}
	else if (false == NewComer::isGuideDone(1010))					/* 引导ID为10，且未完成 */
	{
		_comer = NewComer::create(this, 1010, 1);
	}
	else
	{
		_comer = NULL;
	}
}

void Maidan::onExit()
{
	// 触摸状态移除------未添加
	if (NULL != _comer)
	{
		_comer->removeFromParentAndCleanup(true);
		_comer = NULL;
	}
	Layer::onExit();
}