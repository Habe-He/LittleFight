 /*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ����� RoleLayer
** ���ڣ�   2015:3:24
** ˵����	������ɫ��
** ������	
** ��ʷ��2015:3:24 ��ʼ�汾
*********************************************************************/
#pragma once
#include "cocos2d.h"

const float fDoubleClickDuration = 0.5f;	/* ˫����ʱ */

class RoleLayer : public cocos2d::Layer
{
public:
	RoleLayer(void);
	virtual ~RoleLayer(void);

	CREATE_FUNC(RoleLayer);
	virtual bool init();

public:
	void loadRedRole();
	void loadBlackRole();
	void loadBackground();
	void initRolesTalent();
	cocos2d::Sprite *getPointMap();									/* ��ȡ����ͼ */

protected:
	void loadNormalBlackRole();										/* ������ͨ�ؿ���ɫ */
	void loadJiXiaBlackRole();										/* �������ѧ����ɫ */
	void loadPvpBlackRole();										/* �������ѧ����ɫ */
	
private:
	cocos2d::Sprite *m_spBg;										/* ������Դ */
};

