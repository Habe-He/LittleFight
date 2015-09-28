#include "TaskCell.h"
#include "cocostudio/CocoStudio.h"
#include "TaskLayer.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;

const cocos2d::Size szImage = cocos2d::Size(80, 80);
const char *uiDailyQuestCellRoot = "UI/All/DailyQuestCell.ExportJson";
const char *beganButton = "Began_Button";
const char *getButton = "Get_Button";


TaskCell::TaskCell(void)
{
}

TaskCell::~TaskCell(void)
{
}

bool TaskCell::init()
{
	do 
	{
		m_ptOriginleLoc = Point(0.0f, 0.0f);
		m_ptTouchLoc = Point(0.0f, 0.0f);

		auto taskCell = GUIReader::getInstance()->widgetFromJsonFile(uiDailyQuestCellRoot);
		CC_BREAK_IF( NULL == taskCell );
		this->addChild(taskCell);

		taskCell->addTouchEventListener(this, toucheventselector(TaskCell::panelTouchCallback));
		taskCell->setTouchEnabled(true);

		auto rightPanel = dynamic_cast<Layout*>(Helper::seekWidgetByName(taskCell, "DailyQuestCell_Panel"));

		began = dynamic_cast<Button* >(rightPanel->getChildByName(beganButton));
		began->setVisible(false);
		began->setTouchEnabled(false);

		goToFinish = dynamic_cast<Button* >(rightPanel->getChildByName(getButton));
		goToFinish->setVisible(false);
		goToFinish->setTouchEnabled(false);

		finishPic = dynamic_cast<ImageView *>(rightPanel->getChildByName("Image_537"));
		finishPic->setVisible(false);

	} while ( 0 );
	return true;
}

void TaskCell::setTaskDone(int num)
{
	if (num == 0)
	{
		goToFinish->setVisible(true);
		goToFinish->setTouchEnabled(true);
		finishPic->setVisible(true);
	}
	else
	{
		began->setVisible(true);
		began->setTouchEnabled(true);
	}
}

/*********************************************************************
** 功能：		cell点击响应函数
** 输入参数：	Ref* ref, TouchEventType type
** 返回值： 	无
** 修改记录：	
*********************************************************************/
void TaskCell::panelTouchCallback(Ref* pSender, TouchEventType type)
{
	auto ptLoc = Point(0, 0);
	auto task = (Widget *)pSender;
	auto scroll = (ScrollView *)task->getParent()->getParent()->getParent();
	auto inner = scroll->getInnerContainer();
	auto temp = scroll->getContentSize().height - inner->getContentSize().height;

	if ( TouchEventType::TOUCH_EVENT_BEGAN == type )
	{
		m_ptTouchLoc = task->getTouchStartPos();
		m_ptOriginleLoc = inner->getPosition();
	}
	else if ( TouchEventType::TOUCH_EVENT_MOVED == type )
	{
		ptLoc = task->getTouchMovePos();
		auto pt = m_ptOriginleLoc.y + ptLoc.y - m_ptTouchLoc.y;
		pt = (pt > 0) ? 0 : pt;
		pt = (pt < temp) ? temp : pt;
		inner->setPositionY(pt);
	}
	else
	{
		//
	}
}