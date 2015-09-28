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

	if ("SunBin" == strName)				/* 孙膑 */
	{
		role = (Role *)SunBin::create(strName, mode, resScale);
	}
	else if ("TianJi" == strName)			/* 田忌 */
	{
		role = (Role *)Tianji::create(strName, mode, resScale);
	}
	else if ("ZhongWuYan" == strName)		/* 钟无艳 */
	{
		role = (Role *)ZhongWuYan::create(strName, mode, resScale);
	}
	else if ("LianPo" == strName)			/* 廉颇 */
	{
		role = (Role *)LianPo::create(strName, mode, resScale);
	}
	else if ("LiMu" == strName)				/* 李牧 */
	{
		role = (Role *)LiMu::create(strName, mode, resScale);
	}
	else if ("WuMengYao" == strName)		/* 吴孟瑶 */
	{
		role = (Role *)WuMengYao::create(strName, mode, resScale);
	}
	else if ("WuQi" == strName)				/* 吴起 */
	{
		role = (Role *)WuQi::create(strName, mode, resScale);
	}
	else if ("XiangYan" == strName)			/* 项燕 */
	{
		role = (Role *)XiangYan::create(strName, mode, resScale);
	}
	else if ("QuYuan" == strName)			/* 屈原 */
	{
		role = (Role *)QuYuan::create(strName, mode, resScale);
	}
	else if ("CiKe" == strName)				/* 刺客 */
	{
		role = (Role *)JingKe::create(strName, mode, resScale);
	}
	else if ("BianQue" == strName)			/* 扁鹊 */
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
	else if ("SunWu" == strName)			/* 孙武 */
	{
		role = (Role *)SunWu::create(strName, mode, resScale);
	}
	else if ("ShangYang" == strName)		/* 商鞅 */
	{
		role = (Role *)ShangYang::create(strName, mode, resScale);
	}
	else if ("BaiQi" == strName)			/* 白起 */
	{
		role = (Role *)BaiQi::create(strName, mode, resScale);
	}
	else if ("TianDan" == strName)			/* 田单 */
	{
		role = (Role *)TianDan::create(strName, mode, resScale);
	}
	else if ("ZouJi" == strName)			/* 邹忌 */
	{
		role = (Role *)ZouJi::create(strName, mode, resScale);
	}
	else if ("KuangZhang" == strName)		/* 匡章 */
	{
		role = (Role *)KuangZhang::create(strName, mode, resScale);
	}
	else if ("ZhaoShe" == strName)			/* 赵奢 */
	{
		role = (Role *)ZhaoShe::create(strName, mode, resScale);
	}
	else if ("ZhaoKuo" == strName)			/* 赵括 */
	{
		role = (Role *)ZhaoKuo::create(strName, mode, resScale);
	}
	else if ("PangNuan" == strName)			/* 庞暖 */
	{
		role = (Role *)PangNuan::create(strName, mode, resScale);
	}
	else if ("JingYang" == strName)			/* 景阳 */
	{
		role = (Role *)JingYang::create(strName, mode, resScale);
	}
	else if ("SunShuAo" == strName)			/* 孙叔敖 */
	{
		role = (Role *)SunShuAo::create(strName, mode, resScale);
	}
	else if ("FanBing" == strName)			/* 扇子兵 */
	{
		role = (Role *)JiangYi::create(strName, mode, resScale);
	}
	else if ("PangJuan" == strName)			/* 庞涓 */
	{
		role = (Role *)PangJuan::create(strName, mode, resScale);
	}
	else if ("JianKe" == strName)			/* 剑客 */
	{
		role = (Role *)TaiZiShen::create(strName, mode, resScale);
	}
	else if ("LeYi" == strName)				/* 乐毅 */
	{
		role = (Role *)LeYi::create(strName, mode, resScale);
	}
	else if ("ChuZi" == strName)			/* 触子 */
	{
		role = (Role *)ChuZi::create(strName, mode, resScale);
	}
	else if ("ChunYuKun" == strName)		/* 淳于髡 */
	{
		role = (Role *)ChunYuKun::create(strName, mode, resScale);
	}
	else if ("QiMaoBian" == strName)		/* 齐貌辨 */
	{
		role = (Role *)QiMaoBian::create(strName, mode, resScale);
	}
	else if ("JianDun" == strName)			/* 剑盾兵 */
	{
		role = (Role *)JingShe::create(strName, mode, resScale);
	}
	else if ("QuGai" == strName)			/* 屈匄 */
	{
		role = (Role *)QuGai::create(strName, mode, resScale);
	}
	else if ("DaoBing" == strName)			/* 刀兵 */
	{
		role = (Role *)ChenZhen::create(strName, mode, resScale);
	}
	else if ("YuQing" == strName)			/* 虞卿 */
	{
		role = (Role *)YuQing::create(strName, mode, resScale);
	}
	else if ("ZhuangJi" == strName)			/* 庄姬 */
	{
		role = (Role *)ZhuangJi::create(strName, mode, resScale);
	}
	else if ("LouHuan" == strName)			/* 楼缓 */
	{
		role = (Role *)LouHuan::create(strName, mode, resScale);
	}
	else if ("GongSunYan" == strName)		/* 公孙衍 */
	{
		role = (Role *)GongSunYan::create(strName, mode, resScale);
	}
	else if ("BaoYuan" == strName)			/* 暴鸢 */
	{
		role = (Role *)BaoYuan::create(strName, mode, resScale);
	}
	else /**/	
	{
		if ("QinKai" == strName)			/* 秦开 */
		{
			role = (Role *)QinKai::create(strName, mode, resScale);
		}		
	}

	return role;
}

/*********************************************************************
** 功能：		角色资源加载
** 输入参数：	std::string str: 角色名
**				int num: 资源文件数量
** 返回值：		无
** 修改记录：	
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
	if (false == fs->isFileExist(jsonPath))					/* 文件(角色)不存在 */
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