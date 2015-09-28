#include "RoleLayer.h"
#include "UserInfo/UserData.h"
#include "RoleCreate.h"
#include "RoleResInfo.h"
#include "DataManager/DataManager.h"
#include "Counterpart_Def.h"

USING_NS_CC;
using namespace ui;


RoleLayer::RoleLayer(void)
{
}

RoleLayer::~RoleLayer(void)
{
}

bool RoleLayer::init()
{
	bool bRet = false;

	if (true == (bRet = Layer::init()))
	{
		//m_bDoubleClickFlag = false;
	}

	return bRet;
}

/*********************************************************************
** 功能：		添加我方主将
** 输入参数：	无
** 返回值：		无
** 修改记录：	
*********************************************************************/
void RoleLayer::loadRedRole()
{
	auto warriors = DataManager::getInstance()->interPointSetsVector();
	if (0 == warriors.size())
	{
		DataManager::getInstance()->isGetPointSets();
		warriors = DataManager::getInstance()->interPointSetsVector();
	}
	auto general = DataManager::getInstance()->localGeneralProptyVector();
	UserData::getInstance()->setRedRoleCount(0);
	auto rc = Rect(iRegionLimit, 75, SceneWidth - 2 * iRegionLimit, 130);

	for (unsigned int index = 0; index < warriors.size(); index++)
	{
		auto warrior = warriors[index];
		if (0 == warrior.generalID)
		{
			continue;
		}

		auto msg = general[warrior.generalID - 10001];					/* 该武将基础信息 */
		msg.level = warrior.generalLevel;
		auto role = RoleCreate::create(msg.chinaSmallName, RoleCreMode_Fighting);
		this->addChild(role, order_Role);
		UserData::getInstance()->addRole(role);
		UserData::getInstance()->checkRedRolecount(true);
		role->setMoveRegion(rc);

		RolePanel panel = {0};
		panel.hpTotal = panel.hpCurrent = msg.initHP + msg.level * msg.hpGrowing;
		panel.atk = msg.initAtk + msg.level * msg.atkGrowing;
		panel.pDefend = msg.initPD + msg.level * msg.pdGrowing;
		panel.mDefend = msg.initMD + msg.level * msg.mdGrowing;
		panel.level = msg.level;
		role->setRolePanel(panel);

		auto model = (0 == index) ? RoleMode_Main : RoleMode_Companion;
		role->initRoleInfo(RoleCamp_Red, model, (RoleRace)msg.jobType);
		role->setStarLv(msg.maxStar);
		DataManager::getInstance()->isGetGeneralProperty(warrior.generalPKID);
		role->setRolePkID(warrior.generalPKID);
		role->setRoleID(warrior.generalID);
		role->setPosition(Point(50 + rand()%50, 75 + rand()%130));
	}
}

/*********************************************************************
** 功能：		添加敌方角色
** 输入参数：	无
** 返回值：		无
** 修改记录：	
*********************************************************************/
void RoleLayer::loadBlackRole()
{
	auto model = UserData::getInstance()->getRoleCreateModel();
	if (model <= RoleCreMode_Fighting)
	{
		loadNormalBlackRole();
	}
	else
	{
		loadJiXiaBlackRole();
	}
}

/*********************************************************************
** 功能：		加载背景
** 输入参数：	无
** 返回值：		无
** 修改记录：	
*********************************************************************/
void RoleLayer::loadBackground()
{
	auto strMap = UserData::getInstance()->getPointMap();
	m_spBg = Sprite::create(strMap);
	m_spBg->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	m_spBg->setPosition(Point::ZERO);
	m_spBg->setScaleY(1.042f);
	this->addChild(m_spBg, order_Bkg, order_Bkg);					/* tag用于震动特效 */
	UserData::getInstance()->setBgRegion(m_spBg->getBoundingBox());
}

/*********************************************************************
** 功能：		加载背景
** 输入参数：	无
** 返回值：		无
** 修改记录：	
*********************************************************************/
void RoleLayer::initRolesTalent()
{
	auto vec = UserData::getInstance()->getRoles();
	for (unsigned int index = 0;index < vec.size();index ++)
	{
		auto role = (Role *)vec[index];
		auto info = role->getRoleInfo();
		if (RoleCamp_Red == info.camp)
		{
			role->initTalentEffect();
		}
	}
}

/* 获取背景图 */
Sprite *RoleLayer::getPointMap()
{
	return m_spBg;
}
// protected

void RoleLayer::loadNormalBlackRole()
{
	auto pointInfo = DataManager::getInstance()->localCheckPointVector();/* 所有关卡的所有角色 */
	auto pointRole = pointInfo[UserData::getInstance()->getPointID()];
	auto general = DataManager::getInstance()->localGeneralProptyVector();/* 所有武将数据 */
	UserData::getInstance()->setBlackRoleCount(0);
	auto rc = Rect(iRegionLimit, 75, SceneWidth - 2 * iRegionLimit, 130);

	for (int index = 0;index < pointRole.cRoleNum;index++)
	{
		GeneralProptyStruct msg = general[pointRole.cRoles[index].pID - 10001];
		msg.level = pointRole.cRoles[index].level;

		auto scale = (1 == pointRole.cRoles[index].flag) ? 0.8f : ResourceScale;
		Role *role = RoleCreate::create(msg.chinaSmallName, RoleCreMode_Fighting, scale);
		this->addChild(role, order_Role);
		UserData::getInstance()->addRole(role);
		UserData::getInstance()->checkBlackRolecount(pointRole.cRoles[index].room - 1, true);
		auto rc2 = rc;
		rc2.origin.x += (pointRole.cRoles[index].room - 1) * SceneWidth;
		role->setMoveRegion(rc2);

		RolePanel panel = {0};
		panel.hpTotal = panel.hpCurrent = msg.initHP + msg.level * msg.hpGrowing;
		panel.atk = msg.initAtk + msg.level * msg.atkGrowing;	// 攻击力
		panel.pDefend = msg.initPD + msg.level * msg.pdGrowing;	// 物理防御
		panel.mDefend = msg.initMD + msg.level * msg.mdGrowing;	// 法术防御
		panel.level = msg.level;
		role->setRolePanel(panel);

		auto model = (0 == pointRole.cRoles[index].flag) ? RoleMode_Soldier : RoleMode_Boss;
		role->initRoleInfo(RoleCamp_Black, model, (RoleRace)msg.jobType);
		role->setStarLv(msg.maxStar);
		role->setRoleID(pointRole.cRoles[index].pID);
		role->setSceneID(pointRole.cRoles[index].room - 1);
		role->setPosition(Point(650 + (pointRole.cRoles[index].room - 1) * SceneWidth + rand()%100, 75 + rand()%130));
	}
}

void RoleLayer::loadJiXiaBlackRole()
{
	auto pointInfo = DataManager::getInstance()->localCheckPointVector();	/* 所有关卡的所有角色 */
	auto model = UserData::getInstance()->getRoleCreateModel();
	auto pointRole = pointInfo[model - RoleCreMode_XueGong1];
	auto general = DataManager::getInstance()->localGeneralProptyVector();	/* 所有武将数据 */
	DataManager::getInstance()->isGetTeamInfo();							/* 当前战队等级 */
	auto teamInfo = DataManager::getInstance()->interTeamInfoVector();
	UserData::getInstance()->setBlackRoleCount(0);
	auto rc = Rect(iRegionLimit, 75, SceneWidth - 2 * iRegionLimit, 130);

	for (int index = 0;index < pointRole.cRoleNum;index++)
	{
		GeneralProptyStruct msg = general[pointRole.cRoles[index].pID - 10001];
		msg.level = teamInfo[0].teamLevel;

		Role *role = RoleCreate::create(msg.chinaSmallName, (RoleCreMode)model, 0.75f);
		this->addChild(role, order_Role);
		UserData::getInstance()->addRole(role);
		UserData::getInstance()->checkBlackRolecount(0, true);
		role->setMoveRegion(rc);

		RolePanel panel = {0};
		panel.hpTotal = panel.hpCurrent = msg.initHP + msg.level * msg.hpGrowing;
		panel.atk = msg.initAtk + msg.level * msg.atkGrowing;	// 攻击力
		panel.pDefend = msg.initPD + msg.level * msg.pdGrowing;	// 物理防御
		panel.mDefend = msg.initMD + msg.level * msg.mdGrowing;	// 法术防御
		panel.level = msg.level;
		role->setRolePanel(panel);

		role->initRoleInfo(RoleCamp_Black, RoleMode_Boss, (RoleRace)msg.jobType);
		role->setStarLv(msg.maxStar);
		role->setRoleID(pointRole.cRoles[index].pID);
		role->setSceneID(pointRole.cRoles[index].room - 1);
		role->setPosition(Point(650 + (pointRole.cRoles[index].room - 1) * SceneWidth + rand()%100, 75 + rand()%130));
	}
}

void RoleLayer::loadPvpBlackRole()
{
	auto pvpRoles = DataManager::getInstance()->interPvpPlayerTeamVector(UserData::getInstance()->getPvpPlayerID());
	auto general = DataManager::getInstance()->localGeneralProptyVector();	/* 所有武将数据 */
	UserData::getInstance()->setBlackRoleCount(0);

	for (unsigned int index = 0;index < pvpRoles.size();index++)
	{
		if ((0 == pvpRoles[index].pvpID) || (0 == pvpRoles[index].pvpPKID))
		{
			continue;
		}

		DataManager::getInstance()->isGetGeneralProperty(pvpRoles[index].pvpPKID);
		auto pvpRole = DataManager::getInstance()->interGeneralVector();

		GeneralProptyStruct msg = general[pvpRoles[index].pvpID - 10001];
		msg.level = pvpRole[0].level;

		Role *role = RoleCreate::create(msg.chinaSmallName, RoleCreMode_Fighting, 0.75f);
		this->addChild(role, order_Role);
		UserData::getInstance()->addRole(role);
		UserData::getInstance()->checkBlackRolecount(0, true);

		RolePanel panel = {0};
		panel.hpTotal = panel.hpCurrent = msg.initHP + msg.level * msg.hpGrowing;
		panel.atk = msg.initAtk + msg.level * msg.atkGrowing;	// 攻击力
		panel.pDefend = msg.initPD + msg.level * msg.pdGrowing;	// 物理防御
		panel.mDefend = msg.initMD + msg.level * msg.mdGrowing;	// 法术防御
		panel.level = msg.level;
		role->setRolePanel(panel);

		role->initRoleInfo(RoleCamp_Black, RoleMode_Boss, (RoleRace)msg.jobType);
		role->setStarLv(msg.maxStar);
		role->setRolePkID(pvpRoles[index].pvpPKID);
		role->setRoleID(pvpRoles[index].pvpID);
		role->setSceneID(0);
		role->setPosition(Point(650 + rand()%100, 75 + rand()%130));
	}
}