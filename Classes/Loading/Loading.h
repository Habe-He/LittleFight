/*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名：   Loading
** 日  期：   2015:3:12
** 说  明：	加载界面
** 其  它：	
** 历  史：	2015:3:12 初始版本
*********************************************************************/
#pragma once 
#include "cocos2d.h"
USING_NS_CC;

using namespace std;

#include "Public/EffectAction.h"
#include "Public/FontChina.h"
#include "Public/ToolFunc.h"

const int PROGRESSTAG = 1;
const int LAYERTAG = 2;		// Loading界面Layer的Tag

class Loading : public Layer
{
public:
	Loading();
	~Loading();

	virtual void onEnter();
	virtual void onExit();

	int spriteCount;				// 需要加载图片的总数量
	int loadSpriteCount;			// 已加载图片的数量
	int percent;				// 百分比

	// 纹理资源
	__Array* textureCacheArray;
	
	static Scene* scene();
	bool init();

	// 特定的图片添加到纹理资源数组
	void addTextureCacheFromFileByName(const char* res);
	
	Scene* (*pScene)();
	// 场景切换
	void setChangeScene(Scene*(*pScene)());

	// 场景切换回调
	void callBackReplaceScene();

	// 释放资源
	void purgeCache();
	// 加载资源
	void loadCaChe();

	// 资源加载数量回调
	void loadSpriteCountCallBack(Texture2D* texture, string resourcePath);
	
	void progress(float dt);
	
	static Loading* mpLoading;

	CREATE_FUNC(Loading);

private:
	FontChina* mpFontChina;
};