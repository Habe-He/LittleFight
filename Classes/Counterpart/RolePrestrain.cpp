#include "RolePrestrain.h"
#include "RoleResInfo.h"
#include "Loading/Loading.h"
#include "Counterpart.h"


RolePrestrain::RolePrestrain(void)
{
}

RolePrestrain::~RolePrestrain(void)
{
}

/*********************************************************************
** ���ܣ�		Ԥ���������ɫ
** ���������	int tag: ����id
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
bool RolePrestrain::loading(int tag)
{
	auto roles = RoleResInfo::roleInBattle(tag);
	for (unsigned index = 0;index < roles.size();index ++)			/* �޳��ظ��� */
	{
		auto temp = roles;
		auto str = roles[index];

		for (unsigned int i = 0;i < temp.size();i++)
		{
			auto str2 = temp[i];
			if ((i != index) && (str.compare(str2) == 0))
			{
				roles.erase(roles.begin() + index);
				break;
			}
		}
	}

	auto sz = roles.size();
	unsigned int index = 0;
	for (index = 0;index < sz;index ++)
	{
		auto name = roles[index];
		prestrainRoleArmatureRes(name, RoleResInfo::getRoleResNum(name));
	}

	auto scene = Loading::scene();
	Loading* pGameLoading = static_cast<Loading*>(scene->getChildByTag(2));
	for (index = 0;index < _vecPath.size();index ++)
	{
		pGameLoading->addTextureCacheFromFileByName(_vecPath[index].c_str());			
	}
	pGameLoading->addTextureCacheFromFileByName("res/Sprite");

	CCDirector::getInstance()->replaceScene(scene);
	pGameLoading->setChangeScene(Counterpart::scene);
	_vecPath.clear();

	return true;
}

/*********************************************************************
** ���ܣ�		��ȡ�����ɫ��Դ
** ���������	std::string str: ��ɫ����
**				int num: ��Դ����
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void RolePrestrain::prestrainRoleArmatureRes(std::string str, int num)
{
	for (auto index = 0;index < num;index ++)
	{
		auto strPath = __String::createWithFormat("Roles/%s/%s%d", str.c_str(), str.c_str(), index);
		_vecPath.push_back(strPath->getCString());
	}
}