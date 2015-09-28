 /*********************************************************************
** Copyright (C) 萌动四方网络科技有限公司
** 文件名： Micro_Def
** 日期：   2014:10:14
** 说明：	系统宏定义文件，定义宏路径、常量等
** 其它：	
** 历史：2014:10:14 初始版本
*********************************************************************/
#pragma once

/* MainScene类 Begin */
#define mainSceneUIRoot "UI/All/Mian.ExportJson"							// 主界面UI路径
#define btnAddCoin		"Coin_Button"										// 添加金币
#define btnAddDiamon	"Diamond_Button"									// 添加钻石
#define btnAddPower		"Power_Button"										// 添加体力
#define btnTask			"Button_SingIn"										// 任务
#define imgPost			"Post_Image"										// 公告image
/* MainScene类 End */

/* CommonMenu类 Begin */
#define commonMenuUIRoot	"UI/CommonMenu/CommonMenu.ExportJson"		// 公共菜单UI路径
#define btnAddCoinName		"btnAddCoin"								// 添加金币
#define btnAddDiamondName	"btnAddDiamond"								// 添加钻石
#define btnAddPowerName		"btnAddPower"								// 添加体力
#define btnBackNameMenu		"btnBack"									// 返回菜单
/* CommonMenu类 End */

/* SelectGeneral类 Begin */
#define SelectGeneralUIRoot	"UI/SelectGeneralUI/SelectGeneralUI.ExportJson"// 选择将士UI路径
#define btnSelectName		"Select"									// 选中按钮
#define btnStrongName		"Strong"									// 强化按钮
#define btnEvolutionName	"JinHua"									// 进化按钮
#define imgShowRole			"Role"										// 角色图片显示控件
#define listRoleSelect		"SelectRole_list"							// 角色选择列表

#define selectGeneralLog_FailToLoad		"Fail to load TrainUI!"			// 加载失败log
/* SelectGeneral类 End */

/* SelectAllay类 Begin */
#define SelectAllayUIRoot	"UI/All/PointSets.ExportJson"				// 出阵将士UI路径
#define btnDetial			"Detial"									// 详情
#define btnUnloadGeneral			"unload"							// 下将
#define btnStarFight			"StarFight"								// 开始游戏
#define btnChangeGeneral			"ChangeGeneral"						// 换将
#define ScrollWeaponCellUIRoot			"UI/ScrollWeaponCell/ScrollWeaponCellUi.ExportJson"	
/* SelectAllay类 End */

/* Train类 Begin */
#define TrainUIRoot			"UI/TrainUI/TrainUI.ExportJson"				// 出阵将士UI路径
#define btnFighting			"Fighting"									// 开战
#define scrollCellListName	"traincell_list"							// 滚动层
#define turnPageLeft		"TurnPageLeft"								// 滚动层左翻
#define turnPageRight		"TurnPageRight"								// 滚动层右翻
#define trainLog_FailToLoad "Fail to load TrainUI!"						// 加载UI失败列表
const float maxScrollViewPercent = 100.0f;								// 滚动层翻页最大值
const float minScrollViewPercent = 0.0f;								// 滚动层翻页最小值
const float scrollTime = 0.3f;											// 滚动层翻页时间
/* Train类 End */

/* TrainCell类 Begin */
#define TrainCellUIRoot		"UI/TrainCellUI/TrainCell.json"		// 训练场将士列表UI路径
#define btnFighting			"Fighting"									// 开战
#define imageName			"image"										// 图片控件Name
#define nameText			"name_Label"										// 将士姓名文本框Name
#define countryText			"level_Label"									// 将士国籍文本框Name
#define starText			"star_Label"										// 将士星级文本框Name

const float img_scale_down = 0.8f;										// 图片点击按下缩小倍率
const float img_scale_up = 1.0f;										// 图片点击弹起还原倍率
/* TrainCell类 End */

/* GeneralInfo类 Begin */
#define GeneralInfoUIRoot		"UI/All/GeneralDetails.ExportJson"				// 将士详情UI路径
#define btnStrengthen		"Strength_Button"							// 强化按钮
#define btnEvolution			"Evolution_Button"							// 进化按钮
#define imageGeneral		"OriginalPhoto_Image"							// 原画
#define imageSkill1			"Skill_One_Image"							// 技能1
#define imageSkill2			"Skill_Two_Image"							// 技能2
#define imageSkill3			"Skill_Three_Image"							// 技能3
#define imageSkill4			"Skill_Four_Image"							// 技能4
#define labelATK			"Fighting_Label"								// 战斗力
#define labelPhydefend		"PD_Label"									// 物防
#define labelMagicdefend		"MD_Label"								// 法防
#define	labelLifeUp			"HPRise_Label"								// 回血
#define labelLevel			"Levle_Label"								// 等级
#define labelStrength			"Attack_Label"								// 攻击
#define labelHP				"HP_Label"									// 血量
#define labelMagicValue		"MagicValue_Label"							// 蓝量
#define progressBarExp		"HPRise_Label"								// 经验
#define imageStar1			"Star1"									// 星
#define imageStar2			"Star2"									// 星
#define imageStar3			"Star3"									// 星
#define imageStar4			"Star4"									// 星
#define imageStar5			"Star5"									// 星
/* GeneralInfo类 End */

/* Store类 Begin */
#define StoreUIRoot		"UI/Store/StoreUI/StoreUI.ExportJson"			// 商城UI路径
#define pagePropStore	"Prop"											// 道具
#define pagePacks		"Packs"											// 礼包
#define pageDrawCard	"DrawCard"										// 抽卡
#define pageMysteryShop "MysteryShops"									// 神秘商店
#define storePanel		"Panel_8"										// 容器层
/* Store类 End */

/* Wareroom类 Begin */
#define WareroomUIRoot	"UI/All/Wareroom.ExportJson"						// 商城UI路径
#define wareroomScroll	"PageView"									// 滚动层
#define pagePropWR		"Prop"										// 道具
#define pageEquip		"Equip"										// 装备
#define pageChip		"Pic"											// 碎片
/* Wareroom类 End */