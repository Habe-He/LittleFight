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
	DrawNone,			// û������佫��ʾ
	DrawCom,			// ��ʾ����佫��״̬
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

	void createTeach();													// ����

	CREATE_FUNC(DrawoffDiaplay);
private:
	Button* closeClick;													// �رհ�ť
	DrawStateEnum drawState;												// ����״̬
	int intFor;															// forѭ������
	int index;	
	Label* nameLabel;													// ��Ʒ����
	FontChina* pFontChina;												// �����ַ�
	vector<DrawoffGoodsStruct> drawoffGoodsVector;
	vector<DrawoffIDRecvStruct > drawoffIDVector;
	vector<DrawoffIDRecvStruct > localDrawoffIDVector;
	vector<GeneralProptyStruct > localGeneralVector;
	vector<EquipProptyStruct > localEquipVector;
	vector<PropProptyStruct > localPropVector;
	
};
#endif