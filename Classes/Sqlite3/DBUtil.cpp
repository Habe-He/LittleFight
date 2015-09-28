#include "DBUtil.h"

static DBUtil* s_pInstance = NULL;
const std::string strDBTables[Table_Max] = 
{
	"player",					/* ��ұ� */
	"item",						/* ��Ʒ�� */
	"gMain",					/* �佫��(�ܱ�) */
	"gGrowth",					/* �佫��(�ɳ���) */
	"gSkill",					/* �佫��(���ܱ�) */
	"gEquip",					/* �佫��(װ����) */
	"gTalent",					/* �佫��(�츳��) */
	"point",					/* �ؿ��� */
	"jxxg",						/* ���ѧ���� */
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

/* ��ұ� */
void DBUtil::CreateTable_Player()
{
	std::string strSql = 
		"create table " + strDBTables[Table_Player] +
		//"name text primary key,"									/* �ʺ����� */
		"(level integer,"											/* �ʺŵȼ� */
		"exp integer,"												/* �ʺž��� */
		"coin integer,"												/* �ʺŽ�� */
		"diamond integer,"											/* �ʺ���ʯ */
		"guide integer,"											/* ����ָ�� */
		"propGrid integer,"											// ���߸���
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

/* ��Ʒ�� */
void DBUtil::CreateTable_Item()
{
	std::string strSql = 
		"create table " + strDBTables[Table_Item] + 
		"(PKID integer primary key autoincrement,"					/* ��ƷPKID */
		"ID integer,"												/* ��ƷID */
		"type integer,"												/* ��Ʒ���� */
		"isSelect integer,"											/* ��Ʒ�Ƿ�����ʹ�� */
		"count integer,"											/* ��Ʒ���� */
		"level integer,"											/* ��Ʒ�ȼ� */
		"exp integer)";												/* ��Ʒ���� */

	createTable(strSql, strDBTables[Table_Item]);
}

/* �佫��(�ܱ�) */
void DBUtil::CreateTable_GeneralMain()
{
	std::string strSql = 
		"create table " + strDBTables[Table_gMain] + 
		"(PKID integer primary key autoincrement,"					/* �佫PKID */
		"ID integer,"												/* �佫ID */
		"star integer,"												/* �佫�Ǽ� */
		"level integer,"											/* �佫�ȼ� */
		"lExp integer,"												/* �佫ǿ������ */
		"step integer,"												/* �佫���׵ȼ� */
		"sExp integer,"												/* �佫�������� */
		"appoint int)";												/* �佫���� */

	createTable(strSql, strDBTables[Table_gMain]);
}

/*  �佫��(�ɳ���) */
void DBUtil::CreateTable_GeneralGrowth()
{
	std::string strSql = 
		"create table " + strDBTables[Table_gGrowth] + 
		"(PKID integer primary key autoincrement,"					/* �佫PKID */
		"ID integer,"												/* �佫ID */
		"atk integer,"												/* �佫�������ɳ� */
		"hp integer,"												/* �佫HP���޳ɳ� */
		"pd integer,"												/* �佫����ɳ� */
		"md integer)";												/* �佫�����ɳ� */

	createTable(strSql, strDBTables[Table_gGrowth]);
}

/*  �佫��(���ܱ�) */
void DBUtil::CreateTable_GeneralSkill()
{
	std::string strSql = 
		"create table " + strDBTables[Table_gSkill] + 
		"(PKID integer primary key autoincrement,"					/* �佫PKID */
		"ID integer,"												/* �佫ID */
		"lv1 integer,"												/* �佫����1�ȼ� */
		"lv2 integer,"												/* �佫����2�ȼ� */
		"lv3 integer,"												/* �佫����3�ȼ� */
		"lv4 integer)";												/* �佫����4�ȼ� */

	createTable(strSql, strDBTables[Table_gSkill]);
}

/* �佫��(װ����) */
void DBUtil::CreateTable_GeneralEquip()
{
	std::string strSql = 
		"create table " + strDBTables[Table_gEquip] + 
		"(PKID integer primary key autoincrement,"					/* �佫PKID */
		"ID integer,"												/* �佫ID */
		"equip1 integer,"											/* �佫����1�ȼ� */
		"equip2 integer,"											/* �佫����2�ȼ� */
		"equip3 integer,"											/* �佫����3�ȼ� */
		"equip4 integer,"											/* �佫����4�ȼ� */
		"equip5 integer,"											/* �佫����5�ȼ� */
		"equip6 integer)";											/* �佫����6�ȼ� */

	createTable(strSql, strDBTables[Table_gEquip]);
}

/* �佫��(�츳��) */
void DBUtil::CreateTable_GeneralTalent()
{
	std::string strSql = 
		"create table " + strDBTables[Table_gTalent] + 
		"(PKID integer primary key autoincrement,"					/* �佫PKID */
		"ID integer,"												/* �佫ID */
		"talent1 integer,"											/* �佫�츳1 */
		"talent2 integer,"											/* �佫�츳2 */
		"talent3 integer,"											/* �佫�츳3 */
		"talent4 integer)";											/* �佫�츳6 */

	createTable(strSql, strDBTables[Table_gTalent]);
}

/* �ؿ��� */
void DBUtil::CreateTable_Point()
{
	std::string strSql = 
		"create table " + strDBTables[Table_Point] + 
		"(ID integer primary key,"									/* �ؿ�ID */
		"star integer)";											/* �ؿ��Ǽ� */

	createTable(strSql, strDBTables[Table_Point]);
}

/* ���ѧ���� */
void DBUtil::CreateTable_Jxxg()
{
	std::string strSql = 
		"create table " + strDBTables[Table_Jxxg] + 
		"(mode integer primary key,"								/* ���ѧ��ģʽ */
		"ticket integer,"											/* ������� */
		"reward integer,"											/* ����Buff ID */
		"times integer)";											/* ����Buff ���� */

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
 *  �������ݱ�
 *
 *  @param aSql       ����sql���
 *  @param aTableName ����
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
 *  �Ƿ����ĳ�����ݱ�Ĳ�ѯ�ص�
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
 *  ͨ��������ѯ�ñ��Ƿ����
 *
 *  @param aTabelName ����
 *
 *  @return true: ���� false: ������
 */
bool DBUtil::isExistTableByName(std::string aTabelName)
{
    if (NULL != m_pDataBase)
	{
        bool isExist;												//�жϱ��Ƿ����
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
 *  ɾ�����ݱ�
 *
 *  @param aSql       ɾ��sql���
 *  @param aTableName ����
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
 *  �����¼
 *
 *  @param aSql ��������sql���
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
 *  ɾ����¼
 *
 *  @param aSql ��������sql���
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
 *  �޸ļ�¼
 *
 *  @param aSql �޸�����sql���
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
 *  ��ѯ�ص�
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
 *  ��ѯ��¼
 *
 *  @param aSql     ��ѯ����sql���
 */
std::vector<std::map<std::string, std::string> > DBUtil::searchData(std::string aSql)
{
    openDBWithName(m_strDBName);
    
    //vector�ǲ�ѯ�Ľ������ÿһ�����������map��
    //map�ĵ�һstring��key(�ֶ���)���ڶ���string��value(��ѯ���Ķ�Ӧ����)
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
 *  ��ѯ���������ص�
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
 *  ��ѯ��¼������
 *
 *  @param sql ��ѯ��¼sql���
 *
 *  @return ��¼����
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
 *  ��ʼ����
 *
 *  @return �������(sqlite3�ṩ�ĺ�)
 */
int DBUtil::beginTransaction()
{
    char* errMsg = NULL;
    int result = sqlite3_exec(m_pDataBase, "begin transaction", 0, 0, &errMsg);

    return result;
}

/**
 *  �ύ����(ʧ�ܻع�)
 *
 *  @param aResult       �������
 *
 *  @return �������(sqlite3�ṩ�ĺ�)
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
 *  �����ݿ�(����)
 *
 *  @param aDataBaseName ���ݿ���
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
 *  �ر����ݿ�
 */
void DBUtil::closeDB()
{
    if (NULL != m_pDataBase)
	{
        sqlite3_close(m_pDataBase);
        m_pDataBase = NULL;
    }
}