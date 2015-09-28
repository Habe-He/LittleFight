#include "DBUtil.h"

static DBUtil* s_pInstance = NULL;
const std::string strDBTables[Table_Max] = 
{
	"player",					/* 玩家表 */
	"item",						/* 物品表 */
	"gMain",					/* 武将表(总表) */
	"gGrowth",					/* 武将表(成长表) */
	"gSkill",					/* 武将表(技能表) */
	"gEquip",					/* 武将表(装备表) */
	"gTalent",					/* 武将表(天赋表) */
	"point",					/* 关卡表 */
	"jxxg",						/* 稷下学宫表 */
};

DBUtil::DBUtil()
	: m_pDataBase(NULL)
	, m_strDBName("LittleFight.db")
{
}

DBUtil::~DBUtil()
{
}

DBUtil* DBUtil::getInstance()
{
    if (!s_pInstance)
	{
        s_pInstance = new DBUtil();
    }
    return s_pInstance;
}

void DBUtil::destoryInstance()
{
    delete s_pInstance;
    s_pInstance = NULL;
}

std::string DBUtil::getTableName(EnumTable table)
{
	return strDBTables[table];
}

/* 玩家表 */
void DBUtil::CreateTable_Player()
{
	std::string strSql = 
		"create table " + strDBTables[Table_Player] +
		//"name text primary key,"									/* 帐号名字 */
		"(level integer,"											/* 帐号等级 */
		"exp integer,"												/* 帐号经验 */
		"coin integer,"												/* 帐号金币 */
		"diamond integer,"											/* 帐号钻石 */
		"guide integer,"											/* 新手指引 */
		"propGrid integer,"											// 道具格子
		"euipGrid integer,"											
		"chipGrid integer)";

	if ( createTable(strSql, strDBTables[Table_Player]) )
	{
		std::string insretSql = " insert into " + strDBTables[Table_Player] + " (level, exp, coin, diamond, guide, propGrid, euipGrid, chipGrid) values (1, 0, 0, 0, 0, 80, 80, 80) ";
		if (true == insertData(insretSql))
		{
		}
	}
}

/* 物品表 */
void DBUtil::CreateTable_Item()
{
	std::string strSql = 
		"create table " + strDBTables[Table_Item] + 
		"(PKID integer primary key autoincrement,"					/* 物品PKID */
		"ID integer,"												/* 物品ID */
		"type integer,"												/* 物品类型 */
		"isSelect integer,"											/* 物品是否正被使用 */
		"count integer,"											/* 物品数量 */
		"level integer,"											/* 物品等级 */
		"exp integer)";												/* 物品经验 */

	createTable(strSql, strDBTables[Table_Item]);
}

/* 武将表(总表) */
void DBUtil::CreateTable_GeneralMain()
{
	std::string strSql = 
		"create table " + strDBTables[Table_gMain] + 
		"(PKID integer primary key autoincrement,"					/* 武将PKID */
		"ID integer,"												/* 武将ID */
		"star integer,"												/* 武将星级 */
		"level integer,"											/* 武将等级 */
		"lExp integer,"												/* 武将强化经验 */
		"step integer,"												/* 武将进阶等级 */
		"sExp integer,"												/* 武将进化经验 */
		"appoint int)";												/* 武将任命 */

	createTable(strSql, strDBTables[Table_gMain]);
}

/*  武将表(成长表) */
void DBUtil::CreateTable_GeneralGrowth()
{
	std::string strSql = 
		"create table " + strDBTables[Table_gGrowth] + 
		"(PKID integer primary key autoincrement,"					/* 武将PKID */
		"ID integer,"												/* 武将ID */
		"atk integer,"												/* 武将攻击力成长 */
		"hp integer,"												/* 武将HP上限成长 */
		"pd integer,"												/* 武将物防成长 */
		"md integer)";												/* 武将法防成长 */

	createTable(strSql, strDBTables[Table_gGrowth]);
}

/*  武将表(技能表) */
void DBUtil::CreateTable_GeneralSkill()
{
	std::string strSql = 
		"create table " + strDBTables[Table_gSkill] + 
		"(PKID integer primary key autoincrement,"					/* 武将PKID */
		"ID integer,"												/* 武将ID */
		"lv1 integer,"												/* 武将技能1等级 */
		"lv2 integer,"												/* 武将技能2等级 */
		"lv3 integer,"												/* 武将技能3等级 */
		"lv4 integer)";												/* 武将技能4等级 */

	createTable(strSql, strDBTables[Table_gSkill]);
}

/* 武将表(装备表) */
void DBUtil::CreateTable_GeneralEquip()
{
	std::string strSql = 
		"create table " + strDBTables[Table_gEquip] + 
		"(PKID integer primary key autoincrement,"					/* 武将PKID */
		"ID integer,"												/* 武将ID */
		"equip1 integer,"											/* 武将技能1等级 */
		"equip2 integer,"											/* 武将技能2等级 */
		"equip3 integer,"											/* 武将技能3等级 */
		"equip4 integer,"											/* 武将技能4等级 */
		"equip5 integer,"											/* 武将技能5等级 */
		"equip6 integer)";											/* 武将技能6等级 */

	createTable(strSql, strDBTables[Table_gEquip]);
}

/* 武将表(天赋表) */
void DBUtil::CreateTable_GeneralTalent()
{
	std::string strSql = 
		"create table " + strDBTables[Table_gTalent] + 
		"(PKID integer primary key autoincrement,"					/* 武将PKID */
		"ID integer,"												/* 武将ID */
		"talent1 integer,"											/* 武将天赋1 */
		"talent2 integer,"											/* 武将天赋2 */
		"talent3 integer,"											/* 武将天赋3 */
		"talent4 integer)";											/* 武将天赋6 */

	createTable(strSql, strDBTables[Table_gTalent]);
}

/* 关卡表 */
void DBUtil::CreateTable_Point()
{
	std::string strSql = 
		"create table " + strDBTables[Table_Point] + 
		"(ID integer primary key,"									/* 关卡ID */
		"star integer)";											/* 关卡星级 */

	createTable(strSql, strDBTables[Table_Point]);
}

/* 稷下学宫表 */
void DBUtil::CreateTable_Jxxg()
{
	std::string strSql = 
		"create table " + strDBTables[Table_Jxxg] + 
		"(mode integer primary key,"								/* 稷下学宫模式 */
		"ticket integer,"											/* 进入次数 */
		"reward integer,"											/* 奖励Buff ID */
		"times integer)";											/* 奖励Buff 次数 */

	if (true == createTable(strSql, strDBTables[Table_Jxxg]))
	{
		for (int index = 0;index < 4;index ++)
		{
			char mode[2] = {0};
			sprintf(mode, "%d", index);
			std::string str = "Insert Into " + strDBTables[Table_Jxxg] + " Values(" + mode +  ", 0, 0, 0)";
			insertData(str);
		}
	}
}

/**
 *  创建数据表
 *
 *  @param aSql       建表sql语句
 *  @param aTableName 表名
 *
 *  @usage string sql = "create table user(id integer, username text, password text)";
 */
bool DBUtil::createTable(std::string aSql, std::string aTableName)
{
	bool bRet = false;

    openDBWithName(m_strDBName);    
    if (!isExistTableByName(aTableName))
	{
		char *errMsg = NULL;
        int result = sqlite3_exec(m_pDataBase, aSql.c_str(), NULL, NULL, &errMsg);
        if (result == SQLITE_OK)
		{
			bRet = true;
		}

		if (NULL != errMsg)
		{
			sqlite3_free(errMsg);
			errMsg = NULL;
		}
    }
    
    closeDB();

	return bRet;
}

/**
 *  是否存在某张数据表的查询回调
 *
 *  @return 0
 */
int isExistTableCallback(void* para, int n_column, char ** column_value, char ** column_name)
{
    bool *isExisted_ = (bool*)para;
    *isExisted_ = (**column_value) != '0';
    return 0;
}

/**
 *  通过表名查询该表是否存在
 *
 *  @param aTabelName 表秒
 *
 *  @return true: 存在 false: 不存在
 */
bool DBUtil::isExistTableByName(std::string aTabelName)
{
    if (NULL != m_pDataBase)
	{
        bool isExist;												//判断表是否存在
		char *errMsg = NULL;
        std::string sql = "select count(type) from sqlite_master where type = 'table' and name = '" + aTabelName + "'";
        int result = sqlite3_exec(m_pDataBase, sql.c_str(), isExistTableCallback, &isExist, &errMsg);
        
		if (NULL != errMsg)
		{
			sqlite3_free(errMsg);
			errMsg = NULL;
		}
        
        return isExist;
    }
    
    return false;
}

/**
 *  删除数据表
 *
 *  @param aSql       删表sql语句
 *  @param aTableName 表名
 *
 *  @usage string sql = "drop table name";
 */
bool DBUtil::deleteTable(std::string aSql, std::string aTableName)
{
	bool bRet = false;
    openDBWithName(m_strDBName);    
    beginTransaction();
    
    int result = 0;
    if (isExistTableByName(aTableName))
	{
        char* errMsg = NULL;
        result = sqlite3_exec(m_pDataBase, aSql.c_str(), NULL, NULL, &errMsg);
        if (result == SQLITE_OK)
		{
			bRet = true;
		}
        
        if (NULL != errMsg)
		{
            sqlite3_free(errMsg);
            errMsg = NULL;
        }
    }
    
    commitTransaction(result);    
    closeDB();
	
	return bRet;
}

/**
 *  插入记录
 *
 *  @param aSql 插入数据sql语句
 *
 *  @usage string sql = "insert into User(name) values ('cc') ";
 */
bool DBUtil::insertData(std::string aSql)
{
	bool bRet = false;
    openDBWithName(m_strDBName);    
    beginTransaction();
    
	char* errMsg = NULL;
    int result = sqlite3_exec(m_pDataBase, aSql.c_str(), NULL, NULL, &errMsg);
    if (result == SQLITE_OK)
	{
		bRet = true;
	}
    
    if (NULL != errMsg)
	{
        sqlite3_free(errMsg);
        errMsg = NULL;
    }
    
    commitTransaction(result);    
    closeDB();

	return bRet;
}

/**
 *  删除记录
 *
 *  @param aSql 插入数据sql语句
 *
 *  @usage string sql = "delete from User where name = 'cc'";
 */
bool DBUtil::deleteData(std::string aSql)
{
	bool bRet = false;
    openDBWithName(m_strDBName);
    beginTransaction();
    
    char* errMsg = NULL;
    int result = sqlite3_exec(m_pDataBase, aSql.c_str(), NULL, NULL, &errMsg);
    if (result == SQLITE_OK )
	{
		bRet = true;
	}
    
    if (NULL != errMsg)
	{
        sqlite3_free(errMsg);
        errMsg = NULL;
    }
    
    commitTransaction(result);    
    closeDB();

	return bRet;
}

/**
 *  修改记录
 *
 *  @param aSql 修改数据sql语句
 */
bool DBUtil::updateData(std::string aSql)
{
	bool bRet = false;
    openDBWithName(m_strDBName);    
    beginTransaction();
    
    char* errMsg = NULL;
    int result = sqlite3_exec(m_pDataBase, aSql.c_str(), NULL, NULL, &errMsg );
    if (result == SQLITE_OK)
	{
		bRet = true;
	}
    
    if (NULL != errMsg)
	{
        sqlite3_free(errMsg);
        errMsg = NULL;
    }
    
    commitTransaction(result);    
    closeDB();

	return bRet;
}

/**
 *  查询回调
 *
 *  @return 0
 */
int searchDataCallback(void* para, int n_column, char** column_value, char** column_name)
{
    std::map<std::string, std::string> mapResults ;
    for (int i = 0; i < n_column; i++)
	{
        mapResults.insert(std::make_pair<std::string, std::string>((std::string)column_name[i], (std::string)column_value[i]));
    }
    std::vector<std::map<std::string, std::string> >* vect = (std::vector<std::map<std::string, std::string> >*)para;
    vect->push_back(mapResults);
    return 0;
}


/**
 *  查询记录
 *
 *  @param aSql     查询数据sql语句
 */
std::vector<std::map<std::string, std::string> > DBUtil::searchData(std::string aSql)
{
    openDBWithName(m_strDBName);
    
    //vector是查询的结果集，每一个结果都存在map中
    //map的第一string是key(字段名)，第二个string是value(查询出的对应数据)
    std::vector<std::map<std::string, std::string> > vec;
    
    char* errMsg = NULL;
    int result = sqlite3_exec(m_pDataBase, aSql.c_str(), searchDataCallback, &vec, &errMsg);
    
    if (NULL != errMsg)
	{
        sqlite3_free(errMsg);
        errMsg = NULL;
    }
    
    closeDB();    
    return vec;
}

/**
 *  查询数据条数回调
 *
 *  @return 0
 */
int searchDataCountCallback(void* para, int n_column, char** column_value, char** column_name)
{
    int* count = (int*)para;
    *count = (int)atof(column_value[0]);
    return 0;
}

/**
 *  查询记录的条数
 *
 *  @param sql 查询记录sql语句
 *
 *  @return 记录条数
 */
int DBUtil::searchDataCount(std::string aSql)
{
    openDBWithName(m_strDBName);
    
    int count = 0;
    char* errMsg = NULL;
    int result = sqlite3_exec(m_pDataBase, aSql.c_str(), searchDataCountCallback, &count, &errMsg);
    
    if (NULL != errMsg)
	{
        sqlite3_free(errMsg);
        errMsg = NULL;
    }
    
    closeDB();
    
    return count;
}

/**
 *  开始事务
 *
 *  @return 操作结果(sqlite3提供的宏)
 */
int DBUtil::beginTransaction()
{
    char* errMsg = NULL;
    int result = sqlite3_exec(m_pDataBase, "begin transaction", 0, 0, &errMsg);

    return result;
}

/**
 *  提交事务(失败回滚)
 *
 *  @param aResult       操作结果
 *
 *  @return 操作结果(sqlite3提供的宏)
 */
int DBUtil::commitTransaction(int aResult)
{
	int result = 0;

    if (aResult == SQLITE_OK)
	{
        char* errMsg = NULL;
        result = sqlite3_exec(m_pDataBase, "commit transaction", 0, 0, &errMsg);
    }
	else
	{
        char* errMsg = NULL;
        int result = sqlite3_exec(m_pDataBase, "rollback transaction", 0, 0, &errMsg);
	}

	return result;
}

/**
 *  打开数据库(创建)
 *
 *  @param aDataBaseName 数据库名
 */
void DBUtil::openDBWithName(std::string aDataBaseName)
{
	if (true == aDataBaseName.empty())
	{
		aDataBaseName = m_strDBName;
	}
	
    std::string dbPath = FileUtils::getInstance()->getWritablePath() + aDataBaseName;
    
    int result = sqlite3_open(dbPath.c_str(), &m_pDataBase);
    if (result != SQLITE_OK)
	{
		auto errMsg = sqlite3_errmsg(m_pDataBase);
    }

	m_strDBName = aDataBaseName;
}

/**
 *  关闭数据库
 */
void DBUtil::closeDB()
{
    if (NULL != m_pDataBase)
	{
        sqlite3_close(m_pDataBase);
        m_pDataBase = NULL;
    }
}