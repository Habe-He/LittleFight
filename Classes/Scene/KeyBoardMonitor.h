 /*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ����� KeyBoardMonitor
** ���ڣ�   2014:10:24
** ˵����	����������Ϣ
** ������	
** ��ʷ��2014:10:24 ��ʼ�汾
*********************************************************************/
#pragma once
#include "cocos2d.h"

class KeyBoardMonitor : public cocos2d::Layer
{
public:
	KeyBoardMonitor(void);
	virtual ~KeyBoardMonitor(void);

	virtual bool init();
	CREATE_FUNC(KeyBoardMonitor);

public:
	/* �ֻ��������� */
	void keyBoardListenEvent();

	/* �����ֻ����ؼ���Ӧ */
	void mobileRuturn(cocos2d::EventKeyboard::KeyCode, cocos2d::Event *);
};

