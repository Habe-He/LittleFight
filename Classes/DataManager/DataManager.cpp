#include "DataManager.h"
#include "Sqlite3/DBUtil.h"

const char constPwd = 88;			// 通信固定密码
const char constHeartBeat = 65;		// 心跳自动发送数据
const string DOT = ",";

// int 进制
const int constint = 256;

DataManager* DataManager::mpDataManager = NULL;

DataManager::DataManager()
	: goodsNum( 0 )
	, i_scrollViewPos( 0 )
	, finghtValue( 0 )
	, teamExp( 0 )
	, teamLevel( 0 )
{
	
}

DataManager::~DataManager()
{
	CC_SAFE_DELETE(mpDataManager);
	serviceAreaRecvVector.clear();	
	generalProptyVector.clear();
}

DataManager* DataManager::getInstance()
{	
	if (!mpDataManager)
	{
		mpDataManager = new DataManager();
	}
	return mpDataManager;
}

vector<string> DataManager::splitString(string str, string pattern)
{
	//CCASSERT( str.size() > 0, " split String First String Not NULL"); // 断言描述，当传过来的字符串为空的时候执行断言
	string::size_type pos;
	vector<string > resultString;
	str += pattern;
	for (unsigned int i = 0; i < str.size(); i ++)
	{
		pos = str.find(pattern, i);
		if (pos < (unsigned)str.size())
		{
			string passString = str.substr(i, pos -i);
			resultString.push_back(passString);
			i = pos + pattern.size() - 1;
		}
	}
	return resultString;
}

bool DataManager::isLoginSuccess()
{
	bool bRef = true;

	DBUtil::getInstance()->CreateTable_Player();
	DBUtil::getInstance()->CreateTable_Item();
	DBUtil::getInstance()->CreateTable_GeneralGrowth();
	DBUtil::getInstance()->CreateTable_GeneralMain();
	DBUtil::getInstance()->CreateTable_GeneralSkill();
	DBUtil::getInstance()->CreateTable_GeneralEquip();
	DBUtil::getInstance()->CreateTable_GeneralTalent();
	DBUtil::getInstance()->CreateTable_Point();
	DBUtil::getInstance()->CreateTable_Jxxg();
//	DBUtil::getInstance()->CreateTable_Achievement();

	return bRef;
}

bool DataManager::isGetPlayerInfo()
{
	bool bRet = false;

	std::string strSql = "Select * From " + DBUtil::getInstance()->getTableName(Table_Player);
	auto vct = DBUtil::getInstance()->searchData(strSql);
	if (0 < vct.size())
	{
		bRet = true;
		auto itr = vct[0];

		playerInfoVector.clear();
		PlayerInfoRecvStruct playerInfo = {0};
		
		memcpy(playerInfo.playerName, itr["name"].c_str(), itr["name"].length());
		playerInfo.level = atoi(itr["level"].c_str());
		playerInfo.exp = atoi(itr["exp"].c_str());
		playerInfo.coinValue = atoi(itr["coin"].c_str());
		playerInfo.diamondValue = atoi(itr["diamond"].c_str());
		if (true == isSortGoodsNum(93018))
		{
			playerInfo.soulCount = goodsNum;
		}

		playerInfoVector.push_back(playerInfo);
	}

	return bRet;
}

bool DataManager::siSingIn(int goods_ID, int goodsType, int Num, int day, int isVIP)
{
	bool bRef = false;
	return bRef;
}

bool DataManager::isGetPlayerState()
{
 	bool bRef = true;
// 	PlayerStateSendStruct playerState;
// 	memset(&playerState, 0, sizeof(playerState));
// 	for (int i = 0; i < 4; i ++)
// 	{
// 		playerState.conPassword[ i ] = constPwd;
// 	}
// 	playerState.bigClass = 1;
// 	playerState.smallClass = 8;
// 	playerState.firstValid = 0;
// 	playerState.secondValid = 4;
// 	vector<unsigned char > playerVector = reverseCalcUserID( playerID );
// 	for (int i = 0; i < 4; i ++)
// 	{
// 		playerState.playerID[ i ] = playerVector[ i ];
// 	}
// 	CSuperSocket::getInstance()->Send( (char*)&playerState, sizeof(playerState) );
// 
// 	char res[ 22 ] = { 0 };
// 	CSuperSocket::getInstance()->Recv(res, 22);
// 	PlayerStateRecvStruct playerRecvState;
// 	memset(&playerRecvState, 0, sizeof(playerRecvState));
// 	playerStateVector.clear();
// 
// 	playerRecvState.isFirstDrawoff = res[ 4 ];
// 	playerRecvState.coinDrawoffFree = res[ 5 ];
// 	playerRecvState.diamondDrawoffFree = res[ 6 ];
// 	playerRecvState.isSignIn = res[ 7 ];
// 	playerRecvState.guidePos = res[ 8 ];
// 	playerRecvState.refreshPVPTime = res[ 9 ];
// 	playerRecvState.signInTimes = res[ 10 ];
// 	playerRecvState.buyCoinTimes = res[ 11 ];
// 	playerRecvState.buyPowerTimes = res[ 12 ];
// 	playerRecvState.refreshStoreTimes = res[ 13 ];
// 	playerRecvState.diamondDrawoffFree = res[ 14 ];
// 	playerRecvState.diamondYear = res[ 15 ];
// 	playerRecvState.diamondMonth = res[ 16 ];
// 	playerRecvState.diamondDay = res[ 17 ];
// 	playerRecvState.diamondHour = res[ 18 ];
// 	playerRecvState.diamondMin = res[ 19 ];
// 	playerRecvState.diamondSec = res[ 20 ];
// 	playerStateVector.push_back(playerRecvState);
	return bRef;
}

bool DataManager::isBuyDiamond(int diamondCount)
{
	return wealthUpdate(0, diamondCount);
}

bool DataManager::isDrawoffCard(int coin, int diamond, int isCoin, int isDiamond, vector<DrawoffGoodsStruct > drawoffStruct)
{
	bool bRef = false;
	
	
	string strSql = "";
	unsigned int index = 0;

	if (drawoffIDVector.size() == 0)
	{
		DrawoffIDDataParser();
	}

	for (index = 0;index < drawoffStruct.size();index++)			/* 修改物品数据 */
	{
		auto goods = drawoffStruct[index];
		auto goodsID = drawoffIDVector[goods.goodsID - 90001].wID;
		if (false == parserGoodsGains(goods.goodsType, goodsID, 1))
		{
			break;
		}
	}

	if (index < drawoffStruct.size())
	{
		return bRef;
	}

	bRef = wealthUpdate(coin * -1, diamond * -1);					/* 修改帐号金币经验 */

	return bRef;
}

bool DataManager::isGetMaidan()
{
	bool bRef = false;
	
	string strSql = "Select * From " + DBUtil::getInstance()->getTableName(Table_gMain);	

	auto result = DBUtil::getInstance()->searchData(strSql);

	maidanRecvVector.clear();

	unsigned int iIndex = 0;
	for (iIndex = 0;iIndex < result.size();iIndex++)
	{
		auto itr = result[iIndex];

		MaidanStruct maidan = {0};
		maidan.generalCount = result.size();

		maidan.generalPKID = atoi(itr["PKID"].c_str());				/* PKID */
		maidan.generalType = atoi(itr["ID"].c_str());				/* ID */
		maidan.curStar = atoi(itr["star"].c_str());					/* 星级 */
		maidan.generalLevel = atoi(itr["level"].c_str());			/* 等级 */
		maidan.generalExp = atoi(itr["lExp"].c_str());				/* 强化经验 */
		maidan.evoLevel = atoi(itr["step"].c_str());				/* 进阶等级 */
		maidan.isSelected = atoi(itr["appoint"].c_str());			/* 任命 */
		skillUnlock(maidan.generalPKID, maidan.generalLevel);

		maidanRecvVector.push_back(maidan);
	}

	if ((iIndex == result.size()) && (0 != iIndex))
	{
		bRef = true;
	}

	return bRef;
}

int DataManager::isGetMaidanCount()
{
	string strSql = "Select Count(*) From " + DBUtil::getInstance()->getTableName(Table_gMain);
	return DBUtil::getInstance()->searchDataCount(strSql);
}

bool DataManager::isGetPointSets()
{
	bool bRef = false;
	
	string strSql = "Select * From " + DBUtil::getInstance()->getTableName(Table_gMain) + " Where appoint <> 0 Order by appoint";
	auto result = DBUtil::getInstance()->searchData(strSql);

	pointSetRecvVector.clear();

	unsigned int iIndex = 0;
	for (iIndex = 0;iIndex < result.size();iIndex++)
	{
		auto itr = result[iIndex];

		PointSetsRecvStruct pointSet = {0};
		pointSet.generalPKID = atoi(itr["PKID"].c_str());			/* PKID */
		pointSet.generalID = atoi(itr["ID"].c_str());				/* ID */
		pointSet.generalStar = atoi(itr["star"].c_str());			/* 星级 */
		pointSet.generalLevel = atoi(itr["level"].c_str());			/* 等级 */
		pointSet.evoLevel = atoi(itr["step"].c_str());				/* 进阶等级 */
		pointSet.generalPos = atoi(itr["appoint"].c_str());			/* 上阵位置 */
		skillUnlock(pointSet.generalPKID, pointSet.generalLevel);

		pointSetRecvVector.push_back(pointSet);
	}

	if ((iIndex == result.size()) && (0 != iIndex))
	{
		bRef = true;
	}
	
	return bRef;
}

bool DataManager::isCancelTheLine(int generalIndex, int generalPKID)
{
	bool bRef = false;

	stringstream stream;
	stream << "Update " << DBUtil::getInstance()->getTableName(Table_gMain) << " Set appoint = 0 " << "Where PKID = " << generalPKID;
	string strSql = stream.str();
	
	bRef = DBUtil::getInstance()->updateData(strSql);
	
	return bRef;
}

bool DataManager::isChangeTheLine(int o_GeneralIndex, int o_GeneralPKID, int n_PKID)
{
	bool bRef = false;
	
	stringstream stream;
	stream << "Update " << DBUtil::getInstance()->getTableName(Table_gMain) << " Set appoint = 0 " << "Where PKID = " << o_GeneralPKID;
	string strSql = stream.str();

	if (true == DBUtil::getInstance()->updateData(strSql))
	{
		stream.str("");
		stream << "Update " << DBUtil::getInstance()->getTableName(Table_gMain) << " Set appoint = " << o_GeneralIndex << " Where PKID = " << n_PKID;
		strSql = stream.str();

		bRef = DBUtil::getInstance()->updateData(strSql);
	}

	return bRef;
}

bool DataManager::isGetGeneralProperty(int generalPK)
{
	bool bRef = false;
	
	stringstream stream;
	stream << "Select * From " << DBUtil::getInstance()->getTableName(Table_gMain) << " m, "
		<< DBUtil::getInstance()->getTableName(Table_gEquip) << " e, "
		<< DBUtil::getInstance()->getTableName(Table_gSkill) << " s "
		<< "Where m.PKID = e.PKID and m.PKID = s.PKID and m.PKID = " << generalPK;
	string strSql =  stream.str();

	auto result = DBUtil::getInstance()->searchData(strSql);

	generalDetailRecvVector.clear();

	if (0 < result.size())
	{
		auto itr = result[0];
		GeneralDetailRecvStruct generalDetail = {0};

		generalDetail.starLevel = atoi(itr["star"].c_str());		/* 星级 */
		generalDetail.level = atoi(itr["level"].c_str());			/* 等级 */
		generalDetail.strExp = atoi(itr["lExp"].c_str());			/* 强化经验 */
		generalDetail.evoLevel = atoi(itr["step"].c_str());			/* 进阶等级 */
		generalDetail.evoExp = atoi(itr["sExp"].c_str());			/* 进化经验 */

		for (int jIndex = 0; jIndex < 6; jIndex ++)
		{
			stringstream stream;
			stream << "equip" << jIndex + 1;
			string str = stream.str();

			auto pkID = atoi(itr[str].c_str());
			generalDetail.equipPKID[jIndex] = pkID;

			stream.str("");
			stream << "Select * From " << DBUtil::getInstance()->getTableName(Table_Item) << " Where PKID = " << pkID;
			strSql = stream.str();									/* 查询该装备等级 */

			auto value = DBUtil::getInstance()->searchData(strSql);
			if (0 < value.size())
			{
				generalDetail.equipID[jIndex] = atoi(value[0]["ID"].c_str());
				generalDetail.equipLevel[jIndex] = atoi(value[0]["level"].c_str());	
				generalDetail.equipExp[jIndex] = atoi(value[0]["exp"].c_str());	
			}		
		}

		for (int jIndex = 0; jIndex < 4; jIndex ++)
		{
			stringstream stream;
			stream << "lv" << jIndex + 1;
			string str = stream.str();

			generalDetail.skillLevel[jIndex] = atoi(itr[str].c_str());
		}

		generalDetailRecvVector.push_back(generalDetail);

		bRef = true;
	}

	return bRef;
}

bool DataManager::isDonSucceed(int generalPKID, int equipPKID, int posIndex)
{
	bool bRef = false;
	
	stringstream stream;
	stream << "Update " << DBUtil::getInstance()->getTableName(Table_gEquip) <<
		" Set equip" << posIndex + 1 << " = " << equipPKID << " Where PKID = " << generalPKID;
	auto strSql = stream.str();

	if (true == DBUtil::getInstance()->updateData(strSql))
	{
		stream.str("");
		stream << "Update " << DBUtil::getInstance()->getTableName(Table_Item) << " Set isSelect = 1" << " Where PKID = " << equipPKID;
		strSql = stream.str();
		bRef = DBUtil::getInstance()->updateData(strSql);
	}

	return bRef;
}

bool DataManager::isUnloadEquip(int generalPKID, int equipPKID, int posIndex)
{
	bool bRef = false;

	stringstream stream;
	stream << "Update " << DBUtil::getInstance()->getTableName(Table_gEquip) <<
		" Set equip" << posIndex + 1 << " = 0" << " Where PKID = " << generalPKID;
	auto strSql = stream.str();

	if (true == DBUtil::getInstance()->updateData(strSql))
	{
		stream.str("");
		stream << "Update " << DBUtil::getInstance()->getTableName(Table_Item) << " Set isSelect = 0" << " Where PKID = " << equipPKID;
		strSql = stream.str();

		bRef = DBUtil::getInstance()->updateData(strSql);
	}

	return bRef;
}

bool DataManager::isEnhanceGeneral(int generalPKID, int generalExp, int generalLevel, int propID)
{
	bool bRef = false;

	stringstream stream;
	stream << "Update " << DBUtil::getInstance()->getTableName(Table_gMain) <<
		" Set level = " << generalLevel << ", lExp = " << generalExp << " Where PKID = " << generalPKID;
	auto strSql = stream.str();

	if (true == DBUtil::getInstance()->updateData(strSql))
	{
		bRef = goodsCountUpdate(propID, -1);
	}

	return bRef;
}

bool DataManager::isRevoGeneral(int generalPKID, int curStar, int evoLevel, int evoExp, vector<int > pkIDHero, int useCoin, int useSoul)
{
	bool bRef = false;

	stringstream stream;
	stream << "Update " << DBUtil::getInstance()->getTableName(Table_gMain) <<
		" Set step = " << evoLevel << ", sExp = " << evoExp << ", star = " << curStar << " Where PKID = " << generalPKID;
	auto strSql = stream.str();

	if (false == DBUtil::getInstance()->updateData(strSql))
	{
		return bRef;
	}

	if (false == wealthUpdate(-1 * useCoin, 0))				/* 金币消耗 */
	{
		return bRef;
	}

	for (unsigned int index = 0;index < pkIDHero.size(); index++)
	{
		auto pkID = pkIDHero[index];
		if (false == parseGoodsRemove(GoodsGeneral, pkID))
		{
			return bRef;
		}
	}

	bRef = goodsCountUpdate(93018, -1 * useSoul);			/* 刷新灵魂石数量 */

	return bRef;
}

/* diff: 0:普通关卡，1:精英关卡 cpID: -1取符合难度的所有关卡信息，其它取指定关卡信息 */
bool DataManager::isGetCustomsPass(int diff, int cpID)
{
	bool bRef = false;

	string strSql = "";
	if (-1 == cpID)
	{
		string limit = (0 == diff) ? "<" : ">=";
		strSql = "Select * From " + DBUtil::getInstance()->getTableName(Table_Point) + " Where ID " + limit + " 2000 Order by ID";
	}
	else
	{
		stringstream stream;
		stream << "Select * From " << DBUtil::getInstance()->getTableName(Table_Point) << " Where ID = " << cpID + (diff + 1) * 1000;
		strSql = stream.str();
	}
	auto result = DBUtil::getInstance()->searchData(strSql);

	customsPassVector.clear();
	unsigned int index = 0;
	for (index = 0;index < result.size();index++)
	{
		auto itr = result[index];
		CustomsPassRecvStruct customsPass = {0};

		customsPass.customsPassID = atoi(itr["ID"].c_str());
		customsPass.customsPassStarCount = atoi(itr["star"].c_str());
		
		customsPassVector.push_back(customsPass);
	}

	if ((index == result.size()) && (0 != index))
	{
		bRef = true;
	}

	return bRef;
}

bool DataManager::isCustomsPass(int teamAddExp, int gainCoin)
{
	bool bRef = false;

	string strSql = "Select exp, coin From " + DBUtil::getInstance()->getTableName(Table_Player);
	auto result = DBUtil::getInstance()->searchData(strSql);

	if (0 < result.size())										/* 修改帐号金币经验 */
	{
		auto itr = result[0];
		auto exp = atoi(itr["exp"].c_str()) + teamAddExp;
		auto coin = atoi(itr["coin"].c_str()) + gainCoin;

		stringstream stream;
		stream << "Update " << DBUtil::getInstance()->getTableName(Table_Player) << " Set exp = " << exp << ", coin = " << coin;
		strSql = stream.str();

		bRef = DBUtil::getInstance()->updateData(strSql);
	}

	return bRef;
}

bool DataManager::isSetPointStarLv(int cpID, int star, bool *bReward)
{
	bool bRet = false;
	
	stringstream stream;
	stream << "Select * From " << DBUtil::getInstance()->getTableName(Table_Point) << " Where ID = " << cpID;
	string strSql = stream.str();

	auto result = DBUtil::getInstance()->searchData(strSql);
	if (0 == result.size())											/* 首次通关 */
	{
		if (3 == star)
		{
			*bReward = wealthUpdate(0, 10);							/* 奖励10钻 */
		}
		stream.str("");
		stream << "Insert Into " << DBUtil::getInstance()->getTableName(Table_Point) << " Values(" << cpID << ", " << star << ")";
		string strSql = stream.str();
		bRet = DBUtil::getInstance()->insertData(strSql);
	}
	else
	{
		auto itr = result[0];
		auto numStar = atoi(itr["star"].c_str());
		if ((3 == star) && (3 != numStar))							/* 当前未达到3星，且本次获得3星 */
		{
			*bReward = wealthUpdate(0, 10);							/* 奖励10钻 */
		}

		stream.str("");
		stream << "Update " << DBUtil::getInstance()->getTableName(Table_Point) << " Set star = " << star << " Where ID = " << cpID;
		strSql = stream.str();

		bRet = DBUtil::getInstance()->updateData(strSql);
	}

	return bRet;
}

bool DataManager::isSetPointWarriorsLv(vector<CustomsPassGeneral> cpgs)
{
	bool bRet = false;

	stringstream stream;
	string strSql = "";
	unsigned int index = 0;
	for (index = 0;index < cpgs.size();index++)						/* 修改武将数据 */
	{
		auto general = cpgs[index];

		stream.str("");
		stream << "Update " << DBUtil::getInstance()->getTableName(Table_gMain) <<
			" Set level = " << general.level << ", lExp = " << general.addExp << " Where PKID = " << general.generalPK;
		strSql = stream.str();

		if (false == DBUtil::getInstance()->updateData(strSql))
		{
			return false;
		}
	}

	if ((index == cpgs.size()) && (0 != index))
	{
		bRet = true;
	}

	return bRet;
}

bool DataManager::isSetPointGoods(std::vector<CustomsPassGoodsSendStruct> pointGoods)
{
	bool bRet = false;

	unsigned int index = 0;
	for (index = 0;index < pointGoods.size();index++)				/* 修改物品数据 */
	{
		auto goods = pointGoods[index];
		if (false == parserGoodsGains((GoodsTypeEnum)goods.goodsType, goods.goodsID, goods.goodsCount))
		{
			break;
		}
	}

	if ((index == pointGoods.size()) && (0 != index))
	{
		bRet = true;
	}

	return bRet;
}

bool DataManager::isBuyStoreThing( int goodsID, GoodsTypeEnum goodsType, int num, int price)
{
	bool bRef = false;
	
	if (true == wealthUpdate(0, -1 * price))
	{
		bRef = parserGoodsGains(goodsType, goodsID, num);

		if (false == bRef)
		{
			wealthUpdate(0, price);									/* 购买失败，还钱 */
		}
	}

	return true;
}

bool DataManager::isTalentLightStar(int generalPKID, int talentID, int pos)
{
	bool bRef = false;
	
	stringstream stream;
	stream << "Update " << DBUtil::getInstance()->getTableName(Table_gTalent) << " Set talent" << pos + 1 <<
		" = " << talentID << " Where PKID = " << generalPKID;
	string strSql = stream.str();
	bRef = DBUtil::getInstance()->updateData(strSql);

	return bRef;
}

bool DataManager::isGetTalentDate(int generalPKID)
{
	bool bRef = true;
	
	stringstream stream;
	stream << "Select talent1, talent2, talent3, talent4 From " << DBUtil::getInstance()->getTableName(Table_gTalent) << " Where PKID = " << generalPKID;
	string strSql = stream.str();

	auto result = DBUtil::getInstance()->searchData(strSql);
	if (0 < result.size())
	{
		interTalentVector.clear();

		auto itr = result[0];
		interTalentVector.push_back(atoi(itr["talent1"].c_str()));
		interTalentVector.push_back(atoi(itr["talent2"].c_str()));
		interTalentVector.push_back(atoi(itr["talent3"].c_str()));
		interTalentVector.push_back(atoi(itr["talent4"].c_str()));

		bRef = true;
	}

	return bRef;
}

bool DataManager::isSelectGeneral(int posIndex, int generalPKID)
{
	bool bRef = false;

	stringstream stream;
	stream << "Update " << DBUtil::getInstance()->getTableName(Table_gMain) << " Set appoint = "<< posIndex << " Where PKID = " << generalPKID;
	string strSql = stream.str();

	bRef = DBUtil::getInstance()->updateData(strSql);

	return bRef;
}

bool DataManager::isGetTeamInfo()
{
	bool bRef = true;
	
	stringstream stream;
	stream << "Select exp From " << DBUtil::getInstance()->getTableName(Table_Player);
	string strSql = stream.str();

	auto result = DBUtil::getInstance()->searchData(strSql);
	if (0 < result.size())
	{
		auto itr = result[0];
		auto exp = atoi(itr["exp"].c_str());

		TeamInfoStruct teamInfo = {0};
		teamInfoVector.clear();
		teamInfo.teamExp = exp;

		teamUpgradeDataParser();
		teamUpgradeLocalVector = localTeamUpgradeLocalVector();

		teamInfo.teamLevel = calcTeamLevle(teamInfo.teamExp);
		teamInfoVector.push_back(teamInfo);

		bRef = true;
	}

	return bRef;
}

bool DataManager::isChangeEquip(int generalID, int prePK, int nowPK, int pos)
{
	bool bRef = false;
	
	stringstream stream;
	stream << "Update " << DBUtil::getInstance()->getTableName(Table_Item) << " Set isSelect = 0" << " Where PKID = " << prePK;
	string strSql = stream.str();

	if (false == DBUtil::getInstance()->updateData(strSql))			/* 修改旧装备标记 */
	{
		return bRef;
	}
	
	stream.str("");
	stream << "Update " << DBUtil::getInstance()->getTableName(Table_Item) << " Set isSelect = 1" << " Where PKID = " << nowPK;
	strSql = stream.str();

	if (false == DBUtil::getInstance()->updateData(strSql))			/* 修改新装备标记 */
	{
		return bRef;
	}

	stream.str("");
	stream << "Update " << DBUtil::getInstance()->getTableName(Table_gEquip) << " Set equip" << pos + 1 << " = " << nowPK << " Where PKID = " << generalID;
	strSql = stream.str();

	bRef = DBUtil::getInstance()->updateData(strSql);				/* 修改武将装备PKID */

	return bRef;
}

bool DataManager::isBuyPower(int diamond, int power)
{
	bool bRef = false;
	return bRef;
}

bool DataManager::isBuyCoin(int diamond, int coin)
{
	bool bRef = false;

	bRef = wealthUpdate(coin, -1 * diamond);

	return bRef;
}

bool DataManager::isJxxgPassSucceed(int exp, int coin, vector<JxxgBuffInfoRecvStruct > infos)
{
	bool bRef = false;

	stringstream stream;
	string strSql = "";
	unsigned int index = 0;
	for (index = 0;index < infos.size();index ++)
	{
		auto buff = infos[index];
		stream.str("");

		auto reward = infos[index].rewar;
		auto times = infos[index].num;

		stream.str("");
		stream << "Update " << DBUtil::getInstance()->getTableName(Table_Jxxg) << " Set reward = " << reward << " and times = " << times << " Where Mode = " << index;
		strSql = stream.str();
		if (false == DBUtil::getInstance()->updateData(strSql))
		{
			break;
		}
	}

	if ((index == infos.size()) && (0 != index))
	{
		bRef = true;
	}

	return bRef;
}

bool DataManager::isGetStoreList()
{
	bool bRef = false;
	return bRef;
}

bool DataManager::isSkillUpgrade(int generalPK, int sa, int sb, int sc, int sd, int coin)
{
	bool bRef = false;
	
	if (true == wealthUpdate(-1 * coin, 0))
	{		
		stringstream stream;
		stream << "Update " << DBUtil::getInstance()->getTableName(Table_gSkill) << " Set lv1 = " << sa << 
			", lv2 = " << sb << ", lv3 = " << sc << ", lv4 = " << sd << " Where PKID = " << generalPK;
		auto strSql = stream.str();

		bRef = DBUtil::getInstance()->updateData(strSql);
	}

	return bRef;
}

bool DataManager::isGetJxxgBuffInfo()
{
	bool bRef = true;

	stringstream stream;
	stream << "Select * From " << DBUtil::getInstance()->getTableName(Table_Jxxg);
	auto strSql = stream.str();
	auto result = DBUtil::getInstance()->searchData(strSql);

	jxxgBuffVector.clear();
	for (unsigned int index = 0;index < result.size();index++)
	{
		auto itr = result[index];
		JxxgBuffInfoRecvStruct jxxgBuff = {0};

		jxxgBuff.mode = atoi(itr["mode"].c_str());
		jxxgBuff.ticket = atoi(itr["ticket"].c_str());
		jxxgBuff.rewar = atoi(itr["reward"].c_str());
		jxxgBuff.num = atoi(itr["times"].c_str());

		jxxgBuffVector.push_back(jxxgBuff);

		bRef = true;
	}

	return bRef;
}

bool DataManager::isDrawoffCountZero()
{
	bool bRef = false;
	return bRef;
}

bool DataManager::isRefreshStore(int diamondValue)
{
	bool bRef = false;
	return bRef;
}

bool DataManager::isCultivateGeneral(int gPKID, int coin, int diamond, int pillCount, int gAtk, int gHp, int gPd, int gMd)
{
	bool bRef = true;

	if (false == wealthUpdate(coin * -1, -1 * diamond))
	{
		return bRef;
	}

	if (false == goodsCountUpdate(93019, pillCount * -1))
	{
		return bRef;
	}

	stringstream stream;
	stream << "Select atk, hp, pd, md From " << DBUtil::getInstance()->getTableName(Table_gGrowth) << " Where PKID = " << gPKID;
	string strSql = stream.str();
	auto result = DBUtil::getInstance()->searchData(strSql);

	if (0 < result.size())
	{
		auto itr = result[0];
		auto atk = atoi(itr["atk"].c_str()) + gAtk;
		auto hp = atoi(itr["hp"].c_str()) + gHp;
		auto pd = atoi(itr["pd"].c_str()) + gPd;
		auto md = atoi(itr["md"].c_str()) + gMd;

		stream.str(""); 
		stream << "Update " << DBUtil::getInstance()->getTableName(Table_gGrowth) << " Set atk = " << atk << 
			", hp = " << hp << ", pd = " << pd << ", md = " << md << " Where PKID = " << gPKID;
		strSql = stream.str();
		bRef = DBUtil::getInstance()->updateData(strSql);
	}

	return bRef;
}

bool DataManager::isGetGeneralGrowth(int gPKID)
{
	bool bRet = false;

	stringstream stream;
	stream << "Select atk, hp, pd, md From " << DBUtil::getInstance()->getTableName(Table_gGrowth) << " Where PKID = " << gPKID;
	auto strSql = stream.str();

	auto result = DBUtil::getInstance()->searchData(strSql);
	if (0 <= result.size())
	{
		bRet = true;
		auto itr = result[0];
		generalGrowthVector.clear();
		generalGrowthVector.push_back(atoi(itr["atk"].c_str()));
		generalGrowthVector.push_back(atoi(itr["hp"].c_str()));
		generalGrowthVector.push_back(atoi(itr["pd"].c_str()));
		generalGrowthVector.push_back(atoi(itr["md"].c_str()));
	}

	return bRet;
}

bool DataManager::reSetTalent(int gPKID, int i_Diamond)
{
	bool bRef = true;

	stringstream stream;
	stream << "Update " << DBUtil::getInstance()->getTableName(Table_gTalent) 
		<< " Set (talent1, talent2, talent3, talent4) = Vaules ( 0, 0, 0, 0 ) Where ID = " << gPKID;
	auto sqlString = stream.str();
	DBUtil::getInstance()->updateData(sqlString);

	stream.str("");
	sqlString.clear();
	stream << " Select diamond From " << DBUtil::getInstance()->getTableName(Table_Player);
	sqlString = stream.str();
	auto vct = DBUtil::getInstance()->searchData(sqlString);
	int count = 0;
	if (0 < vct.size())
	{
		auto itr = vct[ 0 ];
		count = atoi(itr["diamond"].c_str());
	}

	stream.str("");
	sqlString.clear();
	stream << "Update " << DBUtil::getInstance()->getTableName(Table_Player) << " Set diamond =  " << count - i_Diamond;
	sqlString = stream.str();
	DBUtil::getInstance()->updateData(sqlString);

	return bRef;
}

bool DataManager::isGetPropData()
{
	bool bRef = true;
	
	stringstream stream;
	stream << "Select * From " << DBUtil::getInstance()->getTableName(Table_Item) << " Where type = " << GoodsProp;
	string strSql = stream.str();

	auto vct = DBUtil::getInstance()->searchData(strSql);
	if (0 < vct.size())
	{
		bRef = true;	

		wareroomPropVector.clear();
		for (unsigned int i = 0; i < vct.size(); i ++)
		{	
			stringstream stream2;
			stream2 << "Select propGrid From " << DBUtil::getInstance()->getTableName(Table_Player) ;
			string strSql2 = stream2.str();

			auto vct2 = DBUtil::getInstance()->searchData(strSql2);

			WareroomCommonRecvStruct wareroomPropRecvStruct = {0};

			int count = 0;
			if (0 < vct2.size())
			{
				auto itr = vct2[ 0 ];
				wareroomPropRecvStruct.itemsNum = atoi(itr["propGrid"].c_str());
			}				
			wareroomPropRecvStruct.itemPKID = atoi(vct[ i ][ "PKID" ].c_str());
			wareroomPropRecvStruct.itemsID = atoi(vct[ i ][ "ID" ].c_str());
			wareroomPropRecvStruct.itemsCount = atoi(vct[ i ][ "count" ].c_str());

			wareroomPropVector.push_back(wareroomPropRecvStruct);	
		}		
	}
	else
	{
		stringstream stream2;
		stream2 << "Select propGrid From " << DBUtil::getInstance()->getTableName(Table_Player) ;
		string strSql2 = stream2.str();

		auto vct = DBUtil::getInstance()->searchData(strSql2);

		WareroomCommonRecvStruct wareroomPropRecvStruct = {0};

		int count = 0;
		if (0 < vct.size())
		{
			auto itr = vct[ 0 ];
			wareroomPropVector.clear();
			wareroomPropRecvStruct.itemsNum = atoi(itr["propGrid"].c_str());
			wareroomPropVector.push_back(wareroomPropRecvStruct);	
		}
	}
	return bRef;
}

bool DataManager::isGetEquipData()
{
	bool bRef = false;

	stringstream stream;
	stream << "Select * From " << DBUtil::getInstance()->getTableName(Table_Item) << " Where type = " << GoodsEquip;
	string strSql = stream.str();

	auto vct = DBUtil::getInstance()->searchData(strSql);
	if (0 < vct.size())
	{
		bRef = true;		

		wareroomEquipVector.clear();
		for (unsigned int i = 0; i < vct.size(); i ++)
		{		
			stringstream stream2;
			stream2 << "Select euipGrid From " << DBUtil::getInstance()->getTableName(Table_Player) ;
			string strSql2 = stream2.str();

			auto vct2 = DBUtil::getInstance()->searchData(strSql2);

			WareroomCommonRecvStruct wareroomEquipRecvStruct = {0};

			int count = 0;
			if (0 < vct2.size())
			{
				auto itr = vct2[ 0 ];
				wareroomEquipRecvStruct.itemsNum = atoi(itr["euipGrid"].c_str());
			}

			wareroomEquipRecvStruct.itemPKID = atoi(vct[ i ][ "PKID" ].c_str());
			wareroomEquipRecvStruct.itemsID = atoi(vct[ i ][ "ID" ].c_str());

			wareroomEquipRecvStruct.isSelect = atoi(vct[ i ][ "isSelect" ].c_str());
			wareroomEquipRecvStruct.itemsCount = atoi(vct[ i ][ "count " ].c_str());
			wareroomEquipRecvStruct.itemsLevel = atoi(vct[ i ][ "level" ].c_str());
			wareroomEquipRecvStruct.equipExp = atoi(vct[ i ][ "exp" ].c_str());

			wareroomEquipVector.push_back(wareroomEquipRecvStruct);	
		}
	}
	else
	{
		stringstream stream2;
		stream2 << "Select euipGrid From " << DBUtil::getInstance()->getTableName(Table_Player) ;
		string strSql2 = stream2.str();

		auto vct = DBUtil::getInstance()->searchData(strSql2);

		WareroomCommonRecvStruct wareroomPropRecvStruct = {0};

		int count = 0;
		if (0 < vct.size())
		{
			bRef = true;
			auto itr = vct[ 0 ];
			wareroomEquipVector.clear();
			wareroomPropRecvStruct.itemsNum = atoi(itr["euipGrid"].c_str());
			wareroomEquipVector.push_back(wareroomPropRecvStruct);	
		}
	}
	return bRef;
}

bool DataManager::isGetEquipData(int PKID)
{
	bool bRef = false;

	stringstream stream;
	stream << "Select * From " << DBUtil::getInstance()->getTableName(Table_Item) << " Where type = " << GoodsEquip << " and PKID = " << PKID;
	string strSql = stream.str();

	auto result = DBUtil::getInstance()->searchData(strSql);

	if (0 < result.size())
	{
		bRef = true;

		auto itr = result[0];
		memset(&itemEquip, 0, sizeof(ItemEquipStruct));
		itemEquip.iPKID = atoi(itr["PKID"].c_str());
		itemEquip.iID = atoi(itr["ID"].c_str());
		itemEquip.iLv = atoi(itr["level"].c_str());
		itemEquip.iExp = atoi(itr["exp"].c_str());
	}

	return bRef;
}

bool DataManager::isGetChipData()
{
	bool bRef = true;

	stringstream stream;
	stream << "Select * From " << DBUtil::getInstance()->getTableName(Table_Item) << " Where type = " << GoodsChip;
	string strSql = stream.str();

	auto vct = DBUtil::getInstance()->searchData(strSql);
	if (0 < vct.size())
	{
		bRef = true;

		wareroomChipVector.clear();

		stringstream stream2;
		stream2 << "Select chipGrid From " << DBUtil::getInstance()->getTableName(Table_Player) ;
		string strSql2 = stream2.str();

		auto vct2 = DBUtil::getInstance()->searchData(strSql2);

		WareroomCommonRecvStruct wareroomChipRecvStruct = {0};

		int count = 0;
		if (0 < vct2.size())
		{
			auto itr = vct2[ 0 ];
			wareroomChipRecvStruct.itemsNum = atoi(itr["chipGrid"].c_str());
		}

		for (unsigned int i = 0; i < vct.size(); i ++)
		{
			wareroomChipRecvStruct.itemPKID = atoi(vct[ i ][ "PKID" ].c_str());
			wareroomChipRecvStruct.itemsID = atoi( vct[ i ][ "ID" ].c_str() );
			wareroomChipRecvStruct.itemsCount = atoi( vct[ i ][ "count" ].c_str() );

			wareroomChipVector.push_back(wareroomChipRecvStruct);	
		}		
	}
	else
	{
		stringstream stream2;
		stream2 << "Select chipGrid From " << DBUtil::getInstance()->getTableName(Table_Player) ;
		string strSql2 = stream2.str();

		auto vct = DBUtil::getInstance()->searchData(strSql2);

		WareroomCommonRecvStruct wareroomPropRecvStruct = {0};

		int count = 0;
		if (0 < vct.size())
		{
			auto itr = vct[ 0 ];
			wareroomChipVector.clear();
			wareroomPropRecvStruct.itemsCount = atoi(itr["chipGrid"].c_str());
			wareroomChipVector.push_back(wareroomPropRecvStruct);	
		}
	}
	return bRef;
}

bool DataManager::isUnlockGridSucceed(WareroomEnum wareroomType, int grid, int diamond)
{
	bool bRef = false;
	string sqlString = "";
	string selectString = "";

	if (wareroomType == 4)
	{
		stringstream stream2;
		stream2 << "Select propGrid From " << DBUtil::getInstance()->getTableName(Table_Player) ;
		selectString = stream2.str();

		auto vct = DBUtil::getInstance()->searchData(selectString);
		int count = 0;
		if (0 < vct.size())
		{
			auto itr = vct[ 0 ];
			count = atoi(itr["propGrid"].c_str());
		}

		stringstream stream;
		stream << "Update " << DBUtil::getInstance()->getTableName(Table_Player) << " Set propGrid = " << grid + count;
		sqlString = stream.str();
	}
	else if ( wareroomType == 5 )
	{
		stringstream stream2;
		stream2 << "Select euipGrid From " << DBUtil::getInstance()->getTableName(Table_Player) ;
		selectString = stream2.str();

		auto vct = DBUtil::getInstance()->searchData(selectString);
		int count = 0;
		if (0 < vct.size())
		{
			auto itr = vct[ 0 ];
			count = atoi(itr["euipGrid"].c_str());
		}

		stringstream stream;
		stream << "Update " << DBUtil::getInstance()->getTableName(Table_Player) << " Set euipGrid = " << grid + count;
		sqlString = stream.str();
	}
	else if ( wareroomType == 6 )
	{
		stringstream stream2;
		stream2 << "Select chipGrid From " << DBUtil::getInstance()->getTableName(Table_Player) ;
		selectString = stream2.str();

		auto vct = DBUtil::getInstance()->searchData(selectString);
		int count = 0;
		if (0 < vct.size())
		{
			auto itr = vct[ 0 ];
			count = atoi(itr["chipGrid"].c_str());
		}

		stringstream stream;
		stream << "Update " << DBUtil::getInstance()->getTableName(Table_Player) << " Set chipGrid = " << grid + count;
		sqlString = stream.str();
	}

	stringstream stream2;
	stream2 << "Select diamond From " << DBUtil::getInstance()->getTableName(Table_Player) ;
	selectString = stream2.str();

	auto vct = DBUtil::getInstance()->searchData(selectString);
	int count = 0;
	if (0 < vct.size())
	{
		auto itr = vct[ 0 ];
		count = atoi(itr["diamond"].c_str());
	}

	stringstream stream;
	stream << "Update " << DBUtil::getInstance()->getTableName(Table_Player) << " Set diamond = " << count - diamond;
	auto sqlString2 = stream.str();

	DBUtil::getInstance()->updateData(sqlString2);

	bRef = DBUtil::getInstance()->updateData(sqlString);

	return bRef;
}

bool DataManager::isPropUseScceed(int propIndex)
{
	bool bRef = false;
	
	bRef = parseGoodsRemove(GoodsProp, propIndex);

	return bRef;
}

bool DataManager::isChipSynthScceed(int chipIndex, int chipNum, int itemID)
{
	bool bRef = false;
	
	if (false == parseGoodsRemove(GoodsChip, chipIndex, chipNum))
	{
		return bRef;
	}

	auto type = (itemID < 93001) ? GoodsGeneral : GoodsEquip;
	bRef = parserGoodsGains(type, itemID, 1);

	return bRef;
}

bool DataManager::isSelloutEquipScceed(int equipIndex, int price)
{
	bool bRef = false;

	stringstream sqlStream1;
	sqlStream1 << "Delete From " << DBUtil::getInstance()->getTableName(Table_Item) << " Where PKID = " << equipIndex;
	string sqlString1 = sqlStream1.str();

	if (false == parseGoodsRemove(GoodsEquip, equipIndex))
	{
		return bRef;
	}

	bRef = wealthUpdate(price, 0);

	return bRef;
}

bool DataManager::isSelloutPropScceed(int propIndex, int price)
{
	bool bRef = false;

	if (false == parseGoodsRemove(GoodsProp, propIndex))
	{
		return bRef;
	}

	bRef = wealthUpdate(price, 0);

	return bRef;
}

bool DataManager::isRefineEquip(int equipID, int equipLevel, vector<int > equipVector, int useExped, int useCoin)
{
	bool bRef = false;

	stringstream streamUpdate;										// 更新装备表
	streamUpdate << "Update " << DBUtil::getInstance()->getTableName(Table_Item) << 
		" Set level = " << equipLevel << ", exp = " << useExped << " Where PKID = " << equipID;
	string updateString = streamUpdate.str();
	if (false == DBUtil::getInstance()->updateData( updateString ))
	{
		return bRef;
	}
	
	if (false == wealthUpdate(-1 * useCoin, 0))
	{
		return bRef;
	}
		
	unsigned int i = 0;
	for (i = 0; i < equipVector.size(); i ++)
	{
		if (false == parseGoodsRemove(GoodsEquip, equipVector[i]))	// 去掉消耗掉的装备
		{
			return bRef;
		}
	}

	if ((i == equipVector.size()) && (0 != i))
	{
		bRef = true;
	}

	return bRef;
}

bool DataManager::isSortGoodsNum(int goodsID)
{
	bool bRef = true;
	stringstream stream;
	stream << "Select count From " << DBUtil::getInstance()->getTableName(Table_Item) << " Where ID = " << goodsID;
	string sqlString = stream.str();
	auto goodsVector = DBUtil::getInstance()->searchData(sqlString);
	if (0 < goodsVector.size())
	{
		auto itr = goodsVector[0];
		goodsNum = atoi(itr["count"].c_str());

		bRef = true;
	}
	else
	{
		goodsNum = 0;
	}

	return bRef;
}

bool DataManager::isEnhanceEquip(int equipID, int equipLevel, int coin)
{
	bool bRef = false;
	
	if (true == wealthUpdate(-1 * coin, 0))
	{
		stringstream stream;		
		stream << "Update " << DBUtil::getInstance()->getTableName(Table_Item) << " Set level = " << equipLevel << " Where PKID = " << equipID;
		string strSql = stream.str();
		bRef = DBUtil::getInstance()->updateData(strSql);
	}
	
	return bRef;
}

bool DataManager::isSortWNum()
{
	bool bRef = true;

	string strSql = "Select propGrid, euipGrid, chipGrid From " + DBUtil::getInstance()->getTableName(Table_Player);
	auto gridRes = DBUtil::getInstance()->searchData(strSql);
	auto itr = gridRes[0];											// 查询道具、装备、碎片总格子
	int pCount = atoi( itr["propGrid"].c_str() );
	int eCount = atoi( itr["euipGrid"].c_str() );
	int cCount = atoi( itr["chipGrid"].c_str() );
	
	stringstream streamProp;
	streamProp << "Select Count(*) From " << DBUtil::getInstance()->getTableName(Table_Item) << " Where type = " << 1;
	string sPropString = streamProp.str();
	auto iPropValue = DBUtil::getInstance()->searchDataCount(sPropString);	// 查询道具行数
	
	stringstream streamEquip;
	streamEquip << " Select Count(*) From " << DBUtil::getInstance()->getTableName(Table_Item) << " Where type = " << 2 << " and isSelect = " << 0;
	string sEquipString = streamEquip.str();
	auto iEquipValue = DBUtil::getInstance()->searchDataCount(sEquipString);// 查询装备行数
	
	stringstream streamChip;
	streamChip << " Select Count(*) From " << DBUtil::getInstance()->getTableName(Table_Item) << " Where type = " << 3;
	string sChipString = streamChip.str();
	auto iChipValue = DBUtil::getInstance()->searchDataCount(sChipString);	// 查询碎皮行数

	WareroomGridRecvStruct wareroomRecv;
	memset(&wareroomRecv, 0, sizeof(wareroomRecv));
	wareroomGridVector.clear();
	wareroomRecv.propGridNum = pCount - iPropValue;
	wareroomRecv.equipGridNum = eCount - iEquipValue;
	wareroomRecv.chipGridNum = cCount - iChipValue;
	wareroomGridVector.push_back(wareroomRecv);

	return bRef;
}

int DataManager::calcTeamLevle(int curExp)
{
	int result = 1;
	for (unsigned int i = 0; i < teamUpgradeLocalVector.size(); i ++)
	{
		if (curExp >= teamUpgradeLocalVector[ i ].needExp)
		{
			curExp -= teamUpgradeLocalVector[ i ].needExp;	
			result ++;
		}
	}
	return result;
}

int DataManager::calcTeamExp(int curExp)
{
	int result = curExp;
	for (unsigned int i = 0; i < teamUpgradeLocalVector.size(); i ++)
	{
		if (curExp >= teamUpgradeLocalVector[ i ].needExp)
		{
			curExp -= teamUpgradeLocalVector[ i ].needExp;	
			result = curExp;
		}
	}
	return result;
}

bool DataManager::parserGoodsGains(GoodsTypeEnum goodsType, int goodsID, int num)
{
	bool bRef = false;

	stringstream stream;
	string strSql = "";
	if (GoodsEquip == goodsType)									/* 装备直接插入数据 */
	{
		stream.str();
		stream << "Insert Into " << DBUtil::getInstance()->getTableName(Table_Item) << " Values (NULL, " << goodsID << ", " << goodsType << ", 0, " << num << ", 0, 0)";
		strSql = stream.str();

		bRef = DBUtil::getInstance()->insertData(strSql);
	}
	else if (GoodsGeneral == goodsType)
	{
		stream.str("");
		stream << "Insert Into " << DBUtil::getInstance()->getTableName(Table_gMain) << " Values (NULL, " << goodsID << ", 1, 1, 0, 0, 0, 0)";
		strSql = stream.str();
		if (false == DBUtil::getInstance()->insertData(strSql))
		{
			return bRef;
		}

		stream.str(""); 
		stream << "Insert Into " << DBUtil::getInstance()->getTableName(Table_gGrowth) << " Values (NULL, " << goodsID << ", 0, 0, 0, 0)";
		strSql = stream.str();
		if (false == DBUtil::getInstance()->insertData(strSql))
		{
			return bRef;
		}

		stream.str("");
		stream << "Insert Into " << DBUtil::getInstance()->getTableName(Table_gSkill) << " Values (NULL, " << goodsID << ", 1, 0, 0, 0)";
		strSql = stream.str();
		if (false == DBUtil::getInstance()->insertData(strSql))
		{
			return bRef;
		}

		stream.str("");
		stream << "Insert Into " << DBUtil::getInstance()->getTableName(Table_gEquip) << " Values (NULL, " << goodsID << ", 0, 0, 0, 0, 0, 0)";
		strSql = stream.str();
		if (false == DBUtil::getInstance()->insertData(strSql))
		{
			return bRef;
		}

		stream.str("");
		stream << "Insert Into " << DBUtil::getInstance()->getTableName(Table_gTalent) << " Values (NULL, " << goodsID << ", 0, 0, 0, 0)";
		strSql = stream.str();
		bRef = DBUtil::getInstance()->insertData(strSql);
	}
	else /*if ((GoodsProp == goodsType) || (GoodsChip == goodsType))*/
	{
		if ((93005 <= goodsID) && (93007 >= goodsID))				/* 宝箱直接插入数据 */
		{
			stream.str("");
			stream << "Insert Into " << DBUtil::getInstance()->getTableName(Table_Item) << " Values (NULL, " << goodsID << ", " << goodsType << ", 0, 1, 0, 0)";
			strSql = stream.str();

			bRef = DBUtil::getInstance()->insertData(strSql);
		}
		else
		{
			if (true == isSortGoodsNum(goodsID))
			{
				if (0 < goodsNum)									/* 有存货更新数量 */
				{
					auto count = goodsNum + num ;

					stream.str("");
					stream << "Update " << DBUtil::getInstance()->getTableName(Table_Item) << " Set count = " << count << " Where ID = " << goodsID;
					strSql = stream.str();

					bRef = DBUtil::getInstance()->updateData(strSql);
				}
				else												/* 无存货 */
				{
					stream.str("");
					stream << "Insert into " << DBUtil::getInstance()->getTableName(Table_Item) << " Values (NULL, " << goodsID << ", " << goodsType << ", 0, " << num << ", 0, 0)";
					strSql = stream.str();

					bRef = DBUtil::getInstance()->insertData(strSql);
				}
			}
		}
	}

	return bRef;
}

bool DataManager::parseGoodsRemove(GoodsTypeEnum goodsType, int goodsID, int num)
{
	bool bRef = false;

	stringstream stream;
	string strSql = "";
	if (GoodsGeneral == goodsType)
	{
		stream.str("");
		stream << "Delete From " << DBUtil::getInstance()->getTableName(Table_gMain) << " Where PKID = " << goodsID;
		strSql = stream.str();
		if (false == DBUtil::getInstance()->deleteData(strSql))
		{
			return bRef;
		}

		stream.str(""); 
		stream << "Delete From " << DBUtil::getInstance()->getTableName(Table_gGrowth) << " Where PKID = " << goodsID;
		strSql = stream.str();
		if (false == DBUtil::getInstance()->deleteData(strSql))
		{
			return bRef;
		}

		stream.str("");
		stream << "Delete From " << DBUtil::getInstance()->getTableName(Table_gSkill) << " Where PKID = " << goodsID;
		strSql = stream.str();
		if (false == DBUtil::getInstance()->deleteData(strSql))
		{
			return bRef;
		}

		stream.str("");
		stream << "Delete From " << DBUtil::getInstance()->getTableName(Table_gEquip) << " Where PKID = " << goodsID;
		strSql = stream.str();
		if (false == DBUtil::getInstance()->deleteData(strSql))
		{
			return bRef;
		}

		stream.str("");
		stream << "Delete From " << DBUtil::getInstance()->getTableName(Table_gTalent) << " Where PKID = " << goodsID;
		strSql = stream.str();
		bRef = DBUtil::getInstance()->deleteData(strSql);
	}
	else /*if ((GoodsEquip == goodsType) || (GoodsProp == goodsType) || (GoodsChip == goodsType))*/	/* 道具装备碎片直接删除数据 */
	{
		stream.str("");
		stream << "Select count From " << DBUtil::getInstance()->getTableName(Table_Item) << " Where PKID = " << goodsID;
		strSql = stream.str();
		auto result = DBUtil::getInstance()->searchData(strSql);	/*  查询道具数量 */

		int count = 0;
		if (0 < result.size())
		{
			auto itr = result[0];
			count = atoi(itr["count"].c_str()) - num;
		}
		else
		{
			return bRef;
		}

		if (0 == count)
		{
			stream.str("");
			stream << "Delete From " << DBUtil::getInstance()->getTableName(Table_Item) << " Where PKID = " << goodsID;
			strSql = stream.str();
			bRef = DBUtil::getInstance()->deleteData(strSql);
		}
		else if (0 < count)
		{
			stream.str("");
			stream << "Update " << DBUtil::getInstance()->getTableName(Table_Item) << " Set count = " << count << " Where PKID = " << goodsID;
			strSql = stream.str();
			bRef = DBUtil::getInstance()->updateData(strSql);
		}
		else
		{
			return bRef;
		}
	}

	return bRef;
}

bool DataManager::wealthUpdate(int coin, int diamond)
{
	bool bRef = false;

	auto selectString = "Select coin, diamond From " + DBUtil::getInstance()->getTableName(Table_Player); 
	auto result = DBUtil::getInstance()->searchData(selectString);

	if (0 < result.size())
	{
		auto itr = result[0];
		auto wealth1 = atoi(itr["coin"].c_str()) + coin;
		auto wealth2 = atoi(itr["diamond"].c_str()) + diamond;

		if ((0 > wealth1) || (0 > wealth2))
		{
			return bRef;											/* 财富不足 */
		}

		stringstream stream;										// 更新金币数量
		stream << "Update " << DBUtil::getInstance()->getTableName(Table_Player) << " Set coin = " << wealth1 << ", diamond = " << wealth2;
		string strSql = stream.str();
		bRef = DBUtil::getInstance()->updateData(strSql);
	}

	return bRef;
}

bool DataManager::goodsCountUpdate(int id, int count)
{
	bool bRet = false;

	if (true == isSortGoodsNum(id))
	{
		stringstream stream;
		string strSql = "";
		auto num = goodsNum + count;

		if (0 == num)												/* 用完了，删除记录 */
		{
			stream.str("");
			stream << "Delete From " << DBUtil::getInstance()->getTableName(Table_Item) << " Where ID = " << id;
			strSql = stream.str();

			bRet = DBUtil::getInstance()->deleteData(strSql);
		}
		
		if (0 < num)
		{
			stream.str("");											// 更新记录
			stream << "Update " << DBUtil::getInstance()->getTableName(Table_Item) << " Set count = " << num << " Where ID = " << id;
			strSql = stream.str();
			bRet = DBUtil::getInstance()->updateData(strSql);
		}
	}

	return bRet;
}

bool DataManager::skillUnlock(int pkID, int level)
{
	bool bRet = false;

	stringstream stream;
	stream << "Select ID, lv2, lv3, lv4 From " << DBUtil::getInstance()->getTableName(Table_gSkill) << " Where PKID = " << pkID;
	string strSql = stream.str();

	auto result = DBUtil::getInstance()->searchData(strSql);
	if (0 < result.size())
	{
		bRet = true;

		auto itr = result[0];
		auto id = atoi(itr["ID"].c_str());
		auto lv2 = atoi(itr["lv2"].c_str());
		auto lv3 = atoi(itr["lv3"].c_str());
		auto lv4 = atoi(itr["lv4"].c_str());

		if (0 == generalProptyVector.size())
		{
			generalDataParser();
		}

		auto skill2 = 1;
		auto skill3 = 1;
		auto skill4 = 1;
		auto general = generalProptyVector[id - 10001];

		if ((general.maxStar >= 3) && (level >= 3))
		{
			if (lv2 != 0)
			{
				skill2 = lv2;
			}
		}
		if ((general.maxStar >= 4) && (level >= 8))
		{
			if (lv3 != 0)
			{
				skill2 = lv2;
			}
		}
		if ((general.maxStar >= 5) && (level >= 15))
		{
			if (lv4 != 0)
			{
				skill4 = lv4;
			}
		}

		stream.str("");
		stream << "Update " << DBUtil::getInstance()->getTableName(Table_gSkill) << 
			" Set lv2 = " << skill2 << " lv3 = " << skill3 << " lv4 = " << skill4 << " Where PKID = " << pkID;
		strSql = stream.str();

		bRet = DBUtil::getInstance()->updateData(strSql);
	}

	return bRet;
}

// ------------------------------- 以下是读取本地Json文件 --------------------- Begin ------------------- //

void DataManager::generalDataParser()
{
	string filename= "DataManager/General.json"; 
	rapidjson::Document doc;   
	if( !FileUtils::getInstance()->isFileExist(filename) )  
	{  
		CCASSERT(false, "Json File IS NOT FIND");
		return;
	}  
	// 读取文件数据，初始化doc  
	string data = FileUtils::getInstance()->getStringFromFile(filename);  
	doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());  
	// 判断读取成功与否 和 是否为数组类型  
	if (doc.HasParseError() || !doc.IsArray())  
	{  
		CCASSERT(false, "Get Json Data Error");
		return;
	}  
	GeneralProptyStruct generalProptyStruct;
	memset(&generalProptyStruct, 0, sizeof(generalProptyStruct));
	generalProptyVector.clear();
	// 数据从第二行开始  
	for(unsigned int i = 1; i < doc.Size(); i ++ )  
	{   
	    rapidjson::Value &value = doc[ i ]; 
		int a = 0;
	    generalProptyStruct.roleID = value[a++].GetInt();  
		std::string str = value[a++].GetString();
		memset(generalProptyStruct.chinaName, 0, sizeof(generalProptyStruct.chinaName));
		memcpy(generalProptyStruct.chinaName, str.c_str(), str.length());
		str = value[a++].GetString();
		memset(generalProptyStruct.chinaSmallName, 0, sizeof(generalProptyStruct.chinaSmallName));
		memcpy(generalProptyStruct.chinaSmallName, str.c_str(), str.length());

		generalProptyStruct.maxStar = value[a++].GetInt();
		generalProptyStruct.jobType = value[a++].GetInt();
		generalProptyStruct.evoLevel = value[ a ++ ].GetInt();
		generalProptyStruct.nowStar = value[a++].GetInt();
		generalProptyStruct.levelLimit = value[a++].GetInt();
		generalProptyStruct.evoLimit = value[a++].GetInt();
		generalProptyStruct.initAtk = value[a++].GetInt();
		generalProptyStruct.atkGrowing = value[a++].GetInt();
		generalProptyStruct.initHP = value[a++].GetInt();
		generalProptyStruct.hpGrowing = value[a++].GetInt();
		generalProptyStruct.initPD = value[a++].GetInt();
		generalProptyStruct.pdGrowing = value[a++].GetInt();
		generalProptyStruct.initMD = value[a++].GetInt();
		generalProptyStruct.mdGrowing = value[a++].GetInt();
		generalProptyStruct.riseHP = value[a++].GetDouble();

		str = value[a++].GetString();
		memset(generalProptyStruct.g_des, 0, sizeof(generalProptyStruct.g_des));
		memcpy(generalProptyStruct.g_des, str.c_str(), str.length());

		generalProptyVector.push_back(generalProptyStruct);
	}
}

void DataManager::generalUpgradeDataParser()
{
	string filename= "DataManager/GeneralUpgrade.json";  
	rapidjson::Document doc;   
	if( !FileUtils::getInstance()->isFileExist(filename) )  
	{
		CCASSERT(false, "Json File IS NOT FIND");
		return;
	}   
	string data = FileUtils::getInstance()->getStringFromFile(filename);  
	doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());   
	if (doc.HasParseError() || !doc.IsArray())  
	{  
		CCASSERT(false, "Get Json Data Error");
		return;
	}  
	GeneralUpgradeStruct generalUpgradeStruct;
	memset(&generalUpgradeStruct, 0, sizeof(generalUpgradeStruct));
	generalUpgradeDataVector.clear();
	for( unsigned int i = 1; i < doc.Size(); i ++ )  
	{    
		rapidjson::Value &value = doc[ i ];
		int a = 0;  
		generalUpgradeStruct.gLevel = value[a++].GetInt();  
		generalUpgradeStruct.gNeedExp = value[a++].GetInt(); 
		generalUpgradeDataVector.push_back(generalUpgradeStruct);
	}
}

void DataManager::equipDataParser()
{
	string filename= "DataManager/Equip.json";  
	rapidjson::Document doc;   
	if( !FileUtils::getInstance()->isFileExist(filename) )  
	{  
		CCASSERT(false, "Json File IS NOT FIND");
		return;
	}   
	string data = FileUtils::getInstance()->getStringFromFile(filename);  
	doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());   
	if (doc.HasParseError() || !doc.IsArray())  
	{  
		CCASSERT(false, "Get Json Data Error");
		return;
	}  
	EquipProptyStruct equipProptyStruct;
	memset(&equipProptyStruct, 0, sizeof(equipProptyStruct));
	equipProptyVector.clear();
	for( unsigned int i = 1; i < doc.Size(); i ++ )  
	{    
		rapidjson::Value &value = doc[ i ];
		int a = 0;  
		equipProptyStruct.eID = value[a++].GetInt();  
		string strName = value[a++].GetString(); 
		memset(equipProptyStruct.eChinaName, 0, sizeof(equipProptyStruct.eChinaName));
		memcpy(equipProptyStruct.eChinaName, strName.c_str(), strName.length());
		equipProptyStruct.ePositionType = value[a++].GetInt();
		string strPos = value[a++].GetString(); 
		memset(equipProptyStruct.ePositionName, 0, sizeof(equipProptyStruct.ePositionName));
		memcpy(equipProptyStruct.ePositionName, strPos.c_str(), strPos.length());
		equipProptyStruct.eColor = value[a++].GetInt();
		equipProptyStruct.eSellOut = value[a++].GetInt();
		equipProptyStruct.eExp = value[a++].GetInt();
		equipProptyStruct.eHP = value[a++].GetInt();
		equipProptyStruct.eAtk = value[a++].GetInt();
		equipProptyStruct.ePD = value[a++].GetInt();
		equipProptyStruct.eMD = value[a++].GetInt();
		equipProptyStruct.eAddCrit = value[a++].GetDouble();
		equipProptyStruct.eReduceCrit = value[a++].GetDouble();
		equipProptyStruct.eAddRealHurt = value[a++].GetInt();
		equipProptyStruct.eReduceHurt = value[a++].GetInt();
		equipProptyStruct.eisSuit = value[a++].GetInt();
		equipProptyStruct.eLevelLimit = value[a++].GetInt();
		string strDes = value[a++].GetString();
		memset(equipProptyStruct.eDes, 0, sizeof(equipProptyStruct.eDes));
		memcpy(equipProptyStruct.eDes, strDes.c_str(), strDes.length());
		equipProptyVector.push_back(equipProptyStruct);
	}
}

void DataManager::equipRefineRule()
{
	string filename= "DataManager/EquipRefine.json";  
	rapidjson::Document doc;
	if( !FileUtils::getInstance()->isFileExist(filename) )  
	{  
		CCASSERT(false, "Json File IS NOT FIND");
		return;
	}

	string data = FileUtils::getInstance()->getStringFromFile(filename);  
	doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());   
	if (doc.HasParseError() || !doc.IsArray())  
	{  
		CCASSERT(false, "Get Json Data Error");
		return;
	}

	equipRefineVector.clear();

	for( unsigned int index = 1; index < doc.Size(); index ++ )  
	{
		int aIndex = 0;
		rapidjson::Value &value = doc[index];
		EquipRefineStruct equipRefineStruct = {0};

		equipRefineStruct.eLevel = value[aIndex++].GetInt();		/* 等级 */
		auto listExp = splitString(value[aIndex++].GetString(), "-");/* 不同品级升级所需经验 */
		for (int i = 0;i < EquipGradeMax;i++)
		{
			equipRefineStruct.eExp[i] = atoi(listExp[i].c_str());
		}

		auto listCoin = splitString(value[aIndex++].GetString(), "-");/* 不同品级升级所需金币 */
		for (int i = 0;i < EquipGradeMax;i++)
		{
			equipRefineStruct.eCoin[i] = atoi(listCoin[i].c_str());
		}

		auto listGrow1 = splitString(value[aIndex++].GetString(), "-");/* 不同品级升级属性成长（奇珍） */
		for (int i = 0;i < EquipGradeMax;i++)
		{
			equipRefineStruct.eGrow1[i] = atof(listGrow1[i].c_str());
		}

		auto listGrow2 = splitString(value[aIndex++].GetString(), "-");/* 不同品级升级属性成长（异宝） */
		for (int i = 0;i < EquipGradeMax;i++)
		{
			equipRefineStruct.eGrow2[i] = atof(listGrow2[i].c_str());
		}

		equipRefineVector.push_back(equipRefineStruct);
	}
}

void DataManager::propDataParser()
{
	string filename= "DataManager/Prop.json";  
	rapidjson::Document doc;   
	if( !FileUtils::getInstance()->isFileExist(filename) )  
	{  
		CCASSERT(false, "Json File IS NOT FIND");
		return;
	}   
	string data = FileUtils::getInstance()->getStringFromFile(filename);  
	doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());   
	if (doc.HasParseError() || !doc.IsArray())  
	{  
		CCASSERT(false, "Get Json Data Error");
		return;
	}  
	PropProptyStruct propProptyStruct;
	memset(&propProptyStruct, 0, sizeof(propProptyStruct));
	propProptyVector.clear();
	for( unsigned int i = 1; i < doc.Size(); i ++ )  
	{    
		rapidjson::Value &value = doc[ i ];
		int a = 0;  
		propProptyStruct.pID = value[a++].GetInt();  
		string str = value[a++].GetString(); 
		memset(propProptyStruct.pChinaName, 0, sizeof(propProptyStruct.pChinaName));
		memcpy(propProptyStruct.pChinaName, str.c_str(), str.length());
		propProptyStruct.pType = value[ a ++ ].GetInt();
		propProptyStruct.pExpAdd = value[a++].GetInt();
		propProptyStruct.pPowerAdd = value[a++].GetInt();
		propProptyStruct.pSellPrice = value[a++].GetInt();
		string strDes = value[a++].GetString();
		memset(propProptyStruct.pDes, 0, sizeof(propProptyStruct.pDes));
		memcpy(propProptyStruct.pDes, strDes.c_str(), strDes.length());
		propProptyVector.push_back(propProptyStruct);
	}
}

void DataManager::checkPointDataParser(int diff)
{
	string afterFile = "";
	afterFile = ((0 == diff) ? "DataManager/CheckPointCom.json" : "DataManager/CheckPointDiff.json"); 

	rapidjson::Document doc;   
	if( !FileUtils::getInstance()->isFileExist(afterFile) )  
	{
		CCASSERT(false, "Json File IS NOT FIND");
		return;
	}
	string data = FileUtils::getInstance()->getStringFromFile(afterFile);  
	doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());   
	if (doc.HasParseError() || !doc.IsArray())  
	{  
		CCASSERT(false, "Get Json Data Error");
		return;
	}

	checkPointPropthVector.clear();

	for(unsigned int i = 1; i < doc.Size(); i ++)  
	{
		auto index = 0;
		auto jsonIndex = 0;
		rapidjson::Value &value = doc[i];
		std::vector<std::string> List;
		CheckPointStruct checkPointProptyStruct = {0};

		checkPointProptyStruct.cID = value[jsonIndex++].GetInt();	/* 关卡ID */

		string str = value[jsonIndex++].GetString();
		checkPointProptyStruct.cNameLen = str.length() + 1;			/* 关卡名称 */
		checkPointProptyStruct.cName = (char*)malloc(checkPointProptyStruct.cNameLen * sizeof(char));
		memset(checkPointProptyStruct.cName, 0, checkPointProptyStruct.cNameLen);
		memcpy(checkPointProptyStruct.cName, str.c_str(), checkPointProptyStruct.cNameLen);

		auto listIndex = 0;
		List = splitString(value[jsonIndex++].GetString(), "-");	/* 关卡角色 */
		checkPointProptyStruct.cRoleNum = List.size() / 4;			/* 4个数据一组角色信息 */
		checkPointProptyStruct.cRoles = (PointRole *)malloc(checkPointProptyStruct.cRoleNum * sizeof(PointRole));
		for (index = 0;index < checkPointProptyStruct.cRoleNum;index++)
		{
			checkPointProptyStruct.cRoles[index].pID = atoi(List[listIndex ++].c_str());
			checkPointProptyStruct.cRoles[index].room = atoi(List[listIndex ++].c_str());
			checkPointProptyStruct.cRoles[index].level = atoi(List[listIndex ++].c_str());
			checkPointProptyStruct.cRoles[index].flag = atoi(List[listIndex ++].c_str());
		}

		checkPointProptyStruct.cPower = value[jsonIndex++].GetInt();/* 关卡体力消耗 */

		List.clear();
		List = splitString(value[jsonIndex++].GetString(), "-");	/* 关卡宝箱 */
		checkPointProptyStruct.cBox.pID = atoi(List[0].c_str());
		checkPointProptyStruct.cBox.num = atoi(List[1].c_str());

		checkPointProptyStruct.cSoul = value[jsonIndex++].GetInt();	/* 可获得灵魂石数量 */

		str = value[jsonIndex++].GetString();
		str = "res/Map/" + str + ".png";
		checkPointProptyStruct.cMapLen = str.length() + 1;			/* 关卡地图名称 */
		checkPointProptyStruct.cMap = (char*)malloc(checkPointProptyStruct.cMapLen * sizeof(char));
		memset(checkPointProptyStruct.cMap, 0, checkPointProptyStruct.cMapLen);
		memcpy(checkPointProptyStruct.cMap, str.c_str(), checkPointProptyStruct.cMapLen);

		stringstream stream;
		stream << value[jsonIndex++].GetInt();
		str = stream.str();
		checkPointProptyStruct.cSongLen = str.length() + 1;			/* 关卡背景音效 */
		checkPointProptyStruct.cSong = (char*)malloc(checkPointProptyStruct.cSongLen * sizeof(char));
		memset(checkPointProptyStruct.cSong, 0, checkPointProptyStruct.cSongLen);
		memcpy(checkPointProptyStruct.cSong, str.c_str(), checkPointProptyStruct.cSongLen);

		listIndex = 0;
		List.clear();
		List = splitString(value[jsonIndex++].GetString(), "-");	/* 关卡物品掉落 */
		checkPointProptyStruct.cThingNum = List.size() / 2;			/* 2个数据一组物品信息 */
		checkPointProptyStruct.cThing = (PointThing *)malloc(checkPointProptyStruct.cRoleNum * sizeof(PointThing));
		for (index = 0;index < checkPointProptyStruct.cThingNum;index++)
		{
			checkPointProptyStruct.cThing[index].pID = atoi(List[listIndex ++].c_str());
			checkPointProptyStruct.cThing[index].rate = atof(List[listIndex ++].c_str());
		}

		List.clear();
		List = splitString(value[jsonIndex++].GetString(), "-");	/* 培养丹 */
		checkPointProptyStruct.cPill= atoi(List[0].c_str());
		checkPointProptyStruct.cPillRate = atof(List[1].c_str());

		str = value[jsonIndex++].GetString();
		checkPointProptyStruct.cDesLen = str.length() + 1;			/* 关卡说明 */
		checkPointProptyStruct.cDes = (char*)malloc(checkPointProptyStruct.cDesLen * sizeof(char));
		memset(checkPointProptyStruct.cDes, 0, checkPointProptyStruct.cDesLen);
		memcpy(checkPointProptyStruct.cDes, str.c_str(), checkPointProptyStruct.cDesLen);

		checkPointPropthVector.push_back(checkPointProptyStruct);
	}
}

void DataManager::pointCellInfoParse()
{
	string filePath = "res/FightPoints/PointCellInfo.json";
	rapidjson::Document doc;

	if( !FileUtils::getInstance()->isFileExist(filePath) )  
	{
		CCASSERT(false, "Json File IS NOT FIND");
		return;
	}
	string data = FileUtils::getInstance()->getStringFromFile(filePath);  
	doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());   
	if (doc.HasParseError() || !doc.IsArray())  
	{  
		CCASSERT(false, "Get Json Data Error");
		return;
	}

	pointCellInfoVector.clear();

	for(unsigned int i = 1; i < doc.Size(); i ++)  
	{
		auto index = 0;
		auto jsonIndex = 0;
		rapidjson::Value &value = doc[i];
		std::vector<std::string> List;
		PointCellInfoStruct pointCellInfoStruct = {0};

		pointCellInfoStruct.pID = value[jsonIndex++].GetInt();		/* 关卡ID */
		pointCellInfoStruct.xLoc = value[jsonIndex++].GetInt();		/* 关卡横坐标 */
		pointCellInfoStruct.yLoc = value[jsonIndex++].GetInt();		/* 关卡纵坐标 */

		pointCellInfoVector.push_back(pointCellInfoStruct);
	}
}

void DataManager::jxxgDataParser()
{ 
	string afterFile = "DataManager/JiXiaXueGong.json";

	rapidjson::Document doc;   
	if( !FileUtils::getInstance()->isFileExist(afterFile) )  
	{
		CCASSERT(false, "Json File IS NOT FIND");
		return;
	}
	string data = FileUtils::getInstance()->getStringFromFile(afterFile);  
	doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());   
	if (doc.HasParseError() || !doc.IsArray())  
	{  
		CCASSERT(false, "Get Json Data Error");
		return;
	}

	checkPointPropthVector.clear();

	for(unsigned int i = 1; i < doc.Size(); i ++)  
	{
		auto index = 0;
		auto jsonIndex = 0;
		rapidjson::Value &value = doc[i];
		std::vector<std::string> List;
		CheckPointStruct checkPointProptyStruct = {0};

		checkPointProptyStruct.cID = value[jsonIndex++].GetInt();	/* 关卡ID */

		string str = value[jsonIndex++].GetString();
		checkPointProptyStruct.cNameLen = str.length() + 1;			/* 关卡名称 */
		checkPointProptyStruct.cName = (char*)malloc(checkPointProptyStruct.cNameLen * sizeof(char));
		memset(checkPointProptyStruct.cName, 0, checkPointProptyStruct.cNameLen);
		memcpy(checkPointProptyStruct.cName, str.c_str(), checkPointProptyStruct.cNameLen);

		auto listIndex = 0;
		List = splitString(value[jsonIndex++].GetString(), "-");	/* 关卡角色 */
		checkPointProptyStruct.cRoleNum = List.size() / 4;			/* 4个数据一组角色信息 */
		checkPointProptyStruct.cRoles = (PointRole *)malloc(checkPointProptyStruct.cRoleNum * sizeof(PointRole));
		for (index = 0;index < checkPointProptyStruct.cRoleNum;index++)
		{
			checkPointProptyStruct.cRoles[index].pID = atoi(List[listIndex ++].c_str());
			checkPointProptyStruct.cRoles[index].room = atoi(List[listIndex ++].c_str());
			checkPointProptyStruct.cRoles[index].level = atoi(List[listIndex ++].c_str());
			checkPointProptyStruct.cRoles[index].flag = atoi(List[listIndex ++].c_str());
		}

		stringstream stream;
		stream << value[jsonIndex++].GetInt();
		str = stream.str();
		checkPointProptyStruct.cSongLen = str.length() + 1;			/* 关卡背景音效 */
		checkPointProptyStruct.cSong = (char*)malloc(checkPointProptyStruct.cSongLen * sizeof(char));
		memset(checkPointProptyStruct.cSong, 0, checkPointProptyStruct.cSongLen);
		memcpy(checkPointProptyStruct.cSong, str.c_str(), checkPointProptyStruct.cSongLen);

		checkPointPropthVector.push_back(checkPointProptyStruct);
	}
}

bool DataManager::signInDataParser()
{
	bool bRef = false;
	string filename= "DataManager/SignIn.json";  
	rapidjson::Document doc;   
	if( !FileUtils::getInstance()->isFileExist(filename) )  
	{
		CCASSERT(false, "Json File IS NOT FIND");
		return bRef;
	}   
	string data = FileUtils::getInstance()->getStringFromFile(filename);  
	doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());   
	if (doc.HasParseError() || !doc.IsArray())  
	{  
		CCASSERT(false, "Get Json Data Error");
		return bRef;
	}  
	SignInStruct signInStruct;
	memset(&signInStruct, 0, sizeof(signInStruct));
	signInVector.clear();
	for( unsigned int i = 1; i < doc.Size(); i ++ )  
	{    
		bRef = true;
		std::vector<std::string> List;
		rapidjson::Value &value = doc[ i ];
		int a = 0;  
		signInStruct.sSignInDay = value[a++].GetInt();  
		std::string str = value[a++].GetString();
		memset(signInStruct.sGoodsName, 0, sizeof(signInStruct.sGoodsName));
		memcpy(signInStruct.sGoodsName, str.c_str(), str.length());
		signInStruct.sGoodsRes = value[a++].GetInt();
		signInStruct.sGoodsType = value[a++].GetInt();
		std::string strID = value[a++].GetString();
		memset(signInStruct.IDRange, 0, sizeof(signInStruct.IDRange));
		memcpy(signInStruct.IDRange, strID.c_str(), strID.length());
		for (int i = 0; i < 10; i ++)
		{
			signInStruct.sNeedVip[ i ] = value[ a++ ].GetInt();
		}		
		signInVector.push_back(signInStruct);
	}
	return bRef;
}

void DataManager::DrawoffIDDataParser()
{
	string filename= "DataManager/DrawoffID.json";  
	rapidjson::Document doc;   
	if( !FileUtils::getInstance()->isFileExist(filename) )  
	{  
		CCASSERT(false, "Json File IS NOT FIND");
		return;
	}   
	string data = FileUtils::getInstance()->getStringFromFile(filename);  
	doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());   
	if (doc.HasParseError() || !doc.IsArray())  
	{  
		CCASSERT(false, "Get Json Data Error");
		return;
	}  
	DrawoffIDRecvStruct drawoffStruct;
	memset(&drawoffStruct, 0, sizeof(drawoffStruct));
	drawoffIDVector.clear();
	for( unsigned int i = 1; i < doc.Size(); i ++ )  
	{    
		rapidjson::Value &value = doc[ i ];
		int a = 0; 
		drawoffStruct.cID = value[a++].GetInt();  
		drawoffStruct.wID = value[a++].GetInt();
		std::string str = value[a++].GetString();
		memset(drawoffStruct.wName, 0, sizeof(drawoffStruct.wName));
		memcpy(drawoffStruct.wName, str.c_str(), str.length());	
		drawoffIDVector.push_back(drawoffStruct);
	}
}

void DataManager::DrawoffDataParser()
{
	string filename= "DataManager/Drawoff.json";  
	rapidjson::Document doc;   
	if( !FileUtils::getInstance()->isFileExist(filename) )  
	{  
		CCASSERT(false, "Json File IS NOT FIND");
		return;
	}   
	string data = FileUtils::getInstance()->getStringFromFile(filename);  
	doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());   
	if (doc.HasParseError() || !doc.IsArray())  
	{  
		CCASSERT(false, "Get Json Data Error");
		return;
	}  
	DrawoffRecvStruct drawoffStruct;
	memset(&drawoffStruct, 0, sizeof(drawoffStruct));
	drawoffVector.clear();
	for( unsigned int i = 1; i < doc.Size(); i ++ )  
	{    
		rapidjson::Value &value = doc[ i ];
		int a = 0; 
		drawoffStruct.goodsType = value[a++].GetInt();  
		string strID = value[ a ++ ].GetString();
		memset(drawoffStruct.idRange, 0, sizeof(drawoffStruct.idRange));
		memcpy(drawoffStruct.idRange, strID.c_str(), strID.length());
		string strCoinRange = value[ a ++ ].GetString();
		memset(drawoffStruct.coinRange, 0, sizeof(drawoffStruct.coinRange));
		memcpy(drawoffStruct.coinRange, strCoinRange.c_str(), strCoinRange.length());
		string strdiamondRange = value[ a ++ ].GetString();
		memset(drawoffStruct.diamonRange, 0, sizeof(drawoffStruct.diamonRange));
		memcpy(drawoffStruct.diamonRange, strdiamondRange.c_str(), strdiamondRange.length());
		drawoffVector.push_back(drawoffStruct);
	}
}

void DataManager::boxDataParser()
{
	string filename = "DataManager/Box.json";  
	rapidjson::Document doc;   
	if( !FileUtils::getInstance()->isFileExist(filename) )  
	{  
		CCASSERT(false, "Json File IS NOT FIND");
		return;
	}   
	string data = FileUtils::getInstance()->getStringFromFile(filename);  
	doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());   
	if (doc.HasParseError() || !doc.IsArray())  
	{  
		CCASSERT(false, "Get Json Data Error");
		return;
	}  
	BoxRecvStruct boxRecvStruct;
	memset(&boxRecvStruct, 0, sizeof(boxRecvStruct));
	boxVector.clear();
	for( unsigned int i = 1; i < doc.Size(); i ++ )  
	{    
		rapidjson::Value &value = doc[ i ];
		int a = 0; 
		boxRecvStruct.goodsType = value[a++].GetInt();  
		string strID = value[ a ++ ].GetString();
		memset(boxRecvStruct.idRange, 0, sizeof(boxRecvStruct.idRange));
		memcpy(boxRecvStruct.idRange, strID.c_str(), strID.length());

		string strTongRange = value[ a ++ ].GetString();
		memset(boxRecvStruct.tong, 0, sizeof(boxRecvStruct.tong));
		memcpy(boxRecvStruct.tong, strTongRange.c_str(), strTongRange.length());

		string strYinRange = value[ a ++ ].GetString();
		memset(boxRecvStruct.yin, 0, sizeof(boxRecvStruct.yin));
		memcpy(boxRecvStruct.yin, strYinRange.c_str(), strYinRange.length());

		string strJinRange = value[ a ++ ].GetString();
		memset(boxRecvStruct.jin, 0, sizeof(boxRecvStruct.jin));
		memcpy(boxRecvStruct.jin, strJinRange.c_str(), strJinRange.length());

		boxVector.push_back(boxRecvStruct);
	}
}

void DataManager::pointGainsParse()
{
	string filename = "DataManager/PointGains.json";  
	rapidjson::Document doc;   
	if( !FileUtils::getInstance()->isFileExist(filename) )  
	{  
		CCASSERT(false, "Json File IS NOT FIND");
		return;
	}
	string data = FileUtils::getInstance()->getStringFromFile(filename);  
	doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());   
	if (doc.HasParseError() || !doc.IsArray())  
	{  
		CCASSERT(false, "Get Json Data Error");
		return;
	}

	pointGainsVector.clear();
	for( unsigned int i = 1; i < doc.Size(); i ++ )  
	{
		auto a = 0;
		PointGainsStruct pointGainsStruct = {0};
		rapidjson::Value &value = doc[i];

		pointGainsStruct.level = value[a++].GetInt();				/* 帐号等级 */
		pointGainsStruct.power[PointDiff_Normal] = value[a++].GetInt();/* 普通级体力消耗 */
		pointGainsStruct.power[PointDiff_Hard] = value[a++].GetInt();/* 困难级体力消耗 */
		pointGainsStruct.exp[PointDiff_Normal] = value[a++].GetInt();/* 普通级经验获取 */
		pointGainsStruct.exp[PointDiff_Hard] = value[a++].GetInt();	/* 困难级经验获取 */
		pointGainsStruct.coin[PointDiff_Normal] = value[a++].GetInt();/* 普通级金币获取 */
		pointGainsStruct.coin[PointDiff_Hard] = value[a++].GetDouble();/* 困难级金币获取 */

		pointGainsVector.push_back(pointGainsStruct);
	}
}

void DataManager::generalChipDataParser()
{
	string filename = "DataManager/GeneralChip.json";  
	rapidjson::Document doc;   
	if( !FileUtils::getInstance()->isFileExist(filename) )  
	{  
		CCASSERT(false, "Json File IS NOT FIND");
		return;
	}   
	string data = FileUtils::getInstance()->getStringFromFile(filename);  
	doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());   
	if (doc.HasParseError() || !doc.IsArray())  
	{  
		CCASSERT(false, "Get Json Data Error");
		return;
	}  
	GeneralChipRecvStruct generalChipRecvStruct;
	memset(&generalChipRecvStruct, 0, sizeof(generalChipRecvStruct));
	generalChipVector.clear();
	for( unsigned int i = 1; i < doc.Size(); i ++ )  
	{    
		rapidjson::Value &value = doc[ i ];
		int a = 0; 
		generalChipRecvStruct.starLevel = value[a++].GetInt(); 
		generalChipRecvStruct.num = value[a++].GetInt();
		generalChipVector.push_back(generalChipRecvStruct);
	}
}

void DataManager::equipChipDataParser()
{
	string filename = "DataManager/EquipChip.json";  
	rapidjson::Document doc;   
	if( !FileUtils::getInstance()->isFileExist(filename) )  
	{  
		CCASSERT(false, "Json File IS NOT FIND");
		return;
	}   
	string data = FileUtils::getInstance()->getStringFromFile(filename);  
	doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());   
	if (doc.HasParseError() || !doc.IsArray())  
	{  
		CCASSERT(false, "Get Json Data Error");
		return;
	}  
	EquipChipRecvStruct equipChipRecvStruct;
	memset(&equipChipRecvStruct, 0, sizeof(equipChipRecvStruct));
	equipChipVector.clear();
	for( unsigned int i = 1; i < doc.Size(); i ++ )  
	{    
		rapidjson::Value &value = doc[ i ];
		int a = 0; 
		equipChipRecvStruct.color = value[a++].GetInt(); 
		equipChipRecvStruct.isSuit = value[a++].GetInt();
		equipChipRecvStruct.num = value[a++].GetInt();
		equipChipVector.push_back(equipChipRecvStruct);
	}
}

void DataManager::SkillNameDataParser()
{
	string filename = "DataManager/SkillName.json";  
	rapidjson::Document doc;   
	if( !FileUtils::getInstance()->isFileExist(filename) )  
	{  
		CCASSERT(false, "Json File IS NOT FIND");
		return;
	}   
	string data = FileUtils::getInstance()->getStringFromFile(filename);  
	doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());   
	if (doc.HasParseError() || !doc.IsArray())  
	{  
		CCASSERT(false, "Get Json Data Error");
		return;
	}  
	SkillNameStruct skillName;
	memset(&skillName, 0, sizeof(skillName));
	skillNameVector.clear();
	for( unsigned int i = 1; i < doc.Size(); i ++ )  
	{    
		rapidjson::Value &value = doc[ i ];
		int a = 0; 
		skillName.RoleID = value[ a ++ ].GetInt(); 
		string aString = value[ a ++ ].GetString();
		memset(skillName.sAName, 0, sizeof(skillName.sAName));
		memcpy(skillName.sAName, aString.c_str(), aString.length());
		string bString = value[ a ++ ].GetString();
		memset(skillName.sBName, 0, sizeof(skillName.sBName));
		memcpy(skillName.sBName, bString.c_str(), bString.length());
		string cString = value[ a ++ ].GetString();
		memset(skillName.sCName, 0, sizeof(skillName.sCName));
		memcpy(skillName.sCName, cString.c_str(), cString.length());
		string dString = value[ a ++ ].GetString();	
		memset(skillName.sDName, 0, sizeof(skillName.sDName));
		memcpy(skillName.sDName, dString.c_str(), dString.length());
		string aMString = value[ a ++ ].GetString();
		memset(skillName.sANameS, 0, sizeof(skillName.sANameS));
		memcpy(skillName.sANameS, aMString.c_str(), aMString.length());
		string bMString = value[ a ++ ].GetString();
		memset(skillName.sBNameS, 0, sizeof(skillName.sBNameS));
		memcpy(skillName.sBNameS, bMString.c_str(), bMString.length());
		string cMString = value[ a ++].GetString();
		memset(skillName.sCNameS, 0, sizeof(skillName.sCNameS));
		memcpy(skillName.sCNameS, cMString.c_str(), cMString.length());
		string dMString = value[ a ++ ].GetString();
		memset(skillName.sDNameS, 0, sizeof(skillName.sDNameS));
		memcpy(skillName.sDNameS, dMString.c_str(), dMString.length());
		skillName.sACD = value[ a ++ ].GetInt();
		skillName.sBCD = value[ a ++ ].GetInt();
		skillName.sCCD = value[ a ++ ].GetInt();
		skillName.sDCD = value[ a ++ ].GetInt();
 		skillName.sAHurt = value[ a ++ ].GetDouble();
		skillName.sBHurt = value[ a ++ ].GetDouble();
		skillName.sCHurt = value[ a ++ ].GetDouble();
		skillName.sDHurt = value[ a ++ ].GetDouble();
		string aDMString = value[ a ++ ].GetString();
		memset(skillName.sADes, 0, sizeof(skillName.sADes));
		memcpy(skillName.sADes, aDMString.c_str(), aDMString.length());
		string bDString = value[ a ++ ].GetString();
		memset(skillName.sBDes, 0, sizeof(skillName.sBDes));
		memcpy(skillName.sBDes, bDString.c_str(), bDString.length());
		string cDString = value[ a ++ ].GetString();
		memset(skillName.sCDes, 0, sizeof(skillName.sCDes));
		memcpy(skillName.sCDes, cDString.c_str(), cDString.length());
		string dDString = value[ a ++ ].GetString();
		memset(skillName.sDDes, 0, sizeof(skillName.sDDes));
		memcpy(skillName.sDDes, dDString.c_str(), dDString.length());
		skillNameVector.push_back(skillName);
	}
}

void DataManager::SkillUpgradeDataParser()
{
	string filename = "DataManager/SkillUpgrade.json";  
	rapidjson::Document doc;   
	if( !FileUtils::getInstance()->isFileExist(filename) )  
	{  
		CCASSERT(false, "Json File IS NOT FIND");
		return;
	}   
	string data = FileUtils::getInstance()->getStringFromFile(filename);  
	doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());   
	if (doc.HasParseError() || !doc.IsArray())  
	{  
		CCASSERT(false, "Get Json Data Error");
		return;
	}  
	SkillUpgradeStruct skillUpgradeStruct;
	memset(&skillUpgradeStruct, 0, sizeof(skillUpgradeStruct));
	skillUpgradeVector.clear();
	for( unsigned int i = 1; i < doc.Size(); i ++ )  
	{    
		rapidjson::Value &value = doc[ i ];
		int a = 0; 
		skillUpgradeStruct.skillLevel = value[a++].GetInt(); 
		skillUpgradeStruct.skillExpandCoin = value[a++].GetInt();
		skillUpgradeStruct.skillPropty = value[a++].GetDouble();
		skillUpgradeVector.push_back(skillUpgradeStruct);
	}
}

void DataManager::GeneralEvoDataParser()
{
	string filename = "DataManager/GeneralEvo.json";  
	rapidjson::Document doc;   
	if( !FileUtils::getInstance()->isFileExist(filename) )  
	{  
		CCASSERT(false, "Json File IS NOT FIND");
		return;
	}   
	string data = FileUtils::getInstance()->getStringFromFile(filename);  
	doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());   
	if (doc.HasParseError() || !doc.IsArray())  
	{  
		CCASSERT(false, "Get Json Data Error");
		return;
	}  
	GeneralEvoLocalStruct generalEvo;
	memset(&generalEvo, 0, sizeof(generalEvo));
	generalEvoLocalVector.clear();
	for( unsigned int i = 1; i < doc.Size(); i ++ )  
	{    
		rapidjson::Value &value = doc[ i ];
		int a = 0; 
		generalEvo.maxStar = value[a++].GetInt(); 
		generalEvo.evoLevel = value[ a++ ].GetInt();
		generalEvo.curStar = value[a++].GetInt();
		generalEvo.sameName = value[a++].GetInt();
		generalEvo.addStar = value[a++].GetInt();
		generalEvo.addEvo = value[a++].GetInt();
		generalEvo.levelLimit = value[a++].GetInt();
		generalEvo.needExp = value[a++].GetInt(); 
		generalEvo.needSoul = value[a++].GetInt();
		generalEvo.needCoin = value[a++].GetInt();
		generalEvoLocalVector.push_back(generalEvo);
	}
}

void DataManager::GeneralEvoExpDataParser()
{
	string filename = "DataManager/CardExp.json";  
	rapidjson::Document doc;   
	if( !FileUtils::getInstance()->isFileExist(filename) )  
	{  
		CCASSERT(false, "Json File IS NOT FIND");
		return;
	}   
	string data = FileUtils::getInstance()->getStringFromFile(filename);  
	doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());   
	if (doc.HasParseError() || !doc.IsArray())  
	{  
		CCASSERT(false, "Get Json Data Error");
		return;
	}  
	GeneralEvoExpLocalStruct generalEvoExp;
	memset(&generalEvoExp, 0, sizeof(generalEvoExp));
	generalEvoExpLocalVector.clear();
	for( unsigned int i = 1; i < doc.Size(); i ++ )  
	{    
		rapidjson::Value &value = doc[ i ];
		int a = 0; 
		generalEvoExp.maxStar = value[a++].GetInt(); 
		generalEvoExp.curStar = value[a++].GetInt();
		generalEvoExp.pridExp = value[a++].GetInt();
		generalEvoExpLocalVector.push_back(generalEvoExp);
	}
}

void DataManager::BuyCoinAndPower()
{
	string filename = "DataManager/PowerAndCoin.json";  
	rapidjson::Document doc;   
	if( !FileUtils::getInstance()->isFileExist(filename) )  
	{  
		CCASSERT(false, "Json File IS NOT FIND");
		return;
	}   
	string data = FileUtils::getInstance()->getStringFromFile(filename);  
	doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());   
	if (doc.HasParseError() || !doc.IsArray())  
	{  
		CCASSERT(false, "Get Json Data Error");
		return;
	}  
	BuyCPLocalStruct buyCPLocal;
	memset(&buyCPLocal, 0, sizeof(buyCPLocal));
	buyCPLocalVector.clear();
	for( unsigned int i = 1; i < doc.Size(); i ++ )  
	{    
		rapidjson::Value &value = doc[ i ];
		int a = 0; 
		buyCPLocal.times = value[a++].GetInt(); 
		buyCPLocal.ruleDP = value[a++].GetInt();
		buyCPLocal.valuePower = value[a++].GetInt();
		buyCPLocal.ruleDC = value[a++].GetInt();
		buyCPLocal.valueCoin = value[a++].GetInt();
		buyCPLocalVector.push_back(buyCPLocal);
	}
}

void DataManager::talentDataParser()
{
	string filename = "DataManager/Talent.json";  
	rapidjson::Document doc;   
	if( !FileUtils::getInstance()->isFileExist(filename) )  
	{  
		CCASSERT(false, "Json File IS NOT FIND");
		return;
	}   
	string data = FileUtils::getInstance()->getStringFromFile(filename);  
	doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());   
	if (doc.HasParseError() || !doc.IsArray())  
	{  
		CCASSERT(false, "Get Json Data Error");
		return;
	}  
	TalentLocalStruct talentStruct;
	memset(&talentStruct, 0, sizeof(talentStruct));
	talentLocalVector.clear();
	for( unsigned int i = 1; i < doc.Size(); i ++ )  
	{    
		rapidjson::Value &value = doc[ i ];
		int a = 0; 
		talentStruct.id = value[a++].GetInt(); 
		talentStruct.type = value[a++].GetInt();
		talentStruct.lightStar = value[a++].GetInt();
		talentStruct.special = value[a++].GetInt();
		string nameString = value[ a++ ].GetString();
		memset(talentStruct.talentName, 0, 20);
		memcpy(talentStruct.talentName, nameString.c_str(), nameString.length());
		string resString = value[ a++ ].GetString();
		memset(talentStruct.resName, 0, 20);
		memcpy(talentStruct.resName, resString.c_str(), resString.length());
		string desString = value[ a++ ].GetString();
		memset(talentStruct.des, 0, 100);
		memcpy(talentStruct.des, desString.c_str(), desString.length());
		talentLocalVector.push_back(talentStruct);
	}
}

void DataManager::teamUpgradeDataParser()
{
	string filename = "DataManager/TeamUpgrad.json";  
	rapidjson::Document doc;   
	if( !FileUtils::getInstance()->isFileExist(filename) )  
	{  
		CCASSERT(false, "Json File IS NOT FIND");
		return;
	}   
	string data = FileUtils::getInstance()->getStringFromFile(filename);  
	doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());   
	if (doc.HasParseError() || !doc.IsArray())  
	{  
		CCASSERT(false, "Get Json Data Error");
		return;
	}  
	TeamUpgradeLocalStrcut teamUpgrade;
	memset(&teamUpgrade, 0, sizeof(teamUpgrade));
	teamUpgradeLocalVector.clear();
	for( unsigned int i = 1; i < doc.Size(); i ++ )  
	{    
		rapidjson::Value &value = doc[ i ];
		int a = 0; 
		teamUpgrade.level = value[a++].GetInt(); 
		teamUpgrade.needExp = value[a++].GetInt();
		teamUpgradeLocalVector.push_back(teamUpgrade);
	}
}

void DataManager::skillUpgradeProptyAdd()
{
	string filename = "DataManager/SkillUpgradeAdd.json";  
	rapidjson::Document doc;   
	if( !FileUtils::getInstance()->isFileExist(filename) )  
	{  
		CCASSERT(false, "Json File IS NOT FIND");
		return;
	}   
	string data = FileUtils::getInstance()->getStringFromFile(filename);  
	doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());   
	if (doc.HasParseError() || !doc.IsArray())  
	{  
		CCASSERT(false, "Get Json Data Error");
		return;
	}  
	SkillAddPropty skillAddPropty;
	memset(&skillAddPropty, 0, sizeof(skillAddPropty));
	localSkillAddProptyVector.clear();
	for( unsigned int i = 1; i < doc.Size(); i ++ )  
	{    
		rapidjson::Value &value = doc[ i ];
		int a = 0; 
		skillAddPropty.skillLevel = value[a++].GetInt(); 
		skillAddPropty.eATK = value[a++].GetInt(); 
		skillAddPropty.eAtkLen = value[a++].GetInt(); 
		skillAddPropty.eHP = value[a++].GetInt(); 
		skillAddPropty.eHPLen = value[a++].GetInt(); 
		skillAddPropty.ePD = value[a++].GetInt(); 
		skillAddPropty.ePDLen = value[a++].GetInt(); 
		skillAddPropty.eMD = value[a++].GetInt(); 
		skillAddPropty.dMDLen= value[a++].GetInt(); 
		skillAddPropty.dHP = value[a++].GetInt(); 
		skillAddPropty.dHPLen = value[a++].GetInt(); 
		skillAddPropty.dPD = value[a++].GetInt(); 
		skillAddPropty.dPDLen = value[a++].GetInt(); 
		skillAddPropty.dMD = value[a++].GetInt(); 
		skillAddPropty.dMDLen = value[a++].GetInt(); 
		skillAddPropty.cPD = value[a++].GetInt(); 
		skillAddPropty.cPDLen = value[a++].GetInt(); 
		skillAddPropty.cMD = value[a++].GetInt(); 
		skillAddPropty.cMDLen = value[a++].GetInt();  
		localSkillAddProptyVector.push_back(skillAddPropty);
	}
}

void DataManager::skillRegionParser()
{
	string filename = "DataManager/SkillRegion.json";  
	rapidjson::Document doc;   
	if( !FileUtils::getInstance()->isFileExist(filename) )  
	{  
		CCASSERT(false, "Json File IS NOT FIND");
		return;
	}   
	string data = FileUtils::getInstance()->getStringFromFile(filename);  
	doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());   
	if (doc.HasParseError())  
	{  
		CCASSERT(false, "Get Json Data Error");
		return;
	}  

	skillRegionMap.clear();
	for( unsigned int index = 1; index < doc.Size(); index ++ )  
	{
		int json = 1;
		auto &value = doc[ index ];
		SkillRegionStruct skillRegion = {0};

		string strName = value[json++].GetString();					/* 角色名 */
		skillRegion.atk[0] = value[json++].GetInt();				/* 普攻第一击 */
		skillRegion.atk[1] = value[json++].GetInt();
		skillRegion.atk2[0] = value[json++].GetInt();				/* 普攻第二击 */
		skillRegion.atk2[1] = value[json++].GetInt();
		skillRegion.atk3[0] = value[json++].GetInt();				/* 普攻第三击 */
		skillRegion.atk3[1] = value[json++].GetInt();
		skillRegion.s1[0] = value[json++].GetInt();					/* 技能一 */
		skillRegion.s1[1] = value[json++].GetInt();
		skillRegion.s2[0] = value[json++].GetInt();					/* 技能二 */
		skillRegion.s2[1] = value[json++].GetInt();
		skillRegion.s3[0] = value[json++].GetInt();					/* 技能三 */
		skillRegion.s3[1] = value[json++].GetInt();
		skillRegion.s4[0] = value[json++].GetInt();					/* 技能四 */
		skillRegion.s4[1] = value[json++].GetInt();
		
		skillRegionMap.insert(pair<string, SkillRegionStruct>(strName, skillRegion));
	}
}

void DataManager::subInfoParser()
{
	string filename = "DataManager/SubInfo.json";  
	rapidjson::Document doc;   
	if( !FileUtils::getInstance()->isFileExist(filename) )  
	{  
		CCASSERT(false, "Json File IS NOT FIND");
		return;
	}   
	string data = FileUtils::getInstance()->getStringFromFile(filename);  
	doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());   
	if (doc.HasParseError())  
	{  
		CCASSERT(false, "Get Json Data Error");
		return;
	}  

	subInfoMap.clear();
	for( unsigned int index = 1; index < doc.Size(); index ++ )  
	{
		int json = 1;
		auto &value = doc[ index ];
		SubInfoStruct subInfo = {0};

		string strName = value[json++].GetString();					/* 角色名 */
		subInfo.anchorX = value[json++].GetDouble();				/* 锚点x */
		subInfo.anchorY = value[json++].GetDouble();				/* 锚点y */
		subInfo.speed = value[json++].GetDouble();					/* 速度 */

		subInfoMap.insert(pair<string, SubInfoStruct>(strName, subInfo));
	}
}

void DataManager::dailyTaskDateParser()
{
	string filename = "DataManager/DailyTask.json";  
	rapidjson::Document doc;   
	if( !FileUtils::getInstance()->isFileExist(filename) )  
	{  
		CCASSERT(false, "Json File IS NOT FIND");
		return;
	}   
	string data = FileUtils::getInstance()->getStringFromFile(filename);  
	doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());   
	if (doc.HasParseError())  
	{  
		CCASSERT(false, "Get Json Data Error");
		return;
	}  
	dailyTaskVector.clear();
	for( unsigned int index = 1; index < doc.Size(); index ++ )  
	{
		int a = 0;
		auto &value = doc[ index ];
		DailyTaskLocalStruct dailyTask;
		memset( &dailyTask, 0, sizeof(dailyTask) );
		dailyTask.id = value[ a ++ ].GetInt();

		string strName = value[ a ++ ].GetString();
		memset(dailyTask.taskName, 0, sizeof(dailyTask.taskName));
		memcpy(dailyTask.taskName, strName.c_str(), strName.length() );

		dailyTask.dTimes = value[ a ++ ].GetInt();

		string strDiamond = value[ a ++ ].GetString();
		memset(dailyTask.diamondValue, 0, sizeof(dailyTask.diamondValue));
		memcpy(dailyTask.diamondValue, strDiamond.c_str(), strDiamond.length() );

		string strCoin = value[ a ++ ].GetString();
		memset(dailyTask.coinValue, 0, sizeof(dailyTask.coinValue));
		memcpy(dailyTask.coinValue, strCoin.c_str(), strCoin.length() );

		string strSoul = value[ a ++ ].GetString();
		memset(dailyTask.soulValue, 0, sizeof(dailyTask.soulValue));
		memcpy(dailyTask.soulValue, strSoul.c_str(), strSoul.length() );

		string strDan = value[ a ++ ].GetString();
		memset(dailyTask.danValue, 0, sizeof(dailyTask.danValue));
		memcpy(dailyTask.danValue, strDan.c_str(), strDan.length() );

		string strComMad = value[ a ++ ].GetString();
		memset(dailyTask.comMadValue, 0, sizeof(dailyTask.comMadValue));
		memcpy(dailyTask.comMadValue, strComMad.c_str(), strComMad.length() );

		string strPower = value[ a ++ ].GetString();
		memset(dailyTask.powerValue, 0, sizeof(dailyTask.powerValue));
		memcpy(dailyTask.powerValue, strPower.c_str(), strPower.length() );

		dailyTask.teamExp = value[ a ++ ].GetInt();

		dailyTaskVector.push_back(dailyTask);
	}
}

void DataManager::PvpDailyGainsParser()
{
	string filename = "DataManager/PvpDailyGains.json";  
	rapidjson::Document doc;   
	if( !FileUtils::getInstance()->isFileExist(filename) )  
	{  
		CCASSERT(false, "Json File IS NOT FIND");
		return;
	}   
	string data = FileUtils::getInstance()->getStringFromFile(filename);  
	doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());   
	if (doc.HasParseError())  
	{  
		CCASSERT(false, "Get Json Data Error");
		return;
	}  

	pvpDailyGainsVector.clear();
	for( unsigned int index = 1; index < doc.Size(); index ++ )  
	{
		int json = 1;
		auto &value = doc[ index ];
		PvpDailyGainsStruct pvpDailyGains = {0};

		pvpDailyGains.rank = value[json++].GetInt();				/* 排名 */
		pvpDailyGains.coin = value[json++].GetInt();				/* 金币 */
		pvpDailyGains.exploit = value[json++].GetInt();				/* 功勋 */

		pvpDailyGainsVector.push_back(pvpDailyGains);
	}
}

void DataManager::PvpPkGainsParser()
{
	string filename = "DataManager/PvpPkGains.json";  
	rapidjson::Document doc;   
	if( !FileUtils::getInstance()->isFileExist(filename) )  
	{  
		CCASSERT(false, "Json File IS NOT FIND");
		return;
	}   
	string data = FileUtils::getInstance()->getStringFromFile(filename);  
	doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());   
	if (doc.HasParseError())  
	{  
		CCASSERT(false, "Get Json Data Error");
		return;
	}  

	pvpDailyGainsVector.clear();
	for( unsigned int index = 1; index < doc.Size(); index ++ )  
	{
		int json = 1;
		auto &value = doc[ index ];
		PvpPkGainsStruct pvpPkGains = {0};

		pvpPkGains.rank = value[json++].GetInt();				/* 排名 */
		pvpPkGains.coin[0] = value[json++].GetInt();			/* 金币胜利 */
		pvpPkGains.coin[1] = value[json++].GetInt();			/* 金币败北 */
		pvpPkGains.exploit[0] = value[json++].GetInt();			/* 功勋胜利 */
		pvpPkGains.exploit[1] = value[json++].GetInt();			/* 功勋败北 */

		pvpPkGainsVector.push_back(pvpPkGains);
	}
}

void DataManager::storeLocalDataParser()
{
	string filename = "DataManager/StoreGoods.json";  
	rapidjson::Document doc;   
	if( !FileUtils::getInstance()->isFileExist(filename) )  
	{  
		CCASSERT(false, "Json File IS NOT FIND");
		return;
	}   
	string data = FileUtils::getInstance()->getStringFromFile(filename);  
	doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());   
	if (doc.HasParseError())  
	{  
		CCASSERT(false, "Get Json Data Error");
		return;
	}  

	localStoreDataVector.clear();
	for( unsigned int index = 1; index < doc.Size(); index ++ )  
	{
		int json = 0;
		auto &value = doc[ index ];
		StoreLocalDataStruct storeData;
		memset(&storeData, 0, sizeof(storeData));

		string idString = value[ json ++ ].GetString();
		memset(storeData.idRange, 0, sizeof(storeData.idRange));
		memcpy(storeData.idRange, idString.c_str(), idString.length());

		storeData.goodType = value[ json++ ].GetInt();				
		storeData.coinPrice = value[ json++ ].GetInt();				
		storeData.diamondPrice = value[ json++ ].GetInt();			
		localStoreDataVector.push_back(storeData);
	}
}

void DataManager::AchievementLocalDataParser()
{
	string filePath = FileUtils::getInstance()->getWritablePath();
	string filename= filePath + "DataManager/AchievementSystem.json";  
	rapidjson::Document doc;   
	if( !FileUtils::getInstance()->isFileExist(filename) )  
	{  
		CCASSERT(false, "Json File IS NOT FIND");
		return;
	}   
	string data = FileUtils::getInstance()->getStringFromFile(filename);  
	doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());   
	if (doc.HasParseError())  
	{  
		CCASSERT(false, "Get Json Data Error");
		return;
	}  
	localAchievementDataVector.clear();
	for( unsigned int index = 1; index < doc.Size(); index ++ )  
	{
		int json = 0;
		auto &value = doc[ index ];
		AchievementLocalDataStruct achievementData;
		memset(&achievementData, 0, sizeof(achievementData));

		achievementData.CID = value[ json ++ ].GetInt();

		string idString = value[ json ++ ].GetString();
		memset(achievementData.CName, 0, sizeof(achievementData.CName));
		memcpy(achievementData.CName, idString.c_str(), idString.length());
		
		idString = value[ json ++ ].GetString();
		memset(achievementData.Condition, 0, sizeof(achievementData.Condition));
		memcpy(achievementData.Condition, idString.c_str(), idString.length());

		achievementData.num = value[ json ++ ].GetInt();

		idString = value[ json ++ ].GetString();
		memset(achievementData.Coin, 0, sizeof(achievementData.Coin));
		memcpy(achievementData.Coin, idString.c_str(), idString.length());

		idString = value[ json ++ ].GetString();
		memset(achievementData.Diamond, 0, sizeof(achievementData.Diamond));
		memcpy(achievementData.Diamond, idString.c_str(), idString.length());

		idString = value[ json ++ ].GetString();
		memset(achievementData.General, 0, sizeof(achievementData.General));
		memcpy(achievementData.General, idString.c_str(), idString.length());

		idString = value[ json ++ ].GetString();
		memset(achievementData.GeneralChip, 0, sizeof(achievementData.GeneralChip));
		memcpy(achievementData.GeneralChip, idString.c_str(), idString.length());

		achievementData.Dan = value[ json ++ ].GetInt();
		achievementData.Soul = value[ json ++ ].GetInt();
		achievementData.SimpleMad = value[ json ++ ].GetInt();

		idString = value[ json ++ ].GetString();
		memset(achievementData.WhiteEquip, 0, sizeof(achievementData.WhiteEquip));
		memcpy(achievementData.WhiteEquip, idString.c_str(), idString.length());

		idString = value[ json ++ ].GetString();
		memset(achievementData.WhiteSpecial, 0, sizeof(achievementData.WhiteSpecial));
		memcpy(achievementData.WhiteSpecial, idString.c_str(), idString.length());

		achievementData.TeamExp = value[ json ++ ].GetInt();

		localAchievementDataVector.push_back(achievementData);
	}

}

void DataManager::OneStartGameStory()
{
	string filename = "DataManager/OpeningCredits.json";
	rapidjson::Document doc;
	if ( !FileUtils::getInstance()->isFileExist(filename) )
	{
		CCASSERT(false, "Json File IS NOT FIND");
		return;
	}
	string data = FileUtils::getInstance()->getStringFromFile(filename);  
	doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());   
	if (doc.HasParseError())  
	{  
		CCASSERT(false, "Get Json Data Error");
		return;
	}

	localOnceStartVector.clear();

	for ( unsigned int i = 1; i < doc.Size(); i ++ )
	{
		rapidjson::Value &value = doc[i];
		int a = 0;
		satrtGameStruct GamestoryStruct;
		memset(&GamestoryStruct, 0, sizeof(GamestoryStruct));

		std::string str = value[a++].GetString();
		memset(GamestoryStruct.OpenStory,0,sizeof(GamestoryStruct.OpenStory));
		memcpy(GamestoryStruct.OpenStory,str.c_str(),sizeof(GamestoryStruct.OpenStory));

		localOnceStartVector.push_back(GamestoryStruct);
	}
}

int DataManager::sortGoodsNum()
{
	return goodsNum;
}

int DataManager::curPvpRank()
{
	return pvpRank;
}

bool DataManager::curPvpPass()
{
	return pvpResult;
}

std::vector<int > DataManager::getGeneralGrowthVector()
{
	return generalGrowthVector;
}

ItemEquipStruct DataManager::interItemEquipStruct()
{
	return itemEquip;
}

vector<SeriveAreaRecvStruct > DataManager::interSeriveAreaVector()
{
	return serviceAreaRecvVector;
}

vector<MaidanStruct > DataManager::interMaidanVector()
{
	return maidanRecvVector;
}

vector<GeneralDetailRecvStruct > DataManager::interGeneralVector()
{
	return generalDetailRecvVector;
}

vector<WareroomCommonRecvStruct > DataManager::interWareroomPropVector()
{
	return wareroomPropVector;
}

vector<WareroomCommonRecvStruct > DataManager::interWareroomEquipVector()
{
	return wareroomEquipVector;
}

vector<WareroomCommonRecvStruct > DataManager::interWareroomChipVector()
{
	return wareroomChipVector;
}

vector<PointSetsRecvStruct > DataManager::interPointSetsVector()
{
	return pointSetRecvVector;
}

vector<PlayerInfoRecvStruct > DataManager::interPlayerInfoVector()
{
	return playerInfoVector;
}

vector<TeamInfoStruct > DataManager::interTeamInfoVector()
{
	return teamInfoVector;
}

vector<int > DataManager::interTalentVectors()
{
	return interTalentVector;
}

vector<PlayerStateRecvStruct > DataManager::interPlayerStateVector()
{
	return playerStateVector;
}

vector<DrawoffCountZeroRecvStruct > DataManager::interCountZeroVector()
{
	return countZeroVector;
}

vector<ServiceDayTimeRecvStruct > DataManager::interDayTimesVector()
{
	return serviceDayTimeVector;
}

vector<JxxgBuffInfoRecvStruct > DataManager::interJxxgBuffVector()
{
	isGetJxxgBuffInfo();
	return jxxgBuffVector;
}

vector<PvpCompetitorRecvStruct > DataManager::interPvpCompetitorVector()
{
	return pvpCompetitorVector;
}

vector<PvpPlayerTeamRecvStruct > DataManager::interPvpPlayerTeamVector(int id)
{
	return pvpPlayerTeamVector;
}

vector<PvpRecordRecvStruct > DataManager::interPvpRecordVector()
{
	return pvpRecordVector;
}

vector<PvpRankRecvStruct > DataManager::interPvpRankingVector()
{
	return pvpRankingVector;
}

vector<WareroomGridRecvStruct > DataManager::interWareroomVector()
{
	return wareroomGridVector;
}

vector<PropProptyStruct > DataManager::localPropProptyVector()
{
	return propProptyVector;
}

vector<GeneralProptyStruct > DataManager::localGeneralProptyVector()
{
	return generalProptyVector;
}

vector<EquipProptyStruct > DataManager::localEquipProptyVector()
{
	return equipProptyVector;
}

vector<EquipRefineStruct > DataManager::localEquipRefineVector()
{
	if (0 == equipRefineVector.size())
	{
		equipRefineRule();
	}
	return equipRefineVector;
}

vector<PointCellInfoStruct > DataManager::localPointCellInfoVector()
{
	if (0 == pointCellInfoVector.size())
	{
		pointCellInfoParse();
	}

	return pointCellInfoVector;
}

vector<CheckPointStruct > DataManager::localCheckPointVector()
{
	return checkPointPropthVector;
}

vector<SignInStruct > DataManager::localSignInVector()
{
	return signInVector;
}

vector<DrawoffIDRecvStruct > DataManager::localDrawoffIDVector()
{
	return drawoffIDVector;
}

vector<DrawoffRecvStruct > DataManager::localDrawoffVector()
{
	return drawoffVector;
}
vector<StoreListRecvStruct > DataManager::localStoreVector(){
	return storeListVector;
}
vector<BoxRecvStruct > DataManager::localBoxVector()
{
	return boxVector;
}

vector<PointGainsStruct > DataManager::localPointGainsVector()
{
	if (0 == pointGainsVector.size())
	{
		pointGainsParse();
	}
	return pointGainsVector;
}

vector<GeneralChipRecvStruct > DataManager::localGeneralChipVector()
{
	return generalChipVector;
}

vector<EquipChipRecvStruct > DataManager::localEquipChipVector()
{
	return equipChipVector;
}

vector<SkillNameStruct > DataManager::localSkillNameVector()
{
	return skillNameVector;
}

vector<SkillUpgradeStruct > DataManager::localSkillUpgradeVector()
{
	return skillUpgradeVector;
}

vector<GeneralEvoLocalStruct > DataManager::localGeneralEvoVector()
{
	return generalEvoLocalVector;
}

vector<GeneralEvoExpLocalStruct > DataManager::localGeneralEvoExpVector()
{
	return generalEvoExpLocalVector;
}

vector<CustomsPassRecvStruct > DataManager::interCustomsPassVector()
{
	return customsPassVector;
}

vector<BuyCPLocalStruct > DataManager::localBuyCPVector()
{
	return buyCPLocalVector;
}

vector<GeneralUpgradeStruct > DataManager::localGeneralUpgradeVector()
{
	if (0 == generalUpgradeDataVector.size())
	{
		generalUpgradeDataParser();
	}
	return generalUpgradeDataVector;
}

vector<TalentLocalStruct > DataManager::localtalentVector()
{
	return talentLocalVector;
}

vector<TeamUpgradeLocalStrcut > DataManager::localTeamUpgradeLocalVector()
{
	if (0 == teamUpgradeLocalVector.size())
	{
		teamUpgradeDataParser();
	}
	return teamUpgradeLocalVector;
}

vector<SkillAddPropty > DataManager::localSkillAddProptyVec()
{
	return localSkillAddProptyVector;
}

map<string, SkillRegionStruct > DataManager::localSkillRegionMap()
{
	if (0 == skillRegionMap.size())
	{
		skillRegionParser();
	}

	return skillRegionMap;
}

map<string, SubInfoStruct > DataManager::localSubInfoMap()
{
	if (0 == subInfoMap.size())
	{
		subInfoParser();
	}

	return subInfoMap;
}

vector<DailyTaskLocalStruct > DataManager::localDailyTaskVector()
{
	if (dailyTaskVector.size() == 0)
	{
		dailyTaskDateParser();
	}
	return dailyTaskVector;
}

vector<PvpDailyGainsStruct > DataManager::localPvpDailyGainsVector()
{
	if (0 == pvpDailyGainsVector.size())
	{
		PvpDailyGainsParser();
	}

	return pvpDailyGainsVector;
}

vector<PvpPkGainsStruct > DataManager::localPvpPkGainsVector()
{
	if (0 == pvpPkGainsVector.size())
	{
		PvpPkGainsParser();
	}

	return pvpPkGainsVector;
}

vector<StoreLocalDataStruct > DataManager::localStoreListDataVector()
{
	if ( localStoreDataVector.size() == 0 )
	{
		storeLocalDataParser();
	}
	return localStoreDataVector;
}

vector<AchievementLocalDataStruct> DataManager::localAchievementListDataVector()
{
	if (localAchievementDataVector.size() == 0)
	{
		AchievementLocalDataParser();
	}
	return localAchievementDataVector;
}

vector<satrtGameStruct > DataManager::localOnceGameVector()
{
	if (localOnceStartVector.size() == 0)
	{
		OneStartGameStory();
	}
	return localOnceStartVector;
}
