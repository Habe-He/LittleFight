 /*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ����� DBUtil
** ���ڣ�   2015:7:1
** ˵����	SQlite���ݿ⹦�ܷ�װ
** ������	
** ��ʷ��2015:7:1 ��ʼ�汾
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "sqlite3.h"


USING_NS_CC;
using namespace std;

enum EnumTable
{
	Table_Player = 0,				/* ��ұ� */
	Table_Item,						/* ��Ʒ�� */
	Table_gMain,					/* �佫��(�ܱ�) */
	Table_gGrowth,					/* �佫��(�ɳ���) */
	Table_gSkill,					/* �佫��(���ܱ�) */
	Table_gEquip,					/* �佫��(װ����) */
	Table_gTalent,					/* �佫��(�츳��) */
	Table_Point,					/* �ؿ��� */
	Table_Jxxg,						/* ���ѧ���� */
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
	void CreateTable_Player();										/* ��ұ� */
	void CreateTable_Item();										/* ��Ʒ�� */
	void CreateTable_GeneralMain();									/* �佫��(�ܱ�) */
	void CreateTable_GeneralGrowth();								/* �佫��(�ɳ���) */
	void CreateTable_GeneralSkill();								/* �佫��(���ܱ�) */
	void CreateTable_GeneralEquip();								/* �佫��(װ����) */
	void CreateTable_GeneralTalent();								/* �佫��(�츳��) */
	void CreateTable_Point();										/* �ؿ��� */
	void CreateTable_Jxxg();										/* ���ѧ���� */
	
public:
    /**
     *  �������ݱ�
     *
     *  @param aSql       ����sql���
     *  @param aTableName ����
     */
    bool createTable(std::string aSql, std::string aTableName);
    
    /**
     *  ͨ��������ѯ�ñ��Ƿ����
     *
     *  @param aTabelName ����
     *
     *  @return true: ���� false: ������
     */
    bool isExistTableByName(std::string aTabelName);
    
    /**
     *  ɾ�����ݱ�
     *
     *  @param aSql       ɾ��sql���
     *  @param aTableName ����
     */
    bool deleteTable(std::string aSql, std::string aTableName);
    
    /**
     *  �����¼
     *
     *  @param aSql ��������sql���
     */
    bool insertData(std::string aSql);
    
    /**
     *  ɾ����¼
     *
     *  @param aSql ɾ������sql���
     */
    bool deleteData(std::string aSql);
    
    /**
     *  �޸ļ�¼
     *
     *  @param aSql �޸�����sql���
     */
    bool updateData(std::string aSql);
    
    /**
     *  ��ѯ��¼
     *
     *  @param aSql     �޸�����sql���
     */
    std::vector<std::map<std::string, std::string> >searchData(std::string aSql);
    
    /**
     *  ��ѯ��¼������
     *
     *  @param sql ��ѯ��¼sql���
     *
     *  @return ��¼����
     */
    int searchDataCount(std::string aSql);
    
    /**
     *  ��ʼ����
     *
     *  @return �������(sqlite3�ṩ�ĺ�)
     */
    int beginTransaction();
    
    /**
     *  �ύ����(ʧ�ܻع�)
     *
     *  @param aResult       �������
     *
     *  @return �������(sqlite3�ṩ�ĺ�)
     */
	int commitTransaction(int aResult);
    
protected:
    /**
     *  �����ݿ�(����)
     *
     *  @param aDataBaseName ���ݿ���
     */
    void openDBWithName(std::string aDataBaseName = "");
    
    /**
     *  �ر����ݿ�
     */
    void closeDB();

private:
	sqlite3* m_pDataBase;							/* ���ݿ� */
	std::string m_strDBName;
};