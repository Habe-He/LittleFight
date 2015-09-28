 /*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ����� NewComer
** ���ڣ�   2015:7:24
** ˵����	����������
** ������	
** ��ʷ��2015:7:24 ��ʼ�汾
*********************************************************************/
#pragma once
#include "cocos2d.h"

class NewComer : public cocos2d::Node
{
public:
	NewComer(void);
	virtual ~NewComer(void);

	static NewComer *create(cocos2d::Node*, int, int, const std::function<void() > &);
	static NewComer *create(cocos2d::Node*, int, int);
	static bool	isGuideDone(int );
	static int getCurGuideID();
	static void setCurGuideID(int );
	static int getCurGuideStep();
	static void setCurGuideStep(int = 1);
	virtual bool init(int, int, const std::function<void() > &);
	virtual bool init(int, int);
	void initParam();

	void addTargetGuide(int , int, float = 0.0f);					/* ��ʾ��ͷ */
	void addTargetFrame(int , int, float = 1.0f, float = 1.0f);

	/* ���� */
	void runGuide(int, int);

	void guide1Step(int);											/* ����1 */
	void guide1Step1();
	void guide1Step2();
	void guide1Step3();
	void guide1Step4();
	void guide1Step5();
	void guide1Step6();
	void guide1Step7();

	void guide2Step(int);											/* ����2 */
	void guide2Step1();
	void guide2Step2();
	void guide2Step3();
	
	void guide3Step(int);											/* ����3 */
	void guide3Step1();
	void guide3Step2();
	void guide3Step3();
	void guide3Step4();
	void guide3Step5();
	void guide3Step6();
	void guide3Step7();

	void guide4Step(int);											/* ����4 */
	void guide4Step1();
	void guide4Step2();
	void guide4Step3();
	void guide4Step4();
	void guide4Step5();

	void guide5Step(int);											/* ����5 */
	void guide5Step1();
	void guide5Step2();
	void guide5Step3();
	void guide5Step4();
	void guide5Step5();
	void guide5Step6();
	void guide5Step7();
	void guide5Step8();
	void guide5Step9();

	void guide6Step(int);											/* ����6 */
	void guide6Step1();
	void guide6Step2();
	void guide6Step3();

	void guide7Step(int);											/* ����7 */
	void guide7Step1();

	void guide8Step(int);											/* ����8 */
	void guide8Step1();
	void guide8Step2();
	void guide8Step3();
	void guide8Step4();
	void guide8Step5();

	void guide9Step(int);											/* ����9 */
	void guide9Step1();
	void guide9Step2();
	void guide9Step3();
	void guide9Step4();

	void guide10Step(int);											/* ����10 */
	void guide10Step1();
	void guide10Step2();
	void guide10Step3();
	void guide10Step4();
	void guide10Step5();

	void guide11Step(int);											/* ����10 */
	void guide11Step1();
	void guide11Step2();
	void guide11Step3();
	void guide11Step4();

private:
	std::function<void() > _func;
};

