#include "MainScene.h"
#include "Wareroom/Wareroom.h"
#include "Task/TaskLayer.h"
#include "FightPoints/FightPoints.h"
#include "Public/FontChina.h"
#include "DailyQuest/DailyQuest.h"
#include "Equipenhance/EquipEnhance.h"
#include "StoreB/StoreB.h"
#include "AppDelegate.h"
#include "NewComer/NewComer.h"

const int challengeFlag = 110;

MainScene::MainScene()
{
}

MainScene::~MainScene()
{
	
}

Scene* MainScene::scene()
{
	Scene* scene = Scene::create();
	MainScene* layer = MainScene::create();
	scene->addChild(layer);
	return scene;
}

bool MainScene::init()
{
	initData();

	UserData::getInstance()->setupMusic = UserDefault::getInstance()->getBoolForKey(MUSIC);
	UserData::getInstance()->setupEffect = UserDefault::getInstance()->getBoolForKey(EFFECT);

	auto mainSceneUI = GUIReader::getInstance()->widgetFromJsonFile(mainSceneUIRoot);
	mainSceneUI->setTag(99);
	this->addChild(mainSceneUI, -2);

	auto stateBarNode = StateBarNode::getInstance(StatePower);
	stateBarNode->setAnchorPoint(Point::ANCHOR_MIDDLE);
	stateBarNode->setPosition(Point(260, 420));
	this->addChild(stateBarNode, 3);

	mianScrollView = dynamic_cast<cocos2d::ui::ScrollView* >(Helper::seekWidgetByName(mainSceneUI, "ScrollView_MAINBG1"));

	auto paraNode = ParallaxNode::create();
	auto sprite1 = Sprite::createWithSpriteFrameName("Main/BG1.png");
	sprite1->setAnchorPoint(Point::ANCHOR_MIDDLE);
	auto sprite2 = Sprite::createWithSpriteFrameName("Main/BG2.png");
	sprite2->setAnchorPoint(Point::ANCHOR_MIDDLE);
	auto sprite3 = Sprite::createWithSpriteFrameName("Main/BG3.png");
	sprite3->setAnchorPoint(Point::ANCHOR_MIDDLE);
	paraNode->addChild(sprite1, -1, Point(0.4f, 0.0f), Point( 800, 240 ) );
	paraNode->addChild(sprite2, 1, Point(0.6f, 0.0f), Point( 800, 240 ) );
	paraNode->addChild(sprite3, 2, Point(1.0f, 0.0f), Point( 800, 240 ) );
	mianScrollView->addChild(paraNode);
	
	auto photoLayout = dynamic_cast<Layout* >(Helper::seekWidgetByName( mainSceneUI, "Panel_touxiang" ));
	
	auto heroImage = dynamic_cast<ImageView* >(Helper::seekWidgetByName(photoLayout, "Image_MroleBg"));							// 人物头像
	heroImage->addTouchEventListener(this, toucheventselector(MainScene::heroButton));
	heroImage->setTouchEnabled(true);
	
	auto trainButton = dynamic_cast<Button* >(Helper::seekWidgetByName(mianScrollView, "Button_train"));								// 练兵场
	trainButton->addTouchEventListener(this, toucheventselector(MainScene::trainButton));
	
	auto battlaButton0 = dynamic_cast<Button* >(Helper::seekWidgetByName(mianScrollView, "Button_ectype"));							// 关卡副本
	battlaButton0->addTouchEventListener(this, toucheventselector(MainScene::battleCtrl));

	auto battlaEffect = EffectAction::getInstance();
	battlaEffect->fbEffect();
	battlaEffect->setPosition(Point( battlaButton0->getPosition() - Point( 0, 20 ) ));
	mianScrollView->addChild(battlaEffect, 5);
	
	auto wareroomButton = dynamic_cast<Button* >(Helper::seekWidgetByName(mianScrollView, "Button_wareroom"));						// 仓库
	wareroomButton->addTouchEventListener(this, toucheventselector(MainScene::wareroom));
	
	auto storeButton = dynamic_cast<Button* >(Helper::seekWidgetByName(mianScrollView, "Button_Drawoff"));							// 酒馆
	storeButton->addTouchEventListener(this, toucheventselector(MainScene::store));

	auto storebButton = dynamic_cast<Button* >(Helper::seekWidgetByName(mianScrollView, "Button_store"));							// 购买物品的商店
	storebButton->addTouchEventListener(this, toucheventselector(MainScene::storebClick));
	
	auto smithyBtn = dynamic_cast<Button* >(Helper::seekWidgetByName(mianScrollView, "Button_equipcom"));							// 铁匠铺
	smithyBtn->addTouchEventListener(this, toucheventselector(MainScene::smithy));	

	auto tieEffect = EffectAction::getInstance();
	tieEffect->tieEffect();
	tieEffect->setScale(0.4f);
	tieEffect->setPosition(Point( smithyBtn->getPosition() - Point( 0, 30 ) ));
	mianScrollView->addChild(tieEffect, 10);
	
	auto yiJiDangQianButton = dynamic_cast<Button* >(Helper::seekWidgetByName(mianScrollView, "Button_yi qi dang qian"));				// 一骑当千
	yiJiDangQianButton->addTouchEventListener(this, toucheventselector(MainScene::YiJiDangQian));
	
	auto jiXiaXueGongButton = dynamic_cast<Button* >(Helper::seekWidgetByName(mianScrollView, "Button_ji xia xue gong"));				// 稷下学宫
	jiXiaXueGongButton->addTouchEventListener(this, toucheventselector(MainScene::JiXiaXueGong));

	buttomPanel = dynamic_cast<Layout* >(Helper::seekWidgetByName(mainSceneUI, "Panel_Down"));								// 下方的功能按钮层
	
	auto rewardButton = dynamic_cast<Button* >(Helper::seekWidgetByName(buttomPanel, "Button_Achievement"));						// 成就
	rewardButton->addTouchEventListener(this, toucheventselector(MainScene::rewardClick));

	auto otherButton = dynamic_cast<Button* >(Helper::seekWidgetByName(buttomPanel, "Button_OtherGame"));							// 其他游戏
	//otherButton->addTouchEventListener(this, toucheventselector(MainScene::otherClick));
	otherButton->setEnabled(false);

	auto buffButton = dynamic_cast<Button* >(Helper::seekWidgetByName(buttomPanel, "Button_Buff"));
	buffButton->setEnabled(false);
	
	auto chanllengeClick = dynamic_cast<Button* >(Helper::seekWidgetByName(buttomPanel, "Button_tiaozhan"));						// 挑战
	chanllengeClick->setTag(challengeFlag);
	chanllengeClick->addTouchEventListener(this, toucheventselector(MainScene::challengeClick));

	this->schedule(schedule_selector( MainScene::update ), 5.0f);

	createTeach();

	return true;
}

void MainScene::initData()
{
	if (DataManager::getInstance()->isGetTeamInfo())
	{
		interTeamInfoVector = DataManager::getInstance()->interTeamInfoVector();
	}
	
	interPlayerInfoVector = DataManager::getInstance()->interPlayerInfoVector();

	FontChina::getInstance()->initStringXml();
}

void MainScene::playInfoShow()
{
	int resultInt = 0;
	auto localGeneralVector = DataManager::getInstance()->localGeneralProptyVector();
	if (localGeneralVector.size() == 0)
	{
		DataManager::getInstance()->generalDataParser();
		localGeneralVector = DataManager::getInstance()->localGeneralProptyVector();
	}
	auto localEquipVector = DataManager::getInstance()->localEquipProptyVector();
	if (localEquipVector.size() == 0)
	{
		DataManager::getInstance()->equipDataParser();
		localEquipVector = DataManager::getInstance()->localEquipProptyVector();
	}
	auto localEquipRefineRuleVector = DataManager::getInstance()->localEquipRefineVector();
	if (localEquipRefineRuleVector.size() == 0)
	{
		DataManager::getInstance()->equipRefineRule();
		localEquipRefineRuleVector = DataManager::getInstance()->localEquipRefineVector();
	}
	vector<PointSetsRecvStruct > pointVec;
	if (DataManager::getInstance()->isGetPointSets())
	{
		pointVec = DataManager::getInstance()->interPointSetsVector();
		for (unsigned int i = 0; i < pointVec.size(); i ++)
		{
			if (pointVec[ i ].generalID != 0)													// 有武将上阵
			{
				if ( DataManager::getInstance()->isGetGeneralProperty(pointVec[ i ].generalPKID) )		// 获取上阵武将的详情	
				{
					auto generalDetialVec = DataManager::getInstance()->interGeneralVector();
					int curRoleID = pointVec[ i ].generalID + generalDetialVec[ 0 ].starLevel + ( generalDetialVec[ 0 ].evoLevel - 1) - 10001;
					int hpValue = localGeneralVector[ curRoleID ].initHP + localGeneralVector[ curRoleID ].hpGrowing * (generalDetialVec[ 0 ].level - 1);			// 人物相应生命值
					int atkValue = localGeneralVector[ curRoleID ].initAtk + localGeneralVector[ curRoleID ].atkGrowing * (generalDetialVec[ 0 ].level - 1);			// 攻击力
					int mdValue = localGeneralVector[ curRoleID ].initMD + localGeneralVector[ curRoleID ].mdGrowing * (generalDetialVec[ 0 ].level - 1);			// 魔法防御
					int pdValue = localGeneralVector[ curRoleID ].initPD + localGeneralVector[ curRoleID ].pdGrowing * (generalDetialVec[ 0 ].level - 1);			// 物理防御
					
					float basicValues[] = { 0.1f, 0.2f, 0.2f, 0.3f };
					float incFValues[] = { 0.008f, 0.01f, 0.01f, 0.01f };
					for (int k = 0; k < 4; k++)
					{
						int i_IncValues = 0;
						float incValues = 0.0f;
						if ( generalDetialVec[ 0 ].equipID[ k ] != 0 )
						{		
							for (int z = 0; z < 4; z++)
							{
								if ( ( localEquipVector[ generalDetialVec[ 0 ].equipID[ k ] - 94001 ].eColor == z + 1 ) && ( generalDetialVec[ 0 ].equipLevel[ k ] != 0 ) )
								{
									incValues += basicValues[ z ] + ( generalDetialVec[ 0 ].equipLevel[ k ] - 1 ) * incFValues[ z ];
								}	
							}								
							if ( k == 0)
							{
								i_IncValues = localEquipVector[ generalDetialVec[ 0 ].equipID[ 0 ] - 94001 ].eHP;
								hpValue += i_IncValues * ( 1 + incValues) ;
							}
							else if ( k == 1 )
							{
								i_IncValues = localEquipVector[ generalDetialVec[ 0 ].equipID[ 1 ] - 94001 ].ePD;
								pdValue += i_IncValues * ( 1 + incValues ) ;
							}
							else if ( k == 2 )
							{
								i_IncValues = localEquipVector[ generalDetialVec[ 0 ].equipID[ 2 ] - 94001 ].eMD;
								mdValue += i_IncValues * ( 1 + incValues ) ;
							}
							else if ( k == 3 )
							{
								i_IncValues = localEquipVector[ generalDetialVec[ 0 ].equipID[ 3 ] - 94001 ].eAtk;
								atkValue += i_IncValues * ( 1 + incValues ) ;
							}
						}
					}

					auto localSkillAddPropty = DataManager::getInstance()->localSkillAddProptyVec();
					if (localSkillAddPropty.size() == 0)
					{
						DataManager::getInstance()->skillUpgradeProptyAdd();
						localSkillAddPropty = DataManager::getInstance()->localSkillAddProptyVec();
					}
					if (generalDetialVec[ 0 ].skillLevel[ 0 ] != 0)
					{
						if (localGeneralVector[ pointVec[ i ].generalID - 10001 ].maxStar == 5)
						{
							pdValue += localSkillAddPropty[ 0 ].ePD + generalDetialVec[ 0 ].skillLevel[ 0 ] * localSkillAddPropty[ 0 ].ePDLen;
						}
						else if (localGeneralVector[ pointVec[ i ].generalID - 10001 ].maxStar == 4)
						{
							pdValue += localSkillAddPropty[ 0 ].dPD + generalDetialVec[ 0 ].skillLevel[ 0 ] * localSkillAddPropty[ 0 ].dPDLen;
						}
						else if (localGeneralVector[ pointVec[ i ].generalID - 10001 ].maxStar == 3)
						{
							pdValue += localSkillAddPropty[ 0 ].cPD + generalDetialVec[ 0 ].skillLevel[ 0 ] * localSkillAddPropty[ 0 ].cPDLen;
						}
					}
					if (generalDetialVec[ 0 ].skillLevel[ 1 ] != 0)
					{
						if (localGeneralVector[ pointVec[ i ].generalID - 10001 ].maxStar == 5)
						{
							mdValue += localSkillAddPropty[ 0 ].eMD + generalDetialVec[ 0 ].skillLevel[ 1 ] * localSkillAddPropty[ 0 ].eMDLen;
						}
						else if (localGeneralVector[ pointVec[ i ].generalID - 10001 ].maxStar == 4)
						{
							mdValue += localSkillAddPropty[ 0 ].dMD + generalDetialVec[ 0 ].skillLevel[ 1 ] * localSkillAddPropty[ 0 ].dMDLen;
						}
						else if (localGeneralVector[ pointVec[ i ].generalID - 10001 ].maxStar == 3)
						{
							mdValue += localSkillAddPropty[ 0 ].cMD + generalDetialVec[ 0 ].skillLevel[ 1 ] * localSkillAddPropty[ 0 ].cMDLen;
						}
					}
					if (generalDetialVec[ 0 ].skillLevel[ 2 ] != 0)
					{
						if (localGeneralVector[ pointVec[ i ].generalID - 10001 ].maxStar == 5)
						{
							hpValue += localSkillAddPropty[ 0 ].eHP + generalDetialVec[ 0 ].skillLevel[ 2 ] * localSkillAddPropty[ 0 ].eHPLen;
						}
						else if (localGeneralVector[ pointVec[ i ].generalID - 10001 ].maxStar == 4)
						{
							hpValue += localSkillAddPropty[ 0 ].dHP + generalDetialVec[ 0 ].skillLevel[ 2 ] * localSkillAddPropty[ 0 ].dHPLen;
						}
					}
					if (generalDetialVec[ 0 ].skillLevel[ 3 ] != 0)
					{
						if (localGeneralVector[ pointVec[ i ].generalID - 10001 ].maxStar == 5)
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
	}	
	auto layerWight = (Layout* )this->getChildByTag(99);
	auto photoLayout = (Layout* )layerWight->getChildByName( "Panel_touxiang" );
	auto fighting = dynamic_cast<TextAtlas* >(Helper::seekWidgetByName(photoLayout, "AtlasLabel_zhan dou li"));				// 战斗力
	DataManager::getInstance()->finghtValue = resultInt;
	auto fightString = __String::createWithFormat("%d", resultInt);
	fighting->setStringValue(fightString->getCString());

	auto levelLabel = dynamic_cast<Text* >( Helper::seekWidgetByName(photoLayout, "Label_deng ji") );						// 战队等级
	auto levelString = __String::createWithFormat( "Lv.%d", interTeamInfoVector[ 0 ].teamLevel );
	levelLabel->setText(levelString->getCString());

	DataManager::getInstance()->teamExp = interTeamInfoVector[ 0 ].teamExp;
	DataManager::getInstance()->teamLevel = interTeamInfoVector[ 0 ].teamLevel;

	auto rolePhotoImage = dynamic_cast<ImageView* >(Helper::seekWidgetByName(photoLayout, "Image_tx"));					// 战队头像
	if ( pointVec.size() != 0 )
	{
		for (unsigned int i = 0; i < pointVec.size(); i ++)
		{
			if ( pointVec[ i ].generalPos == 1 )
			{
				// 加载队长头像
				auto roleNameString = __String::createWithFormat("%s.png", localGeneralVector[ pointVec[ i ].generalID - 10001 ].chinaSmallName);
				rolePhotoImage->loadTexture(roleNameString->getCString(), TextureResType::UI_TEX_TYPE_PLIST);
				rolePhotoImage->setFlippedX(true);
				rolePhotoImage->setScale(78.0f / 95.0f);

				auto namelLabel = dynamic_cast<Text* >( Helper::seekWidgetByName(photoLayout, "Label_76") );					// 战队名称
				auto nameString = __String::createWithFormat( "%s", localGeneralVector[ pointVec[ i ].generalID - 10001 ].chinaName );
				namelLabel->setText(nameString->getCString());

			}
		}
	}
}

void MainScene::trainButton(Ref* sender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		ToolFunc::playEffectFile( Click );

		if (false == NewComer::isGuideDone(1000))					/* 引导ID为0，且未完成 */
		{
			if (1 == NewComer::getCurGuideStep())					/* 第二步骤 */
			{
				NewComer::setCurGuideStep();
			}
		}
		else if (false == NewComer::isGuideDone(1002))
		{
			if (2 == NewComer::getCurGuideStep())
			{
				NewComer::setCurGuideStep();
			}
		}
		else if (false == NewComer::isGuideDone(1004))
		{
			if (3 == NewComer::getCurGuideStep())
			{
				NewComer::setCurGuideStep();
			}
		}
		else if (false == NewComer::isGuideDone(1005) ||
			(false == NewComer::isGuideDone(1009)) ||
			(false == NewComer::isGuideDone(1010)))
		{
			if (0 == NewComer::getCurGuideStep())
			{
				NewComer::setCurGuideStep();
			}
		}
		else
		{
		}

		Director::getInstance()->replaceScene(Maidan::scene());
		DataManager::getInstance()->i_scrollViewPos = EtnTrian;
	}
}

void MainScene::battleCtrl(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		ToolFunc::playEffectFile( Click );

		DataManager::getInstance()->i_scrollViewPos = EtnFB;

 		auto warriors = DataManager::getInstance()->interPointSetsVector();
 		if (0 == warriors.size())
 		{
 			if (false == DataManager::getInstance()->isGetPointSets())
			{
				return;
			}
 			warriors = DataManager::getInstance()->interPointSetsVector();
 		}
 
 		if (0 == warriors[0].generalID)				/* 无主将 */
 		{
 			auto notice = PromptBox::getInstance(FontChina::getInstance()->getComString("NoMainRole")->getCString());
 			notice->setFade();
 			this->addChild(notice);
 			return;
 		}

		auto btnBattle = (Button*)pSender;
		Director::getInstance()->replaceScene(FightPoints::scene());
	}
}

void MainScene::wareroom(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		ToolFunc::playEffectFile( Click );

		DataManager::getInstance()->i_scrollViewPos = EtnWareroom;

		if (false == NewComer::isGuideDone(1007))					/* 引导ID为7，且未完成 */
		{
			if (1 == NewComer::getCurGuideStep())
			{
				NewComer::setCurGuideStep();
			}
		}
		
		Director::getInstance()->replaceScene(Wareroom::scene());
	}
}

void MainScene::YiJiDangQian(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		ToolFunc::playEffectFile( Click );

		auto notice = PromptBox::getInstance(FontChina::getInstance()->getComString("YJDQ")->getCString());
		notice->setFade();
		this->addChild(notice);

		//DataManager::getInstance()->i_scrollViewPos = EtnYJ;

		//Director::getInstance()->pushScene(YiJiDangQian::create());
	}
}

void MainScene::JiXiaXueGong(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		ToolFunc::playEffectFile( Click );

		DataManager::getInstance()->i_scrollViewPos = EtnJx;

		DataManager::getInstance()->isGetTeamInfo();					/* 当前战队等级 */
		auto teamInfo = DataManager::getInstance()->interTeamInfoVector();

		if (teamInfo[0].teamLevel < 8)									/* 8级开启 */
		{
			auto notice = PromptBox::getInstance(FontChina::getInstance()->getComString("JxxgLvLimit")->getCString());
			notice->setFade();
			this->addChild(notice);
		}
		else
		{
			Director::getInstance()->pushScene(JiXiaXueGong::create());
		}		
	}
}

void MainScene::heroButton(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		ToolFunc::playEffectFile( Click );

		this->addChild(TeamInfo::scene(), 10);
	}
}

void MainScene::store(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		ToolFunc::playEffectFile( Click );

		DataManager::getInstance()->i_scrollViewPos = EtnJiuGuan;

		if (false == NewComer::isGuideDone(1002))					/* 引导ID为2，且未完成 */
		{
			if (0 == NewComer::getCurGuideStep())
			{
				NewComer::setCurGuideStep();
			}
		}

		Director::getInstance()->replaceScene(Store::create());
	}
}

void MainScene::smithy(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		ToolFunc::playEffectFile( Click );

		DataManager::getInstance()->i_scrollViewPos = EtnTie;

		if (false == NewComer::isGuideDone(1003) || 				/* 引导ID为3，且未完成 */
			(false == NewComer::isGuideDone(1008)))					/* 引导ID为8，且未完成 */
		{
			if (0 == NewComer::getCurGuideStep())
			{
				NewComer::setCurGuideStep();
			}
		}

		Director::getInstance()->replaceScene(EquipEnhance::Create());
	}
}

void MainScene::rewardClick(Ref* pSender, TouchEventType type)
{
	if ( type == TOUCH_EVENT_ENDED )
	{
		ToolFunc::playEffectFile( Click );
	}
}

void MainScene::otherClick(Ref* pSender, TouchEventType type)
{
	if ( type == TOUCH_EVENT_ENDED )
	{
		ToolFunc::playEffectFile( Click );
	}
}

void MainScene::storebClick(Ref* pSender, TouchEventType type)
{
	if ( type == TOUCH_EVENT_ENDED )
	{
		ToolFunc::playEffectFile( Click );

		DataManager::getInstance()->i_scrollViewPos = EtnStore;

		if (false == NewComer::isGuideDone(1004))
		{
			if (0 == NewComer::getCurGuideStep())
			{
				NewComer::setCurGuideStep();
			}
		}

		Director::getInstance()->replaceScene(StoreB::create());
	}
}

void MainScene::challengeClick(Ref* pSender, TouchEventType type)
{
	if ( type == TOUCH_EVENT_ENDED )
	{
		ToolFunc::playEffectFile( Click );

		auto warriors = DataManager::getInstance()->interPointSetsVector();
		if (0 == warriors.size())
		{
			if (false == DataManager::getInstance()->isGetPointSets())
			{
				return;
			}
			warriors = DataManager::getInstance()->interPointSetsVector();
		}

		if (0 == warriors[0].generalID)				/* 无主将 */
		{
			auto notice = PromptBox::getInstance(FontChina::getInstance()->getComString("NoMainRole")->getCString());
			notice->setFade();
			this->addChild(notice);
			return;
		}

		auto btnBattle = (Button*)pSender;
		Director::getInstance()->replaceScene(FightPoints::scene());
	}
}

void MainScene::createTeach()
{
	NewComer *comer = NULL;
	if (false == NewComer::isGuideDone(1000))						/* 引导ID为0，且未完成 */
	{
		comer = NewComer::create(this, 1000, 0, CC_CALLBACK_0(MainScene::teachCB, this));
		if (NULL == comer)
		{
			comer = NewComer::create(mianScrollView, 1000, 1);
			if (NULL == comer)
			{
				comer = NewComer::create(buttomPanel, 1000, 5);
			}
		}
	}
	else if (false == NewComer::isGuideDone(1001))					/* 引导ID为1，且未完成 */
	{
		comer = NewComer::create(this, 1001, 0, CC_CALLBACK_0(MainScene::teachCB, this));
		if (NULL == comer)
		{
			comer = NewComer::create(buttomPanel, 1001, 1);
		}
	}
	else if (false == NewComer::isGuideDone(1002))					/* 引导ID为2，且未完成 */
	{
		comer = NewComer::create(mianScrollView, 1002, 0);
		if (NULL == comer)
		{
			comer = NewComer::create(mianScrollView, 1002, 2);
			if (NULL == comer)
			{
				comer = NewComer::create(buttomPanel, 1002, 5);
			}
		}
	}
	else if (false == NewComer::isGuideDone(1003))					/* 引导ID为3，且未完成 */
	{
		comer = NewComer::create(mianScrollView, 1003, 0);
		if (NULL == comer)
		{
			comer = NewComer::create(buttomPanel, 1003, 3);
		}
		else
		{
			mianScrollView->scrollToPercentHorizontal(90.0f, 0.1f, false);
		}
	}
	else if (false == NewComer::isGuideDone(1004))					/* 引导ID为4，且未完成 */
	{
		comer = NewComer::create(mianScrollView, 1004, 0);
		if (NULL == comer)
		{
			comer = NewComer::create(mianScrollView, 1004, 3);
			if (NULL == comer)
			{
				comer = NewComer::create(buttomPanel, 1004, 7);
			}
		}
	}
	else if (false == NewComer::isGuideDone(1005))					/* 引导ID为5，且未完成 */
	{
		comer = NewComer::create(mianScrollView, 1005, 0);
	}
	else if (false == NewComer::isGuideDone(1006))					/* 引导ID为6，且未完成 */
	{
		comer = NewComer::create(this, 1006, 0, CC_CALLBACK_0(MainScene::teachCB, this));
	}
	else if (false == NewComer::isGuideDone(1007))					/* 引导ID为7，且未完成 */
	{
		comer = NewComer::create(this, 1007, 0, CC_CALLBACK_0(MainScene::teachCB, this));
		if (NULL == comer)
		{
			NewComer::create(mianScrollView, 1007, 1);
		}
		else
		{
			mianScrollView->scrollToPercentHorizontal(80.0f, 0.1f, false);
		}
	}
	else if (false == NewComer::isGuideDone(1008))					/* 引导ID为8，且未完成 */
	{
		comer = NewComer::create(mianScrollView, 1008, 0);
	}
	else if (false == NewComer::isGuideDone(1009))					/* 引导ID为9，且未完成 */
	{
		comer = NewComer::create(mianScrollView, 1009, 0);
	}
	else if (false == NewComer::isGuideDone(1010))					/* 引导ID为10，且未完成 */
	{
		comer = NewComer::create(mianScrollView, 1010, 0);
	}
	else
	{
	}
}

void MainScene::teachCB()
{
	UserData::getInstance()->setGuideStep();

	if (false == NewComer::isGuideDone(1000))
	{
		DrawoffGoodsStruct drawoff = {GoodsEquip, 90047};			/* 获得学徒短剑 */
		std::vector<DrawoffGoodsStruct > tempVector;
		tempVector.push_back(drawoff);
		DataManager::getInstance()->isDrawoffCard(0, 0, 0, 0, tempVector);

		NewComer::create(mianScrollView, 1000, 1);
	}
	else if (false == NewComer::isGuideDone(1001))
	{
		DrawoffGoodsStruct drawoff = {GoodsEquip, 90052};			/* 获得天机镜 */
		std::vector<DrawoffGoodsStruct > tempVector;
		tempVector.push_back(drawoff);
		DataManager::getInstance()->isDrawoffCard(0, 0, 0, 0, tempVector);

		NewComer::create(buttomPanel, 1001, 1);
	}
	else if (false == NewComer::isGuideDone(1006))
	{
		DrawoffGoodsStruct drawoff = {GoodsEquip, 90051};			/* 获得玉净瓶 */
		std::vector<DrawoffGoodsStruct > tempVector;
		tempVector.push_back(drawoff);
		DataManager::getInstance()->isDrawoffCard(0, 0, 0, 0, tempVector);

		auto cpID = NewComer::getCurGuideID();
		cpID = cpID | 0x010000;										/* 完成ID为0的引导 */
		NewComer::setCurGuideID(cpID);
		NewComer::setCurGuideStep(0);								/* 步骤ID重置 */
	}
	else if (false == NewComer::isGuideDone(1007))
	{
		std::vector<DrawoffGoodsStruct > tempVector;				/* 获得暴鸳碎片 * 30 */
		for (int index = 0; index < 30; index++)
		{
			DrawoffGoodsStruct drawoff = {GoodsChip, 90028};
			tempVector.push_back(drawoff);
		}
		DataManager::getInstance()->isDrawoffCard(0, 0, 0, 0, tempVector);

		NewComer::create(mianScrollView, 1007, 1);
	}
	else
	{
	}
}

void MainScene::update(float dt)
{
	auto button = (Button*)buttomPanel->getChildByTag(challengeFlag);
	auto rRight = RotateTo::create(0.1f, 30.0f);
	auto rBRight = RotateTo::create(0.1f, -20.0f);
 	auto rNRight = RotateTo::create(0.1f, 30.0f);
	auto rNRight1 = RotateTo::create(0.1f, 0.0f);
	button->runAction(Sequence::create(rRight, rBRight, rNRight, rNRight1, NULL));
}

void MainScene::onEnter()
{
	Layer::onEnter();
	playInfoShow();
	
	switch (DataManager::getInstance()->i_scrollViewPos)
	{
	case EtnJx:
		mianScrollView->scrollToPercentHorizontal(0.0f, 0.1f, false);
		break;
	case EtnTrian:
		mianScrollView->scrollToPercentHorizontal(0.0f, 0.1f, false);
		break;
	case EtnJiuGuan:
		mianScrollView->scrollToPercentHorizontal(20.0f, 0.1f, false);
		break;
	case EtnStore:
		mianScrollView->scrollToPercentHorizontal(40.0f, 0.1f, false);
		break;
	case EtnWareroom:
		mianScrollView->scrollToPercentHorizontal(80.0f, 0.1f, false);
		break;
	case EtnTie:
		mianScrollView->scrollToPercentHorizontal(90.0f, 0.1f, false);
		break;
	case EtnYJ:
		mianScrollView->scrollToPercentHorizontal(100.0f, 0.1f, false);
		break;
	case EtnFB:
		mianScrollView->scrollToPercentHorizontal(100.0f, 0.1f, false);
		break;
	}

	auto app = (AppDelegate *)(Application::getInstance()); 
	app->showBanner();
}

void MainScene::onExit()
{
	auto app = (AppDelegate *)(Application::getInstance()); 
	app->hideBanner();
	Layer::onExit();
}