#include "GamePause.h"
#include "cocostudio/CocoStudio.h"
#include "Counterpart/Counterpart_Def.h"
#include "Scene/MainScene.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;

const char *PauseLayerNames[PCtrl_Max] = 
{
	"Button_Quit",									/* 退出 */
	"Button_Resume",								/* 回到战斗 */
	"Button_Restart",								/* 重新开始 */
};

GamePause::GamePause(void)
{
}

GamePause::~GamePause(void)
{
}

bool GamePause::init()
{
	if (false == Layer::init())
	{
		return false;
	}

	loadPauseScene();

	return true;
}

/*********************************************************************
** 功能：		加载暂停界面
** 输入参数：	无
** 返回值：		无
** 修改记录：	
*********************************************************************/
void GamePause::loadPauseScene()
{
	m_hUIPause = GUIReader::getInstance()->widgetFromJsonFile("UI/All/Pause.ExportJson");
	this->addChild(m_hUIPause, order_Pause, order_Pause);

	auto itemQuit = dynamic_cast<Button *>(Helper::seekWidgetByName(m_hUIPause, PauseLayerNames[PCtrl_Quit]));
	itemQuit->setTag(PCtrl_Quit);									/* 退出 */
	itemQuit->addTouchEventListener(this, toucheventselector(GamePause::btnPauseClicked));

	auto itemResume = dynamic_cast<Button *>(Helper::seekWidgetByName(m_hUIPause, PauseLayerNames[PCtrl_Resume]));
	itemResume->setTag(PCtrl_Resume);								/* 继续战斗 */
	itemResume->addTouchEventListener(this, toucheventselector(GamePause::btnPauseClicked));

	auto itemRestart = dynamic_cast<Button *>(Helper::seekWidgetByName(m_hUIPause, PauseLayerNames[PCtrl_Restart]));
	itemRestart->setTag(PCtrl_Restart);								/* 重新开始 */
	itemRestart->addTouchEventListener(this, toucheventselector(GamePause::btnPauseClicked));

	setEnabled(false);
}

void GamePause::btnPauseClicked(Ref* ref, TouchEventType type)
{
	Button *btn = (Button *)ref;
	int tag = btn->getTag();
	Director::getInstance()->resume();

	if (TOUCH_EVENT_ENDED == type)
	{
		switch (tag)
		{
		case PCtrl_Quit:											/* 退出 */
		case PCtrl_Restart:											/* 重新开始 */
			Director::getInstance()->replaceScene(MainScene::scene());
			break;
		case PCtrl_Resume:											/* 继续战斗 */
			setEnabled(false);
			break;
		}
	}
}

void GamePause::setEnabled(bool enable)
{
	m_hUIPause->setEnabled(enable);
	if (true == enable)
	{
		Director::getInstance()->pause();		
	}
}