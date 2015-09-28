#include "RoleResInfo.h"
#include "DataManager/DataManager.h"
#include "Roles/Role/Role_Def.h"

bool RoleResInfo::_flag = false;
int RoleResInfo::_battle = 0;
std::map<std::string, int> RoleResInfo::_map;

RoleResInfo::RoleResInfo(void)
{
}

RoleResInfo::~RoleResInfo(void)
{
}

void RoleResInfo::init()
{
	if (false == _flag)
	{
		_map.insert(std::make_pair("SunBin", 3));			/* ���� */
		_map.insert(std::make_pair("TianJi", 2));			/* ��� */
		_map.insert(std::make_pair("ZhongWuYan", 2));		/* ������ */
		_map.insert(std::make_pair("LianPo", 3));			/* ���� */
		_map.insert(std::make_pair("LiMu", 2));				/* ���� */
		_map.insert(std::make_pair("WuMengYao", 2));		/* ������ */
		_map.insert(std::make_pair("WuQi", 1));				/* ���� */
		_map.insert(std::make_pair("XiangYan", 3));			/* ���� */
		_map.insert(std::make_pair("QuYuan", 1));			/* ��ԭ */
		_map.insert(std::make_pair("CiKe", 1));				/* �̿� */
		_map.insert(std::make_pair("BianQue", 3));			/* ��ȵ */
		_map.insert(std::make_pair("SunWu", 2));			/* ���� */
		_map.insert(std::make_pair("ShangYang", 2));		/* ���� */
		_map.insert(std::make_pair("BaiQi", 2));			/* ���� */
		_map.insert(std::make_pair("TianDan", 2));			/* �ﵥ */
		_map.insert(std::make_pair("ZouJi", 2));			/* �޼� */
		_map.insert(std::make_pair("KuangZhang", 2));		/* ���� */
		_map.insert(std::make_pair("ZhaoShe", 4));			/* ���� */
		_map.insert(std::make_pair("ZhaoKuo", 1));			/* ���� */
		_map.insert(std::make_pair("PangNuan", 2));			/* ��ů */
		_map.insert(std::make_pair("JingYang", 3));			/* ���� */
		_map.insert(std::make_pair("SunShuAo", 2));			/* ���尽 */
		_map.insert(std::make_pair("FanBing", 1));			/* ���ӱ� */
		_map.insert(std::make_pair("PangJuan", 2));			/* ��� */
		_map.insert(std::make_pair("JianKe", 1));			/* ���� */
		_map.insert(std::make_pair("LeYi", 3));				/* ���� */
		_map.insert(std::make_pair("ChuZi", 1));			/* ���� */
		_map.insert(std::make_pair("ChunYuKun", 1));		/* ������ */
		_map.insert(std::make_pair("QiMaoBian", 1));		/* ��ò�� */
		_map.insert(std::make_pair("JianDun", 1));			/* ���ܱ� */
		_map.insert(std::make_pair("QuGai", 2));			/* ���� */
		_map.insert(std::make_pair("DaoBing", 1));			/* ���� */
		_map.insert(std::make_pair("YuQing", 1));			/* ���� */
		_map.insert(std::make_pair("ZhuangJi", 1));			/* ׯ�� */
		_map.insert(std::make_pair("LouHuan", 4));			/* ¥�� */
		_map.insert(std::make_pair("GongSunYan", 1));		/* ������ */
		_map.insert(std::make_pair("BaoYuan", 2));			/* ��ԧ */
		_map.insert(std::make_pair("QinKai", 2));			/* �ؿ� */

		_flag = true;
	}
}

int RoleResInfo::getRoleResNum(std::string str)
{
	if (false == _flag)
	{
		init();
	}
	return _map[str];
}

/*********************************************************************
** ���ܣ�		��ȡ�����ɫ
** ���������	int tag: ����id
** ����ֵ��		std::vector<GeneralPropertyData> �����ɫ
** �޸ļ�¼��	
*********************************************************************/
std::vector<std::string> RoleResInfo::roleInBattle(int tag)
{
	_battle = tag;
	return getRoleInBattle();
}

std::vector<std::string> RoleResInfo::getRoleInBattle()
{
	std::vector<std::string> _msg;

	auto warriors = DataManager::getInstance()->interPointSetsVector();/* ��ȡ�����佫ID */
	if (0 == warriors.size())
	{
		DataManager::getInstance()->isGetPointSets();
		warriors = DataManager::getInstance()->interPointSetsVector();
	}

	auto general = DataManager::getInstance()->localGeneralProptyVector();/* �����佫���� */
	if (general.size() == 0)
	{
		DataManager::getInstance()->generalDataParser();
		general = DataManager::getInstance()->localGeneralProptyVector();
	}

	for (unsigned int index = 0; index < warriors.size(); index++)
	{
		auto warrior = warriors[index];
		if (0 != warrior.generalID)
		{
			_msg.push_back(general[warrior.generalID - 10001].chinaSmallName);
		}
	}

	auto model = UserData::getInstance()->getRoleCreateModel();
	if (model <= RoleCreMode_Fighting)
	{
		DataManager::getInstance()->checkPointDataParser(UserData::getInstance()->getFightDifficulty());
		auto pointInfo = DataManager::getInstance()->localCheckPointVector();/* ���йؿ������н�ɫ */
			
		for (int index = 0;index < pointInfo[_battle].cRoleNum;index++)	/* ��õ�����Ϣ */
		{
			_msg.push_back(general[pointInfo[_battle].cRoles[index].pID - 10001].chinaSmallName);
		}

		UserData::getInstance()->setPointMap(pointInfo[_battle].cMap);	/* ���ùؿ���ͼ */
	}
	else
	{
		/* ��ȡ���ѧ����ɫ */
		DataManager::getInstance()->jxxgDataParser();
		auto pointInfo = DataManager::getInstance()->localCheckPointVector();/* ���йؿ������н�ɫ */

		for (int index = 0;index < pointInfo[_battle].cRoleNum;index++)	/* ��õ�����Ϣ */
		{
			_msg.push_back(general[pointInfo[_battle].cRoles[index].pID - 10001].chinaSmallName);
		}

		//UserData::getInstance()->setPointMap(pointInfo[_battle].cMap);/* ���ùؿ���ͼ */
	}

	return _msg;
}