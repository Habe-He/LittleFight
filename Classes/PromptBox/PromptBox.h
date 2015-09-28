/*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ�����   PromptBox
** ��  �ڣ�   2015:5:21
** ˵  ����	���浯����ʾ
** ��  ����	
** ��  ʷ��	2015:5:21 ��ʼ�汾
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