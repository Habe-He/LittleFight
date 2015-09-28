 /*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ����� RoleResInfo
** ���ڣ�   2015:4:17
** ˵����	��ɫ�ṹ��Ϣ
** ������	
** ��ʷ��2015:4:17 ��ʼ�汾
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include <map>
#include "DataManager/DataRecvEntities.h"

class RoleResInfo : public cocos2d::Ref
{
public:
	RoleResInfo(void);
	virtual ~RoleResInfo(void);

	static void init();
	static int getRoleResNum(std::string);
	static std::vector<std::string> roleInBattle(int);/* ��ȡ�����ɫ */
	static std::vector<std::string> getRoleInBattle();

private:
	static std::map<std::string, int> _map;
	static bool _flag;
	static int _battle;
};

