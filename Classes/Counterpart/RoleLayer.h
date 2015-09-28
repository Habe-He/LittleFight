 /*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名： RoleLayer
** 日期：   2015:3:24
** 说明：	副本角色层
** 其它：	
** 历史：2015:3:24 初始版本
*********************************************************************/
#pragma once
#include "cocos2d.h"

const float fDoubleClickDuration = 0.5f;	/* 双击延时 */

class RoleLayer : public cocos2d::Layer
{
public:
	RoleLayer(void);
	virtual ~RoleLayer(void);

	CREATE_FUNC(RoleLayer);
	virtual bool init();

public:
	void loadRedRole();
	void loadBlackRole();
	void loadBackground();
	void initRolesTalent();
	cocos2d::Sprite *getPointMap();									/* 获取背景图 */

protected:
	void loadNormalBlackRole();										/* 加载普通关卡角色 */
	void loadJiXiaBlackRole();										/* 加载稷下学宫角色 */
	void loadPvpBlackRole();										/* 加载稷下学宫角色 */
	
private:
	cocos2d::Sprite *m_spBg;										/* 背景资源 */
};

