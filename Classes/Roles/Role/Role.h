/*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名： Role
** 日期：   2014:9:18
** 说明：	角色基类，定义角色基本行为等
** 其它：	
** 历史：	2014:9:18 初始版本
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "Role_Def.h"
#include "UserInfo/UserData.h"
#include "Public/ToolFunc.h"

class Role : public cocos2d::Node
{
public:
	Role();
	virtual ~Role(void);
	
public:
	virtual bool init(std::string, RoleCreMode, float);				/* 初始化角色变量 */

public:
	bool runRoleAction(RoleActSign);								/* 动作接口 */ 
	bool runLordlAction(RoleCmdSign,cocos2d::Point = ptInvalid);	/* 主将执行技能动作 */

	void initRoleInfo(RoleCamp, RoleMode, RoleRace);				/* 初始化角色信息 */
	virtual void initTalentEffect();								/* 设置天赋buff */
	void setRoleInfo(RoleInfo);										/* 设置角色信息 */
	void setRoleBuff(RoleBuff);										/* 设置角色buff */
	void setRolePanel(RolePanel);									/* 角色属性设置 */
	void setRoleSkillInfo(SkillInfo*);								/* 角色技能属性 */
	void setRoleHpUp(int);											/* hp恢复 */
	void setRoleCondition(RoleCondition, float);					/* 异常状态设置 */
	void setRoleAbnormalDamage(int , float);						/* 异常状态伤害 */
	void setActionCD(RoleActSign, float = 0);						/* 重置角色动作cd */
	void setRolePkID(int);											/* 武将主键ID */
	int  getRolePkID();												/* 武将主键ID */
	void setRoleID(int);											/* 武将ID */
	int  getRoleID();												/* 武将ID */
	RoleInfo getRoleInfo();											/* 角色信息获取 */
	RoleBuff getRoleBuff();											/* 获取角色buff */
	SkillInfo* getRoleSkillInfo();									/* 获取角色技能数据 */
	void resetUISkillBtnCD();										/* 重置界面技能按钮设置的cd */
	void setAnimateSpeed(float);									/* 设置动画速率 */
	void backToLife();												/* 复活 */
	void setHealthCtrl(cocos2d::Node *);							/* 设置角色HP、MP显示控件 */
	void removeHealthCtrl();										/* 移除角色HP、MP显示控件 */

	virtual int roleHurt(Role*, SkillInfo, bool);

protected:
	virtual void loadArmature();									/* 加载动画资源 */
	void initHealthBar();											/* 初始化角色生命显示条 */
	void initSubInfo();												/* 设置角色副属性 */
	void initActAiLimit();											/* 设置Ai行为的概率 */
	void initSkillRegion();											/* 设置角色技能属性 */
	void initSkillGains();											/* 设置技能等级的属性增益 */
	void initJxxgBuff();											/* 初始化稷下学宫buff */
	virtual void setAiActionSequence();								/* 设置Ai攻击序列 */
	virtual void initActInherent();									/* 初始化角色技能属性 */
	virtual void initFlightPropInfo();								/* 初始化技能飞行道具 */

	virtual void aiActSequenceSoldier();							/* 杂鱼Ai攻击序列 */
	virtual void aiActSequenceCompanion();							/* 小伙伴Ai攻击序列 */
	virtual void aiActSequenceBoss();								/* Boss Ai攻击序列 */
	virtual void aiActSequenceMain();								/* 主将 Ai攻击序列 */
	
	std::string getFrameEventName(RoleFrameEvent);					/* 获取动画事件名称 */
	std::string getFlightPropPath();								/* 获取飞行道具资源路径 */
	unsigned int playEffectOgg(const char* , bool = false,
		float = 1.0f, float = 0.0f, float = 1.0f);					/* 播放音效 */
	bool isRoleLearnedTalent(RoleTalent);							/* 角色是否习得天赋 */
	void warMsgDecision();											/* 战局消息决策 */
	void passRoomByAuto();											/* 自动过图 */
	void shaky();													/* 抖动 */
	void playAureoleEffect();										/* 脚底光环特效 */
	void playHitEffect();											/* 被击特效 */
	void hitEffectCB(cocos2d::Node*);
	void deathEffect();												/* 死亡特效 */
	void deathEffectCB(cocos2d::Node*);
	void addTrail(int );
	void removeTrail(cocos2d::Node*);

	virtual void roleCollisionDetective(bool);						/* 执行碰撞检测 */

	bool runArmatureAction(RoleActSign);							/* 执行动作 */
	void stopArmatureAction();										/* 停止动作 */
	bool checkAnimateExistByName(const std::string);				/* 根据名称检测动作存在否 */
	void setRoleTurnedDirInfo(RoleDirSign);							/* 设置角色转身方向信息 */
	void setRoleTurnedDirInfo(float);								/* 设置角色转身方向信息 */

	virtual void movement(const std::string&, cocostudio::MovementEventType, float);
	virtual void movement(const std::string&);						/* 动作时消息响应 */
	virtual void frameEvent(const std::string&);					/* 动作时帧事件 */

	virtual void onEnter();
	virtual void onExit();
	void update(float);
	virtual void updateRole();										/* 刷新 */

	virtual void hpReture(float);									/* hp回复 */
	void actionCDFlag(float);										/* CD计时 */

	void roleSchedule(float , RoleScheduleType);					/* 计时器 */
	void roleUnSchedule(RoleScheduleType);

	void comboResume(float);										/* 连击标记复位 */
	void conditionResume(float);									/* 异常状态恢复 */
	void aiActionResume(float);										/* AI行为重置 */
	void abnormalResume(float);										/* 异常伤害重置 */
	void buffShieldResume(float);									/* 护盾消失 */
	void buffHpBack(float);											/* hp恢复天赋 */
	void buffHarmGrow(float);										/* 迫在眉睫天赋 */
	void buffDenfendLResume(float);									/* 减防负buff复位 */
	void checkRoleInBgRegion();										/* 确保角色不移动到背景区域外 */
	void makeRoleMoving(float);										/* 移动角色 */
	void downResume(float);											/* 取消倒地 */
	void flashEffect();												/* 角色闪烁特效 */
	void flashEffectCallBack();										/* 倒地起身后，状态恢复正常 */
	virtual void deathEffectCallBack();								/* 死亡后回调 */
	void smittenResume(float);										/* 受击恢复 */
	void shakyCallBack(cocos2d::Node*);								/* 抖动结束 */

	/* 动作执行 Begin */
	virtual	bool runActionAtkCtrl();
	virtual	bool runActionIdle();
	virtual	bool runActionMove();
	virtual bool runActionAttack();
	virtual bool runActionTwiceAtk();
	virtual bool runActionThriceAtk();
	virtual	bool runActionSmitten();
	virtual	bool runActionDown();
	virtual	bool runActionDeath();
	virtual bool runActionSkillOne();
	virtual bool runActionSkillTwo();
	virtual bool runActionSkillThree();
	virtual bool runActionSkillFour();
	/* 动作执行 End */

	virtual float getExtraHarm(Role*);								/* 计算伤害加成 */
	virtual void talentEffect(Role*, float);						/* 天赋效应 */
	void setRoleHitAction(int , bool);								/* 角色被击时动作 */
	void showRoleHealthChange(int);									/* hp变化label */
	void hpLabelCallBack(cocos2d::Node *);							/* 扣血显示label回调函数 */
	
	/* AI */
	virtual void runRoleAI();
	void runRoleMainAI();
	void roleAiStep();												/* Ai行为选择 */
	void roleAiPursuit(cocos2d::Point);								/* Ai行为追击 */
	void roleAiShortMove();											/* Ai行为短距离移动 */
	void roleAiSleep();												/* Ai行为休眠 */

	/* AI辅助函数 Begin */
	bool checkAIAviable();											/* 判断AI有效性 */
	void calcuRoleDangerSignValue(bool *, float *);					/* 计算角色是否有危险 */
	void setMoveVector(cocos2d::Point);								/* 获取移动方向 */
	bool checkRoleCanBeHit(cocos2d::Point);							/* 判断指定角色是否在攻击范围 */
	Role* getNearestRole();											/* 获取最近的角色 */
	cocos2d::Rect getRectByTwoPoint(cocos2d::Point, cocos2d::Point);/* 以两个定点构造矩形 */
	cocos2d::Rect getRectBySize(cocos2d::Size);						/* 以自身位置和范围构造矩形 */
	/* AI辅助函数 End */

protected:
	int				m_iRolePkID;									/* 武将主键ID */
	int				m_iRoleID;										/* 武将ID */
	float			m_fResScale;									/* 资源缩放比例 */
	float			m_fActCD[RoleAct_Max];							/* cd计时 */
	bool			m_bRoleActBreak;								/* 动作中断标记 */
	RoleInfo		m_stRoleInfo;
	RoleBuff		m_stRoleBuff;									/* 天赋buff */
	SkillInfo		m_stSkillInfo[RoleAct_Max];
	RoleSubInfo		m_stRoleSubInfo;
	RoleCreMode		m_eRoleCreMode;									/* 角色创建模式 */
	RoleActMode		m_stActMode[RoleAct_Max];						/* 角色技能属性 */
	RoleActAiSign	m_eRoleActAi;									/* 角色Ai行为 */
	cocos2d::Node	*m_nAureoleEffect;								/* 角色光环特效 */
	std::vector<RoleActSign>		m_vctAiActSeq;					/* Ai攻击序列 */

	float			m_fActAiLimit[RoleActAi_Max];					/* 角色Ai，动作选择概率 */

	CC_SYNTHESIZE(std::string, m_strRoleName, StrRoleName);			/* 角色名字 */
	CC_SYNTHESIZE(RoleWarMsg, m_eRoleWarMsg, RoleWarMsg);			/* 可通过标记（敌人全清） */
	CC_SYNTHESIZE(int, m_iSceneID, SceneID);						/* 角色区域ID */
	CC_SYNTHESIZE(int, m_iRoleStarLv, StarLv);						/* 武将 星级 */
	CC_SYNTHESIZE(cocos2d::Rect, m_rcRegion, MoveRegion);			/* 移动区域 */
	CC_SYNTHESIZE(bool, m_bShadow, ShadowFlag);						/* 分身标记 */
	CC_SYNTHESIZE(int, m_iShadowOwner, ShadowOwner);				/* 分身本尊(以PKID标记) */

private:
	cocos2d::Point		m_ptMoveDir;								/* 移动向量 */
	cocos2d::Point		m_ptMoveDes;								/* 主将移动目的地 */
	cocos2d::Node		*m_nHealth;									/* 角色HP、MP显示控件 */

	cocos2d::ProgressTimer	*_roleHealth;							/* 角色生命值 */

	RoleHealthSign		m_ehealthSign;								/* hp变化类型 */

	unsigned int		m_iAiActSeqIndex;							/* 当前执行Ai攻击序列的索引 */
	int					m_iRoleCombo;								/* 普攻连击动作状态 */
};