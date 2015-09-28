#include "KeyBoardMonitor.h"

USING_NS_CC;

KeyBoardMonitor::KeyBoardMonitor(void)
{
}


KeyBoardMonitor::~KeyBoardMonitor(void)
{
}

bool KeyBoardMonitor::init()
{
	bool bRet = false;

	do 
	{
		CC_BREAK_IF( false == Layer::init() );

		keyBoardListenEvent();
		bRet = true;

	} while ( 0 );

	return bRet;
}

/*********************************************************************
** 功能：		手机按键监听
** 输入参数：	无
** 返回值： 	无
** 修改记录：	
*********************************************************************/
void KeyBoardMonitor::keyBoardListenEvent()
{
	//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	//	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
	//#else
	//	CCScene* se = WelComeGameLayer::scene();
	//	CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(1,se));
	//	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	//	exit(0);
	//#endif
	//#endif

	/* 对手机返回键的监听 */
	auto listener = EventListenerKeyboard::create();
	/* 和回调函数绑定 */
	listener->onKeyReleased = CC_CALLBACK_2(KeyBoardMonitor::mobileRuturn, this);
	/* 添加到事件分发器中 */
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

/*********************************************************************
** 功能：		加载手机返回键响应
** 输入参数：	无
** 返回值： 	无
** 修改记录：	
*********************************************************************/
void KeyBoardMonitor::mobileRuturn(EventKeyboard::KeyCode keyCode,Event * pEvent)
{
	return;

	if ( keyCode == EventKeyboard::KeyCode::KEY_BACKSPACE )  /* 返回键 */
	{
		Director::getInstance()->end();
	}

	else if ( keyCode == EventKeyboard::KeyCode::KEY_MENU )
	{
		return;
	}
}