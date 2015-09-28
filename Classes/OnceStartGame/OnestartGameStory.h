#pragma once

#include "cocos2d.h"
USING_NS_CC;

class startonce : public Layer
{
public:
	static Scene* scene();

    virtual bool init();

    CREATE_FUNC(startonce);

	void repScene();
};
