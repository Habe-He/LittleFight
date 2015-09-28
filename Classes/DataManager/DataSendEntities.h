/*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ�����   DataEntities
** ��  �ڣ�   2015:3:20
** ˵  ����	���յ������ݵ�ʵ��
** ��  ����	
** ��  ʷ��	2015:3:20 ��ʼ�汾
*********************************************************************/
#pragma once
#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
using namespace std;

// �鿨����
enum CardEnum
{
	DrawoffWithNode,
	DrawoffWiteCoin,
	DrawoffWiteDiamond
};

// ��ȡ������Ʒ����
enum GoodsTypeEnum
{
	GoodsNone,
	GoodsProp,
	GoodsEquip,
	GoodsChip,
	GoodsGeneral,
	GoodsPower
};

// �ֿ��а�ť����
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
	unsigned char userID[ 4 ];						// ͨ����¼��ȡ���û�ID
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

// �鿨
struct DrawoffCardStruct
{
	unsigned char constPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValidData;
	unsigned char secondValidData;
	unsigned char playerID[ 4 ];					// ���ID
	unsigned char useCoin[ 4 ];					// ���Ľ������
	unsigned char useDiamond[ 4 ];				// ������ʯ����
	unsigned char iscCoin[ 4 ];					// �Ƿ�Ϊ���
	unsigned char isdDiamond[ 4 ];				// �Ƿ�Ϊ��ʯ
	unsigned char goodsCount[ 4 ];				// ��Ʒ��Ŀ
	unsigned char newBuffer[ 60 ];
};

struct WareroomCommonStruct
{
	unsigned char conPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValidData;
	unsigned char secondValidData;	
	unsigned char playerID[ 4 ];				// ���ID
	unsigned char gridNum[ 4 ];				// ������
	unsigned char diamond[ 4 ];				// ������ʯ
};

struct TeamInfoSendStruct
{
	unsigned char conPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValidData;
	unsigned char secondValidData;	
	unsigned char playerID[ 4 ];				// ���ID
};

struct PropUseStruct
{
	unsigned char conPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValidData;
	unsigned char secondValidData;
	unsigned char playerID[ 4 ];				// ���ID
	unsigned char propIndex;					// ��������ֵ�������������е������±꣩
};

struct ChipSynthStruct
{
	unsigned char conPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValidData;
	unsigned char secondValidData;
	unsigned char playerID[ 4 ];				// ���ID
	unsigned char chipIndex;					// ��������ֵ�������������е������±꣩
	unsigned char chipCount;					// ������Ƭ������
	unsigned char generalID[ 4 ];				// �ϳɽ����ID
};

struct WareroomSelloutStruct
{
	unsigned char conPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValidData;
	unsigned char secondValidData;
	unsigned char playerID[ 4 ];				// ���ID
	unsigned char chipIndex;					// ��������ֵ�������������е������±꣩
	unsigned char price[ 4 ];					// �۸�
};

struct PointSetInLineSend
{
	unsigned char conPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValidData;
	unsigned char secondValidData;
	unsigned char playerID[ 4 ];				// ���ID
	unsigned char generalIndex;				// ����ֵ�������������е������±꣩
	unsigned char generalPKID[ 4 ];			// ��������ID
};

struct PointSetCancelLineSend
{
	unsigned char conPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValidData;
	unsigned char secondValidData;
	unsigned char playerID[ 4 ];				// ���ID
	unsigned char generalIndex;				// ����ֵ�������������е������±꣩
	unsigned char generalPKID[ 4 ];			// ��������ID
	unsigned char newPKID[ 4 ];				// ��������ID
};

// ��ȡ����Ʒ�Ľṹ��
struct DrawoffGoodsStruct
{
	GoodsTypeEnum goodsType;
	int goodsID;
};

// ǩ��
struct SingInStruct
{
	unsigned char conPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValidData;
	unsigned char secondValidData;
	unsigned char playerID[ 4 ];					// ���ID
	unsigned char goodsID[ 4 ];					// ��ƷID
	unsigned char goodsType[ 4 ];					// ��Ʒ����
	unsigned char goodsNum[ 4 ];					// ��Ʒ����
	unsigned char day[ 4 ];						// �ڼ���
	unsigned char isVIP[ 4 ];						// �Ƿ���VIP��������������⣩
};

// �佫����
struct GeneralSendStruct
{
	unsigned char conpassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValid;
	unsigned char secondValid;
	unsigned char generalPK[ 4 ];
};

// �佫����װ�������Ϻ�ж�£�
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

// �佫ǿ��
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

// �佫����
struct GeneralRevoSendStruct
{
	unsigned char conPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValid;
	unsigned char secondValid;
	unsigned char generalPK[ 4 ];				// ������Ӣ������
	unsigned char useCoin[ 4 ];				// ���ĵĽ������
	unsigned char useSoul[ 4 ];				// �������ʯ����
	unsigned char curStar;					// ��ǰ�Ǽ�
	unsigned char evoLevel;					// ���׵ȼ�
	unsigned char playerID[ 4 ];				// ���ID
	unsigned char soulID[ 4 ];				// ���ʯID
	unsigned char maxStar[ 4 ];				// ��������Ǽ�
	unsigned char heroCount[ 4 ];				// ������Ӣ������
	unsigned char newBuffer[ 30 ];				
};

// �ؿ������Ʒ
struct CustomsPassGoodsSendStruct
{
	int goodsID;
	int goodsType;
	int goodsCount;
};

//
struct CustomsPassGeneral
{
	int generalPK;			// ��������
	int addExp;			// ���ӵľ���
	int level;				// �ȼ�
};
// �ؿ�ͨ��
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

// װ������
struct EquipRefineSendStruct
{
	unsigned char conPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValid;
	unsigned char secondValid;
	unsigned char playerID[ 4 ];
	unsigned char equipID[ 4 ];						// װ��ID
	unsigned char equipLevel[ 4 ];						// װ���ȼ�
	unsigned char equipNum[ 4 ];						// װ����Ŀ
	unsigned char newBuffer[ 1024 ];
};

// װ��ǿ������
struct EquipEnhanceSendStruct
{
	unsigned char conPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValid;
	unsigned char secondValid;
	unsigned char playerID[ 4 ];
	unsigned char equipID[ 4 ];						// װ��ID
	unsigned char equipLevel[ 4 ];						// װ���ȼ�
	unsigned char useCoin[ 4 ];						// ���Ľ��
};

struct ScrollEquipSendStruct
{
	unsigned char conPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValid;
	unsigned char secondValid;
	unsigned char playerID[ 4 ];
	unsigned char gainEquipID[ 4 ];						// ��õ�װ��ID
	unsigned char equipPK[ 16 ];							// ���ĵ�װ������
	unsigned char scrollPK[ 4 ];							// ���������
};

// ����װ��
struct ChangeEquipSendStruct
{
	unsigned char conPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValid;
	unsigned char secondValid;
	unsigned char generalID[ 4 ];						// ����ID
	unsigned char preEquipID[ 4 ];						// ԭװ��ID
	unsigned char NowEquipID[ 4 ];					// Ҫ���ϵ�װ��ID
	unsigned char posIndex;							// ��λ
};

// �����Һ�����
struct BuyCPSendStruct
{
	unsigned char conPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValid;
	unsigned char secondValid;
	unsigned char playerID[ 4 ];						// ���ID
	unsigned char diamond[ 4 ];						// ������ʯ
	unsigned char value[ 4 ];							// �����һ�����������
};

// ���ѧ��ͨ��
struct JxxgPassSendStruct
{
	unsigned char conPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValid;
	unsigned char secondValid;
	unsigned char playerID[ 4 ];						// ���ID
	unsigned char exp[ 4 ];								// ����
	unsigned char coin[ 4 ];							// ����
	unsigned char mode1[ 4 ];							// ģʽ1����
	unsigned char mode2[ 4 ];							// ģʽ2����
	unsigned char mode3[ 4 ];							// ģʽ3����
	unsigned char mode4[ 4 ];							// ģʽ4����
	unsigned char reward1[ 4 ];							// ����1
	unsigned char reward2[ 4 ];							// ����2
	unsigned char reward3[ 4 ];							// ����3
	unsigned char reward4[ 4 ];							// ����4
	unsigned char num1[ 4 ];							// �ؿ�����1
	unsigned char num2[ 4 ];							// �ؿ�����2
	unsigned char num3[ 4 ];							// �ؿ�����3
	unsigned char num4[ 4 ];							// �ؿ�����4
};

// ��ѯ��Ʒ
struct SortGoodsNumSendStruct
{
	unsigned char conPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValid;
	unsigned char secondValid;
	unsigned char playerID[ 4 ];						// ���ID
	unsigned char goodsID[ 4 ];						// ��ƷID
};

// �佫�����츳
struct GeneralLightStarTalentSendStruct
{
	unsigned char conPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValid;
	unsigned char secondValid;
	unsigned char playerID[ 4 ];						// ���ID
	unsigned char generalPK[ 4 ];						// ��������
	unsigned char talentID[ 4 ];						// �츳ID
};

// ��������
struct SkillUpgradeSendStruct
{
	unsigned char conPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValid;
	unsigned char secondValid;
	unsigned char generalPK[ 4 ];						// ��������
	unsigned char skillSA[ 4 ];						// �ȼ�
	unsigned char skillSB[ 4 ];						// �ȼ�
	unsigned char skillSC[ 4 ];						// �ȼ�
	unsigned char skillSD[ 4 ];						// �ȼ�
	unsigned char playerID[ 4 ];						// ��ңɣ�
	unsigned char useCoin[ 4 ];						// ���Ľ��
};

// ������ʯ
struct BuyDiamondSendStruct
{
	unsigned char conPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValid;
	unsigned char secondValid;
	unsigned char playerID[ 4 ];						// ���ID
	unsigned char diamondValue[ 4 ];					// ��ʯ��Ŀ
};

// ��ȡ���״̬
struct JxxgBuffInfoSendStruct
{
	unsigned char conPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValid;
	unsigned char secondValid;
	unsigned char playerID[ 4 ];						// ���ID
};

// ��ȡ���״̬
struct PlayerStateSendStruct
{
	unsigned char conPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValid;
	unsigned char secondValid;
	unsigned char playerID[ 4 ];						// ���ID
};

// ����������״̬
struct SetPlayerStateSendStruct
{
	unsigned char conPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValid;
	unsigned char secondValid;
	unsigned char playerID[ 4 ];						// ���ID
	unsigned char isFirstDrawoff;						// �Ƿ��ǵ�һ�γ鿨
	unsigned char isFreeDrawoff;						// �Ƿ���ѳ鿨
	unsigned char isSignIn;							// �Ƿ�ǩ��
	unsigned char pvpRefreshTimes;					// PVPˢ�´���
	unsigned char signInCount;						// ǩ��������
	unsigned char buyCoinTimes;					// �����Ҵ���
	unsigned char buyPowerTimes;						// ������������
};

// Pvp��Ϣ
struct PvpInfoSendStruct
{
	unsigned char conPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValid;
	unsigned char secondValid;
	unsigned char playerID[ 4 ];						// ���ID
};

// Pvpͨ��
struct PvpPassSendStruct
{
	unsigned char conPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValid;
	unsigned char secondValid;
	unsigned char ownID[ 4 ];							// ��Ҽ���ID
	unsigned char otherID[ 4 ];							// ��ҶԷ�ID
	unsigned char result[ 4 ];							// ���
};

// Pvp���������������佫
struct PvpWarriorsSetSendStruct
{
	unsigned char conPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValid;
	unsigned char secondValid;
	unsigned char playerID[ 4 ];						// ���ID
	unsigned char pkID1[4];								// �佫PKID1
	unsigned char pkID2[4];								// �佫PKID2
	unsigned char pkID3[4];								// �佫PKID3
	unsigned char pkID4[4];								// �佫PKID4
};

// �ֿ������
struct WareroomGridNum
{
	unsigned char conPassword[ 4 ];
	unsigned char bigClass;
	unsigned char smallClass;
	unsigned char firstValid;
	unsigned char secondValid;
	unsigned char playerID[ 4 ];
};

// �̵깺����Ʒ
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
