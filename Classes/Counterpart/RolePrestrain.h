 /*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ����� RolePrestrain
** ���ڣ�   2015:4:17
** ˵����	��ɫԤ����
** ������	
** ��ʷ��2015:4:17 ��ʼ�汾
*********************************************************************/
#pragma once
#include "cocos2d.h"

class RolePrestrain : cocos2d::Ref
{
public:
	RolePrestrain(void);
	virtual ~RolePrestrain(void);

public:
	bool loading(int tag);									/* Ԥ���������ɫ */

protected:
	void prestrainRoleArmatureRes(std::string , int);		/* ��ȡ�����ɫ��Դ */

private:
	std::vector<std::string>			_vecPath;			/* Ҫ���ص���Դ */
};

