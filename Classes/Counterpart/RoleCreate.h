 /*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ����� RoleCreate
** ���ڣ�   2015:1:31
** ˵����	��ɫ������
** ������	
** ��ʷ��2015:1:31 ��ʼ�汾
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "Roles/Role/Role.h"


class RoleCreate : public cocos2d::Ref
{
public:
	RoleCreate(void);
	virtual ~RoleCreate(void);

public:
	static Role* create(std::string, RoleCreMode, float = ResourceScale);

protected:
	static void loadRoleArmatureRes(std::string , int);
};

