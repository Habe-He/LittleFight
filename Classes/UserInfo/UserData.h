/********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ����� UserData
** ���ߣ�   WangZho
** ���ڣ�   2014:7:28
** ˵����	��Ϸ���������ڴ��д��
** ������	
** ��ʷ��	2014:7:28 ��ʼ�汾
**			2014:8:7  ȡ��m_szSaveFile����Ϊ�궨��
/********************************************************************/
#pragma once
#include "cocos2d.h"
using namespace std;

class UserData : cocos2d::Ref
{
public:
	UserData(void);
	virtual ~UserData(void);

	static UserData *getInstance();
	void init();

	// ���ý��汳�����ֺ���Ч����
	bool setupMusic;
	bool setupEffect;
	
public:
	void savaNewcomerGuide(int );							/* ��������ָ������ */
	int getNewcomerGuide();									/* ��ȡ����ָ������ */

	void setGuideStep(int step = 1);						/* ���������������� */
	int  getGuideStep();									/* ��ȡ������������ */	

	void saveMusicState();									// �������ֿ���
	bool getMusicState();									// ��ȡ���ֿ���

	void saveEffectState();									// ������Ч����
	bool getEffectState();									// ��ȡ��Ч����

	void saveDraw(int times);								/* �Ƿ���ʯ��һ�γ鿨 */
	int getDraw();											/* ��ȡ */

	void saveUserName(string _userName);					// �����������
	string getUserName();									// ��ȡ�������

	void saveUserPwd(string _userPwd);						// �����������
	string getUserPwd();									// ��ȡ�������
		
	void saveDiamondDraw(int times);						/* �Ƿ���ʯʮ�����һ�γ鿨 */
	int getDiamondDraw();									/* ��ȡ */

	void addRole(cocos2d::Node *);							/* ��ӽ�ɫ */
	void removeRole(cocos2d::Node *);						/* �Ƴ���ɫ */
	void removeAllRoles();									/* �Ƴ����н�ɫ */
	std::vector<cocos2d::Node *> getRoles();				/* ��ȡ��ɫ�� */
	void setRedRoleCount(int);								/* �����ҷ��佫���� */
	void setBlackRoleCount(int, int = 0);					/* ���õз��佫���� */
	int	 getRedRoleCount();									/* ��ȡ�ҷ��佫���� */
	int  getBlackRoleCount(int);							/* ��ȡ�з��佫���� */
	int	 getBlackRoleTotalCount();							/* ��ȡ�з��佫������ */
	void checkRedRolecount(bool = false);					/* �ҷ��佫��������/�� */
	void checkBlackRolecount(int , bool = false);			/* �з��佫��������/�� */

	void setBgRegion(cocos2d::Rect);						/* ���õ�ǰ����ͼ��С(����ɫ���ƶ�����) */
	cocos2d::Rect getBgRegion();							/* ��ȡ��ǰ����ͼ��С(����ɫ���ƶ�����) */

	void setBattleID(int);									/* ���ø���ID */
	int  getBattleID();										/* ��ȡ����ID */

	void setPointID(int);									/* ���ùؿ�ID */
	int  getPointID();										/* ��ȡ�ؿ�ID */

	void setFightDifficulty(int);							/* ���ø����Ѷ� */
	int  getFightDifficulty();								/* ��ȡ�����Ѷ� */

	void setRoleCreateModel(int);							/* ���ý�ɫ����ģʽ */
	int  getRoleCreateModel();								/* ��ȡ��ɫ����ģʽ */

	void setPointMap(std::string);							/* ���ùؿ���ͼ */
	std::string getPointMap();								/* ��ȡ�ؿ���ͼ */

	void setCurrentPointStar(int);							/* ���õ�ǰ�ؿ���õ��Ǽ� */
	int  getCurrentPointStar();								/* ��ȡ��ǰ�ؿ���õ��Ǽ� */

	void setJxxg3Grade(int);								/* �������ѧ��ģʽ3�ĳɼ� */
	int  getJxxg3Grade();									/* ��ȡ���ѧ��ģʽ3�ĳɼ� */

	void setJxxg4Grade(int);								/* �������ѧ��ģʽ4�ĳɼ� */
	int  getJxxg4Grade();									/* ��ȡ���ѧ��ģʽ4�ĳɼ� */

	void setPvpPlayerID(int);								/* ���þ�����ѡ�ж���ID */
	int  getPvpPlayerID();									/* ��ȡ������ѡ�ж���ID */

	void setBattleSVPercent(float);							/* ���ø������������ */
	float getBattleSVPercent();								/* ��ȡ������������� */

	void setPointLive(int life = 1);						/* ���ùؿ�������� */
	int  getPointLive();									/* ��ȡ�ؿ�������� */

	int numOfWeaponLocation;
protected:
	void setUserData();										/* ��ʼ����Ϸ�洢���� */

private:
	cocos2d::Rect			m_rcBgRegion;					/* ��ǰ����ͼ��С(����ɫ���ƶ�����) */

	std::vector<cocos2d::Node *>	m_vctRoles;				/* ��ɫ�� */
	std::string				m_strPointMap;					/* �ؿ���ͼ */

	int	 m_iRedRoleCount;									/* �ҷ��佫���� */
	std::vector<int>  m_iBlackRoleCount;					/* �з��佫���� */
	int  m_iBattleID;										/* ����ID */
	int  m_iPointID;										/* �ؿ�ID */
	int  m_iFightDifficulty;								/* �����Ѷ� */
	int	 m_iRoleCreModel;									/* ��ɫ����ģʽ */
	int	 m_iCurPointStar;									/* ��ǰ�ؿ���õ��Ǽ� */
	int	 m_iJxxg3Grade;										/* ���ѧ��ģʽ3�ĳɼ� */
	int	 m_iJxxg4Grade;										/* ���ѧ��ģʽ4�ĳɼ� */
	int	 m_iPvpPlayerID;									/* ������ѡ�ж���ID */
	float  m_fBattleSVPercent;								/* ������������� */
	int	 m_iLife;											/* �ؿ�������� */
};