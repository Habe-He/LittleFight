/*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ����� StoreProp
** ���ڣ�   2014:10:10
** ˵����	  ���˽���----------------���߽���
** ������	  
** ��ʷ��	2014:10:10 ��ʼ�汾
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Public/FontChina.h"
using namespace std;
USING_NS_CC;

class StoreProp : public cocos2d::Node
{
public:
	StoreProp();
	virtual ~StoreProp();

public:
	// ��ƷID���������ơ�����ƴ�����������۸񡢱���������
	static StoreProp *create(int id, const std::string chinaName, const std::string chinaSmallName, const int count, int price, char tableName[30], int index);

protected:
	bool init(int id, const std::string chinaName, const std::string chinaSmallName, const int count, int price, char tableName[30], int index);
	/* �رհ�ť */
	void btnBuy(cocos2d::Ref* , cocos2d::ui::TouchEventType);
	/* ͼƬ��ʾ */
	void showImage(cocos2d::ui::ImageView* , std::string);

private:
	std::string m_strPropName;

	// �����
	std::vector<std::string> v_tableName;
	// ID 
	vector<int> v_tableID;
	// ����
	vector<int> v_count;
	// ����
	vector<int> v_price;
};