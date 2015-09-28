/*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名：   DataManager
** 日  期：   2015:3:18
** 说  明：	向服务器发送、请求数据
** 其  它：	
** 历  史：	2015:3:18 初始版本
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "DataSendEntities.h"
#include "DataRecvEntities.h"
#include "ChineseCode/ChineseCode.h"
#include "Public/FontChina.h"
#include "UserInfo/UserData.h"
// 读取本地文件使用
#include "json/rapidjson.h"
#include "json/document.h"




USING_NS_CC;
using namespace std;

const int resCount = 4;				// 加载Plist数量
const int maxPvpRecord = 10;			// pvp对战记录数

class DataManager
{
public:
	DataManager();
	virtual ~DataManager();

	static DataManager* mpDataManager;		

	static DataManager* getInstance();

	vector<string> splitString(string str, string pattern);															// 根据分隔符分割字符串

	bool isLoginSuccess();																				// 登陆（1、3）

	bool isGetPlayerInfo();																				// 获取玩家信息（1、6）

	bool siSingIn(int goods_ID, int goodsType, int Num, int day, int isVIP);											// 签到（1、7）

	bool isGetPlayerState();																				// 获取玩家状态（1、8）
	
	bool isBuyDiamond(int diamondCount);																	// 购买钻石（1、10）

	bool isDrawoffCard(int coin, int diamond, int isCoin, int isDiamond, vector<DrawoffGoodsStruct > drawoffStruct);				// 抽卡是否成功（2、1）

	bool isGetMaidan();																					// 获取练兵场武将信息（2、2）

	int  isGetMaidanCount();																				// 获取练兵场武将数量

	bool isGetPointSets();																					// 获取点将台信息（2、3）

	bool isCancelTheLine(int generalIndex, int generalPKID);														// 武将下阵（2、4）

	bool isChangeTheLine(int o_GeneralIndex, int o_GeneralPKID, int n_PKID);										// 换将（2、5）

	bool isGetGeneralProperty(int generalPK);																	// 获取武将属性（2、6）参数为在数组中下标

	bool isDonSucceed(int generalPKID, int equipPKID, int posIndex);												// 武将穿戴装备（2、7）

	bool isUnloadEquip(int generalPKID, int equipPKID, int posIndex);												// 武将卸下装备（2、8）

	bool isEnhanceGeneral(int generalPKID, int generalExp, int generalLevel, int propID);								// 武将强化（2、9）

	bool isRevoGeneral(int generalPKID, int curStar, int evoLevel, int evoExp, vector<int > pkIDHero, int useCoin, int useSoul);// 武将进化（2、10）

	bool isGetCustomsPass(int diff = 0, int cpID = -1);															// 关卡信息（2、11）

	bool isCustomsPass(int teamAddExp, int gainCoin);															// 关卡通关（2、12）

	bool isSetPointStarLv(int cpID, int star, bool *bReward);													/* 设置关卡通关星级 */

	bool isSetPointWarriorsLv(vector<CustomsPassGeneral> cpgs);														/* 设置通关武将等级 */

	bool isSetPointGoods(std::vector<CustomsPassGoodsSendStruct> pointGoods);										/* 设置通关物品 */

	bool isBuyStoreThing( int goodsID, GoodsTypeEnum goodsType, int num, int price);									// 商店购买物品（2、13）

	bool isTalentLightStar(int generalPKID, int talentID, int pos);														// 武将点亮天赋（2、16）

	bool isGetTalentDate(int generalPKID);																	// 获取武将点亮天赋（2、17）

	bool isSelectGeneral(int posIndex, int generalPKID);															// 武将上阵（2、19）

	bool isGetTeamInfo();																					// 获取战队信息（2、20）

	bool isChangeEquip(int generalID, int prePK, int nowPK, int pos);												// 更换装备（2、22）

	bool isBuyPower(int diamond, int power);																	// 购买体力（2、23）

	bool isBuyCoin(int diamond, int coin);																	// 购买金币（2、24）

	bool isJxxgPassSucceed(int exp, int coin, vector<JxxgBuffInfoRecvStruct > infos);									// 稷下学宫通关 (2、25)

	bool isGetStoreList();																					// 获取商店物品列表 (2、26)

	bool isSkillUpgrade(int generalPK, int sa, int sb, int sc, int sd, int coin);											// 技能升级（2、30）

	bool isGetJxxgBuffInfo();																				// 获取稷下学宫buff（2、32）

	bool isDrawoffCountZero();																				// 抽卡倒计时（2，33）

	bool isRefreshStore(int diamondValue);																	// 手动刷新商店（2，34）

	bool isCultivateGeneral(int gPKID, int coin, int diamond, int pillCount, int gAtk, int gHp, int gPd, int gMd);	// 武将培养

	bool isGetGeneralGrowth(int gPKID);																		// 获取武将培养属性

	bool reSetTalent(int gPKID, int i_Diamond);																// 重置天赋

	bool isGetPropData();																					// 获取所有道具数据（3、1）

	bool isGetEquipData();																				// 获取所有装备（3、2）

	bool isGetEquipData(int PKID);																			/* 获取指定装备信息 */
	
	bool isGetChipData();																					// 获取所有碎片（3、3）

	bool isUnlockGridSucceed(WareroomEnum wareroomType, int grid, int diamond);									// 开启仓库格子数是否成功（3、4/5/6 (道具、装备、碎片)）

	bool isPropUseScceed(int propIndex);																		// 道具使用（3、7）（在容器中的数组下标）

	bool isChipSynthScceed(int chipIndex, int chipNum, int itemID);												// 碎片合成（3、8）（在容器中的数组下标）

	bool isSelloutEquipScceed(int equipIndex, int price);														// 卖出装备（3、10）（在容器中的数组下标）

	bool isSelloutPropScceed(int propIndex, int price);															// 卖出道具（3、9）（在容器中的数组下标）

	bool isRefineEquip(int equipID, int equipLevel, vector<int > equipVector, int useExped, int useCoin);		// 精炼装备（3、11）

	bool isSortGoodsNum(int goodsID);																		// 查询物品数量（3、13）

	bool isEnhanceEquip(int equipID, int equipLevel, int coin);														// 强化装备（3、14）

	bool isSortWNum();																						// 仓库格子数和物品数量（3、15）
	
	int calcTeamLevle(int curExp);																			// 战队当前等级

	int calcTeamExp(int curExp);																			// 战队当前剩余经验

	bool parserGoodsGains(GoodsTypeEnum goodsType, int goodsID, int num);									/* 解析物品获得 */

	bool parseGoodsRemove(GoodsTypeEnum goodsType, int goodsID, int num = 1);								/* 解析物品删除 */

	bool wealthUpdate(int coin, int diamond);																/* 财富更新 */
	
	bool goodsCountUpdate(int id, int count);																/* 物品更新(刷新可叠加物品道具) */

	bool skillUnlock(int pkID, int level);																	/* 武将技能解锁 */


	// 定义接收数据的结构体
private:
	int goodsNum;														// 查询物品数量
	int pvpRank;														// Pvp排名
	bool pvpResult;														// pvp通关
	std::vector<int >	generalGrowthVector;							/* 武将培养增幅属性 */
	ItemEquipStruct		itemEquip;
	vector<SeriveAreaRecvStruct > serviceAreaRecvVector;						// 存放服务区列表信息	
	vector<MaidanStruct > maidanRecvVector;									// 练兵场武将信息	
	vector<GeneralDetailRecvStruct > generalDetailRecvVector;						// 武将详情	
	vector<PointSetsRecvStruct > pointSetRecvVector;							// 点将台	
	vector<WareroomCommonRecvStruct > wareroomPropVector;					// 仓库中道具	
	vector<WareroomCommonRecvStruct > wareroomEquipVector;					// 仓库中装备	
	vector<WareroomCommonRecvStruct > wareroomChipVector;					// 仓库中碎片
	vector<CustomsPassRecvStruct > customsPassVector;							// 关卡（网络）
	vector<PlayerInfoRecvStruct > playerInfoVector;								// 玩家信息（网络）
	vector<TeamInfoStruct > teamInfoVector;									// 战队信息（网络）
	vector<int > interTalentVector;											// 武将天赋（网络）
	vector<PlayerStateRecvStruct > playerStateVector;							// 玩家状态
	vector<DrawoffCountZeroRecvStruct > countZeroVector;						// 抽卡倒计时
	vector<ServiceDayTimeRecvStruct > serviceDayTimeVector;						// 服务器当前时间
	vector<JxxgBuffInfoRecvStruct > jxxgBuffVector;								// 稷下学宫信息
	vector<PvpCompetitorRecvStruct > pvpCompetitorVector;						// 竞技场对手
	vector<PvpPlayerTeamRecvStruct > pvpPlayerTeamVector;						// 竞技场对手战队
	vector<PvpRecordRecvStruct > pvpRecordVector;							// 竞技场对战记录
	vector<PvpRankRecvStruct > pvpRankingVector;								// pvp排行榜
	vector<WareroomGridRecvStruct > wareroomGridVector;						// 仓库物品、格子数量
	vector<StoreListRecvStruct > storeListVector;								// 商店物品

public:
	// ------------------------------- 以下是读取本地Json文件 ---------- 实现方法 ----------- Begin ------------------- //
	void generalDataParser();														// 解析武将表
	void generalUpgradeDataParser();												// 解析武将升级规则表
	void equipDataParser();														// 解析装备表
	void equipRefineRule();														// 解析装备精炼规则
	void propDataParser();														// 解析道具表
	void checkPointDataParser(int = 0);												// 解析关卡详情表: 0:普通关卡；1:精英关卡
	void pointCellInfoParse();														/* 解析关卡图标信息 */
	void jxxgDataParser();														// 解析稷下学宫表
	bool signInDataParser();														// 解析签到表				
	void DrawoffIDDataParser();													// 解析抽取物品的表	（抽卡和宝箱开启产生的ID和物品ID的对应表）
	void DrawoffDataParser();														// 解析抽卡表	
	void boxDataParser();														// 解析宝箱表
	void pointGainsParse();														// 关卡收益
	void generalChipDataParser();													// 武将碎片合成
	void equipChipDataParser();													// 装备碎片合成
	void SkillNameDataParser();													// 技能名称
	void SkillUpgradeDataParser();													// 技能升级
	void GeneralEvoDataParser();													// 武将进化规则
	void GeneralEvoExpDataParser();												// 武将进化是所提供的经验
	void BuyCoinAndPower();														// 购买金币和体力
	void talentDataParser();														// 天赋
	void teamUpgradeDataParser();													// 战队升级数据解析
	void skillUpgradeProptyAdd();													// 技能升级对应人物属性增加
	void skillRegionParser();														/* 技能范围解析 */
	void subInfoParser();															/* 人物副属性解析 */
	void dailyTaskDateParser();													// 每日任务数据解析
	void PvpDailyGainsParser();													/* 竞技场排名每日收益 */
	void PvpPkGainsParser();														/* 竞技场对战收益 */
	void storeLocalDataParser();													// 解析商店物品基础信息表

	void AchievementLocalDataParser();													//解析成就数据

	void OneStartGameStory();														//第一次进入游戏的剧情介绍

	void encfile(const char *in_filename, char *pwd, const char *out_file);
	void decryptfile(const char *in_filename, char *pwd, const char *out_file);
private:
	vector<GeneralProptyStruct > generalProptyVector;									// 武将基础属性				
	vector<GeneralUpgradeStruct > generalUpgradeDataVector;								// 武将升级数据
	vector<EquipProptyStruct > equipProptyVector;										// 装备
	vector<EquipRefineStruct > equipRefineVector;										// 装备精炼规则
	vector<PropProptyStruct > propProptyVector;										// 道具基础属性
	vector<CheckPointStruct > checkPointPropthVector;									// 关卡详情数据
	vector<PointCellInfoStruct > pointCellInfoVector;										// 关卡图标信息数据
	vector<SignInStruct > signInVector;												// 签到数据
	vector<DrawoffIDRecvStruct > drawoffIDVector;										// 抽取（抽卡和宝箱开启产生的ID和物品ID的对应表）
	vector<DrawoffRecvStruct > drawoffVector;											// 抽卡
	vector<BoxRecvStruct > boxVector;												// 宝箱开启物品
	vector<PointGainsStruct > pointGainsVector;										// 关卡收益
	vector<GeneralChipRecvStruct > generalChipVector;									// 武将碎片合成规则
	vector<EquipChipRecvStruct > equipChipVector;										// 装备碎片合成规则
	vector<SkillNameStruct > skillNameVector;											// 技能表
	vector<SkillUpgradeStruct > skillUpgradeVector;										// 技能升级
	vector<GeneralEvoLocalStruct > generalEvoLocalVector;								// 武将进化本地
	vector<GeneralEvoExpLocalStruct > generalEvoExpLocalVector;							// 武将进化所提供经验本地
	vector<BuyCPLocalStruct > buyCPLocalVector;										// 购买金币和体力本地规则
	vector<TalentLocalStruct > talentLocalVector;										// 天赋
	vector<TeamUpgradeLocalStrcut > teamUpgradeLocalVector;							// 战队升级
	vector<SkillAddPropty > localSkillAddProptyVector;									// 技能升级属性增加
	map<std::string, SkillRegionStruct > skillRegionMap;									// 角色技能范围
	map<string, SubInfoStruct > subInfoMap;											/* 人物副属性 */
	vector<DailyTaskLocalStruct > dailyTaskVector;										// 每日任务
	vector<PvpDailyGainsStruct > pvpDailyGainsVector;									/* 竞技场排名每日收益 */
	vector<PvpPkGainsStruct > pvpPkGainsVector;										/* 竞技场对战收益 */
	vector<StoreLocalDataStruct > localStoreDataVector;									// 商店物品基础信息表

	
	vector<AchievementLocalDataStruct> localAchievementDataVector;							// 保存成就数据

	vector<satrtGameStruct > localOnceStartVector;									//第一次进入游戏的剧情字幕
	// 通过以下函数访问内部数据
public:
	int sortGoodsNum();															// 查询物品数量
	int curPvpRank();															// pvp排名
	bool curPvpPass();															// pvp通关
	std::vector<int >	getGeneralGrowthVector();								/* 武将培养增幅属性 */
	ItemEquipStruct interItemEquipStruct();										/* 获取指定装备信息 */
	vector<SeriveAreaRecvStruct > interSeriveAreaVector();								// 服务区列表	
	vector<MaidanStruct > interMaidanVector();											// 练兵场武将网络数据
	vector<GeneralDetailRecvStruct > interGeneralVector();								// 武将详情	
	vector<WareroomCommonRecvStruct > interWareroomPropVector();						// 仓库中道具网络数据	
	vector<WareroomCommonRecvStruct > interWareroomEquipVector();						// 仓库中装备网络数据	
	vector<WareroomCommonRecvStruct > interWareroomChipVector();						// 仓库中碎片网络数据
	vector<PointSetsRecvStruct > interPointSetsVector();									// 点将台网络数据	
	vector<PlayerInfoRecvStruct > interPlayerInfoVector();									// 玩家信息网络数据
	vector<TeamInfoStruct > interTeamInfoVector();										// 战队信息
	vector<int > interTalentVectors();												// 武将将天赋
	vector<PlayerStateRecvStruct > interPlayerStateVector();								// 玩家状态
	vector<DrawoffCountZeroRecvStruct > interCountZeroVector();							// 倒计时
	vector<ServiceDayTimeRecvStruct > interDayTimesVector();								// 服务器当前时间
	vector<JxxgBuffInfoRecvStruct > interJxxgBuffVector();									// 获取稷下学宫信息
	vector<PvpCompetitorRecvStruct > interPvpCompetitorVector();						// 获取获取竞技场对手
	vector<PvpPlayerTeamRecvStruct > interPvpPlayerTeamVector(int id);					// 竞技场对手战队
	vector<PvpRecordRecvStruct > interPvpRecordVector();								// 竞技场对战记录
	vector<PvpRankRecvStruct > interPvpRankingVector();									// pvp排行榜
	vector<WareroomGridRecvStruct > interWareroomVector();								// 仓库物品、格子

	vector<PropProptyStruct > localPropProptyVector();									// 道具基础数据	
	vector<GeneralProptyStruct > localGeneralProptyVector();								// 武将基础属性	
	vector<EquipProptyStruct > localEquipProptyVector();									// 装备基础属性	
	vector<EquipRefineStruct > localEquipRefineVector();									// 装备精炼规则
	vector<CheckPointStruct > localCheckPointVector();									// 关卡基础属性
	vector<PointCellInfoStruct > localPointCellInfoVector();							// 关卡图标信息数据
	vector<SignInStruct > localSignInVector();											// 签到奖励
	vector<DrawoffIDRecvStruct > localDrawoffIDVector();									// 抽取
	vector<DrawoffRecvStruct > localDrawoffVector();										// 抽卡
	vector<StoreListRecvStruct > localStoreVector();										//商店
	vector<BoxRecvStruct > localBoxVector();											// 宝箱
	vector<PointGainsStruct > localPointGainsVector();										/* 关卡收益 */
	vector<GeneralChipRecvStruct > localGeneralChipVector();								// 武将碎片合成
	vector<EquipChipRecvStruct > localEquipChipVector();									// 装备碎片合成
	vector<SkillNameStruct > localSkillNameVector();										// 技能基础表
	vector<SkillUpgradeStruct > localSkillUpgradeVector();									// 技能升级
	vector<GeneralEvoLocalStruct > localGeneralEvoVector();								// 武将进化本地
	vector<GeneralEvoExpLocalStruct > localGeneralEvoExpVector();							// 武将进化所提供经验本地
	vector<CustomsPassRecvStruct > interCustomsPassVector();							// 关卡（网络）
	vector<BuyCPLocalStruct > localBuyCPVector();										// 购买金币和体力	
	vector<GeneralUpgradeStruct > localGeneralUpgradeVector();							// 武将升级规则
	vector<TalentLocalStruct > localtalentVector();										// 天赋
	vector<TeamUpgradeLocalStrcut > localTeamUpgradeLocalVector();						// 战队升级
	vector<SkillAddPropty > localSkillAddProptyVec();										// 技能升级属性增加
	map<string, SkillRegionStruct > localSkillRegionMap();									// 角色技能范围
	map<string, SubInfoStruct > localSubInfoMap();										/* 人物副属性 */
	vector<DailyTaskLocalStruct > localDailyTaskVector();									// 每日任务
	vector<PvpDailyGainsStruct > localPvpDailyGainsVector();								/* 竞技场排名每日收益 */
	vector<PvpPkGainsStruct > localPvpPkGainsVector();									/* 竞技场对战收益 */
	vector<StoreLocalDataStruct > localStoreListDataVector();								// 商店物品基础表

	
	vector<AchievementLocalDataStruct> localAchievementListDataVector();					//获取成就数据

	vector<satrtGameStruct > localOnceGameVector();									//获得剧情字幕

	// 内部数据
	int userID;																	// 用户ID
	int playerID;																// 玩家ID
	
	// 第三方数据，在界面跳转信息传递
	int scrollType[ 2 ];															// 卷轴的类型（在仓库中使用）（0 == 卷轴ID，1 == 卷轴主键）
	int equipType;																// 武将详情点击装备的类型
	int i_scrollViewPos;															// 主界面滚动侧位置
	int finghtValue;																// 主界面计算的战斗力
	int teamLevel;																// 战队等级
	int teamExp;																// 战队经验
	vector<DrawoffGoodsStruct > drawoffGoodsVectorForDis;								// 此容器在抽取到卡牌显示时，在DrawoffDisplay类中调用
	vector<GeneralProptyStruct > reGeneralVector;										// 练兵场跳转详情
};