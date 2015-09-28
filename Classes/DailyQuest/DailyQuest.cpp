#include "DailyQuest.h"
#include "DataManager/DataManager.h"
#include "DailyCell.h"

const int cellRow = 1;
const Size cellSize = Size(570.0f, 90.0f);				// 滚动层cell size 
const float cellScale = 1.0f;

bool DailyQuest::init()
{
	auto layer = LayerColor::create(Color4B(0, 0, 0, 166));
	this->addChild(layer);
	auto dailyQuestUI = GUIReader::getInstance()->widgetFromJsonFile("DailyQuest.ExportJson");
	layer->addChild(dailyQuestUI, 2);

	auto closeButton = dynamic_cast<Button* >(Helper::seekWidgetByName(dailyQuestUI, "Button_Close"));					
	closeButton->addTouchEventListener(this, toucheventselector(DailyQuest::closeClick));	

	dailyScrollView = dynamic_cast<cocos2d::ui::ScrollView* >(Helper::seekWidgetByName(dailyQuestUI, "D_ScrollView"));
	
	showDailyCell();

	return true;
}

void DailyQuest::showDailyCell()
{
	auto dailyVector = DataManager::getInstance()->localDailyTaskVector();

	dailyScrollView->removeAllChildrenWithCleanup(true);
	int cellCount = dailyVector.size();
	auto cell_Size = cellSize * cellScale;
	Size szInnerContainer = dailyScrollView->getContentSize();
	int cellGap = 0;									// 滚动层宽间隔 
	int cellHeightGap = 10;								// 滚动层高间隔 

	auto height = (cellSize.height * cellScale + cellHeightGap) * cellCount ;
	height = (height > szInnerContainer.height) ? height : szInnerContainer.height;
	dailyScrollView->setInnerContainerSize(Size(szInnerContainer.width, height));

	for (int i = 0; i < cellCount; i ++)
	{
		auto cell = DailyCell::getInstance();
		cell->setCellTitle(dailyVector[ i ].taskName);
		cell->setCellPro(0, dailyVector[ i ].dTimes);
		cell->setCellClearn( 0 );
		cell->setCellFinish( 0 );	
		cell->setPosition(Point( ( i % cellRow ) * (cellSize.width * cellScale + cellGap),
			height - ( i / cellRow + 1 ) * (cellSize.height * cellScale + cellHeightGap)));
		cell->setCellTag( i );
		dailyScrollView->addChild(cell);	
	}
}

void DailyQuest::closeClick(Ref* sender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		this->removeFromParentAndCleanup(true);
	}
}

