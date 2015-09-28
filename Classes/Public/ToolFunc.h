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

	// ���������
	static int calcRandom(int starNum, int endNum);

	// ����Ƕ�
	static float getAngle(Point starPoint, Point endPoint);

	/* ������Ч */
	static unsigned int playEffectFile(const char* , bool = false, float = 1.0f, float = 0.0f, float = 1.0f);

	/* ���ű������� */
	static void playBackgroundFile(const char* = NULL, bool = false);

	// ͼƬ��Ϊ�Ұ�ɫ
	static void graySprite(Sprite* sprite);
	static void graySprite(cocos2d::ui::ImageView* sprite);

	// ��ͼƬ��Ϊ������ɫ
	static void normalSprite(Sprite* sprite);
};
#endif