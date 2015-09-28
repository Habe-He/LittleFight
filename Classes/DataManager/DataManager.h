/*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ�����   DataManager
** ��  �ڣ�   2015:3:18
** ˵  ����	����������͡���������
** ��  ����	
** ��  ʷ��	2015:3:18 ��ʼ�汾
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "DataSendEntities.h"
#include "DataRecvEntities.h"
#include "ChineseCode/ChineseCode.h"
#include "Public/FontChina.h"
#include "UserInfo/UserData.h"
// ��ȡ�����ļ�ʹ��
#include "json/rapidjson.h"
#include "json/document.h"




USING_NS_CC;
using namespace std;

const int resCount = 4;				// ����Plist����
const int maxPvpRecord = 10;			// pvp��ս��¼��

class DataManager
{
public:
	DataManager();
	virtual ~DataManager();

	static DataManager* mpDataManager;		

	static DataManager* getInstance();

	vector<string> splitString(string str, string pattern);															// ���ݷָ����ָ��ַ���

	bool isLoginSuccess();																				// ��½��1��3��

	bool isGetPlayerInfo();																				// ��ȡ�����Ϣ��1��6��

	bool siSingIn(int goods_ID, int goodsType, int Num, int day, int isVIP);											// ǩ����1��7��

	bool isGetPlayerState();																				// ��ȡ���״̬��1��8��
	
	bool isBuyDiamond(int diamondCount);																	// ������ʯ��1��10��

	bool isDrawoffCard(int coin, int diamond, int isCoin, int isDiamond, vector<DrawoffGoodsStruct > drawoffStruct);				// �鿨�Ƿ�ɹ���2��1��

	bool isGetMaidan();																					// ��ȡ�������佫��Ϣ��2��2��

	int  isGetMaidanCount();																				// ��ȡ�������佫����

	bool isGetPointSets();																					// ��ȡ�㽫̨��Ϣ��2��3��

	bool isCancelTheLine(int generalIndex, int generalPKID);														// �佫����2��4��

	bool isChangeTheLine(int o_GeneralIndex, int o_GeneralPKID, int n_PKID);										// ������2��5��

	bool isGetGeneralProperty(int generalPK);																	// ��ȡ�佫���ԣ�2��6������Ϊ���������±�

	bool isDonSucceed(int generalPKID, int equipPKID, int posIndex);												// �佫����װ����2��7��

	bool isUnloadEquip(int generalPKID, int equipPKID, int posIndex);												// �佫ж��װ����2��8��

	bool isEnhanceGeneral(int generalPKID, int generalExp, int generalLevel, int propID);								// �佫ǿ����2��9��

	bool isRevoGeneral(int generalPKID, int curStar, int evoLevel, int evoExp, vector<int > pkIDHero, int useCoin, int useSoul);// �佫������2��10��

	bool isGetCustomsPass(int diff = 0, int cpID = -1);															// �ؿ���Ϣ��2��11��

	bool isCustomsPass(int teamAddExp, int gainCoin);															// �ؿ�ͨ�أ�2��12��

	bool isSetPointStarLv(int cpID, int star, bool *bReward);													/* ���ùؿ�ͨ���Ǽ� */

	bool isSetPointWarriorsLv(vector<CustomsPassGeneral> cpgs);														/* ����ͨ���佫�ȼ� */

	bool isSetPointGoods(std::vector<CustomsPassGoodsSendStruct> pointGoods);										/* ����ͨ����Ʒ */

	bool isBuyStoreThing( int goodsID, GoodsTypeEnum goodsType, int num, int price);									// �̵깺����Ʒ��2��13��

	bool isTalentLightStar(int generalPKID, int talentID, int pos);														// �佫�����츳��2��16��

	bool isGetTalentDate(int generalPKID);																	// ��ȡ�佫�����츳��2��17��

	bool isSelectGeneral(int posIndex, int generalPKID);															// �佫����2��19��

	bool isGetTeamInfo();																					// ��ȡս����Ϣ��2��20��

	bool isChangeEquip(int generalID, int prePK, int nowPK, int pos);												// ����װ����2��22��

	bool isBuyPower(int diamond, int power);																	// ����������2��23��

	bool isBuyCoin(int diamond, int coin);																	// �����ң�2��24��

	bool isJxxgPassSucceed(int exp, int coin, vector<JxxgBuffInfoRecvStruct > infos);									// ���ѧ��ͨ�� (2��25)

	bool isGetStoreList();																					// ��ȡ�̵���Ʒ�б� (2��26)

	bool isSkillUpgrade(int generalPK, int sa, int sb, int sc, int sd, int coin);											// ����������2��30��

	bool isGetJxxgBuffInfo();																				// ��ȡ���ѧ��buff��2��32��

	bool isDrawoffCountZero();																				// �鿨����ʱ��2��33��

	bool isRefreshStore(int diamondValue);																	// �ֶ�ˢ���̵꣨2��34��

	bool isCultivateGeneral(int gPKID, int coin, int diamond, int pillCount, int gAtk, int gHp, int gPd, int gMd);	// �佫����

	bool isGetGeneralGrowth(int gPKID);																		// ��ȡ�佫��������

	bool reSetTalent(int gPKID, int i_Diamond);																// �����츳

	bool isGetPropData();																					// ��ȡ���е������ݣ�3��1��

	bool isGetEquipData();																				// ��ȡ����װ����3��2��

	bool isGetEquipData(int PKID);																			/* ��ȡָ��װ����Ϣ */
	
	bool isGetChipData();																					// ��ȡ������Ƭ��3��3��

	bool isUnlockGridSucceed(WareroomEnum wareroomType, int grid, int diamond);									// �����ֿ�������Ƿ�ɹ���3��4/5/6 (���ߡ�װ������Ƭ)��

	bool isPropUseScceed(int propIndex);																		// ����ʹ�ã�3��7�����������е������±꣩

	bool isChipSynthScceed(int chipIndex, int chipNum, int itemID);												// ��Ƭ�ϳɣ�3��8�����������е������±꣩

	bool isSelloutEquipScceed(int equipIndex, int price);														// ����װ����3��10�����������е������±꣩

	bool isSelloutPropScceed(int propIndex, int price);															// �������ߣ�3��9�����������е������±꣩

	bool isRefineEquip(int equipID, int equipLevel, vector<int > equipVector, int useExped, int useCoin);		// ����װ����3��11��

	bool isSortGoodsNum(int goodsID);																		// ��ѯ��Ʒ������3��13��

	bool isEnhanceEquip(int equipID, int equipLevel, int coin);														// ǿ��װ����3��14��

	bool isSortWNum();																						// �ֿ����������Ʒ������3��15��
	
	int calcTeamLevle(int curExp);																			// ս�ӵ�ǰ�ȼ�

	int calcTeamExp(int curExp);																			// ս�ӵ�ǰʣ�ྭ��

	bool parserGoodsGains(GoodsTypeEnum goodsType, int goodsID, int num);									/* ������Ʒ��� */

	bool parseGoodsRemove(GoodsTypeEnum goodsType, int goodsID, int num = 1);								/* ������Ʒɾ�� */

	bool wealthUpdate(int coin, int diamond);																/* �Ƹ����� */
	
	bool goodsCountUpdate(int id, int count);																/* ��Ʒ����(ˢ�¿ɵ�����Ʒ����) */

	bool skillUnlock(int pkID, int level);																	/* �佫���ܽ��� */


	// ����������ݵĽṹ��
private:
	int goodsNum;														// ��ѯ��Ʒ����
	int pvpRank;														// Pvp����
	bool pvpResult;														// pvpͨ��
	std::vector<int >	generalGrowthVector;							/* �佫������������ */
	ItemEquipStruct		itemEquip;
	vector<SeriveAreaRecvStruct > serviceAreaRecvVector;						// ��ŷ������б���Ϣ	
	vector<MaidanStruct > maidanRecvVector;									// �������佫��Ϣ	
	vector<GeneralDetailRecvStruct > generalDetailRecvVector;						// �佫����	
	vector<PointSetsRecvStruct > pointSetRecvVector;							// �㽫̨	
	vector<WareroomCommonRecvStruct > wareroomPropVector;					// �ֿ��е���	
	vector<WareroomCommonRecvStruct > wareroomEquipVector;					// �ֿ���װ��	
	vector<WareroomCommonRecvStruct > wareroomChipVector;					// �ֿ�����Ƭ
	vector<CustomsPassRecvStruct > customsPassVector;							// �ؿ������磩
	vector<PlayerInfoRecvStruct > playerInfoVector;								// �����Ϣ�����磩
	vector<TeamInfoStruct > teamInfoVector;									// ս����Ϣ�����磩
	vector<int > interTalentVector;											// �佫�츳�����磩
	vector<PlayerStateRecvStruct > playerStateVector;							// ���״̬
	vector<DrawoffCountZeroRecvStruct > countZeroVector;						// �鿨����ʱ
	vector<ServiceDayTimeRecvStruct > serviceDayTimeVector;						// ��������ǰʱ��
	vector<JxxgBuffInfoRecvStruct > jxxgBuffVector;								// ���ѧ����Ϣ
	vector<PvpCompetitorRecvStruct > pvpCompetitorVector;						// ����������
	vector<PvpPlayerTeamRecvStruct > pvpPlayerTeamVector;						// ����������ս��
	vector<PvpRecordRecvStruct > pvpRecordVector;							// ��������ս��¼
	vector<PvpRankRecvStruct > pvpRankingVector;								// pvp���а�
	vector<WareroomGridRecvStruct > wareroomGridVector;						// �ֿ���Ʒ����������
	vector<StoreListRecvStruct > storeListVector;								// �̵���Ʒ

public:
	// ------------------------------- �����Ƕ�ȡ����Json�ļ� ---------- ʵ�ַ��� ----------- Begin ------------------- //
	void generalDataParser();														// �����佫��
	void generalUpgradeDataParser();												// �����佫���������
	void equipDataParser();														// ����װ����
	void equipRefineRule();														// ����װ����������
	void propDataParser();														// �������߱�
	void checkPointDataParser(int = 0);												// �����ؿ������: 0:��ͨ�ؿ���1:��Ӣ�ؿ�
	void pointCellInfoParse();														/* �����ؿ�ͼ����Ϣ */
	void jxxgDataParser();														// �������ѧ����
	bool signInDataParser();														// ����ǩ����				
	void DrawoffIDDataParser();													// ������ȡ��Ʒ�ı�	���鿨�ͱ��俪��������ID����ƷID�Ķ�Ӧ��
	void DrawoffDataParser();														// �����鿨��	
	void boxDataParser();														// ���������
	void pointGainsParse();														// �ؿ�����
	void generalChipDataParser();													// �佫��Ƭ�ϳ�
	void equipChipDataParser();													// װ����Ƭ�ϳ�
	void SkillNameDataParser();													// ��������
	void SkillUpgradeDataParser();													// ��������
	void GeneralEvoDataParser();													// �佫��������
	void GeneralEvoExpDataParser();												// �佫���������ṩ�ľ���
	void BuyCoinAndPower();														// �����Һ�����
	void talentDataParser();														// �츳
	void teamUpgradeDataParser();													// ս���������ݽ���
	void skillUpgradeProptyAdd();													// ����������Ӧ������������
	void skillRegionParser();														/* ���ܷ�Χ���� */
	void subInfoParser();															/* ���︱���Խ��� */
	void dailyTaskDateParser();													// ÿ���������ݽ���
	void PvpDailyGainsParser();													/* ����������ÿ������ */
	void PvpPkGainsParser();														/* ��������ս���� */
	void storeLocalDataParser();													// �����̵���Ʒ������Ϣ��

	void AchievementLocalDataParser();													//�����ɾ�����

	void OneStartGameStory();														//��һ�ν�����Ϸ�ľ������

	void encfile(const char *in_filename, char *pwd, const char *out_file);
	void decryptfile(const char *in_filename, char *pwd, const char *out_file);
private:
	vector<GeneralProptyStruct > generalProptyVector;									// �佫��������				
	vector<GeneralUpgradeStruct > generalUpgradeDataVector;								// �佫��������
	vector<EquipProptyStruct > equipProptyVector;										// װ��
	vector<EquipRefineStruct > equipRefineVector;										// װ����������
	vector<PropProptyStruct > propProptyVector;										// ���߻�������
	vector<CheckPointStruct > checkPointPropthVector;									// �ؿ���������
	vector<PointCellInfoStruct > pointCellInfoVector;										// �ؿ�ͼ����Ϣ����
	vector<SignInStruct > signInVector;												// ǩ������
	vector<DrawoffIDRecvStruct > drawoffIDVector;										// ��ȡ���鿨�ͱ��俪��������ID����ƷID�Ķ�Ӧ��
	vector<DrawoffRecvStruct > drawoffVector;											// �鿨
	vector<BoxRecvStruct > boxVector;												// ���俪����Ʒ
	vector<PointGainsStruct > pointGainsVector;										// �ؿ�����
	vector<GeneralChipRecvStruct > generalChipVector;									// �佫��Ƭ�ϳɹ���
	vector<EquipChipRecvStruct > equipChipVector;										// װ����Ƭ�ϳɹ���
	vector<SkillNameStruct > skillNameVector;											// ���ܱ�
	vector<SkillUpgradeStruct > skillUpgradeVector;										// ��������
	vector<GeneralEvoLocalStruct > generalEvoLocalVector;								// �佫��������
	vector<GeneralEvoExpLocalStruct > generalEvoExpLocalVector;							// �佫�������ṩ���鱾��
	vector<BuyCPLocalStruct > buyCPLocalVector;										// �����Һ��������ع���
	vector<TalentLocalStruct > talentLocalVector;										// �츳
	vector<TeamUpgradeLocalStrcut > teamUpgradeLocalVector;							// ս������
	vector<SkillAddPropty > localSkillAddProptyVector;									// ����������������
	map<std::string, SkillRegionStruct > skillRegionMap;									// ��ɫ���ܷ�Χ
	map<string, SubInfoStruct > subInfoMap;											/* ���︱���� */
	vector<DailyTaskLocalStruct > dailyTaskVector;										// ÿ������
	vector<PvpDailyGainsStruct > pvpDailyGainsVector;									/* ����������ÿ������ */
	vector<PvpPkGainsStruct > pvpPkGainsVector;										/* ��������ս���� */
	vector<StoreLocalDataStruct > localStoreDataVector;									// �̵���Ʒ������Ϣ��

	
	vector<AchievementLocalDataStruct> localAchievementDataVector;							// ����ɾ�����

	vector<satrtGameStruct > localOnceStartVector;									//��һ�ν�����Ϸ�ľ�����Ļ
	// ͨ�����º��������ڲ�����
public:
	int sortGoodsNum();															// ��ѯ��Ʒ����
	int curPvpRank();															// pvp����
	bool curPvpPass();															// pvpͨ��
	std::vector<int >	getGeneralGrowthVector();								/* �佫������������ */
	ItemEquipStruct interItemEquipStruct();										/* ��ȡָ��װ����Ϣ */
	vector<SeriveAreaRecvStruct > interSeriveAreaVector();								// �������б�	
	vector<MaidanStruct > interMaidanVector();											// �������佫��������
	vector<GeneralDetailRecvStruct > interGeneralVector();								// �佫����	
	vector<WareroomCommonRecvStruct > interWareroomPropVector();						// �ֿ��е�����������	
	vector<WareroomCommonRecvStruct > interWareroomEquipVector();						// �ֿ���װ����������	
	vector<WareroomCommonRecvStruct > interWareroomChipVector();						// �ֿ�����Ƭ��������
	vector<PointSetsRecvStruct > interPointSetsVector();									// �㽫̨��������	
	vector<PlayerInfoRecvStruct > interPlayerInfoVector();									// �����Ϣ��������
	vector<TeamInfoStruct > interTeamInfoVector();										// ս����Ϣ
	vector<int > interTalentVectors();												// �佫���츳
	vector<PlayerStateRecvStruct > interPlayerStateVector();								// ���״̬
	vector<DrawoffCountZeroRecvStruct > interCountZeroVector();							// ����ʱ
	vector<ServiceDayTimeRecvStruct > interDayTimesVector();								// ��������ǰʱ��
	vector<JxxgBuffInfoRecvStruct > interJxxgBuffVector();									// ��ȡ���ѧ����Ϣ
	vector<PvpCompetitorRecvStruct > interPvpCompetitorVector();						// ��ȡ��ȡ����������
	vector<PvpPlayerTeamRecvStruct > interPvpPlayerTeamVector(int id);					// ����������ս��
	vector<PvpRecordRecvStruct > interPvpRecordVector();								// ��������ս��¼
	vector<PvpRankRecvStruct > interPvpRankingVector();									// pvp���а�
	vector<WareroomGridRecvStruct > interWareroomVector();								// �ֿ���Ʒ������

	vector<PropProptyStruct > localPropProptyVector();									// ���߻�������	
	vector<GeneralProptyStruct > localGeneralProptyVector();								// �佫��������	
	vector<EquipProptyStruct > localEquipProptyVector();									// װ����������	
	vector<EquipRefineStruct > localEquipRefineVector();									// װ����������
	vector<CheckPointStruct > localCheckPointVector();									// �ؿ���������
	vector<PointCellInfoStruct > localPointCellInfoVector();							// �ؿ�ͼ����Ϣ����
	vector<SignInStruct > localSignInVector();											// ǩ������
	vector<DrawoffIDRecvStruct > localDrawoffIDVector();									// ��ȡ
	vector<DrawoffRecvStruct > localDrawoffVector();										// �鿨
	vector<StoreListRecvStruct > localStoreVector();										//�̵�
	vector<BoxRecvStruct > localBoxVector();											// ����
	vector<PointGainsStruct > localPointGainsVector();										/* �ؿ����� */
	vector<GeneralChipRecvStruct > localGeneralChipVector();								// �佫��Ƭ�ϳ�
	vector<EquipChipRecvStruct > localEquipChipVector();									// װ����Ƭ�ϳ�
	vector<SkillNameStruct > localSkillNameVector();										// ���ܻ�����
	vector<SkillUpgradeStruct > localSkillUpgradeVector();									// ��������
	vector<GeneralEvoLocalStruct > localGeneralEvoVector();								// �佫��������
	vector<GeneralEvoExpLocalStruct > localGeneralEvoExpVector();							// �佫�������ṩ���鱾��
	vector<CustomsPassRecvStruct > interCustomsPassVector();							// �ؿ������磩
	vector<BuyCPLocalStruct > localBuyCPVector();										// �����Һ�����	
	vector<GeneralUpgradeStruct > localGeneralUpgradeVector();							// �佫��������
	vector<TalentLocalStruct > localtalentVector();										// �츳
	vector<TeamUpgradeLocalStrcut > localTeamUpgradeLocalVector();						// ս������
	vector<SkillAddPropty > localSkillAddProptyVec();										// ����������������
	map<string, SkillRegionStruct > localSkillRegionMap();									// ��ɫ���ܷ�Χ
	map<string, SubInfoStruct > localSubInfoMap();										/* ���︱���� */
	vector<DailyTaskLocalStruct > localDailyTaskVector();									// ÿ������
	vector<PvpDailyGainsStruct > localPvpDailyGainsVector();								/* ����������ÿ������ */
	vector<PvpPkGainsStruct > localPvpPkGainsVector();									/* ��������ս���� */
	vector<StoreLocalDataStruct > localStoreListDataVector();								// �̵���Ʒ������

	
	vector<AchievementLocalDataStruct> localAchievementListDataVector();					//��ȡ�ɾ�����

	vector<satrtGameStruct > localOnceGameVector();									//��þ�����Ļ

	// �ڲ�����
	int userID;																	// �û�ID
	int playerID;																// ���ID
	
	// ���������ݣ��ڽ�����ת��Ϣ����
	int scrollType[ 2 ];															// ��������ͣ��ڲֿ���ʹ�ã���0 == ����ID��1 == ����������
	int equipType;																// �佫������װ��������
	int i_scrollViewPos;															// �����������λ��
	int finghtValue;																// ����������ս����
	int teamLevel;																// ս�ӵȼ�
	int teamExp;																// ս�Ӿ���
	vector<DrawoffGoodsStruct > drawoffGoodsVectorForDis;								// �������ڳ�ȡ��������ʾʱ����DrawoffDisplay���е���
	vector<GeneralProptyStruct > reGeneralVector;										// ��������ת����
};