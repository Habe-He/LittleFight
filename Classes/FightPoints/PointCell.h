 /*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名： PointCell
** 日期：   2015:5:7
** 说明：	关卡按钮
** 其它：	
** 历史：2015:5:7 初始版本
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "FightPoints_Def.h"

class PointCell : public cocos2d::Node
{
public:
	PointCell(void);
	virtual ~PointCell(void);

	static PointCell* create(CellInfo, BattleSign);
	virtual bool init(CellInfo, BattleSign);

public:
	/* 设置button回调事件 */
	void addBtnTouchEvent(cocos2d::Ref* , cocos2d::ui::SEL_TouchEvent);
	void btnPoints(cocos2d::Ref*, cocos2d::ui::TouchEventType);		/* 关卡的回调 */
	void loadFlagAnimate();											/* 旗帜飘扬动画 */
	void loadAureoleAnimate();										/* Boss关卡光环动画 */
	CellInfo getCellInfo();

private:
	CellInfo			_cell;

	int					_battle;									/* 战场ID */

	cocos2d::Sprite		*_spAureole;								/* Boss关卡光环动画 */
	cocos2d::Sprite		*_spCom;									/* 按钮背景图 */
	cocos2d::Sprite		*_spFlag;									/* boss关卡旗帜 */
	cocos2d::ui::Button *_btnCell;
};

