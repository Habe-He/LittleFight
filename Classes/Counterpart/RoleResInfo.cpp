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
		_map.insert(std::make_pair("SunBin", 3));			/* 孙膑 */
		_map.insert(std::make_pair("TianJi", 2));			/* 田忌 */
		_map.insert(std::make_pair("ZhongWuYan", 2));		/* 钟无艳 */
		_map.insert(std::make_pair("LianPo", 3));			/* 廉颇 */
		_map.insert(std::make_pair("LiMu", 2));				/* 李牧 */
		_map.insert(std::make_pair("WuMengYao", 2));		/* 吴孟瑶 */
		_map.insert(std::make_pair("WuQi", 1));				/* 吴起 */
		_map.insert(std::make_pair("XiangYan", 3));			/* 项燕 */
		_map.insert(std::make_pair("QuYuan", 1));			/* 屈原 */
		_map.insert(std::make_pair("CiKe", 1));				/* 刺客 */
		_map.insert(std::make_pair("BianQue", 3));			/* 扁鹊 */
		_map.insert(std::make_pair("SunWu", 2));			/* 孙武 */
		_map.insert(std::make_pair("ShangYang", 2));		/* 商鞅 */
		_map.insert(std::make_pair("BaiQi", 2));			/* 白起 */
		_map.insert(std::make_pair("TianDan", 2));			/* 田单 */
		_map.insert(std::make_pair("ZouJi", 2));			/* 邹忌 */
		_map.insert(std::make_pair("KuangZhang", 2));		/* 匡章 */
		_map.insert(std::make_pair("ZhaoShe", 4));			/* 赵奢 */
		_map.insert(std::make_pair("ZhaoKuo", 1));			/* 赵括 */
		_map.insert(std::make_pair("PangNuan", 2));			/* 庞暖 */
		_map.insert(std::make_pair("JingYang", 3));			/* 景阳 */
		_map.insert(std::make_pair("SunShuAo", 2));			/* 孙叔敖 */
		_map.insert(std::make_pair("FanBing", 1));			/* 扇子兵 */
		_map.insert(std::make_pair("PangJuan", 2));			/* 庞涓 */
		_map.insert(std::make_pair("JianKe", 1));			/* 剑客 */
		_map.insert(std::make_pair("LeYi", 3));				/* 乐毅 */
		_map.insert(std::make_pair("ChuZi", 1));			/* 触子 */
		_map.insert(std::make_pair("ChunYuKun", 1));		/* 淳于髡 */
		_map.insert(std::make_pair("QiMaoBian", 1));		/* 齐貌辨 */
		_map.insert(std::make_pair("JianDun", 1));			/* 剑盾兵 */
		_map.insert(std::make_pair("QuGai", 2));			/* 屈匄 */
		_map.insert(std::make_pair("DaoBing", 1));			/* 刀兵 */
		_map.insert(std::make_pair("YuQing", 1));			/* 虞卿 */
		_map.insert(std::make_pair("ZhuangJi", 1));			/* 庄姬 */
		_map.insert(std::make_pair("LouHuan", 4));			/* 楼缓 */
		_map.insert(std::make_pair("GongSunYan", 1));		/* 公孙衍 */
		_map.insert(std::make_pair("BaoYuan", 2));			/* 暴鸳 */
		_map.insert(std::make_pair("QinKai", 2));			/* 秦开 */

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
** 功能：		获取上阵角色
** 输入参数：	int tag: 副本id
** 返回值：		std::vector<GeneralPropertyData> 上阵角色
** 修改记录：	
*********************************************************************/
std::vector<std::string> RoleResInfo::roleInBattle(int tag)
{
	_battle = tag;
	return getRoleInBattle();
}

std::vector<std::string> RoleResInfo::getRoleInBattle()
{
	std::vector<std::string> _msg;

	auto warriors = DataManager::getInstance()->interPointSetsVector();/* 获取上阵武将ID */
	if (0 == warriors.size())
	{
		DataManager::getInstance()->isGetPointSets();
		warriors = DataManager::getInstance()->interPointSetsVector();
	}

	auto general = DataManager::getInstance()->localGeneralProptyVector();/* 所有武将数据 */
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
		auto pointInfo = DataManager::getInstance()->localCheckPointVector();/* 所有关卡的所有角色 */
			
		for (int index = 0;index < pointInfo[_battle].cRoleNum;index++)	/* 获得敌人信息 */
		{
			_msg.push_back(general[pointInfo[_battle].cRoles[index].pID - 10001].chinaSmallName);
		}

		UserData::getInstance()->setPointMap(pointInfo[_battle].cMap);	/* 设置关卡地图 */
	}
	else
	{
		/* 读取稷下学宫角色 */
		DataManager::getInstance()->jxxgDataParser();
		auto pointInfo = DataManager::getInstance()->localCheckPointVector();/* 所有关卡的所有角色 */

		for (int index = 0;index < pointInfo[_battle].cRoleNum;index++)	/* 获得敌人信息 */
		{
			_msg.push_back(general[pointInfo[_battle].cRoles[index].pID - 10001].chinaSmallName);
		}

		//UserData::getInstance()->setPointMap(pointInfo[_battle].cMap);/* 设置关卡地图 */
	}

	return _msg;
}