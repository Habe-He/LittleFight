/*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名：   PromptBox
** 日  期：   2015:5:21
** 说  明：	界面弹出提示
** 其  它：	
** 历  史：	2015:5:21 初始版本
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

#include "Public/FontChina.h"

class PromptBox : public Node
{
public:
	static PromptBox* getInstance(string comString);

	bool init(string initString);

	void setMoveTop();

	void setFade();

	void callBack();

private:
	Scale9Sprite* sprite;
};