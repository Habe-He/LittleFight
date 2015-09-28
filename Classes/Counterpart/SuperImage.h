 /*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名： SuperImage
** 日期：   2015:4:27
** 说明：	角色头像、hp显示、操作按钮cd显示
** 其它：	
** 历史：2015:4:27 初始版本
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Roles/Role/Role.h"

enum SpImgModeSign
{
	SpImgMode_Major = 0,		/* 主将、敌兵HP显示层 */
	SpImgMode_Help,				/* 小伙伴HP显示层 */
	SpImgMode_Skill,			/* 技能CD显示层 */
	SpImgMode_Max
};

class SuperImage : public cocos2d::Node
{
public:
	SuperImage(void);
	virtual ~SuperImage(void);

	static SuperImage* Create(SpImgModeSign);
	bool init(SpImgModeSign);

	CREATE_FUNC(SuperImage);
	bool init();

public:	
	void createClipper(std::string , std::string , float  = 1.0f);	/* 创建裁剪模板图 */
	void setProgressBar(cocos2d::ui::LoadingBar *, cocos2d::ui::LoadingBar *);
	void setProgressBar(std::string, std::string = "", float = 1.0f);
	void resetOwner(Role *);										/* 切换角色 */

	/* 动作CD */
	void setProgressDuration(float);								/* cd设置 */
	void runSpriteProgressToRadial(float = 100, int = 1);			/*  */

protected:
	void update(float);
	void progressCDOver(cocos2d::Node*);
	void showActionCD();

private:
	Role *_owner;

	cocos2d::ui::LoadingBar *_mainHp;								/* 主hp进度条 */
	cocos2d::ui::LoadingBar *_subHp;								/* 副hp进度条 */
	cocos2d::ProgressTimer	*_proTimer;								/* 小伙伴hp/CD显示 */
	cocos2d::Sprite			*_spClip;								/* 被遮罩的图片 */
	cocos2d::Label			*_label;								/* 显示cd */

	float	_cd;													/* cd设置 */
	bool	_bGrayFlag;												/* 头像被置灰标记 */
};

