#include "NewComer.h"
#include "NewModule.h"
#include "Public/FontChina.h"
#include "UserInfo/UserData.h"
#include "DataManager/DataManager.h"

USING_NS_CC;

const int MaxGuidePoint = 1010;

NewComer::NewComer(void)
{
}

NewComer::~NewComer(void)
{
}

NewComer* NewComer::create(Node* container, int pID, int step, const std::function<void() > &func)
{
	auto ret = new NewComer;
	if (ret && ret->init(pID, step, func))
	{
		container->addChild(ret, 1000);
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}

	return ret;
}

NewComer* NewComer::create(Node* container, int pID, int step)
{
	auto ret = new NewComer;
	if (ret && ret->init(pID, step))
	{
		container->addChild(ret, 1000);
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}

	return ret;
}

bool NewComer::isGuideDone(int pID)
{
	bool bRet = true;

	auto cpID = UserData::getInstance()->getNewcomerGuide();
	auto high = cpID >> 16;										/* 完成标记 */
	auto low = cpID & 0x00FFFF;									/* 引导ID */

	if (((pID & 0xFFFF) == low) && (0 == high))					/* 引导ID为pID，且未完成 */
	{
		bRet = false;
	}

	return bRet;
}

int NewComer::getCurGuideID()
{
	return UserData::getInstance()->getNewcomerGuide();
}

void NewComer::setCurGuideID(int ID)
{
	UserData::getInstance()->savaNewcomerGuide(ID);
}

int NewComer::getCurGuideStep()
{
	return UserData::getInstance()->getGuideStep();
}

void NewComer::setCurGuideStep(int step)
{
	UserData::getInstance()->setGuideStep(step);
}

bool NewComer::init(int pID, int step, const std::function<void() > &func)
{
	initParam();
	if (func)
	{
		_func = func;
	}

	return init(pID, step);
}

bool NewComer::init(int pID, int step)
{
	auto cpID = UserData::getInstance()->getNewcomerGuide();
	cpID = cpID & 0x00FFFF;
	auto curStep = UserData::getInstance()->getGuideStep();
	if (pID != cpID)												/* 不是当前引导ID */
	{
		return false;
	}

	if (step != curStep)											/* 不是当前引导步骤 */
	{
		return false;
	}

	if (cpID > MaxGuidePoint)										/* 还有引导未完成 */
	{
		return false;
	}

	runGuide(cpID, step);

	return true;
}

void NewComer::initParam()
{
}

/* 显示箭头 */
void NewComer::addTargetGuide(int xLoc, int yLoc, float radius)
{
	auto spArrow = Sprite::create("res/Guide/arrow0.png");
	spArrow->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
	spArrow->setRotation(radius);
	this->addChild(spArrow);

	auto ptMove = Point(0, 0);
	auto offset = 10;
	if (radius == -90)												/* 箭头右指 */
	{
		spArrow->setPosition(xLoc - offset, yLoc);
		ptMove = Point(offset, 0);
	}
	else if (radius == 90)
	{
		spArrow->setPosition(xLoc + offset, yLoc);
		ptMove = Point(-offset, 0);
	}
	else
	{
		spArrow->setPosition(xLoc, yLoc + offset);
		ptMove = Point(0, -offset);
	}
	auto move = MoveBy::create(0.6f, ptMove);
	auto seq = Sequence::createWithTwoActions(move, move->reverse());
	spArrow->runAction(RepeatForever::create(seq));
}

void NewComer::addTargetFrame(int xLoc, int yLoc, float rateX, float rateY)
{
	auto spFrame = Sprite::create("res/Guide/frame.png");
	spFrame->setPosition(xLoc, yLoc);
	spFrame->setScaleX(rateX);
	spFrame->setScaleY(rateY);
	this->addChild(spFrame);
}

void NewComer::runGuide(int cpID, int step)
{
	switch (cpID - 1000)
	{
	case 0:
		guide1Step(step);
		break;
	case 1:
		guide2Step(step);
		break;
	case 2:
		guide3Step(step);
		break;
	case 3:
		guide4Step(step);
		break;
	case 4:
		guide5Step(step);
		break;
	case 5:
		guide6Step(step);
		break;
	case 6:
		guide7Step(step);
		break;
	case 7:
		guide8Step(step);
		break;
	case 8:
		guide9Step(step);
		break;
	case 9:
		guide10Step(step);
		break;
	case 10:
		guide11Step(step);
		break;
	}
}

void NewComer::guide1Step(int step)
{
	switch (step)
	{
	case 0:
		guide1Step1();
		break;
	case 1:
		guide1Step2();
		break;
	case 2:
		guide1Step3();
		break;
	case 3:
		guide1Step4();
		break;
	case 4:
		guide1Step5();
		break;
	case 5:
		guide1Step6();
		break;
	case 6:
		guide1Step7();
		break;
	}
}

void NewComer::guide2Step(int step)
{
	switch (step)
	{
	case 0:
		guide2Step1();
		break;
	case 1:
		guide2Step2();
		break;
	case 2:
		guide2Step3();
		break;
	}
}

void NewComer::guide3Step(int step)
{
	switch (step)
	{
	case 0:
		guide3Step1();
		break;
	case 1:
		guide3Step2();
		break;
	case 2:
		guide3Step3();
		break;
	case 3:
		guide3Step4();
		break;
	case 4:
		guide3Step5();
		break;
	case 5:
		guide3Step6();
		break;
	case 6:
		guide3Step7();
		break;
	}
}

void NewComer::guide4Step(int step)
{
	switch (step)
	{
	case 0:
		guide4Step1();
		break;
	case 1:
		guide4Step2();
		break;
	case 2:
		guide4Step3();
		break;
	case 3:
		guide4Step4();
		break;
	case 4:
		guide4Step5();
		break;
	}
}

void NewComer::guide5Step(int step)
{
	switch (step)
	{
	case 0:
		guide5Step1();
		break;
	case 1:
		guide5Step2();
		break;
	case 2:
		guide5Step3();
		break;
	case 3:
		guide5Step4();
		break;
	case 4:
		guide5Step5();
		break;
	case 5:
		guide5Step6();
		break;
	case 6:
		guide5Step7();
		break;
	case 7:
		guide5Step8();
		break;
	case 8:
		guide5Step9();
		break;
	}
}

void NewComer::guide6Step(int step)
{
	switch (step)
	{
	case 0:
		guide6Step1();
		break;
	case 1:
		guide6Step2();
		break;
	case 2:
		guide6Step3();
		break;
	}
}

void NewComer::guide7Step(int step)
{
	switch (step)
	{
	case 0:
		guide7Step1();
		break;
	}
}

void NewComer::guide8Step(int step)
{
	switch (step)
	{
	case 0:
		guide8Step1();
		break;
	case 1:
		guide8Step2();
		break;
	case 2:
		guide8Step3();
		break;
	case 3:
		guide8Step4();
		break;
	case 4:
		guide8Step5();
		break;
	}
}

void NewComer::guide9Step(int step)
{
	switch (step)
	{
	case 0:
		guide9Step1();
		break;
	case 1:
		guide9Step2();
		break;
	case 2:
		guide9Step3();
		break;
	case 3:
		guide9Step4();
		break;
	}
}

void NewComer::guide10Step(int step)
{
	switch (step)
	{
	case 0:
		guide10Step1();
		break;
	case 1:
		guide10Step2();
		break;
	case 2:
		guide10Step3();
		break;
	case 3:
		guide10Step4();
		break;
	case 4:
		guide10Step5();
		break;
	}
}

void NewComer::guide11Step(int step)
{
	switch (step)
	{
	case 0:
		guide11Step1();
		break;
	case 1:
		guide11Step2();
		break;
	case 2:
		guide11Step3();
		break;
	case 3:
		guide11Step4();
		break;
	}
}

/* 获得学徒短剑 */
void NewComer::guide1Step1()
{
	auto module = NewModule::create(this, ModeEquip);
	module->showItem("94013", FontChina::getInstance()->getComString("GuideID1")->getCString());
	if (_func)
	{
		module->setFunction(_func);
	}
}

/* 点击练兵场 */
void NewComer::guide1Step2()
{
	addTargetGuide(315, 270);
}

/* 点击第一个角色 */
void NewComer::guide1Step3()
{
	addTargetGuide(230, 355, 90.0f);
	addTargetFrame(179, 352, 1.02f, 1.2f);
}

/* 点击武将装备栏 */
void NewComer::guide1Step4()
{
	addTargetGuide(86, 80, -90.0f);
	addTargetFrame(116, 76, 0.6f, 0.6f);
}

/* 点击穿上装备 */
void NewComer::guide1Step5()
{
	addTargetGuide(175, 125);
	addTargetFrame(175, 100, 0.9f, 0.5f);
}

/* 点击挑战 */
void NewComer::guide1Step6()
{
	addTargetGuide(719, 120);
	addTargetFrame(719, 62, 1.6f, 1.2f);
}

/* 点击关卡 */
void NewComer::guide1Step7()
{
	addTargetGuide(142, 185, 90.0f);
	addTargetFrame(122, 185, 0.42f, 0.32f);
}


/* 获得天机镜 */
void NewComer::guide2Step1()
{
	auto module = NewModule::create(this, ModeEquip);
	module->showItem("94018", FontChina::getInstance()->getComString("GuideID2")->getCString());
	if (_func)
	{
		module->setFunction(_func);
	}
}

/* 点击挑战 */
void NewComer::guide2Step2()
{
	addTargetGuide(719, 120);
	addTargetFrame(719, 62, 1.6f, 1.2f);
}

/* 点击关卡 */
void NewComer::guide2Step3()
{
	addTargetGuide(140, 109, 90.0f);
	addTargetFrame(120, 109, 0.42f, 0.32f);
}

/* 点击酒馆 */
void NewComer::guide3Step1()
{
	addTargetGuide(520, 250);
}

/* 点击百里挑一 */
void NewComer::guide3Step2()
{
	addTargetGuide(408, 68);
	addTargetFrame(408, 48, 1.4f, 0.45f);
}

/* 点击练兵场 */
void NewComer::guide3Step3()
{
	addTargetGuide(315, 270);
}

/* 点击上阵位置 */
void NewComer::guide3Step4()
{
	addTargetGuide(452, 83);
	addTargetFrame(452, 47, 0.8f, 0.8f);
}

/* 点击第二个武将 */
void NewComer::guide3Step5()
{
	addTargetGuide(310, 355, 90.0f);
	addTargetFrame(290, 352, 1.02f, 1.2f);
}

/* 点击挑战 */
void NewComer::guide3Step6()
{
	addTargetGuide(719, 120);
	addTargetFrame(719, 62, 1.6f, 1.2f);
}

/* 点击关卡 */
void NewComer::guide3Step7()
{
	addTargetGuide(227, 158, 90.0f);
	addTargetFrame(207, 158, 0.42f, 0.32f);
}

/* 点击铁匠铺 */
void NewComer::guide4Step1()
{
	addTargetGuide(1128, 255);
}

/* 点击装备 */
void NewComer::guide4Step2()
{
	addTargetGuide(90, 85, -90.0f);
	addTargetFrame(116, 77, 0.6f, 0.6f);
}

/* 点击强化 */
void NewComer::guide4Step3()
{
	addTargetGuide(680, 70);
	addTargetFrame(680, 50, 1.35f, 0.45f);
}

/* 点击挑战 */
void NewComer::guide4Step4()
{
	addTargetGuide(719, 120);
	addTargetFrame(719, 62, 1.6f, 1.2f);
}

/* 点击关卡 */
void NewComer::guide4Step5()
{
	addTargetGuide(340, 174, 90.0f);
	addTargetFrame(320, 174, 0.42f, 0.32f);
}

/* 点击商城 */
void NewComer::guide5Step1()
{
	addTargetGuide(706, 275);
}

/* 点击经验药水 */
void NewComer::guide5Step2()
{
	addTargetGuide(380, 287, 90.0f);
	addTargetFrame(330, 287, 1.3f, 1.5f);
}

/* 点击购买确认 */
void NewComer::guide5Step3()
{
	addTargetGuide(473, 190);
	addTargetFrame(473, 177, 0.92f, 0.42f);
}

/* 点击练兵场 */
void NewComer::guide5Step4()
{
	addTargetGuide(315, 270);
}

/* 点击升级 */
void NewComer::guide5Step5()
{
	addTargetGuide(70, 255, 90.0f);
	addTargetFrame(45, 255, 0.45f, 0.82f);
}

/* 点击经验药水 */
void NewComer::guide5Step6()
{
	addTargetGuide(327, 98);
	addTargetFrame(327, 53, 0.78f, 0.78f);
}

/* 点击第二个武将 */
void NewComer::guide5Step7()
{
	addTargetGuide(310, 355, 90.0f);
	addTargetFrame(290, 352, 1.02f, 1.2f);
}

/* 点击挑战 */
void NewComer::guide5Step8()
{
	addTargetGuide(719, 120);
	addTargetFrame(719, 62, 1.6f, 1.2f);
}

/* 点击关卡 */
void NewComer::guide5Step9()
{
	addTargetGuide(454, 183, 90.0f);
	addTargetFrame(434, 183, 0.42f, 0.32f);
}

/* 点击练兵场 */
void NewComer::guide6Step1()
{
	addTargetGuide(315, 270);
}

/* 点击第一个角色 */
void NewComer::guide6Step2()
{
	addTargetGuide(230, 355, 90.0f);
	addTargetFrame(179, 352, 1.02f, 1.2f);
}

/* 点击技能升级按钮 */
void NewComer::guide6Step3()
{
	addTargetGuide(668, 351, -90.0f);
	addTargetFrame(685, 351, 0.36f, 0.36f);
}

/* 获得玉净瓶 */
void NewComer::guide7Step1()
{
	auto module = NewModule::create(this, ModeEquip);
	module->showItem("94017", FontChina::getInstance()->getComString("GuideID7")->getCString());
	if (_func)
	{
		module->setFunction(_func);
	}
}

/* 获得暴鸳碎片 * 30 */
void NewComer::guide8Step1()
{
	auto module = NewModule::create(this, ModeEquip);
	module->showItem("BaoYuan", FontChina::getInstance()->getComString("GuideID8")->getCString());
	if (_func)
	{
		module->setFunction(_func);
	}
}

/* 点击仓库 */
void NewComer::guide8Step2()
{
	addTargetGuide(920, 230);
}

/* 点击碎片菜单 */
void NewComer::guide8Step3()
{
	addTargetGuide(700, 158, -90.0f);
	addTargetFrame(752, 158, 0.9f, 0.58f);
}

/* 点击暴鸳碎片 */
void NewComer::guide8Step4()
{
	addTargetGuide(380, 353, 90.0f);
	addTargetFrame(354, 353, 0.6f, 0.6f);
}

/* 点击合成 */
void NewComer::guide8Step5()
{
	addTargetGuide(154, 95);
	addTargetFrame(154, 76, 1.0f, 0.45f);
}

/* 点击铁匠铺 */
void NewComer::guide9Step1()
{
	addTargetGuide(1128, 255);
}

/* 点击装备 */
void NewComer::guide9Step2()
{
	addTargetGuide(160, 76, -90.0f);
	addTargetFrame(182, 76, 0.6f, 0.6f);
}

/* 点击材料 */
void NewComer::guide9Step3()
{
	addTargetGuide(418, 179, 90.0f);
	addTargetFrame(393, 179, 0.5f, 0.48f);
}

/* 点击精炼 */
void NewComer::guide9Step4()
{
	addTargetGuide(680, 65);
	addTargetFrame(680, 47, 1.35f, 0.45f);
}

/* 点击练兵场 */
void NewComer::guide10Step1()
{
	addTargetGuide(315, 270);
}

/* 点击第一个角色 */
void NewComer::guide10Step2()
{
	addTargetGuide(230, 355, 90.0f);
	addTargetFrame(179, 352, 1.02f, 1.2f);
}

/* 点击培养 */
void NewComer::guide10Step3()
{
	addTargetGuide(750, 253, -90.0f);
	addTargetFrame(773, 253, 0.5f, 0.9f);
}

/* 点击培养丹 */
void NewComer::guide10Step4()
{
	addTargetGuide(385, 108, -90.0f);
	addTargetFrame(431, 108, 0.82f, 0.82f);
}

/* 点击替换按钮 */
void NewComer::guide10Step5()
{
	addTargetGuide(642, 210);
	addTargetFrame(642, 193, 1.35f, 0.5f);
}

/* 点击练兵场 */
void NewComer::guide11Step1()
{
	addTargetGuide(315, 270);
}

/* 点击第一个角色 */
void NewComer::guide11Step2()
{
	addTargetGuide(230, 355, 90.0f);
	addTargetFrame(179, 352, 1.02f, 1.2f);
}

/* 点击突破 */
void NewComer::guide11Step3()
{
	addTargetGuide(750, 153, -90.0f);
	addTargetFrame(773, 153, 0.5f, 0.9f);
}

/* 点击突破按钮 */
void NewComer::guide11Step4()
{
	addTargetGuide(550, 70);
	addTargetFrame(550, 57, 1.40f, 0.5f);
}