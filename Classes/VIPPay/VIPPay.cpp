#include "VIPPay.h"
#include "AppDelegate.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)  
#include "platform/android/jni/JniHelper.h"  
#endif

int diamondVaule = 0;

bool VIPPay::init()
{
	mpFontChina = FontChina::getInstance();
	mpFontChina->initStringXml();

	auto vipUI = GUIReader::getInstance()->widgetFromJsonFile("VIP.ExportJson");
	vipUI->setTag(99);
	this->addChild(vipUI, -1);

	vipScrollView = dynamic_cast<cocos2d::ui::ScrollView* >(Helper::seekWidgetByName(vipUI, "ScrollView_Buy"));

	for (int i = 1; i <= 5; i++)
	{
		auto buyString = __String::createWithFormat("Button_Buy%d", i );
		auto buy = dynamic_cast<Button* >(Helper::seekWidgetByName(vipScrollView, buyString->getCString()));
		buy->setTag( i );
		buy->addTouchEventListener(this, toucheventselector(VIPPay::itemClick));
	}
	
	auto buttonClose = dynamic_cast<Button* >(Helper::seekWidgetByName(vipUI, "Button_Close"));				// ¹Ø±Õ°´Å¥
	buttonClose->addTouchEventListener(this, toucheventselector(VIPPay::closeClick));

	return true;
}

void VIPPay::itemClick(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		ToolFunc::playEffectFile( Click );
		auto itemTag = ((Button* )pSender)->getTag();
		float price = 0.0f;
		if (itemTag == 0)
		{
			return;
		}
		else if (itemTag == 1)
		{
			diamondVaule = 150;
			price = 2.0f;
		}
		else if (itemTag == 2)
		{
			diamondVaule = 500;
			price = 6.0f;
		}
		else if (itemTag == 3)
		{
			diamondVaule = 1000;
			price = 12.0f;
		}
		else if (itemTag == 4)
		{
			diamondVaule = 3000;
			price = 30.0f;
		}
		else if (itemTag == 5)
		{
			diamondVaule = 980;
		}
		auto app = (AppDelegate *)(Application::getInstance()); 
		app->purchase(price);
	}	
}

void VIPPay::closeClick(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		ToolFunc::playEffectFile( Click );
		Director::getInstance()->popScene();	
	}
}

extern "C"
{
	void Java_org_cocos2dx_cpp_AppActivity_orderSuccess()
	{
		DataManager::getInstance()->isBuyDiamond(diamondVaule);
	}

	void Java_org_cocos2dx_cpp_AppActivity_orderFail()
	{
		log("Order Fail ");
	}
};
