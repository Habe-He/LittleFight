 /*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名： FightPoints
** 日期：   2015:5:7
** 说明：	关卡选择界面
** 其它：	
** 历史：2015:5:7 初始版本
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "PointCell.h"
#include "DataManager/DataRecvEntities.h"

class FightPoints : public cocos2d::Layer
{
public:
	FightPoints(void);
	virtual ~FightPoints(void);

	static cocos2d::Scene* scene();
	virtual bool init();
	CREATE_FUNC(FightPoints);

public:
	void removeGoods();												/* 取消关卡物品显示 */

protected:
	void loadUI();													/* 加载UI */
	void loadPointsInfo(PointMode);								/* 放置关卡 */
	void PointButtonClick(cocos2d::Ref*, cocos2d::ui::TouchEventType);/* 关闭按钮 */
	void BattleButtonClick(cocos2d::Ref*, cocos2d::ui::TouchEventType);/* 战场按钮 */
	void CellButtonClick(cocos2d::Ref*, cocos2d::ui::TouchEventType);/* 关卡的回调 */
	std::vector<CustomsPassRecvStruct > getPointPassInfo(PointMode);/* 获取关卡通关信息 */
	void changeBattleSign(BattleSign);
	void showGoods(int );
	void removeGuide();

private:
	BattleSign		_battle;										/* 战场ID */
	PointMode		_mode;											/* 关卡模式 */

	cocos2d::ui::Widget			*_UIWidget;

	cocos2d::ui::ScrollView		*_scrollViewBattle;					/* 战场滚动层 */
	cocos2d::ui::Button			*_btnCom;							/* 普通关卡 */
	cocos2d::ui::Button			*_btnElite;							/* 精英关卡 */
	cocos2d::ui::Button			*_btnBattle[Battle_Max];			/* 战场 */
	cocos2d::ui::ImageView		*_imgGoods[8];						/* 关卡掉落物品 */
};

