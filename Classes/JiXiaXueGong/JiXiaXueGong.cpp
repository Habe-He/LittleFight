#include "JiXiaXueGong.h"
#include "Scene/MainScene.h"
#include "Counterpart/RolePrestrain.h"

enum JiXiaBtnEnum
{
	JiXiaBtnItem1 = 0,
	JiXiaBtnItem2,
	JiXiaBtnItem3,
	JiXiaBtnItem4,
	JiXiaBtnClose,
	JiXiaBtnMax
};

bool JiXiaXueGong::init()
{
	auto jiXiaXueGongUI = GUIReader::getInstance()->widgetFromJsonFile("UI/All/JiXiaXueGong.ExportJson");
	this->addChild(jiXiaXueGongUI);

	auto btnJX1 = dynamic_cast<Button *>(Helper::seekWidgetByName(jiXiaXueGongUI, "Button_BGJ1"));
	btnJX1->addTouchEventListener(this, toucheventselector(JiXiaXueGong::jixiaButtonClick));
	btnJX1->setTag(JiXiaBtnItem1);

	auto btnJX2 = dynamic_cast<Button *>(Helper::seekWidgetByName(jiXiaXueGongUI, "Button_BGJ2"));
	btnJX2->addTouchEventListener(this, toucheventselector(JiXiaXueGong::jixiaButtonClick));
	btnJX2->setTag(JiXiaBtnItem2);

	auto btnJX3 = dynamic_cast<Button *>(Helper::seekWidgetByName(jiXiaXueGongUI, "Button_BGJ3"));
	btnJX3->addTouchEventListener(this, toucheventselector(JiXiaXueGong::jixiaButtonClick));
	btnJX3->setTag(JiXiaBtnItem3);

	auto btnJX4 = dynamic_cast<Button *>(Helper::seekWidgetByName(jiXiaXueGongUI, "Button_BGJ4"));
	btnJX4->addTouchEventListener(this, toucheventselector(JiXiaXueGong::jixiaButtonClick));
	btnJX4->setTag(JiXiaBtnItem4);

	auto closeButton = dynamic_cast<Button *>(Helper::seekWidgetByName(jiXiaXueGongUI, "Button_Close"));
	closeButton->addTouchEventListener(this, toucheventselector(JiXiaXueGong::jixiaButtonClick));
	closeButton->setTag(JiXiaBtnClose);

	auto btnRule = dynamic_cast<Button *>(Helper::seekWidgetByName(jiXiaXueGongUI, "Button_Rule"));
	btnRule->setEnabled(false);

	auto imgPower = dynamic_cast<ImageView *>(Helper::seekWidgetByName(jiXiaXueGongUI, "J_Power"));
	imgPower->setEnabled(false);

	auto imgTimes = dynamic_cast<ImageView *>(Helper::seekWidgetByName(jiXiaXueGongUI, "J_Times"));
	imgTimes->setEnabled(false);

	auto imgAddTimes = dynamic_cast<ImageView *>(Helper::seekWidgetByName(jiXiaXueGongUI, "Image_AddFrequency"));
	imgAddTimes->setEnabled(false);

	auto imgDiamond = dynamic_cast<ImageView *>(Helper::seekWidgetByName(jiXiaXueGongUI, "Diamond_Image_0"));
	imgDiamond->setEnabled(false);

	return true;
}

void JiXiaXueGong::jixiaButtonClick(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		if (UserData::getInstance()->setupEffect)
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(Click);

		auto btn = (Button*)pSender;
		auto tag = (JiXiaBtnEnum)btn->getTag();
		
		if (JiXiaBtnClose == tag)
		{
			Director::getInstance()->replaceScene(MainScene::scene());
		}
		else
		{
			auto jxxgBuffInfo = DataManager::getInstance()->interJxxgBuffVector();
			if (jxxgBuffInfo[0].ticket + jxxgBuffInfo[1].ticket + jxxgBuffInfo[2].ticket + jxxgBuffInfo[3].ticket > 3)
			{
				auto notice = PromptBox::getInstance(FontChina::getInstance()->getComString("JxxgTickets")->getCString());
				notice->setFade();
				this->addChild(notice);
				return;													/* 稷下学宫最多进入3次 */
			}

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

			UserData::getInstance()->setPointID(tag);
			switch (tag)
			{
			case JiXiaBtnItem1:
				UserData::getInstance()->setRoleCreateModel(RoleCreMode_XueGong1);
				break;
			case JiXiaBtnItem2:
				UserData::getInstance()->setRoleCreateModel(RoleCreMode_XueGong2);
				break;
			case JiXiaBtnItem3:
				UserData::getInstance()->setJxxg3Grade(-1);
				UserData::getInstance()->setRoleCreateModel(RoleCreMode_XueGong3);
				break;
			case JiXiaBtnItem4:
				UserData::getInstance()->setJxxg4Grade(0);
				UserData::getInstance()->setRoleCreateModel(RoleCreMode_XueGong4);
				break;
			}

			RolePrestrain begin;
			begin.loading(tag);
		}
	}
}