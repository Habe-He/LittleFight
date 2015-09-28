 /*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ����� FlightProp
** ���ڣ�   2015:1:24
** ˵����	���е���(����ħ�����)
** ������	
** ��ʷ��2015:1:24 ��ʼ�汾
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "Roles/Role/Role.h"
#include "UserInfo/UserData.h"

const int	iActionSeqTag = 1000;			/* ���ƶ�����Tag */
/* ����������ÿ����ʱ��Ч�������ء��쳣״̬�ȣ������˾��� */
typedef struct tagFlightPropInfo
{
	int				num;					/* ��Դͼ���� */
	float			dur;					/* ��Դͼ����ʱ���� */
	float			reserve;				/* Ԥ�� */
	SkillInfo		skillInfo;				/* ���߼������� */
} FlightPropInfo;

typedef struct _tagRoleRes
{
	std::string strPath;					/* ������Դ·�� */
	cocos2d::Point	ptOffset;				/* ���߳�ʼƫ������ */
	int		iImgNum;						/* ������Դ���� */
} RoleFlightProp;

class FlightProp : public cocos2d::Sprite
{
public:
	FlightProp();
	virtual ~FlightProp(void);
	
	virtual void runPropCollisionDetective(float, cocos2d::Point);	/* �����ƶ���������ײ��� */
	virtual void setPropFlag(bool = true, float = 0.05f);			/* ���ñ�־Ϊ���� */
	void setPropPosition(Point);									/* �������� */
	void releaseCallBack();											/* ���� */
	void releaseWithDelay(float);

protected:
	void InitParam(Role *, FlightPropInfo, std::string);			/* ��ʼ����Ա���� */
	virtual void PropCollisionDetective(float);						/* ��ײ��� */

	std::string	getImgSuffix();										/* ��ȡ��Դͼ���ƺ�׺ */
	void imgAnimation();											/* ͼƬ���� */

	Role			*_owner;										/* �����ͷ��� */
	
protected:
	FlightPropInfo	m_stPropInfo;									/* ������Ϣ */
	cocos2d::Rect	m_rcBgRegion;									/* ��ǰ����ͼ��С(����ɫ���ƶ�����) */

	bool			m_bDown;										/* �������Է�ʱ�Ƿ񵹵� */
	float			m_fStay;										/* ��������Ŀ���ﵽ��̺���ʱ��ʧʱ�� */
	float			m_fHeight;										/* �߶� */

	std::string		m_strImg;										/* ͼƬ��Դ·�� */
};