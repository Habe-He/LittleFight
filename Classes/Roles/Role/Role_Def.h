#pragma once
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

const int maxActAiLimit = 1000;					/* 随机数最大值 */
const int minActAiLimit = 1;					/* 随机数最小值 */
const int DamageOffset = 50;					/* 伤害浮动率 */
const int MoveSpeed = 130;						/* 移动速度单位 */
const int iRegionLimit = 30;					/* 可移动区域左右边界 */
const float ResourceScale = 0.7f;				/* 资源缩放比例 */
const float ComboDuration = 0.2f;				/* 默认连击标记重置时间 */
const float HealthRetRate = 1.0f;				/* hp mp回复频率 */
const float InvincibleDelay = 0.5f;				/* 无敌时间 */
const float DownDelay = 0.6f;					/* 倒地时间 */
const float ConfusionDuration = 8.0f;			/* 混乱持续时间8s */
const float FrozenDuration = 5.0f;				/* 冰冻持续时间8s */
const float	SleepDuration = 2.5f;				/* 最长休眠延时 */
const float MoveDuration = 2.0f;				/* 最长漫游时间 */
const float DirDuration = 0.5f;					/* 移动方向变化CD */
const float SceneWidth = 800.0f;				/* 场景图宽度 */
const cocos2d::Point ptAtkOffset = cocos2d::Point(10, 0); /* 攻击时，角色略向前移动 */
const cocos2d::Point ptInvalid = cocos2d::Point(-1, -1); /* 无效点 */

/* 角色创建模式 */
enum RoleCreMode
{
	RoleCreMode_Preview = 0,					/* 武将详情界面预览模式 */
	RoleCreMode_Fighting,						/* 角色上阵模式 */
	RoleCreMode_XueGong1,						/* 稷下学宫：群体buff */
	RoleCreMode_XueGong2,						/* 稷下学宫：战队经验buff */
	RoleCreMode_XueGong3,						/* 稷下学宫：武将经验buff */
	RoleCreMode_XueGong4,						/* 稷下学宫：材料装备 */
	RoleCreMode_Max
};

/* 动画帧事件 */
enum RoleFrameEvent
{
	FrameEvent_Begin = 0,						/* 动作准备完毕（开始霸体） */
	FrameEvent_End,								/* 动作开始收招（结束霸体） */
	FrameEvent_Attack,							/* 攻击事件（不倒地） */
	FrameEvent_Attack_FD,						/* 攻击事件（倒地） */
	FrameEvent_Shot,							/* 发射事件（不倒地） */
	FrameEvent_Shot_FD,							/* 发射事件（倒地） */
	FrameEvent_Invincible,						/* 无敌事件 */
	FrameEvent_Break,							/* 中断动作事件 */
	FrameEvent_Left,							/* 攻击方向: 前 */
	FrameEvent_Middle,							/* 攻击方向: 前后双方 */
	FrameEvent_Right,							/* 攻击方向: 后 */
	FrameEvent_Max
};

/* AI行为类型 */
enum RoleActAiSign
{
	RoleActAi_None = 0,							/* 无行为 */
	RoleActAi_Pursuit,							/* 追击 */
	RoleActAi_ShortMove,						/* 短距离移动 */
	RoleActAi_Sleep,							/* 休眠 */
	RoleActAi_Max
};

/* 角色类型 */
enum RoleMode
{
	RoleMode_Main = 0,							/* 主将 */
	RoleMode_Soldier,							/* 杂鱼 */
	RoleMode_Companion,							/* 小伙伴 */
	RoleMode_Boss,								/* boss */
	RoleMode_Max
};

const float roleActAiLimit[RoleMode_Max][RoleActAi_Max] = {
	{ 0, 734, 952, 1000 },						/* 主将 */
	{ 0, 250, 700, 1000 },						/* 杂鱼 */
	{ 0, 657, 900, 1000 },						/* 小伙伴 */
	{ 0, 763, 950, 1000 },						/* boss */
};

/** 角色动作定义 **/
enum RoleActSign
{
	RoleAct_Idle = 0,							/* 0：待机 */
	RoleAct_Attack,								/* 1：普通一连击 */
	RoleAct_Twice_Atk,							/* 2：普通二连击 */
	RoleAct_Thrice_Atk,							/* 3：普通三连击 */
	RoleAct_Move,								/* 4：移动 */
	RoleAct_SkillOne,							/* 5：技能一 */
	RoleAct_SkillTwo,							/* 6：技能二 */
	RoleAct_SkillThree,							/* 7：技能三 */
	RoleAct_SkillFour,							/* 8：技能四 */
	RoleAct_Smitten,							/* 9：被击 */
	RoleAct_Down,								/* 10：倒地 */
	RoleAct_Death,								/* 11：死亡 */
	RoleAct_Max
};

/** 技能操作指令定义 **/
enum RoleCmdSign
{
	RoleCmdSign_Move,					/* 移动 */
	RoleCmdSign_Attack,					/* 攻击 */
	RoleCmdSign_SkillOne,				/* 技能一 */
	RoleCmdSign_SkillTwo,				/* 技能二 */
	RoleCmdSign_SkillThree,				/* 技能三 */
	RoleCmdSign_SkillFour,				/* 技能四 */
	RoleCmdSign_Release,				/* 按钮弹起 */
	RoleCmdSign_Max
};

/** 角色状态定义 **/
enum RoleStatus
{
	RoleStatus_Normal = 0,
	RoleStatus_Invincible,						/* 无敌 */
	RoleStatus_Superarmor,						/* 霸体 */
	RoleStatus_Death,							/* 死亡 */
	RoleStatus_Max
};

/** 异常状态定义 **/
enum RoleCondition
{
	RoleCondition_Normal = 0,					/* 正常 */
	//RoleCondition_Poisoning,					/* 中毒 */
	//RoleCondition_Bleeding,					/* 出血 */
	//RoleCondition_Fixed,						/* 禁锢 */
	RoleCondition_Confusion,					/* 混乱 */
	RoleCondition_Frozen,						/* 冰冻 */
	RoleCondition_Max
};

/** 敌我定义 **/
enum RoleCamp
{
	RoleCamp_Normal = 0,
	RoleCamp_Red,								/* 我军 */
	RoleCamp_Black,								/* 敌军 */
	RoleCamp_Max
};

/*  标记左右方向 */
enum RoleDirSign
{
	RoleDir_Right = -1,							/* 正方向 */
	RoleDir_Middle = 0,
	RoleDir_Left = 1,							/* 反方向 */
	RoleDir_Max
};

/* 角色职业 */
enum RoleRace
{
	RoleRace_Power = 1,							/* 力量 */
	RoleRace_Wizard,							/* 智力 */
	RoleRace_Speed,								/* 敏捷 */
	RoleRace_Max
};

/* 技能物魔属性 */
enum RoleActMode
{
	RoleActMode_Normal = 0,						/* 普通 */
	RoleActMode_Physical,						/* 物理攻击 */
	RoleActMode_Magic,							/* 魔法攻击 */
	RoleActMode_Super,							/* 对敌攻击，对己补血 */
	RoleActMode_Control,						/* 控场技能(孙膑骷髅头等) */
	RoleActMode_Guard,							/* 防御技能(田单火焰等) */
	RoleActMode_Max
};

/** 角色计时器类型 **/
enum RoleScheduleType
{
	RoleSchedule_Combo = 0,						/* 动作记录计时器 */
	RoleSchedule_Condition,						/* 异状态计时器 */
	RoleSchedule_AiAction,						/* Ai行为计时器 */
	RoleSchedule_Abnormal,						/* 异常状态伤害 */
	RoleSchedule_Shield,						/* 护盾计时器 */
	RoleSchedule_HpReturn,						/* hp恢复计时器 */
	RoleSchedule_Max
};

/** 角色hp变化显示 **/
enum RoleHealthSign
{
	RoleHealth_RedNormal = 0,					/* 己方普通伤害 */
	RoleHealth_OppNormal,						/* 对方普通伤害 */
	RoleHealth_Critical,						/* 暴击伤害 */
	RoleHealth_Up,								/* 回血 */
	RoleHealth_Max
};

/** 角色天赋 **/
enum RoleTalent
{
	RoleTalent_ShiHua = 1,						/* 0石化：增加4%的物理防御和法术防御 */
	RoleTalent_FuSuZhiFeng,						/* 1复苏之风：增加12点每秒的血量回复 */
	RoleTalent_GeDang,							/* 2格挡：减少来自敌方的伤害 */
	RoleTalent_XueYeFeiTeng,					/* 3血液沸腾：生命值最大值提升6% */
	RoleTalent_NengLiangHua,					/* 4能量化：使用技能时额外获得生命值为3%的护盾，持续7秒 */
	RoleTalent_JuRen,							/* 5巨人：上场力量系武将伤害增加8% */
	RoleTalent_QianFeng,						/* 6前锋：自身攻击力增加4% */
	RoleTalent_ZhengMianDuiJue,					/* 7正面对决：对敏捷系的敌人造成伤害提高6% */
	RoleTalent_ZhanSha,							/* 8斩杀：击杀一个敌方单位后回复8%血量 */
	RoleTalent_PoZaiMeiJie,						/* 9迫在眉睫：每当战斗时间过去20秒，提高1.5%的伤害 */
	RoleTalent_LiLiangBaoFa,					/* 10力量爆发：增加75点攻击力 */
	RoleTalent_FuWenHuDun,						/* 11符文护盾：进入战场时获得生命值10%的护盾 */
	RoleTalent_PoMoZhiRen,						/* 12破魔之刃：上场敏捷系武将伤害增加4% */
	RoleTalent_DunQiang,						/* 13盾墙：敌方造成的伤害减少5% */
	RoleTalent_WuShiLieRen,						/* 14巫师猎人：对智力系的敌人造成伤害提高6% */
	RoleTalent_XiXueXiXing,						/* 15吸血习性：普通攻击的6%转化为生命值 */
	RoleTalent_KuangNu,							/* 16狂怒：自身增加攻击力5% */
	RoleTalent_GongFaJianBei,					/* 17功法兼备：上场智力系武将攻击增加3% */
	RoleTalent_CaoYaoZhuanJia,					/* 18草药专家：每25秒给队伍中血量最少的队友回复7.5%的血量 */
	RoleTalent_ZhiYu,							/* 19治愈：回血速度提高1% */
	RoleTalent_GangJingJiSha,					/* 20干净击杀：当一名敌人被技能击中并致死时，技能cd清零 */
	RoleTalent_YinMouJia,						/* 21阴谋家：对力量系的敌人造成伤害提高6% */
	/* 以下五星武将天赋 */
	RoleTalent_JingGangHuTi,					/* 李牧：金刚护体：每次承受的攻击伤害减少8% */
	RoleTalent_KuangBao,						/* 吴起：狂暴：普通攻击输出增加8% */
	RoleTalent_PoJia,							/* 吴孟瑶：破甲：普通攻击降低15%的护甲值，持续2秒. */
	RoleTalent_ShiXue,							/* 田忌：嗜血：武将血量高于80%，伤害提高12% */
	RoleTalent_ZhiSi,							/* 荆轲：致死：当敌方血量少于25%时，对其造成的伤害增加15% */
	RoleTalent_JianGuFangYu,					/* 廉颇：坚固防御：增加全队武将5%物理防御和5%法术防御 */
	RoleTalent_XueMoFa,							/* 商鞅：血魔法：攻击时，可恢复伤害的8%的生命值 */
	RoleTalent_ZhangKongZhanChang,				/* 扁鹊：掌控战场：血量低于35%时，攻击额外增加8%，治疗量提高8% */
	RoleTalent_JueShiLiShao,					/* 屈原：绝世离骚：攻击潜力提高5点，血量潜力提高25点 */
	RoleTalent_YaZhi,							/* 孙膑：压制：自身血量高于目标时，造成伤害提高15% */
	RoleTalent_MoNvMiXing,						/* 钟无艳：魔女迷行：物理伤害的8%伤害量吸收成为你的血量 */
	RoleTalent_ShuangRenJian,					/* 白起：双刃剑：造成的伤害提高20%，受到的伤害提高10% */
	RoleTalent_ZhongXingWuQi,					/* 项燕：重型武器：暴击率增加15%，暴击伤害提高20% */
	RoleTalent_BingJiaZhiZhu,					/* 孙武：兵家之主：每存活一名队友，增加自身3%的攻击力，3%的法术防御和护甲 */
	RoleTalent_JiLi,							/* 孙叔敖：激励：技能冷却时间减少15% */
	RoleTalent_TongShuai,						/* 田文：统帅：成为主将后，自身伤害提高50% */
	RoleTalent_BenNeng,							/* 魏无忌：本能：全体攻击伤害增加5% */
	RoleTalent_XueSeJieXian,					/* 赵胜：血色界限：我方武将全体血量上限增加5% */
	RoleTalent_WenDingJieJie,					/* 黄歇：稳定结界：降低全体敌方15%物理防御和15%法术防御 */
	RoleTalent_Max
};

/** 战局消息 **/
enum RoleWarMsg
{
	RoleWarMsg_None = 0,						/* 无 */
	RoleWarMsg_Pause,							/* 暂停 */
	RoleWarMsg_Pass,							/* 过图 */
	RoleWarMsg_Over,							/* 结束 */
	RoleWarMsg_Max
};

#define CREATE_ROLE_FUNC(__TYPE__) \
	static __TYPE__* create(std::string strName, RoleCreMode mode, float resScale = ResourceScale) \
	{ \
		__TYPE__ *pRet = new __TYPE__(); \
		if ((NULL != pRet) && (true == pRet->init(strName, mode, resScale))) \
		{ \
			pRet->autorelease(); \
			return pRet; \
		} \
		delete pRet; \
		pRet = NULL; \
		return NULL; \
	}

/** 角色技能属性结构 **/
typedef struct tagSkillInfo
{
	int		level;								/* 技能等级 */
	float	cd;									/* cd */
	float	damage;								/* 伤害 */
	float	damageAddition;						/* 附加伤害 */
	float	xAtkDis;							/* 水平向攻击距离 */
	float	yAtkDis;							/* 里外向攻击距离 */
	char	name[20];							/* 技能攻击次数 */
	RoleActMode	model;						/* 性质 */
} SkillInfo, *pSkillInfo;

/* 角色副属性 */
typedef struct tagRoleSubInfo
{
	float				speed;					/* 走动速度 */
	RoleDirSign			side;					/* 标记正反朝向 */
	RoleDirSign			atkSide;				/* 攻击方向 */
	RoleDirSign			hitSide;				/* 受击方向 */
	cocos2d::Point		anchorPoint;			/* 锚点 */
} RoleSubInfo, *pRoleSubInfo;

/** 人物属性 **/
typedef struct tagRolePanel						/* 人物属性 */
{
	int		hpTotal;							/* 总生命值 */
	int		hpCurrent;							/* 当前生命值 */
	int		atk;								/* 攻击力 */
	int		realAtk;							/* 真实伤害 */
	int		realAtkDefend;						/* 真实伤害抗性 */
	int		pDefend;							/* 物理防御 */
	int		mDefend;							/* 法术防御 */
	float	critical;							/* 暴击 */
	float	criDefend;							/* 暴击抗性 */
	float	criExtra;							/* 暴击伤害加成 */
	int		level;								/* 等级 */
	/* 以下是全程buff */
	int		hpBack;								/* hp回复率 */
	float	allHarm;							/* 对所有伤害加成（百分比） */
	float	wizardHarm;							/* 对智力型伤害加成（百分比） */
	float	speedHarm;							/* 对敏捷型伤害加成（百分比） */
	float	powerHarm;							/* 对力量型伤害加成（百分比） */
	float	lowerHarm;							/* 免伤率 */
	int		shield;								/* 护盾 */
	int		talent;								/* 角色天赋 */
	int		pDefendL;							/* 降低对手物防 */
	int		mDefendL;							/* 降低对手魔法 */
} RolePanel, *pRolePanel;

/** 角色信息结构 **/
typedef struct tagRoleInfo 
{
	RolePanel				panel;				/* 人物属性 */
	RoleActSign				actSign;			/* 动作 */
	RoleCamp				camp;				/* 阵营 */
	RoleMode				mode;				/* 角色类型（队友、小怪、小头目等） */
	RoleRace				race;				/* 角色职业 */
	RoleStatus				status;				/* 动作状态: 普通、无敌、霸体、死亡 */
	RoleCondition			condition;			/* 异常状态：中毒、出血等 */
	cocostudio::Armature	*arAnimate;			/* 骨骼动画资源 */
} RoleInfo, *pRoleInfo;

/* 以下是临时buff */
typedef struct tagRoleBuff
{
	int		hpLimit;							/* 生命上限 */
	int		hpBack;								/* hp回复率 */
	int		atk;								/* 攻击力 */
	float	allHarm;							/* 对所有伤害加成（百分比） */
	float	wizardHarm;							/* 对智力型伤害加成（百分比） */
	float	speedHarm;							/* 对敏捷型伤害加成（百分比） */
	float	powerHarm;							/* 对力量型伤害加成（百分比） */
	float	lowerHarm;							/* 免伤率 */
	float	critical;							/* 暴击 */
	float	criExtra;							/* 暴击伤害加成 */
	int		pDefend;							/* 物防天赋 */
	int		mDefend;							/* 法防天赋 */
	int		shield;								/* 护盾 */
} RoleBuff;