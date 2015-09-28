/*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名：   GeneralDetails
** 日  期：   2015:4:30
** 说  明：	
** 其  它：	武将详情
** 历  史：	2015:4:30 初始版本
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;
using namespace std;

#include "Counterpart/RoleCreate.h"
#include "DataManager/DataManager.h"
#include "EquipmentInfo.h"
#include "Public/FontChina.h"
#include "PromptBox/PromptBox.h"
#include "StateBar/StateBarNode.h"
#include "NewComer/NewComer.h"


const int EquipCount = 6;				// 装备数量
const int StarID = 10001;				// 武将起始ID
const int SkillStarEnum = 4;			// 技能起始枚举
const int PanelTrainZ = 2;			// 培养和天赋面板的Zorder
const int RoleLayerFlag = 3900;		// 显示人物层
const int TalentFlag = 4;				// 天赋
const int SkillFlag = 5;				// 技能
const int TopPanelFlag = 3901;

enum PanelButton
{
	SKILLButton,					// 技能
	DETIALButton,					// 详情
	EVOButton,					// 进化
	TRAINButton,					// 培养
	TALENTButton,					// 天赋
	MAXButton,					// 最大值
};

enum SkillOrder
{
	SkillSA = 10,
	SkillSB,
	SkillSC,
	SkillSD,
};

struct SESCStruct
{
	int sameName;		// 同名武将
	int addStar;		// 升星
	int addEvo;		// 升阶
	int level;			// 升星等级限制
	int exp;
	int soul;
	int coin;
};

class GeneralDetails : public Scene
{
public:
	GeneralDetails();
	virtual ~GeneralDetails();
	bool init();

	void closeButton(Ref* pSender, TouchEventType type);				// 界面关闭按钮
	void initHeroData();											// 当前界面所用数据初始化
	void initHeroAnimation(string nameString);							// 初始化人物动画
	void initEquipData();											// 装备初始化、以及人物名称星级类型初始化
	void initHeroSkill(int heroStarLevel, int heroID);						// 人物技能（图片、名称、伤害、等级、升级消耗金币）
	void showLabel();											// 详细属性
	void setButtonBright(PanelButton panelButton);						// 设置按钮高亮
	void setBright(int btnID);										// 设置右侧三个按钮高亮
	void skillPhotoCallBack(Ref* pSender, TouchEventType type);			// 点击技能按钮回调
	void SkillUpgradeCallBack(Ref* pSender, TouchEventType type);			// 技能升级回调
	void equipCallBack(Ref* pSender, TouchEventType type);				// 点击装备图片
	void skillButton(Ref* pSender, TouchEventType type);					// 技能		
	void detailButton(Ref* pSender, TouchEventType type);				// 详情
	void evolutionButton(Ref* pSender, TouchEventType type);				// 进化
	void trainButton(Ref* pSender, TouchEventType type);				// 培养
	void skillBasicButton(Ref* pSender, TouchEventType type);				// 技能（基础界面）
	void talentButton(Ref* pSender, TouchEventType type);				// 天赋
	void talentImageButton(Ref* pSender, TouchEventType type);			// 天赋图片
	void skillPanelButton(Ref* pSender, TouchEventType type);				// 点击技能框提示技能介绍
	void lightTalentButton(Ref* pSender, TouchEventType type);			// 天赋确认按钮
	void cancelTalentButton(Ref* pSender, TouchEventType type);			// 天赋重置按钮
	void topCloseButton(Ref* pSender, TouchEventType type);				// 关闭弹出选择武将界面
	void photoImageCall( Ref* pSender, TouchEventType type );			// 进化选择人物头像回调
	void panelTouchCallback(Ref* pSender, TouchEventType type);			// 显示选择武将界面
	void evoClick(Ref* pSender, TouchEventType type);					// 进化按钮
	void trainTypeButton(Ref* pSender, TouchEventType type);				// 培养通用按钮
	void backButton(Ref* pSender, TouchEventType type);				// 详情返回按钮
	void trianPillButton(Ref* pSender, TouchEventType type);				// 培养发送按钮
	bool isTalentIDValid();										// 当前选择的天赋ID是否有效
	int calcGeneralExp(int level, int exp);								// 计算武将当前剩余经验值
	void setHeroSkillLevel();										// 设置人物升级后，技能未解锁的问题
	int trainShowLabel( int tag );									// 培养显示函数
	void evoInit();												// 进化初始化
	void filxCallBack();											// 左侧翻转回调
	void filxCallBackA();											// 左侧翻转回调2
	void effectCallBack();											// 培养特效完成

	int calcEvoSYExp(int iExp);									// 升星或者升阶剩余经验
	SESCStruct calcNeedNum();									// 计算对应的 同名武将、经验、灵魂石、金币
	void showGeneral();											// 显示武将
	void onEnter();
	void onExit();	

	void typeButton(Ref* pSender, TouchEventType type);				// 筛选武将按钮

	void showSelectHero();										// 加载被吃武将头像

	CREATE_FUNC(GeneralDetails);

	// 以下是弹出界面的功能
	void initMaidanData();											// 可选武将数据初始化
	void initHeroPanel();											// 初始化可用来选择英雄界面

private:
	int pillValues[ 5 ];											// 培养提供的属相变 
	ImageView* photoImage[ 5 ];									// 进化选择人物头像
	int selectedTalentID;											// 选择天赋的ID
	FontChina* mpFontChina;										// 提示文字
	Role* heroRole;												// 人物
	Layout* panelRight;											// 右侧面板
	Layout* panelDetial;											// 左侧详情
	Layout* panelLeft;											// 左侧面板
	Layout* panelTrain;											// 显示培养
	Layout* panelEvo;											// 进化层
	int clickPosFlag;												// 点击位置的标志
	int expCount;												// 被吃武将所提供经验
	cocos2d::Point m_ptOriginleLoc;									// 临时变量
	cocos2d::Point m_ptTouchLoc;
	cocos2d::ui::ScrollView* topScrollView;								// 选择人物层	
	Layout* skillLayout;											// 技能层
	Layout* talentLayout;											// 天赋层
	vector<GeneralProptyStruct > maidanVector;						// 练兵场获取到的武将属性
	vector<GeneralProptyStruct > curGeneralVector;						// 当前界面所需的当前武将属性
	vector<GeneralProptyStruct > localGeneralVector;					// 武将的原始属性值
	vector<EquipProptyStruct > localEquipVector;						// 装备基础属性
	vector<EquipRefineStruct > localEquipRefineRuleVector;				// 装备精炼本地规则
	vector<GeneralDetailRecvStruct > interGeneralVector;					// 服务器获取到的武将属性
	vector<SkillNameStruct > localSkillNameVector;						// 技能基础属性
	vector<SkillUpgradeStruct > localSkillUpgradeVector;					// 技能升级数据
	vector<GeneralUpgradeStruct > localGeneralUpgradeVector;			// 武将技能升级规则
	vector<TalentLocalStruct > lcoalTalentVector;						// 所有天赋
	vector<TalentLocalStruct > meetTalentVector;						// 适合天赋
	vector<SkillNameStruct > localTempSkillNameVector;					// 符合要求的技能
	vector<SkillAddPropty > localSkillAddPropty;						// 本地技能升级属性增加
	vector<int > interTalentVector;									// 武将天赋
	vector<PlayerInfoRecvStruct > interPlayerInfoVector;					// 玩家数据
	vector<GeneralEvoLocalStruct > localGeneralEvoVector;				// 本地武将进化规则
	vector<GeneralProptyStruct > selectedHero;						// 选中被吃掉的武将
	vector<MaidanStruct > interMaidanVector;							// 服务器读取到的练兵场数据
	vector<GeneralProptyStruct > tempGeneralVector;					// 根据按钮选择显示武将信息
	vector<GeneralProptyStruct > curTempGeneralVector;					// 当前界面所需的当前武将属性
	vector<GeneralEvoExpLocalStruct > localGeneralEvoExpVector;			// 本地武将进化提供经验

	NewComer	*_comer;
};
