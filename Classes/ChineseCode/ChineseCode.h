#pragma once
#include <iostream>
//#include <string>
#include <list>
#include "cocos2d.h"
USING_NS_CC;
using namespace std;

class ChineseCode
{
public:
	ChineseCode(void);
	~ChineseCode(void);

	void UTF_8ToGB2312(string &pOut, char *pText, int pLen);			// utf_8转为gb2312 ****************
	void GB2312ToUTF_8(string& pOut,char *pText, int pLen);				// gb2312 转utf_8
	string UrlGB2312(const char * str);								// url gb2312编码  ***************
	string UrlUTF8(char * str);										// url utf8 编码
	string UrlUTF8Decode(string str);								// url utf8解码
	string UrlGB2312Decode(string str);								// url gb2312解码

private:
	void Gb2312ToUnicode(wchar_t* pOut, char *gbBuffer);
	void UTF_8ToUnicode(wchar_t* pOut, char *pText);
	void UnicodeToUTF_8(char* pOut, wchar_t* pText);
	void UnicodeToGB2312(char* pOut, wchar_t uData);
	char  CharToInt(char ch);
	char StrToBin(char *str);
};