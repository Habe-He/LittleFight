 /*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ����� MainFight
** ���ڣ�   2015:3:11
** ˵����	ս��������
** ������	
** ��ʷ��2015:3:11 ��ʼ�汾
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Counterpart_Def.h"
#include "Roles/Role/Role.h"

class MainFight : public cocos2d::Layer
{
public:
	MainFight(void);
	virtual ~MainFight(void);

	bool init();
	CREATE_FUNC(MainFight);

public:
	void setRoleHealthCtrl();										/* ���ý�ɫHP��MP��ʾ�ؼ� */
	void setRoleActButton();										/* ���ý�ɫ������ť */
	void resetActCD(int, float);									/* ���ö�������cd */
	void setButtonEventListener(cocos2d::Ref *, cocos2d::ui::SEL_TouchEvent );

protected:
	void loadMainFightScene();										/* ս��������� */
	void addRoleHelp(Role *);										/* ��Ӹ��� */

	void uiPanelClicked(cocos2d::Ref*, cocos2d::ui::TouchEventType);/* ҡ����Ϣ��Ӧ */

	void actionBtnClicked(cocos2d::Ref*, cocos2d::ui::TouchEventType);

private:
	cocos2d::ui::Widget		*m_hUIMain;
	cocos2d::ui::Button		*m_hBtnPause;

	int			m_iHelpNum;
};

