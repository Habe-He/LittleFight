#pragma once 

#include "extensions/cocos-ext.h"
#include "Public/FontChina.h"

USING_NS_CC;
USING_NS_CC_EXT;

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace cocostudio;
using namespace ui;

#include "Loading/Loading.h"

class Login : public Layer
{
public:
	Login();
	~Login();

	bool init();

	static Scene* scene();

	void loginButtton(Ref* sender, TouchEventType type);					// 开始游戏

	void itemButtton(Ref* sender, TouchEventType type);					// 选项

	void otherButtton(Ref* sender, TouchEventType type);				// 其他游戏

	void shareButtton(Ref* sender, TouchEventType type);				// 分享

	CREATE_FUNC(Login);
};