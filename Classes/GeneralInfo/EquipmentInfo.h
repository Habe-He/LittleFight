/*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名：   EquipmentInfo
** 日  期：   2015:5:8
** 说  明：	装备信息
** 其  它：	
** 历  史：	2015:5:8 初始版本
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;
using namespace std;

#include "EquipmentCell.h"
#include "DataManager/DataManager.h"
#include "DataManager/DataRecvEntities.h"
#include "Public/FontChina.h"
#include "NewComer/NewComer.h"

enum EquipPosType
{
	PosTypeNone,				// 空
	PosTypeArmour,				// 铠甲
	PosTypeHead,				// 头盔
	PosTypeDecorations,			// 饰品
	PosTypeWeapons,			// 武器
	PosTypeQi,				// 奇珍
	PosTypeYi					// 异宝
};

class EquipmentInfo : public Scene
{
public:
	EquipmentInfo();
	virtual ~EquipmentInfo();

	bool init();

	void initEquipmentData();											// 所需要的信息初始化

	void showEquipment();											// 显示滚动层上面的信息

	void singleEquipmentInfo(int pkID, int typeClick);						// 显示单个装备的信息........1 = 默认显示   0 = 点击显示

	void closeClick(Ref* pSender, TouchEventType type);						// 关闭按钮

	void imageClick(Ref* pSender, TouchEventType type);					// 装备图片点击回调

	void equipClick(Ref* pSender, TouchEventType type);						// 装备按钮
	void unloadClick(Ref* pSender, TouchEventType type);					// 卸下按钮
	void changeClick(Ref* pSender, TouchEventType type);					// 更换按钮

	CREATE_FUNC(EquipmentInfo);
private:
	bool isFull;													// 点击位置是否有装备
	// 临时变量
	cocos2d::Point m_ptOriginleLoc;
	cocos2d::Point m_ptTouchLoc;
	int equipmentPKID;												// 穿装备的主键
	FontChina* mpFontChina;											// 属性字体显示
	Layout* equipmentLayer;											// 右侧装备层
	Layout* singleInfo;												// 左侧单独装备信息
	cocos2d::ui::ScrollView* equipmentScrollView;							// 右侧装备滚动层
	vector<WareroomCommonRecvStruct > interEquipVector;					// 仓库中装备网络数据
	vector<EquipProptyStruct > localEquipVector;							// 装备基础属性
	vector<EquipProptyStruct > tempEquipVector;							// 装备基础属性
	vector<GeneralDetailRecvStruct > interGeneralEquipVector;					// 武将装备服务器获取到的信息

	NewComer	*_comer;
};