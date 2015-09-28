 /*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ����� ChuZi
** ���ڣ�   2015:1:31
** ˵����	����
** ������	
** ��ʷ��2015:1:31 ��ʼ�汾
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "Roles/Role/Role.h"
#include "Roles/SkillProps/CommonProp.h"

enum ChuZiArrow
{
	ChuZi_Normal = 0,
	ChuZi_S2Prop,
	ChuZi_Max
};

class ChuZi : public Role
{
public:
	ChuZi(void);
	virtual ~ChuZi(void);

	CREATE_ROLE_FUNC(ChuZi);

protected:
	void loadArmature();											/* ���ض�����Դ */
	void initFlightPropInfo();										/* ��ʼ�����ܷ��е��� */

	void actionMovementCallFunc(cocostudio::Armature *, cocostudio::MovementEventType, const std::string&);
	void actionFrameEventCallFunc(cocostudio::Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);

	/* ����ִ�� Begin */
	bool runActionAttack();
	bool runActionTwiceAtk();
	bool runActionThriceAtk();
	bool runActionSkillOne();
	bool runActionSkillTwo();
	/* ����ִ�� End */

	void ChuZiShot(ChuZiArrow, bool);							/* ��� */
	void ChuziS1();
	void s1CallBack1(cocos2d::Node *);
	void s1CallBack2(cocos2d::Node *);

private:
	std::map<cocos2d::Sprite*, cocos2d::Point> m_mapS1;			/* ����s1������*/

	RoleFlightProp m_stChuZiShot[ChuZi_Max];
};

