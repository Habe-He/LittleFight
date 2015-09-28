/*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名： StoreProp
** 日期：   2014:10:10
** 说明：	  商人界面----------------道具界面
** 其它：	  
** 历史：	2014:10:10 初始版本
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Public/FontChina.h"
using namespace std;
USING_NS_CC;

class StoreProp : public cocos2d::Node
{
public:
	StoreProp();
	virtual ~StoreProp();

public:
	// 物品ID、中文名称、中文拼音、数量、价格、表名、序列
	static StoreProp *create(int id, const std::string chinaName, const std::string chinaSmallName, const int count, int price, char tableName[30], int index);

protected:
	bool init(int id, const std::string chinaName, const std::string chinaSmallName, const int count, int price, char tableName[30], int index);
	/* 关闭按钮 */
	void btnBuy(cocos2d::Ref* , cocos2d::ui::TouchEventType);
	/* 图片显示 */
	void showImage(cocos2d::ui::ImageView* , std::string);

private:
	std::string m_strPropName;

	// 存表名
	std::vector<std::string> v_tableName;
	// ID 
	vector<int> v_tableID;
	// 数量
	vector<int> v_count;
	// 单价
	vector<int> v_price;
};