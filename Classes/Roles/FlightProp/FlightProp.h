 /*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名： FlightProp
** 日期：   2015:1:24
** 说明：	飞行道具(箭、魔法球等)
** 其它：	
** 历史：2015:1:24 初始版本
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "Roles/Role/Role.h"
#include "UserInfo/UserData.h"

const int	iActionSeqTag = 1000;			/* 箭移动动作Tag */
/* 攻击次数、每次延时，效果（倒地、异常状态等）、击退距离 */
typedef struct tagFlightPropInfo
{
	int				num;					/* 资源图数量 */
	float			dur;					/* 资源图播放时间间隔 */
	float			reserve;				/* 预留 */
	SkillInfo		skillInfo;				/* 道具技能属性 */
} FlightPropInfo;

typedef struct _tagRoleRes
{
	std::string strPath;					/* 道具资源路径 */
	cocos2d::Point	ptOffset;				/* 道具初始偏移坐标 */
	int		iImgNum;						/* 道具资源数量 */
} RoleFlightProp;

class FlightProp : public cocos2d::Sprite
{
public:
	FlightProp();
	virtual ~FlightProp(void);
	
	virtual void runPropCollisionDetective(float, cocos2d::Point);	/* 道具移动及开启碰撞检测 */
	virtual void setPropFlag(bool = true, float = 0.05f);			/* 设置标志为倒地 */
	void setPropPosition(Point);									/* 设置坐标 */
	void releaseCallBack();											/* 销毁 */
	void releaseWithDelay(float);

protected:
	void InitParam(Role *, FlightPropInfo, std::string);			/* 初始化成员参数 */
	virtual void PropCollisionDetective(float);						/* 碰撞检测 */

	std::string	getImgSuffix();										/* 获取资源图名称后缀 */
	void imgAnimation();											/* 图片动画 */

	Role			*_owner;										/* 技能释放者 */
	
protected:
	FlightPropInfo	m_stPropInfo;									/* 道具信息 */
	cocos2d::Rect	m_rcBgRegion;									/* 当前背景图大小(即角色可移动区域) */

	bool			m_bDown;										/* 攻击到对方时是否倒地 */
	float			m_fStay;										/* 箭攻击到目标或达到射程后延时消失时间 */
	float			m_fHeight;										/* 高度 */

	std::string		m_strImg;										/* 图片资源路径 */
};