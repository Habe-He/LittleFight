#include "Login.h"
#include "Loading/Loading.h"
#include "SimpleAudioEngine.h"
#include "DataManager/DataManager.h"
#include "Scene/MainScene.h"
#include "Sqlite3/DBUtil.h"
#include "Counterpart/Counterpart.h"
#include "Counterpart/RolePrestrain.h"
#include "AppDelegate.h"

Login::Login()
{

}

Login::~Login()
{

}

Scene* Login::scene()
{
	Scene* scene = Scene::create();
	Login* layer = Login::create();
	scene->addChild(layer);
	return scene;
}

bool Login::init()
{
	auto app = (AppDelegate *)(Application::getInstance()); 
	app->hideBanner();

	auto loginUI = GUIReader::getInstance()->widgetFromJsonFile("Login.ExportJson");
	this->addChild(loginUI);

	auto loginClick = dynamic_cast<Button* >(Helper::seekWidgetByName(loginUI, "Button_ks"));
	loginClick->addTouchEventListener(this, toucheventselector(Login::loginButtton));

	auto otherClick = dynamic_cast<Button* >(Helper::seekWidgetByName(loginUI, "Button_qtyx"));
	//otherClick->addTouchEventListener(this, toucheventselector(Login::otherButtton));
	otherClick->setEnabled(false);

	auto itemClick = dynamic_cast<Button* >(Helper::seekWidgetByName(loginUI, "Button_xx"));
	//itemClick->addTouchEventListener(this, toucheventselector(Login::itemButtton));
	itemClick->setEnabled(false);

	auto shareClick = dynamic_cast<Button* >(Helper::seekWidgetByName(loginUI, "Button_fx"));
	//shareClick->addTouchEventListener(this, toucheventselector(Login::shareButtton));
	shareClick->setEnabled(false);

	if (UserData::getInstance()->setupMusic)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BackGround);
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(BackGround, true);
	}
	if ( UserData::getInstance()->setupEffect )
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(Click);
	}

	return true;
}

void Login::loginButtton(Ref* sender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{ 
		if (DataManager::getInstance()->isLoginSuccess())
		{
			auto scene = Loading::scene();
			Loading* pGameLoading = static_cast<Loading*>( scene->getChildByTag(2) );
			for (int i = 0; i < resCount; i ++)
			{
				auto uiString = __String::createWithFormat("UI/All/LittleFight_UI%d", i);
				pGameLoading->addTextureCacheFromFileByName(uiString->getCString());			
			}
			pGameLoading->addTextureCacheFromFileByName("res/Sprite");					
			Director::getInstance()->replaceScene(scene);

			vector< PointSetsRecvStruct > interPointSetsVector;
			if ( DataManager::getInstance()->isGetPointSets() )  
			{
				interPointSetsVector = DataManager::getInstance()->interPointSetsVector();
			}
			if ( interPointSetsVector.size() == 0 )
			{
				// 送一个以上阵的武将，跳转到副本
				auto generalID = 10001;
				stringstream streamInsert;
				streamInsert << "Insert Into " << DBUtil::getInstance()->getTableName(Table_gMain) << " (ID, star, level, lExp, step, sExp, appoint) Values (" << generalID << ", 1, 1, 0, 0, 0, 1)";
				auto stringInsert = streamInsert.str();

				stringstream streamInsert1;  
				streamInsert1 << "Insert Into " << DBUtil::getInstance()->getTableName(Table_gGrowth) << " (ID, atk, hp, pd, md) Values (" << generalID << ", 0, 0, 0, 0)";
				auto stringInsert1 = streamInsert1.str();

				stringstream streamInsert2;  
				streamInsert2 << "Insert Into " << DBUtil::getInstance()->getTableName(Table_gSkill) << " (ID, lv1, lv2, lv3, lv4) Values (" << generalID << ", 1, 0, 0, 0 )";
				auto stringInsert2 = streamInsert2.str();

				stringstream streamInsert3;  
				streamInsert3 << "Insert Into " << DBUtil::getInstance()->getTableName(Table_gEquip) 
					<< " (ID, equip1, equip2, equip3, equip4, equip5, equip6) Values (" << generalID << ", 0, 0, 0, 0, 0, 0)";
				auto stringInsert3 = streamInsert3.str();

				stringstream streamInsert4;  
				streamInsert4 << "Insert Into " << DBUtil::getInstance()->getTableName(Table_gTalent) << " (ID, talent1, talent2, talent3, talent4) Values (" << generalID << ", 0, 0, 0, 0)";
				auto stringInsert4 = streamInsert4.str();
				if (  DBUtil::getInstance()->insertData(stringInsert) && DBUtil::getInstance()->insertData(stringInsert1) &&
					DBUtil::getInstance()->insertData(stringInsert2) && DBUtil::getInstance()->insertData(stringInsert3) && DBUtil::getInstance()->insertData(stringInsert4) )
				{
					UserData::getInstance()->setRoleCreateModel(RoleCreMode_Fighting);
					RolePrestrain begin;
					begin.loading( 1 );
				}
			}
			else
			{
				pGameLoading->setChangeScene( MainScene::scene );
			}
 		}
 	}	
}

void Login::itemButtton(Ref* sender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{

	}
}

void Login::otherButtton(Ref* sender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{

	}
}

void Login::shareButtton(Ref* sender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		auto app = (AppDelegate *)(Application::getInstance()); 
		app->shareTimeLine();
	}
}
