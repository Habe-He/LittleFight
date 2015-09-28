#include "RoleCreate.h"
#include "Roles/Hero/TianJi.h"
#include "Roles/Hero/XiangYan.h"
#include "Roles/Hero/LianPo.h"
#include "Roles/Hero/BaiQi.h"
#include "Roles/Hero/BaoYuan.h"
#include "Roles/Hero/BianQue.h"
#include "Roles/NPC/BianQueNPC.h"
#include "Roles/Hero/ChenZhen.h"
#include "Roles/Hero/ChuZi.h"
#include "Roles/Hero/GongSunYan.h"
#include "Roles/Hero/ChunYuKun.h"
#include "Roles/Hero/JiangYi.h"
#include "Roles/Hero/JingYang.h"
#include "Roles/Hero/KuangZhang.h"
#include "Roles/Hero/JingKe.h"
#include "Roles/Hero/JingShe.h"
#include "Roles/Hero/LiMu.h"
#include "Roles/Hero/LouHuan.h"
#include "Roles/Hero/LeYi.h"
#include "Roles/Hero/PangJuan.h"
#include "Roles/Hero/QinKai.h"
#include "Roles/Hero/QuGai.h"
#include "Roles/Hero/QuYuan.h"
#include "Roles/Hero/SunShuAo.h"
#include "Roles/Hero/SunWu.h"
#include "Roles/Hero/TaiZiShen.h"
#include "Roles/Hero/ZouJi.h"
#include "Roles/Hero/WuQi.h"
#include "Roles/Hero/ZhaoShe.h"
#include "Roles/Hero/ShangYang.h"
#include "Roles/Hero/PangNuan.h"
#include "Roles/Hero/QiMaoBian.h"
#include "Roles/Hero/YuQing.h"
#include "Roles/Hero/ZhuangJi.h"
#include "Roles/Hero/SunShuAo.h"
#include "Roles/Hero/ZhaoKuo.h"
#include "Roles/Hero/TianDan.h"
#include "Roles/Hero/SunWu.h"
#include "Roles/Hero/SunBin.h"
#include "Roles/Hero/WuMengYao.h"
#include "Roles/Hero/ZhongWuYan.h"
#include "RoleResInfo.h"

using namespace cocostudio;


RoleCreate::RoleCreate(void)
{
}

RoleCreate::~RoleCreate(void)
{
}

Role* RoleCreate::create(std::string strName, RoleCreMode mode, float resScale)
{
	Role *role = NULL;

	loadRoleArmatureRes(strName, RoleResInfo::getRoleResNum(strName));

	if ("SunBin" == strName)				/* ���� */
	{
		role = (Role *)SunBin::create(strName, mode, resScale);
	}
	else if ("TianJi" == strName)			/* ��� */
	{
		role = (Role *)Tianji::create(strName, mode, resScale);
	}
	else if ("ZhongWuYan" == strName)		/* ������ */
	{
		role = (Role *)ZhongWuYan::create(strName, mode, resScale);
	}
	else if ("LianPo" == strName)			/* ���� */
	{
		role = (Role *)LianPo::create(strName, mode, resScale);
	}
	else if ("LiMu" == strName)				/* ���� */
	{
		role = (Role *)LiMu::create(strName, mode, resScale);
	}
	else if ("WuMengYao" == strName)		/* ������ */
	{
		role = (Role *)WuMengYao::create(strName, mode, resScale);
	}
	else if ("WuQi" == strName)				/* ���� */
	{
		role = (Role *)WuQi::create(strName, mode, resScale);
	}
	else if ("XiangYan" == strName)			/* ���� */
	{
		role = (Role *)XiangYan::create(strName, mode, resScale);
	}
	else if ("QuYuan" == strName)			/* ��ԭ */
	{
		role = (Role *)QuYuan::create(strName, mode, resScale);
	}
	else if ("CiKe" == strName)				/* �̿� */
	{
		role = (Role *)JingKe::create(strName, mode, resScale);
	}
	else if ("BianQue" == strName)			/* ��ȵ */
	{
		if (RoleCreMode_XueGong3 == UserData::getInstance()->getRoleCreateModel())
		{
			role = (Role *)BianQueNpc::create(strName, mode, resScale);
		}
		else
		{
			role = (Role *)BianQue::create(strName, mode, resScale);
		}
	}
	else if ("SunWu" == strName)			/* ���� */
	{
		role = (Role *)SunWu::create(strName, mode, resScale);
	}
	else if ("ShangYang" == strName)		/* ���� */
	{
		role = (Role *)ShangYang::create(strName, mode, resScale);
	}
	else if ("BaiQi" == strName)			/* ���� */
	{
		role = (Role *)BaiQi::create(strName, mode, resScale);
	}
	else if ("TianDan" == strName)			/* �ﵥ */
	{
		role = (Role *)TianDan::create(strName, mode, resScale);
	}
	else if ("ZouJi" == strName)			/* �޼� */
	{
		role = (Role *)ZouJi::create(strName, mode, resScale);
	}
	else if ("KuangZhang" == strName)		/* ���� */
	{
		role = (Role *)KuangZhang::create(strName, mode, resScale);
	}
	else if ("ZhaoShe" == strName)			/* ���� */
	{
		role = (Role *)ZhaoShe::create(strName, mode, resScale);
	}
	else if ("ZhaoKuo" == strName)			/* ���� */
	{
		role = (Role *)ZhaoKuo::create(strName, mode, resScale);
	}
	else if ("PangNuan" == strName)			/* ��ů */
	{
		role = (Role *)PangNuan::create(strName, mode, resScale);
	}
	else if ("JingYang" == strName)			/* ���� */
	{
		role = (Role *)JingYang::create(strName, mode, resScale);
	}
	else if ("SunShuAo" == strName)			/* ���尽 */
	{
		role = (Role *)SunShuAo::create(strName, mode, resScale);
	}
	else if ("FanBing" == strName)			/* ���ӱ� */
	{
		role = (Role *)JiangYi::create(strName, mode, resScale);
	}
	else if ("PangJuan" == strName)			/* ��� */
	{
		role = (Role *)PangJuan::create(strName, mode, resScale);
	}
	else if ("JianKe" == strName)			/* ���� */
	{
		role = (Role *)TaiZiShen::create(strName, mode, resScale);
	}
	else if ("LeYi" == strName)				/* ���� */
	{
		role = (Role *)LeYi::create(strName, mode, resScale);
	}
	else if ("ChuZi" == strName)			/* ���� */
	{
		role = (Role *)ChuZi::create(strName, mode, resScale);
	}
	else if ("ChunYuKun" == strName)		/* ������ */
	{
		role = (Role *)ChunYuKun::create(strName, mode, resScale);
	}
	else if ("QiMaoBian" == strName)		/* ��ò�� */
	{
		role = (Role *)QiMaoBian::create(strName, mode, resScale);
	}
	else if ("JianDun" == strName)			/* ���ܱ� */
	{
		role = (Role *)JingShe::create(strName, mode, resScale);
	}
	else if ("QuGai" == strName)			/* ���� */
	{
		role = (Role *)QuGai::create(strName, mode, resScale);
	}
	else if ("DaoBing" == strName)			/* ���� */
	{
		role = (Role *)ChenZhen::create(strName, mode, resScale);
	}
	else if ("YuQing" == strName)			/* ���� */
	{
		role = (Role *)YuQing::create(strName, mode, resScale);
	}
	else if ("ZhuangJi" == strName)			/* ׯ�� */
	{
		role = (Role *)ZhuangJi::create(strName, mode, resScale);
	}
	else if ("LouHuan" == strName)			/* ¥�� */
	{
		role = (Role *)LouHuan::create(strName, mode, resScale);
	}
	else if ("GongSunYan" == strName)		/* ������ */
	{
		role = (Role *)GongSunYan::create(strName, mode, resScale);
	}
	else if ("BaoYuan" == strName)			/* ��� */
	{
		role = (Role *)BaoYuan::create(strName, mode, resScale);
	}
	else /**/	
	{
		if ("QinKai" == strName)			/* �ؿ� */
		{
			role = (Role *)QinKai::create(strName, mode, resScale);
		}		
	}

	return role;
}

/*********************************************************************
** ���ܣ�		��ɫ��Դ����
** ���������	std::string str: ��ɫ��
**				int num: ��Դ�ļ�����
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void RoleCreate::loadRoleArmatureRes(std::string str, int num)
{
	std::stringstream stream;
	std::string	strPath;

	stream.str("");
	stream << "Roles/" << str << "/" << str;
	strPath = stream.str();
	std::string jsonPath = strPath + ".ExportJson";

	auto fs = FileUtils::getInstance();
	if (false == fs->isFileExist(jsonPath))					/* �ļ�(��ɫ)������ */
	{
		return;
	}	

	for (auto index = 0;index < num;index ++)
	{
		stream.str("");
		stream << strPath << index;

		ArmatureDataManager::getInstance()->addArmatureFileInfo(stream.str() + ".png", stream.str() + ".plist", jsonPath);
	}
}