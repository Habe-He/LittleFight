#pragma once
#include "cocos2d.h"

enum BattleSign
{
	Battle_One = 0,
	Battle_Two,
	Battle_Three,
	Battle_Max
};

enum PointMode
{
	PointModel_Normal = 0,						/* 普通级 */
	PointModel_Hard,							/* 精英级 */
	PointModel_Max
};

enum PointState
{
	PointState_Off = 0,							/* 关卡未开启 */
	PointState_Normal,							/* 普通关卡 */
	PointState_Boss,							/* Boss关卡 */
	PointState_Max
};

enum PointZorder
{
	PointZorder_Effect = 0,						/* 光环层 */
	PointZorder_Button,
	PointZorder_Flag,
	PointZorder_Max
};

const int maxStarNum = 3;						/* 最大星级 */
const int PointsPerBattle = 20;					/* 每个战场关卡数 */
const int PointIDStart = 1000;					/* 关卡ID 1000开始 */

typedef struct tagCellInfo
{
	int		station;							/* 关卡ID */
	int		stars;								/* 星级 */
	int		model;								/* 模式 1: 精英级 */
	bool	isOn;								/* 是否开启 true: 是 */
} CellInfo;