#include "UserData.h"
#include "UserInfo_Name_Def.h"

USING_NS_CC;
static UserData *s_UserData = NULL;
#define userDefault UserDefault::getInstance()

UserData::UserData(void)
	: setupMusic(true)
	, setupEffect(true)
	, m_iRedRoleCount(0)
	, m_iBattleID(0)									/* ����ID */
	, m_iPointID(0)										/* �ؿ�ID */
	, m_iFightDifficulty(0)								/* �����Ѷ� */
	, m_iRoleCreModel(0)
	, m_strPointMap("res/Map/bingyuan.png")
	, m_iJxxg3Grade(-1)
	, m_iJxxg4Grade(0)
	, m_iCurPointStar(0)
	, m_iPvpPlayerID(0)
	, m_fBattleSVPercent(0.0f)
	, m_iLife(0)
{
}

UserData::~UserData(void)
{
	CC_SAFE_RELEASE( s_UserData );
	s_UserData = NULL;
}

/********************************************************************/
// ���ܣ�   	��ȡ�洢��ʵ��
// ���������	��
// ����ֵ�� 	UserData*
// �޸ļ�¼��	
/*********************************************************************/
 UserData *UserData::getInstance()
 {
 	if ( NULL == s_UserData )
 	{
 		s_UserData = new UserData;
		s_UserData->setUserData();
		s_UserData->init();
 	}
 	return s_UserData;
 }

 void UserData::init()
 {
	 m_rcBgRegion = Rect(0, 0, 0, 0);
 }

/********************************************************************/
// ���ܣ�   	��ʼ����Ϸ�洢����
// ���������	��
// ����ֵ�� 	void
// �޸ļ�¼��	
/*********************************************************************/
void UserData::setUserData()
{
	int index = 0;

	userDefault->setBoolForKey(SAVING_FILE, false);

	if ( !userDefault->getBoolForKey(SAVING_FILE, false) )
	{
		userDefault->setBoolForKey(SAVING_FILE, true);
	}
}

void UserData::saveDraw(int times)
{
	userDefault->setIntegerForKey(DiamondA, times);
	userDefault->flush();
}

int UserData::getDraw()
{
	return userDefault->getIntegerForKey(DiamondA);
}

void UserData::saveUserName(string _userName)
{
	userDefault->setStringForKey(AccountName, _userName);
}

string UserData::getUserName()
{
	return userDefault->getStringForKey(AccountName);
}

void UserData::saveUserPwd(string _userPwd)
{
	userDefault->setStringForKey(AccountPassword, _userPwd);
}

string UserData::getUserPwd()
{
	return userDefault->getStringForKey(AccountPassword);
}

void UserData::saveDiamondDraw(int times)
{
	userDefault->setIntegerForKey(DiamondB, times);
	userDefault->flush();
}

int UserData::getDiamondDraw()
{
	return userDefault->getIntegerForKey(DiamondB);
}

void UserData::saveMusicState()
{
	userDefault->setBoolForKey(MusicState, setupMusic);
}

bool UserData::getMusicState()
{
	return userDefault->getBoolForKey(MusicState);
}

void UserData::saveEffectState()
{
	userDefault->setBoolForKey(EffectState, setupEffect);
}

bool UserData::getEffectState()
{
	return userDefault->getBoolForKey(EffectState);
}

/*********************************************************************
 ** ���ܣ�		��������ָ������
 ** ���������	��
 ** ����ֵ�� 	int������ָ������
 ** �޸ļ�¼��	
 *********************************************************************/
void UserData::savaNewcomerGuide(int guide)
{
	userDefault->setIntegerForKey(NewcomerGuide, guide);
}

/*********************************************************************
 ** ���ܣ�		��ȡ����ָ������
 ** ���������	��
 ** ����ֵ�� 	int������ָ������
 ** �޸ļ�¼��	
 *********************************************************************/
int UserData::getNewcomerGuide()
{
	return userDefault->getIntegerForKey(NewcomerGuide);
}

void UserData::setGuideStep(int step)
{
	auto value = getGuideStep();									/* �����������裬��λ0��1��ʾ�����񣬵�λ��ʾID */
	value = (0 == step) ? 0 : value + step;
	userDefault->setIntegerForKey(GuideStep, value);
}

int  UserData::getGuideStep()
{
	return userDefault->getIntegerForKey(GuideStep);
}

/*********************************************************************
** ���ܣ�		��ӽ�ɫ
** ���������	��ɫ
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void UserData::addRole(Node *node)
{
	m_vctRoles.push_back(node);
}

/*********************************************************************
** ���ܣ�		�Ƴ���ɫ
** ���������	��ɫ
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void UserData::removeRole(Node * node)
{
	auto pos = find(m_vctRoles.begin(), m_vctRoles.end(), node);
	if ( pos != m_vctRoles.end() )
	{
		m_vctRoles.erase(pos);
	}
}

/*********************************************************************
** ���ܣ�		�Ƴ����н�ɫ
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void UserData::removeAllRoles()
{
	m_vctRoles.clear();
	m_iBlackRoleCount.clear();
	m_iRedRoleCount = 0;
}

/*********************************************************************
** ���ܣ�		��ȡ��ɫ��
** ���������	��ɫ��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
std::vector<Node *> UserData::getRoles()
{
	return m_vctRoles;
}

/* �����ҷ��佫���� */
void UserData::setRedRoleCount(int count)
{
	m_iRedRoleCount = count;
}

/* ���õз��佫���� */
void UserData::setBlackRoleCount(int room, int count)
{
	if (0 == count)											/* ����Ϊ0��Ĭ����� */
	{
		m_iBlackRoleCount.clear();
	}
	else
	{
		auto size = (int)m_iBlackRoleCount.size();
		while (room > size - 1)
		{
			m_iBlackRoleCount.push_back(0);
			size = (int)m_iBlackRoleCount.size();
		}
		m_iBlackRoleCount[room] = count;
	}
}

/* ��ȡ�ҷ��佫���� */
int	UserData::getRedRoleCount()
{
	return m_iRedRoleCount;
}

/* ��ȡ�з��佫���� */
int UserData::getBlackRoleCount(int room)
{
	return m_iBlackRoleCount[room];
}

/* ��ȡ�з��佫������ */
int UserData::getBlackRoleTotalCount()
{
	int iRet = 0;

	for (unsigned int index = 0;index < m_iBlackRoleCount.size();index++)
	{
		iRet += m_iBlackRoleCount[index];
	}

	return iRet;
}

/* �ҷ��佫��������/�� *//* true: �� false: �� */
void UserData::checkRedRolecount(bool flag)
{
	m_iRedRoleCount = (true == flag) ? m_iRedRoleCount + 1 : m_iRedRoleCount - 1;
}

/* �з��佫��������/�� *//* true: �� false: �� */
void UserData::checkBlackRolecount(int room, bool flag)
{
	auto size = (int)m_iBlackRoleCount.size();
	while (room > size - 1)
	{
		m_iBlackRoleCount.push_back(0);
		size = (int)m_iBlackRoleCount.size();
	}
	m_iBlackRoleCount[room] = (true == flag) ? m_iBlackRoleCount[room] + 1 : m_iBlackRoleCount[room] - 1;
}

/*********************************************************************
** ���ܣ�		���õ�ǰ����ͼ��С(����ɫ���ƶ�����)
** ���������	Rect rc:��ǰ����ͼ��С
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void UserData::setBgRegion(Rect rc)
{
	m_rcBgRegion = rc;
}

Rect UserData::getBgRegion()
{
	return m_rcBgRegion;
}

void UserData::setBattleID(int battle)
{
	m_iBattleID = battle;
}

int UserData::getBattleID()
{
	return m_iBattleID;
}

void UserData::setPointID(int point)
{
	m_iPointID = point;
}

int UserData::getPointID()
{
	return m_iPointID;
}

void UserData::setFightDifficulty(int diff)
{
	m_iFightDifficulty = diff;
}

int UserData::getFightDifficulty()
{
	return m_iFightDifficulty;
}

void UserData::setRoleCreateModel(int model)
{
	m_iRoleCreModel = model;
}

int UserData::getRoleCreateModel()
{
	return m_iRoleCreModel;
}

void UserData::setPointMap(std::string strMap)
{
	m_strPointMap = strMap;
}

std::string UserData::getPointMap()
{
	return m_strPointMap;
}

void UserData::setCurrentPointStar(int star)
{
	m_iCurPointStar = star;
}

int UserData::getCurrentPointStar()
{
	return m_iCurPointStar;
}

void UserData::setJxxg3Grade(int grade)
{
	m_iJxxg3Grade = grade;
}

int UserData::getJxxg3Grade()
{
	return m_iJxxg3Grade;
}

void UserData::setJxxg4Grade(int grade)
{
	if (0 == grade)
	{
		m_iJxxg4Grade = grade;
	}
	else
	{
		m_iJxxg4Grade += grade;
	}
}

int UserData::getJxxg4Grade()
{
	return m_iJxxg4Grade;
}

void UserData::setPvpPlayerID(int playerID)
{
	m_iPvpPlayerID = playerID;
}

int UserData::getPvpPlayerID()
{
	return m_iPvpPlayerID;
}

void UserData::setBattleSVPercent(float svPer)
{
	m_fBattleSVPercent = svPer;
}

float UserData::getBattleSVPercent()
{
	return m_fBattleSVPercent;
}

void UserData::setPointLive(int life)
{
	if (0 == life)
	{
		m_iLife = 0;
	}
	else
	{
		m_iLife ++;
	}
}

int UserData::getPointLive()
{
	return m_iLife;
}