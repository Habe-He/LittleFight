/*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名： TrainCell
** 日期：   2014:10:9
** 说明：	练兵场列表单元
** 其它：	
** 历史：	2014:10:9 初始版本
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "DataManager/DataManager.h"
using namespace std;

class TrainCell : public cocos2d::Node
{
public:
	TrainCell(void);
	virtual ~TrainCell(void);

	bool init();
	CREATE_FUNC(TrainCell);

public:
	
	void setCellName(const char *name, const int starLevel);						// 设置单元项姓名 	
 	void setCellLevel(const int level);										// 设置单元项等级
	void setCurStar(const int star, const int maxStar);							// 设置当前星级和最大星级
	void setCellImage(const char *imgRoot, int maxStar);							// 设置人物头像
	void setCellGeneralIndex(int index);										// 设置索引值
	void setType(int type);												// 角色类型
	void setExp(int, int exp);												// 强化经验
	void setCellGeneralName(const char *name);								// 人物名称	
	void setCellUp(int id);												// 是否上阵
	int getCellUp();														// 是否上阵
	void setEquip(int index, int nameID);										// 武将装备

	int calcGeneralExp(int level, int exp);										// 计算武将当前剩余经验值

	cocos2d::ui::ImageView *image;											// 列表单元项图片	
	cocos2d::ui::ImageView *imageType;										// 列表单元项类型
	cocos2d::ui::ImageView *imageSelectSign;									// 以上阵的样式
	cocos2d::ui::LoadingBar *	progressBar;									// 经验条 
	cocos2d::ui::ImageView *imageWeapon[ 6 ];								// 装备图片
	cocos2d::ui::ImageView* typeImageView[ 3 ];								// 人物类型

	cocos2d::ui::ImageView *battle_Image;
	cocos2d::ui::ImageView *captain_Image;
	cocos2d::ui::Widget * trainCellUI;

private:
	cocos2d::ui::Text *txtName;											// 列表单元项姓名
	cocos2d::ui::Text* curStarLevel;										// 当前星级
	cocos2d::ui::Text *level_Label;										// 列表单元项等级

	int cellSelectFlag;
	int		m_hRole;
	std::string m_hRoleName;
	int		m_hRoleUp;
private:
	cocos2d::Point m_ptOriginleLoc;
	cocos2d::Point m_ptTouchLoc;

	vector<GeneralUpgradeStruct > localGeneralUpgradeVector;				// 武将技能升级规则
};

