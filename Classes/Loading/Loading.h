/*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ�����   Loading
** ��  �ڣ�   2015:3:12
** ˵  ����	���ؽ���
** ��  ����	
** ��  ʷ��	2015:3:12 ��ʼ�汾
*********************************************************************/
#pragma once 
#include "cocos2d.h"
USING_NS_CC;

using namespace std;

#include "Public/EffectAction.h"
#include "Public/FontChina.h"
#include "Public/ToolFunc.h"

const int PROGRESSTAG = 1;
const int LAYERTAG = 2;		// Loading����Layer��Tag

class Loading : public Layer
{
public:
	Loading();
	~Loading();

	virtual void onEnter();
	virtual void onExit();

	int spriteCount;				// ��Ҫ����ͼƬ��������
	int loadSpriteCount;			// �Ѽ���ͼƬ������
	int percent;				// �ٷֱ�

	// ������Դ
	__Array* textureCacheArray;
	
	static Scene* scene();
	bool init();

	// �ض���ͼƬ��ӵ�������Դ����
	void addTextureCacheFromFileByName(const char* res);
	
	Scene* (*pScene)();
	// �����л�
	void setChangeScene(Scene*(*pScene)());

	// �����л��ص�
	void callBackReplaceScene();

	// �ͷ���Դ
	void purgeCache();
	// ������Դ
	void loadCaChe();

	// ��Դ���������ص�
	void loadSpriteCountCallBack(Texture2D* texture, string resourcePath);
	
	void progress(float dt);
	
	static Loading* mpLoading;

	CREATE_FUNC(Loading);

private:
	FontChina* mpFontChina;
};