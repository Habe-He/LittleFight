/*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ�����   EffectAction
** ��  �ڣ�   2015:5:22
** ˵  ����	��Ч�ࣨ�ر��ۣ�
** ��  ����	
** ��  ʷ��	2015:5:22 ��ʼ�汾
*********************************************************************/
#pragma once
#include "cocos2d.h"
USING_NS_CC;

class EffectAction : public Node
{
public:
	static EffectAction* getInstance();

	void unLockAnim();				// �ֿ����

	void loadingEffect();				// ����

	void buttonBack();				// �����湦�ܰ�ť

	void drawoffEffect();				// �鿨��ʾ��Ч

	void fbEffect();					// �����渱����Ч

	void tieEffect();					// �����渱����Ч

	void trainEffect();				// ����������Ч

	void callBack();

	void waitSignInEffect();      // �� ǩ������
};