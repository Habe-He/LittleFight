#include "ChineseCode.h"

ChineseCode::ChineseCode(void)
{
}

ChineseCode::~ChineseCode(void)
{
}

void ChineseCode::Gb2312ToUnicode(wchar_t* pOut, char *gbBuffer)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	MultiByteToWideChar(0, 0, gbBuffer, 2, pOut, 1);
#endif
	return;
}

void ChineseCode::UTF_8ToUnicode(wchar_t* pOut, char *pText)
{
	char* uchar = (char *)pOut;

	uchar[1] = ((pText[0] & 0x0F) << 4) + ((pText[1] >> 2) & 0x0F);
	uchar[0] = ((pText[1] & 0x03) << 6) + (pText[2] & 0x3F);

	return;
}

void ChineseCode::UnicodeToUTF_8(char* pOut, wchar_t* pText)
{
	// ע�� WCHAR�ߵ��ֵ�˳��,���ֽ���ǰ�����ֽ��ں�
	char* pchar = (char *)pText;

	pOut[0] = (0xE0 | ((pchar[1] & 0xF0) >> 4));
	pOut[1] = (0x80 | ((pchar[1] & 0x0F) << 2)) + ((pchar[0] & 0xC0) >> 6);
	pOut[2] = (0x80 | (pchar[0] & 0x3F));

	return;
}

void ChineseCode::UnicodeToGB2312(char* pOut, wchar_t uData)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	WideCharToMultiByte(0, NULL, &uData, 1, pOut, sizeof(wchar_t), NULL, NULL);
#endif
	return;
}

// ��Ϊ��Urlʹ��
char ChineseCode:: CharToInt(char ch)
{
	if(ch>='0' && ch<='9')return (char)(ch-'0');
	if(ch>='a' && ch<='f')return (char)(ch-'a'+10);
	if(ch>='A' && ch<='F')return (char)(ch-'A'+10);
	return -1;
}

char ChineseCode::StrToBin(char *str)
{
	char tempWord[2];
	char chn;

	tempWord[0] = CharToInt(str[0]);                         //make the B to 11 -- 00001011
	tempWord[1] = CharToInt(str[1]);                         //make the 0 to 0  -- 00000000

	chn = (tempWord[0] << 4) | tempWord[1];                //to change the BO to 10110000

	return chn;
}

// UTF_8 תgb2312
void ChineseCode::UTF_8ToGB2312(string &pOut, char *pText, int pLen)
{
	char buf[4];
	char* rst = new char[pLen + (pLen >> 2) + 2];
	memset(buf, 0, 4);
	memset(rst, 0, pLen + (pLen >> 2) + 2);
	int i = 0;
	int j = 0;
	while(i < pLen)
	{
		if(*(pText + i) >= 0)
		{

			rst[ j ++ ] = pText[ i ++ ];
		}
		else                 
		{
			wchar_t Wtemp;
			UTF_8ToUnicode(&Wtemp, pText + i);
			UnicodeToGB2312(buf, Wtemp);
			unsigned short int tmp = 0;
			tmp = rst[ j ] = buf[ 0 ];
			tmp = rst[ j + 1] = buf[ 1 ];
			tmp = rst[ j + 2 ] = buf[ 2 ];
			i += 3;    
			j += 2;   
		}
	}
	rst[ j ] = '\0';
	pOut = rst; 
	delete [] rst;
}

// GB2312 תΪ UTF-8
void ChineseCode::GB2312ToUTF_8(string& pOut,char *pText, int pLen)
{
	char buf[4];
	memset(buf,0,4);
	pOut.clear();
	int i = 0;
	while(i < pLen)
	{
		//�����Ӣ��ֱ�Ӹ��ƾͿ���
		if( pText[i] >= 0)
		{
			char asciistr[2]={0};
			asciistr[0] = (pText[i++]);
			pOut.append(asciistr);
		}
		else
		{
			wchar_t pbuffer;
			Gb2312ToUnicode( &pbuffer, pText + i );
			UnicodeToUTF_8( buf, &pbuffer );
			pOut.append(buf);
			i += 2;
		}
	}
	return;
}

// ��str����Ϊ��ҳ�е� GB2312 url encode ,Ӣ�Ĳ��䣬����˫�ֽ�  ��%3D%AE%88
string ChineseCode::UrlGB2312(const char * str)
{
	string dd;
	size_t len = strlen( str );
	for (size_t i = 0; i < len; i ++)
	{
		if(isalnum((unsigned char)str[ i ]))
		{
			char tempbuff[ 4 ];
			sprintf(tempbuff, "%%%X", str[ i ]);
			dd.append( tempbuff );
		}
		else if (isspace((unsigned char)str[ i ]))
		{
			dd.append("+");
		}
		else
		{
			char tempbuff[ 4 ];
			sprintf(tempbuff, "%%%X%X", ((unsigned char*)str)[ i ] >> 4, ((unsigned char*)str)[ i ] % 16);
			dd.append(tempbuff);
		}
	}
	return dd;
}

// ��str����Ϊ��ҳ�е� UTF-8 url encode ,Ӣ�Ĳ��䣬�������ֽ�  ��%3D%AE%88
string ChineseCode::UrlUTF8(char * str)
{
	string tt;
	string dd;
	GB2312ToUTF_8(tt, str, (int)strlen(str));

	size_t len = tt.length();
	for (size_t i = 0; i < len; i ++)
	{
		if ( isalnum( (char)tt.at( i ) ) )
		{
			char tempbuff[ 2 ] = { 0 };
			sprintf(tempbuff, "%c", (char)tt.at( i ) );
			dd.append(tempbuff);
		}
		else if ( isspace( (char)tt.at( i ) ) )
		{
			dd.append("+");
		}
		else
		{
			char tempbuff[ 4 ];
			sprintf(tempbuff, "%%%X%X", ((char)tt.at( i ) ) >> 4, ( ( char )tt.at( i ) ) % 16);
			dd.append(tempbuff);
		}

	}
	return dd;
}

// ��url GB2312����
string ChineseCode::UrlGB2312Decode(string str)
{
	string output="";
	char tmp[2];
	int i = 0, idx = 0, len = str.length();

	while( i < len )
	{
		if( str[ i ] == '%' )
		{
			tmp[ 0 ] = str[ i + 1 ];
			tmp[ 1 ] = str[ i + 2 ];
			output += StrToBin(tmp);
			i = i + 3;
		}
		else if( str[ i ] == '+' )
		{
			output += ' ';
			i ++;
		}
		else
		{
			output += str[ i ];
			i ++;
		}
	}
	return output;
}

// ��url utf8����
string ChineseCode::UrlUTF8Decode(string str)
{
	string output="";

	string temp =UrlGB2312Decode(str);//

	UTF_8ToGB2312(output,(char *)temp.data(),strlen(temp.data()));

	return output;
}



