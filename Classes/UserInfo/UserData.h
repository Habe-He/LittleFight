/********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名： UserData
** 作者：   WangZho
** 日期：   2014:7:28
** 说明：	游戏公共数据内存读写。
** 其它：	
** 历史：	2014:7:28 初始版本
**			2014:8:7  取消m_szSaveFile，改为宏定义
/********************************************************************/
#pragma once
#include "cocos2d.h"
using namespace std;

class UserData : cocos2d::Ref
{
public:
	UserData(void);
	virtual ~UserData(void);

	static UserData *getInstance();
	void init();

	// 设置界面背景音乐和音效开关
	bool setupMusic;
	bool setupEffect;
	
public:
	void savaNewcomerGuide(int );							/* 设置新手指引进度 */
	int getNewcomerGuide();									/* 获取新手指引进度 */

	void setGuideStep(int step = 1);						/* 设置新手引导步骤 */
	int  getGuideStep();									/* 获取新手引导步骤 */	

	void saveMusicState();									// 设置音乐开关
	bool getMusicState();									// 获取音乐开关

	void saveEffectState();									// 设置音效开关
	bool getEffectState();									// 获取音效开关

	void saveDraw(int times);								/* 是否钻石第一次抽卡 */
	int getDraw();											/* 获取 */

	void saveUserName(string _userName);					// 保存玩家名称
	string getUserName();									// 获取玩家名称

	void saveUserPwd(string _userPwd);						// 保存玩家密码
	string getUserPwd();									// 获取玩家密码
		
	void saveDiamondDraw(int times);						/* 是否钻石十连抽第一次抽卡 */
	int getDiamondDraw();									/* 获取 */

	void addRole(cocos2d::Node *);							/* 添加角色 */
	void removeRole(cocos2d::Node *);						/* 移除角色 */
	void removeAllRoles();									/* 移除所有角色 */
	std::vector<cocos2d::Node *> getRoles();				/* 获取角色组 */
	void setRedRoleCount(int);								/* 设置我方武将数量 */
	void setBlackRoleCount(int, int = 0);					/* 设置敌方武将数量 */
	int	 getRedRoleCount();									/* 获取我方武将数量 */
	int  getBlackRoleCount(int);							/* 获取敌方武将数量 */
	int	 getBlackRoleTotalCount();							/* 获取敌方武将总数量 */
	void checkRedRolecount(bool = false);					/* 我方武将数量自增/减 */
	void checkBlackRolecount(int , bool = false);			/* 敌方武将数量自增/减 */

	void setBgRegion(cocos2d::Rect);						/* 设置当前背景图大小(即角色可移动区域) */
	cocos2d::Rect getBgRegion();							/* 获取当前背景图大小(即角色可移动区域) */

	void setBattleID(int);									/* 设置副本ID */
	int  getBattleID();										/* 获取副本ID */

	void setPointID(int);									/* 设置关卡ID */
	int  getPointID();										/* 获取关卡ID */

	void setFightDifficulty(int);							/* 设置副本难度 */
	int  getFightDifficulty();								/* 获取副本难度 */

	void setRoleCreateModel(int);							/* 设置角色创建模式 */
	int  getRoleCreateModel();								/* 获取角色创建模式 */

	void setPointMap(std::string);							/* 设置关卡地图 */
	std::string getPointMap();								/* 获取关卡地图 */

	void setCurrentPointStar(int);							/* 设置当前关卡获得的星级 */
	int  getCurrentPointStar();								/* 获取当前关卡获得的星级 */

	void setJxxg3Grade(int);								/* 设置稷下学宫模式3的成绩 */
	int  getJxxg3Grade();									/* 获取稷下学宫模式3的成绩 */

	void setJxxg4Grade(int);								/* 设置稷下学宫模式4的成绩 */
	int  getJxxg4Grade();									/* 获取稷下学宫模式4的成绩 */

	void setPvpPlayerID(int);								/* 设置竞技场选中对手ID */
	int  getPvpPlayerID();									/* 获取竞技场选中对手ID */

	void setBattleSVPercent(float);							/* 设置副本滚动层进度 */
	float getBattleSVPercent();								/* 获取副本滚动层进度 */

	void setPointLive(int life = 1);						/* 设置关卡复活次数 */
	int  getPointLive();									/* 获取关卡复活次数 */

	int numOfWeaponLocation;
protected:
	void setUserData();										/* 初始化游戏存储数据 */

private:
	cocos2d::Rect			m_rcBgRegion;					/* 当前背景图大小(即角色可移动区域) */

	std::vector<cocos2d::Node *>	m_vctRoles;				/* 角色组 */
	std::string				m_strPointMap;					/* 关卡地图 */

	int	 m_iRedRoleCount;									/* 我方武将数量 */
	std::vector<int>  m_iBlackRoleCount;					/* 敌方武将数量 */
	int  m_iBattleID;										/* 副本ID */
	int  m_iPointID;										/* 关卡ID */
	int  m_iFightDifficulty;								/* 副本难度 */
	int	 m_iRoleCreModel;									/* 角色创建模式 */
	int	 m_iCurPointStar;									/* 当前关卡获得的星级 */
	int	 m_iJxxg3Grade;										/* 稷下学宫模式3的成绩 */
	int	 m_iJxxg4Grade;										/* 稷下学宫模式4的成绩 */
	int	 m_iPvpPlayerID;									/* 竞技场选中对手ID */
	float  m_fBattleSVPercent;								/* 副本滚动层进度 */
	int	 m_iLife;											/* 关卡复活次数 */
};