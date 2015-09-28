#include "EquipmentInfo.h"
#include "Public/ToolFunc.h"
#include "UserInfo/Define_Info.h"

const Point LayerPoint = Point(310, 20);				// 装备显示层位置
const Point InfoPoint = Point(20, 30);				// 装备信息显示位置
const Size cellSize = Size(95.0f, 95.0f);				// 滚动层cell size 
const float cellScale = 1.0f;
const float FontSize = 18.0f;
const int Label1 = 60;
const int Label2 = 61;

EquipmentInfo::EquipmentInfo()
{
	isFull = false;
}

EquipmentInfo::~EquipmentInfo()
{

}

bool EquipmentInfo::init()
{
	mpFontChina = FontChina::getInstance();
	mpFontChina->initStringXml();
	_comer = NULL;

	auto equipInfoUI = GUIReader::getInstance()->widgetFromJsonFile("UI/All/SelectEquip.ExportJson");
	this->addChild(equipInfoUI);

	singleInfo = dynamic_cast<Layout* >(Helper::seekWidgetByName(equipInfoUI, "Panel_Left"));
	equipmentLayer = dynamic_cast<Layout* >(Helper::seekWidgetByName(equipInfoUI, "Panel_Right"));

	auto closeButton = dynamic_cast<Button* >(Helper::seekWidgetByName(equipInfoUI, "Button_Close"));
	closeButton->addTouchEventListener(this, toucheventselector(EquipmentInfo::closeClick));
	
	auto panelRight = dynamic_cast<Layout* >(Helper::seekWidgetByName(equipmentLayer, "Panel_Right"));
	equipmentScrollView = dynamic_cast<cocos2d::ui::ScrollView* >(Helper::seekWidgetByName(panelRight, "ScrollView_Equip"));

	interGeneralEquipVector = DataManager::getInstance()->interGeneralVector();										// 获取武将装备信息

	initEquipmentData();

	showEquipment();
	if (interGeneralEquipVector[ 0 ].equipID[ DataManager::getInstance()->equipType -1 ] == 0)							// 点击的位置没有装备
	{
		isFull = true;
		if (tempEquipVector.size() != 0)
		{
			singleEquipmentInfo(tempEquipVector[ 0 ].ePKID, 1);
		}		
	}
	else
	{
		isFull = false;
		EquipProptyStruct equipStrcut;
		memset(&equipStrcut, 0, sizeof(equipStrcut));
		for (unsigned int i = 0; i < interEquipVector.size(); i ++)
		{
			if (interEquipVector[ i ].itemsID == 0)
			{
				continue;
			}
			if ( interGeneralEquipVector[ 0 ].equipPKID[ DataManager::getInstance()->equipType -1 ] == interEquipVector[ i ].itemPKID )																	// 颜色类型相同并且没有被使用
			{
				equipStrcut.ePKID = interEquipVector[ i ].itemPKID;
				equipStrcut.eID = interEquipVector[ i ].itemsID;
				equipStrcut.eLevel = interEquipVector[ i ].itemsLevel;
				tempEquipVector.push_back(equipStrcut);
			}
		}
		singleEquipmentInfo(interGeneralEquipVector[ 0 ].equipPKID[ DataManager::getInstance()->equipType -1 ], 1);
	}

	return true;
}

void EquipmentInfo::initEquipmentData()
{
	localEquipVector = DataManager::getInstance()->localEquipProptyVector();
	if (localEquipVector.size() == 0)
	{
		DataManager::getInstance()->equipDataParser();
		localEquipVector = DataManager::getInstance()->localEquipProptyVector();
	}
	if (DataManager::getInstance()->isGetEquipData())
	{
		interEquipVector = DataManager::getInstance()->interWareroomEquipVector();
	}	
	
	EquipProptyStruct equipStrcut;
	memset(&equipStrcut, 0, sizeof(equipStrcut));
	for (unsigned int i = 0; i < interEquipVector.size(); i ++)
	{
		if (interEquipVector[ i ].itemsID == 0)
		{
			continue;
		}
		if ( (localEquipVector[ interEquipVector[ i ].itemsID - 94001 ].ePositionType == DataManager::getInstance()->equipType) &&
			(interEquipVector[ i ].isSelect != 1) )																	// 颜色类型相同并且没有被使用
		{
			equipStrcut.ePKID = interEquipVector[ i ].itemPKID;
			equipStrcut.eID = interEquipVector[ i ].itemsID;
			equipStrcut.eLevel = interEquipVector[ i ].itemsLevel;
			tempEquipVector.push_back(equipStrcut);
		}
	}
}

void EquipmentInfo::showEquipment()
{
	if (tempEquipVector.size() == 0)
	{
		auto label = Label::create();
		label->setPosition(Point(220, 150));
		label->setString(mpFontChina->getComString("DetailNoEquip")->getCString());
		label->setSystemFontSize(18.0f);
		equipmentScrollView->addChild(label);
		return;
	}
	equipmentScrollView->removeAllChildrenWithCleanup(true);
	int cellCount = tempEquipVector.size();
	auto cell_Size = cellSize * cellScale;
	Size szInnerContainer = equipmentScrollView->getContentSize();
	int cellGap = 0;									// 滚动层cell间隔 
	int cellHeightGap = 10;								// 滚动层cell间隔 

	auto columuNum = cellCount / 4;
	if ( cellCount % 4 != 0 )
	{
		columuNum ++;
	}
	auto height = (cellSize.height * cellScale + cellHeightGap) * columuNum ;
	height = (height > szInnerContainer.height) ? height : szInnerContainer.height;
	equipmentScrollView->setInnerContainerSize(Size(szInnerContainer.width, height));
	for (unsigned int i = 0; i < tempEquipVector.size(); i ++)
	{
		auto nameString = __String::createWithFormat("%d.png", localEquipVector[ tempEquipVector[ i ].eID - 94001 ].eID);
		auto equip = EquipmentCell::create();
		equip->setImage(nameString->getCString());
		equip->setPosition(Point( ( i % 4 ) * (cellSize.width * cellScale + cellGap) + 10,
     			height - ( i / 4 + 1 ) * (cellSize.height * cellScale + cellHeightGap)));
		equip->setScale(0.8f);
		equip->setTag( 100 + i );
		equip->equipmentPanel->setTag( tempEquipVector[ i ].ePKID );
		equip->equipmentPanel->setTouchEnabled(true);
		equip->equipmentPanel->addTouchEventListener(this, toucheventselector(EquipmentInfo::imageClick));
		equipmentScrollView->addChild(equip);
	}	
}

void EquipmentInfo::singleEquipmentInfo(int pkID, int typeClick)
{
	equipmentPKID = pkID;
	for (unsigned int i = 0; i < tempEquipVector.size(); i ++)
	{
		if (tempEquipVector[ i ].ePKID == pkID)
		{
			auto singlePanel = dynamic_cast<Layout* >(Helper::seekWidgetByName(singleInfo, "Panel_Left"));								// 获取属性面板
			auto nameImageString = __String::createWithFormat("%d.png", localEquipVector[ tempEquipVector[ i ].eID - 94001 ].eID);			
			auto nameImage = dynamic_cast<ImageView* >(Helper::seekWidgetByName(singlePanel, "Image_Equip_0"));						// 设置物品图片
			nameImage->loadTexture(nameImageString->getCString(), TextureResType::UI_TEX_TYPE_PLIST);
			nameImage->setScale(81.0f / 120.0f);
			auto nameText = dynamic_cast<Text* >(Helper::seekWidgetByName(singlePanel, "Label_Name"));								// 装备名称
			if (tempEquipVector[ i ].eLevel == 0)
			{
				auto equipLevel = __String::createWithFormat("%s", localEquipVector[ tempEquipVector[ i ].eID - 94001 ].eChinaName);
				nameText->setText(equipLevel->getCString());
			}
			else
			{
				auto equipLevel = __String::createWithFormat("%s+%d", localEquipVector[ tempEquipVector[ i ].eID - 94001 ].eChinaName, tempEquipVector[ i ].eLevel);
				nameText->setText(equipLevel->getCString());
			}
			for (int z = 60; z < 62; z ++)
			{
				singlePanel->removeChildByTag( z );
			}
																											// 功能按钮
			auto equipButton = dynamic_cast<Button*>(Helper::seekWidgetByName(singlePanel, "Button_Equip"));						// 装备按钮
			equipButton->addTouchEventListener(this, toucheventselector(EquipmentInfo::equipClick));
			equipButton->setVisible(false);
			equipButton->setTouchEnabled(false);

			auto changeButton = dynamic_cast<Button*>(Helper::seekWidgetByName(singlePanel, "Button_Change"));					// 更换
			changeButton->addTouchEventListener(this, toucheventselector(EquipmentInfo::changeClick));
			changeButton->setVisible(false);
			changeButton->setTouchEnabled(false);

			auto unloadButton = dynamic_cast<Button*>(Helper::seekWidgetByName(singlePanel, "Button_Unload"));					// 卸下
			unloadButton->addTouchEventListener(this, toucheventselector(EquipmentInfo::unloadClick));
			unloadButton->setVisible(false);
			unloadButton->setTouchEnabled(false);
			if (interGeneralEquipVector[ 0 ].equipID[ DataManager::getInstance()->equipType - 1 ] == 0)							// 点击的位置没有装备
			{
				equipButton->setVisible(true);
				equipButton->setTouchEnabled(true);

				if (false == NewComer::isGuideDone(1000))						/* 引导ID为0，且未完成 */
				{
					_comer = NewComer::create(this, 1000, 4);
				}
			}
			else
			{
				if ( interGeneralEquipVector[ 0 ].equipPKID[ DataManager::getInstance()->equipType - 1 ] == pkID )
				{
					unloadButton->setVisible(true);
					unloadButton->setTouchEnabled(true);	
				}
				else
				{
					changeButton->setVisible(true);
					changeButton->setTouchEnabled(true);
				}								
			}

			// 物品属性
			auto proptyLabel1 = (Text*)singlePanel->getChildByName("Label_Propty_1");
			proptyLabel1->setFontSize(FontSize);
			proptyLabel1->setVisible(false);
			auto proptyLabel2 = (Text*)singlePanel->getChildByName("Label_Propty_2");
			proptyLabel2->setFontSize(FontSize);
			proptyLabel2->setVisible(false);
			auto label1 = Label::create();
			label1->setSystemFontSize(FontSize);
			label1->setColor(Color3B(255, 76, 0));
			label1->setTag(Label1);
			singlePanel->addChild(label1, 10);
			auto label2 = Label::create();
			label2->setSystemFontSize(FontSize);
			label2->setColor(Color3B(255, 76, 0));
			label2->setTag(Label2);
			singlePanel->addChild(label2, 10);

			auto goodsTypeString = __String::createWithFormat("%s", localEquipVector[ tempEquipVector[ i ].eID - 94001 ].ePositionName);
			auto goodsDesString = __String::createWithFormat("%s", localEquipVector[ tempEquipVector[ i ].eID - 94001 ].eDes);
			auto typeLabel = dynamic_cast<Text*>(Helper::seekWidgetByName(singlePanel, "Label_Num"));
			auto desLabel = (Text*)singlePanel->getChildByName("Label_Des");
			typeLabel->setVisible(true);
			typeLabel->setText(goodsTypeString->getCString());

			desLabel->setVisible(true);
			desLabel->ignoreContentAdaptWithSize(false); 
			desLabel->setSize(Size(180, 150)); 
			desLabel->setTextHorizontalAlignment(TextHAlignment::LEFT);
			desLabel->setText(goodsDesString->getCString());	
			switch (localEquipVector[ tempEquipVector[ i ].eID - 94001 ].ePositionType)
			{
			case PosTypeHead:
				{
					proptyLabel1->setVisible(true);
					proptyLabel2->setVisible(false);
					proptyLabel1->setText(mpFontChina->getComString("PD")->getCString());

					auto hpString = __String::createWithFormat("%d", localEquipVector[ tempEquipVector[ i ].eID - 94001 ].ePD);
					label1->setPosition(Point(proptyLabel1->getPositionX() + proptyLabel1->getContentSize().width + 10, proptyLabel1->getPositionY()));
					label1->setString(hpString->getCString());
				}		
				break;
			case PosTypeArmour:
				{
					proptyLabel1->setVisible(true);
					proptyLabel2->setVisible(false);
					proptyLabel1->setText(mpFontChina->getComString("HP")->getCString());

					auto hpString = __String::createWithFormat("%d", localEquipVector[ tempEquipVector[ i ].eID - 94001 ].eHP);
					label1->setPosition(Point(proptyLabel1->getPositionX() + proptyLabel1->getContentSize().width + 10, proptyLabel1->getPositionY()));
					label1->setString(hpString->getCString());
				}		
				break;
			case PosTypeDecorations:
				{
					proptyLabel1->setVisible(true);
					proptyLabel1->setText(mpFontChina->getComString("MD")->getCString());
					proptyLabel2->setVisible(false);
					auto attackString = __String::createWithFormat("%d", localEquipVector[ tempEquipVector[ i ].eID - 94001 ].eMD);
					label1->setPosition(Point(proptyLabel1->getPositionX() + proptyLabel1->getContentSize().width + 10, proptyLabel1->getPositionY()));
					label1->setString(attackString->getCString());
				}		
				break;
			case PosTypeWeapons:
				{
					proptyLabel1->setVisible(true);
					proptyLabel2->setVisible(false);
					proptyLabel1->setText(mpFontChina->getComString("Attack")->getCString());
					label1->setPosition(proptyLabel1->getPosition().x + proptyLabel1->getContentSize().width + 10, proptyLabel1->getPosition().y);
					auto hpString = __String::createWithFormat("%d", localEquipVector[ tempEquipVector[ i ].eID - 94001 ].eAtk);
					label1->setString(hpString->getCString());
				}		
				break;
			case PosTypeQi:
				{
					proptyLabel1->setVisible(true);
					proptyLabel2->setVisible(true);
					proptyLabel1->setText(mpFontChina->getComString("APR")->getCString());
					label1->setPosition(proptyLabel1->getPosition().x + proptyLabel1->getContentSize().width + 10, proptyLabel1->getPosition().y);
					auto hpString = __String::createWithFormat("%.2f", localEquipVector[ tempEquipVector[ i ].eID - 94001 ].eAddCrit);
					label1->setString(hpString->getCString());

					proptyLabel2->setText(mpFontChina->getComString("RPR")->getCString());
					label2->setPosition(proptyLabel2->getPosition().x + proptyLabel2->getContentSize().width + 10, proptyLabel2->getPosition().y);
					auto hpString2 = __String::createWithFormat("%.2f", localEquipVector[ tempEquipVector[ i ].eID - 94001 ].eReduceCrit);
					label2->setString(hpString2->getCString());
				}
				break;
			case PosTypeYi:
				{
					proptyLabel1->setVisible(true);
					proptyLabel2->setVisible(true);
					proptyLabel1->setText(mpFontChina->getComString("ARH")->getCString());
					label1->setPosition(proptyLabel1->getPosition().x + proptyLabel1->getContentSize().width + 10, proptyLabel1->getPosition().y);
					auto hpString = __String::createWithFormat("%d", localEquipVector[ tempEquipVector[ i ].eID - 94001 ].eAddRealHurt);
					label1->setString(hpString->getCString());

					proptyLabel2->setText(mpFontChina->getComString("RRH")->getCString());
					label2->setPosition(proptyLabel2->getPosition().x + proptyLabel2->getContentSize().width + 10, proptyLabel2->getPosition().y);
					auto hpString2 = __String::createWithFormat("%d", localEquipVector[ tempEquipVector[ i ].eID - 94001 ].eReduceHurt);
					label2->setString(hpString2->getCString());
				}
				break;
			}		
		}
	}
}

void EquipmentInfo::closeClick(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		if (false == NewComer::isGuideDone(1000))					/* 引导ID为0，且未完成 */
		{
			if (5 != NewComer::getCurGuideStep())					/* 值为5，表示已经穿上装备 */
			{
				if (NULL != _comer)									/* 执行了引导 */
				{
					NewComer::setCurGuideStep(-1);
				}
			}
		}

		ToolFunc::playEffectFile( Click );
		Director::getInstance()->popScene();
	}
}

void EquipmentInfo::imageClick(Ref* pSender, TouchEventType type)
{
	auto ptLoc = Point(0, 0);
	auto task = (Widget *)pSender;
	auto tag = task->getTag();
	auto scroll = (cocos2d::ui::ScrollView *)task->getParent()->getParent()->getParent();
	auto inner = scroll->getInnerContainer();
	auto temp = scroll->getContentSize().height - inner->getContentSize().height;

	if ( isFull )
	{
		for (unsigned int i = 0; i < tempEquipVector.size(); i++)
		{
			auto ttt = (EquipmentCell*)equipmentScrollView->getChildByTag( 100 + i );
			auto equipBG = dynamic_cast<ImageView* >(ttt->equipmentPanel->getChildByName("Image_BG"));
			equipBG->loadTexture("TempPic/Selected.png");
			equipBG->setScale( 1.3f );
			equipBG->setVisible(false);
		}
	}
	else
	{
		for (unsigned int i = 0; i < tempEquipVector.size() - 1; i++)
		{
			auto ttt = (EquipmentCell*)equipmentScrollView->getChildByTag( 100 + i );
			auto equipBG = dynamic_cast<ImageView* >(ttt->equipmentPanel->getChildByName("Image_BG"));
			equipBG->loadTexture("TempPic/Selected.png");
			equipBG->setScale( 1.3f );
			equipBG->setVisible(false);
		}
	}
	

	if (type == TOUCH_EVENT_ENDED)
	{
		ptLoc = task->getTouchEndPos();
		if ( ( (ptLoc.x <= m_ptTouchLoc.x + 10) && ( ptLoc.y <= m_ptTouchLoc.y + 10 )) || ( (ptLoc.x >= m_ptTouchLoc.x - 10) && ( ptLoc.y >= m_ptTouchLoc.y - 10 ) ) )
		{
			ToolFunc::playEffectFile( Click );
			singleEquipmentInfo(tag, 0);

			auto equipBG = dynamic_cast<ImageView* >(Helper::seekWidgetByName(task, "Image_BG"));
			equipBG->setVisible(true);
		}
	}	
	else if ( TOUCH_EVENT_BEGAN == type )
	{
		m_ptTouchLoc = task->getTouchStartPos();
		m_ptOriginleLoc = inner->getPosition();
	}
	else if ( TOUCH_EVENT_MOVED == type )
	{
		ptLoc = task->getTouchMovePos();
		auto pt = m_ptOriginleLoc.y + ptLoc.y - m_ptTouchLoc.y;
		pt = (pt > 0) ? 0 : pt;
		pt = (pt < temp) ? temp : pt;
		inner->setPositionY(pt);
	}
}

void EquipmentInfo::equipClick(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		ToolFunc::playEffectFile( Click );
		if (DataManager::getInstance()->isDonSucceed(DataManager::getInstance()->reGeneralVector[ 0 ].PKID, equipmentPKID, DataManager::getInstance()->equipType - 1 ))
		{
			if (false == NewComer::isGuideDone(1000))					/* 引导ID为0，且未完成 */
			{
				if (4 == NewComer::getCurGuideStep())
				{
					NewComer::setCurGuideStep();
				}
			}

			closeClick(NULL, TOUCH_EVENT_ENDED);
		}
	}
}

void EquipmentInfo::unloadClick(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		ToolFunc::playEffectFile( Click );
		if (DataManager::getInstance()->isUnloadEquip(DataManager::getInstance()->reGeneralVector[ 0 ].PKID, equipmentPKID, DataManager::getInstance()->equipType - 1))
		{
			closeClick(NULL, TOUCH_EVENT_ENDED);
		}
	}
}

void EquipmentInfo::changeClick(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		ToolFunc::playEffectFile( Click );
		if (DataManager::getInstance()->isChangeEquip( DataManager::getInstance()->reGeneralVector[ 0 ].PKID, 
			interGeneralEquipVector[ 0 ].equipPKID[ DataManager::getInstance()->equipType - 1 ], equipmentPKID, DataManager::getInstance()->equipType - 1 ))
		{
			closeClick(NULL, TOUCH_EVENT_ENDED);
		}
	}
}