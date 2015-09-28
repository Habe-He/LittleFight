/*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名：   DataRecvEntities
** 日  期：   2015:3:25
** 说  明：	根据从服务器接收的数据匹配
** 其  它：	
** 历  史：	2015:3:25 初始版本
*********************************************************************/
#pragma once
#include "cocos2d.h"
USING_NS_CC;
using namespace std;

enum StorePayType
{
	witeCoin,
	witeDiamond,
};

// 玩家信息
struct PlayerInfoRecvStruct
{
	char playerName[ 20 ];				// 玩家名称
	int level;							// 等级
	int exp;							// 经验
	int coinValue;						// 金币
	int diamondValue;					// 钻石


	int playerID;						// 玩家ID
	int powerValue;						// 体力
	int soulCount;						// 灵魂石数目
	int gongXun;						// 功勋数目
	int coinTimes;						// 购买金币次数
	int powerTimes;						// 购买体力次数
};

struct SeriveAreaRecvStruct
{		
	short bigSmallClass[ 2 ];
	short validData[ 2 ];					// 数据总的有效长度
	char serviceCount;					// 服务区数量
	int serviceID;						// 服务区ID
	char serviceNameValidData;			// 服务区名称有效长度
	string serviceName;					// 服务区名称
};

// 装备
struct EquipProptyStruct
{
	int ePKID;								// 装备主键ID
	int eID;								// 装备ID
	char eChinaName[ 20 ];					// 中文名称
	int eLevel;								// 装备等级
	int ePositionType;						// 装备部位
	char ePositionName[ 10];					// 部位名称
	int eColor;								// 装备颜色
	int eSellOut;							// 装备价格
	int eExp;								// 经验
	int eHP;								// 增加血量
	int eAtk;								// 增加攻击力
	int eMD;								// 增加法术防御
	int ePD;								// 增加物理防御
	float eAddCrit;							// 增加暴击几率
	float eReduceCrit;						// 减少暴击几率
	int eAddRealHurt;						// 增加真实伤害
	int eReduceHurt;						// 减少真实伤害
	int eisSuit;								// 是否为套装
	int eLevelLimit;							// 装备等级限制
	char eDes[ 200 ];						// 装备介绍
};

// 装备品级
enum EquipGradeEnum
{
	EquipGradeWhite = 0,					// 白色 
	EquipGradeGreen,						// 绿色
	EquipGradeBlue,							// 蓝色
	EquipGradePurple,						// 紫色
	EquipGradeMax
};

// 装备精炼
struct EquipRefineStruct
{
	int		eLevel;							// 等级
	int		eExp[EquipGradeMax];			// 不同品级所需经验
	int		eCoin[EquipGradeMax];			// 不同品级所需金币
	float	eGrow1[EquipGradeMax];			// 不同品级属性成长（奇珍）
	float	eGrow2[EquipGradeMax];			// 不同品级属性成长（异宝）
};

// 技能
struct SkillNameStruct
{
	int RoleID;								// 技能对应人物ID
	char sAName[ 15 ];						// 技能一中文名称
	char sBName[ 15 ];						// 技能二中文名称
	char sCName[ 15 ];						// 技能三中文名称
	char sDName[ 15 ];						// 技能四中文名称
	char sANameS[ 15 ];					// 技能一拼音
	char sBNameS[ 15 ];					// 技能二拼音
	char sCNameS[ 15 ];					// 技能三拼音
	char sDNameS[ 15 ];					// 技能四拼音
	int sACD;								// 技能一CD
	int sBCD;								// 技能二CD
	int sCCD;								// 技能三CD
	int sDCD;								// 技能四CD
	float sAHurt;							// 技能一伤害
	float sBHurt;							// 技能二伤害
	float sCHurt;							// 技能三伤害
	float sDHurt;							// 技能四伤害
	char sADes[ 120 ];						// 技能一介绍
	char sBDes[ 120 ];						// 技能二介绍
	char sCDes[ 120 ];						// 技能三介绍
	char sDDes[ 120 ];						// 技能四介绍
};

struct GeneralProptyStruct
{
	int roleID;							// 角色ID
	char chinaName[20];					// 中文名称
	char chinaSmallName[20];				// 中文拼音名称
	char country[4];						// 所属国家	
	int maxStar;						// 最大星级
	int jobType;						// 职业类型
	int evoLevel;						// 进阶等级
	int nowStar;						// 当前星级（升星所需）
	int levelLimit;						// 升星所需等级
	int	evoLimit;						// 阶级等级需求
	int initAtk;							// 初始攻击力
	int atkGrowing;						// 攻击力增长
	int initHP;							// 初始血量
	int hpGrowing;						// 血量增长
	int initPD;							// 初始物理防御
	int pdGrowing;						// 物理防御增长
	int initMD;							// 初始法术防御
	int mdGrowing;						// 法术防御增长
	float riseHP;						// 回血
	char g_des[500];					// 介绍
	int curStarLevel;					// 武将当前星级（服务器获得）
	int isSelect;						// 是否上阵（1、上阵。0、为上阵）
	float strongExp;						// 强化经验
	int evoExp;						// 进化经验
	int equipID[6];						// 装备的武器
	EquipProptyStruct equipPropty[ 6 ];		// 装备数组
	int level;							// 当前等级	
	int PKID;							// 武将主键ID
	int posFlag;						// (测试)武将进化所对应的位置
	int skillLevel[ 4 ];					// 技能等级
};

// 本地技能升级
struct SkillUpgradeStruct
{
	int skillLevel;
	int skillExpandCoin;
	float skillPropty;
};

struct GeneralUpgradeStruct
{
	int gLevel;
	int gNeedExp;
};

// 抽取
struct DrawoffIDRecvStruct
{
	int cID;
	int wID;
	char wName[130];
};

// 抽卡
struct DrawoffRecvStruct
{
	int goodsType;
	char idRange[15];
	char coinRange[15];
	char diamonRange[15];
};

// 宝箱
struct BoxRecvStruct
{
	int goodsType;
	char idRange[ 15 ];
	char tong[ 15 ];
	char yin[ 15 ];
	char jin[ 15 ];
};

enum PointDifficulty
{
	PointDiff_Normal = 0,
	PointDiff_Hard,
	PointDiff_Max
};

/* 关卡收益 */
struct PointGainsStruct
{
	int		level;						/* 帐号等级 */
	int		power[PointDiff_Max];		/* 体力消耗 */
	int		exp[PointDiff_Max];			/* 经验获取 */
	int		coin[PointDiff_Max];		/* 金币获取 */
};

// 武将碎片
struct GeneralChipRecvStruct
{
	int starLevel;
	int num;
};

// 装备碎片
struct EquipChipRecvStruct
{
	int color;
	int isSuit;
	int num;
};

// 关卡
struct CustomsPassRecvStruct
{
	int customsPassID;
	int customsPassStarCount;
};



struct PropProptyStruct
{
	int pID;
	char pChinaName[ 20 ];
	int pType;					// 道具类型
	int pExpAdd;
	int pPowerAdd;
	int pSellPrice;
	char pDes[ 300 ];
};

struct PointRole					/* 关卡角色 */
{
	int		pID;
	int		room;					/* 第几场景 */
	int		level;					/* 等级 */
	int		flag;					/* 是否boss */
};

struct PointBox						/* 关卡宝箱 */
{
	int		pID;
	int		num;
};

struct PointThing					/* 关卡获得物品 */
{
	int		pID;
	float	rate;					/* 获得几率 */
};

struct CheckPointStruct
{
	int cID;
	char *cName;					/* 关卡名 */
	int cNameLen;					/* 关卡名长度 */
	PointRole *cRoles;				/* 关卡角色 */
	int cRoleNum;					/* 关卡角色数 */
	int cPower;						// 消耗的体力
	PointBox cBox;					/* 宝箱 */
	int cSoul;						// 可获得灵魂石数量
	char *cMap;						/* 关卡地图 */
	int cMapLen;					/* 地图长度 */
	char *cSong;					/* 关卡背景音效 */
	char cSongLen;					/* 音效文件长度 */
	PointThing *cThing;				// 可获得的物品
	int cThingNum;					// 可获得的物品数量
	int cPill;						/* 培养丹 */
	float cPillRate;				/* 培养丹获取几率 */
	char *cDes;
	char cDesLen;
};

struct PointCellInfoStruct
{
	int pID;						/* 关卡ID */
	int	xLoc;						/* 关卡横坐标 */
	int yLoc;						/* 关卡纵坐标 */
};

struct SignInStruct
{
	int sSignInDay;
	char sGoodsName[20];
	int sGoodsRes;						// 资源名称
	int sGoodsType;					// 资源类型
	char IDRange[ 20 ];					// ID范围
	int sNeedVip[10];					// VIP等级对应物品数量
};

struct WareroomCommonRecvStruct
{
	int itemsNum;					// 仓库格子数目
	int itemPKID;					// 物品主键ID
	int itemsID;					// 物品ID
	int itemsCount;					// 物品数量
	int itemsLevel;					// 装备等级
	int isSelect;					// 是否被使用 1 使用    0 未使用
	int equipExp;					// 装备经验
};

struct ItemEquipStruct
{
	int iPKID;						// 装备主键ID
	int iID;						// 装备ID
	int iLv;						// 装备等级
	int iExp;						// 装备经验
};
	
struct MaidanStruct		// 练兵场结构体
{
	int generalCount;				// 武将数量
	int generalPKID;				// 将领主键ID
	int generalType;					// 将领ID
	int generalLevel	;				// 将领等级
	int generalStar;					// 将领星级
	int isSelected;					// 将领是否上阵（1 = 参战， 0 = 不参战）
	int curStar;					// 阶数（当前星级）
	int generalExp;					// 武将经验
	int evoLevel;					// 进阶等级
	//int invalidMaxStar;				// 最大星级
};

struct PointSetsRecvStruct
{
	int generalPKID;				// 将领主键ID
	int generalID;					// 将领ID
	int generalLevel;				// 将领等级
	int generalStar;					// 将领星级
	int evoLevel;					// 进阶等级
	int generalPos;					// 上阵位置
};

// 武将详细属性结构体
struct GeneralDetailRecvStruct
{
	int strExp;						// 强化经验				
	int level;
	int starLevel;					// 当前
	int evoExp;					// 进化经验
	int evoLevel;					// 进化等级
	int equipPKID[ 6 ];				// 装备主键ID
	int equipID[ 6 ];				// 装备ID
	int equipLevel[ 6 ];				// 装备等级
	int equipExp[ 6 ];				// 装备精炼经验值
	int skillLevel[ 4 ];				// 四个技能等级
};

// 本地武将进化规则
struct GeneralEvoLocalStruct
{
	int maxStar;					// 人物最大星级
	int evoLevel;					// 进阶等级
	int curStar;					// 当前星级
	int sameName;					// 同名武将数量
	int addStar;					// 是否可以升星
	int addEvo;					// 进化等级
	int levelLimit;					// 进化规则
	int needExp;					// 所需经验
	int needSoul;					// 所需灵魂石
	int needCoin;					// 所需金币
};

// 武将进化时所提供经验
struct GeneralEvoExpLocalStruct
{
	int maxStar;				// 最大星级
	int curStar;				// 当前星级
	int pridExp;				// 提供的经验
};

// 购买金币和体力
struct BuyCPLocalStruct
{
	int times;					// 购买次数
	int ruleDP;					// 钻石购买体力的价格
	int valuePower;				// 钻石购买体力的数量
	int ruleDC;				// 钻石购买金币的价格
	int valueCoin;				// 钻石购买金币的数量
};

// 天赋
struct TalentLocalStruct
{
	int id;					// 天赋编号
	int type;					// 天赋类型
	int lightStar;				// 点亮星级要求
	int special;				// 特殊天赋
	char talentName[ 20 ];		// 天赋中文名称
	char resName[ 20 ];			// 资源名称
	char des[ 100 ];			// 天赋介绍
};

// 战队信息
struct TeamInfoStruct
{
	int teamLevel;
	int teamExp;
};

// 战队升级
struct TeamUpgradeLocalStrcut
{
	int level;
	int needExp;
};

// 武将点亮的天赋
struct GeneralLightStarTalentRecvStruct
{
	unsigned char conPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValid;
	unsigned char secondValid;
	unsigned char playerID[ 4 ];						// 玩家ID
	unsigned char generalPK[ 4 ];						// 将领主键
};

// 玩家状态
struct PlayerStateRecvStruct
{
	int isFirstDrawoff;					// 是否是第一次抽卡
	int coinDrawoffFree;					// 是否可以金币免费抽
	int diamondDrawoffFree;				// 是否可以钻石免费抽
	int isSignIn;						// 今天是否签到
	int guidePos;						// 新手引导的位置
	int refreshPVPTime;					// ＰＶＰ刷新次数
	int signInTimes;						// 签到总天数
	int buyCoinTimes;					// 购买金币次数
	int buyPowerTimes;					// 购买体力次数
	int refreshStoreTimes;              //商店刷新次数

	int coinDrawTimes;					// 金币抽卡次数
	int diamondYear;					// 钻石年
	int diamondMonth;					// 钻石月
	int diamondDay;						// 钻石日
	int diamondHour;					// 钻石时
	int diamondMin;						// 钻石分
	int diamondSec;						// 钻石秒
};

// 抽卡倒计时
struct DrawoffCountZeroRecvStruct
{
	int isCoinFree;
	int coinHour;
	int coinMin;
	int coinSec;
	int isdiamondFree;
	int diamondHour;
	int diamondMin;
	int diamondSec;
};

// 服务器当前时间
struct ServiceDayTimeRecvStruct
{
	int year;
	int mon;
	int day;
	int hour;
	int min;
	int sec;
};

// 稷下学宫buff获取
struct JxxgBuffInfoRecvStruct
{
	int mode;								// 模式次数
	int ticket;								// 门票
	int rewar;								// 奖励
	int num;								// buff次数
};

// 竞技场玩家上阵武将
struct PvpPlayerTeamRecvStruct
{
	int	pvpID;								// 玩家id
	int pvpPKID;							// 玩家pkid
};

// 随机获取竞技场5名对手
struct PvpCompetitorRecvStruct
{
	int	pvpID;								// 玩家id
	int pvpLv;								// 玩家等级
	int pvpRank;							// 玩家pvp排名
	char pvpName[20];						// 玩家名称
};

// 竞技场记录
struct PvpRecordRecvStruct
{
	int	pvpID;								// 对方id
	int pvpWinLos;							// 0:输, 1:赢
	int pvpUpDown;							// 排名上升下降
	int pvpRank;							// 排名
	int pvpYear;							// 年
	int pvpMonth;							// 月
	int pvpDay;								// 日
	int pvpHour;							// 时
	int pvpMinute;							// 分
	int pvpSecond;							// 秒
	char pvpName[20];						// 对方名称
	int pvpPower;							// 对方战斗力
	int pvpLv;								// 对方玩家等级
};

// 竞技场排名记录
struct PvpRankRecvStruct
{
	int	pvpID;								// 对方id
	int pvpLv;								// 对方玩家等级
	char pvpName[20];						// 对方名称
	int pvpPower;							// 对方战斗力
};

// 技能等级对应人物属性增加
struct SkillAddPropty
{
	int skillLevel;
	int eATK;				// 五星增加攻击力
	int eAtkLen;			// 
	int eHP;				// 五星增加生命值
	int eHPLen;			//
	int ePD;				// 五星物防
	int ePDLen;			// 
	int eMD;				// 五星法防
	int eMDLen;			//
	int dHP;				// 四星生命值
	int dHPLen;			//
	int dPD;				// 四星物防
	int dPDLen;			//
	int dMD;				// 四星法防
	int dMDLen;			// 
	int cPD;				// 三星物防
	int cPDLen;			// 
	int cMD;				// 三星法防
	int cMDLen;			//
};

// 角色技能范围
struct SkillRegionStruct
{
	int		atk[2];			// 普攻第一击范围
	int		atk2[2];		// 普攻第二击范围
	int		atk3[2];		// 普攻第三击范围
	int		s1[2];			// 技能一范围
	int		s2[2];			// 技能二范围
	int		s3[2];			// 技能三范围
	int		s4[2];			// 技能四范围
};

// 角色副属性
struct SubInfoStruct
{
	float	anchorX;		// 锚点x
	float	anchorY;		// 锚点y
	float	speed;			// 速度
};

// 竞技场排名每日收益
struct PvpDailyGainsStruct
{
	int		rank;			// 排名
	int		coin;			// 金币
	int		exploit;		// 功勋
};

// 竞技场对战收益
struct PvpPkGainsStruct
{
	int		rank;			// 排名
	int		coin[2];		// 金币
	int		exploit[2];		// 功勋
};

struct WareroomGridRecvStruct
{
	int propGridNum;
	int equipGridNum;
	int chipGridNum;
};

// 每日任务
struct DailyTaskLocalStruct
{
	int id;								// 编号
	char taskName[ 60 ];					// 任务名称
	int dTimes;							// 执行次数
	char diamondValue[ 10 ];					// 钻石奖励数量
	char coinValue[ 10 ];					// 金币奖励数量
	char soulValue[ 10 ];					// 灵魂石--数量
	char danValue[ 10 ];						// 培养丹--数量
	char comMadValue[ 10 ];					// 普通经验药水---数量
	char powerValue[ 10 ];					// 体力---数量
	int teamExp;
};

struct StoreListRecvStruct
{
	int goodsID;					// 物品ID
	StorePayType payType;			// 支付方式
	int isBuy;						// 是否购买过
};

// 商店物品
struct StoreLocalDataStruct
{
	char idRange[ 30 ];
	int goodType;
	int coinPrice;
	int diamondPrice;
};

//本地成就数据
struct AchievementLocalDataStruct 
{
	int CID;				//编号
	char CName[30];			//成就名称
	char Condition[50];		//成就条件
	int  num;	
	char Coin[10];			//金币物品类型和数量
	char Diamond[10];		//钻石物品类型和数量
	char General[10];		//人物整卡ID与数量
	char GeneralChip[10];	//人物碎片ID与数量
	int Dan;				//培养丹数量
	int Soul;				//灵魂石数量
	int SimpleMad;			//普通经验药水数量
	char WhiteEquip[10];	//白色装备ID与数量
	char  WhiteSpecial[10];	//白色宝物ID与数量
	int TeamExp;			//战队经验值
	
};
//成就领取状态数据
struct AchievementDataStruct 
{
	int corpsGrade;				//战队成就领取状态
	int generalUpgrade[3];		//武将升级成就领取状态
	int coins;				//金币成就领取状态
	int daimonds;			//钻石成就领取状态
	int customs[14];		//关卡成就领取状态
	int warerooms;			//仓库解锁成就领取状态
	int generalCollect[6];		//武将收集成就领取状态
	int jiXiaXueGong;		//稷下学宫成就领取状态
	int yiQiDangQian;		//一骑当千成就领取状态
	int isHp;				//购买体力成就领取状态
	int  generalStar[41];	//武将升星成就领取状态
	int arena;				//竞技场成就领取状态
	int skillUp;			//技能升级成就领取状态
	int getEquipment[4];	//获得装备成就领取状态
	int equipmentIndensify;	//装备强化成就领取状态
	int equipmentRefine;	//装备精炼成就领取状态
	int patchCompose;		//碎片合成成就领取状态
};

//第一次进入游戏的字幕
struct satrtGameStruct
{
	char OpenStory[100];
};