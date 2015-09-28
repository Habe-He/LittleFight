/*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ����� Role
** ���ڣ�   2014:9:18
** ˵����	��ɫ���࣬�����ɫ������Ϊ��
** ������	
** ��ʷ��	2014:9:18 ��ʼ�汾
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "Role_Def.h"
#include "UserInfo/UserData.h"
#include "Public/ToolFunc.h"

class Role : public cocos2d::Node
{
public:
	Role();
	virtual ~Role(void);
	
public:
	virtual bool init(std::string, RoleCreMode, float);				/* ��ʼ����ɫ���� */

public:
	bool runRoleAction(RoleActSign);								/* �����ӿ� */ 
	bool runLordlAction(RoleCmdSign,cocos2d::Point = ptInvalid);	/* ����ִ�м��ܶ��� */

	void initRoleInfo(RoleCamp, RoleMode, RoleRace);				/* ��ʼ����ɫ��Ϣ */
	virtual void initTalentEffect();								/* �����츳buff */
	void setRoleInfo(RoleInfo);										/* ���ý�ɫ��Ϣ */
	void setRoleBuff(RoleBuff);										/* ���ý�ɫbuff */
	void setRolePanel(RolePanel);									/* ��ɫ�������� */
	void setRoleSkillInfo(SkillInfo*);								/* ��ɫ�������� */
	void setRoleHpUp(int);											/* hp�ָ� */
	void setRoleCondition(RoleCondition, float);					/* �쳣״̬���� */
	void setRoleAbnormalDamage(int , float);						/* �쳣״̬�˺� */
	void setActionCD(RoleActSign, float = 0);						/* ���ý�ɫ����cd */
	void setRolePkID(int);											/* �佫����ID */
	int  getRolePkID();												/* �佫����ID */
	void setRoleID(int);											/* �佫ID */
	int  getRoleID();												/* �佫ID */
	RoleInfo getRoleInfo();											/* ��ɫ��Ϣ��ȡ */
	RoleBuff getRoleBuff();											/* ��ȡ��ɫbuff */
	SkillInfo* getRoleSkillInfo();									/* ��ȡ��ɫ�������� */
	void resetUISkillBtnCD();										/* ���ý��漼�ܰ�ť���õ�cd */
	void setAnimateSpeed(float);									/* ���ö������� */
	void backToLife();												/* ���� */
	void setHealthCtrl(cocos2d::Node *);							/* ���ý�ɫHP��MP��ʾ�ؼ� */
	void removeHealthCtrl();										/* �Ƴ���ɫHP��MP��ʾ�ؼ� */

	virtual int roleHurt(Role*, SkillInfo, bool);

protected:
	virtual void loadArmature();									/* ���ض�����Դ */
	void initHealthBar();											/* ��ʼ����ɫ������ʾ�� */
	void initSubInfo();												/* ���ý�ɫ������ */
	void initActAiLimit();											/* ����Ai��Ϊ�ĸ��� */
	void initSkillRegion();											/* ���ý�ɫ�������� */
	void initSkillGains();											/* ���ü��ܵȼ����������� */
	void initJxxgBuff();											/* ��ʼ�����ѧ��buff */
	virtual void setAiActionSequence();								/* ����Ai�������� */
	virtual void initActInherent();									/* ��ʼ����ɫ�������� */
	virtual void initFlightPropInfo();								/* ��ʼ�����ܷ��е��� */

	virtual void aiActSequenceSoldier();							/* ����Ai�������� */
	virtual void aiActSequenceCompanion();							/* С���Ai�������� */
	virtual void aiActSequenceBoss();								/* Boss Ai�������� */
	virtual void aiActSequenceMain();								/* ���� Ai�������� */
	
	std::string getFrameEventName(RoleFrameEvent);					/* ��ȡ�����¼����� */
	std::string getFlightPropPath();								/* ��ȡ���е�����Դ·�� */
	unsigned int playEffectOgg(const char* , bool = false,
		float = 1.0f, float = 0.0f, float = 1.0f);					/* ������Ч */
	bool isRoleLearnedTalent(RoleTalent);							/* ��ɫ�Ƿ�ϰ���츳 */
	void warMsgDecision();											/* ս����Ϣ���� */
	void passRoomByAuto();											/* �Զ���ͼ */
	void shaky();													/* ���� */
	void playAureoleEffect();										/* �ŵ׹⻷��Ч */
	void playHitEffect();											/* ������Ч */
	void hitEffectCB(cocos2d::Node*);
	void deathEffect();												/* ������Ч */
	void deathEffectCB(cocos2d::Node*);
	void addTrail(int );
	void removeTrail(cocos2d::Node*);

	virtual void roleCollisionDetective(bool);						/* ִ����ײ��� */

	bool runArmatureAction(RoleActSign);							/* ִ�ж��� */
	void stopArmatureAction();										/* ֹͣ���� */
	bool checkAnimateExistByName(const std::string);				/* �������Ƽ�⶯�����ڷ� */
	void setRoleTurnedDirInfo(RoleDirSign);							/* ���ý�ɫת������Ϣ */
	void setRoleTurnedDirInfo(float);								/* ���ý�ɫת������Ϣ */

	virtual void movement(const std::string&, cocostudio::MovementEventType, float);
	virtual void movement(const std::string&);						/* ����ʱ��Ϣ��Ӧ */
	virtual void frameEvent(const std::string&);					/* ����ʱ֡�¼� */

	virtual void onEnter();
	virtual void onExit();
	void update(float);
	virtual void updateRole();										/* ˢ�� */

	virtual void hpReture(float);									/* hp�ظ� */
	void actionCDFlag(float);										/* CD��ʱ */

	void roleSchedule(float , RoleScheduleType);					/* ��ʱ�� */
	void roleUnSchedule(RoleScheduleType);

	void comboResume(float);										/* ������Ǹ�λ */
	void conditionResume(float);									/* �쳣״̬�ָ� */
	void aiActionResume(float);										/* AI��Ϊ���� */
	void abnormalResume(float);										/* �쳣�˺����� */
	void buffShieldResume(float);									/* ������ʧ */
	void buffHpBack(float);											/* hp�ָ��츳 */
	void buffHarmGrow(float);										/* ����ü���츳 */
	void buffDenfendLResume(float);									/* ������buff��λ */
	void checkRoleInBgRegion();										/* ȷ����ɫ���ƶ������������� */
	void makeRoleMoving(float);										/* �ƶ���ɫ */
	void downResume(float);											/* ȡ������ */
	void flashEffect();												/* ��ɫ��˸��Ч */
	void flashEffectCallBack();										/* ���������״̬�ָ����� */
	virtual void deathEffectCallBack();								/* ������ص� */
	void smittenResume(float);										/* �ܻ��ָ� */
	void shakyCallBack(cocos2d::Node*);								/* �������� */

	/* ����ִ�� Begin */
	virtual	bool runActionAtkCtrl();
	virtual	bool runActionIdle();
	virtual	bool runActionMove();
	virtual bool runActionAttack();
	virtual bool runActionTwiceAtk();
	virtual bool runActionThriceAtk();
	virtual	bool runActionSmitten();
	virtual	bool runActionDown();
	virtual	bool runActionDeath();
	virtual bool runActionSkillOne();
	virtual bool runActionSkillTwo();
	virtual bool runActionSkillThree();
	virtual bool runActionSkillFour();
	/* ����ִ�� End */

	virtual float getExtraHarm(Role*);								/* �����˺��ӳ� */
	virtual void talentEffect(Role*, float);						/* �츳ЧӦ */
	void setRoleHitAction(int , bool);								/* ��ɫ����ʱ���� */
	void showRoleHealthChange(int);									/* hp�仯label */
	void hpLabelCallBack(cocos2d::Node *);							/* ��Ѫ��ʾlabel�ص����� */
	
	/* AI */
	virtual void runRoleAI();
	void runRoleMainAI();
	void roleAiStep();												/* Ai��Ϊѡ�� */
	void roleAiPursuit(cocos2d::Point);								/* Ai��Ϊ׷�� */
	void roleAiShortMove();											/* Ai��Ϊ�̾����ƶ� */
	void roleAiSleep();												/* Ai��Ϊ���� */

	/* AI�������� Begin */
	bool checkAIAviable();											/* �ж�AI��Ч�� */
	void calcuRoleDangerSignValue(bool *, float *);					/* �����ɫ�Ƿ���Σ�� */
	void setMoveVector(cocos2d::Point);								/* ��ȡ�ƶ����� */
	bool checkRoleCanBeHit(cocos2d::Point);							/* �ж�ָ����ɫ�Ƿ��ڹ�����Χ */
	Role* getNearestRole();											/* ��ȡ����Ľ�ɫ */
	cocos2d::Rect getRectByTwoPoint(cocos2d::Point, cocos2d::Point);/* ���������㹹����� */
	cocos2d::Rect getRectBySize(cocos2d::Size);						/* ������λ�úͷ�Χ������� */
	/* AI�������� End */

protected:
	int				m_iRolePkID;									/* �佫����ID */
	int				m_iRoleID;										/* �佫ID */
	float			m_fResScale;									/* ��Դ���ű��� */
	float			m_fActCD[RoleAct_Max];							/* cd��ʱ */
	bool			m_bRoleActBreak;								/* �����жϱ�� */
	RoleInfo		m_stRoleInfo;
	RoleBuff		m_stRoleBuff;									/* �츳buff */
	SkillInfo		m_stSkillInfo[RoleAct_Max];
	RoleSubInfo		m_stRoleSubInfo;
	RoleCreMode		m_eRoleCreMode;									/* ��ɫ����ģʽ */
	RoleActMode		m_stActMode[RoleAct_Max];						/* ��ɫ�������� */
	RoleActAiSign	m_eRoleActAi;									/* ��ɫAi��Ϊ */
	cocos2d::Node	*m_nAureoleEffect;								/* ��ɫ�⻷��Ч */
	std::vector<RoleActSign>		m_vctAiActSeq;					/* Ai�������� */

	float			m_fActAiLimit[RoleActAi_Max];					/* ��ɫAi������ѡ����� */

	CC_SYNTHESIZE(std::string, m_strRoleName, StrRoleName);			/* ��ɫ���� */
	CC_SYNTHESIZE(RoleWarMsg, m_eRoleWarMsg, RoleWarMsg);			/* ��ͨ����ǣ�����ȫ�壩 */
	CC_SYNTHESIZE(int, m_iSceneID, SceneID);						/* ��ɫ����ID */
	CC_SYNTHESIZE(int, m_iRoleStarLv, StarLv);						/* �佫 �Ǽ� */
	CC_SYNTHESIZE(cocos2d::Rect, m_rcRegion, MoveRegion);			/* �ƶ����� */
	CC_SYNTHESIZE(bool, m_bShadow, ShadowFlag);						/* ������ */
	CC_SYNTHESIZE(int, m_iShadowOwner, ShadowOwner);				/* ������(��PKID���) */

private:
	cocos2d::Point		m_ptMoveDir;								/* �ƶ����� */
	cocos2d::Point		m_ptMoveDes;								/* �����ƶ�Ŀ�ĵ� */
	cocos2d::Node		*m_nHealth;									/* ��ɫHP��MP��ʾ�ؼ� */

	cocos2d::ProgressTimer	*_roleHealth;							/* ��ɫ����ֵ */

	RoleHealthSign		m_ehealthSign;								/* hp�仯���� */

	unsigned int		m_iAiActSeqIndex;							/* ��ǰִ��Ai�������е����� */
	int					m_iRoleCombo;								/* �չ���������״̬ */
};