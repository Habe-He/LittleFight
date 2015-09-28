#include "ToolFunc.h"
#include "UserInfo/UserData.h"
#include "SimpleAudioEngine.h"
#include "UserInfo/Define_Info.h"

static bool bFlag = false;

int ToolFunc::calcRandom(int starNum, int endNum)
{
	int result = 0;
	if(starNum >= endNum)
		return endNum;

	if ( false == bFlag )
	{
		struct timeval now;
		gettimeofday(&now, NULL);
		srand(now.tv_usec);
		bFlag = true;
	}
	
	result = starNum + rand() % (endNum - starNum + 1);

	return result;
}

float ToolFunc::getAngle(Point starPoint, Point endPoint)
{
	auto theta = (starPoint - endPoint).getAngle();
	return (theta) * 180 / M_PI;
}

/*********************************************************************
** 功能：		播放音效
** 输入参数：	
** 返回值：		unsigned int
** 修改记录：	
*********************************************************************/
unsigned int ToolFunc::playEffectFile(const char* pszFilePath, bool bLoop, float pitch, float pan, float gain)
{
	if (UserData::getInstance()->getEffectState())
	{
		std::stringstream stream;
		stream << "EM/" << pszFilePath << ".ogg";
		return CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(stream.str().c_str(), bLoop, pitch, pan, gain);
	}

	return 0;
}

/*********************************************************************
** 功能：		播放背景音乐
** 输入参数：	bool bFlag: 开启或关闭
** 返回值：		无
** 修改记录：	
*********************************************************************/
void ToolFunc::playBackgroundFile(const char* pszFilePath, bool bLoop)
{
	if (UserData::getInstance()->getEffectState())
	{		
		if (NULL == pszFilePath)
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(BackGround, bLoop);
		}
		else
		{
			std::stringstream stream;
			stream << "EM/" << pszFilePath << ".ogg";
			CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(stream.str().c_str(), bLoop);
		}
	}
}

void ToolFunc::graySprite(Sprite* sprite)
{
	if(sprite)  
	{  
		GLProgram * p = new GLProgram();  
		p->initWithFilenames("Shader/gray.vsh", "Shader/gray.fsh");  
		p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);  
		p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);  
		p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);  
		p->link();  
		p->updateUniforms();  
		sprite->setShaderProgram(p);  
	} 
}

void ToolFunc::graySprite(cocos2d::ui::ImageView* sprite)
{
	if(sprite)  
	{  
		GLProgram * p = new GLProgram();  
		p->initWithFilenames("Shader/gray.vsh", "Shader/gray.fsh");  
		p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);  
		p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);  
		p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);  
		p->link();  
		p->updateUniforms();  
		sprite->setShaderProgram(p);  
	} 
}

void ToolFunc::normalSprite(Sprite* sprite)
{
	if(sprite)  
	{  
		sprite->setShaderProgram(ShaderCache::getInstance()->getProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP));
	} 
}