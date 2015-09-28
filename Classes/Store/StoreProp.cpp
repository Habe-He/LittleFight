#include "StoreProp.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;

StoreProp::StoreProp()
{
}

StoreProp::~StoreProp()
{
}

StoreProp *StoreProp::create(int id, const std::string chinaName, const std::string chinaSmallName, const int count, int price, char tableName[30], int index)
{
	auto pRet = new StoreProp;

	if ( pRet && pRet->init(id, chinaName, chinaSmallName, count, price, tableName, index) )
	{
		pRet->autorelease();
	}
	else
	{
		delete pRet;
		pRet = NULL;
	}

	return pRet;
}

bool StoreProp::init(int id, const std::string chinaName, const std::string chinaSmallName, const int count, int price, char tableName[30], int index)
{
	auto propSceneUI = GUIReader::getInstance()->widgetFromJsonFile("UI/All/StoreCell.ExportJson");
	this->addChild(propSceneUI, 10);
	setContentSize(propSceneUI->getContentSize());
	
	// 表名
	v_tableName.push_back(tableName);
	v_tableID.push_back(id);
	v_count.push_back(count);
	v_price.push_back(price);

	/* 道具图片 */
	auto imgItem = dynamic_cast<ImageView* >(Helper::seekWidgetByName(propSceneUI, "Image_Goods"));
	showImage(imgItem, chinaSmallName);
	m_strPropName = chinaSmallName;

	/* 道具说明 */
	auto txtDescribe = dynamic_cast<Text* >(Helper::seekWidgetByName(propSceneUI, "Des_Label"));
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	txtDescribe->setText(FontChina::G2U(chinaName.c_str()));
#else
	txtDescribe->setText(FontChina::G2U(chinaName.c_str()));
#endif
	txtDescribe->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);

	/* 道具价格 */
	auto txtPrice = dynamic_cast<Text* >(Helper::seekWidgetByName(propSceneUI, "Price_Label"));
	std::string str;
	std::stringstream stream;
	stream << count * price;
	str = stream.str();
	txtPrice->setText(str);

	/* 购买按钮 */
	auto btnBuy = dynamic_cast<Button* >(Helper::seekWidgetByName(propSceneUI, "Buy"));
	btnBuy->setTag(index);
	btnBuy->addTouchEventListener(this, toucheventselector(StoreProp::btnBuy));

	return true;
}

/*********************************************************************
** 功能：		购买按钮
** 输入参数：	Ref* pSender, TouchEventType type
** 返回值： 	无
** 修改记录：	
*********************************************************************/
void StoreProp::btnBuy(Ref* pSender, TouchEventType type)
{
	if ( TouchEventType::TOUCH_EVENT_ENDED == type )
	{
		
	}
}

/*********************************************************************
** 功能：		图片显示
** 输入参数：	ImageView* image:图片显示控件
**				std::string strImage:图片路径
** 返回值：		
** 修改记录：	
*********************************************************************/
void StoreProp::showImage(ImageView* image, std::string strImage)
{
	std::stringstream stream;
	std::string str;

	stream << strImage << ".png";
	str = stream.str();
	image->loadTexture(str, TextureResType::UI_TEX_TYPE_PLIST);
}