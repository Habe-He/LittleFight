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
	PointModel_Normal = 0,						/* ��ͨ�� */
	PointModel_Hard,							/* ��Ӣ�� */
	PointModel_Max
};

enum PointState
{
	PointState_Off = 0,							/* �ؿ�δ���� */
	PointState_Normal,							/* ��ͨ�ؿ� */
	PointState_Boss,							/* Boss�ؿ� */
	PointState_Max
};

enum PointZorder
{
	PointZorder_Effect = 0,						/* �⻷�� */
	PointZorder_Button,
	PointZorder_Flag,
	PointZorder_Max
};

const int maxStarNum = 3;						/* ����Ǽ� */
const int PointsPerBattle = 20;					/* ÿ��ս���ؿ��� */
const int PointIDStart = 1000;					/* �ؿ�ID 1000��ʼ */

typedef struct tagCellInfo
{
	int		station;							/* �ؿ�ID */
	int		stars;								/* �Ǽ� */
	int		model;								/* ģʽ 1: ��Ӣ�� */
	bool	isOn;								/* �Ƿ��� true: �� */
} CellInfo;