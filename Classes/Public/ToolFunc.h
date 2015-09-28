#ifndef __ToolFunc__
#define __ToolFunc__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace std;

class ToolFunc
{
public:
	ToolFunc();
	~ToolFunc();

	// 计算随机数
	static int calcRandom(int starNum, int endNum);

	// 计算角度
	static float getAngle(Point starPoint, Point endPoint);

	/* 播放音效 */
	static unsigned int playEffectFile(const char* , bool = false, float = 1.0f, float = 0.0f, float = 1.0f);

	/* 播放背景音乐 */
	static void playBackgroundFile(const char* = NULL, bool = false);

	// 图片变为灰白色
	static void graySprite(Sprite* sprite);
	static void graySprite(cocos2d::ui::ImageView* sprite);

	// 把图片变为正常颜色
	static void normalSprite(Sprite* sprite);
};
#endif