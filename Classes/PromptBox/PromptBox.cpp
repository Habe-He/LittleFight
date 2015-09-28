#include "PromptBox.h"

PromptBox* PromptBox::getInstance(string comString)
{
	auto prompt = new PromptBox();
	if (prompt)
	{
		prompt->autorelease();
		prompt->init(comString);
	}
	else
	{
		CC_SAFE_DELETE(prompt);
		prompt = NULL;
	}
	return prompt;
}

bool PromptBox::init(string initString)
{
	auto label = Label::create();
	label->setString(initString.c_str());
	label->setSystemFontSize(20.0f);
	label->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	auto size = Size(label->getContentSize().width + 20, label->getContentSize().height + 10);

	sprite = Scale9Sprite::create("TempPic/Prompt.png");
	sprite->setContentSize(size);
	sprite->addChild(label);
	label->setPosition(Point(sprite->getPosition() + Point(8, 5)));
	sprite->setPosition(Point(400, 240));
	this->addChild(sprite);

	return true;
}

void PromptBox::setMoveTop()
{
	auto moveto = MoveTo::create(2.0f, Point(0, 200));
	auto removeSprite = CallFunc::create(CC_CALLBACK_0(PromptBox::callBack, this));
	auto sequence = Sequence::create(moveto, removeSprite, NULL);
	this->runAction(sequence);
}

void PromptBox::setFade()
{
	auto fadeout = MoveTo::create(1.0f, Point( 0, 150 ));
	auto removeSprite = CallFunc::create(CC_CALLBACK_0(PromptBox::callBack, this));
	auto sequence = Sequence::create(fadeout, removeSprite, NULL);
	this->runAction(sequence);
}

void PromptBox::callBack()
{
	this->removeAllChildrenWithCleanup(true);	
}