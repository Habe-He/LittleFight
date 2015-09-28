#include "AppDelegate.h"
#include "Start/Login.h"
#include "SimpleAudioEngine.h"
#include "OnceStartGame/OnestartGameStory.h"

using namespace CocosDenshion;
USING_NS_CC;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)  
#include "platform/android/jni/JniHelper.h"  
#endif  
#include "DataManager/DataManager.h"

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("Litttle Fight");
		glview->setFrameSize(800.0f, 480.0f);
        director->setOpenGLView(glview);
    }
	/* 游戏设计大小 */
	glview->setDesignResolutionSize(800, 480, ResolutionPolicy::EXACT_FIT);

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

	std::vector<std::string> searchPaths;
	searchPaths.push_back("UI/All");
	FileUtils::getInstance()->setSearchPaths(searchPaths);

	Scene* scene;
	if ( !UserDefault::getInstance()->getBoolForKey("firstGame") )
	{
		scene = startonce::scene();
	}
	else
	{
		scene = Login::scene();
	}
    director->runWithScene(scene); 

    return true;
}

void AppDelegate::showSpot()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	DataManager::getInstance()->isGetTeamInfo();					/* 当前战队等级 */
	auto teamInfo = DataManager::getInstance()->interTeamInfoVector();
	if (teamInfo[ 0 ].teamLevel > 6)
	{
		JniMethodInfo minfo;  
		bool isHave = JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/cpp/AppActivity", "getInstance", "()Ljava/lang/Object;" );  
		jobject activityObj;  
		if (isHave)  
		{  
			activityObj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);  
		}  
		isHave = JniHelper::getMethodInfo(minfo, "org/cocos2dx/cpp/AppActivity", "showSpot", "()V");  
		if (isHave)  
		{  
			minfo.env->CallVoidMethod(activityObj, minfo.methodID); 
		}
	}
#endif
}

void AppDelegate::showBanner()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	DataManager::getInstance()->isGetTeamInfo();					/* 当前战队等级 */
	auto teamInfo = DataManager::getInstance()->interTeamInfoVector();
	if (teamInfo[ 0 ].teamLevel > 6)
	{
		JniMethodInfo minfo;  
		bool isHave = JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/cpp/AppActivity", "getInstance", "()Ljava/lang/Object;" );  
		jobject activityObj;  
		if (isHave)  
		{  
			activityObj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);  
		}  
		isHave = JniHelper::getMethodInfo(minfo, "org/cocos2dx/cpp/AppActivity", "showBanner", "()V");  
		if (isHave)  
		{  
			minfo.env->CallVoidMethod(activityObj, minfo.methodID); 
		}
	}
#endif
}

void AppDelegate::hideBanner()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	JniMethodInfo minfo;  
	bool isHave = JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/cpp/AppActivity", "getInstance", "()Ljava/lang/Object;" );
	jobject activityObj;  
	if (isHave)  
	{
		activityObj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);  
	}  
	isHave = JniHelper::getMethodInfo(minfo, "org/cocos2dx/cpp/AppActivity", "hideBanner", "()V");  
	if (isHave)  
	{  
		minfo.env->CallVoidMethod(activityObj, minfo.methodID);  
	}
#endif
}

void AppDelegate::shareTimeLine()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	JniMethodInfo minfo;  
	bool isHave = JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/cpp/AppActivity", "getInstance", "()Ljava/lang/Object;" );
	jobject activityObj;  
	if (isHave)  
	{
		activityObj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);  
	}  
	isHave = JniHelper::getMethodInfo(minfo, "org/cocos2dx/cpp/AppActivity", "sendWCMsgTimeLine", "()V");  
	if (isHave)  
	{  
		minfo.env->CallVoidMethod(activityObj, minfo.methodID);  
	}
#endif
}

void AppDelegate::purchase(float price)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	JniMethodInfo minfo;  
	jfloat fPrice= (float)price;
	bool isHave = JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/cpp/AppActivity", "getInstance", "()Ljava/lang/Object;" );
	jobject activityObj;  
	if (isHave)  
	{
		activityObj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID); 
	}  
	isHave = JniHelper::getMethodInfo(minfo, "org/cocos2dx/cpp/AppActivity", "purchase", "(F)V");  
	if (isHave)  
	{  
		minfo.env->CallVoidMethod(activityObj, minfo.methodID, fPrice);  
	}
#endif
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
