#include "FontChina.h"
#include "extensions/cocos-ext.h"
#include "tinyxml2/tinyxml2.h"
using namespace tinyxml2;

FontChina* FontChina::mpInstance = NULL;

FontChina::FontChina()
{

}

FontChina::~FontChina()
{

}

const char* FontChina::G2U(const char* gb2312)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	int len = MultiByteToWideChar(0, 0, gb2312, -1, NULL, 0);    
	wchar_t* wstr = new wchar_t[len+1];    
	memset(wstr, 0, len+1);    
	MultiByteToWideChar(0, 0, gb2312, -1, wstr, len);    
	len = WideCharToMultiByte(65001, 0, wstr, -1, NULL, 0, NULL, NULL);    
	char* str = new char[len+1];    
	memset(str, 0, len+1);    
	WideCharToMultiByte(65001, 0, wstr, -1, str, len, NULL, NULL);    
	if(wstr) 
		delete[] wstr;    
	return str;    
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	return gb2312; 
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	return gb2312; 
#endif
}

void FontChina::purgeFontChina()
{
	if (mpDicComXml != NULL)
	{
		mpDicComXml->removeAllObjects();
		CC_SAFE_RELEASE(mpDicComXml);
	}
	delete this;
}

FontChina* FontChina::getInstance()
{
	if (mpInstance == NULL)
	{
		mpInstance = new FontChina();
	}
	return mpInstance;
}

void FontChina::initStringXml()
{
	mpDicComXml = Dictionary::create();
	mpDicComXml->retain();

	__String* path = __String::createWithFormat("Documents/string.xml");
	unsigned char* pBuffer = NULL;
	ssize_t bufferSize = 0;
	tinyxml2::XMLDocument myDoc;
	pBuffer = cocos2d::FileUtils::getInstance()->getFileData(path->getCString(), "rb", &bufferSize);
	myDoc.Parse((const char*)pBuffer);

	tinyxml2::XMLElement * root = myDoc.FirstChildElement();
	tinyxml2::XMLElement * block = root->FirstChildElement();
	while (block)
	{
		std::string key = block->GetText();
		block = block->NextSiblingElement();
		__String* value = __String::create(block->GetText());
		mpDicComXml->setObject(value, key);
		block = block->NextSiblingElement();
	}
}

const __String* FontChina::getComString(std::string key)
{
	return mpDicComXml->valueForKey(key);
}