/*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ����� FontChina
** ���ڣ�   2014:9:10
** ˵����	 ��ȡXml����������
** ������	
** ��ʷ��	2014:9:10 ��ʼ�汾
*********************************************************************/
#ifndef  __FONT_CHINA__
#define __FONT_CHINA__

#include <iostream>
#include <list>
#include "cocos2d.h"
USING_NS_CC;

class FontChina
{
public:
	FontChina();
	virtual ~FontChina();

	static FontChina* getInstance();

	static const char* G2U(const char* gb2312);

	void purgeFontChina();
	
	void initStringXml();
	
	const __String* getComString(std::string key);
private:
	static FontChina* mpInstance;

	__Dictionary* mpDicComXml;
};
#endif