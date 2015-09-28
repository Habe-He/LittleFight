#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "StateBar/StateBarNode.h"
#include "NewComer/NewComer.h"

class EquipEnhance : public cocos2d::Layer
{
public:
	EquipEnhance(void);
	virtual ~EquipEnhance(void);

	static cocos2d::Scene *Create();
	bool init();
	CREATE_FUNC(EquipEnhance);

protected:
	enum EEMode {EE_Strengthen = 0, EE_Refine};						/* 强化、精炼模式 */
	enum EEImgEquip {EE_Equip_1, EE_Equip_2, EE_Equip_3, EE_Equip_4, EE_Equip_5, EE_Equip_6, EE_Equip_Max};

	typedef struct _tagEERoleInfo									/* 角色装备信息 */
	{
		int		pkID;												/* 角色PKID */
		char	name[20];											/* 角色名字 */
		char	cname[20];											/* 角色名字 */
		int		job;												/* 角色职业 */
		int		level;												/* 角色等级 */
		int		exp;												/* 角色经验进度 */
		int		fight;												/* 角色战斗力 */
		EquipProptyStruct	Equips[EE_Equip_Max];					/* 角色装备 */
	} EERoleInfo;

	enum EERole
	{
		EE_RoleName,
		EE_RoleLv,
		EE_RoleMax
	};

	enum EEButton
	{
		EE_RolePrev,												/* 前一个角色 */
		EE_RoleNext,												/* 下一个角色 */
		EE_EquipS,													/* 强化 */
		EE_EquipS5,													/* 强化5 */
		EE_EquipR,													/* 精炼 */
		EE_Close,													/* 关闭 */
		EE_Btn_Max
	};

	enum EELabelStr													/* 装备强化信息文本框 */
	{
		EE_StrName,													/* 名称 */
		EE_StrLv0,													/* 等级（前） */
		EE_StrLv1,													/* 等级（后） */
		EE_StrProp0,												/* 属性（前） */
		EE_StrProp1,												/* 属性（后） */
		EE_StrCoin0,												/* 一次强化金币 */
		EE_StrCoin1,												/* 5次强化金币 */
		EE_StrMax
	};

	enum EELableRef													/* 装备精炼信息文本框 */
	{
		EE_RefName0,												/* 名称（前） */
		EE_RefName1,												/* 名称（后） */
		EE_RefProp00,												/* 属性1（前） */
		EE_RefProp10,												/* 属性2（前） */
		EE_RefProp01,												/* 属性1（后） */
		EE_RefProp11,												/* 属性2（后） */
		EE_RefCoin,													/* 精炼金币 */
		EE_RefMax
	};

protected:
	void initPara();												/* 参数初始化 */
	void loadStateBar();
	void loadEnhanceFactory();										/* 加载UI */
	void loadRoleEquipInfo();										/* 加载角色装备信息 */
	void loadEquipList();											/* 加载可用装备列表 */

	/* 显示 */
	void showRoleEquipInfo();										/* 显示角色装备 */
	void showStrEquipInfo();										/* 显示装备1-4信息 */
	void showRefEquipInfo();										/* 显示装备5-6信息 */
	void showEquipUsable();											/* 显示精炼装备材料 */
	void showNotice(std::string);									/* 显示提示 */

	/* 事件响应 */
	void btnResponse(cocos2d::Ref* , cocos2d::ui::TouchEventType ); /* Button点击响应 */
	void btnEquipStrengthen();										/* 装备强化 */
	void btnEquipStrengthen5();										/* 装备强化5次 */
	void btnEquipRefine();											/* 装备精炼 */
	void imgResponse(cocos2d::Ref* , cocos2d::ui::TouchEventType ); /* ImageView点击响应 */
	void svEquipListResponse(cocos2d::Ref* , cocos2d::ui::TouchEventType );/* ScrollView点击响应 */

	/* 其它 */
	void changeEnhanceMode(EEMode);									/* 强化、精炼模式切换 */
	float getStrengthenImprove(int , int);							/* 获取强化属性提升值 */
	int	getStrengthenCoin(int , int);								/* 获取强化消耗金币 */
	void clearPanel();												/* 情况装备信息显示 */
	void removeEquipUsed();											/* 移除使用掉的装备 */
	void EnhanceAnimate();											/* 强化、精炼动画 */
	void EnhanceAnimateCB(cocos2d::Node *);							/* 强化、精炼动画回调函数 */

private:
	unsigned int			_PointSetIndex;							/* 武将索引ID */
	int						_iEquipIndex;							/* 选中强化/精炼的装备索引 */
	int						_iRefineCost;							/* 精炼费用 */
	EEMode					_EE_EnMode;								/* 标记强化、精炼模式 */

	StateBarNode			*_StateBar;
	cocos2d::ui::Widget		*_EnhanceUI;
	cocos2d::ui::Layout		*_panelStr;								/* 强化层 */
	cocos2d::ui::Layout		*_panelRef;								/* 精炼层 */
	cocos2d::ui::ImageView	*_imgEquip[EE_Equip_Max];				/* 装备显示控件 */
	cocos2d::ui::ImageView	*_imgJob[3];							/* 职业图标 */
	cocos2d::ui::ImageView	*_imgStrSelect;							/* 选中的强化装备 */
	cocos2d::ui::ImageView	*_imgRefSelect;							/* 选中的精炼装备 */
	cocos2d::ui::Text		*_txtStr[EE_StrMax];					/* 装备强化信息文本框 */
	cocos2d::ui::Text		*_txtRef[EE_RefMax];					/* 装备精炼信息文本框 */
	cocos2d::ui::Text		*_txtRole[EE_RoleMax];					/* 武将基本信息 */
	cocos2d::ui::TextAtlas	*_txtRoleFight;							/* 武将战斗力 */
	cocos2d::ui::LoadingBar	*_lbRefineExp;							/* 精炼经验值 */
	cocos2d::ui::LoadingBar *_lbRoleExp;							/* 武将经验进度条 */
	cocos2d::ui::ScrollView	*_svEquipList;							/* 被选中装备列表 */

	cocos2d::Node			*_roleNode;								/* 角色显示层 */

	std::vector<EERoleInfo >			_PointSets;					/* 上阵武将装备信息 */
	std::vector<int >					_EquipUsing;				/* 精炼时被选中的装备PKID */
	std::vector<EquipProptyStruct >		_EquipList;					/* 可用装备列表 */
	std::vector<EquipRefineStruct >		_localRefineRule;

	NewComer		*_comer;
};

