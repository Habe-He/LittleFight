#ifndef __Drawoff_Display_Scene__
#define __Drawoff_Display_Scene__
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;
using namespace std;

#include "DataManager/DataManager.h"
#include "DataManager/DataRecvEntities.h"
#include "DataManager/DataSendEntities.h"
#include "Public/FontChina.h"
#include "Counterpart/RoleCreate.h"

const int ActionFlag = 11;
const int DRoleLayerFlag = 12;

enum DrawStateEnum
{
	DrawNone,			// 没有完成武将显示
	DrawCom,			// 显示完成武将的状态
};

class DrawoffDiaplay : public cocos2d::Scene
{
public:
	static Scene* scene();

	DrawoffDiaplay();
	~DrawoffDiaplay();
		
	bool init();

	void showAnim(string nameString);

	void showSprite();

	void showSpriteCallBack( Node* pSender, void* targat );

	void close(Ref* pSender, TouchEventType type);

	void layerRoleClose();

	void onEnter();
	void onExit();	
	bool onTouchBegan(Touch *touch, Event *unused_event);

	void createTeach();													// 引导

	CREATE_FUNC(DrawoffDiaplay);
private:
	Button* closeClick;													// 关闭按钮
	DrawStateEnum drawState;												// 界面状态
	int intFor;															// for循环次数
	int index;	
	Label* nameLabel;													// 物品名称
	FontChina* pFontChina;												// 中文字符
	vector<DrawoffGoodsStruct> drawoffGoodsVector;
	vector<DrawoffIDRecvStruct > drawoffIDVector;
	vector<DrawoffIDRecvStruct > localDrawoffIDVector;
	vector<GeneralProptyStruct > localGeneralVector;
	vector<EquipProptyStruct > localEquipVector;
	vector<PropProptyStruct > localPropVector;
	
};
#endif