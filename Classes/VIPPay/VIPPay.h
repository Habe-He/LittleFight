#ifndef __VIPPay_Scene__
#define __VIPPay_Scene__
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace cocostudio;
using namespace ui;
USING_NS_CC;

#include "PromptBox/PromptBox.h"
#include "Public/FontChina.h"
#include "Scene/MainScene.h"

class VIPPay : public Scene
{
public:
	bool init();

	void itemClick(Ref* pSender, TouchEventType type);							// �����ÿ�����
		
	void closeClick(Ref* pSender, TouchEventType type);							// �ر�

	CREATE_FUNC(VIPPay);
private:
	FontChina* mpFontChina;
	cocos2d::ui::ScrollView* vipScrollView;										// VIP�����ʾ��
};
#endif