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
** ���ܣ�		�ֻ���������
** ���������	��
** ����ֵ�� 	��
** �޸ļ�¼��	
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

	/* ���ֻ����ؼ��ļ��� */
	auto listener = EventListenerKeyboard::create();
	/* �ͻص������� */
	listener->onKeyReleased = CC_CALLBACK_2(KeyBoardMonitor::mobileRuturn, this);
	/* ��ӵ��¼��ַ����� */
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

/*********************************************************************
** ���ܣ�		�����ֻ����ؼ���Ӧ
** ���������	��
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
void KeyBoardMonitor::mobileRuturn(EventKeyboard::KeyCode keyCode,Event * pEvent)
{
	return;

	if ( keyCode == EventKeyboard::KeyCode::KEY_BACKSPACE )  /* ���ؼ� */
	{
		Director::getInstance()->end();
	}

	else if ( keyCode == EventKeyboard::KeyCode::KEY_MENU )
	{
		return;
	}
}