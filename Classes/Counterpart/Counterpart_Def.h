 /*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ����� Counterpart_Def
** ���ڣ�   2014:11:14
** ˵����	���������ݡ����ݽṹ����
** ������	
** ��ʷ��2014:11:14 ��ʼ�汾
*********************************************************************/
#pragma once
#include "cocos2d.h"

/***********************UI����ؼ� Begin***************************/
enum MFControl
{
	MFCtrl_Sa,
	MFCtrl_Sb,
	MFCtrl_Sc,
	MFCtrl_Sd,
	MFCtrl_Pause,
	MFCtrl_MainHP,							/* ��HP������ */
	MFCtrl_SubHP,							/* ��HP������ */
	MFCtrl_Health,							/* ����ͷ��� */
	MFCtrl_Max
};

enum PauseControl
{
	PCtrl_Quit,								/* �˳� */
	PCtrl_Resume,							/* �ص�ս�� */
	PCtrl_Restart,							/* ���¿�ʼ */
	PCtrl_Max
};

const int DefSceneNum = 2;							/* ÿ���ؿ������� */
const int CmdSign[14] = {'e','d','s','f','r','v','w','x','j','u','i','o','p','q'};
/* �ϡ��¡����ҡ����ϡ����¡����ϡ����¡�����������1������2������3������4����ť���� */
const float UNIT_WIDTH = 55.0f;						/* С���ͼ������ */
const float GameResultAniDuration = 2.5f;			/* ս������ʱ�䡢���鶯��ʱ�� */
const cocos2d::Point ptActDir = cocos2d::Point(104, 88);/* ���������� */

enum CounterpartOrder
{
	order_Bkg = 0,
	order_Role = 500,
	order_MainFight = 1000,
	order_Pause,
	order_Result,
	order_Max
};