 /*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名： GameResult
** 日期：   2015:7:10
** 说明：	关卡稷下学宫通关层
** 其它：	
** 历史：2015:7:10 初始版本
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

enum Result
{
	Result_Win = 0,
	Result_Loss,
	Result_Max
};

class GameResult : public cocos2d::Layer
{
public:
	GameResult(void);
	virtual ~GameResult(void);

	static GameResult* create(Result = Result_Win, int = 180);
	virtual bool init(Result = Result_Win, int = 180);

protected:
	Result checkResult(Result);										/* 根据模式修正胜负 */
	void ResultModeWin();
	void ResultModeLoss();

	void loadPointWin();											/* 关卡胜利 */
	void loadPointLoss();											/* 关卡失败 */
	void winCallBack();
	void getPointStarLv();											/* 获得通关星级 */
	void loadFightWarriors();										/* 加载上阵武将 */
	void loadPointCoinExp();										/* 获得通关金币、经验奖励 */
	void loadPointGoods();											/* 获得通关物品奖励 */

	void loadGameXG1Win();											/* 稷下学宫模式1胜利 */
	void loadGameXG2Win();											/* 稷下学宫模式2胜利 */
	void loadGameXG3Win();											/* 稷下学宫模式3胜利 */
	void loadGameXG4Win();											/* 稷下学宫模式4胜利 */
	void loadGameXGLoss(int);										/* 稷下学宫模式失败 */

	float getTeamExpImprove();										/* 获取稷下学宫帐号经验加成 */
	float getRoleExpImprove();										/* 获取稷下学宫主将经验加成 */

	void btnPointWin(cocos2d::Ref*, cocos2d::ui::TouchEventType);	/* 关卡胜利回调 */
	void btnPointLoss(cocos2d::Ref*, cocos2d::ui::TouchEventType);	/* 关卡失败回调 */

	void pointLossSchedule(float);									/* 复活倒计时 */

	/* Animate */
	void starAnimate(int);											/* 星级动画 */
	void subStarAnimate(int);										/* 星级动画 */
	void fireworks();												/* 胜利烟花 */
	void goodsAnimate(cocos2d::ui::ImageView *, float);				/* 获得物品动画 */

private:
	int		_iTime;													/* 通关时间 */
	int		_iPoint;												/* 关卡ID */
	int		_iDiff;													/* 关卡难度 */
	int		_iStarLv;												/* 通关星级 */
	int		_iGameMode;												/* 模式 */
	int		_iSchedule;												/* 倒计时数字 */

	cocos2d::ui::Widget		*_uiPointWin;							/* 胜利UI */
	cocos2d::ui::Button		*_btnLife;								/* 复活按钮 */
	cocos2d::Sprite			*_spSchedule;							/* 倒计时 */
};

