#include "Counterpart.h"
#include "UserInfo/UserData.h"
#include "Public/VisibleRect.h"
#include "GameResult.h"
#include "DataManager/DataManager.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;

Counterpart::Counterpart(void)
	: m_iSceneID(0)
	, m_iEnemyTotal(0)
	, m_eSituation(RoleWarMsg_None)
	, m_labelTime(NULL)
	, m_labelDone(NULL)
	, maxSceneNum(DefSceneNum)
	, m_bTimeFlag(true)
	, _spGo(NULL)
	, _ptMove(ptInvalid)
{
}

Counterpart::~Counterpart(void)
{
}

Scene *Counterpart::scene()
{
	auto se = Scene::create();
	auto layer = Counterpart::create();
	se->addChild(layer);
	return se;
}

bool Counterpart::init()
{
	if (false == Layer::init())
	{
		return false;
	}

	resetGameTime();
	auto pointInfo = DataManager::getInstance()->localCheckPointVector();/* ���йؿ������н�ɫ */
	ToolFunc::playBackgroundFile(pointInfo[UserData::getInstance()->getPointID()].cSong, true);
	UserData::getInstance()->setPointLive(0);

	loadMainFightScene();
	
	return true;
}

void Counterpart::onEnter()
{
	Layer::onEnter();

	this->scheduleUpdate();
	addTouchEventListener();
}

void Counterpart::onExit()
{
	this->unscheduleUpdate();

	auto roles = UserData::getInstance()->getRoles();
	for (unsigned int index = 0;index < roles.size();index ++)
	{
		roles[index]->removeFromParentAndCleanup(true);
	}
	UserData::getInstance()->removeAllRoles();

	_eventDispatcher->removeEventListener(m_listener);

	ToolFunc::playBackgroundFile();

	Layer::onExit();
}

/*********************************************************************
** ���ܣ�		���ؿ��Ʋ�
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void Counterpart::loadMainFightScene()
{
	m_hMainFight = MainFight::create();								/* ���Ʋ� */
	this->addChild(m_hMainFight, order_MainFight, order_MainFight);
	m_hLayerRole = RoleLayer::create();								/* ��ɫ�� */
	this->addChild(m_hLayerRole, order_Role);
	m_hGamePause = GamePause::create();
	this->addChild(m_hGamePause, order_Pause);						/* ��Ϸ��ͣ */
	m_hMainFight->setButtonEventListener(this, toucheventselector(Counterpart::btnPauseClicked));

	m_hLayerRole->loadRedRole();
	m_hLayerRole->loadBlackRole();
	m_hLayerRole->loadBackground();

	m_hMainFight->setRoleHealthCtrl();
	m_hMainFight->setRoleActButton();
	m_hLayerRole->initRolesTalent();								/* �����츳������������������ɺ���� */

	auto vct = UserData::getInstance()->getRoles();
	m_MainRole = (Role *)vct[0];
	m_iEnemyTotal = UserData::getInstance()->getBlackRoleTotalCount();	
	this->schedule(schedule_selector(Counterpart::gameTimer), 1.0f);

	m_rcMoveRegion = Rect(iRegionLimit, 75, SceneWidth - 2 * iRegionLimit, 130);
	UserData::getInstance()->setBgRegion(m_rcMoveRegion);

	_spGo = Sprite::create("res/MainFight/Go.png");
	_spGo->setAnchorPoint(Point::ANCHOR_MIDDLE);
	_spGo->setPosition(Point(657, 324));
	_spGo->setVisible(false);
	m_hMainFight->addChild(_spGo);
	
	gameTimer(0.0f);
	showPointGains();
}

void Counterpart::update(float dt)
{
	judgeWarSituation();											/* �ж��Ƿ��ͨ����ǰ���� */
	//checkRoleInBgRegion();
}

/*********************************************************************
** ���ܣ�		�����ƶ�ʱ������ͼ�ƶ��ж�
** ���������	Role *role: �ҷ���һ��Ϊ�������佫
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void Counterpart::setSceneScroll(Role *role)
{
	auto ptActual = Point::ZERO;
	auto winSize = VisibleRect::getVisibleRect().size;

	ptActual.x = MAX(role->getPositionX(), winSize.width / 2);
	ptActual.y = MAX(role->getPositionY(), winSize.height / 2);
	ptActual.x = MIN(ptActual.x, m_rcMoveRegion.getMaxX() + iRegionLimit - winSize.width / 2);
	ptActual.y = MIN(ptActual.y, m_rcMoveRegion.getMaxX() + iRegionLimit - winSize.height / 2);

	auto ptCenter = VisibleRect::center();
	auto ptView = ptCenter - ptActual;
	m_hLayerRole->setPositionX(ptView.x);

	if (role->getPositionX() > (m_iSceneID + 1) * SceneWidth + iRegionLimit)/* ������һͼ */
	{
		m_iSceneID ++;
		m_eSituation = RoleWarMsg_None;

		m_bTimeFlag = true;
		this->unschedule(schedule_selector(Counterpart::warGuidepost));
		_spGo->setVisible(false);

 		auto move = MoveTo::create(1.5f, Point(-SceneWidth * m_iSceneID, 0));
 		m_hLayerRole->runAction(move);								/* ������Ļ */

		m_rcMoveRegion.size.width = SceneWidth - 2 * iRegionLimit;
		m_rcMoveRegion.origin.x = SceneWidth * m_iSceneID + iRegionLimit;
		UserData::getInstance()->setBgRegion(m_rcMoveRegion);
	}
}

/*********************************************************************
** ���ܣ�		�ж�ս��
** ���������	
** ����ֵ��		
** �޸ļ�¼��	
*********************************************************************/
void Counterpart::judgeWarSituation()
{
	if ((RoleWarMsg_Over == m_eSituation) || (RoleWarMsg_Pause == m_eSituation))
	{
		return;
	}

	if (0 == UserData::getInstance()->getRedRoleCount())			/* �ҷ�ȫ���� */
	{
		gameLose();
	}
	if (0 == UserData::getInstance()->getBlackRoleTotalCount())		/* ʤ�� */
	{
		gameWin();
	}

	gameDoneRate();

	auto role = m_MainRole;
	auto vct = UserData::getInstance()->getRoles();
	for (unsigned int index = 0;index < vct.size();index++)			/* ȡ�ҷ���һ��δ�������佫 */
	{
		role = (Role * )vct[index];
		auto info = role->getRoleInfo();
		if (RoleStatus_Death != info.status)
		{
			break;
		}
	}

	if (0 == UserData::getInstance()->getBlackRoleCount(m_iSceneID))/* ��ǰ�������ȫ���� */
	{
		if (m_iSceneID < maxSceneNum - 1)
		{
			auto center = SceneWidth * (m_iSceneID + 0.5f);
			auto pt = m_hLayerRole->getPosition();
			if (pt.x + role->getPositionX() > center)				/* �佫����Ļ�����Ҳ� */
			{
				m_hLayerRole->setPosition(pt.x - 3.0f, 0);
			}
			else
			{
				if (RoleWarMsg_Pass != m_eSituation)
				{
					m_rcMoveRegion.size.width = 2 * SceneWidth;
					m_rcMoveRegion.origin.x = SceneWidth * m_iSceneID;
					UserData::getInstance()->setBgRegion(m_rcMoveRegion);

					this->schedule(schedule_selector(Counterpart::warGuidepost), 0.5f);

					m_bTimeFlag = false;
					m_eSituation = RoleWarMsg_Pass;
				}
					setSceneScroll(role);							/* ��������������� */
			}
		}
	}
}

/*********************************************************************
** ���ܣ�		ȷ����ɫ���ƶ�������������
** ���������	��
** ����ֵ�� 	��
** �޸ļ�¼��	
*********************************************************************/
void Counterpart::checkRoleInBgRegion()
{
	auto roles = UserData::getInstance()->getRoles();

	for (int index = 0;index < (int)roles.size();index ++)
	{
		auto role = (Role *)roles[index];
		if ((m_iSceneID != role->getSceneID()) || (RoleStatus_Death == role->getRoleInfo().status))
		{
			continue;
		}

		auto pt = m_hMainFight->convertToNodeSpace(role->getPosition());

		role->setLocalZOrder(m_rcMoveRegion.getMaxY() - pt.y + order_Role);
		if (pt.y > m_rcMoveRegion.getMaxY())
		{
			role->setPositionY(m_rcMoveRegion.getMaxY());
		}
		if (pt.y < m_rcMoveRegion.getMinY())
		{
			role->setPositionY(m_rcMoveRegion.getMinY());
		}
		if (pt.x > m_rcMoveRegion.getMaxX())
		{
			role->setPositionX(m_rcMoveRegion.getMaxX());
		}
		if (pt.x < m_rcMoveRegion.getMinX())
		{
			role->setPositionX(m_rcMoveRegion.getMinX());
		}
	}
}

/*********************************************************************
** ���ܣ�		���ý�ɫս�ֱ��
** ���������	RoleWarMsg war: ս��
**				RoleCamp camp: ��Ӫ����
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void Counterpart::setRoleWarMsg(RoleWarMsg war, RoleCamp camp)
{
	auto roles = UserData::getInstance()->getRoles();
	for (unsigned int index = 0;index < roles.size();index ++)
	{
		auto role = (Role *)roles[index];
		auto info = role->getRoleInfo();

		if (RoleStatus_Death == info.status)						/* ������ */
		{
			continue;
		}

		if ((RoleCamp_Normal == camp) || 							/* ������ */
			((RoleCamp_Normal != camp) && (camp == info.camp)))
		{
			role->setRoleWarMsg(war);
		}
	}

	m_eSituation = war;
}

/*********************************************************************
** ���ܣ�		��ͼʱ��ͷָ��
** ���������	float dt
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void Counterpart::warGuidepost(float dt)
{
	auto visible = _spGo->isVisible();
	_spGo->setVisible(!visible);
}

/* ��ʾ�ؿ����� */
void Counterpart::showPointGains()
{
	DataManager::getInstance()->pointGainsParse();
	auto gains = DataManager::getInstance()->localPointGainsVector();
	auto pointID = UserData::getInstance()->getPointID()%1000;
	auto diff = UserData::getInstance()->getFightDifficulty();

	auto coinLabel = Label::createWithSystemFont("", "Arial", 24);	/* ��ʾ��� */
	coinLabel->setPosition(Point(730, 386));
	coinLabel->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
	m_hMainFight->addChild(coinLabel, 1);

	auto strCoin = __String::createWithFormat("%d", gains[pointID].coin[diff]);
	coinLabel->setString(strCoin->getCString());
	coinLabel->setColor(Color3B(0xEB, 0xDB, 0x8F));
}
void Counterpart::btnPauseClicked(Ref* ref, TouchEventType type)
{
	Button *btn = (Button *)ref;
	int tag = btn->getTag();

	if (TOUCH_EVENT_ENDED == type)
	{
		switch (tag)
		{
		case MFCtrl_Pause:
			m_hGamePause->setEnabled(true);
			break;
		}
	}
}

void Counterpart::addTouchEventListener()
{
	m_listener = EventListenerTouchOneByOne::create();				/* ����һ���¼������� OneByOne Ϊ���㴥�� */
	m_listener->setSwallowTouches(false);							/* �����Ƿ���û�¼����� onTouchBegan �������� true ʱ��û*/

	m_listener->onTouchBegan = CC_CALLBACK_2(Counterpart::onTouchBegan, this);
	m_listener->onTouchMoved = CC_CALLBACK_2(Counterpart::onTouchMoved, this);
	m_listener->onTouchEnded = CC_CALLBACK_2(Counterpart::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(m_listener, this);
}

bool Counterpart::onTouchBegan(Touch *touch, Event *unused_event)
{
	if (0 == UserData::getInstance()->getBlackRoleCount(m_iSceneID))
	{
		return true;
	}
	
	_ptMove = m_hLayerRole->convertToNodeSpace(touch->getLocation());
	if (RoleStatus_Death != m_MainRole->getRoleInfo().status)
	{
		auto ptDir = _ptMove - getPosition();
		if ((abs(ptDir.x) > 5.0f) && (abs(ptDir.y) > 5.0f))			/* ��Χ */
		{
			m_MainRole->runLordlAction(RoleCmdSign_Move, _ptMove);
		}
	}
	return true;
}

void Counterpart::onTouchMoved(Touch *touch, Event *unused_event)
{
	if (0 == UserData::getInstance()->getBlackRoleCount(m_iSceneID))
	{
		return;
	}

	_ptMove = m_hLayerRole->convertToNodeSpace(touch->getLocation());
	if (RoleStatus_Death != m_MainRole->getRoleInfo().status)
	{
		auto ptDir = _ptMove - getPosition();
		if ((abs(ptDir.x) > 5.0f) && (abs(ptDir.y) > 5.0f))			/* ��Χ */
		{
			m_MainRole->runLordlAction(RoleCmdSign_Move, _ptMove);
		}
	}
}

void Counterpart::onTouchEnded(Touch *touch, Event *unused_event)
{
	if (0 == UserData::getInstance()->getBlackRoleCount(m_iSceneID))
	{
		return;
	}

	if (RoleStatus_Death != m_MainRole->getRoleInfo().status)
	{
		m_MainRole->runLordlAction(RoleCmdSign_Release);
	}
}

/*********************************************************************
** ���ܣ�		���ùؿ�ͨ��ʱ��
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void Counterpart::resetGameTime()
{
	m_iGameTime = 180;												/* ��Ϸ����ʱ�� */
	auto mode = UserData::getInstance()->getRoleCreateModel();		/* ���ѧ��ֻ��һ������ */

	if (mode > RoleCreMode_Fighting)
	{
		maxSceneNum = 1;
	}

	if (mode == RoleCreMode_XueGong4)
	{
		m_iGameTime = 45;
	}
}

/*********************************************************************
** ���ܣ�		ʤ��
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void Counterpart::gameWin()
{
	m_labelTime->setVisible(false);
	m_eSituation = RoleWarMsg_Over;

	this->unschedule(schedule_selector(Counterpart::gameTimer));
	auto result = GameResult::create(Result_Win, 180 - m_iGameTime);
	this->addChild(result, order_Result);
}

/*********************************************************************
** ���ܣ�		ʧ��
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void Counterpart::gameLose()
{
	m_labelTime->setVisible(false);
	m_eSituation = RoleWarMsg_Over;

	this->unschedule(schedule_selector(Counterpart::gameTimer));
	auto result = GameResult::create(Result_Loss, 180 - m_iGameTime);
	this->addChild(result, order_Result);
}

/*********************************************************************
** ���ܣ�		����ָ���Ϸ
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void Counterpart::gameResume()
{
	resetGameTime();
	m_labelTime->setVisible(true);
	this->schedule(schedule_selector(Counterpart::gameTimer), 1.0f);
	m_eSituation = RoleWarMsg_None;

	UserData::getInstance()->setPointLive();
	auto roles = UserData::getInstance()->getRoles();
	for (unsigned int index = 0;index < roles.size();index ++)
	{
		auto role = (Role *)roles[index];
		if (RoleCamp_Red == role->getRoleInfo().camp)
		{
			role->backToLife();
			role->removeHealthCtrl();
		}
		role->setRoleWarMsg(RoleWarMsg_None);
	}

	m_hMainFight->setRoleHealthCtrl();
}

/*********************************************************************
** ���ܣ�		��Ϸ��ʱ��
** ���������	float dt:
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void Counterpart::gameTimer(float dt)
{
	if (false == m_bTimeFlag)
	{
		return;
	}

	if (0 == m_iGameTime)
	{
		gameLose();
	}

	if (NULL == m_labelTime)
	{
		m_labelTime = Label::createWithSystemFont("", "Arial", 35);
		m_labelTime->setPosition(Point(600, 440));
		m_labelTime->setAnchorPoint(Point::ANCHOR_MIDDLE);
		this->addChild(m_labelTime, order_MainFight);
	}

	auto strTime = __String::createWithFormat("%d:%02d", m_iGameTime/60, m_iGameTime%60);
	m_labelTime->setString(strTime->getCString());
	m_labelTime->setColor(Color3B(0xFF, 0xF7, 0xD3));
	m_iGameTime --;
}

/*********************************************************************
** ���ܣ�		�ؿ���ɶ�
** ���������	��
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void Counterpart::gameDoneRate()
{
	if (NULL == m_labelDone)
	{
		m_labelDone = Label::createWithSystemFont("", "Arial", 18);
		m_labelDone->setPosition(Point(672, 443));
		m_labelDone->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
		this->addChild(m_labelDone, order_MainFight);
	}

	auto count = UserData::getInstance()->getBlackRoleTotalCount();
	auto rate = (int)(count * 100.0f / m_iEnemyTotal);
	auto strDone = __String::createWithFormat("%d%%", rate);
	m_labelDone->setString(strDone->getCString());
	m_labelDone->setColor(Color3B::RED);
}