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
	
	// ����
	v_tableName.push_back(tableName);
	v_tableID.push_back(id);
	v_count.push_back(count);
	v_price.push_back(price);

	/* ����ͼƬ */
	auto imgItem = dynamic_cast<ImageView* >(Helper::seekWidgetByName(propSceneUI, "Image_Goods"));
	showImage(imgItem, chinaSmallName);
	m_strPropName = chinaSmallName;

	/* ����˵�� */
	auto txtDescribe = dynamic_cast<Text* >(Helper::seekWidgetByName(propSceneUI, "Des_Label"));
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	txtDescribe->setText(FontChina::G2U(chinaName.c_str()));
#else
	txtDescribe->setText(FontChina::G2U(chinaName.c_str()));
#endif
	txtDescribe->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);

	/* ���߼۸� */
	auto txtPrice = dynamic_cast<Text* >(Helper::seekWidgetByName(propSceneUI, "Price_Label"));
	std::string str;
	std::stringstream stream;
	stream << count * price;
	str = stream.str();
	txtPrice->setText(str);

	/* ����ť */
	auto btnBuy = dynamic_cast<Button* >(Helper::seekWidgetByName(propSceneUI, "Buy"));
	btnBuy->setTag(index);
	btnBuy->addTouchEventListener(this, toucheventselector(StoreProp::btnBuy));

	return true;
}

/*********************************************************************
** ���ܣ�		����ť
** ���������	Ref* pSender, TouchEventType type
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
void StoreProp::btnBuy(Ref* pSender, TouchEventType type)
{
	if ( TouchEventType::TOUCH_EVENT_ENDED == type )
	{
		
	}
}

/*********************************************************************
** ���ܣ�		ͼƬ��ʾ
** ���������	ImageView* image:ͼƬ��ʾ�ؼ�
**				std::string strImage:ͼƬ·��
** ����ֵ��		
** �޸ļ�¼��	
*********************************************************************/
void StoreProp::showImage(ImageView* image, std::string strImage)
{
	std::stringstream stream;
	std::string str;

	stream << strImage << ".png";
	str = stream.str();
	image->loadTexture(str, TextureResType::UI_TEX_TYPE_PLIST);
}