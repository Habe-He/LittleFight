#include "GeneralDetails.h"

const int cellRow = 5;							// 武将列数
const Size cellSize = Size(110.0f, 160.0f);				// 滚动层cell size 
const float cellScale = 0.9f;

const int DiamondValue = 20;						// 重置天赋消耗
const int pillNeed = 10;							// 培养丹消耗数量
const int coinNeed = 2000;						// 培养金币消耗
const int diamondNeed = 10;						// 钻石数目消耗

GeneralDetails::GeneralDetails()
{
	expCount = 0;
	for (int i = 0; i < 5; i++)
	{
		pillValues[ i ] = 0;
	}
}

GeneralDetails::~GeneralDetails()
{

}

bool GeneralDetails::init()
{
	localSkillNameVector = DataManager::getInstance()->localSkillNameVector();
	if (localSkillNameVector.size() == 0)
	{
		DataManager::getInstance()->SkillNameDataParser();
		localSkillNameVector = DataManager::getInstance()->localSkillNameVector();
	}

	localSkillUpgradeVector = DataManager::getInstance()->localSkillUpgradeVector();
	if (localSkillUpgradeVector.size() == 0)
	{
		DataManager::getInstance()->SkillUpgradeDataParser();
		localSkillUpgradeVector = DataManager::getInstance()->localSkillUpgradeVector();
	}
	localGeneralUpgradeVector = DataManager::getInstance()->localGeneralUpgradeVector();
	if (localGeneralUpgradeVector.size() == 0)
	{
		DataManager::getInstance()->generalUpgradeDataParser();
		localGeneralUpgradeVector = DataManager::getInstance()->localGeneralUpgradeVector();
	}
	localEquipRefineRuleVector = DataManager::getInstance()->localEquipRefineVector();
	if (localEquipRefineRuleVector.size() == 0)
	{
		DataManager::getInstance()->equipRefineRule();
		localEquipRefineRuleVector = DataManager::getInstance()->localEquipRefineVector();
	}
	localEquipVector = DataManager::getInstance()->localEquipProptyVector();
	if (localEquipVector.size() == 0)
	{
		DataManager::getInstance()->equipDataParser();
		localEquipVector = DataManager::getInstance()->localEquipProptyVector();
	}
	localSkillAddPropty = DataManager::getInstance()->localSkillAddProptyVec();
	if (localSkillAddPropty.size() == 0)
	{
		DataManager::getInstance()->skillUpgradeProptyAdd();
		localSkillAddPropty = DataManager::getInstance()->localSkillAddProptyVec();
	}

	mpFontChina = FontChina::getInstance();
	mpFontChina->initStringXml();

	auto generalUI = GUIReader::getInstance()->widgetFromJsonFile("GeneralDetails.ExportJson");
	generalUI->setTag(99);
	this->addChild(generalUI, -2);

	panelLeft = dynamic_cast<Layout* >(Helper::seekWidgetByName(generalUI, "G_Panel_Left"));			// 左侧初始界面
	panelLeft->setLocalZOrder( 5 );

	panelDetial = dynamic_cast<Layout* >(Helper::seekWidgetByName(generalUI, "Panel_Detial"));			// 左侧详情
	panelEvo = dynamic_cast<Layout* >(Helper::seekWidgetByName(generalUI, "G_GeneralStar"));			// 突破（进化）
	panelTrain = dynamic_cast<Layout* >(Helper::seekWidgetByName(generalUI, "Panel_GT"));				// 培养
	panelRight = dynamic_cast<Layout* >(Helper::seekWidgetByName(generalUI, "G_Panel_Right"));			// 技能（基础层）
	panelDetial->setLocalZOrder( -1 );
	panelDetial->setVisible(false);
	panelEvo->setLocalZOrder( -1 );
	panelEvo->setVisible(false);
	panelTrain->setLocalZOrder(-1);
	panelTrain->setVisible(false);

	skillLayout = dynamic_cast<Layout* >(Helper::seekWidgetByName(panelRight, "Panel_Skill"));
	talentLayout = dynamic_cast<Layout* >(Helper::seekWidgetByName(panelRight, "Panel_Talent"));

	auto close = dynamic_cast<Button *>(Helper::seekWidgetByName(generalUI, "Button_Close"));
	close->addTouchEventListener(this, toucheventselector(GeneralDetails::closeButton));

	auto buttonSkill = dynamic_cast<Button *>(Helper::seekWidgetByName(panelRight, "Button_Skill"));
	buttonSkill->setTag(SKILLButton);
	buttonSkill->addTouchEventListener(this, toucheventselector(GeneralDetails::skillButton));

	auto buttonTalent = dynamic_cast<Button *>(Helper::seekWidgetByName(panelRight, "Button_Talent"));
	buttonTalent->setTag(DETIALButton);
	buttonTalent->addTouchEventListener(this, toucheventselector(GeneralDetails::talentButton));

	auto buttonEvo = dynamic_cast<Button *>(Helper::seekWidgetByName(generalUI, "Button_Revo"));
	buttonEvo->setTag( 6 );
	buttonEvo->addTouchEventListener(this, toucheventselector(GeneralDetails::evolutionButton));

	auto buttonTrain = dynamic_cast<Button *>(Helper::seekWidgetByName(generalUI, "Button_Train"));
	buttonTrain->setTag( 5 );
	buttonTrain->addTouchEventListener(this, toucheventselector(GeneralDetails::trainButton));

	auto skillBasicTrainClick = dynamic_cast<Button *>(Helper::seekWidgetByName(generalUI, "Button_Skill"));
	skillBasicTrainClick->setTag( 4 );
	skillBasicTrainClick->addTouchEventListener(this, toucheventselector(GeneralDetails::skillBasicButton));

	auto detailClick = dynamic_cast<Button *>(Helper::seekWidgetByName(panelLeft, "Button_Detial"));
	detailClick->addTouchEventListener(this, toucheventselector(GeneralDetails::detailButton));
	
	if (false == NewComer::isGuideDone(1000))						/* 引导ID为0，且未完成 */
	{
		_comer = NewComer::create(this, 1000, 3);
	}
	else if (false == NewComer::isGuideDone(1005))					/* 引导ID为5，且未完成 */
	{
		_comer = NewComer::create(this, 1005, 2);
	}
	else if (false == NewComer::isGuideDone(1009))					/* 引导ID为9，且未完成 */
	{
		_comer = NewComer::create(this, 1009, 2);
	}
	else if (false == NewComer::isGuideDone(1010))					/* 引导ID为10，且未完成 */
	{
		_comer = NewComer::create(this, 1010, 2);
	}
	else
	{
		_comer = NULL;
	}

	return true;
}

void GeneralDetails::initHeroData()
{
	maidanVector = DataManager::getInstance()->reGeneralVector;
	if (DataManager::getInstance()->isGetGeneralProperty(maidanVector[ 0 ].PKID))
	{
		localGeneralVector = DataManager::getInstance()->localGeneralProptyVector();
		interGeneralVector = DataManager::getInstance()->interGeneralVector();
		curGeneralVector.clear();
		GeneralProptyStruct generalStruct;
		memset(&generalStruct, 0, sizeof(generalStruct));
		generalStruct.PKID = maidanVector[ 0 ].PKID;
		generalStruct.roleID = maidanVector[ 0 ].roleID;
		string strName = localGeneralVector[ maidanVector[ 0 ].roleID - 10001 ].chinaName;					// 中文名称
		memset(generalStruct.chinaName, 0, sizeof(generalStruct.chinaName));
		memcpy(generalStruct.chinaName, strName.c_str(), strName.length());
		string strSmallName = localGeneralVector[ maidanVector[ 0 ].roleID - 10001 ].chinaSmallName;			// 拼音
		memset(generalStruct.chinaSmallName, 0, sizeof(generalStruct.chinaSmallName));
		memcpy(generalStruct.chinaSmallName, strSmallName.c_str(), strSmallName.length());
		generalStruct.jobType = maidanVector[ 0 ].jobType;											// 职业类型
		generalStruct.evoLevel = maidanVector[ 0 ].evoLevel;											// 进阶等级
		generalStruct.strongExp = interGeneralVector[ 0 ].strExp;										// 强化经验
		generalStruct.evoExp = interGeneralVector[ 0 ].evoExp;										// 进化经验
		generalStruct.evoLevel = interGeneralVector[ 0 ].evoLevel;										// 进化等级
		generalStruct.level = interGeneralVector[ 0 ].level;											// 等级
		generalStruct.curStarLevel = interGeneralVector[ 0 ].starLevel;									// 当前星级
		int curRoleID = maidanVector[ 0 ].roleID + (interGeneralVector[ 0 ].starLevel + ( maidanVector[ 0 ].evoLevel - 1 )) - StarID;
		generalStruct.maxStar = localGeneralVector[ curRoleID ].maxStar;
		generalStruct.atkGrowing = localGeneralVector[ curRoleID ].atkGrowing;
		generalStruct.hpGrowing = localGeneralVector[ curRoleID ].hpGrowing;
		generalStruct.pdGrowing = localGeneralVector[ curRoleID ].pdGrowing;
		generalStruct.mdGrowing = localGeneralVector[ curRoleID ].mdGrowing;
		generalStruct.initAtk = localGeneralVector[ curRoleID ].initAtk;
		generalStruct.initHP = localGeneralVector[ curRoleID ].initHP;
		generalStruct.initPD = localGeneralVector[ curRoleID ].initPD;
		generalStruct.initMD = localGeneralVector[ curRoleID ].initMD;
		generalStruct.riseHP = localGeneralVector[ curRoleID ].riseHP;
		for (int i = 0; i < EquipCount; i ++)
		{
			generalStruct.equipPropty[ i ].ePKID = interGeneralVector[ 0 ].equipPKID[ i ];
			generalStruct.equipPropty[ i ].eID = interGeneralVector[ 0 ].equipID[ i ];
			generalStruct.equipPropty[ i ].eLevel = interGeneralVector[ 0 ].equipLevel[ i ];
		}
		for (int i = 0; i < 4; i ++)
		{
			generalStruct.skillLevel[ i ] = interGeneralVector[ 0 ].skillLevel[ i ];
		}
		string desString = localGeneralVector[ maidanVector[ 0 ].roleID - StarID ].g_des;
		memset(&generalStruct.g_des, 0, sizeof(generalStruct.g_des));
		memcpy(generalStruct.g_des, desString.c_str(), desString.length());
		curGeneralVector.push_back(generalStruct);

		setHeroSkillLevel();
		initHeroAnimation(maidanVector[ 0 ].chinaSmallName);
		initHeroSkill(curGeneralVector[ 0 ].maxStar, maidanVector[ 0 ].roleID);
		initEquipData();
		showLabel();
	}	
	lcoalTalentVector = DataManager::getInstance()->localtalentVector();
	if (lcoalTalentVector.size() == 0)
	{
		DataManager::getInstance()->talentDataParser();
		lcoalTalentVector = DataManager::getInstance()->localtalentVector();
	}
	meetTalentVector.clear();
	for (unsigned int i = 0; i < lcoalTalentVector.size(); i ++)								// 查找符合的天赋
	{
		if (maidanVector[ 0 ].jobType == lcoalTalentVector[ i ].type)
		{
			if (lcoalTalentVector[ i ].special == curGeneralVector[ 0 ].roleID)				// 五星武将
			{
				meetTalentVector.push_back(lcoalTalentVector[ i ]);
			}
			else if (lcoalTalentVector[ i ].special == 0)
			{
				meetTalentVector.push_back(lcoalTalentVector[ i ]);
			}
		}
	}
	if ( DataManager::getInstance()->isGetPlayerInfo() )
	{
		interPlayerInfoVector = DataManager::getInstance()->interPlayerInfoVector();
	}
}

void GeneralDetails::initHeroAnimation(string nameString)
{
	panelLeft->removeChildByTag(RoleLayerFlag);

	heroRole = RoleCreate::create(nameString.c_str(), RoleCreMode_Preview, 1.0f);
	auto layer = Layer::create();
	layer->setPosition( Point( 140, 170 ) );
	layer->setTag(RoleLayerFlag);
	layer->addChild(heroRole);
	panelLeft->addChild(layer, 4);
}

void GeneralDetails::initEquipData()
{
	for (int i = 0; i < 3; i++)
	{
		for (int i = 0; i < EquipCount ; i ++)
		{
			auto equipString = __String::createWithFormat("G_Equip%d_BG_0", i + 1); 
			auto equipImage = dynamic_cast<ImageView* >(Helper::seekWidgetByName(panelLeft, equipString->getCString()));
			equipImage->setTag( i + 1 );
			equipImage->loadTexture("GeneralDetails/G_Equipe.png", TextureResType::UI_TEX_TYPE_PLIST);
			equipImage->setScale(1.0f);
			equipImage->addTouchEventListener(this, toucheventselector(GeneralDetails::equipCallBack));
			if (interGeneralVector[ 0 ].equipID[ i ] != 0)
			{			
				auto equipNameString = __String::createWithFormat("%d.png", interGeneralVector[ 0 ].equipID[ i ]);
				equipImage->loadTexture(equipNameString->getCString(), TextureResType::UI_TEX_TYPE_PLIST);	
				equipImage->setScale(0.5f);
			}		
		}
	}
	
	auto nameLabel = dynamic_cast<Text* >(Helper::seekWidgetByName(panelLeft, "Label_Name"));								// 武将名称
	nameLabel->setText(maidanVector[ 0 ].chinaName);

	auto starPanel = dynamic_cast<Layout* >(Helper::seekWidgetByName(panelLeft, "GS_Star_0"));

	ImageView* starImage[ 5 ];
	ImageView* darkImage[ 5 ];
	for (int i = 0; i < 5; i++)
	{
		auto starString = __String::createWithFormat("GS_Star_%d", i + 1);
		auto darkString = __String::createWithFormat("GS_DarkStar_%d", i + 1);

		starImage[ i ] = dynamic_cast<ImageView* >(Helper::seekWidgetByName(starPanel, starString->getCString()));
		darkImage[ i ] = dynamic_cast<ImageView* >(Helper::seekWidgetByName(starPanel, darkString->getCString()));
		starImage[ i ]->setVisible(false);
		darkImage[ i ]->setVisible(false);
	}

	for (int i = 0; i < curGeneralVector[ 0 ].curStarLevel; i++)
	{
		starImage[ i ]->setVisible(true);
	}
	for (int i = 0; i < curGeneralVector[ 0 ].maxStar; i ++)
	{
		darkImage[ i ]->setVisible(true);
	}

	auto atkLabel = dynamic_cast<TextAtlas* >(Helper::seekWidgetByName(panelLeft, "AtlasLabel_ATKNum"));						// 战斗力
	float atkHP = curGeneralVector[ 0 ].initHP + curGeneralVector[ 0 ].hpGrowing * (interGeneralVector[ 0 ].level - 1);
	float atkAtk = curGeneralVector[ 0 ].initAtk + curGeneralVector[ 0 ].atkGrowing * (interGeneralVector[ 0 ].level - 1);
	float atkPD = curGeneralVector[ 0 ].initPD + curGeneralVector[ 0 ].pdGrowing * (interGeneralVector[ 0 ].level - 1);
	float atkMD = curGeneralVector[ 0 ].initMD + curGeneralVector[ 0 ].mdGrowing * (interGeneralVector[ 0 ].level - 1);
	int i_Equip[] = { 0, 1, 2, 3 };
	int i_Color[] = { 1, 2, 3, 4 };
	float f_Rate[] = { 0.1f, 0.2f, 0.2f, 0.3f };
	float f_FRate[] = { 0.008f, 0.01f, 0.01f, 0.01f };
	
	for (int i = 0; i < 4; i ++)
	{
		float incNum = 0.0f;
		int i_BasicValues = 0;
		if ( interGeneralVector[ 0 ].equipID[ i ] != 0 )
		{
			for (int k = 0; k < 4; k++)
			{
				if ( ( localEquipVector[ interGeneralVector[ 0 ].equipID[ i ] - 94001 ].eColor == i_Color[ k ] ) && (interGeneralVector[ 0 ].equipLevel[ i ] != 0) )
				{
					incNum += f_Rate[ k ] + ( interGeneralVector[ 0 ].equipLevel[ i ] - 1 ) * f_FRate[ k ];
				}
			}
			
			switch ( i )
			{
			case 0:
				i_BasicValues = localEquipVector[ interGeneralVector[ 0 ].equipID[ 0 ] - 94001 ].eHP;
				atkHP += i_BasicValues * ( 1 + incNum );
				break;
			case 1:
				i_BasicValues = localEquipVector[ interGeneralVector[ 0 ].equipID[ 1 ] - 94001 ].ePD;
				atkPD += i_BasicValues * ( 1 + incNum );
				break;
			case 2:
				i_BasicValues = localEquipVector[ interGeneralVector[ 0 ].equipID[ 2 ] - 94001 ].eMD;
				atkMD += i_BasicValues * ( 1 + incNum );
				break;
			case 3:
				i_BasicValues = localEquipVector[ interGeneralVector[ 0 ].equipID[ 3 ] - 94001 ].eAtk;
				atkAtk += i_BasicValues * ( 1 + incNum );
				break;
			}
		}
	}

	if (curGeneralVector[ 0 ].skillLevel[ 0 ] != 0)
	{
		if (curGeneralVector[ 0 ].maxStar == 5)
		{
			atkPD += localSkillAddPropty[ 0 ].ePD + curGeneralVector[ 0 ].skillLevel[ 0 ] * localSkillAddPropty[ 0 ].ePDLen;
		}
		else if (curGeneralVector[ 0 ].maxStar == 4)
		{
			atkPD += localSkillAddPropty[ 0 ].dPD + curGeneralVector[ 0 ].skillLevel[ 0 ] * localSkillAddPropty[ 0 ].dPDLen;
		}
		else if (curGeneralVector[ 0 ].maxStar == 3)
		{
			atkPD += localSkillAddPropty[ 0 ].cPD + curGeneralVector[ 0 ].skillLevel[ 0 ] * localSkillAddPropty[ 0 ].cPDLen;
		}
	}
	if (curGeneralVector[ 0 ].skillLevel[ 1 ] != 0)
	{
		if (curGeneralVector[ 0 ].maxStar == 5)
		{
			atkMD += localSkillAddPropty[ 0 ].eMD + curGeneralVector[ 0 ].skillLevel[ 1 ] * localSkillAddPropty[ 0 ].eMDLen;
		}
		else if (curGeneralVector[ 0 ].maxStar == 4)
		{
			atkMD += localSkillAddPropty[ 0 ].dMD + curGeneralVector[ 0 ].skillLevel[ 1 ] * localSkillAddPropty[ 0 ].dMDLen;
		}
		else if (curGeneralVector[ 0 ].maxStar == 3)
		{
			atkMD += localSkillAddPropty[ 0 ].cMD + curGeneralVector[ 0 ].skillLevel[ 1 ] * localSkillAddPropty[ 0 ].cMDLen;
		}
	}
	if (curGeneralVector[ 0 ].skillLevel[ 2 ] != 0)
	{
		if (curGeneralVector[ 0 ].maxStar == 5)
		{
			atkHP += localSkillAddPropty[ 0 ].eHP + curGeneralVector[ 0 ].skillLevel[ 2 ] * localSkillAddPropty[ 0 ].eHPLen;
		}
		else if (curGeneralVector[ 0 ].maxStar == 4)
		{
			atkHP += localSkillAddPropty[ 0 ].dHP + curGeneralVector[ 0 ].skillLevel[ 2 ] * localSkillAddPropty[ 0 ].dHPLen;
		}
	}
	if (curGeneralVector[ 0 ].skillLevel[ 3 ] != 0)
	{
		if (curGeneralVector[ 0 ].maxStar == 5)
		{
			atkAtk += localSkillAddPropty[ 0 ].eATK + curGeneralVector[ 0 ].skillLevel[ 3 ] * localSkillAddPropty[ 0 ].eAtkLen;
		}
	}

	vector<int > growthVector;
	if ( DataManager::getInstance()->isGetGeneralGrowth( curGeneralVector[ 0 ].PKID ) )
	{
		growthVector = DataManager::getInstance()->getGeneralGrowthVector();
	}

	float atkValue = (atkHP + growthVector[ 1 ]) / 5 + atkAtk + growthVector[ 0 ] + ( atkMD + growthVector[ 3 ] + atkPD + growthVector[ 2 ] ) / 2;
	auto atkValueString = __String::createWithFormat("%.0f", atkValue);
	atkLabel->setStringValue(atkValueString->getCString());

	for (int i = 0; i < 3; i ++)																		// 职业类型
	{
		auto jogString = __String::createWithFormat("Image_Job_%d", i + 1);
		auto jobType = dynamic_cast<ImageView* >(Helper::seekWidgetByName(panelLeft, jogString->getCString()));
		jobType->setVisible(false);
		if (maidanVector[ 0 ].jobType == i + 1)
		{
			jobType->setVisible(true);
		}
	}

	int curExp = calcGeneralExp(curGeneralVector[ 0 ].level, curGeneralVector[ 0 ].strongExp);
	int maxExp = localGeneralUpgradeVector[ curGeneralVector[ 0 ].level - 1 ].gNeedExp;
	float expPercnet = curExp * 1.0f / maxExp * 100;
	auto expProgress = dynamic_cast<LoadingBar* >(Helper::seekWidgetByName(panelLeft, "G_ProgressBar_EXP"));						// 武将经验值
	expProgress->setPercent(expPercnet);	

	auto levelText = dynamic_cast<Text* >(Helper::seekWidgetByName(panelLeft, "Label_Level"));									// 等级	
	auto levelString = __String::createWithFormat("Lv.%d", curGeneralVector[ 0 ].level);
	levelText->setText(levelString->getCString());

}

void GeneralDetails::initHeroSkill(int heroStarLevel, int heroID)
{
	for (unsigned int i = 0; i < localSkillNameVector.size(); i ++)
	{
		if (localSkillNameVector[ i ].RoleID == heroID)
		{
			localTempSkillNameVector.clear();
			localTempSkillNameVector.push_back(localSkillNameVector[ i ]);
		}
	}
	Layout* skillPanel[ 4 ];
	__String* imagePhotoString ;					// 图片
	__String* nameString;							// 名称
	__String* levelString;							// 等级
	__String* coinString;							// 金币数量
	for (int i = 0; i < heroStarLevel - 1; i ++)
	{
		auto skillPanelString = __String::createWithFormat("Panel_Skill%d", i + 1);
		skillPanel[ i ] = dynamic_cast<Layout* >(Helper::seekWidgetByName(panelRight, skillPanelString->getCString()));				// 技能层
		skillPanel[ i ]->setTag( i );
		skillPanel[ i ]->addTouchEventListener(this, toucheventselector(GeneralDetails::skillPanelButton));

		auto imagePhoto = dynamic_cast<ImageView* >(Helper::seekWidgetByName(skillPanel[ i ], "Skill1_1"));						// 技能图片
		imagePhoto->setTag( i + 1);
		imagePhoto->setTouchEnabled(true);
		imagePhoto->addTouchEventListener(this, toucheventselector(GeneralDetails::skillPhotoCallBack));
		
		auto upgradeClick = dynamic_cast<Button* >(Helper::seekWidgetByName(skillPanel[ i ], "Button_SkillUp"));					// 升级按钮
		upgradeClick->setTag( i + 1 );
		if ( (curGeneralVector[ 0 ].skillLevel[ i ] != 0 ) && (curGeneralVector[ 0 ].skillLevel[ i ] <= curGeneralVector[ 0 ].level) )
		{
			upgradeClick->addTouchEventListener(this, toucheventselector(GeneralDetails::SkillUpgradeCallBack));
		}
		auto skillName = dynamic_cast<Text* >(Helper::seekWidgetByName(skillPanel[ i ], "Label_SkillName"));						// 技能名称
		auto levelLabel = dynamic_cast<Text* >(Helper::seekWidgetByName(skillPanel[ i ], "Label_SkillLevel"));						// 等级
		auto liftCoin = dynamic_cast<Text* >(Helper::seekWidgetByName(skillPanel[ i ], "Label_SkillValue"));						// 技能升级消耗金币
		auto graySprite = dynamic_cast<ImageView* >(Helper::seekWidgetByName(skillPanel[ i ], "Image_GDBlackBG"));				// 设置遮罩图片
		if (curGeneralVector[ 0 ].skillLevel[ i ] > 0)
		{
			graySprite->setVisible(false);
		}
		if ( i == 0 )
		{
			imagePhotoString = __String::createWithFormat("%s.png", localTempSkillNameVector[ 0 ].sANameS);
			nameString = __String::createWithFormat("%s", localTempSkillNameVector[ 0 ].sAName);
			levelString = __String::createWithFormat("lv.%d", curGeneralVector[ 0 ].skillLevel[ 0 ]);
			coinString = __String::createWithFormat("%d", localSkillUpgradeVector[ curGeneralVector[ 0 ].skillLevel[ 0 ] ].skillExpandCoin);		
		} 
		else if (i == 1)
		{
			imagePhotoString = __String::createWithFormat("%s.png", localTempSkillNameVector[ 0 ].sBNameS);
			nameString = __String::createWithFormat("%s", localTempSkillNameVector[ 0 ].sBName);
			levelString = __String::createWithFormat("lv.%d", curGeneralVector[ 0 ].skillLevel[ 1 ]);
			coinString = __String::createWithFormat("%d", localSkillUpgradeVector[ curGeneralVector[ 0 ].skillLevel[ 1 ] ].skillExpandCoin);	
		}
		else if (i == 2)
		{
			imagePhotoString = __String::createWithFormat("%s.png", localTempSkillNameVector[ 0 ].sCNameS);
			nameString = __String::createWithFormat("%s", localTempSkillNameVector[ 0 ].sCName);
			levelString = __String::createWithFormat("lv.%d", curGeneralVector[ 0 ].skillLevel[ 2 ]);
			coinString = __String::createWithFormat("%d", localSkillUpgradeVector[ curGeneralVector[ 0 ].skillLevel[ 2 ] ].skillExpandCoin);	
		}
		else if(i == 3)
		{
			imagePhotoString = __String::createWithFormat("%s.png", localTempSkillNameVector[ 0 ].sDNameS);
			nameString = __String::createWithFormat("%s", localTempSkillNameVector[ 0 ].sDName);
			levelString = __String::createWithFormat("lv.%d", curGeneralVector[ 0 ].skillLevel[ 3 ]);
			coinString = __String::createWithFormat("%d", localSkillUpgradeVector[ curGeneralVector[ 0 ].skillLevel[ 3 ] ].skillExpandCoin);	
		}
		imagePhoto->loadTexture(imagePhotoString->getCString(), TextureResType::UI_TEX_TYPE_PLIST);
		imagePhoto->setScale(0.65f);		
		skillName->setText(nameString->getCString());
		levelLabel->setText(levelString->getCString());
		liftCoin->setText(coinString->getCString());
	}
}

void GeneralDetails::showLabel()
{		
	auto detialScrollView = dynamic_cast<cocos2d::ui::ScrollView* >(Helper::seekWidgetByName(panelDetial, "ScrollView_Detial"));		

	auto backClick = dynamic_cast<Button* >(Helper::seekWidgetByName(panelDetial, "Button_Return"));
	backClick->addTouchEventListener(this, toucheventselector(GeneralDetails::backButton));
	
	__String* basicString ;
	auto atkGText = dynamic_cast<Text* >(Helper::seekWidgetByName(detialScrollView, "Label_ATK__Value"));							// 攻击力
	auto hpText = dynamic_cast<Text* >(Helper::seekWidgetByName(detialScrollView, "Label_HP__Value"));								// 血量
	auto pdText = dynamic_cast<Text* >(Helper::seekWidgetByName(detialScrollView, "Label_PD_Value"));								// 物理防御
	auto mdText = dynamic_cast<Text* >(Helper::seekWidgetByName(detialScrollView, "Label_MD_Value"));								// 法术防御
	
	int equipIndex[] = { 0, 1, 2, 3 }; 
	//int equipColor[] = { 1, 2, 3, 4 };
	float equipBasic[] = { 0.005f, 0.005f, 0.006f, 0.007f };
	float equipInc[] = { 0.003f, 0.004f, 0.006f, 0.008f };
	int basicEValue, basicHValue = 0;
	for (int i = 0; i < 4; i ++)
	{		
		float incValue = 0.0f;
		if ( interGeneralVector[ 0 ].equipID[ i ] != 0 )
		{		
			switch ( i )
			{
			case 0:
				basicEValue = localEquipVector[ interGeneralVector[ 0 ].equipID[ 0 ] - 94001 ].eHP;
				break;
			case 1:
				basicEValue = localEquipVector[ interGeneralVector[ 0 ].equipID[ 1 ] - 94001 ].ePD;
				break;
			case 2:
				basicEValue = localEquipVector[ interGeneralVector[ 0 ].equipID[ 2 ] - 94001 ].eMD;
				break;
			case 3:
				basicEValue = localEquipVector[ interGeneralVector[ 0 ].equipID[ 3 ] - 94001 ].eAtk;
				break;
			}
			for (int k = 0; k < 4; k++)
			{
				if ( localEquipVector[ interGeneralVector[ 0 ].equipID[ i ] - 94001 ].eColor == k + 1 )
				{
					incValue = basicEValue + ( equipBasic[ k ] + ( interGeneralVector[ 0 ].equipLevel[ 0 ] - 1 ) * equipInc[ k ]  );
				}
			}
						
		}		
		if ( i == 0 )
		{
			basicHValue = curGeneralVector[ 0 ].initHP + curGeneralVector[ 0 ].hpGrowing * (curGeneralVector[ 0 ].level - 1);
			basicString = __String::createWithFormat("%.0f", incValue + basicHValue);
			hpText->setText(basicString->getCString());
		}
		else if ( i == 1 )
		{
			basicHValue = curGeneralVector[ 0 ].initPD + curGeneralVector[ 0 ].pdGrowing * (curGeneralVector[ 0 ].level - 1);
			basicString = __String::createWithFormat("%.0f", incValue + basicHValue);
			pdText->setText(basicString->getCString());
		}
		else if ( i == 2 )
		{
			basicHValue = curGeneralVector[ 0 ].initMD + curGeneralVector[ 0 ].mdGrowing * (curGeneralVector[ 0 ].level - 1);
			basicString = __String::createWithFormat("%.0f", incValue + basicHValue);
			mdText->setText(basicString->getCString());
		}
		else if ( i == 3 )
		{
			basicHValue = curGeneralVector[ 0 ].initAtk + curGeneralVector[ 0 ].atkGrowing * (curGeneralVector[ 0 ].level - 1);
			basicString = __String::createWithFormat("%.0f", incValue + basicHValue);
			atkGText->setText(basicString->getCString());
		}
	}
	auto riseHPText = dynamic_cast<Text* >(Helper::seekWidgetByName(detialScrollView, "Label_RiseHP_Value"));						// 回血速率
	auto riseHPstring = __String::createWithFormat("%1.3f", curGeneralVector[ 0 ].riseHP );
	riseHPText->setText(riseHPstring->getCString());
	auto critText = dynamic_cast<Text* >(Helper::seekWidgetByName(detialScrollView, "Label_AddCrit_Value"));							// 物理暴击几率
	auto kCritText = dynamic_cast<Text* >(Helper::seekWidgetByName(detialScrollView, "Label_ReduceCrit_Value"));						// 抗暴击几率
	__String* critString ;
	__String* kCritString;	
	if (interGeneralVector[ 0 ].equipID[ 4 ] != 0)
	{
		float basicCrit = localEquipVector[ interGeneralVector[ 0 ].equipID[ 4 ] - 94001 ].eAddCrit;
		if (interGeneralVector[ 0 ].equipLevel[ 4 ] == 0)
		{
			critString = __String::createWithFormat("%.3f", basicCrit);
		}
		else
		{			
			float incCrite = 0.0f;
			if (localEquipVector[ interGeneralVector[ 0 ].equipID[ 4 ] - 94001 ].eColor == 1 )										// 白色
			{
				incCrite = basicCrit + ( 0.005 + (interGeneralVector[ 0 ].equipLevel[ 4 ] - 1 ) * 0.003 );
			}
			else if (localEquipVector[ interGeneralVector[ 0 ].equipID[ 4 ] - 94001 ].eColor == 2)
			{
				incCrite = basicCrit + ( 0.005 + (interGeneralVector[ 0 ].equipLevel[ 4 ] - 1 ) * 0.004 );
			}
			else if (localEquipVector[ interGeneralVector[ 0 ].equipID[ 4 ] - 94001 ].eColor == 3)
			{
				incCrite = basicCrit + ( 0.006 + (interGeneralVector[ 0 ].equipLevel[ 4 ] - 1 ) * 0.006 );
			}
			else if (localEquipVector[ interGeneralVector[ 0 ].equipID[ 4 ] - 94001 ].eColor == 4)
			{
				incCrite = basicCrit + ( 0.007 + (interGeneralVector[ 0 ].equipLevel[ 4 ] - 1 ) * 0.008 );
			}
			critString = __String::createWithFormat("%.3f", incCrite);
		}		
	}
	else
	{
		critString = __String::createWithFormat("%d", 0);
	}
	if (interGeneralVector[ 0 ].equipID[ 4 ] != 0)
	{
		float basicCrit = localEquipVector[ interGeneralVector[ 0 ].equipID[ 4 ] - 94001 ].eReduceCrit;
		if (interGeneralVector[ 0 ].equipLevel[ 0 ] == 0)
		{
			kCritString = __String::createWithFormat("%.3f", basicCrit);
		}
		else
		{			
			float incCrite = 0.0f;
			if (localEquipVector[ interGeneralVector[ 0 ].equipID[ 4 ] - 94001 ].eColor == 1 )										// 白色
			{
				incCrite = basicCrit + ( 0.005 + (interGeneralVector[ 0 ].equipLevel[ 4 ] - 1 ) * 0.003 );
			}
			else if (localEquipVector[ interGeneralVector[ 0 ].equipID[ 4 ] - 94001 ].eColor == 2)
			{
				incCrite = basicCrit + ( 0.005 + (interGeneralVector[ 0 ].equipLevel[ 4 ] - 1 ) * 0.004 );
			}
			else if (localEquipVector[ interGeneralVector[ 0 ].equipID[ 4 ] - 94001 ].eColor == 3)
			{
				incCrite = basicCrit + ( 0.006 + (interGeneralVector[ 0 ].equipLevel[ 4 ] - 1 ) * 0.006 );
			}
			else if (localEquipVector[ interGeneralVector[ 0 ].equipID[ 4 ] - 94001 ].eColor == 4)
			{
				incCrite = basicCrit + ( 0.007 + (interGeneralVector[ 0 ].equipLevel[ 4 ] - 1 ) * 0.008 );
			}
			kCritString = __String::createWithFormat("%.3f", incCrite);
		}		
	}
	else
	{
		kCritString = __String::createWithFormat("%d", 0);
	}
	critText->setText(critString->getCString());
	kCritText->setText(kCritString->getCString());
	auto addRealText = dynamic_cast<Text* >(Helper::seekWidgetByName(detialScrollView, "Label_RealHurt_Value"));						// 真是伤害
	auto reRealText = dynamic_cast<Text* >(Helper::seekWidgetByName(detialScrollView, "Label_ReduceHurt_Value"));					// 减伤
	__String* addString;
	__String* reString;
	if (interGeneralVector[ 0 ].equipID[ 5 ] != 0)
	{
		float basicCrit = localEquipVector[ interGeneralVector[ 0 ].equipID[ 5 ] - 94001 ].eAddRealHurt;
		if (interGeneralVector[ 0 ].equipLevel[ 0 ] == 0)
		{
			addString = __String::createWithFormat("%.3f", basicCrit);
		}
		else
		{			
			float incCrite = 0.0f;
			if (localEquipVector[ interGeneralVector[ 0 ].equipID[ 5 ] - 94001 ].eColor == 1 )										// 白色
			{
				incCrite = basicCrit + ( 0.001 + (interGeneralVector[ 0 ].equipLevel[ 5 ] - 1 ) * 0.008 );
			}
			else if (localEquipVector[ interGeneralVector[ 0 ].equipID[ 5 ] - 94001 ].eColor == 2)
			{
				incCrite = basicCrit + ( 0.001 + (interGeneralVector[ 0 ].equipLevel[ 5 ] - 1 ) * 0.01 );
			}
			else if (localEquipVector[ interGeneralVector[ 0 ].equipID[ 5 ] - 94001 ].eColor == 3)
			{
				incCrite = basicCrit + ( 0.001 + (interGeneralVector[ 0 ].equipLevel[ 5 ] - 1 ) * 0.012 );
			}
			else if (localEquipVector[ interGeneralVector[ 0 ].equipID[ 5 ] - 94001 ].eColor == 4)
			{
				incCrite = basicCrit + ( 0.002 + (interGeneralVector[ 0 ].equipLevel[ 5 ] - 1 ) * 0.015 );
			}
			addString = __String::createWithFormat("%.3f", incCrite);
		}		
	}
	else
	{
		addString = __String::createWithFormat("%d", 0);
	}
	if (interGeneralVector[ 0 ].equipID[ 5 ] != 0)
	{
		float basicCrit = localEquipVector[ interGeneralVector[ 0 ].equipID[ 5 ] - 94001 ].eAddRealHurt;
		if (interGeneralVector[ 0 ].equipLevel[ 0 ] == 0)
		{
			reString = __String::createWithFormat("%.3f", basicCrit);
		}
		else
		{			
			float incCrite;
			if (localEquipVector[ interGeneralVector[ 0 ].equipID[ 5 ] - 94001 ].eColor == 1 )										// 白色
			{
				incCrite = basicCrit + ( 0.001 + (interGeneralVector[ 0 ].equipLevel[ 5 ] - 1 ) * 0.008 );
			}
			else if (localEquipVector[ interGeneralVector[ 0 ].equipID[ 5 ] - 94001 ].eColor == 2)
			{
				incCrite = basicCrit + ( 0.001 + (interGeneralVector[ 0 ].equipLevel[ 5 ] - 1 ) * 0.01 );
			}
			else if (localEquipVector[ interGeneralVector[ 0 ].equipID[ 5 ] - 94001 ].eColor == 3)
			{
				incCrite = basicCrit + ( 0.001 + (interGeneralVector[ 0 ].equipLevel[ 5 ] - 1 ) * 0.012 );
			}
			else if (localEquipVector[ interGeneralVector[ 0 ].equipID[ 5 ] - 94001 ].eColor == 4)
			{
				incCrite = basicCrit + ( 0.002 + (interGeneralVector[ 0 ].equipLevel[ 5 ] - 1 ) * 0.015 );
			}
			reString = __String::createWithFormat("%.3f", incCrite);
		}		
	}
	else
	{
		reString = __String::createWithFormat("%d", 0);
	}
	addRealText->setText(addString->getCString());
	reRealText->setText(reString->getCString());
	
	auto desText = dynamic_cast<Text* >(Helper::seekWidgetByName(detialScrollView, "Label_General_Des_String"));
	desText->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
	auto desString = __String::createWithFormat("%s", curGeneralVector[ 0 ].g_des);
	desText->ignoreContentAdaptWithSize(false); 
	desText->setSize(Size(220, 100)); 
	desText->setTextHorizontalAlignment(TextHAlignment::LEFT);	
	desText->setText(desString->getCString());
	detialScrollView->setInnerContainerSize(Size(detialScrollView->getInnerContainerSize().width, 
		detialScrollView->getInnerContainerSize().height + desText->getSize().height));
	for (int i = 0; i < detialScrollView->getChildrenCount(); i ++)
	{
		detialScrollView->getChildren().at(i)->setPositionY(detialScrollView->getChildren().at(i)->getPositionY() + desText->getSize().height);
	}
}

void GeneralDetails::setButtonBright(PanelButton panelButton)
{
	for (int i = 0; i < EVOButton; i ++)
	{
		auto button = (Button*)(panelRight->getChildByTag( i ));
		button->setBrightStyle(BrightStyle::BRIGHT_NORMAL);
		if (panelButton == i)
		{
			button->setBrightStyle(BrightStyle::BRIGHT_HIGHLIGHT);
		}
	}
}

void GeneralDetails::setBright(int btnID)
{
	auto layer = (Layout*)(this->getChildByTag( 99 ));
	for (int i = 4; i < 7; i ++)
	{
		auto button = (Button*)(layer->getChildByTag( i ));
		button->setBrightStyle(BrightStyle::BRIGHT_NORMAL);
		if (btnID == i)
		{
			button->setBrightStyle(BrightStyle::BRIGHT_HIGHLIGHT);
		}
	}
}

void GeneralDetails::SkillUpgradeCallBack(Ref* pSender, TouchEventType type)
{	
	if (type == TOUCH_EVENT_ENDED)
	{
		ToolFunc::playEffectFile( Click );
		auto button = (Button*)pSender;
		int tag = button->getTag();

		if (false == NewComer::isGuideDone(1005))					/* 引导ID为5，且未完成 */
		{
			if (1 != tag)
			{
				return;
			}

			if (2 == NewComer::getCurGuideStep())
			{
				auto cpID = NewComer::getCurGuideID();
				cpID = cpID | 0x010000;								/* 完成ID为0的引导 */
				NewComer::setCurGuideID(cpID);
				NewComer::setCurGuideStep(0);						/* 步骤ID重置 */
				_comer->removeFromParentAndCleanup(true);
				_comer = NULL;
			}
		}

		if (curGeneralVector[ 0 ].skillLevel[ tag - 1 ] == curGeneralVector[ 0 ].level)
		{
			// 弹出提示：技能等级不能高于武将等级
			auto promp = PromptBox::getInstance(mpFontChina->getComString("LevelLimit")->getCString());
			promp->setFade();
			this->addChild(promp, 10);
			return;
		}

		if (tag == 1)
		{
			if (interPlayerInfoVector[ 0 ].coinValue >= localSkillUpgradeVector[ curGeneralVector[ 0 ].skillLevel[ 0 ] ].skillExpandCoin)
			{
				DataManager::getInstance()->isSkillUpgrade(maidanVector[ 0 ].PKID, 
					curGeneralVector[ 0 ].skillLevel[ 0 ] + 1, curGeneralVector[ 0 ].skillLevel[ 1 ], 
					curGeneralVector[ 0 ].skillLevel[ 2 ], curGeneralVector[ 0 ].skillLevel[ 3 ],
					localSkillUpgradeVector[ curGeneralVector[ 0 ].skillLevel[ 0 ] ].skillExpandCoin);

				auto promp = PromptBox::getInstance(mpFontChina->getComString("SkillUpgrade")->getCString());
				promp->setFade();
				this->addChild(promp, 10);
			}
			else
			{
				// 弹出提示：金币数量不足
				auto pro = PromptBox::getInstance(mpFontChina->getComString("NoCoin")->getCString());
				pro->setFade();
				this->addChild(pro, 10);
			}
			
		}
		else if (tag == 2)
		{
			if (interPlayerInfoVector[ 0 ].coinValue >= localSkillUpgradeVector[ curGeneralVector[ 0 ].skillLevel[ 1 ] ].skillExpandCoin)
			{
				DataManager::getInstance()->isSkillUpgrade(maidanVector[ 0 ].PKID, 
					curGeneralVector[ 0 ].skillLevel[ 0 ], curGeneralVector[ 0 ].skillLevel[ 1 ] + 1, 
					curGeneralVector[ 0 ].skillLevel[ 2 ], curGeneralVector[ 0 ].skillLevel[ 3 ],
					localSkillUpgradeVector[ curGeneralVector[ 0 ].skillLevel[ 1 ] ].skillExpandCoin);

				auto promp = PromptBox::getInstance(mpFontChina->getComString("SkillUpgrade")->getCString());
				promp->setFade();
				this->addChild(promp, 10);
			}
			else
			{
				auto pro = PromptBox::getInstance(mpFontChina->getComString("NoCoin")->getCString());
				pro->setFade();
				this->addChild(pro, 10);
			}
			
		}
		else if (tag == 3)
		{
			if (interPlayerInfoVector[ 0 ].coinValue >= localSkillUpgradeVector[ curGeneralVector[ 0 ].skillLevel[ 2 ] ].skillExpandCoin)
			{
				DataManager::getInstance()->isSkillUpgrade(maidanVector[ 0 ].PKID, 
					curGeneralVector[ 0 ].skillLevel[ 0 ], curGeneralVector[ 0 ].skillLevel[ 1 ], 
					curGeneralVector[ 0 ].skillLevel[ 2 ] + 1, curGeneralVector[ 0 ].skillLevel[ 3 ],
					localSkillUpgradeVector[ curGeneralVector[ 0 ].skillLevel[ 2 ] ].skillExpandCoin);

				auto promp = PromptBox::getInstance(mpFontChina->getComString("SkillUpgrade")->getCString());
				promp->setFade();
				this->addChild(promp, 10);
			}
			else
			{
				auto pro = PromptBox::getInstance(mpFontChina->getComString("NoCoin")->getCString());
				pro->setFade();
				this->addChild(pro, 10);
			}
			
		}
		else if (tag == 4)
		{
			if (interPlayerInfoVector[ 0 ].coinValue >= localSkillUpgradeVector[ curGeneralVector[ 0 ].skillLevel[ 3 ] ].skillExpandCoin)
			{
				DataManager::getInstance()->isSkillUpgrade(maidanVector[ 0 ].PKID, 
					curGeneralVector[ 0 ].skillLevel[ 0 ], curGeneralVector[ 0 ].skillLevel[ 1 ], 
					curGeneralVector[ 0 ].skillLevel[ 2 ], curGeneralVector[ 0 ].skillLevel[ 3 ] + 1,
					localSkillUpgradeVector[ curGeneralVector[ 0 ].skillLevel[ 3 ]  ].skillExpandCoin);

				auto promp = PromptBox::getInstance(mpFontChina->getComString("SkillUpgrade")->getCString());
				promp->setFade();
				this->addChild(promp, 10);
			}
			else
			{
				auto pro = PromptBox::getInstance(mpFontChina->getComString("NoCoin")->getCString());
				pro->setFade();
				this->addChild(pro, 10);
			}			
		}
		interPlayerInfoVector = DataManager::getInstance()->interPlayerInfoVector();
		initHeroData();
		skillButton(NULL, TOUCH_EVENT_ENDED);
	}
}

void GeneralDetails::skillPhotoCallBack(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_BEGAN)
	{
		ToolFunc::playEffectFile( Click );
		auto button = (Button*)pSender;
		int tag = button->getTag();

		heroRole->runRoleAction(RoleActSign(tag + SkillStarEnum));
	}
}

void GeneralDetails::equipCallBack(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		ToolFunc::playEffectFile( Click );
		auto button = (ImageView*)pSender;
		DataManager::getInstance()->equipType = button->getTag();

		if ((4 == button->getTag()) && (false == NewComer::isGuideDone(1000)))/* 引导ID为0，且点击的是第一个武将，步骤自增 */
		{
			NewComer::setCurGuideStep();
			if (NULL != _comer)
			{
				_comer->removeFromParentAndCleanup(true);
				_comer = NULL;
			}
		}

		Director::getInstance()->pushScene(EquipmentInfo::create());	
	}
}

void GeneralDetails::closeButton(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		if (false == NewComer::isGuideDone(1000))					/* 引导ID为0，且未完成 */
		{
			if (5 != NewComer::getCurGuideStep())					/* 值为5，表示已经穿上装备 */
			{
				NewComer::setCurGuideStep(-1);
			}
		}
		else if (false == NewComer::isGuideDone(1005))				/* 引导ID为5，且未完成 */
		{
			if (0 != NewComer::getCurGuideStep())					/* 值为0，表示引导5结束 */
			{
				NewComer::setCurGuideStep(-1);
			}
		}
		else if ((false == NewComer::isGuideDone(1009)) ||			/* 引导ID为9，且未完成 */
			(false == NewComer::isGuideDone(1010)))					/* 引导ID为10，且未完成 */
		{
			if (0 != NewComer::getCurGuideStep())					/* 值为0，表示引导结束 */
			{
				NewComer::setCurGuideStep(0);
				NewComer::setCurGuideStep();
			}
		}
		else
		{
		}

		ToolFunc::playEffectFile( Click );
		Director::getInstance()->popScene();
	}
}

void GeneralDetails::skillButton(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		if ( pSender != NULL )
		{
			ToolFunc::playEffectFile( Click );
		}

		if (false == NewComer::isGuideDone(1005))					/* 引导ID为5，且未完成 */
		{
			if (NULL != _comer)
			{
				_comer->removeFromParentAndCleanup(true);
			}
			_comer = NewComer::create(this, 1005, 2);
		}
		if (false == NewComer::isGuideDone(1009))					/* 引导ID为9，且未完成 */
		{
			if (2 != NewComer::getCurGuideStep())
			{
				_comer->removeFromParentAndCleanup(true);
				NewComer::setCurGuideStep(0);
				NewComer::setCurGuideStep(2);
				_comer = NewComer::create(this, 1009, 2);
			}
		}
		if (false == NewComer::isGuideDone(1010))					/* 引导ID为10，且未完成 */
		{
			if (2 != NewComer::getCurGuideStep())
			{
				_comer->removeFromParentAndCleanup(true);
				NewComer::setCurGuideStep(0);
				NewComer::setCurGuideStep(2);
				_comer = NewComer::create(this, 1010, 2);
			}
		}
		
		skillLayout->setVisible(true);
		skillLayout->setTouchEnabled(true);
		skillLayout->setLocalZOrder( 2 );
		talentLayout->setLocalZOrder( 0 );
		talentLayout->setVisible(false);
		talentLayout->setTouchEnabled(false);
		setButtonBright(SKILLButton);
	}
}

void GeneralDetails::detailButton(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		ToolFunc::playEffectFile( Click );
		Director::getInstance()->setProjection(Director::Projection::_2D);
		if ( panelLeft->getAnchorPoint() != Point( 0.5, 0.5 ) )
		{
			panelLeft->setAnchorPoint( Point( 0.5, 0.5 ) );
			panelLeft->setPosition(Point( panelLeft->getPositionX() + panelLeft->getContentSize().width / 2, panelLeft->getPositionY() + panelLeft->getContentSize().height / 2 ));
		}		
		auto ss = OrbitCamera::create(0.2f, 1.0f, 0.1f, 1.0f, 90.0f, 0.1f, 0.1f);
		auto callA = CallFunc::create( CC_CALLBACK_0( GeneralDetails::filxCallBack, this ) );
		panelLeft->runAction( Sequence::createWithTwoActions(ss, callA) );
	}
}

void GeneralDetails::evolutionButton(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		ToolFunc::playEffectFile( Click );

		if (false == NewComer::isGuideDone(1005))					/* 引导ID为5，且未完成 */
		{
			if (NULL != _comer)
			{
				_comer->removeFromParentAndCleanup(true);
				_comer = NULL;
			}
		}

		if (false == NewComer::isGuideDone(1009))					/* 引导ID为9，且未完成 */
		{
			if (2 != NewComer::getCurGuideStep())
			{
				_comer->removeFromParentAndCleanup(true);
				NewComer::setCurGuideStep(0);
				NewComer::setCurGuideStep(2);
				_comer = NewComer::create(this, 1009, 2);
			}
		}

		if (false == NewComer::isGuideDone(1010))					/* 引导ID为10，且未完成 */
		{
			if (2 == NewComer::getCurGuideStep())
			{
				_comer->removeFromParentAndCleanup(true);
				NewComer::setCurGuideStep();
				_comer = NewComer::create(this, 1010, 3);
			}
		}

		setBright( 6 );
		panelEvo->setLocalZOrder( 5 );
		panelEvo->setVisible(true);

		panelRight->setLocalZOrder( -1 );
		panelRight->setVisible(false);
		panelTrain->setLocalZOrder( -1 );
		panelTrain->setVisible(false);

		evoInit();
	}
}

void GeneralDetails::trainButton(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		ToolFunc::playEffectFile( Click );

		if (false == NewComer::isGuideDone(1005))					/* 引导ID为5，且未完成 */
		{
			if (NULL != _comer)
			{
				_comer->removeFromParentAndCleanup(true);
				_comer = NULL;
			}
		}

		if (false == NewComer::isGuideDone(1009))					/* 引导ID为9，且未完成 */
		{
			if (2 == NewComer::getCurGuideStep())
			{
				_comer->removeFromParentAndCleanup(true);
				NewComer::setCurGuideStep();
				_comer = NewComer::create(this, 1009, 3);
			}
		}

		if (false == NewComer::isGuideDone(1010))					/* 引导ID为9，且未完成 */
		{
			if (2 != NewComer::getCurGuideStep())
			{
				_comer->removeFromParentAndCleanup(true);
				NewComer::setCurGuideStep(0);
				NewComer::setCurGuideStep(2);
				_comer = NewComer::create(this, 1010, 2);
			}
		}

		setBright( 5 );
		panelTrain->setLocalZOrder( 5 );
		panelTrain->setVisible(true);

		panelRight->setLocalZOrder( -1 );
		panelRight->setVisible(false);
		panelRight->setTouchEnabled(false);
		panelEvo->setLocalZOrder( -1 );
		panelEvo->setVisible(false);
		panelEvo->setTouchEnabled(false);

		vector<int > growthVector;
		if ( DataManager::getInstance()->isGetGeneralGrowth( curGeneralVector[ 0 ].PKID ) )
		{
			growthVector = DataManager::getInstance()->getGeneralGrowthVector();
		}

		auto trainDetial = dynamic_cast<Layout* >(panelTrain->getChildByName("GT_Panel_RightDetail"));
		auto atkLabel = dynamic_cast<Text* >( trainDetial->getChildByName("Label_ATKB") );
		auto atkString = __String::createWithFormat("%d+(%d)", curGeneralVector[ 0 ].initAtk, growthVector[ 0 ]);
		atkLabel->setText(atkString->getCString());
		auto atkLabelA = dynamic_cast<Text* >( trainDetial->getChildByName("Label_ATKA") );
		__String* atkStringA  = __String::createWithFormat("+%d", 0);
		atkLabelA->setText(atkStringA->getCString());

		auto hpLabel = dynamic_cast<Text* >( trainDetial->getChildByName("Label_HPB") );
		auto hpString = __String::createWithFormat("%d+(%d)", curGeneralVector[ 0 ].initHP, growthVector[ 1 ]);
		hpLabel->setText(hpString->getCString());
		auto hpLabelA = dynamic_cast<Text* >( trainDetial->getChildByName("Label_HPA") );
		__String* hpStringA  = __String::createWithFormat("+%d", 0);
		hpLabelA->setText(hpStringA->getCString());

		auto pdLabel = dynamic_cast<Text* >( trainDetial->getChildByName("Label_PDB") );
		auto pdString = __String::createWithFormat("%d+(%d)", curGeneralVector[ 0 ].initPD, growthVector[ 2 ]);
		pdLabel->setText(pdString->getCString());
		auto pdLabelA = dynamic_cast<Text* >( trainDetial->getChildByName("Label_PDA") );
		__String* pdStringA = __String::createWithFormat("+%d", 0);
		pdLabelA->setText(pdStringA->getCString());

		auto mdLabel = dynamic_cast<Text* >( trainDetial->getChildByName("Label_MDB") );
		auto mdString = __String::createWithFormat("%d+(%d)", curGeneralVector[ 0 ].initMD, growthVector[ 3 ]);
		mdLabel->setText(mdString->getCString());
		auto mdLabelA = dynamic_cast<Text* >( trainDetial->getChildByName("Label_MDA") );
		__String* mdStringA = __String::createWithFormat("+%d", 0);
		mdLabelA->setText(mdStringA->getCString());

		DataManager::getInstance()->isSortGoodsNum( 93019 );
		auto pillCount = DataManager::getInstance()->sortGoodsNum(); 
		auto pillString = __String::createWithFormat("%d", pillCount);
		auto pillLabelA = dynamic_cast<Text* >( trainDetial->getChildByName("Label_PeiyangdanNum") );
		pillLabelA->setText(pillString->getCString());

		auto pillClick = dynamic_cast<Button* >(Helper::seekWidgetByName(trainDetial, "Button_Train"));
		pillClick->addTouchEventListener(this, toucheventselector( GeneralDetails::trianPillButton ));
		
		for (int i = 1; i <= 3; i ++)
		{
			auto btnString = __String::createWithFormat("Image_GTbg%d", i );
			auto btnType = dynamic_cast<ImageView* >(Helper::seekWidgetByName(panelTrain, btnString->getCString()));
			btnType->setTouchEnabled(true);
			btnType->setTag( i );
			btnType->addTouchEventListener(this, toucheventselector( GeneralDetails::trainTypeButton ));
		}
	}
}

void GeneralDetails::skillBasicButton(Ref* pSender, TouchEventType type)
{
	if ( type == TOUCH_EVENT_ENDED )
	{
		if ( pSender != NULL )
		{
			ToolFunc::playEffectFile( Click );
		}
		
		skillButton(NULL, TOUCH_EVENT_ENDED);

		panelEvo->setLocalZOrder( -1 );
		panelEvo->setVisible(false);
		panelEvo->setTouchEnabled(false);

		panelTrain->setLocalZOrder( -1 );
		panelTrain->setVisible(false);
		panelTrain->setTouchEnabled(false);

		panelRight->setLocalZOrder( 4 );
		panelRight->setVisible(true);
		panelRight->setTouchEnabled(true);

		setBright( 4 );
	}
}

void GeneralDetails::talentButton(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		ToolFunc::playEffectFile( Click );

		if (false == NewComer::isGuideDone(1005))					/* 引导ID为5，且未完成 */
		{
			_comer->removeFromParentAndCleanup(true);
			_comer = NULL;
		}

		setButtonBright(DETIALButton);
		talentLayout->setTouchEnabled(true);
		talentLayout->setVisible(true);
		talentLayout->setLocalZOrder( 2 );
		skillLayout->setLocalZOrder( 0 );
		skillLayout->setVisible(false);
		skillLayout->setTouchEnabled(false);
		if (DataManager::getInstance()->isGetTalentDate(curGeneralVector[ 0 ].PKID))
		{
			interTalentVector = DataManager::getInstance()->interTalentVectors();
		}

		auto confirmClick = dynamic_cast<Button* >(Helper::seekWidgetByName(talentLayout, "Button_Confirm"));
		confirmClick->addTouchEventListener(this, toucheventselector(GeneralDetails::lightTalentButton));
		ImageView* lightImage[ 10 ];
		for (unsigned int i = 0; i < meetTalentVector.size(); i ++)
		{
			auto iconString = __String::createWithFormat("Image_%d_0", i + 1);
			auto iconImageString = __String::createWithFormat("%s.png", meetTalentVector[ i ].resName);
			auto lightString = __String::createWithFormat("Image_%d", i + 1);
			lightImage[ i ] = dynamic_cast<ImageView* >(Helper::seekWidgetByName(talentLayout, lightString->getCString()));
			//lightImage[ i ]->setScale(58.0f / 95.0f);
			for (unsigned int z = 0; z < interTalentVector.size(); z ++)
			{
				if (meetTalentVector[ i ].id == interTalentVector[ z ])
				{
					lightImage[ i ]->loadTexture("Wareroom/WmGridSelect.png", TextureResType::UI_TEX_TYPE_PLIST);
					lightImage[ i ]->setScale( 0.6f );
					break;
				}
				else
				{
					lightImage[ i ]->loadTexture("GeneralDetails/G_EquipBG.png", TextureResType::UI_TEX_TYPE_PLIST);
				}
			}			
			auto talentIcon = dynamic_cast<ImageView* >(Helper::seekWidgetByName(talentLayout, iconString->getCString()));
			talentIcon->loadTexture(iconImageString->getCString(), TextureResType::UI_TEX_TYPE_PLIST);
			talentIcon->setScale(50.0f / 95.0f);
			talentIcon->setTag( i );
			if (curGeneralVector[ 0 ].curStarLevel < meetTalentVector[ i ].lightStar)
			{
				ToolFunc::graySprite((Sprite*)talentIcon->getVirtualRenderer());
			}
			talentIcon->addTouchEventListener(this, toucheventselector(GeneralDetails::talentImageButton));
		}
	}
}

void GeneralDetails::talentImageButton(Ref* pSender, TouchEventType type)
{
	auto button = (Button* )pSender;
	auto index = button->getTag();
	if (type == TOUCH_EVENT_BEGAN)
	{
		ToolFunc::playEffectFile( Click );
		selectedTalentID = meetTalentVector[ index ].id;
		for (unsigned int i = 0; i < meetTalentVector.size(); i ++)
		{
			auto lightString = __String::createWithFormat("Image_%d", i + 1);
			auto lightImage = dynamic_cast<ImageView* >(Helper::seekWidgetByName(talentLayout, lightString->getCString()));
			lightImage->loadTexture("GeneralDetails/G_EquipBG.png", TextureResType::UI_TEX_TYPE_PLIST);			
		}
		if (curGeneralVector[ 0 ].curStarLevel == meetTalentVector[ index ].lightStar)
		{
			auto lightString = __String::createWithFormat("Image_%d", index + 1);
			auto lightImage = dynamic_cast<ImageView* >(Helper::seekWidgetByName(talentLayout, lightString->getCString()));
			lightImage->loadTexture("Wareroom/WmGridSelect.png", TextureResType::UI_TEX_TYPE_PLIST);
			lightImage->setScale( 0.6f );
		}

		auto promptText = Label::create();
		promptText->setSystemFontSize(13.0f);
		promptText->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
		promptText->setString(meetTalentVector[ index ].des);
		promptText->setDimensions(200, 30);
		auto size = Size(promptText->getContentSize().width + 20, promptText->getContentSize().height + 10);

		auto promptSprite = Scale9Sprite::create("TempPic/TianFuBox.png");
		promptSprite->setContentSize(size);
		promptSprite->addChild(promptText);
		promptText->setPosition(Point( promptSprite->getPosition() + Point( 8, 35 ) ));
		promptSprite->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
		promptSprite->setPosition(Point(button->getPosition() + Point(300, 0)));
		this->addChild(promptSprite, 10, TalentFlag);
	}
	else /*	if ( (type == TOUCH_EVENT_ENDED)  || (type == TOUCH_EVENT_MOVED) )*/
	{
		this->removeChildByTag(TalentFlag);		
	}
}

void GeneralDetails::skillPanelButton(Ref* pSender, TouchEventType type)
{
	auto button = (Layout* )pSender;
	if (type == TOUCH_EVENT_BEGAN)
	{
		ToolFunc::playEffectFile( Click );

		if (false == NewComer::isGuideDone(1005))					/* 引导ID为5，且未完成 */
		{
			if (0 != button->getTag())
			{
				return;
			}
			_comer->removeFromParentAndCleanup(true);
			_comer = NULL;
			auto cpID = NewComer::getCurGuideID();
			cpID = cpID | 0x010000;								/* 完成ID为0的引导 */
			NewComer::setCurGuideID(cpID);
			NewComer::setCurGuideStep(0);						/* 步骤ID重置 */
		}

		auto labelHurt = Label::create();
		labelHurt->setSystemFontSize(20.0f);
		labelHurt->setColor(Color3B(117, 117, 254));
		labelHurt->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
		
		auto labelDes = Label::create();
		labelDes->setSystemFontSize(20.0f);
		labelDes->setColor(Color3B(219, 201, 147));
		labelDes->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);	

		auto labelPropty = Label::create();
		labelPropty->setSystemFontSize(20.0f);
		labelPropty->setColor(Color3B(191, 191, 191));
		labelPropty->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);	

		int atkValue = curGeneralVector[ 0 ].initAtk + curGeneralVector[ 0 ].atkGrowing * ( curGeneralVector[ 0 ].level -1 );
		int mdValue = curGeneralVector[ 0 ].initMD + curGeneralVector[ 0 ].mdGrowing * ( curGeneralVector[ 0 ].level -1 );
		__String* skillHurtDes ;
		__String* skillProptyString;						// 技能升级增加的人物属性
		if (button->getTag() == 0)
		{
			labelDes->setString(localTempSkillNameVector[ 0 ].sADes);
			float skillHurt = curGeneralVector[ 0 ].initAtk * ( 1 - mdValue / (mdValue + curGeneralVector[ 0 ].skillLevel[ 0 ] * 73 + 877 )) + 
				curGeneralVector[ 0 ].skillLevel[ 0 ] * 80 * localTempSkillNameVector[ 0 ].sAHurt ;
			skillHurtDes = __String::createWithFormat("%s%.1f", mpFontChina->getComString("SkillHurt")->getCString(), skillHurt);
			if (curGeneralVector[ 0 ].maxStar == 5)
			{
				skillProptyString = __String::createWithFormat("%s%d",mpFontChina->getComString("AddPD")->getCString(), localSkillAddPropty[ 0 ].ePD + curGeneralVector[ 0 ].skillLevel[ 0 ] * localSkillAddPropty[ 0 ].ePDLen);
			}
			else if (curGeneralVector[ 0 ].maxStar == 4)
			{
				skillProptyString = __String::createWithFormat("%s%d", mpFontChina->getComString("AddPD")->getCString(), localSkillAddPropty[ 0 ].dPD + curGeneralVector[ 0 ].skillLevel[ 0 ] * localSkillAddPropty[ 0 ].dPDLen);
			}
			else if (curGeneralVector[ 0 ].maxStar == 3)
			{
				skillProptyString = __String::createWithFormat("%s%d", mpFontChina->getComString("AddPD")->getCString(), localSkillAddPropty[ 0 ].cPD + curGeneralVector[ 0 ].skillLevel[ 0 ] * localSkillAddPropty[ 0 ].cPDLen);
			}			
		}
		else if (button->getTag() == 1)
		{
			labelDes->setString(localTempSkillNameVector[ 0 ].sBDes);
			float skillHurt = (curGeneralVector[ 0 ].initAtk * ( 1 - mdValue / (mdValue + curGeneralVector[ 0 ].skillLevel[ 1 ] * 73 + 877 )) + 
				curGeneralVector[ 0 ].skillLevel[ 1 ] * 80 * localTempSkillNameVector[ 0 ].sAHurt) * localTempSkillNameVector[ 0 ].sBHurt;
			skillHurtDes = __String::createWithFormat("%s%.1f", mpFontChina->getComString("SkillHurt")->getCString(), skillHurt);
			if (curGeneralVector[ 0 ].maxStar == 5)
			{
				skillProptyString = __String::createWithFormat("%s%d", mpFontChina->getComString("AddMD")->getCString(), localSkillAddPropty[ 0 ].eMD + curGeneralVector[ 0 ].skillLevel[ 1 ] * localSkillAddPropty[ 0 ].eMDLen);
			}
			else if (curGeneralVector[ 0 ].maxStar == 4)
			{
				skillProptyString = __String::createWithFormat("%s%d", mpFontChina->getComString("AddMD")->getCString(), localSkillAddPropty[ 0 ].dMD + curGeneralVector[ 0 ].skillLevel[ 1 ] * localSkillAddPropty[ 0 ].dMDLen);
			}
			else if (curGeneralVector[ 0 ].maxStar == 3)
			{
				skillProptyString = __String::createWithFormat("%s%d", mpFontChina->getComString("AddMD")->getCString(), localSkillAddPropty[ 0 ].cMD + curGeneralVector[ 0 ].skillLevel[ 1 ] * localSkillAddPropty[ 0 ].cMDLen);
			}
		}
		else if (button->getTag() == 2)
		{
			labelDes->setString(localTempSkillNameVector[ 0 ].sCDes);
			float skillHurt = (curGeneralVector[ 0 ].initAtk * ( 1 - mdValue / (mdValue + curGeneralVector[ 0 ].skillLevel[ 2 ] * 73 + 877 )) + 
				curGeneralVector[ 0 ].skillLevel[ 2 ] * 80 * localTempSkillNameVector[ 0 ].sAHurt) * localTempSkillNameVector[ 0 ].sCHurt;
			skillHurtDes = __String::createWithFormat("%s%.1f", mpFontChina->getComString("SkillHurt")->getCString(), skillHurt);
			if (curGeneralVector[ 0 ].maxStar == 5)
			{
				skillProptyString = __String::createWithFormat("%s%d", mpFontChina->getComString("AddHP")->getCString(), localSkillAddPropty[ 0 ].eHP + curGeneralVector[ 0 ].skillLevel[ 2 ] * localSkillAddPropty[ 0 ].eHPLen);
			}
			else if (curGeneralVector[ 0 ].maxStar == 4)
			{
				skillProptyString = __String::createWithFormat("%s%d", mpFontChina->getComString("AddHP")->getCString(), localSkillAddPropty[ 0 ].dHP + curGeneralVector[ 0 ].skillLevel[ 2 ] * localSkillAddPropty[ 0 ].dHPLen);
			}
		}
		else if (button->getTag() == 3)
		{
			labelDes->setString(localTempSkillNameVector[ 0 ].sDDes);
			float skillHurt = (curGeneralVector[ 0 ].initAtk * ( 1 - mdValue / (mdValue + curGeneralVector[ 0 ].skillLevel[ 3 ] * 73 + 877 )) + 
				curGeneralVector[ 0 ].skillLevel[ 3 ] * 80 * localTempSkillNameVector[ 0 ].sAHurt) * localTempSkillNameVector[ 0 ].sDHurt;
			skillHurtDes = __String::createWithFormat("%s%.1f", mpFontChina->getComString("SkillHurt")->getCString(), skillHurt);
			if (curGeneralVector[ 0 ].maxStar == 5)
			{
				skillProptyString = __String::createWithFormat("%s%d", mpFontChina->getComString("AddAttack")->getCString(), localSkillAddPropty[ 0 ].eATK + curGeneralVector[ 0 ].skillLevel[ 3 ] * localSkillAddPropty[ 0 ].eAtkLen);
			}
		}	
		labelHurt->setString(skillHurtDes->getCString());
		labelPropty->setString(skillProptyString->getCString());
		auto sizeHurt = Size(labelHurt->getContentSize().width + 20, labelHurt->getContentSize().height + 10);
		auto sizeDes = Size(labelDes->getContentSize().width + 20, labelDes->getContentSize().height + 10);
		auto sprite = Scale9Sprite::create("TempPic/Prompt.png");
		sprite->setContentSize(Size( sizeDes.width, sizeDes.height + sizeHurt.height + labelPropty->getContentSize().height ));
		sprite->setAnchorPoint(Point(0, 0));
		sprite->addChild(labelHurt);
		sprite->addChild(labelDes);
		sprite->addChild(labelPropty);
		labelHurt->setPosition(Point(sprite->getPosition() + Point(8, 55)));
		labelPropty->setPosition(Point(sprite->getPosition() + Point(8, 30)));
		labelDes->setPosition(Point(sprite->getPosition() + Point(8, 5)));
		sprite->setPosition(Point(240 - sprite->getContentSize().width / 3, 330 - sprite->getContentSize().height * button->getTag()));
		this->addChild(sprite, 10, SkillFlag);
	}
	else 	if (type == TOUCH_EVENT_CANCELED)
	{
		this->removeChildByTag(SkillFlag);
	}
	else 	if (type == TOUCH_EVENT_ENDED)
	{
		this->removeChildByTag(SkillFlag);
	}
	
}

void GeneralDetails::lightTalentButton(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		ToolFunc::playEffectFile( Click );
		/*
			1：选择的是可以点亮的
			2：判断服务器点亮天赋的数目
		*/ 
		if (isTalentIDValid())
		{
			// 判断相同星级的是否点亮过
			unsigned int meetStar = 0;
			for (unsigned int i = 0; i < meetTalentVector.size(); i ++)
			{
				if (meetTalentVector[ i ].id == selectedTalentID)				// 当前选择的是几星天赋
				{
					meetStar = meetTalentVector[ i ].lightStar;
				}
			}
			if ( interTalentVector[ meetStar - 2 ] != 0 )
			{
				// 弹出提示：可以通过重置按钮重新选择天赋 
				auto promp = PromptBox::getInstance(mpFontChina->getComString("InvalidTalent")->getCString());
				promp->setFade();
				this->addChild(promp, 10);
				talentButton(NULL, TOUCH_EVENT_ENDED);
				return ;
			}

			if (DataManager::getInstance()->isTalentLightStar(curGeneralVector[ 0 ].PKID, selectedTalentID, meetStar - 2))
			{

			}
		}
		else
		{
			// 弹出提示：请选择要点亮的天赋
			auto promp = PromptBox::getInstance(mpFontChina->getComString("TalentInvalid")->getCString());
			promp->setFade();
			this->addChild(promp);
			talentButton(NULL, TOUCH_EVENT_ENDED);
		}		
	}
}

void GeneralDetails::cancelTalentButton(Ref* pSender, TouchEventType type)
{
	if ( type == TOUCH_EVENT_ENDED )
	{
		ToolFunc::playEffectFile( Click );
		if ( DataManager::getInstance()->reSetTalent(curGeneralVector[ 0 ].PKID, DiamondValue) )
		{
			talentButton(NULL, TOUCH_EVENT_ENDED);
		}
	}
}

void GeneralDetails::topCloseButton(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		ToolFunc::playEffectFile( Click );
		this->removeChildByTag(TopPanelFlag);
	}
}

void GeneralDetails::photoImageCall( Ref* pSender, TouchEventType type )
{
	if ( type == TOUCH_EVENT_ENDED )
	{
		ToolFunc::playEffectFile( Click );
		auto posImage = (Button*)pSender;
		clickPosFlag = posImage->getTag();
		initMaidanData();
		initHeroPanel();
	}
}

void GeneralDetails::panelTouchCallback(Ref* pSender, TouchEventType type)
{
	auto ptLoc = Point(0, 0);
	auto task = (Widget *)pSender;
	auto pBar = (LoadingBar *)task->getChildByName("ProgressBar");
	auto tag = task->getTag();
	auto scroll = (cocos2d::ui::ScrollView *)task->getParent()->getParent()->getParent();
	auto inner = scroll->getInnerContainer();
	auto temp = scroll->getContentSize().height - inner->getContentSize().height;

	if ( TouchEventType::TOUCH_EVENT_ENDED == type )
	{
		ptLoc = task->getTouchEndPos();
		ToolFunc::playEffectFile( Click );
		if ( (( (ptLoc.x <= m_ptTouchLoc.x + 10) && ( ptLoc.y <= m_ptTouchLoc.y + 10 )) || ( (ptLoc.x >= m_ptTouchLoc.x - 10) && ( ptLoc.y >= m_ptTouchLoc.y - 10 ) ) ) )
		{
			for (unsigned int i = 0; i < curTempGeneralVector.size(); i ++)							// 所有可选择武将遍历
			{
				if (curTempGeneralVector[ i ].PKID == tag)										// 所有武将中主键等于点击位置武将的主键
				{	
					unsigned int selectCount = selectedHero.size();
					if (selectCount == 0)
					{
						curTempGeneralVector[ i ].posFlag = clickPosFlag;							// 没有武将上阵
						selectedHero.push_back(curTempGeneralVector[ i ]);
 						topCloseButton(NULL, TOUCH_EVENT_ENDED);
						showSelectHero();						
					}
					else
					{
						for (unsigned int z = 0; z < selectedHero.size(); z ++)						// 已选择的武将遍历
						{
							if (selectedHero[ z ].posFlag == clickPosFlag)							// 已选择武将中的位置标记等于点击位置的标记
							{							
								auto itor = selectedHero.begin();								// 先移除后添加
								while (itor != selectedHero.end())							
								{
									if ( itor->posFlag == clickPosFlag ) 
									{
										itor = selectedHero.erase(itor);							// 移除当前位置上的武将
									}
									else 
									{
										++itor;
									}
								}
								curTempGeneralVector[ i ].posFlag = clickPosFlag;					// 添加选中的武将到点击位置
								selectedHero.push_back(curTempGeneralVector[ i ]);
 								topCloseButton(NULL, TOUCH_EVENT_ENDED);
								showSelectHero();
							} 
							else
							{
								curTempGeneralVector[ i ].posFlag = clickPosFlag;					// 点击的位置没有武将
								selectedHero.push_back(curTempGeneralVector[ i ]);
 								topCloseButton(NULL, TOUCH_EVENT_ENDED);
								showSelectHero();
							}
						}
					}					
				}
			}
 		}
	}
	else if ( TouchEventType::TOUCH_EVENT_BEGAN == type )
	{
		m_ptTouchLoc = task->getTouchStartPos();
		m_ptOriginleLoc = inner->getPosition();
	}
	else if ( TouchEventType::TOUCH_EVENT_MOVED == type )
	{
		ptLoc = task->getTouchMovePos();
		auto pt = m_ptOriginleLoc.y + ptLoc.y - m_ptTouchLoc.y;
		pt = (pt > 0) ? 0 : pt;
		pt = (pt < temp) ? temp : pt;
		inner->setPositionY(pt);
	}
}

void GeneralDetails::evoClick(Ref* pSender, TouchEventType type)
{
	if ( type == TOUCH_EVENT_ENDED )
	{
		ToolFunc::playEffectFile( Click );
		int sameInt = 0;			// 统计同名武将数量
		vector<int > heroVector ;		// 武将主键ID
		expCount = 0;
		for (unsigned int i = 0; i < selectedHero.size(); i ++)
		{
			heroVector.push_back(selectedHero[ i ].PKID);
			if (selectedHero[ i ].roleID == curGeneralVector[ 0 ].roleID)
			{
				sameInt ++;
			}
			for (unsigned int z = 0; z < localGeneralEvoExpVector.size(); z ++)			// 计算选择被吃掉武将能提供的经验值
			{
				if (selectedHero[ i ].maxStar == localGeneralEvoExpVector[ z ].maxStar)
				{
					if (selectedHero[ i ].curStarLevel == localGeneralEvoExpVector[ z ].curStar)
					{
						expCount += localGeneralEvoExpVector[ z ].pridExp;
					}
				}
			}
		}

		int i_MaxStar[] = { 3, 4, 5 };
		int i_CurStar[] = { 1, 2, 3, 4, 5 };
		int i_EvoLevel[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		for (int i = 0; i < sizeof( i_MaxStar ) / sizeof( i_MaxStar[ 0 ] ); i ++)
		{
			if ( curGeneralVector[ 0 ].maxStar == i_MaxStar[ i ] )
			{
				for (int k = 0; k < sizeof( i_CurStar ) / sizeof( i_CurStar[ 0 ] ); k++)
				{
					if ( curGeneralVector[ 0 ].curStarLevel == i_CurStar[ k ] )
					{
						for (int z = 0; z < sizeof( i_EvoLevel ) / sizeof( i_EvoLevel[ 0 ] ); z++)
						{
							if ( curGeneralVector[ 0 ].evoLevel == i_EvoLevel[ z ] )
							{
								// 判断、经验、金币、同名武将、灵魂石数量
								SESCStruct seStruct;
								memset(&seStruct, 0, sizeof(seStruct));
								seStruct = calcNeedNum();
								if ( interPlayerInfoVector[ 0 ].coinValue >= seStruct.coin)
								{
									if ( interPlayerInfoVector[ 0 ].soulCount >= seStruct.soul )
									{
										if ( sameInt >= seStruct.sameName )
										{
											if ( curGeneralVector[ 0 ].level >= seStruct.level )
											{
												int sy = calcEvoSYExp(curGeneralVector[ 0 ].evoExp);
												if ( expCount + calcEvoSYExp(curGeneralVector[ 0 ].evoExp) >= seStruct.exp )			// 如果被吃的武将能提供升星或者升阶所需经验
												{
													if ( DataManager::getInstance()->isRevoGeneral( curGeneralVector[ 0 ].PKID, curGeneralVector[ 0 ].curStarLevel + seStruct.addStar,
														curGeneralVector[ 0 ].evoLevel + seStruct.addEvo, curGeneralVector[ 0 ].evoExp + expCount, heroVector,
														seStruct.coin, seStruct.soul ) )
													{
														sameInt = 0;
														expCount = 0;
														heroVector.clear();
														selectedHero.clear();
														if ( seStruct.addEvo != 0 )
														{
															auto prompt = PromptBox::getInstance(mpFontChina->getComString("evo9")->getCString());
															prompt->setFade();
															this->addChild(prompt, 10);

															if (false == NewComer::isGuideDone(1010))					/* 引导ID为10，且未完成 */
															{
																if (3 == NewComer::getCurGuideStep())
																{
																	_comer->removeFromParentAndCleanup(true);
																	auto cpID = NewComer::getCurGuideID();
																	cpID = cpID | 0x010000;								/* 完成ID为0的引导 */
																	NewComer::setCurGuideID(cpID);
																	NewComer::setCurGuideStep(0);						/* 步骤ID重置 */
																}
															}
														}
														else
														{
															auto prompt = PromptBox::getInstance(mpFontChina->getComString("evo8")->getCString());
															prompt->setFade();
															this->addChild(prompt, 10);
														}
														// 刷新界面
														for (int i = 0; i < 5; i ++)
														{
															photoImage[ i ]->loadTexture("PointSets/dui-3.png", TextureResType::UI_TEX_TYPE_PLIST);
															photoImage[ i ]->setScale( 1.0f );
														}
														initHeroData();
														evoInit();
														return;
													}
												}
												else
												{
													if ( heroVector.size() == 0 )
													{
														auto prompt = PromptBox::getInstance(mpFontChina->getComString("AddGeneral")->getCString());
														prompt->setFade();
														this->addChild(prompt, 10);
														return;
													}
													// 被吃武将提供经验
													if ( DataManager::getInstance()->isRevoGeneral( curGeneralVector[ 0 ].PKID, curGeneralVector[ 0 ].curStarLevel,
														curGeneralVector[ 0 ].evoLevel, curGeneralVector[ 0 ].evoExp + expCount, heroVector,
														seStruct.coin, seStruct.soul ) )
													{
														// 刷新界面
														sameInt = 0;
														expCount = 0;
														heroVector.clear();
														selectedHero.clear();
														for (int i = 0; i < 5; i ++)
														{
															photoImage[ i ]->loadTexture("PointSets/dui-3.png", TextureResType::UI_TEX_TYPE_PLIST);
															photoImage[ i ]->setScale( 1.0f );
														}
														evoInit();
														return;
													}
												}
											}
											else
											{
												// 等级不足
												if ( curGeneralVector[ 0 ].curStarLevel == 1 )
												{
													if ( curGeneralVector[ 0 ].evoLevel == 2 )		// 一星 2 升到 二星
													{
														auto prompt = PromptBox::getInstance(mpFontChina->getComString("evo1")->getCString());
														prompt->setFade();
														this->addChild(prompt, 10);
													}
												}
												else if ( curGeneralVector[ 0 ].curStarLevel == 2 )
												{
													if ( curGeneralVector[ 0 ].evoLevel == 3 )
													{
														auto prompt = PromptBox::getInstance(mpFontChina->getComString("evo2")->getCString());
														prompt->setFade();
														this->addChild(prompt, 10);
													}
													else if ( curGeneralVector[ 0 ].evoLevel == 4 )
													{
														auto prompt = PromptBox::getInstance(mpFontChina->getComString("evo3")->getCString());
														prompt->setFade();
														this->addChild(prompt, 10);
													}
												}
												else if ( curGeneralVector[ 0 ].curStarLevel == 3 )
												{
													if ( curGeneralVector[ 0 ].evoLevel == 5 )
													{
														auto prompt = PromptBox::getInstance(mpFontChina->getComString("evo4")->getCString());
														prompt->setFade();
														this->addChild(prompt, 10);
													}
												}
												else if ( curGeneralVector[ 0 ].curStarLevel == 4 )
												{
													if ( curGeneralVector[ 0 ].evoLevel == 7 )
													{
														auto prompt = PromptBox::getInstance(mpFontChina->getComString("evo5")->getCString());
														prompt->setFade();
														this->addChild(prompt, 10);
													}
													else if ( curGeneralVector[ 0 ].evoLevel == 8 )
													{
														auto prompt = PromptBox::getInstance(mpFontChina->getComString("evo6")->getCString());
														prompt->setFade();
														this->addChild(prompt, 10);
													}
												}
												else
												{
													auto prompt = PromptBox::getInstance(mpFontChina->getComString("evo7")->getCString());
													prompt->setFade();
													this->addChild(prompt, 10);
												}
											}
										}
										else
										{
											// 同名武将不足
											auto prompt = PromptBox::getInstance(mpFontChina->getComString("NoSameName")->getCString());
											prompt->setFade();
											this->addChild(prompt, 10);
										}
									}
									else
									{
										// 灵魂石不足
										auto prompt = PromptBox::getInstance(mpFontChina->getComString("NoSoul")->getCString());
										prompt->setFade();
										this->addChild(prompt, 10);
									}
								}
								else
								{
									// 金币不足
									auto prompt = PromptBox::getInstance(mpFontChina->getComString("NoCoin")->getCString());
									prompt->setFade();
									this->addChild(prompt, 10);
								}
							}
						}
					}
				}
			}
		}
	}
}

void GeneralDetails::trainTypeButton(Ref* pSender, TouchEventType type)
{
	if ( type == TOUCH_EVENT_ENDED )
	{
		ToolFunc::playEffectFile( Click );
		auto btnFlag = ( (Button*)pSender )->getTag();
		int atkValue, hpValue, pdValue, mdValue = 0;
		if ( btnFlag == 1 )									// 培养丹培养
		{
			if ( DataManager::getInstance()->isSortGoodsNum( 93019 ) )
			{
				auto pillCount = DataManager::getInstance()->sortGoodsNum();
				if ( pillCount >= pillNeed )
				{
					if (false == NewComer::isGuideDone(1009))					/* 引导ID为9，且未完成 */
					{
						if (3 == NewComer::getCurGuideStep())
						{
							_comer->removeFromParentAndCleanup(true);
							NewComer::setCurGuideStep();
							_comer = NewComer::create(this, 1009, 4);
						}
					}

					// 刷新界面
					atkValue = trainShowLabel( 0 );
					hpValue = trainShowLabel( 0 );
					pdValue = trainShowLabel( 0 );
					mdValue = trainShowLabel( 0 );

					if ( DataManager::getInstance()->isCultivateGeneral(curGeneralVector[ 0 ].PKID, 0, 0, pillNeed, 0, 0, 0, 0) )
					{
						// 刷新培养丹
						if ( DataManager::getInstance()->isSortGoodsNum( 93019 ) )
						{
							auto trainDetial = dynamic_cast<Layout* >(panelTrain->getChildByName("GT_Panel_RightDetail"));
							auto pillCount = DataManager::getInstance()->sortGoodsNum(); 
							auto pillString = __String::createWithFormat("%d", pillCount);
							auto pillLabelA = dynamic_cast<Text* >( trainDetial->getChildByName("Label_PeiyangdanNum") );
							pillLabelA->setText(pillString->getCString());
						}
					}
				}
				else
				{
					// 弹出提示：培养丹数量不足
					auto promp = PromptBox::getInstance(mpFontChina->getComString("Plus545")->getCString());
					promp->setFade();
					this->addChild(promp, 10);
					return;
				}
			}
		}
		else if ( btnFlag == 2 )								// 金币
		{
			if ( interPlayerInfoVector[ 0 ].coinValue >= coinNeed )
			{
				atkValue = trainShowLabel( 1 );
				hpValue = trainShowLabel( 1 );
				pdValue = trainShowLabel( 1 );
				mdValue = trainShowLabel( 1 );

				if ( DataManager::getInstance()->isCultivateGeneral(curGeneralVector[ 0 ].PKID, coinNeed, 0, 0, 0, 0, 0, 0) )
				{
					if ( DataManager::getInstance()->isGetPlayerInfo() )
					{
						interPlayerInfoVector = DataManager::getInstance()->interPlayerInfoVector();
					}
				}
			}
			else
			{
				// 弹出提示：金币数量不足
				auto promp = PromptBox::getInstance(mpFontChina->getComString("NoCoin")->getCString());
				promp->setFade();
				this->addChild(promp, 10);
				return;
			}
		}
		else if ( btnFlag == 3 )								// 钻石
		{
			if ( interPlayerInfoVector[ 0 ].diamondValue >= diamondNeed )
			{
				atkValue = trainShowLabel( 2 );
				hpValue = trainShowLabel( 2 );
				pdValue = trainShowLabel( 2 );
				mdValue = trainShowLabel( 2 );

				if ( DataManager::getInstance()->isCultivateGeneral(curGeneralVector[ 0 ].PKID, 0, diamondNeed, 0, 0, 0, 0, 0) )
				{
					if ( DataManager::getInstance()->isGetPlayerInfo() )
					{
						interPlayerInfoVector = DataManager::getInstance()->interPlayerInfoVector();
					}
				}
			}
			else
			{
				// 弹出提示：钻石数量不足
				auto promp = PromptBox::getInstance(mpFontChina->getComString("Loading16")->getCString());
				promp->setFade();
				this->addChild(promp, 10);
				return;
			}
		}
		trainShowLabel( btnFlag );

		pillValues[ 4 ] = btnFlag;
		pillValues[ 0 ] = atkValue;
		pillValues[ 1 ] = hpValue;
		pillValues[ 2 ] = pdValue;
		pillValues[ 3 ] = mdValue;

		vector<int > growthVector;
		if ( DataManager::getInstance()->isGetGeneralGrowth( curGeneralVector[ 0 ].PKID ) )
		{
			growthVector = DataManager::getInstance()->getGeneralGrowthVector();
		}

		auto trainDetial = dynamic_cast<Layout* >(panelTrain->getChildByName("GT_Panel_RightDetail"));
		auto atkLabel = dynamic_cast<Text* >( trainDetial->getChildByName("Label_ATKB") );
		auto atkString = __String::createWithFormat("%d+(%d)", curGeneralVector[ 0 ].initAtk, growthVector[ 0 ]);
		atkLabel->setText(atkString->getCString());
		auto atkLabelA = dynamic_cast<Text* >( trainDetial->getChildByName("Label_ATKA") );

		auto effectA = EffectAction::getInstance();
		effectA->trainEffect();
		effectA->setPosition( atkLabelA->getPosition() + Point( 80, 20 ) );
		panelTrain->addChild(effectA, 10);

		auto hpLabel = dynamic_cast<Text* >( trainDetial->getChildByName("Label_HPB") );
		auto hpString = __String::createWithFormat("%d+(%d)", curGeneralVector[ 0 ].initHP, growthVector[ 1 ]);
		hpLabel->setText(hpString->getCString());
		auto hpLabelA = dynamic_cast<Text* >( trainDetial->getChildByName("Label_HPA") );
		auto effectB = EffectAction::getInstance();
		effectB->trainEffect();
		effectB->setPosition( hpLabelA->getPosition() + Point( 80, 20 ) );
		panelTrain->addChild(effectB, 10);

		auto pdLabel = dynamic_cast<Text* >( trainDetial->getChildByName("Label_PDB") );
		auto pdString = __String::createWithFormat("%d+(%d)", curGeneralVector[ 0 ].initPD, growthVector[ 2 ]);
		pdLabel->setText(pdString->getCString());
		auto pdLabelA = dynamic_cast<Text* >( trainDetial->getChildByName("Label_PDA") );
		auto effectC = EffectAction::getInstance();
		effectC->trainEffect();
		effectC->setPosition( pdLabelA->getPosition() + Point( 80, 20 ) );
		panelTrain->addChild(effectC, 10);

		auto mdLabel = dynamic_cast<Text* >( trainDetial->getChildByName("Label_MDB") );
		auto mdString = __String::createWithFormat("%d+(%d)", curGeneralVector[ 0 ].initMD, growthVector[ 3 ]);
		mdLabel->setText(mdString->getCString());
		auto mdLabelA = dynamic_cast<Text* >( trainDetial->getChildByName("Label_MDA") );
		auto effectD = EffectAction::getInstance();
		effectD->trainEffect();
		effectD->setPosition( mdLabelA->getPosition() + Point( 80, 20 ) );
		panelTrain->addChild(effectD, 10);

		this->runAction( Sequence::createWithTwoActions(DelayTime::create(0.3f), CallFunc::create(CC_CALLBACK_0( GeneralDetails::effectCallBack, this )) ) );
	}
}

void GeneralDetails::backButton(Ref* pSender, TouchEventType type)
{
	if ( type == TOUCH_EVENT_ENDED )
	{
		ToolFunc::playEffectFile( Click );
		Director::getInstance()->setProjection(Director::Projection::_2D);
		if ( panelDetial->getAnchorPoint() != Point( 0.5, 0.5 ) )
		{
			panelDetial->setAnchorPoint( Point( 0.5, 0.5 ) );
			panelDetial->setPosition(Point( panelDetial->getPositionX() + panelDetial->getContentSize().width / 2, panelDetial->getPositionY() + panelDetial->getContentSize().height / 2 ));
		}		
		auto ss = OrbitCamera::create(0.2f, 1.0f, 0.1f, 1.0f, 90.0f, 0.1f, 0.1f);
		auto callA = CallFunc::create( CC_CALLBACK_0( GeneralDetails::filxCallBackA, this ) );
		panelDetial->runAction( Sequence::createWithTwoActions(ss, callA) );
	}
}

void GeneralDetails::trianPillButton(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		ToolFunc::playEffectFile( Click );
		if ( ( pillValues[ 0 ] == 0 ) && ( pillValues[ 1 ] == 0 ) && ( pillValues[ 2 ] == 0 ) && ( pillValues[ 3 ] == 0 ) )
		{
			// 请选择一种培养方式
			auto prompt = PromptBox::getInstance(mpFontChina->getComString("Plus950")->getCString());
			prompt->setFade();
			this->addChild(prompt, 10);
			return;
		}
		else
		{
			if (false == NewComer::isGuideDone(1009))				/* 引导ID为9，且未完成 */
			{
				if (4 == NewComer::getCurGuideStep())
				{
					_comer->removeFromParentAndCleanup(true);
					auto cpID = NewComer::getCurGuideID();
					cpID = cpID | 0x010000;							/* 完成ID为0的引导 */
					NewComer::setCurGuideID(cpID);
					NewComer::setCurGuideStep(0);					/* 步骤ID重置 */
				}
			}

			if ( pillValues[ 4 ] == 1 )
			{
				if ( DataManager::getInstance()->isCultivateGeneral(curGeneralVector[ 0 ].PKID, 0, 0, pillNeed, pillValues[ 0 ], pillValues[ 1 ], pillValues[ 2 ], pillValues[ 3 ]) )
				{
					for (int i = 0; i < 5; i++)
					{
						pillValues[ i ] = 0;
					}
				}
			}
			else if ( pillValues[ 4 ] == 2 )
			{
				if ( DataManager::getInstance()->isCultivateGeneral(curGeneralVector[ 0 ].PKID, coinNeed, 0, 0, pillValues[ 0 ], pillValues[ 1 ], pillValues[ 2 ], pillValues[ 3 ]) )
				{
					for (int i = 0; i < 5; i++)
					{
						pillValues[ i ] = 0;
					}
				}
			}
			else if ( pillValues[ 4 ] == 3 )
			{
				if ( DataManager::getInstance()->isCultivateGeneral(curGeneralVector[ 0 ].PKID, 0, diamondNeed, 0, pillValues[ 0 ], pillValues[ 1 ], pillValues[ 2 ], pillValues[ 3 ]) )
				{
					for (int i = 0; i < 5; i++)
					{
						pillValues[ i ] = 0;
					}
				}
			}
			trainButton(NULL, TOUCH_EVENT_ENDED);
			initEquipData();
		}
	}
}

void GeneralDetails::typeButton(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		ToolFunc::playEffectFile( Click );
		tempGeneralVector.clear();
		auto button = (Button*)pSender;
		if (button->getTag() == 0)
		{
			tempGeneralVector = curTempGeneralVector;
		}
		else
		{
			for (unsigned int i = 0; i < curTempGeneralVector.size(); i ++)
			{
				if (curTempGeneralVector[ i ].jobType == button->getTag())
				{
					tempGeneralVector.push_back(curTempGeneralVector[ i ]);
				}
			}
		}
		showGeneral();
	}
}

bool GeneralDetails::isTalentIDValid()
{
	bool bRef = false;
	for (unsigned int i = 0; i < meetTalentVector.size(); i ++)
	{
		if (curGeneralVector[ 0 ].curStarLevel >= meetTalentVector[ i ].lightStar)
		{
			if (selectedTalentID == meetTalentVector[ i ].id)					// 当选择的ID存在于当前天赋点亮星级中
			{
				bRef = true;
			}
		}
	}
	return bRef;
}

int GeneralDetails::calcGeneralExp(int level, int exp)
{
	int resultExp = 0;
	for (unsigned int i = 0; i < localGeneralUpgradeVector.size(); i ++)
	{
		if (localGeneralUpgradeVector[ i ].gNeedExp >= exp)
		{
			resultExp = exp;
		}
		else
		{
			exp -= localGeneralUpgradeVector[ i ].gNeedExp;
		}
	}
	return resultExp;
}

void GeneralDetails::setHeroSkillLevel()
{
	if (curGeneralVector[ 0 ].maxStar == 3)													// 三星武将
	{
		if ( (curGeneralVector[ 0 ].level >= 3) && (curGeneralVector[ 0 ].skillLevel[ 1 ] == 0) )			// 人物等级大于三级第二个技能解锁
		{
			DataManager::getInstance()->isSkillUpgrade(maidanVector[ 0 ].PKID, curGeneralVector[ 0 ].skillLevel[ 0 ], 1, 0, 0, 0);
			initHeroData();
		} 
	}
	else if (curGeneralVector[ 0 ].maxStar == 4)
	{
		if ( (curGeneralVector[ 0 ].level >= 3) && (curGeneralVector[ 0 ].skillLevel[ 1 ] == 0) )			// 人物等级大于三级第二个技能解锁
		{
			DataManager::getInstance()->isSkillUpgrade(maidanVector[ 0 ].PKID, curGeneralVector[ 0 ].skillLevel[ 0 ], 1, 0, 0, 0);
			initHeroData();
		} 
		if ( (curGeneralVector[ 0 ].level >= 8) && (curGeneralVector[ 0 ].skillLevel[ 2 ] == 0) )
		{
			DataManager::getInstance()->isSkillUpgrade(maidanVector[ 0 ].PKID, curGeneralVector[ 0 ].skillLevel[ 0 ], curGeneralVector[ 0 ].skillLevel[ 1 ], 1, 0, 0);
			initHeroData();
		}
	}
	else if (curGeneralVector[ 0 ].maxStar == 5)
	{
		if ( (curGeneralVector[ 0 ].level >= 3) && (curGeneralVector[ 0 ].skillLevel[ 1 ] == 0) )			// 人物等级大于三级第二个技能解锁
		{
			DataManager::getInstance()->isSkillUpgrade(maidanVector[ 0 ].PKID, curGeneralVector[ 0 ].skillLevel[ 0 ], 1, 0, 0, 0);
			initHeroData();
		} 
		if ( (curGeneralVector[ 0 ].level >= 8) && (curGeneralVector[ 0 ].skillLevel[ 2 ] == 0) )
		{
			DataManager::getInstance()->isSkillUpgrade(maidanVector[ 0 ].PKID, curGeneralVector[ 0 ].skillLevel[ 0 ], curGeneralVector[ 0 ].skillLevel[ 1 ], 1, 0, 0);
			initHeroData();
		}
		if ( (curGeneralVector[ 0 ].level >= 15) && (curGeneralVector[ 0 ].skillLevel[ 3 ] == 0) )
		{
			DataManager::getInstance()->isSkillUpgrade(maidanVector[ 0 ].PKID, curGeneralVector[ 0 ].skillLevel[ 0 ], curGeneralVector[ 0 ].skillLevel[ 1 ], curGeneralVector[ 0 ].skillLevel[ 2 ], 1, 0);
			initHeroData();
		}
	}	
}

int GeneralDetails::trainShowLabel( int tag )
{
	int resultNum = -1;
	auto calcNum = ToolFunc::calcRandom( 1, 100 );
	if ( tag == 0 )		// 培养丹
	{		
		if ( ( calcNum >= 1 ) && ( calcNum <= 3 ) )
		{
			resultNum = ToolFunc::calcRandom( -10, -5);
		}
		else if ( ( calcNum >= 4 ) && ( calcNum <= 18 ) )
		{
			resultNum = ToolFunc::calcRandom( -4, -2);
		}
		else if ( ( calcNum >= 15 ) && ( calcNum <= 53 ) )
		{
			resultNum = ToolFunc::calcRandom( -1, 0);
		}
		else if ( ( calcNum >= 54 ) && ( calcNum <= 88 ) )
		{
			resultNum = ToolFunc::calcRandom( 1, 2);
		}
		else if ( ( calcNum >= 89 ) && ( calcNum <= 96 ) )
		{
			resultNum = ToolFunc::calcRandom( 3, 5);
		}
		else if ( ( calcNum >= 97 ) && ( calcNum <= 99 ) )
		{
			resultNum = ToolFunc::calcRandom( 6, 8);
		}
		else if ( calcNum == 100 )
		{
			resultNum = ToolFunc::calcRandom( 9, 10);
		}
	}
	else if ( tag == 1 )
	{
		if ( ( calcNum >= 1 ) && ( calcNum <= 3 ) )
		{
			resultNum = ToolFunc::calcRandom( -10, -5);
		}
		else if ( ( calcNum >= 4 ) && ( calcNum <= 12 ) )
		{
			resultNum = ToolFunc::calcRandom( -6, -2 );
		}
		else if ( ( calcNum >= 13 ) && ( calcNum <= 48 ) )
		{
			resultNum = ToolFunc::calcRandom( -1, 0 );
		}
		else if ( ( calcNum >= 49 ) && ( calcNum <= 82 ) )
		{
			resultNum = ToolFunc::calcRandom( 1, 2 );
		}
		else if ( calcNum == 83 )
		{
			resultNum = ToolFunc::calcRandom( 3, 5 );
		}
		else if ( ( calcNum >= 84 ) && ( calcNum <= 99 ) )
		{
			resultNum = ToolFunc::calcRandom( 6, 8 );
		}
		else if ( calcNum == 100 )
		{
			resultNum = ToolFunc::calcRandom( 9, 10 );
		}
	}
	else if ( tag == 2 )
	{
		if ( ( calcNum >= 1 ) && ( calcNum <= 4 ) )
		{
			resultNum = ToolFunc::calcRandom( -10, -5);
		}
		else if ( calcNum == 5 )
		{
			resultNum = ToolFunc::calcRandom( -6, -2 );
		}
		else if ( ( calcNum >= 6 ) && ( calcNum <= 31 ) )
		{
			resultNum = ToolFunc::calcRandom( -1, 0 );
		}
		else if ( ( calcNum >= 32 ) && ( calcNum <= 70 ) )
		{
			resultNum = ToolFunc::calcRandom( 1, 2 );
		}
		else if ( ( calcNum >= 71 ) && ( calcNum <= 72 ) )
		{
			resultNum = ToolFunc::calcRandom( 3, 5 );
		}
		else if ( ( calcNum >= 93 ) && ( calcNum <= 98 ) )
		{
			resultNum = ToolFunc::calcRandom( 6, 8 );
		}
		else if ( ( calcNum >= 99 ) && ( calcNum <= 100 ) )
		{
			resultNum = ToolFunc::calcRandom( 9, 10 );
		}
	}
	return resultNum;
}

void GeneralDetails::evoInit()
{

	initHeroData();

	// 初始属性
	auto sNameText = dynamic_cast<Text* >(Helper::seekWidgetByName(panelEvo, "Label_NameBefore"));
	auto sNameString = __String::createWithFormat("%s+%d", curGeneralVector[ 0 ].chinaName, curGeneralVector[ 0 ].evoLevel);
	sNameText->setText(sNameString->getCString());

	auto starPanel = dynamic_cast<Layout* >(Helper::seekWidgetByName(panelEvo, "GS_Star"));
	ImageView* bStar[ 5 ];
	ImageView* bDarkStar[ 5 ];
	for (int i = 0; i < 5; i ++)
	{
		auto sStar = __String::createWithFormat("GS_Star_%d", i + 1);
		auto sDarkStar = __String::createWithFormat("GS_DarkStar_%d", i + 1);
		bStar[ i ] = dynamic_cast<ImageView* >(Helper::seekWidgetByName(starPanel, sStar->getCString()));
		bDarkStar[ i ] = dynamic_cast<ImageView* >(Helper::seekWidgetByName(starPanel, sDarkStar->getCString()));
		bStar[ i ]->setVisible(false);
		bDarkStar[ i ]->setVisible(false);
	}
	for (int i = 0; i < curGeneralVector[ 0 ].maxStar; i++)
	{
		bDarkStar[ i ]->setVisible(true);
	}
	for (int i = 0; i < curGeneralVector[ 0 ].curStarLevel; i++)
	{
		bStar[ i ]->setVisible(true);
	}

	auto comPanel = dynamic_cast<Layout* >(Helper::seekWidgetByName(panelEvo, "Panel_110"));
	auto beforePanel = dynamic_cast<Layout* >(Helper::seekWidgetByName(comPanel, "Panel_Before"));
	auto bAttack = dynamic_cast<Text* >(Helper::seekWidgetByName(beforePanel, "Label_ATKB_0"));			// 攻击
	auto bHP = dynamic_cast<Text* >(Helper::seekWidgetByName(beforePanel, "Label_HPB_0"));			// 血量
	auto bPD = dynamic_cast<Text* >(Helper::seekWidgetByName(beforePanel, "Label_PDB_0"));			// 物防
	auto bMD = dynamic_cast<Text* >(Helper::seekWidgetByName(beforePanel, "Label_MDB_0"));			// 法防
	auto bRHP = dynamic_cast<Text* >(Helper::seekWidgetByName(beforePanel, "Label_RiseHPB_0"));		// 回血

	auto sAttack = __String::createWithFormat("%d", curGeneralVector[ 0 ].atkGrowing );
	auto sHP = __String::createWithFormat("%d", curGeneralVector[ 0 ].hpGrowing );
	auto sPD = __String::createWithFormat("%d", curGeneralVector[ 0 ].pdGrowing );
	auto sMD = __String::createWithFormat("%d", curGeneralVector[ 0 ].mdGrowing );
	auto sRHP = __String::createWithFormat("%.3f", curGeneralVector[ 0 ].riseHP );

	bAttack->setText(sAttack->getCString());
	bHP->setText(sHP->getCString());
	bPD->setText(sPD->getCString());
	bMD->setText(sMD->getCString());
	bRHP->setText(sRHP->getCString());

	// 进化后的属性

	auto afNameText = dynamic_cast<Text* >(Helper::seekWidgetByName(panelEvo, "Label_NameAfter"));
	auto afNameString = __String::createWithFormat("%s+%d", curGeneralVector[ 0 ].chinaName, curGeneralVector[ 0 ].evoLevel + 1);
	afNameText->setText(afNameString->getCString());

	auto afStarPanel = dynamic_cast<Layout* >(Helper::seekWidgetByName(panelEvo, "GS_Star_0"));
	ImageView* afStar[ 5 ];
	ImageView* afDarkStar[ 5 ];
	for (int i = 0; i < 5; i ++)
	{
		auto afsStar = __String::createWithFormat("GS_Star_%d", i + 1);
		auto afsDarkStar = __String::createWithFormat("GS_DarkStar_%d", i + 1);
		afStar[ i ] = dynamic_cast<ImageView* >(Helper::seekWidgetByName(afStarPanel, afsStar->getCString()));
		afDarkStar[ i ] = dynamic_cast<ImageView* >(Helper::seekWidgetByName(afStarPanel, afsDarkStar->getCString()));
		afStar[ i ]->setVisible(false);
		afDarkStar[ i ]->setVisible(false);
	}
	for (int i = 0; i < curGeneralVector[ 0 ].maxStar; i++)
	{
		afDarkStar[ i ]->setVisible(true);
	}
	int curMaxStar = curGeneralVector[ 0 ].curStarLevel + 1 ;
	if ( curMaxStar >= curGeneralVector[ 0 ].maxStar )
	{
		curMaxStar = curGeneralVector[ 0 ].maxStar;
	}

	for (int i = 0; i < curMaxStar; i++)
	{
		afStar[ i ]->setVisible(true);
	}

	GeneralProptyStruct generalStruct;
	memset(&generalStruct, 0, sizeof(generalStruct));
	int curRoleID = maidanVector[ 0 ].roleID + interGeneralVector[ 0 ].starLevel + maidanVector[ 0 ].evoLevel - StarID;
	generalStruct.initAtk = localGeneralVector[ curRoleID ].initAtk;
	generalStruct.initHP = localGeneralVector[ curRoleID ].initHP;
	generalStruct.initPD = localGeneralVector[ curRoleID ].initPD;
	generalStruct.initMD = localGeneralVector[ curRoleID ].initMD;
	generalStruct.riseHP = localGeneralVector[ curRoleID ].riseHP;

	auto afterPanel = dynamic_cast<Layout* >(Helper::seekWidgetByName(comPanel, "Panel_After"));
	auto pAttack = dynamic_cast<Text* >(Helper::seekWidgetByName(afterPanel, "Label_ATKB_0"));		// 攻击
	auto pHP = dynamic_cast<Text* >(Helper::seekWidgetByName(afterPanel, "Label_HPB_0"));			// 血量
	auto pPD = dynamic_cast<Text* >(Helper::seekWidgetByName(afterPanel, "Label_PDB_0"));			// 物防
	auto pMD = dynamic_cast<Text* >(Helper::seekWidgetByName(afterPanel, "Label_MDB_0"));			// 法防
	auto pRHP = dynamic_cast<Text* >(Helper::seekWidgetByName(afterPanel, "Label_RiseHPB_0"));		// 回血
	
	auto psAttack = __String::createWithFormat("%d", localGeneralVector[ curRoleID ].atkGrowing );
	auto psHP = __String::createWithFormat("%d", localGeneralVector[ curRoleID ].hpGrowing );
	auto psPD = __String::createWithFormat("%d", localGeneralVector[ curRoleID ].pdGrowing );
	auto psMD = __String::createWithFormat("%d", localGeneralVector[ curRoleID ].mdGrowing );
	auto psRHP = __String::createWithFormat("%.3f", generalStruct.riseHP );

	pAttack->setText(psAttack->getCString());
	pHP->setText(psHP->getCString());
	pPD->setText(psPD->getCString());
	pMD->setText(psMD->getCString());
	pRHP->setText(psRHP->getCString());

	SESCStruct seStruct;
	memset(&seStruct, 0, sizeof(seStruct));
	seStruct = calcNeedNum();

	auto soulText = dynamic_cast<Text* >(Helper::seekWidgetByName(panelEvo, "GS_SoulNum"));					// 灵魂石数量	
	auto soulString = __String::createWithFormat("%d", seStruct.soul);
	soulText->setText(soulString->getCString());

	// 进化经验值显示
// 	auto evoText = dynamic_cast<Text* >(Helper::seekWidgetByName(panelEvo, "Label_Pre"));						// 前后经验值
 	auto curExp = calcEvoSYExp(curGeneralVector[ 0 ].evoExp);
// 	auto expString = __String::createWithFormat("%d/%d", curExp, seStruct.exp);
// 	evoText->setText(expString->getCString());

	auto expBar = dynamic_cast<LoadingBar* >(Helper::seekWidgetByName(panelEvo, "GS_Star_EXP"));				// 当前的经验条
	auto expExpanBar = dynamic_cast<LoadingBar* >(Helper::seekWidgetByName(panelEvo, "GS_Star_EXP_0"));		// 增加的经验条
	int calcExp = curExp * 1.0f / seStruct.exp * 100.0f;
	if ( calcExp >= 100 )
	{
		calcExp = 100;
	}
	else if ( calcExp < 0 )
	{
		calcExp = 100;
	}
	expBar->setPercent( calcExp );
	expExpanBar->setPercent( calcExp );

	auto coinText = dynamic_cast<Text* >(Helper::seekWidgetByName(panelEvo, "GS_coinCount"));					// 金币数量
	auto coinString = __String::createWithFormat("%d", seStruct.coin);
	coinText->setText(coinString->getCString());

	for (int i = 0; i < 5; i ++)
	{
		auto panelString = __String::createWithFormat("Panel_GSRole%d", i );
		auto smPanel = dynamic_cast<Layout* >(Helper::seekWidgetByName(panelEvo, panelString->getCString()));
		auto imageString = __String::createWithFormat( "Image_SameRolePhoto_%d", i );
		photoImage[ i ] = dynamic_cast<ImageView* >(Helper::seekWidgetByName(smPanel, "Image_RRoleBG_1" ));
		photoImage[ i ]->setTouchEnabled(true);
		photoImage[ i ]->setTag( i );
		photoImage[ i ]->addTouchEventListener(this, toucheventselector(GeneralDetails::photoImageCall));
	}

	auto evoButton = dynamic_cast<Button* >(Helper::seekWidgetByName(panelEvo, "Button_GSstart_0"));
	evoButton->addTouchEventListener(this, toucheventselector(GeneralDetails::evoClick));
}

void GeneralDetails::filxCallBack()
{
	Director::getInstance()->setProjection(Director::Projection::_2D);
	auto ss = OrbitCamera::create(0.2f, 1.0f, 0.1f, 1.0f, 0.0f, 0.1f, 0.1f);
	panelDetial->runAction( ss );

	panelLeft->setLocalZOrder( -1 );
	panelLeft->setVisible(false);
	panelLeft->setTouchEnabled(false);

	panelDetial->setLocalZOrder( 2 );
	panelDetial->setVisible(true);
	panelDetial->setTouchEnabled(true);

	showLabel();
}

void GeneralDetails::filxCallBackA()
{
	Director::getInstance()->setProjection(Director::Projection::_2D);
	auto ss = OrbitCamera::create(0.2f, 1.0f, 0.1f, 1.0f, 0.0f, 0.1f, 0.1f);
	panelLeft->runAction( ss );

	panelLeft->setLocalZOrder( 2 );
	panelLeft->setVisible(true);
	panelLeft->setTouchEnabled(true);

	panelDetial->setLocalZOrder( -1 );
	panelDetial->setVisible(false);
	panelDetial->setTouchEnabled(false);
}

void GeneralDetails::effectCallBack()
{
	auto trainDetial = dynamic_cast<Layout* >(panelTrain->getChildByName("GT_Panel_RightDetail"));

	auto atkLabelA = dynamic_cast<Text* >( trainDetial->getChildByName("Label_ATKA") );
	__String* atkStringA ;
	if ( pillValues[ 0 ] < 0 )
		atkStringA = __String::createWithFormat("%d", pillValues[ 0 ]);
	else
		atkStringA = __String::createWithFormat("+%d", pillValues[ 0 ]);
	atkLabelA->setText(atkStringA->getCString());

	auto hpLabelA = dynamic_cast<Text* >( trainDetial->getChildByName("Label_HPA") );
	__String* hpStringA ;
	if ( pillValues[ 1 ] < 0 )
		hpStringA = __String::createWithFormat("%d", pillValues[ 1 ]);
	else
		hpStringA = __String::createWithFormat("+%d", pillValues[ 1 ]);
	hpLabelA->setText(hpStringA->getCString());

	auto pdLabelA = dynamic_cast<Text* >( trainDetial->getChildByName("Label_PDA") );
	__String* pdStringA ;
	if ( pillValues[ 2 ] < 0 )
		pdStringA = __String::createWithFormat("%d", pillValues[ 2 ]);
	else
		pdStringA = __String::createWithFormat("+%d", pillValues[ 2 ]);
	pdLabelA->setText(pdStringA->getCString());

	auto mdLabelA = dynamic_cast<Text* >( trainDetial->getChildByName("Label_MDA") );
	__String* mdStringA;
	if ( pillValues[ 3 ] < 0 )
		mdStringA = __String::createWithFormat("%d", pillValues[ 3 ]);
	else
		mdStringA = __String::createWithFormat("+%d", pillValues[ 3 ]);
	mdLabelA->setText(mdStringA->getCString());
}

void GeneralDetails::showSelectHero()
{
	for (unsigned int i = 0; i < selectedHero.size(); i++)
	{
		auto heroName = __String::createWithFormat("%s.png", selectedHero[ i ].chinaSmallName);
		photoImage[ selectedHero[ i ].posFlag ]->loadTexture(heroName->getCString(), TextureResType::UI_TEX_TYPE_PLIST);
		photoImage[ selectedHero[ i ].posFlag ]->setScale( 77.0f / 95.0f );
	}

	localGeneralEvoExpVector = DataManager::getInstance()->localGeneralEvoExpVector();				// 进化武将提供经验初始化
	if (localGeneralEvoExpVector.size() == 0)
	{
		DataManager::getInstance()->GeneralEvoExpDataParser();
		localGeneralEvoExpVector = DataManager::getInstance()->localGeneralEvoExpVector();
	}
	expCount = 0;
	for (unsigned int i = 0; i < selectedHero.size(); i ++)
	{
		for (unsigned int z = 0; z < localGeneralEvoExpVector.size(); z ++)			// 计算选择被吃掉武将能提供的经验值
		{
			if (selectedHero[ i ].maxStar == localGeneralEvoExpVector[ z ].maxStar)
			{
				if (selectedHero[ i ].curStarLevel == localGeneralEvoExpVector[ z ].curStar)
				{
					expCount += localGeneralEvoExpVector[ z ].pridExp;
				}
			}
		}
	}

	SESCStruct seStruct;
	memset(&seStruct, 0, sizeof(seStruct));
	seStruct = calcNeedNum();
	// 刷新经验值
// 	auto evoText = dynamic_cast<Text* >(Helper::seekWidgetByName(panelEvo, "Label_Pre"));						// 前后经验值
	auto curExp = calcEvoSYExp(curGeneralVector[ 0 ].evoExp);
// 	auto expString = __String::createWithFormat("%d/%d", curExp + expCount, seStruct.exp);
// 	evoText->setText(expString->getCString());

	auto expExpanBar = dynamic_cast<LoadingBar* >(Helper::seekWidgetByName(panelEvo, "GS_Star_EXP_0"));		// 增加的经验条
	int calcExp = ( curExp + expCount ) * 1.0f / seStruct.exp * 100.0f;
	if ( calcExp >= 100 )
	{
		calcExp = 100;
	}
	expExpanBar->setPercent( calcExp );
}

int GeneralDetails::calcEvoSYExp(int iExp)
{
	int i_Exp = 0;
	if ( curGeneralVector[ 0 ].maxStar == 3 )
	{
		if ( curGeneralVector[ 0 ].curStarLevel == 1 )
		{
			if ( ( curGeneralVector[ 0 ].evoLevel == 0 ) || ( curGeneralVector[ 0 ].evoLevel == 1 ) )
			{
				i_Exp = iExp;
			}
			else if ( curGeneralVector[ 0 ].evoLevel == 2 )
			{
				if ( iExp > 1000 )
				{
					i_Exp = iExp - 1000;
				}
				else
				{
					i_Exp = iExp;
				}
			}
		}
		else if ( curGeneralVector[ 0 ].curStarLevel == 2 )
		{
			if ( ( curGeneralVector[ 0 ].evoLevel == 2 ) || ( curGeneralVector[ 0 ].evoLevel == 3 ) )
			{
				i_Exp = iExp - 1000;
			}
			else if ( curGeneralVector[ 0 ].evoLevel == 4 )
			{
				if ( iExp > 1000 + 1000 )
				{
					i_Exp = iExp - 1000 - 1000;
				}
				else
				{
					i_Exp = iExp - 1000;
				}
			}
		}
		else if ( curGeneralVector[ 0 ].curStarLevel == 3 )
		{
			i_Exp = iExp;
		}
	}
	else if ( curGeneralVector[ 0 ].maxStar == 4 )
	{
		if ( curGeneralVector[ 0 ].curStarLevel == 1 )
		{
			if ( ( curGeneralVector[ 0 ].evoLevel == 0 ) || ( curGeneralVector[ 0 ].evoLevel == 1 ) )
			{
				i_Exp = iExp;
			}
			else if ( curGeneralVector[ 0 ].evoLevel == 2 )
			{
				if ( iExp > 2500 )
				{
					i_Exp = iExp - 2500;
				}
				else
				{
					i_Exp = iExp;
				}
			}
		}
		else if ( curGeneralVector[ 0 ].curStarLevel == 2 )
		{
			if ( ( curGeneralVector[ 0 ].evoLevel == 2 ) || ( curGeneralVector[ 0 ].evoLevel == 3 ) )
			{
				i_Exp = iExp - 2500;
			}
			else if ( curGeneralVector[ 0 ].evoLevel == 4 )
			{
				if ( iExp > 2500 + 3000 )
				{
					i_Exp = iExp - 2500 - 3000;
				}
				else
				{
					i_Exp = iExp - 2500;
				}
			}			
		}
		else if ( curGeneralVector[ 0 ].curStarLevel == 3 )
		{
			if ( ( curGeneralVector[ 0 ].evoLevel == 4 ) || ( curGeneralVector[ 0 ].evoLevel == 5 ) )
			{
				i_Exp = iExp - 2500 - 3000 ;
			}
			else if ( curGeneralVector[ 0 ].evoLevel == 6 )
			{
				if ( iExp > 2500 + 3000 + 5500 )
				{
					i_Exp = iExp - 2500 - 3000 - 5500;
				}
				else
				{
					i_Exp = iExp - 2500 - 3000;
				}
			}
		}
		else if ( curGeneralVector[ 0 ].curStarLevel == 4 )
		{
			i_Exp = iExp;
		}
	}
	else if ( curGeneralVector[ 0 ].maxStar == 5 )
	{
		if ( curGeneralVector[ 0 ].curStarLevel == 1 )
		{
			if ( ( curGeneralVector[ 0 ].evoLevel == 1 ) || ( curGeneralVector[ 0 ].evoLevel == 0 ) )
			{
				i_Exp = iExp;
			}
			else if ( curGeneralVector[ 0 ].evoLevel == 2 )
			{
				if ( i_Exp >= 1000 )
				{
					i_Exp = iExp - 1000;
				}
				else
				{
					i_Exp = iExp;
				}
			}
		}
		else if ( curGeneralVector[ 0 ].curStarLevel == 2 )
		{
			if ( ( curGeneralVector[ 0 ].evoLevel == 2 ) || ( curGeneralVector[ 0 ].evoLevel == 3 ) )
			{
				i_Exp = iExp - 1000;				
			}
			else if ( curGeneralVector[ 0 ].evoLevel == 4 )
			{
				if ( i_Exp >= 8000 )
				{
					i_Exp = iExp - 8000;
				}
				else
				{
					i_Exp = iExp - 1000;
				}
			}
		}
		else if ( curGeneralVector[ 0 ].curStarLevel == 3 )
		{
			if ( ( curGeneralVector[ 0 ].evoLevel == 4 ) || ( curGeneralVector[ 0 ].evoLevel == 5 ) )
			{
				i_Exp = iExp - 8000;
			}
			else if ( curGeneralVector[ 0 ].evoLevel == 6 )
			{
				if ( i_Exp >= 19000 )
				{
					i_Exp = iExp - 19000;
				}
				else
				{
					i_Exp = iExp - 8000;
				}
			}
		}
		else if ( curGeneralVector[ 0 ].curStarLevel == 4 )
		{
			if ( ( curGeneralVector[ 0 ].evoLevel == 6 ) || ( curGeneralVector[ 0 ].evoLevel == 7 ) )
			{
				i_Exp = iExp - 19000 ;
			}
			else if ( curGeneralVector[ 0 ].evoLevel == 8 )
			{
				if ( i_Exp >= 19000 + 13000 )
				{
					i_Exp = iExp - 19000 - 13000;
				}
				else
				{
					i_Exp = iExp - 19000;
				}
			}
		}
		else if ( curGeneralVector[ 0 ].curStarLevel == 5 )
		{
			i_Exp = iExp;
		}
	}
	return i_Exp;
}

SESCStruct GeneralDetails::calcNeedNum()
{
	SESCStruct sESCStruct;
	memset(&sESCStruct, 0, sizeof(sESCStruct));
	localGeneralEvoVector = DataManager::getInstance()->localGeneralEvoVector();
	if ( localGeneralEvoVector.size() == 0 )
	{
		DataManager::getInstance()->GeneralEvoDataParser();
		localGeneralEvoVector = DataManager::getInstance()->localGeneralEvoVector();
	}
	for (unsigned int i = 0; i < localGeneralEvoVector.size(); i ++)
	{
		if ( curGeneralVector[ 0 ].maxStar == localGeneralEvoVector[ i ].maxStar )
		{
			if ( curGeneralVector[ 0 ].curStarLevel == localGeneralEvoVector[ i ].curStar )
			{
				int evoLevel = 0;
				if ( curGeneralVector[ 0 ].evoLevel == 0 )
				{
					evoLevel = 1;
				}
				else
				{
					evoLevel = curGeneralVector[ 0 ].evoLevel;
				}
				if ( evoLevel == localGeneralEvoVector[ i ].evoLevel )
				{				
					sESCStruct.sameName = localGeneralEvoVector[ i ].sameName;
					sESCStruct.exp = localGeneralEvoVector[ i ].needExp;
					sESCStruct.soul = localGeneralEvoVector[ i ].needSoul;
					sESCStruct.level = localGeneralEvoVector[ i ].levelLimit;
					sESCStruct.addEvo = localGeneralEvoVector[ i ].addEvo;
					sESCStruct.addStar = localGeneralEvoVector[ i ].addStar;
					sESCStruct.coin = localGeneralEvoVector[ i ].needCoin;
				}
			}
		}
	}
	return sESCStruct;
}

void GeneralDetails::showGeneral()
{
	topScrollView->removeAllChildrenWithCleanup(true);
	int cellCount = tempGeneralVector.size();
	auto cell_Size = cellSize * cellScale;
	Size szInnerContainer = topScrollView->getContentSize();
	int cellGap = 10;									// 滚动层cell间隔 
	int cellHeightGap = 0;								// 滚动层cell间隔 

	auto columuNum = cellCount / cellRow;
	if ( cellCount % cellRow != 0 )
	{
		columuNum ++;
	}
	auto height = (cellSize.height * cellScale + cellHeightGap) * columuNum ;
	height = (height > szInnerContainer.height) ? height : szInnerContainer.height;
	topScrollView->setInnerContainerSize(Size(szInnerContainer.width, height));

	for (int i = 0; i < cellCount; i ++)
	{
		auto cell = TrainCell::create();
		cell->setCellImage(tempGeneralVector[ i ].chinaSmallName, tempGeneralVector[ i ].maxStar);
		cell->setCellGeneralIndex(tempGeneralVector[ i ].roleID);
		cell->setCurStar(tempGeneralVector[ i ].curStarLevel, tempGeneralVector[ i ].maxStar);
		cell->setCellLevel(tempGeneralVector[ i ].level);
		cell->setExp(tempGeneralVector[ i ].level, tempGeneralVector[ i ].strongExp);
		cell->setCellName(tempGeneralVector[ i ].chinaName, tempGeneralVector[ i ].evoLevel );
		cell->setType(tempGeneralVector[ i ].jobType);
		cell->setCellUp(tempGeneralVector[ i ].isSelect);
		for (int z = 0; z < 6; z ++)
		{
			if (tempGeneralVector[ i ].equipID[ z ] != 0)
			{
				cell->setEquip(z , tempGeneralVector[ i ].equipID[ z ]);
			}			
		}
		cell->setPosition(Point( ( i % cellRow ) * (cellSize.width * cellScale + cellGap) + 37,
			height - ( i / cellRow + 1 ) * (cellSize.height * cellScale + cellHeightGap)));
		cell->trainCellUI->setTag( tempGeneralVector[ i ].PKID );
		cell->trainCellUI->addTouchEventListener(this, toucheventselector(GeneralDetails::panelTouchCallback));
		cell->trainCellUI->setTouchEnabled(true);
		cell->setScale(cellScale);
		topScrollView->addChild(cell);	
	}
}

void GeneralDetails::initMaidanData()
{
	if (DataManager::getInstance()->isGetMaidan())
	{
		
	}
	interMaidanVector = DataManager::getInstance()->interMaidanVector();
	localGeneralVector = DataManager::getInstance()->localGeneralProptyVector();
	if (localGeneralVector.size() == 0)
	{
		DataManager::getInstance()->generalDataParser();
		localGeneralVector = DataManager::getInstance()->localGeneralProptyVector();
	}
	GeneralProptyStruct generalStruct;
	memset(&generalStruct, 0, sizeof(generalStruct));
	curTempGeneralVector.clear();
	for (unsigned int i = 0; i < interMaidanVector.size(); i ++)
	{
		generalStruct.PKID = interMaidanVector[ i ].generalPKID;												// 主键ID
		generalStruct.roleID = localGeneralVector[ interMaidanVector[ i ].generalType - 10001 ].roleID;					// 角色ID
		string strName = localGeneralVector[ interMaidanVector[ i ].generalType - 10001 ].chinaName;					// 中文名称
		memset(generalStruct.chinaName, 0, sizeof(generalStruct.chinaName));
		memcpy(generalStruct.chinaName, strName.c_str(), strName.length());
		string strSmallName = localGeneralVector[ interMaidanVector[ i ].generalType - 10001 ].chinaSmallName;			// 拼音
		memset(generalStruct.chinaSmallName, 0, sizeof(generalStruct.chinaSmallName));
		memcpy(generalStruct.chinaSmallName, strSmallName.c_str(), strSmallName.length());
		generalStruct.curStarLevel = interMaidanVector[ i ].curStar;												// 当前星级
		generalStruct.maxStar = localGeneralVector[ interMaidanVector[ i ].generalType - 10001 ].maxStar;				// 最大星级
		generalStruct.jobType = localGeneralVector[ interMaidanVector[ i ].generalType - 10001 ].jobType;				// 职业类型
		generalStruct.level = interMaidanVector[ i ].generalLevel;												// 等级
		generalStruct.strongExp = interMaidanVector[ i ].generalExp;											// 强化经验值
		generalStruct.isSelect = interMaidanVector[ i ].isSelected;												// 是否上阵
		generalStruct.evoLevel = interMaidanVector[ i ].evoLevel;												// 进阶等级

// 		for (int z = 0; z < 6; z ++)
// 		{
// 			generalStruct.equipID[ z ] = interMaidanVector[ i ].EquipID[ z ];
// 		}
		curTempGeneralVector.push_back(generalStruct);
	}

	auto iter = curTempGeneralVector.begin();							// 移除武将自身、以上阵的武将
	while (iter != curTempGeneralVector.end()) 
	{
		if ( (iter->PKID == curGeneralVector[ 0 ].PKID) || (iter->isSelect != 0) ) 
		{
			iter = curTempGeneralVector.erase(iter);
		}
		else 
		{
			++iter;
		}
	}

	for (unsigned int i = 0; i < selectedHero.size(); i ++)
	{
		auto itor = curTempGeneralVector.begin();							// 移除已被选择的武将
		while (itor != curTempGeneralVector.end()) 
		{
			if ( itor->PKID == selectedHero[ i ].PKID ) 
			{
				itor = curTempGeneralVector.erase(itor);
			}
			else 
			{
				++itor;
			}
		}
	}
}

void GeneralDetails::initHeroPanel()
{
	auto trainUI = GUIReader::getInstance()->widgetFromJsonFile("UI/All/Train.ExportJson");	
	trainUI->setTag(TopPanelFlag);
	this->addChild(trainUI, TopPanelFlag);

	topScrollView = dynamic_cast<cocos2d::ui::ScrollView* >(Helper::seekWidgetByName(trainUI, "T_ScrollView"));

	auto close = dynamic_cast<Button *>(Helper::seekWidgetByName(trainUI, "Button_Close"));
	close->addTouchEventListener(this, toucheventselector(GeneralDetails::topCloseButton));

	auto movePanel = dynamic_cast<Layout* >(Helper::seekWidgetByName(trainUI, "Panel_Move"));
	auto topButtonPanel = dynamic_cast<Layout* >(Helper::seekWidgetByName(movePanel, "Panel_RSideButton_1"));
	auto trainSidePanel = dynamic_cast<Layout *>(Helper::seekWidgetByName(movePanel, "Panel_TrainSide"));
	auto trainSidePanel2 = dynamic_cast<Layout *>(Helper::seekWidgetByName(movePanel, "Panel_PreSet"));
	trainSidePanel2->setTouchEnabled(false);
	trainSidePanel2->setVisible(false);
	auto rightButtonPanel = dynamic_cast<Layout* >(Helper::seekWidgetByName(trainSidePanel, "Panel_RSideButton"));
	rightButtonPanel->setVisible(false);
	rightButtonPanel->setTouchEnabled(false);

	auto countString = __String::createWithFormat("%d/40", curTempGeneralVector.size());
	auto countLabel = dynamic_cast<Text* >(Helper::seekWidgetByName(trainUI, "Label_87"));
	countLabel->setText(countString->getCString());

	// 上面的按钮
	auto allButton1 = dynamic_cast<Button *>(Helper::seekWidgetByName(topButtonPanel, "T_Button_ALL_0"));
	allButton1->setTag(0);
	allButton1->addTouchEventListener(this, toucheventselector(GeneralDetails::typeButton));

	auto liButton1 = dynamic_cast<Button *>(Helper::seekWidgetByName(topButtonPanel, "T_Button_Li_0"));
	liButton1->setTag( 1 );
	liButton1->addTouchEventListener(this, toucheventselector(GeneralDetails::typeButton));

	auto zhiButton1 = dynamic_cast<Button *>(Helper::seekWidgetByName(topButtonPanel, "T_Button_Zhi_0"));
	zhiButton1->setTag( 2 );
	zhiButton1->addTouchEventListener(this, toucheventselector(GeneralDetails::typeButton));

	auto minButton1 = dynamic_cast<Button *>(Helper::seekWidgetByName(topButtonPanel, "T_Button_Min_0"));
	minButton1->setTag( 3 );
	minButton1->addTouchEventListener(this, toucheventselector(GeneralDetails::typeButton));


	auto button_Str = dynamic_cast<Button *>(Helper::seekWidgetByName(trainSidePanel, "Button_Str"));				// 强化
	button_Str->setVisible(false);

	auto button_PreSet = dynamic_cast<Button *>(Helper::seekWidgetByName(trainSidePanel, "Button_PreSet"));			// 预设
	button_PreSet->setVisible(false);

	typeButton(allButton1, TOUCH_EVENT_ENDED);
}

void GeneralDetails::onEnter()
{
	Scene::onEnter();

	initHeroData();
	skillButton(NULL, TOUCH_EVENT_ENDED);
	skillBasicButton(NULL, TOUCH_EVENT_ENDED);
}

void GeneralDetails::onExit()
{
	Scene::onExit();
}	