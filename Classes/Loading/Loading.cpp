#include "Loading.h"

Loading* Loading::mpLoading = NULL;

Loading::Loading():spriteCount(0), loadSpriteCount(0), percent(0)
{

}

Loading::~Loading()
{
	CC_SAFE_RELEASE_NULL(textureCacheArray);
	CC_SAFE_RELEASE(mpLoading);
}

void Loading::onEnter()
{
	Layer::onEnter();
}

void Loading::onExit()
{
	
	textureCacheArray->removeAllObjects();
	mpLoading = NULL;
	Layer::onExit();
}

Scene* Loading::scene()
{
	auto scene = Scene::create();
	auto layer = Loading::create();
	layer->setTag(LAYERTAG);
	scene->addChild(layer);
	return scene;
}

bool Loading::init()
{
	textureCacheArray = __Array::create();
	textureCacheArray->retain();

	mpFontChina = FontChina::getInstance();
	mpFontChina->initStringXml();

	

	auto spriteBG = Sprite::create("TempPic/Loading/loading1.png");
	spriteBG->setPosition(Point(400, 240));
	this->addChild(spriteBG);
	
	auto size = Director::getInstance()->getVisibleSize();
	auto spriteProgress = Sprite::create("TempPic/Loading/Loading.png");
	auto progressBar = ProgressTimer::create(spriteProgress);
	progressBar->setType(ProgressTimer::Type::BAR);
	progressBar->setMidpoint(Point::ANCHOR_BOTTOM_LEFT);
	progressBar->setBarChangeRate(Point::ANCHOR_BOTTOM_RIGHT);
	progressBar->setPosition(Point(size.width / 2, 0 + 80));
	progressBar->setPercentage(0);
	this->addChild(progressBar, 10, PROGRESSTAG);

	auto sprite2 = Sprite::create("TempPic/Loading/LoadingBG.png");
	sprite2->setPosition(Point(size.width / 2, 0 + 80));
	this->addChild(sprite2, 2);

	auto label = Label::create();
	label->setPosition(Point(400, 40));
	label->setSystemFontSize( 20.0f );
	this->addChild(label, 10);

	auto nameString = __String::createWithFormat("Loading%d", ToolFunc::calcRandom(1, 19));
	auto labelString = __String::createWithFormat("%s", mpFontChina->getComString(nameString->getCString())->getCString());
	label->setString(labelString->getCString());

	return true;
}

void Loading::addTextureCacheFromFileByName(const char* res)
{
	auto spriteString = __String::createWithFormat("%s", res);
	textureCacheArray->addObject(spriteString);
}

void Loading::setChangeScene(Scene*(*pScene)())
{
	this->pScene = pScene;
	auto action = Sequence::create(CallFunc::create(CC_CALLBACK_0(Loading::purgeCache, this)), CallFunc::create(CC_CALLBACK_0(Loading::loadCaChe, this)), NULL);
	this->runAction(action);
	this->schedule(schedule_selector(Loading::progress), 0.2f);
}

void Loading::purgeCache()
{
// 	TextureCache::getInstance()->removeAllTextures();
// 	TextureCache::getInstance()->removeUnusedTextures();
//	TextureCache::destroyInstance();
	SpriteFrameCache::destroyInstance();
}

void Loading::loadCaChe()
{
	spriteCount = textureCacheArray->count();
	if (spriteCount == 0)
		callBackReplaceScene();
	Ref* pSender;
	CCARRAY_FOREACH(textureCacheArray, pSender)
	{
		auto pString = static_cast<__String*>(pSender);
		auto pngString = __String::createWithFormat("%s.png", pString->getCString());
		Director::getInstance()->getTextureCache()->addImageAsync(pngString->getCString(), CC_CALLBACK_1(Loading::loadSpriteCountCallBack, this, pString->getCString() ));
	}
}

void Loading::progress(float dt)
{
}

void Loading::callBackReplaceScene()
{
	Scene* scene = (*pScene)();
	Director::getInstance()->replaceScene(scene);
}

void Loading::loadSpriteCountCallBack(Texture2D* texture, string resourcePath)
{
	loadSpriteCount ++;
 	if ( percent < loadSpriteCount / spriteCount * 100 )
 		percent = loadSpriteCount / spriteCount * 100;
	auto progressBar = (ProgressTimer*)this->getChildByTag(PROGRESSTAG);
	progressBar->setPercentage(progressBar->getPercentage() + percent + 100 / spriteCount);

 	auto plistString = __String::createWithFormat("%s.plist", resourcePath.c_str());
	auto pngString = __String::createWithFormat("%s.png", resourcePath.c_str());
 	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plistString->getCString(), pngString->getCString());
	

	if (loadSpriteCount == spriteCount)
	{
		progressBar->setPercentage(100.0f);
		auto pAction = CallFunc::create(this, callfunc_selector(Loading::callBackReplaceScene));
		this->runAction(pAction);
	}
}

