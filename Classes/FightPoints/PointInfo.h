#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "DataManager/DataRecvEntities.h"

class PointInfo : public cocos2d::Layer
{
public:
	PointInfo(void);
	virtual ~PointInfo(void);

public:
	static cocos2d::Scene* scene(cocos2d::Point, int, int);
	static PointInfo* create(cocos2d::Point, int, int);
	virtual bool init(cocos2d::Point, int, int);

protected:
	virtual void onEnter();
	virtual void onExit();

	void confirmButton(cocos2d::Ref*, cocos2d::ui::TouchEventType);	/* ȷ�� */
	void wipeOutButton(cocos2d::Ref*, cocos2d::ui::TouchEventType); /* ɨ�� */

	void showPointInfo(cocos2d::Point);											/* �ؿ���Ϣ */
	void parseJxxgBuff();

	void addTouchEventListener();
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event); 
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event); 
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);

private:
	int		_station;												/* �ؿ�id */
	int		_star;													/* �Ǽ� */
	cocos2d::EventListenerTouchOneByOne* listener;					/* �����¼� */
	cocos2d::ui::ImageView* _piImg;
	std::vector<CheckPointStruct > pointInfo;
};

