 /*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名： DBUtil
** 日期：   2015:7:1
** 说明：	SQlite数据库功能封装
** 其它：	
** 历史：2015:7:1 初始版本
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "sqlite3.h"


USING_NS_CC;
using namespace std;

enum EnumTable
{
	Table_Player = 0,				/* 玩家表 */
	Table_Item,						/* 物品表 */
	Table_gMain,					/* 武将表(总表) */
	Table_gGrowth,					/* 武将表(成长表) */
	Table_gSkill,					/* 武将表(技能表) */
	Table_gEquip,					/* 武将表(装备表) */
	Table_gTalent,					/* 武将表(天赋表) */
	Table_Point,					/* 关卡表 */
	Table_Jxxg,						/* 稷下学宫表 */
	Table_Max
};

class DBUtil
{
private:
    DBUtil();    
    virtual ~DBUtil();
    
public :
    static DBUtil* getInstance();    
    static void destoryInstance();

public:
	std::string getTableName(EnumTable);
	void CreateTable_Player();										/* 玩家表 */
	void CreateTable_Item();										/* 物品表 */
	void CreateTable_GeneralMain();									/* 武将表(总表) */
	void CreateTable_GeneralGrowth();								/* 武将表(成长表) */
	void CreateTable_GeneralSkill();								/* 武将表(技能表) */
	void CreateTable_GeneralEquip();								/* 武将表(装备表) */
	void CreateTable_GeneralTalent();								/* 武将表(天赋表) */
	void CreateTable_Point();										/* 关卡表 */
	void CreateTable_Jxxg();										/* 稷下学宫表 */
	
public:
    /**
     *  创建数据表
     *
     *  @param aSql       建表sql语句
     *  @param aTableName 表名
     */
    bool createTable(std::string aSql, std::string aTableName);
    
    /**
     *  通过表名查询该表是否存在
     *
     *  @param aTabelName 表名
     *
     *  @return true: 存在 false: 不存在
     */
    bool isExistTableByName(std::string aTabelName);
    
    /**
     *  删除数据表
     *
     *  @param aSql       删表sql语句
     *  @param aTableName 表名
     */
    bool deleteTable(std::string aSql, std::string aTableName);
    
    /**
     *  插入记录
     *
     *  @param aSql 插入数据sql语句
     */
    bool insertData(std::string aSql);
    
    /**
     *  删除记录
     *
     *  @param aSql 删除数据sql语句
     */
    bool deleteData(std::string aSql);
    
    /**
     *  修改记录
     *
     *  @param aSql 修改数据sql语句
     */
    bool updateData(std::string aSql);
    
    /**
     *  查询记录
     *
     *  @param aSql     修改数据sql语句
     */
    std::vector<std::map<std::string, std::string> >searchData(std::string aSql);
    
    /**
     *  查询记录的条数
     *
     *  @param sql 查询记录sql语句
     *
     *  @return 记录条数
     */
    int searchDataCount(std::string aSql);
    
    /**
     *  开始事务
     *
     *  @return 操作结果(sqlite3提供的宏)
     */
    int beginTransaction();
    
    /**
     *  提交事务(失败回滚)
     *
     *  @param aResult       操作结果
     *
     *  @return 操作结果(sqlite3提供的宏)
     */
	int commitTransaction(int aResult);
    
protected:
    /**
     *  打开数据库(创建)
     *
     *  @param aDataBaseName 数据库名
     */
    void openDBWithName(std::string aDataBaseName = "");
    
    /**
     *  关闭数据库
     */
    void closeDB();

private:
	sqlite3* m_pDataBase;							/* 数据库 */
	std::string m_strDBName;
};