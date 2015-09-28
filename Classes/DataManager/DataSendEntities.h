/*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名：   DataEntities
** 日  期：   2015:3:20
** 说  明：	接收到的数据的实体
** 其  它：	
** 历  史：	2015:3:20 初始版本
*********************************************************************/
#pragma once
#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
using namespace std;

// 抽卡类型
enum CardEnum
{
	DrawoffWithNode,
	DrawoffWiteCoin,
	DrawoffWiteDiamond
};

// 抽取到的物品类型
enum GoodsTypeEnum
{
	GoodsNone,
	GoodsProp,
	GoodsEquip,
	GoodsChip,
	GoodsGeneral,
	GoodsPower
};

// 仓库中按钮类型
enum WareroomEnum
{
	wareroomNone0,
	wareroomNone1,
	wareroomNone2,
	wareroomProp,
	wareroomEquip,
	wareroomChip
};

struct HeartBeatStruct
{
	unsigned char constPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValidData;
	unsigned char secondValidData;
	unsigned char heartBeatInt[ 10 ];
};

struct ReginsterAndLoginStruct
{
	unsigned char constPassword[4];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValidData;
	unsigned char secondValidData;
	unsigned char userNameValidData;
	unsigned char passwordVliadData;
	unsigned char newBuffer[ 60 ];
};

struct ServiceAreaStruct
{
	unsigned char constPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValidData;
	unsigned char secondValidData;
	unsigned char userID[ 4 ];						// 通过登录获取的用户ID
};

struct ReginsterPlayerNameStruct
{
	unsigned char constPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValidData;
	unsigned char secondValidData;
	unsigned char serviceID[4];
	unsigned char userID[4];
	unsigned char playerName;
	unsigned char newBuffer[ 32 ];
};

struct PlayerInfoStruct
{
	unsigned char constPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValidData;
	unsigned char secondValidData;
	unsigned char serviceID[4];
	unsigned char userID[4];
};

// 抽卡
struct DrawoffCardStruct
{
	unsigned char constPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValidData;
	unsigned char secondValidData;
	unsigned char playerID[ 4 ];					// 玩家ID
	unsigned char useCoin[ 4 ];					// 消耗金币数量
	unsigned char useDiamond[ 4 ];				// 消耗钻石数量
	unsigned char iscCoin[ 4 ];					// 是否为金币
	unsigned char isdDiamond[ 4 ];				// 是否为钻石
	unsigned char goodsCount[ 4 ];				// 物品数目
	unsigned char newBuffer[ 60 ];
};

struct WareroomCommonStruct
{
	unsigned char conPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValidData;
	unsigned char secondValidData;	
	unsigned char playerID[ 4 ];				// 玩家ID
	unsigned char gridNum[ 4 ];				// 格子数
	unsigned char diamond[ 4 ];				// 消耗钻石
};

struct TeamInfoSendStruct
{
	unsigned char conPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValidData;
	unsigned char secondValidData;	
	unsigned char playerID[ 4 ];				// 玩家ID
};

struct PropUseStruct
{
	unsigned char conPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValidData;
	unsigned char secondValidData;
	unsigned char playerID[ 4 ];				// 玩家ID
	unsigned char propIndex;					// 道具索引值（根据在容器中的数组下标）
};

struct ChipSynthStruct
{
	unsigned char conPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValidData;
	unsigned char secondValidData;
	unsigned char playerID[ 4 ];				// 玩家ID
	unsigned char chipIndex;					// 道具索引值（根据在容器中的数组下标）
	unsigned char chipCount;					// 消耗碎片的数量
	unsigned char generalID[ 4 ];				// 合成将领的ID
};

struct WareroomSelloutStruct
{
	unsigned char conPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValidData;
	unsigned char secondValidData;
	unsigned char playerID[ 4 ];				// 玩家ID
	unsigned char chipIndex;					// 道具索引值（根据在容器中的数组下标）
	unsigned char price[ 4 ];					// 价格
};

struct PointSetInLineSend
{
	unsigned char conPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValidData;
	unsigned char secondValidData;
	unsigned char playerID[ 4 ];				// 玩家ID
	unsigned char generalIndex;				// 索引值（根据在容器中的数组下标）
	unsigned char generalPKID[ 4 ];			// 将领主键ID
};

struct PointSetCancelLineSend
{
	unsigned char conPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValidData;
	unsigned char secondValidData;
	unsigned char playerID[ 4 ];				// 玩家ID
	unsigned char generalIndex;				// 索引值（根据在容器中的数组下标）
	unsigned char generalPKID[ 4 ];			// 将领主键ID
	unsigned char newPKID[ 4 ];				// 将领主键ID
};

// 抽取到物品的结构体
struct DrawoffGoodsStruct
{
	GoodsTypeEnum goodsType;
	int goodsID;
};

// 签到
struct SingInStruct
{
	unsigned char conPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValidData;
	unsigned char secondValidData;
	unsigned char playerID[ 4 ];					// 玩家ID
	unsigned char goodsID[ 4 ];					// 物品ID
	unsigned char goodsType[ 4 ];					// 物品类型
	unsigned char goodsNum[ 4 ];					// 物品数量
	unsigned char day[ 4 ];						// 第几天
	unsigned char isVIP[ 4 ];						// 是否是VIP（这个还存在问题）
};

// 武将属性
struct GeneralSendStruct
{
	unsigned char conpassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValid;
	unsigned char secondValid;
	unsigned char generalPK[ 4 ];
};

// 武将操作装备（穿上和卸下）
struct General_Equip
{
	unsigned char conPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValid;
	unsigned char secondValid;
	unsigned char generalPK[ 4 ];
	unsigned char equipPK[ 4 ];
	unsigned char index;
};

// 武将强化
struct GeneralEnhanceSendStruct
{
	unsigned char conPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValid;
	unsigned char secondValid;
	unsigned char generalPK[ 4 ];
	unsigned char generalExp[ 4 ];
	unsigned char generalLevel[ 4 ];
	unsigned char propID[ 4 ];
	unsigned char playerID[ 4 ];
};

// 武将进化
struct GeneralRevoSendStruct
{
	unsigned char conPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValid;
	unsigned char secondValid;
	unsigned char generalPK[ 4 ];				// 进化的英雄主键
	unsigned char useCoin[ 4 ];				// 消耗的金币数量
	unsigned char useSoul[ 4 ];				// 消耗灵魂石数量
	unsigned char curStar;					// 当前星级
	unsigned char evoLevel;					// 进阶等级
	unsigned char playerID[ 4 ];				// 玩家ID
	unsigned char soulID[ 4 ];				// 灵魂石ID
	unsigned char maxStar[ 4 ];				// 人物最大星级
	unsigned char heroCount[ 4 ];				// 被消耗英雄数量
	unsigned char newBuffer[ 30 ];				
};

// 关卡获得物品
struct CustomsPassGoodsSendStruct
{
	int goodsID;
	int goodsType;
	int goodsCount;
};

//
struct CustomsPassGeneral
{
	int generalPK;			// 将领主键
	int addExp;			// 增加的经验
	int level;				// 等级
};
// 关卡通关
struct CustomsPassSucceedSendStruct
{
	unsigned char conPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValid;
	unsigned char secondValid;
	unsigned char isCross[ 4 ];
	unsigned char playerID[ 4 ];
	unsigned char customsPassID[ 4 ];
	unsigned char goodsNum[ 4 ];
	unsigned char newBuffer[ 110 ];
};

// 装备精炼
struct EquipRefineSendStruct
{
	unsigned char conPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValid;
	unsigned char secondValid;
	unsigned char playerID[ 4 ];
	unsigned char equipID[ 4 ];						// 装备ID
	unsigned char equipLevel[ 4 ];						// 装备等级
	unsigned char equipNum[ 4 ];						// 装备数目
	unsigned char newBuffer[ 1024 ];
};

// 装备强化消耗
struct EquipEnhanceSendStruct
{
	unsigned char conPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValid;
	unsigned char secondValid;
	unsigned char playerID[ 4 ];
	unsigned char equipID[ 4 ];						// 装备ID
	unsigned char equipLevel[ 4 ];						// 装备等级
	unsigned char useCoin[ 4 ];						// 消耗金币
};

struct ScrollEquipSendStruct
{
	unsigned char conPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValid;
	unsigned char secondValid;
	unsigned char playerID[ 4 ];
	unsigned char gainEquipID[ 4 ];						// 获得的装备ID
	unsigned char equipPK[ 16 ];							// 消耗的装备主键
	unsigned char scrollPK[ 4 ];							// 卷轴的主键
};

// 更换装备
struct ChangeEquipSendStruct
{
	unsigned char conPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValid;
	unsigned char secondValid;
	unsigned char generalID[ 4 ];						// 将领ID
	unsigned char preEquipID[ 4 ];						// 原装备ID
	unsigned char NowEquipID[ 4 ];					// 要穿上的装备ID
	unsigned char posIndex;							// 部位
};

// 购买金币和体力
struct BuyCPSendStruct
{
	unsigned char conPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValid;
	unsigned char secondValid;
	unsigned char playerID[ 4 ];						// 玩家ID
	unsigned char diamond[ 4 ];						// 消耗钻石
	unsigned char value[ 4 ];							// 购买金币或者体力数量
};

// 稷下学宫通关
struct JxxgPassSendStruct
{
	unsigned char conPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValid;
	unsigned char secondValid;
	unsigned char playerID[ 4 ];						// 玩家ID
	unsigned char exp[ 4 ];								// 经验
	unsigned char coin[ 4 ];							// 经验
	unsigned char mode1[ 4 ];							// 模式1次数
	unsigned char mode2[ 4 ];							// 模式2次数
	unsigned char mode3[ 4 ];							// 模式3次数
	unsigned char mode4[ 4 ];							// 模式4次数
	unsigned char reward1[ 4 ];							// 奖励1
	unsigned char reward2[ 4 ];							// 奖励2
	unsigned char reward3[ 4 ];							// 奖励3
	unsigned char reward4[ 4 ];							// 奖励4
	unsigned char num1[ 4 ];							// 关卡次数1
	unsigned char num2[ 4 ];							// 关卡次数2
	unsigned char num3[ 4 ];							// 关卡次数3
	unsigned char num4[ 4 ];							// 关卡次数4
};

// 查询物品
struct SortGoodsNumSendStruct
{
	unsigned char conPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValid;
	unsigned char secondValid;
	unsigned char playerID[ 4 ];						// 玩家ID
	unsigned char goodsID[ 4 ];						// 物品ID
};

// 武将点亮天赋
struct GeneralLightStarTalentSendStruct
{
	unsigned char conPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValid;
	unsigned char secondValid;
	unsigned char playerID[ 4 ];						// 玩家ID
	unsigned char generalPK[ 4 ];						// 将领主键
	unsigned char talentID[ 4 ];						// 天赋ID
};

// 技能升级
struct SkillUpgradeSendStruct
{
	unsigned char conPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValid;
	unsigned char secondValid;
	unsigned char generalPK[ 4 ];						// 将领主键
	unsigned char skillSA[ 4 ];						// 等级
	unsigned char skillSB[ 4 ];						// 等级
	unsigned char skillSC[ 4 ];						// 等级
	unsigned char skillSD[ 4 ];						// 等级
	unsigned char playerID[ 4 ];						// 玩家ＩＤ
	unsigned char useCoin[ 4 ];						// 消耗金币
};

// 购买钻石
struct BuyDiamondSendStruct
{
	unsigned char conPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValid;
	unsigned char secondValid;
	unsigned char playerID[ 4 ];						// 玩家ID
	unsigned char diamondValue[ 4 ];					// 钻石数目
};

// 获取玩家状态
struct JxxgBuffInfoSendStruct
{
	unsigned char conPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValid;
	unsigned char secondValid;
	unsigned char playerID[ 4 ];						// 玩家ID
};

// 获取玩家状态
struct PlayerStateSendStruct
{
	unsigned char conPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValid;
	unsigned char secondValid;
	unsigned char playerID[ 4 ];						// 玩家ID
};

// 设置玩家玩家状态
struct SetPlayerStateSendStruct
{
	unsigned char conPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValid;
	unsigned char secondValid;
	unsigned char playerID[ 4 ];						// 玩家ID
	unsigned char isFirstDrawoff;						// 是否是第一次抽卡
	unsigned char isFreeDrawoff;						// 是否免费抽卡
	unsigned char isSignIn;							// 是否签到
	unsigned char pvpRefreshTimes;					// PVP刷新次数
	unsigned char signInCount;						// 签到总天数
	unsigned char buyCoinTimes;					// 购买金币次数
	unsigned char buyPowerTimes;						// 购买体力次数
};

// Pvp信息
struct PvpInfoSendStruct
{
	unsigned char conPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValid;
	unsigned char secondValid;
	unsigned char playerID[ 4 ];						// 玩家ID
};

// Pvp通关
struct PvpPassSendStruct
{
	unsigned char conPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValid;
	unsigned char secondValid;
	unsigned char ownID[ 4 ];							// 玩家己方ID
	unsigned char otherID[ 4 ];							// 玩家对方ID
	unsigned char result[ 4 ];							// 结局
};

// Pvp竞技场设置上阵武将
struct PvpWarriorsSetSendStruct
{
	unsigned char conPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValid;
	unsigned char secondValid;
	unsigned char playerID[ 4 ];						// 玩家ID
	unsigned char pkID1[4];								// 武将PKID1
	unsigned char pkID2[4];								// 武将PKID2
	unsigned char pkID3[4];								// 武将PKID3
	unsigned char pkID4[4];								// 武将PKID4
};

// 仓库格子数
struct WareroomGridNum
{
	unsigned char conPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValid;
	unsigned char secondValid;
	unsigned char playerID[ 4 ];
};

// 商店购买物品
struct StoreBuyGoodsSendStruct
{
	unsigned char conPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValid;
	unsigned char secondValid;
	unsigned char playerID[ 4 ];
	unsigned char goodsID[ 4 ];
	unsigned char goodsType[ 4 ];
	unsigned char goodsNum[ 4 ];
	unsigned char price[ 4 ];
};

struct  StoreRefreshSendStruct
{
	unsigned char conPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValid;
	unsigned char secondValid;
	unsigned char playerID[ 4 ];
	unsigned char diamond[ 4 ];
};
struct storeBuyGoodsStruct{
	int goodsID;
	GoodsTypeEnum goodsType;
	int goodsNum;
	int goodsPrice;
};
