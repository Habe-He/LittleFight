/*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名： FontChina
** 日期：   2014:9:10
** 说明：	 读取Xml的中文字体
** 其它：	
** 历史：	2014:9:10 初始版本
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