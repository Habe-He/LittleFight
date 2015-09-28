 /*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名： Counterpart_Def
** 日期：   2014:11:14
** 说明：	副本类数据、数据结构定义
** 其它：	
** 历史：2014:11:14 初始版本
*********************************************************************/
#pragma once
#include "cocos2d.h"

/***********************UI界面控件 Begin***************************/
enum MFControl
{
	MFCtrl_Sa,
	MFCtrl_Sb,
	MFCtrl_Sc,
	MFCtrl_Sd,
	MFCtrl_Pause,
	MFCtrl_MainHP,							/* 主HP进度条 */
	MFCtrl_SubHP,							/* 副HP进度条 */
	MFCtrl_Health,							/* 主将头像框 */
	MFCtrl_Max
};

enum PauseControl
{
	PCtrl_Quit,								/* 退出 */
	PCtrl_Resume,							/* 回到战斗 */
	PCtrl_Restart,							/* 重新开始 */
	PCtrl_Max
};

const int DefSceneNum = 2;							/* 每个关卡场景数 */
const int CmdSign[14] = {'e','d','s','f','r','v','w','x','j','u','i','o','p','q'};
/* 上、下、左、右、右上、右下、左上、左下、攻击、技能1、技能2、技能3、技能4、按钮弹起 */
const float UNIT_WIDTH = 55.0f;						/* 小伙伴图像坐标 */
const float GameResultAniDuration = 2.5f;			/* 战斗结算时间、经验动画时间 */
const cocos2d::Point ptActDir = cocos2d::Point(104, 88);/* 方向盘坐标 */

enum CounterpartOrder
{
	order_Bkg = 0,
	order_Role = 500,
	order_MainFight = 1000,
	order_Pause,
	order_Result,
	order_Max
};