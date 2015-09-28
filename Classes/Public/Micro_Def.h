 /*********************************************************************
** Copyright (C) �ȶ��ķ�����Ƽ����޹�˾
** �ļ����� Micro_Def
** ���ڣ�   2014:10:14
** ˵����	ϵͳ�궨���ļ��������·����������
** ������	
** ��ʷ��2014:10:14 ��ʼ�汾
*********************************************************************/
#pragma once

/* MainScene�� Begin */
#define mainSceneUIRoot "UI/All/Mian.ExportJson"							// ������UI·��
#define btnAddCoin		"Coin_Button"										// ��ӽ��
#define btnAddDiamon	"Diamond_Button"									// �����ʯ
#define btnAddPower		"Power_Button"										// �������
#define btnTask			"Button_SingIn"										// ����
#define imgPost			"Post_Image"										// ����image
/* MainScene�� End */

/* CommonMenu�� Begin */
#define commonMenuUIRoot	"UI/CommonMenu/CommonMenu.ExportJson"		// �����˵�UI·��
#define btnAddCoinName		"btnAddCoin"								// ��ӽ��
#define btnAddDiamondName	"btnAddDiamond"								// �����ʯ
#define btnAddPowerName		"btnAddPower"								// �������
#define btnBackNameMenu		"btnBack"									// ���ز˵�
/* CommonMenu�� End */

/* SelectGeneral�� Begin */
#define SelectGeneralUIRoot	"UI/SelectGeneralUI/SelectGeneralUI.ExportJson"// ѡ��ʿUI·��
#define btnSelectName		"Select"									// ѡ�а�ť
#define btnStrongName		"Strong"									// ǿ����ť
#define btnEvolutionName	"JinHua"									// ������ť
#define imgShowRole			"Role"										// ��ɫͼƬ��ʾ�ؼ�
#define listRoleSelect		"SelectRole_list"							// ��ɫѡ���б�

#define selectGeneralLog_FailToLoad		"Fail to load TrainUI!"			// ����ʧ��log
/* SelectGeneral�� End */

/* SelectAllay�� Begin */
#define SelectAllayUIRoot	"UI/All/PointSets.ExportJson"				// ����ʿUI·��
#define btnDetial			"Detial"									// ����
#define btnUnloadGeneral			"unload"							// �½�
#define btnStarFight			"StarFight"								// ��ʼ��Ϸ
#define btnChangeGeneral			"ChangeGeneral"						// ����
#define ScrollWeaponCellUIRoot			"UI/ScrollWeaponCell/ScrollWeaponCellUi.ExportJson"	
/* SelectAllay�� End */

/* Train�� Begin */
#define TrainUIRoot			"UI/TrainUI/TrainUI.ExportJson"				// ����ʿUI·��
#define btnFighting			"Fighting"									// ��ս
#define scrollCellListName	"traincell_list"							// ������
#define turnPageLeft		"TurnPageLeft"								// ��������
#define turnPageRight		"TurnPageRight"								// �������ҷ�
#define trainLog_FailToLoad "Fail to load TrainUI!"						// ����UIʧ���б�
const float maxScrollViewPercent = 100.0f;								// �����㷭ҳ���ֵ
const float minScrollViewPercent = 0.0f;								// �����㷭ҳ��Сֵ
const float scrollTime = 0.3f;											// �����㷭ҳʱ��
/* Train�� End */

/* TrainCell�� Begin */
#define TrainCellUIRoot		"UI/TrainCellUI/TrainCell.json"		// ѵ������ʿ�б�UI·��
#define btnFighting			"Fighting"									// ��ս
#define imageName			"image"										// ͼƬ�ؼ�Name
#define nameText			"name_Label"										// ��ʿ�����ı���Name
#define countryText			"level_Label"									// ��ʿ�����ı���Name
#define starText			"star_Label"										// ��ʿ�Ǽ��ı���Name

const float img_scale_down = 0.8f;										// ͼƬ���������С����
const float img_scale_up = 1.0f;										// ͼƬ�������ԭ����
/* TrainCell�� End */

/* GeneralInfo�� Begin */
#define GeneralInfoUIRoot		"UI/All/GeneralDetails.ExportJson"				// ��ʿ����UI·��
#define btnStrengthen		"Strength_Button"							// ǿ����ť
#define btnEvolution			"Evolution_Button"							// ������ť
#define imageGeneral		"OriginalPhoto_Image"							// ԭ��
#define imageSkill1			"Skill_One_Image"							// ����1
#define imageSkill2			"Skill_Two_Image"							// ����2
#define imageSkill3			"Skill_Three_Image"							// ����3
#define imageSkill4			"Skill_Four_Image"							// ����4
#define labelATK			"Fighting_Label"								// ս����
#define labelPhydefend		"PD_Label"									// ���
#define labelMagicdefend		"MD_Label"								// ����
#define	labelLifeUp			"HPRise_Label"								// ��Ѫ
#define labelLevel			"Levle_Label"								// �ȼ�
#define labelStrength			"Attack_Label"								// ����
#define labelHP				"HP_Label"									// Ѫ��
#define labelMagicValue		"MagicValue_Label"							// ����
#define progressBarExp		"HPRise_Label"								// ����
#define imageStar1			"Star1"									// ��
#define imageStar2			"Star2"									// ��
#define imageStar3			"Star3"									// ��
#define imageStar4			"Star4"									// ��
#define imageStar5			"Star5"									// ��
/* GeneralInfo�� End */

/* Store�� Begin */
#define StoreUIRoot		"UI/Store/StoreUI/StoreUI.ExportJson"			// �̳�UI·��
#define pagePropStore	"Prop"											// ����
#define pagePacks		"Packs"											// ���
#define pageDrawCard	"DrawCard"										// �鿨
#define pageMysteryShop "MysteryShops"									// �����̵�
#define storePanel		"Panel_8"										// ������
/* Store�� End */

/* Wareroom�� Begin */
#define WareroomUIRoot	"UI/All/Wareroom.ExportJson"						// �̳�UI·��
#define wareroomScroll	"PageView"									// ������
#define pagePropWR		"Prop"										// ����
#define pageEquip		"Equip"										// װ��
#define pageChip		"Pic"											// ��Ƭ
/* Wareroom�� End */