#include "YiJiDangQian.h"

bool YiJiDangQian::init()
{
	auto yiJiDangQianUI = GUIReader::getInstance()->widgetFromJsonFile("UI/All/YiJiDangQian.ExportJson");
	this->addChild(yiJiDangQianUI);

	auto closeButton = dynamic_cast<Button *>(Helper::seekWidgetByName(yiJiDangQianUI, "Button_Close"));
	closeButton->addTouchEventListener(this, toucheventselector(YiJiDangQian::closeButton));

	return true;
}

void YiJiDangQian::closeButton(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		ToolFunc::playEffectFile( Click );
		Director::getInstance()->popScene();
	}
}