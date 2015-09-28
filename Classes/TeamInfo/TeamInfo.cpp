#include "TeamInfo.h"
#include "Scene/MainScene.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

const int NameEditTag = 1;

Scene* TeamInfo::scene()
{
	auto scene = Scene::create();
	scene->addChild(TeamInfo::create());
	return scene;
}

bool TeamInfo::init()
{
	interPlayerInfoVector = DataManager::getInstance()->interPlayerInfoVector();

	auto layerTeamInfo = LayerColor::create(Color4B(0, 0, 0, 166));
	this->addChild(layerTeamInfo, -1);
	
	teamInfoUI = GUIReader::getInstance()->widgetFromJsonFile("TeamInfo.ExportJson");
	teamInfoUI->setAnchorPoint(Point::ANCHOR_MIDDLE);
	teamInfoUI->setPosition(Point(800 - teamInfoUI->getContentSize().width / 2, 480 - teamInfoUI->getContentSize().height / 2));
	teamInfoUI->setScale(0.0f);
	teamInfoUI->setTag( 99 );
	layerTeamInfo->addChild(teamInfoUI);
	auto scm = ScaleTo::create(0.4f, 1.0f, 1.0f, 1.0f);
	teamInfoUI->runAction(scm);

	spriteView = dynamic_cast<ImageView* >(Helper::seekWidgetByName(teamInfoUI, "BigBG"));

	auto teamLevel = dynamic_cast<Text* >(Helper::seekWidgetByName(teamInfoUI, "Label_Level"));									// 等级
	auto levelString = __String::createWithFormat("Lv.%d", DataManager::getInstance()->teamLevel);
	teamLevel->setText( levelString->getCString() );

	auto teamExp = dynamic_cast<LoadingBar* >(Helper::seekWidgetByName(teamInfoUI, "ProgressBar_Exp"));							// 经验条
	int precent = calcExp( DataManager::getInstance()->teamExp ) * 1.0f / ruleVector[ DataManager::getInstance()->teamLevel - 1 ].needExp * 100.0f;
	teamExp->setPercent( precent );

	auto teamFight = dynamic_cast<TextAtlas* >(Helper::seekWidgetByName(teamInfoUI, "AtlasLabel_ATK"));							// 战斗力
	auto fightString = __String::createWithFormat("%d", DataManager::getInstance()->finghtValue);
	teamFight->setStringValue( fightString->getCString() );

	auto teamName = dynamic_cast<Text* >(Helper::seekWidgetByName(teamInfoUI, "Label_Role_Name"));
	auto teamPhoto = dynamic_cast<ImageView* >(Helper::seekWidgetByName(teamInfoUI, "Role"));
	if ( DataManager::getInstance()->isGetPointSets() )
	{
		auto interPointset = DataManager::getInstance()->interPointSetsVector();
		auto localGeneral = DataManager::getInstance()->localGeneralProptyVector();
		if ( localGeneral.size() == 0 )
		{
			DataManager::getInstance()->generalDataParser();
			localGeneral = DataManager::getInstance()->localGeneralProptyVector();
		}
		int i_ID = 0;
		for (unsigned int i = 0; i < interPointset.size(); i++)
		{
			if ( interPointset[ i ].generalPos == 1 )
			{
				i_ID = interPointset[ i ].generalID;
			}
		}
		if ( i_ID != 0 )
		{
			auto nameString = __String::createWithFormat("%s", localGeneral[ i_ID - 10001 ].chinaName );
			auto photoString = __String::createWithFormat("%s.png", localGeneral[ i_ID - 10001 ].chinaSmallName );
			teamName->setText(nameString->getCString());
			teamPhoto->loadTexture(photoString->getCString(), UI_TEX_TYPE_PLIST);
			teamPhoto->setFlippedX(true);
			teamPhoto->setScale(78.0f / 95.0f);
		}		
	}

	auto onMenu = MenuItemImage::create("TempPic/SoundOn.png", "TempPic/SoundOn.png");  
	auto offMenu = MenuItemImage::create("TempPic/SoundOff.png", "TempPic/SoundOff.png");  
	MenuItemToggle* pMusic = MenuItemToggle::createWithCallback(CC_CALLBACK_1(TeamInfo::musicCall, this), onMenu, offMenu, nullptr);  
	if ( UserData::getInstance()->getMusicState() )
	{
		pMusic->setSelectedIndex( 0 );
	}
	else
	{
		pMusic->setSelectedIndex( 1 );
	}
	pMusic->setPosition(Point(-70, -50 ));

	auto onEffect = MenuItemImage::create("TempPic/EffectOn.png", "TempPic/EffectOn.png");  
	auto offEffect = MenuItemImage::create("TempPic/EffectOff.png", "TempPic/EffectOff.png"); 
	auto pEffect = MenuItemToggle::createWithCallback(CC_CALLBACK_1(TeamInfo::effectCall, this), onEffect, offEffect, nullptr);  
	if ( UserData::getInstance()->getEffectState() )
	{
		pEffect->setSelectedIndex( 0 );
	}
	else
	{
		pEffect->setSelectedIndex( 1 );
	}
	pEffect->setPosition(Point(90, -50 ));

	auto pMenu = Menu::create(pMusic, pEffect, NULL);  
	pMenu->setAnchorPoint( Point( 0, 0 ) );
	teamInfoUI->addChild(pMenu, 4);  

	return true;
}

void TeamInfo::closeButton(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		auto scm = ScaleTo::create(0.4f, 0.0f, 0.0f, 1.0f);
		auto callF = CallFunc::create(this, callfunc_selector(TeamInfo::closeCall));
		teamInfoUI->runAction( Sequence::createWithTwoActions( scm, callF ) );
	}
}

void TeamInfo::musicCall(Ref* pSender)
{
	if ( UserData::getInstance()->getMusicState() )
		SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
	else
		SimpleAudioEngine::getInstance()->playBackgroundMusic(BackGround, true);

	UserData::getInstance()->setupMusic = !UserData::getInstance()->setupMusic;
	UserData::getInstance()->saveMusicState();
}

void TeamInfo::effectCall(Ref* pSender)
{
	if ( UserData::getInstance()->getEffectState() )		
		ToolFunc::playEffectFile( Click );

	UserData::getInstance()->setupEffect = !UserData::getInstance()->setupEffect;
	UserData::getInstance()->saveEffectState();
}

void TeamInfo::closeCall()
{
	this->removeFromParentAndCleanup(true);
}

int TeamInfo::calcExp(int curExp)
{
	int i_Rexp = curExp;
	ruleVector = DataManager::getInstance()->localTeamUpgradeLocalVector();
	if ( ruleVector.size() == 0 )
	{
		DataManager::getInstance()->teamUpgradeDataParser();
		ruleVector = DataManager::getInstance()->localTeamUpgradeLocalVector();
	}

	for (unsigned int i = 0; i < ruleVector.size(); i++)
	{
		if ( i_Rexp >= ruleVector[ i ].needExp )
		{
			i_Rexp -= ruleVector[ i ].needExp;
		}
	}
	return i_Rexp;
}

void TeamInfo::onEnter()
{
	Layer::onEnter();
	auto listener = EventListenerTouchOneByOne::create();	
	listener->onTouchBegan = CC_CALLBACK_2(TeamInfo::onTouchBegan, this);
	listener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void TeamInfo::onExit()
{
	Layer::onExit();
}

bool TeamInfo::onTouchBegan(Touch *touch, Event *unused_event)
{
	bool bRef = false;
	Size size = spriteView->getContentSize();
	auto point = spriteView->getPosition();
	Rect rect = Rect(point.x - size.width / 2, point.y - size.height / 2, size.width, size.height );
	if (!rect.containsPoint(touch->getLocation()))
	{
		bRef = true;
		closeButton(NULL, TOUCH_EVENT_ENDED);
	}
	return bRef;
}
