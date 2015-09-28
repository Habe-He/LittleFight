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

	void confirmButton(cocos2d::Ref*, cocos2d::ui::TouchEventType);	/* 确认 */
	void wipeOutButton(cocos2d::Ref*, cocos2d::ui::TouchEventType); /* 扫荡 */

	void showPointInfo(cocos2d::Point);											/* 关卡信息 */
	void parseJxxgBuff();

	void addTouchEventListener();
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event); 
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event); 
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);

private:
	int		_station;												/* 关卡id */
	int		_star;													/* 星级 */
	cocos2d::EventListenerTouchOneByOne* listener;					/* 触摸事件 */
	cocos2d::ui::ImageView* _piImg;
	std::vector<CheckPointStruct > pointInfo;
};

