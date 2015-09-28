 /*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ����� SuperImage
** ���ڣ�   2015:4:27
** ˵����	��ɫͷ��hp��ʾ��������ťcd��ʾ
** ������	
** ��ʷ��2015:4:27 ��ʼ�汾
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Roles/Role/Role.h"

enum SpImgModeSign
{
	SpImgMode_Major = 0,		/* �������б�HP��ʾ�� */
	SpImgMode_Help,				/* С���HP��ʾ�� */
	SpImgMode_Skill,			/* ����CD��ʾ�� */
	SpImgMode_Max
};

class SuperImage : public cocos2d::Node
{
public:
	SuperImage(void);
	virtual ~SuperImage(void);

	static SuperImage* Create(SpImgModeSign);
	bool init(SpImgModeSign);

	CREATE_FUNC(SuperImage);
	bool init();

public:	
	void createClipper(std::string , std::string , float  = 1.0f);	/* �����ü�ģ��ͼ */
	void setProgressBar(cocos2d::ui::LoadingBar *, cocos2d::ui::LoadingBar *);
	void setProgressBar(std::string, std::string = "", float = 1.0f);
	void resetOwner(Role *);										/* �л���ɫ */

	/* ����CD */
	void setProgressDuration(float);								/* cd���� */
	void runSpriteProgressToRadial(float = 100, int = 1);			/*  */

protected:
	void update(float);
	void progressCDOver(cocos2d::Node*);
	void showActionCD();

private:
	Role *_owner;

	cocos2d::ui::LoadingBar *_mainHp;								/* ��hp������ */
	cocos2d::ui::LoadingBar *_subHp;								/* ��hp������ */
	cocos2d::ProgressTimer	*_proTimer;								/* С���hp/CD��ʾ */
	cocos2d::Sprite			*_spClip;								/* �����ֵ�ͼƬ */
	cocos2d::Label			*_label;								/* ��ʾcd */

	float	_cd;													/* cd���� */
	bool	_bGrayFlag;												/* ͷ���ûұ�� */
};

