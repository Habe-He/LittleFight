#include "ConfirmationBox.h"

ConfirmationBox* ConfirmationBox::getInstance(BoxState boxState)
{
	auto confirmBox = new ConfirmationBox();
	if (confirmBox)
	{
		confirmBox->autorelease();
		confirmBox->init(boxState);
	}
	else
	{
		CC_SAFE_DELETE(confirmBox);
		confirmBox = NULL;
	}
	return confirmBox;
}

bool ConfirmationBox::init(BoxState boxState)
{
	eBoxState = boxState;

	mpFontChina = FontChina::getInstance();
	mpFontChina->initStringXml();

	auto layerColor = LayerColor::create(Color4B(0, 0, 0, 166));
	this->addChild(layerColor);

	auto confirmBoxUI = GUIReader::getInstance()->widgetFromJsonFile("Confirm.ExportJson");
	confirmBoxUI->setPosition(Point(400 - confirmBoxUI->getContentSize().width / 2, 240 - confirmBoxUI->getContentSize().height / 2));
	layerColor->addChild(confirmBoxUI);

	promptText = dynamic_cast<Text* >(Helper::seekWidgetByName(confirmBoxUI, "Des_Label"));

	auto confirmClick = dynamic_cast<Button* >(Helper::seekWidgetByName(confirmBoxUI, "Confirm_Button"));
	confirmClick->addTouchEventListener(this, toucheventselector(ConfirmationBox::confirmButton));

	auto cancelClick = dynamic_cast<Button* >(Helper::seekWidgetByName(confirmBoxUI, "Cancel_Button"));
	cancelClick->addTouchEventListener(this, toucheventselector(ConfirmationBox::cancelButton));

	exchange();

	return true;
}

void ConfirmationBox::exchange()
{
	__String* promptString;
	switch (eBoxState)
	{
	case StateNoCoin:
		promptString = __String::createWithFormat("%s", mpFontChina->getComString("CoinAdd")->getCString());
		break;
	case StateNoDiamond:
		promptString = __String::createWithFormat("%s", mpFontChina->getComString("DiamondAdd")->getCString());
		break;
	case StateBuyPropGrid:
		promptString = __String::create("Opne Prop");
		break;
	case StateBuyEquipGrid:
		promptString = __String::create("Open Diamond");
		break;
	case StateChipGrid:
		promptString = __String::create("Open Chip");
		break;
	case StateMaxCoin:
		promptString = __String::createWithFormat("%s", mpFontChina->getComString("BuyTimesMax")->getCString());
		break;
	case StateMaxDiamond:
		promptString = __String::createWithFormat("%s", mpFontChina->getComString("BuyTimesMax")->getCString());
		break;
	default:
		break;
	}
	setPromptText(promptString->getCString());
}

void ConfirmationBox::setPromptText(string promptString)
{
	promptText->setText(promptString.c_str());
}

void ConfirmationBox::cancelButton(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		this->removeFromParentAndCleanup(true);
	}
}

void ConfirmationBox::confirmButton(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		switch (eBoxState)
		{
		case StateNoCoin:
			{
				auto starBar = StateBarNode::getInstance(StatePower);
				starBar->setPosition(Point(140, 430));
				starBar->addCoinClick(NULL, TOUCH_EVENT_ENDED);
				this->addChild(starBar, 3);
			}			
			break;
		case StateNoDiamond:
			this->removeFromParentAndCleanup(true);
			Director::getInstance()->pushScene(VIPPay::create());
			break;
		case StateBuyPropGrid:
			break;
		case StateBuyEquipGrid:
			break;
		case StateChipGrid:
			break;
		case StateMaxCoin:
			this->removeFromParentAndCleanup(true);
			break;
		case StateMaxDiamond:
			this->removeFromParentAndCleanup(true);
			break;
		default:
			break;
		}
	}
}

void ConfirmationBox::onEnter()
{
	Node::onEnter();
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(ConfirmationBox::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void ConfirmationBox::onExit()
{
	Node::onExit();
}

bool ConfirmationBox::onTouchBegan(Touch *touch, Event *unused_event)
{
	return true;
}