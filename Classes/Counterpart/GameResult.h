 /*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ����� GameResult
** ���ڣ�   2015:7:10
** ˵����	�ؿ����ѧ��ͨ�ز�
** ������	
** ��ʷ��2015:7:10 ��ʼ�汾
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

enum Result
{
	Result_Win = 0,
	Result_Loss,
	Result_Max
};

class GameResult : public cocos2d::Layer
{
public:
	GameResult(void);
	virtual ~GameResult(void);

	static GameResult* create(Result = Result_Win, int = 180);
	virtual bool init(Result = Result_Win, int = 180);

protected:
	Result checkResult(Result);										/* ����ģʽ����ʤ�� */
	void ResultModeWin();
	void ResultModeLoss();

	void loadPointWin();											/* �ؿ�ʤ�� */
	void loadPointLoss();											/* �ؿ�ʧ�� */
	void winCallBack();
	void getPointStarLv();											/* ���ͨ���Ǽ� */
	void loadFightWarriors();										/* ���������佫 */
	void loadPointCoinExp();										/* ���ͨ�ؽ�ҡ����齱�� */
	void loadPointGoods();											/* ���ͨ����Ʒ���� */

	void loadGameXG1Win();											/* ���ѧ��ģʽ1ʤ�� */
	void loadGameXG2Win();											/* ���ѧ��ģʽ2ʤ�� */
	void loadGameXG3Win();											/* ���ѧ��ģʽ3ʤ�� */
	void loadGameXG4Win();											/* ���ѧ��ģʽ4ʤ�� */
	void loadGameXGLoss(int);										/* ���ѧ��ģʽʧ�� */

	float getTeamExpImprove();										/* ��ȡ���ѧ���ʺž���ӳ� */
	float getRoleExpImprove();										/* ��ȡ���ѧ����������ӳ� */

	void btnPointWin(cocos2d::Ref*, cocos2d::ui::TouchEventType);	/* �ؿ�ʤ���ص� */
	void btnPointLoss(cocos2d::Ref*, cocos2d::ui::TouchEventType);	/* �ؿ�ʧ�ܻص� */

	void pointLossSchedule(float);									/* �����ʱ */

	/* Animate */
	void starAnimate(int);											/* �Ǽ����� */
	void subStarAnimate(int);										/* �Ǽ����� */
	void fireworks();												/* ʤ���̻� */
	void goodsAnimate(cocos2d::ui::ImageView *, float);				/* �����Ʒ���� */

private:
	int		_iTime;													/* ͨ��ʱ�� */
	int		_iPoint;												/* �ؿ�ID */
	int		_iDiff;													/* �ؿ��Ѷ� */
	int		_iStarLv;												/* ͨ���Ǽ� */
	int		_iGameMode;												/* ģʽ */
	int		_iSchedule;												/* ����ʱ���� */

	cocos2d::ui::Widget		*_uiPointWin;							/* ʤ��UI */
	cocos2d::ui::Button		*_btnLife;								/* ���ť */
	cocos2d::Sprite			*_spSchedule;							/* ����ʱ */
};

