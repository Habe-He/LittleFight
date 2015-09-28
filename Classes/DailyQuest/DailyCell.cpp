#include "DailyCell.h"
#include "SimpleAudioEngine.h"
#include "UserInfo/Define_Info.h"

DailyCell::DailyCell()
{

}

DailyCell::~DailyCell()
{

}

DailyCell* DailyCell::getInstance()
{
	auto dDailyCell = new DailyCell();
	if (dDailyCell)
	{
		dDailyCell->init();
	}
	else
	{
		CC_SAFE_DELETE(dDailyCell);
		dDailyCell = NULL;
	}
	return dDailyCell;
}

bool DailyCell::init()
{
	dailyCellUI = GUIReader::getInstance()->widgetFromJsonFile("DailyQuestCell.ExportJson");
	dailyCellUI->setTouchEnabled(false);
	this->addChild(dailyCellUI);

	auto cellTag = dailyCellUI->getTag();

	titleName = dynamic_cast<Text* >(Helper::seekWidgetByName(dailyCellUI, "Label_TitleName"));
	goodsNum = dynamic_cast<Text* >(Helper::seekWidgetByName(dailyCellUI, "Label_DQRewardNum"));								
	finishFlag = dynamic_cast<Text* >(Helper::seekWidgetByName(dailyCellUI, "Label_clear"));	
	finishImage = dynamic_cast<ImageView* >(Helper::seekWidgetByName(dailyCellUI, "Image_finished"));
	goodsImage = dynamic_cast<ImageView* >(Helper::seekWidgetByName(dailyCellUI, "Image_Reward"));						
	gotoButton = dynamic_cast<Button* >(Helper::seekWidgetByName(dailyCellUI, "Began_Button"));	
	gotoButton->setVisible(false);
	gotoButton->setTouchEnabled(false);
	gotoButton->setTag(cellTag);
	gotoButton->addTouchEventListener(this, toucheventselector(DailyCell::gotoClick));
	collectButton = dynamic_cast<Button* >(Helper::seekWidgetByName(dailyCellUI, "Get_Button"));	
	collectButton->setVisible(false);
	collectButton->setTouchEnabled(false);
	collectButton->setTag(cellTag);
	collectButton->addTouchEventListener(this, toucheventselector(DailyCell::collectClick));

	return true;
}

void DailyCell::initData()
{
	if (DataManager::getInstance()->isGetCustomsPass())
	{
		interCustomsPassVector = DataManager::getInstance()->interCustomsPassVector();
	}

}

void DailyCell::setCellTitle(const string titleString)
{
	auto tiString = __String::createWithFormat("%s", titleString.c_str());
	titleName->setText(tiString->getCString());
	titleName->setFontSize(16);
}

void DailyCell::setCellPro(int iProgress, int maxProgress)
{
	auto proString = __String::createWithFormat("%d/%d", iProgress, maxProgress);
	auto labelPro = Label::create();
	labelPro->setPosition(Point(titleName->getPosition().x + titleName->getContentSize().width + 20, titleName->getPositionY()));
	labelPro->setString(proString->getCString());
	labelPro->setColor(Color3B::BLACK);
	labelPro->setSystemFontSize(16);
	this->addChild(labelPro, 10);
}

void DailyCell::setCellSprite(int iGoodsName)
{
	auto nameString = __String::createWithFormat("%d.png", iGoodsName);
	goodsImage->loadTexture(nameString->getCString());
}

void DailyCell::setCellClearn(int bInt)
{
	if (bInt == 0)
	{
		finishImage->setVisible(false);
		gotoButton->setVisible(true);
		gotoButton->setTouchEnabled(true);		
	}
	else
	{
		finishImage->setVisible(true);
		collectButton->setVisible(false);
		collectButton->setTouchEnabled(false);
	}
}

void DailyCell::setCellFinish(int bInt)
{
	if (bInt == 0)
	{
		finishFlag->setVisible(false);
	}
	else
	{
		finishFlag->setVisible(true);
	}
}

void DailyCell::setCellTag(int iTag)
{
	dailyCellUI->setTag(iTag);
	gotoButton->setTag(iTag);
	collectButton->setTag(iTag);
}

void DailyCell::gotoClick(Ref* sender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{

		if (UserData::getInstance()->setupEffect)
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(Click);

		auto gotoTag = ((Button* )sender)->getTag();
		if (gotoTag == 0)					// �ֶ�ͨ��δͨ����ͨ�ؿ�
		{
			int comCount = 0;
			for (unsigned int i = 0; i < interCustomsPassVector.size(); i ++)
			{
				if (interCustomsPassVector[ i ].customsPassID >= 2000)					// ��Ӣ�ؿ�
				{
					comCount ++;
				}
			}
			int comNum = 0;			// ��ͨ�ؿ�����
			comNum = interCustomsPassVector.size() - comCount;
			if ( comNum >= 20 )
			{
				// �ڶ����
			}
			else if ( comNum >= 40 )
			{
				// �������
			}
			else
			{
				// ��һ���
			}
// 
// 			auto warriors = DataManager::getInstance()->interPointSetsVector();
// 			if (0 == warriors.size())
// 			{
// 				DataManager::getInstance()->isGetPointSets();
// 				warriors = DataManager::getInstance()->interPointSetsVector();
// 			}
// 
// 			if (0 == warriors[0].generalID)				/* ������ */
// 			{
// 				auto notice = PromptBox::getInstance(FontChina::getInstance()->getComString("NoMainRole")->getCString());
// 				notice->setFade();
// 				this->addChild(notice);
// 				return;
// 			}
// 
// 			auto btnBattle = (Button*)pSender;
// 			auto tagButton = (BattleSign)btnBattle->getTag();
// 			Director::getInstance()->replaceScene(FightPoints::scene(tagButton));
// 			UserData::getInstance()->setBattleID(tagButton);
		}
		else if (gotoTag == 1)				// ͨ��һ��δͨ�ؾ�Ӣ�ؿ�
		{

		}
		else if (gotoTag == 2)				// �ֶ�ս����ȡ��������������ؿ���
		{

		}
		else if (gotoTag == 3)				// ͨ�ظ���10��
		{

		}
		else if (gotoTag == 4)				// �ھ���������5����ս
		{

		}
		else if (gotoTag == 5)				// �佫ǿ������
		{

		}
		else if (gotoTag == 6)				// �佫ǿ��10������
		{

		}
		else if (gotoTag == 7)				// �佫����
		{

		}
		else if (gotoTag == 8)				// һ��һ�ﵱǧ��һ�أ�
		{

		}
		else if (gotoTag == 9)				// һ�����ѧ����һ�أ�
		{

		}
		else if (gotoTag == 10)				// һ�����ѧ����һ�أ�
		{

		}
		else if (gotoTag == 11)				// ����һ�ν��
		{

		}
		else if (gotoTag == 12)				// ����һ������
		{

		}
		else if (gotoTag == 13)				// һ��������ʯ�鿨
		{

		}
		else if (gotoTag == 14)				// װ��10������
		{

		}
		else if (gotoTag == 15)				// װ��2�ξ���
		{

		}
		else if (gotoTag == 16)				// ���
		{

		}
		else if (gotoTag == 17)				// ���
		{

		}
		else if (gotoTag == 18)				// �������
		{

		}
	}
}

void DailyCell::collectClick(Ref* sender, TouchEventType type)
{
}