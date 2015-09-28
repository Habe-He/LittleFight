#include "OnestartGameStory.h"
#include "DataManager/DataManager.h"
#include "Sqlite3/DBUtil.h"
#include "Counterpart/Counterpart.h"
#include "Counterpart/RolePrestrain.h"
#include "Loading/Loading.h"
#include "AppDelegate.h"

Scene* startonce::scene()
{
	auto scene = Scene::create();
	auto layer = startonce::create();
	scene->addChild(layer);
	return scene;
}

bool startonce::init()
{

	auto app = (AppDelegate *)(Application::getInstance()); 
	app->hideBanner();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	auto aboutGame = DataManager::getInstance()->localOnceGameVector();


	if (UserDefault::getInstance()->getBoolForKey("firstGame") == false)
	{
		UserData::getInstance()->setupEffect = true;
		UserData::getInstance()->saveEffectState();

		UserData::getInstance()->setupMusic = true;
		UserData::getInstance()->saveMusicState();

		UserDefault::getInstance()->setBoolForKey("firstGame",true);
		for (int i = 0; i < 5; i++)
		{
			auto label  = Label::create();
			label->setPosition(Point(visibleSize.width / 2, 200 - i * 50 ));
			label->setString(String::createWithFormat("%s", aboutGame[ i ].OpenStory)->getCString());
			label->setSystemFontSize( 20.0f );
			addChild(label);

			label->runAction(Sequence::create(MoveBy::create(6.0f, Point(0, 500)),/*CallFunc::create(CC_CALLBACK_0(startonce::repScene,this)),*/NULL));

		}
		this->runAction(Sequence::createWithTwoActions( DelayTime::create( 5.0f ), CallFunc::create( CC_CALLBACK_0( startonce::repScene, this ) ) ));
		//repScene();
	}
	
    return true;
}

void startonce::repScene()
{
	vector< PointSetsRecvStruct > interPointSetsVector;
	if ( DataManager::getInstance()->isGetPointSets() )  
	{
		interPointSetsVector = DataManager::getInstance()->interPointSetsVector();
	}
	if ( interPointSetsVector.size() == 0 )
	{
		// 送一个以上阵的武将，跳转到副本

		DBUtil::getInstance()->CreateTable_Player();
		DBUtil::getInstance()->CreateTable_Item();
		DBUtil::getInstance()->CreateTable_GeneralGrowth();
		DBUtil::getInstance()->CreateTable_GeneralMain();
		DBUtil::getInstance()->CreateTable_GeneralSkill();
		DBUtil::getInstance()->CreateTable_GeneralEquip();
		DBUtil::getInstance()->CreateTable_GeneralTalent();
		DBUtil::getInstance()->CreateTable_Point();
		DBUtil::getInstance()->CreateTable_Jxxg();

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
}
