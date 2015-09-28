#include "NewModule.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;

NewModule::NewModule(void)
{
}

NewModule::~NewModule(void)
{
}

NewModule* NewModule::create(Node* container, ModuleMode mode)
{
	auto ret = new NewModule;
	if (ret && ret->init(mode))
	{
		ret->setPosition(220, 130);
		container->addChild(ret);
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

bool NewModule::init(ModuleMode mode)
{
	if (false == Layer::init())
	{
		return false;
	}

	auto module = GUIReader::getInstance()->widgetFromJsonFile("UI/All/NewModule.ExportJson");
	this->addChild(module);
	module->setTouchEnabled(false);
	_rcInvalidRegion = module->getBoundingBox();
	_rcInvalidRegion.origin = Point(180, 110);

	if (ModeFunction == mode)
	{
		auto func = dynamic_cast<ImageView *>(Helper::seekWidgetByName(module, "Image_NewModuleTitle"));
		func->setVisible(true);
	}
	else if (ModeEquip == mode)
	{
		auto func = dynamic_cast<ImageView *>(Helper::seekWidgetByName(module, "Image_NewModuleTitle_0"));
		func->setVisible(true);
	}
	else
	{
		auto func = dynamic_cast<ImageView *>(Helper::seekWidgetByName(module, "Image_NewModuleTitle_1"));
		func->setVisible(true);
	}

	_textInfo = dynamic_cast<Text *>(Helper::seekWidgetByName(module, "Label_ModuleIntro"));

	return true;
}

/*********************************************************************
** 功能：		显示内容
** 输入参数：	std::string strPic: 图片
**				std::string strInfo: 说明
** 返回值：		
** 修改记录：	
*********************************************************************/
void NewModule::showItem(std::string strPic, std::string strInfo)
{
	auto sp = Sprite::createWithSpriteFrameName(strPic + ".png");
	sp->setPosition(220, 130);
	this->addChild(sp);
	sp->setScale(0.2f);

	auto scale1 = ScaleTo::create(0.3f, 3.0f);
	auto delay = DelayTime::create(0.1f);
	auto scale2 = ScaleTo::create(0.15f, 1.0f);
	auto seq = Sequence::create(scale1, delay, scale2, NULL);
	sp->runAction(seq);
	
	_textInfo->setText(strInfo);
}

bool NewModule::onTouchBegan(Touch *touch, Event *unused_event)
{
	return true;
}

void NewModule::onTouchEnded(Touch *touch, Event *unused_event)
{
	auto point = touch->getLocation();
	if (true == _rcInvalidRegion.containsPoint(point))
	{
		if (_func)
		{
			_func();
		}
		this->removeFromParentAndCleanup(true);
	}
}

void NewModule::onEnter()
{
	Node::onEnter();

	_listener = EventListenerTouchOneByOne::create();
	_listener->setSwallowTouches(true);
	_listener->onTouchBegan = CC_CALLBACK_2(NewModule::onTouchBegan, this);
	_listener->onTouchEnded = CC_CALLBACK_2(NewModule::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener, this);
}

void NewModule::onExit()
{
	_eventDispatcher->removeEventListener(_listener);
	Node::onExit();
}

void NewModule::setFunction(const std::function<void() > &func)
{
	_func = func;
}