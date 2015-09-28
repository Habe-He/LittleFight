#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

enum ModuleMode
{
	ModeFunction,
	ModeEquip,
	ModeGoods,
	ModeMax
};

class NewModule : public cocos2d::Layer
{
public:
	NewModule(void);
	virtual ~NewModule(void);

public:
	static NewModule* create(cocos2d::Node *, ModuleMode);
	bool init(ModuleMode);
	void showItem(std::string, std::string);						/* ��ʾ���� */
	
	virtual void onEnter();
	virtual void onExit();
	virtual bool onTouchBegan(cocos2d::Touch *, cocos2d::Event *);
	virtual void onTouchEnded(cocos2d::Touch *, cocos2d::Event *);
	void setFunction(const std::function<void() > &);

private:
	cocos2d::ui::Text			*_textInfo;							/* ����˵�� */

	cocos2d::EventListenerTouchOneByOne* _listener;					/* �������� */

	cocos2d::Rect		_rcInvalidRegion;							/* �����Ч���� */
	std::function<void() > _func;
};

