#include "TaskLayer.h"
#include "TaskCell.h"
#include "cocostudio/CocoStudio.h"
#include "Scene/MainScene.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;

const Size cellSize = Size(298, 97);

TaskLayer::TaskLayer()
{
}

TaskLayer::~TaskLayer()
{
}

Scene* TaskLayer::scene()
{
	Scene* scene = Scene::create();
	TaskLayer* layer = TaskLayer::create();
	scene->addChild(layer);
	return scene;
}

bool TaskLayer::init()
{
	if ( false == Layer::init() )
	{
		return false;
	}

	auto DailyQuestUI = GUIReader::getInstance()->widgetFromJsonFile("UI/All/DailyQuest.ExportJson");
	DailyQuestUI->setAnchorPoint(Point(0.5, 0.5));
	DailyQuestUI->setPosition(Point(400, 240));
	this->addChild(DailyQuestUI);

	auto S_E_UI_Panel = dynamic_cast<Layout*>(DailyQuestUI->getChildByName("DailyQuest_Panel"));
	auto bg_Panel = dynamic_cast<Layout*>(DailyQuestUI->getChildByName("Panel_29"));

	m_ScrollTaskCellList = dynamic_cast<cocos2d::ui::ScrollView* >(bg_Panel->getChildByName("D_ScrollView"));

	auto closeBtn = dynamic_cast<Button *>(bg_Panel->getChildByName("Close"));
	closeBtn->addTouchEventListener(this, toucheventselector(TaskLayer::btnCloseClicked));

	getDailyQuestData();

	return true;
}

void TaskLayer::getDailyQuestData()
{
	addDailyQuest();
}

void TaskLayer::addDailyQuest()
{
	m_ScrollTaskCellList->removeAllChildrenWithCleanup(true);
	if ( NULL == m_ScrollTaskCellList )
	{
		return;
	}
	m_ScrollTaskCellList->removeAllChildrenWithCleanup(true);

	int size = numOfTask.size();
	auto scrollViewSize = m_ScrollTaskCellList->getContentSize();
	auto gapVer = 25;
	auto gapHor = (scrollViewSize.width - cellSize.width) / 2;
	auto height = (cellSize.height + gapVer) * size + gapVer;

	if ( height <= scrollViewSize.height )
	{
		height = scrollViewSize.height;
	}

	m_ScrollTaskCellList->setInnerContainerSize(Size(scrollViewSize.width, height));

	for (int i = 0;i < size;i ++)
	{
		auto cell = TaskCell::create();
		cell->setPosition(Point(gapHor -gapVer , height - (gapVer + cellSize.height) * (i + 1)));
		cell->setTaskDone(numOfTask[ i ]);

		cell->began->addTouchEventListener(this, toucheventselector(TaskLayer::btnGoTask));
		cell->goToFinish->addTouchEventListener(this, toucheventselector(TaskLayer::btnGoFinish));
		cell->began->setTag(whichTask[i]);
		cell->goToFinish->setTag(whichTask[i]);

		m_ScrollTaskCellList->addChild(cell);
	}
}

void TaskLayer::btnGoTask(Ref* pSender, TouchEventType type)
{
	if ( TouchEventType::TOUCH_EVENT_ENDED == type )
	{
		auto btn = (Button *)pSender;
		auto tag = btn->getTag();
		
		Director::getInstance()->replaceScene(MainScene::scene());
	}
}

void TaskLayer::btnGoFinish(Ref* pSender, TouchEventType type)
{
	if ( TouchEventType::TOUCH_EVENT_ENDED == type )
	{
		auto btn = (Button *)pSender;
		auto tag = btn->getTag();
		
		getDailyQuestData();
	}
}

void TaskLayer::btnCloseClicked(Ref* pSender, TouchEventType type)
{
	if ( TouchEventType::TOUCH_EVENT_ENDED == type )
	{
		Director::getInstance()->replaceScene(MainScene::scene());
	}
}