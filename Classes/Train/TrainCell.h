/*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ����� TrainCell
** ���ڣ�   2014:10:9
** ˵����	�������б�Ԫ
** ������	
** ��ʷ��	2014:10:9 ��ʼ�汾
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "DataManager/DataManager.h"
using namespace std;

class TrainCell : public cocos2d::Node
{
public:
	TrainCell(void);
	virtual ~TrainCell(void);

	bool init();
	CREATE_FUNC(TrainCell);

public:
	
	void setCellName(const char *name, const int starLevel);						// ���õ�Ԫ������ 	
 	void setCellLevel(const int level);										// ���õ�Ԫ��ȼ�
	void setCurStar(const int star, const int maxStar);							// ���õ�ǰ�Ǽ�������Ǽ�
	void setCellImage(const char *imgRoot, int maxStar);							// ��������ͷ��
	void setCellGeneralIndex(int index);										// ��������ֵ
	void setType(int type);												// ��ɫ����
	void setExp(int, int exp);												// ǿ������
	void setCellGeneralName(const char *name);								// ��������	
	void setCellUp(int id);												// �Ƿ�����
	int getCellUp();														// �Ƿ�����
	void setEquip(int index, int nameID);										// �佫װ��

	int calcGeneralExp(int level, int exp);										// �����佫��ǰʣ�ྭ��ֵ

	cocos2d::ui::ImageView *image;											// �б�Ԫ��ͼƬ	
	cocos2d::ui::ImageView *imageType;										// �б�Ԫ������
	cocos2d::ui::ImageView *imageSelectSign;									// ���������ʽ
	cocos2d::ui::LoadingBar *	progressBar;									// ������ 
	cocos2d::ui::ImageView *imageWeapon[ 6 ];								// װ��ͼƬ
	cocos2d::ui::ImageView* typeImageView[ 3 ];								// ��������

	cocos2d::ui::ImageView *battle_Image;
	cocos2d::ui::ImageView *captain_Image;
	cocos2d::ui::Widget * trainCellUI;

private:
	cocos2d::ui::Text *txtName;											// �б�Ԫ������
	cocos2d::ui::Text* curStarLevel;										// ��ǰ�Ǽ�
	cocos2d::ui::Text *level_Label;										// �б�Ԫ��ȼ�

	int cellSelectFlag;
	int		m_hRole;
	std::string m_hRoleName;
	int		m_hRoleUp;
private:
	cocos2d::Point m_ptOriginleLoc;
	cocos2d::Point m_ptTouchLoc;

	vector<GeneralUpgradeStruct > localGeneralUpgradeVector;				// �佫������������
};

