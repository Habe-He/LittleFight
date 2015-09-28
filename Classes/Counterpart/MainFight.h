 /*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名： MainFight
** 日期：   2015:3:11
** 说明：	战斗主界面
** 其它：	
** 历史：2015:3:11 初始版本
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
	void setRoleHealthCtrl();										/* 设置角色HP、MP显示控件 */
	void setRoleActButton();										/* 设置角色攻击按钮 */
	void resetActCD(int, float);									/* 重置动作技能cd */
	void setButtonEventListener(cocos2d::Ref *, cocos2d::ui::SEL_TouchEvent );

protected:
	void loadMainFightScene();										/* 战斗界面加载 */
	void addRoleHelp(Role *);										/* 添加副将 */

	void uiPanelClicked(cocos2d::Ref*, cocos2d::ui::TouchEventType);/* 摇杆消息响应 */

	void actionBtnClicked(cocos2d::Ref*, cocos2d::ui::TouchEventType);

private:
	cocos2d::ui::Widget		*m_hUIMain;
	cocos2d::ui::Button		*m_hBtnPause;

	int			m_iHelpNum;
};

