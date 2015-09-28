#ifndef __VISIBLERECT_H__
#define __VISIBLERECT_H__

#include "cocos2d.h"

class VisibleRect
{
public:
	/* 获取界面矩形区域 */
    static cocos2d::Rect getVisibleRect();

	/* 获取界面矩形区域“左中”点 */
	static cocos2d::Point left();
	/* 获取界面矩形区域“右中”点 */
	static cocos2d::Point right();
	/* 获取界面矩形区域“中顶”点 */
	static cocos2d::Point top();
	/* 获取界面矩形区域“中底”点 */
	static cocos2d::Point bottom();
	/* 获取界面矩形区域“中心”点 */
	static cocos2d::Point center();
	/* 获取界面矩形区域“左上”点 */
	static cocos2d::Point leftTop();
	/* 获取界面矩形区域“右上”点 */
	static cocos2d::Point rightTop();
	/* 获取界面矩形区域原点 */
	static cocos2d::Point leftBottom();
	/* 获取界面矩形区域“右下”点 */
    static cocos2d::Point rightBottom();
private:
    static void lazyInit();
    static cocos2d::Rect s_visibleRect;
};

#endif /* __VISIBLERECT_H__ */
