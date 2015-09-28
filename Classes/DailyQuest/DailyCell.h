/*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名：   DailyCell
** 日  期：   2015:6:11
** 说  明：	每日任务每一单元
** 其  它：	
** 历  史：	2015:6:11 初始版本
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace cocostudio;
using namespace ui;
using namespace std;

#include "FightPoints/FightPoints.h"
#include "DataManager/DataManager.h"

class DailyCell : public Node
{
public:
	DailyCell();
	~DailyCell();

	static DailyCell* getInstance();

	bool init();
	
	void initData();										// 所需数据初始化

	void gotoClick(Ref* sender, TouchEventType type);			// 前往

	void collectClick(Ref* sender, TouchEventType type);			// 领取

	void setCellTitle(const string titleString);					// 设置单元格标题

	void setCellPro(int iProgress, int maxProgress);				// 设置进度（当前完成数、需要数）

	void setCellSprite(int iGoodsName);						// 设置图片

	void setCellClearn(int bInt);							// 设置此单元格是否完成

	void setCellFinish(int bInt);								// 此单元格是否	显示领取状态	

	void setCellTag(int iTag);								// 设置标志

private:
	Text* titleName;										// 标题
	Text* goodsNum;									// 物品数量
	Text* finishFlag;										// 已完成文字
	ImageView* finishImage;								// 已完成
	ImageView* goodsImage;								// 物品图片
	Button* gotoButton;									// 前往按钮
	Button* collectButton;									// 领取
	cocos2d::ui::Widget* dailyCellUI;							// cell控件
	vector< CustomsPassRecvStruct > interCustomsPassVector;   // 网络读取关卡信息
};