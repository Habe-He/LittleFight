/*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ�����   DataRecvEntities
** ��  �ڣ�   2015:3:25
** ˵  ����	���ݴӷ��������յ�����ƥ��
** ��  ����	
** ��  ʷ��	2015:3:25 ��ʼ�汾
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

// �����Ϣ
struct PlayerInfoRecvStruct
{
	char playerName[ 20 ];				// �������
	int level;							// �ȼ�
	int exp;							// ����
	int coinValue;						// ���
	int diamondValue;					// ��ʯ


	int playerID;						// ���ID
	int powerValue;						// ����
	int soulCount;						// ���ʯ��Ŀ
	int gongXun;						// ��ѫ��Ŀ
	int coinTimes;						// �����Ҵ���
	int powerTimes;						// ������������
};

struct SeriveAreaRecvStruct
{		
	short bigSmallClass[ 2 ];
	short validData[ 2 ];					// �����ܵ���Ч����
	char serviceCount;					// ����������
	int serviceID;						// ������ID
	char serviceNameValidData;			// ������������Ч����
	string serviceName;					// ����������
};

// װ��
struct EquipProptyStruct
{
	int ePKID;								// װ������ID
	int eID;								// װ��ID
	char eChinaName[ 20 ];					// ��������
	int eLevel;								// װ���ȼ�
	int ePositionType;						// װ����λ
	char ePositionName[ 10];					// ��λ����
	int eColor;								// װ����ɫ
	int eSellOut;							// װ���۸�
	int eExp;								// ����
	int eHP;								// ����Ѫ��
	int eAtk;								// ���ӹ�����
	int eMD;								// ���ӷ�������
	int ePD;								// �����������
	float eAddCrit;							// ���ӱ�������
	float eReduceCrit;						// ���ٱ�������
	int eAddRealHurt;						// ������ʵ�˺�
	int eReduceHurt;						// ������ʵ�˺�
	int eisSuit;								// �Ƿ�Ϊ��װ
	int eLevelLimit;							// װ���ȼ�����
	char eDes[ 200 ];						// װ������
};

// װ��Ʒ��
enum EquipGradeEnum
{
	EquipGradeWhite = 0,					// ��ɫ 
	EquipGradeGreen,						// ��ɫ
	EquipGradeBlue,							// ��ɫ
	EquipGradePurple,						// ��ɫ
	EquipGradeMax
};

// װ������
struct EquipRefineStruct
{
	int		eLevel;							// �ȼ�
	int		eExp[EquipGradeMax];			// ��ͬƷ�����辭��
	int		eCoin[EquipGradeMax];			// ��ͬƷ��������
	float	eGrow1[EquipGradeMax];			// ��ͬƷ�����Գɳ������䣩
	float	eGrow2[EquipGradeMax];			// ��ͬƷ�����Գɳ����챦��
};

// ����
struct SkillNameStruct
{
	int RoleID;								// ���ܶ�Ӧ����ID
	char sAName[ 15 ];						// ����һ��������
	char sBName[ 15 ];						// ���ܶ���������
	char sCName[ 15 ];						// ��������������
	char sDName[ 15 ];						// ��������������
	char sANameS[ 15 ];					// ����һƴ��
	char sBNameS[ 15 ];					// ���ܶ�ƴ��
	char sCNameS[ 15 ];					// ������ƴ��
	char sDNameS[ 15 ];					// ������ƴ��
	int sACD;								// ����һCD
	int sBCD;								// ���ܶ�CD
	int sCCD;								// ������CD
	int sDCD;								// ������CD
	float sAHurt;							// ����һ�˺�
	float sBHurt;							// ���ܶ��˺�
	float sCHurt;							// �������˺�
	float sDHurt;							// �������˺�
	char sADes[ 120 ];						// ����һ����
	char sBDes[ 120 ];						// ���ܶ�����
	char sCDes[ 120 ];						// ����������
	char sDDes[ 120 ];						// �����Ľ���
};

struct GeneralProptyStruct
{
	int roleID;							// ��ɫID
	char chinaName[20];					// ��������
	char chinaSmallName[20];				// ����ƴ������
	char country[4];						// ��������	
	int maxStar;						// ����Ǽ�
	int jobType;						// ְҵ����
	int evoLevel;						// ���׵ȼ�
	int nowStar;						// ��ǰ�Ǽ����������裩
	int levelLimit;						// ��������ȼ�
	int	evoLimit;						// �׼��ȼ�����
	int initAtk;							// ��ʼ������
	int atkGrowing;						// ����������
	int initHP;							// ��ʼѪ��
	int hpGrowing;						// Ѫ������
	int initPD;							// ��ʼ�������
	int pdGrowing;						// �����������
	int initMD;							// ��ʼ��������
	int mdGrowing;						// ������������
	float riseHP;						// ��Ѫ
	char g_des[500];					// ����
	int curStarLevel;					// �佫��ǰ�Ǽ�����������ã�
	int isSelect;						// �Ƿ�����1������0��Ϊ����
	float strongExp;						// ǿ������
	int evoExp;						// ��������
	int equipID[6];						// װ��������
	EquipProptyStruct equipPropty[ 6 ];		// װ������
	int level;							// ��ǰ�ȼ�	
	int PKID;							// �佫����ID
	int posFlag;						// (����)�佫��������Ӧ��λ��
	int skillLevel[ 4 ];					// ���ܵȼ�
};

// ���ؼ�������
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

// ��ȡ
struct DrawoffIDRecvStruct
{
	int cID;
	int wID;
	char wName[130];
};

// �鿨
struct DrawoffRecvStruct
{
	int goodsType;
	char idRange[15];
	char coinRange[15];
	char diamonRange[15];
};

// ����
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

/* �ؿ����� */
struct PointGainsStruct
{
	int		level;						/* �ʺŵȼ� */
	int		power[PointDiff_Max];		/* �������� */
	int		exp[PointDiff_Max];			/* �����ȡ */
	int		coin[PointDiff_Max];		/* ��һ�ȡ */
};

// �佫��Ƭ
struct GeneralChipRecvStruct
{
	int starLevel;
	int num;
};

// װ����Ƭ
struct EquipChipRecvStruct
{
	int color;
	int isSuit;
	int num;
};

// �ؿ�
struct CustomsPassRecvStruct
{
	int customsPassID;
	int customsPassStarCount;
};



struct PropProptyStruct
{
	int pID;
	char pChinaName[ 20 ];
	int pType;					// ��������
	int pExpAdd;
	int pPowerAdd;
	int pSellPrice;
	char pDes[ 300 ];
};

struct PointRole					/* �ؿ���ɫ */
{
	int		pID;
	int		room;					/* �ڼ����� */
	int		level;					/* �ȼ� */
	int		flag;					/* �Ƿ�boss */
};

struct PointBox						/* �ؿ����� */
{
	int		pID;
	int		num;
};

struct PointThing					/* �ؿ������Ʒ */
{
	int		pID;
	float	rate;					/* ��ü��� */
};

struct CheckPointStruct
{
	int cID;
	char *cName;					/* �ؿ��� */
	int cNameLen;					/* �ؿ������� */
	PointRole *cRoles;				/* �ؿ���ɫ */
	int cRoleNum;					/* �ؿ���ɫ�� */
	int cPower;						// ���ĵ�����
	PointBox cBox;					/* ���� */
	int cSoul;						// �ɻ�����ʯ����
	char *cMap;						/* �ؿ���ͼ */
	int cMapLen;					/* ��ͼ���� */
	char *cSong;					/* �ؿ�������Ч */
	char cSongLen;					/* ��Ч�ļ����� */
	PointThing *cThing;				// �ɻ�õ���Ʒ
	int cThingNum;					// �ɻ�õ���Ʒ����
	int cPill;						/* ������ */
	float cPillRate;				/* ��������ȡ���� */
	char *cDes;
	char cDesLen;
};

struct PointCellInfoStruct
{
	int pID;						/* �ؿ�ID */
	int	xLoc;						/* �ؿ������� */
	int yLoc;						/* �ؿ������� */
};

struct SignInStruct
{
	int sSignInDay;
	char sGoodsName[20];
	int sGoodsRes;						// ��Դ����
	int sGoodsType;					// ��Դ����
	char IDRange[ 20 ];					// ID��Χ
	int sNeedVip[10];					// VIP�ȼ���Ӧ��Ʒ����
};

struct WareroomCommonRecvStruct
{
	int itemsNum;					// �ֿ������Ŀ
	int itemPKID;					// ��Ʒ����ID
	int itemsID;					// ��ƷID
	int itemsCount;					// ��Ʒ����
	int itemsLevel;					// װ���ȼ�
	int isSelect;					// �Ƿ�ʹ�� 1 ʹ��    0 δʹ��
	int equipExp;					// װ������
};

struct ItemEquipStruct
{
	int iPKID;						// װ������ID
	int iID;						// װ��ID
	int iLv;						// װ���ȼ�
	int iExp;						// װ������
};
	
struct MaidanStruct		// �������ṹ��
{
	int generalCount;				// �佫����
	int generalPKID;				// ��������ID
	int generalType;					// ����ID
	int generalLevel	;				// ����ȼ�
	int generalStar;					// �����Ǽ�
	int isSelected;					// �����Ƿ�����1 = ��ս�� 0 = ����ս��
	int curStar;					// ��������ǰ�Ǽ���
	int generalExp;					// �佫����
	int evoLevel;					// ���׵ȼ�
	//int invalidMaxStar;				// ����Ǽ�
};

struct PointSetsRecvStruct
{
	int generalPKID;				// ��������ID
	int generalID;					// ����ID
	int generalLevel;				// ����ȼ�
	int generalStar;					// �����Ǽ�
	int evoLevel;					// ���׵ȼ�
	int generalPos;					// ����λ��
};

// �佫��ϸ���Խṹ��
struct GeneralDetailRecvStruct
{
	int strExp;						// ǿ������				
	int level;
	int starLevel;					// ��ǰ
	int evoExp;					// ��������
	int evoLevel;					// �����ȼ�
	int equipPKID[ 6 ];				// װ������ID
	int equipID[ 6 ];				// װ��ID
	int equipLevel[ 6 ];				// װ���ȼ�
	int equipExp[ 6 ];				// װ����������ֵ
	int skillLevel[ 4 ];				// �ĸ����ܵȼ�
};

// �����佫��������
struct GeneralEvoLocalStruct
{
	int maxStar;					// ��������Ǽ�
	int evoLevel;					// ���׵ȼ�
	int curStar;					// ��ǰ�Ǽ�
	int sameName;					// ͬ���佫����
	int addStar;					// �Ƿ��������
	int addEvo;					// �����ȼ�
	int levelLimit;					// ��������
	int needExp;					// ���辭��
	int needSoul;					// �������ʯ
	int needCoin;					// ������
};

// �佫����ʱ���ṩ����
struct GeneralEvoExpLocalStruct
{
	int maxStar;				// ����Ǽ�
	int curStar;				// ��ǰ�Ǽ�
	int pridExp;				// �ṩ�ľ���
};

// �����Һ�����
struct BuyCPLocalStruct
{
	int times;					// �������
	int ruleDP;					// ��ʯ���������ļ۸�
	int valuePower;				// ��ʯ��������������
	int ruleDC;				// ��ʯ�����ҵļ۸�
	int valueCoin;				// ��ʯ�����ҵ�����
};

// �츳
struct TalentLocalStruct
{
	int id;					// �츳���
	int type;					// �츳����
	int lightStar;				// �����Ǽ�Ҫ��
	int special;				// �����츳
	char talentName[ 20 ];		// �츳��������
	char resName[ 20 ];			// ��Դ����
	char des[ 100 ];			// �츳����
};

// ս����Ϣ
struct TeamInfoStruct
{
	int teamLevel;
	int teamExp;
};

// ս������
struct TeamUpgradeLocalStrcut
{
	int level;
	int needExp;
};

// �佫�������츳
struct GeneralLightStarTalentRecvStruct
{
	unsigned char conPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValid;
	unsigned char secondValid;
	unsigned char playerID[ 4 ];						// ���ID
	unsigned char generalPK[ 4 ];						// ��������
};

// ���״̬
struct PlayerStateRecvStruct
{
	int isFirstDrawoff;					// �Ƿ��ǵ�һ�γ鿨
	int coinDrawoffFree;					// �Ƿ���Խ����ѳ�
	int diamondDrawoffFree;				// �Ƿ������ʯ��ѳ�
	int isSignIn;						// �����Ƿ�ǩ��
	int guidePos;						// ����������λ��
	int refreshPVPTime;					// �У֣�ˢ�´���
	int signInTimes;						// ǩ��������
	int buyCoinTimes;					// �����Ҵ���
	int buyPowerTimes;					// ������������
	int refreshStoreTimes;              //�̵�ˢ�´���

	int coinDrawTimes;					// ��ҳ鿨����
	int diamondYear;					// ��ʯ��
	int diamondMonth;					// ��ʯ��
	int diamondDay;						// ��ʯ��
	int diamondHour;					// ��ʯʱ
	int diamondMin;						// ��ʯ��
	int diamondSec;						// ��ʯ��
};

// �鿨����ʱ
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

// ��������ǰʱ��
struct ServiceDayTimeRecvStruct
{
	int year;
	int mon;
	int day;
	int hour;
	int min;
	int sec;
};

// ���ѧ��buff��ȡ
struct JxxgBuffInfoRecvStruct
{
	int mode;								// ģʽ����
	int ticket;								// ��Ʊ
	int rewar;								// ����
	int num;								// buff����
};

// ��������������佫
struct PvpPlayerTeamRecvStruct
{
	int	pvpID;								// ���id
	int pvpPKID;							// ���pkid
};

// �����ȡ������5������
struct PvpCompetitorRecvStruct
{
	int	pvpID;								// ���id
	int pvpLv;								// ��ҵȼ�
	int pvpRank;							// ���pvp����
	char pvpName[20];						// �������
};

// ��������¼
struct PvpRecordRecvStruct
{
	int	pvpID;								// �Է�id
	int pvpWinLos;							// 0:��, 1:Ӯ
	int pvpUpDown;							// ���������½�
	int pvpRank;							// ����
	int pvpYear;							// ��
	int pvpMonth;							// ��
	int pvpDay;								// ��
	int pvpHour;							// ʱ
	int pvpMinute;							// ��
	int pvpSecond;							// ��
	char pvpName[20];						// �Է�����
	int pvpPower;							// �Է�ս����
	int pvpLv;								// �Է���ҵȼ�
};

// ������������¼
struct PvpRankRecvStruct
{
	int	pvpID;								// �Է�id
	int pvpLv;								// �Է���ҵȼ�
	char pvpName[20];						// �Է�����
	int pvpPower;							// �Է�ս����
};

// ���ܵȼ���Ӧ������������
struct SkillAddPropty
{
	int skillLevel;
	int eATK;				// �������ӹ�����
	int eAtkLen;			// 
	int eHP;				// ������������ֵ
	int eHPLen;			//
	int ePD;				// �������
	int ePDLen;			// 
	int eMD;				// ���Ƿ���
	int eMDLen;			//
	int dHP;				// ��������ֵ
	int dHPLen;			//
	int dPD;				// �������
	int dPDLen;			//
	int dMD;				// ���Ƿ���
	int dMDLen;			// 
	int cPD;				// �������
	int cPDLen;			// 
	int cMD;				// ���Ƿ���
	int cMDLen;			//
};

// ��ɫ���ܷ�Χ
struct SkillRegionStruct
{
	int		atk[2];			// �չ���һ����Χ
	int		atk2[2];		// �չ��ڶ�����Χ
	int		atk3[2];		// �չ���������Χ
	int		s1[2];			// ����һ��Χ
	int		s2[2];			// ���ܶ���Χ
	int		s3[2];			// ��������Χ
	int		s4[2];			// �����ķ�Χ
};

// ��ɫ������
struct SubInfoStruct
{
	float	anchorX;		// ê��x
	float	anchorY;		// ê��y
	float	speed;			// �ٶ�
};

// ����������ÿ������
struct PvpDailyGainsStruct
{
	int		rank;			// ����
	int		coin;			// ���
	int		exploit;		// ��ѫ
};

// ��������ս����
struct PvpPkGainsStruct
{
	int		rank;			// ����
	int		coin[2];		// ���
	int		exploit[2];		// ��ѫ
};

struct WareroomGridRecvStruct
{
	int propGridNum;
	int equipGridNum;
	int chipGridNum;
};

// ÿ������
struct DailyTaskLocalStruct
{
	int id;								// ���
	char taskName[ 60 ];					// ��������
	int dTimes;							// ִ�д���
	char diamondValue[ 10 ];					// ��ʯ��������
	char coinValue[ 10 ];					// ��ҽ�������
	char soulValue[ 10 ];					// ���ʯ--����
	char danValue[ 10 ];						// ������--����
	char comMadValue[ 10 ];					// ��ͨ����ҩˮ---����
	char powerValue[ 10 ];					// ����---����
	int teamExp;
};

struct StoreListRecvStruct
{
	int goodsID;					// ��ƷID
	StorePayType payType;			// ֧����ʽ
	int isBuy;						// �Ƿ����
};

// �̵���Ʒ
struct StoreLocalDataStruct
{
	char idRange[ 30 ];
	int goodType;
	int coinPrice;
	int diamondPrice;
};

//���سɾ�����
struct AchievementLocalDataStruct 
{
	int CID;				//���
	char CName[30];			//�ɾ�����
	char Condition[50];		//�ɾ�����
	int  num;	
	char Coin[10];			//�����Ʒ���ͺ�����
	char Diamond[10];		//��ʯ��Ʒ���ͺ�����
	char General[10];		//��������ID������
	char GeneralChip[10];	//������ƬID������
	int Dan;				//����������
	int Soul;				//���ʯ����
	int SimpleMad;			//��ͨ����ҩˮ����
	char WhiteEquip[10];	//��ɫװ��ID������
	char  WhiteSpecial[10];	//��ɫ����ID������
	int TeamExp;			//ս�Ӿ���ֵ
	
};
//�ɾ���ȡ״̬����
struct AchievementDataStruct 
{
	int corpsGrade;				//ս�ӳɾ���ȡ״̬
	int generalUpgrade[3];		//�佫�����ɾ���ȡ״̬
	int coins;				//��ҳɾ���ȡ״̬
	int daimonds;			//��ʯ�ɾ���ȡ״̬
	int customs[14];		//�ؿ��ɾ���ȡ״̬
	int warerooms;			//�ֿ�����ɾ���ȡ״̬
	int generalCollect[6];		//�佫�ռ��ɾ���ȡ״̬
	int jiXiaXueGong;		//���ѧ���ɾ���ȡ״̬
	int yiQiDangQian;		//һ�ﵱǧ�ɾ���ȡ״̬
	int isHp;				//���������ɾ���ȡ״̬
	int  generalStar[41];	//�佫���ǳɾ���ȡ״̬
	int arena;				//�������ɾ���ȡ״̬
	int skillUp;			//���������ɾ���ȡ״̬
	int getEquipment[4];	//���װ���ɾ���ȡ״̬
	int equipmentIndensify;	//װ��ǿ���ɾ���ȡ״̬
	int equipmentRefine;	//װ�������ɾ���ȡ״̬
	int patchCompose;		//��Ƭ�ϳɳɾ���ȡ״̬
};

//��һ�ν�����Ϸ����Ļ
struct satrtGameStruct
{
	char OpenStory[100];
};