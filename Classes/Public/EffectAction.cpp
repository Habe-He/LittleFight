#include "EffectAction.h"
#include "ToolFunc.h"

EffectAction* EffectAction::getInstance()
{
	auto mpEffectAction = new EffectAction();
	if (mpEffectAction)
	{
		mpEffectAction->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(mpEffectAction);
		mpEffectAction = NULL;
	}
	return mpEffectAction;
}

void EffectAction::unLockAnim()
{
	auto sprite = Sprite::create("TempPic/unLock/1.png"); // TempPic\unLock
	sprite->setPosition(Point(400, 240));
	this->addChild(sprite);

	auto animation = Animation::create();
	char strName[50] = {0};
	for(int i = 1; i <= 36; i++)
	{
		sprintf(strName, "TempPic/unLock/%d.png", i );
		animation->addSpriteFrameWithFile(strName);
	}

	animation->setDelayPerUnit(2.5f / 36);
	animation->setRestoreOriginalFrame(false);
	sprite->runAction(Sequence::create(Animate::create(animation), CallFunc::create(CC_CALLBACK_0(EffectAction::callBack, this)), NULL));
}

void EffectAction::loadingEffect()
{
	auto sprite = Sprite::create("TempPic/Loading/1.png");
	this->addChild(sprite);

	auto animation = Animation::create();
	char strName[ 50 ] = { 0 };
	for(int i = 1; i <= 4; i++)
	{
		sprintf(strName, "TempPic/Loading/%d.png", i );
		animation->addSpriteFrameWithFile(strName);
	}

	animation->setDelayPerUnit(1.0f / 4);
	animation->setRestoreOriginalFrame(true);
	sprite->runAction(RepeatForever::create( Animate::create(animation) ));
}

void EffectAction::waitSignInEffect(){
	auto sprite = Sprite::create("TempPic/SignIn/1.png");
	this->addChild(sprite);
	auto animation = Animation::create();
	char strName[ 50 ] = { 0 };
	for(int i = 1; i <= 25; i++)
	{
		sprintf(strName, "TempPic/SignIn/%d.png", i );
		animation->addSpriteFrameWithFile(strName);
	}

	animation->setDelayPerUnit(1.0f / 8);
	animation->setRestoreOriginalFrame(true);
	sprite->runAction(RepeatForever::create( Animate::create(animation) ));
}

void EffectAction::buttonBack()
{
	auto sprite = Sprite::create("TempPic/mainEF/2.png");
	this->addChild(sprite);

	auto animation = Animation::create();
	char strName[ 50 ] = { 0 };
	for( int i = 2; i <= 60; i += 2 )
	{
		sprintf(strName, "TempPic/mainEF/%d.png", i );
		animation->addSpriteFrameWithFile(strName);
	}
	float dt = ToolFunc::calcRandom(8, 12) / 10.0f;
	animation->setDelayPerUnit(dt / 30);
	animation->setRestoreOriginalFrame(true);
	sprite->runAction(RepeatForever::create( Animate::create(animation) ));
}

void EffectAction::drawoffEffect()
{
	auto sprite = Sprite::create("TempPic/Drawoff/Image1.png");
	sprite->setPosition(Point(400, 240));
	this->addChild(sprite);

	auto animation = Animation::create();
	char strName[50] = {0};
	for(int i = 1; i <= 5; i++)
	{
		sprintf(strName, "TempPic/Drawoff/Image%d.png", i );
		animation->addSpriteFrameWithFile(strName);
	}
	animation->setDelayPerUnit(1.0f / 5);
	animation->setRestoreOriginalFrame(true);
	sprite->runAction(RepeatForever::create( Animate::create(animation) ));
}

void EffectAction::fbEffect()
{
	auto sprite = Sprite::create("TempPic/FB/cgmap1.png");
	this->addChild(sprite);

	auto animation = Animation::create();
	char strName[ 50 ] = { 0 };
	for( int i = 1; i <= 63; i ++ )
	{
		sprintf(strName, "TempPic/FB/cgmap%d.png", i );
		animation->addSpriteFrameWithFile(strName);
	}
	animation->setDelayPerUnit(2.0f / 63);
	animation->setRestoreOriginalFrame(true);
	sprite->runAction(RepeatForever::create( Animate::create(animation) ));
}

void EffectAction::tieEffect()
{
	auto sprite = Sprite::create("TempPic/Tie/cgmap1.png");
	this->addChild(sprite);

	auto animation = Animation::create();
	char strName[ 50 ] = { 0 };
	for( int i = 1; i <= 64; i ++ )
	{
		sprintf(strName, "TempPic/Tie/cgmap%d.png", i );
		animation->addSpriteFrameWithFile(strName);
	}
	animation->setDelayPerUnit(2.0f / 63);
	animation->setRestoreOriginalFrame(true);
	sprite->runAction(RepeatForever::create( Animate::create(animation) ));
}

void EffectAction::trainEffect()
{
	auto sprite = Sprite::create("TempPic/Propty/cgmap1.png");
	sprite->setScale(1.2f);
//	sprite->setPosition(Point(400, 240));
	this->addChild(sprite);

	auto animation = Animation::create();
	char strName[50] = {0};
	for(int i = 1; i <= 17; i++)
	{
		sprintf(strName, "TempPic/Propty/cgmap%d.png", i );
		animation->addSpriteFrameWithFile(strName);
	}

	animation->setDelayPerUnit(0.5f / 17);
	animation->setRestoreOriginalFrame(false);
	sprite->runAction(Sequence::create(Animate::create(animation), CallFunc::create(CC_CALLBACK_0(EffectAction::callBack, this)), NULL));
}

void EffectAction::callBack()
{
	this->removeFromParentAndCleanup(true);
}