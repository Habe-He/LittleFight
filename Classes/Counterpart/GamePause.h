 /*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ����� GamePause
** ���ڣ�   2015:7:31
** ˵����	ս����ͣUI
** ������	
** ��ʷ��2015:7:31 ��ʼ�汾
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class GamePause : public cocos2d::Layer
{
public:
	GamePause(void);
	virtual ~GamePause(void);

	bool init();
	CREATE_FUNC(GamePause);

public:
	void loadPauseScene();											/* ������ͣ���� */
	void btnPauseClicked(cocos2d::Ref*, cocos2d::ui::TouchEventType);/* ��ͣ��ť�����Ϣ��Ӧ */
	void setEnabled(bool);

private:
	cocos2d::ui::Widget		*m_hUIPause;
};

