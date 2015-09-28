#include "EquipEnhance.h"
#include "cocostudio/CocoStudio.h"
#include "EEEquipCell.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;

const int svListGap = 5;											/* �б�Ԫ�ؼ�϶ */
const int svUnitCell = 50;											/* �б�Ԫ��Size */
const int svColumnNum = 7;											/* �б����7�� */
const int MaxRefineLv = 5;											/* ��߾����ȼ� */
const int MaxStrengthenLv = 50;										/* ���ǿ���ȼ� */
const Point ptAnimate[2] = {Point(565, 320), Point(550, 360)};

EquipEnhance::EquipEnhance(void)
{
}

EquipEnhance::~EquipEnhance(void)
{
}

Scene *EquipEnhance::Create()
{
	auto sce = Scene::create();
	auto layer = EquipEnhance::create();
	sce->addChild(layer);
	return sce;
}

bool EquipEnhance::init()
{
	if (false == Layer::init())
	{
		return false;
	}

	initPara();
	//loadStateBar();
	loadEnhanceFactory();
	loadRoleEquipInfo();
	showRoleEquipInfo();
	changeEnhanceMode(EE_Strengthen);
	loadEquipList();

	if (false == NewComer::isGuideDone(1003))					/* ����IDΪ3����δ��� */
	{
		_comer = NewComer::create(this, 1003, 1);
	}
	else if (false == NewComer::isGuideDone(1008))				/* ����IDΪ8����δ��� */
	{
		_comer = NewComer::create(this, 1008, 1);
	}
	else
	{
		_comer = NULL;
	}
	
	return true;
}

/* ������ʼ�� */
void EquipEnhance::initPara()
{
	_EE_EnMode = EE_Refine;
	_PointSetIndex = 0;
	_iEquipIndex = EE_Equip_Max;
	_iRefineCost = 0;
	_StateBar = NULL;

	_roleNode = Node::create();
	_roleNode->setPosition(185, 200);
	this->addChild(_roleNode, 100);

	_localRefineRule = DataManager::getInstance()->localEquipRefineVector();
}

/* ����״̬�� */
void EquipEnhance::loadStateBar()
{
	_StateBar = StateBarNode::getInstance(StatePower);
	_StateBar->setAnchorPoint(Point::ANCHOR_MIDDLE);
	_StateBar->setPosition(Point(90, 420));
	this->addChild(_StateBar, 10);
}

/* ����UI */
void EquipEnhance::loadEnhanceFactory()
{
	_EnhanceUI = GUIReader::getInstance()->widgetFromJsonFile("UI/All/StrongerEquip.ExportJson");
	this->addChild(_EnhanceUI);

	auto btnClose = dynamic_cast<Button *>(Helper::seekWidgetByName(_EnhanceUI, "Button_Close"));
	btnClose->addTouchEventListener(this, toucheventselector(EquipEnhance::btnResponse));
	btnClose->setTag(EE_Close);

	auto panelLeft = dynamic_cast<Layout *>(Helper::seekWidgetByName(_EnhanceUI, "G_Panel_Left"));
	//panelLeft->setScaleY(0.9f);
	for (int index = 0; index < EE_Equip_Max; index++)
	{
		auto strName = __String::createWithFormat("G_Equip%d_BG_0", index + 1);
		_imgEquip[index] = dynamic_cast<ImageView *>(Helper::seekWidgetByName(panelLeft, strName->getCString()));
		_imgEquip[index]->setVisible(false);
		_imgEquip[index]->addTouchEventListener(this, toucheventselector(EquipEnhance::imgResponse));
		_imgEquip[index]->setTag(index);
		_imgEquip[index]->setTouchEnabled(true);
	}

	for (int index = 0; index < 3; index++)
	{
		auto strName = __String::createWithFormat("Image_Job_%d", index + 1);
		_imgJob[index] = dynamic_cast<ImageView *>(Helper::seekWidgetByName(panelLeft, strName->getCString()));
	}

	auto btnPrev = dynamic_cast<Button *>(Helper::seekWidgetByName(panelLeft, "Button_LeftArrows"));
	btnPrev->addTouchEventListener(this, toucheventselector(EquipEnhance::btnResponse));
	btnPrev->setTag(EE_RolePrev);

	auto btnNext = dynamic_cast<Button *>(Helper::seekWidgetByName(panelLeft, "Button_RightArrows"));
	btnNext->addTouchEventListener(this, toucheventselector(EquipEnhance::btnResponse));
	btnNext->setTag(EE_RoleNext);

	_txtRole[EE_RoleName] = dynamic_cast<Text *>(Helper::seekWidgetByName(panelLeft, "Label_Name"));
	_txtRole[EE_RoleLv] = dynamic_cast<Text *>(Helper::seekWidgetByName(panelLeft, "Label_Level"));
	_txtRoleFight = dynamic_cast<TextAtlas *>(Helper::seekWidgetByName(panelLeft, "AtlasLabel_ATKNum"));
	_lbRoleExp = dynamic_cast<LoadingBar *>(Helper::seekWidgetByName(panelLeft, "G_ProgressBar_EXP"));

	auto panelRight = dynamic_cast<Layout *>(Helper::seekWidgetByName(_EnhanceUI, "Panel_SERight"));
	//panelRight->setScaleY(0.9f);
	_panelStr = dynamic_cast<Layout *>(Helper::seekWidgetByName(panelRight, "Panel_SEStr"));
	_panelRef = dynamic_cast<Layout *>(Helper::seekWidgetByName(panelRight, "Panel_SERefine"));

	_imgStrSelect = dynamic_cast<ImageView *>(Helper::seekWidgetByName(_panelStr, "Image_StroEquip"));
	_imgRefSelect = dynamic_cast<ImageView *>(Helper::seekWidgetByName(_panelRef, "Image_StroEquip_0"));

	auto btnS = dynamic_cast<Button *>(Helper::seekWidgetByName(_panelStr, "Button_Str"));
	btnS->addTouchEventListener(this, toucheventselector(EquipEnhance::btnResponse));
	btnS->setTag(EE_EquipS);

	auto btnS5 = dynamic_cast<Button *>(Helper::seekWidgetByName(_panelStr, "Button_One"));
	btnS5->addTouchEventListener(this, toucheventselector(EquipEnhance::btnResponse));
	btnS5->setTag(EE_EquipS5);

	auto btnR = dynamic_cast<Button *>(Helper::seekWidgetByName(_panelRef, "Button_Refine"));
	btnR->addTouchEventListener(this, toucheventselector(EquipEnhance::btnResponse));
	btnR->setTag(EE_EquipR);

	_txtStr[EE_StrName] = dynamic_cast<Text *>(Helper::seekWidgetByName(_panelStr, "Label_Equip_Name"));
	_txtStr[EE_StrLv0] = dynamic_cast<Text *>(Helper::seekWidgetByName(_panelStr, "Label_Equip_Level"));
	_txtStr[EE_StrLv1] = dynamic_cast<Text *>(Helper::seekWidgetByName(_panelStr, "Label_Equip_Level_0"));
	_txtStr[EE_StrProp0] = dynamic_cast<Text *>(Helper::seekWidgetByName(_panelStr, "Label_Propty"));
	_txtStr[EE_StrProp1] = dynamic_cast<Text *>(Helper::seekWidgetByName(_panelStr, "Label_Propty_0"));
	_txtStr[EE_StrCoin0] = dynamic_cast<Text *>(Helper::seekWidgetByName(_panelStr, "Label_SEPrice"));
	_txtStr[EE_StrCoin1] = dynamic_cast<Text *>(Helper::seekWidgetByName(_panelStr, "Label_SEPrice_0"));

	_lbRefineExp = dynamic_cast<LoadingBar *>(Helper::seekWidgetByName(_panelRef, "ProgressBar_SEPro"));
	_svEquipList = dynamic_cast<ui::ScrollView *>(Helper::seekWidgetByName(_panelRef, "ScrollView_Materia"));
	_svEquipList->setDirection(SCROLLVIEW_DIR_VERTICAL);
	_svEquipList->addTouchEventListener(this, toucheventselector(EquipEnhance::svEquipListResponse));

	_txtRef[EE_RefName0] = dynamic_cast<Text *>(Helper::seekWidgetByName(_panelRef, "Label_Equip_Name"));
	_txtRef[EE_RefName1] = dynamic_cast<Text *>(Helper::seekWidgetByName(_panelRef, "Label_Equip_Name_0"));
	_txtRef[EE_RefProp00] = dynamic_cast<Text *>(Helper::seekWidgetByName(_panelRef, "Label_Propty1"));
	_txtRef[EE_RefProp10] = dynamic_cast<Text *>(Helper::seekWidgetByName(_panelRef, "Label_Propty2"));
	_txtRef[EE_RefProp01] = dynamic_cast<Text *>(Helper::seekWidgetByName(_panelRef, "Label_Propty1_0"));
	_txtRef[EE_RefProp11] = dynamic_cast<Text *>(Helper::seekWidgetByName(_panelRef, "Label_Propty2_0"));
	_txtRef[EE_RefCoin] = dynamic_cast<Text *>(Helper::seekWidgetByName(_panelRef, "Label_SEPrice"));
}

/* ���ؽ�ɫװ����Ϣ */
void EquipEnhance::loadRoleEquipInfo()
{
	auto interPointSet = DataManager::getInstance()->interPointSetsVector();	/* ��ȡ�����佫 */
	if (0 == interPointSet.size())
	{
		DataManager::getInstance()->isGetPointSets();
		interPointSet = DataManager::getInstance()->interPointSetsVector();
	}

	auto localGeneral = DataManager::getInstance()->localGeneralProptyVector();/* ��ȡ�佫������Ϣ */
	if (localGeneral.size() == 0)
	{
		DataManager::getInstance()->generalDataParser();
		localGeneral = DataManager::getInstance()->localGeneralProptyVector();
	}

	auto localEquip = DataManager::getInstance()->localEquipProptyVector();		/* װ���������� */
	if (localEquip.size() == 0)
	{
		DataManager::getInstance()->equipDataParser();
		localEquip = DataManager::getInstance()->localEquipProptyVector();
	}

	auto localUpgrade = DataManager::getInstance()->localGeneralUpgradeVector();/* �佫�������� */
	if (localUpgrade.size() == 0)
	{
		DataManager::getInstance()->generalUpgradeDataParser();
		localUpgrade = DataManager::getInstance()->localGeneralUpgradeVector();
	}

	_PointSets.clear();

	for (unsigned int index = 0; index < interPointSet.size(); index ++)
	{
		EERoleInfo eeInfo = {0};
		auto interG = localGeneral[interPointSet[index].generalID - 10001];
		eeInfo.pkID = interPointSet[index].generalPKID;				// ����ID
		memcpy(eeInfo.name, interG.chinaSmallName, sizeof(interG.chinaSmallName));
		memcpy(eeInfo.cname, interG.chinaName, sizeof(interG.chinaName));
		eeInfo.job = interG.jobType - 1;							// ְҵ
		eeInfo.level = interPointSet[index].generalLevel;

		if ( DataManager::getInstance()->isGetGeneralProperty(eeInfo.pkID) )		// ��ȡ�����佫������	
		{
			auto generalDetialVec = DataManager::getInstance()->interGeneralVector();
			int curRoleID = interG.roleID + generalDetialVec[0].starLevel + generalDetialVec[0].evoLevel - 1 - 10001;
			int hpValue = localGeneral[curRoleID].initHP + localGeneral[curRoleID].hpGrowing * (generalDetialVec[0].level - 1);			// ������Ӧ����ֵ
			int atkValue = localGeneral[curRoleID].initAtk + localGeneral[curRoleID].atkGrowing * (generalDetialVec[0].level - 1);			// ������
			int mdValue = localGeneral[curRoleID].initMD + localGeneral[curRoleID].mdGrowing * (generalDetialVec[0].level - 1);			// ħ������
			int pdValue = localGeneral[curRoleID].initPD + localGeneral[curRoleID].pdGrowing * (generalDetialVec[0].level - 1);			// �������
			float incValues = 0.0f;
			float basicValues[] = { 0.1f, 0.2f, 0.2f, 0.3f };
			float incFValues[] = { 0.008f, 0.01f, 0.01f, 0.01f };
			int i_IncValues = 0;
			for (int k = 0; k < 4; k++)
			{
				if ( generalDetialVec[0].equipID[k] != 0 )
				{							
					if ( ( localEquip[generalDetialVec[0].equipID[k] - 94001].eColor == k + 1 ) && ( generalDetialVec[0].equipLevel[k] != 0 ) )
					{
						incValues += basicValues[k] + ( generalDetialVec[0].equipLevel[k] - 1 ) * incFValues[k];
					}		
					if ( k == 0)
					{
						i_IncValues = localEquip[generalDetialVec[0].equipID[0] - 94001].eHP;
						hpValue += i_IncValues * ( 1 + incValues) ;
					}
					else if ( k == 1 )
					{
						i_IncValues = localEquip[generalDetialVec[0].equipID[1] - 94001].ePD;
						pdValue += i_IncValues * ( 1 + incValues ) ;
					}
					else if ( k == 2 )
					{
						i_IncValues = localEquip[generalDetialVec[0].equipID[2] - 94001].eMD;
						mdValue += i_IncValues * ( 1 + incValues ) ;
					}
					else if ( k == 3 )
					{
						i_IncValues = localEquip[generalDetialVec[0].equipID[3] - 94001].eAtk;
						atkValue += i_IncValues * ( 1 + incValues ) ;
					}
				}
			}

			auto localSkillAddPropty = DataManager::getInstance()->localSkillAddProptyVec();
			if (localSkillAddPropty.size() == 0)
			{
				DataManager::getInstance()->skillUpgradeProptyAdd();
				localSkillAddPropty = DataManager::getInstance()->localSkillAddProptyVec();
			}
			if (generalDetialVec[0].skillLevel[0] != 0)
			{
				if (localGeneral[interG.roleID - 10001].maxStar == 5)
				{
					pdValue += localSkillAddPropty[0].ePD + generalDetialVec[0].skillLevel[0] * localSkillAddPropty[0].ePDLen;
				}
				else if (localGeneral[interG.roleID - 10001].maxStar == 4)
				{
					pdValue += localSkillAddPropty[0].dPD + generalDetialVec[0].skillLevel[0] * localSkillAddPropty[0].dPDLen;
				}
				else if (localGeneral[interG.roleID - 10001].maxStar == 3)
				{
					pdValue += localSkillAddPropty[0].cPD + generalDetialVec[0].skillLevel[0] * localSkillAddPropty[0].cPDLen;
				}
			}
			if (generalDetialVec[0].skillLevel[1] != 0)
			{
				if (localGeneral[interG.roleID - 10001].maxStar == 5)
				{
					mdValue += localSkillAddPropty[0].eMD + generalDetialVec[0].skillLevel[1] * localSkillAddPropty[0].eMDLen;
				}
				else if (localGeneral[interG.roleID - 10001].maxStar == 4)
				{
					mdValue += localSkillAddPropty[0].dMD + generalDetialVec[0].skillLevel[1] * localSkillAddPropty[0].dMDLen;
				}
				else if (localGeneral[interG.roleID - 10001].maxStar == 3)
				{
					mdValue += localSkillAddPropty[0].cMD + generalDetialVec[0].skillLevel[1] * localSkillAddPropty[0].cMDLen;
				}
			}
			if (generalDetialVec[0].skillLevel[2] != 0)
			{
				if (localGeneral[interG.roleID - 10001].maxStar == 5)
				{
					hpValue += localSkillAddPropty[0].eHP + generalDetialVec[0].skillLevel[2] * localSkillAddPropty[0].eHPLen;
				}
				else if (localGeneral[interG.roleID - 10001].maxStar == 4)
				{
					hpValue += localSkillAddPropty[0].dHP + generalDetialVec[0].skillLevel[2] * localSkillAddPropty[0].dHPLen;
				}
			}
			if (generalDetialVec[0].skillLevel[3] != 0)
			{
				if (localGeneral[interG.roleID - 10001].maxStar == 5)
				{
					atkValue += localSkillAddPropty[0].eATK + generalDetialVec[0].skillLevel[3] * localSkillAddPropty[0].eAtkLen;
				}
			}
			vector<int > growthVector;
			if ( DataManager::getInstance()->isGetGeneralGrowth(interPointSet[index].generalPKID) )
			{
				growthVector = DataManager::getInstance()->getGeneralGrowthVector();
			}
			eeInfo.fight = (hpValue + growthVector[1]) / 5 + atkValue + growthVector[0] + (pdValue + growthVector[2] + mdValue + growthVector[3])/2;
			eeInfo.exp = generalDetialVec[0].strExp * 100.0f / localUpgrade[eeInfo.level - 1].gNeedExp;

			for (int eIndex = 0; eIndex < EE_Equip_Max; eIndex ++)
			{
				auto eID = generalDetialVec[0].equipID[eIndex];
				if (0 != eID)
				{
					auto equip = localEquip[eID - 94001];
					equip.eColor --;
					equip.eLevel = generalDetialVec[0].equipLevel[eIndex];
					equip.ePKID = generalDetialVec[0].equipPKID[eIndex];
					equip.eExp = generalDetialVec[0].equipExp[eIndex];	/* װ������ֵ */
					memcpy(&eeInfo.Equips[eIndex], &equip, sizeof(EquipProptyStruct));
				}
			}
		}

		_PointSets.push_back(eeInfo);
	}
}

/* ���ؿ���װ���б� */
void EquipEnhance::loadEquipList()
{
	DataManager::getInstance()->isGetEquipData();					/* ��ȡ�ֿ�װ�� */
	auto interEquip = DataManager::getInstance()->interWareroomEquipVector();

	auto localEquip = DataManager::getInstance()->localEquipProptyVector();
	if (0 == localEquip.size())
	{
		DataManager::getInstance()->equipDataParser();
		localEquip = DataManager::getInstance()->localEquipProptyVector();
	}

	_EquipList.clear();

	for (unsigned int index = 0;index < interEquip.size();index++)
	{
		if ((interEquip[index].itemsID != 0) && (interEquip[index].isSelect == 0))
		{
			auto equip = localEquip[interEquip[index].itemsID - 94001];
			equip.eLevel = interEquip[index].itemsLevel;
			equip.ePKID = interEquip[index].itemPKID;

			_EquipList.push_back(equip);
		}
	}
}

/* ��ʾ��ɫװ�� */
void EquipEnhance::showRoleEquipInfo()
{
	if (_PointSetIndex > _PointSets.size())
	{
		return;
	}

	auto eeInfo = _PointSets[_PointSetIndex];

	for (int index = 0; index < 3; index++)
	{
		_imgJob[index]->setVisible(false);
	}
	_imgJob[eeInfo.job]->setVisible(true);

	for (int index = 0; index < EE_Equip_Max; index++)
	{
		if (0 != eeInfo.Equips[index].eID)							/* ��װ��:��ʾ */ 
		{
			auto strName = __String::createWithFormat("%d.png", eeInfo.Equips[index].eID);
			_imgEquip[index]->setVisible(true);
			_imgEquip[index]->loadTexture(strName->getCString(), TextureResType::UI_TEX_TYPE_PLIST);
			_imgEquip[index]->setScale(55.0f / 95.0f);
		}
		else														/* ��װ��:���� */ 
		{
			_imgEquip[index]->setVisible(false);
		}
	}

	auto role = RoleCreate::create(eeInfo.name, RoleCreMode_Preview, 0.9f);
	_roleNode->removeAllChildrenWithCleanup(true);
	_roleNode->addChild(role);

	_txtRole[EE_RoleName]->setText(eeInfo.cname);
	auto strLv = __String::createWithFormat("Lv%d", eeInfo.level);
	_txtRole[EE_RoleLv]->setText(strLv->getCString());
	_lbRoleExp->setPercent(eeInfo.exp);
	auto strFight = __String::createWithFormat("%d", eeInfo.fight);
	_txtRoleFight->setStringValue(strFight->getCString());
}

/* ��ʾװ��1-4��Ϣ */
void EquipEnhance::showStrEquipInfo()
{
	auto eInfo = _PointSets[_PointSetIndex].Equips[_iEquipIndex];
	_txtStr[EE_StrName]->setText(eInfo.eChinaName);

	stringstream stream;
	auto strLevel0 = __String::create("");
	auto strLevel1 = __String::create("");
	auto strProp0 = __String::create("");
	auto strProp1 = __String::create("");
	auto strCoin0 = __String::create("");
	auto strCoin1 = __String::create("");

	if (MaxStrengthenLv == eInfo.eLevel)							/* �Ѿ�ǿ������߼� */
	{
		auto improve = getStrengthenImprove(eInfo.eColor, eInfo.eLevel);
		strLevel0->appendWithFormat("%s", FontChina::getInstance()->getComString("MaxStrengthen")->getCString());

		if (0 != eInfo.eHP)
		{
			stream << FontChina::getInstance()->getComString("HP")->getCString() << (int)eInfo.eHP * improve;
		}
		else if (0 != eInfo.eAtk)
		{
			stream << FontChina::getInstance()->getComString("Attack")->getCString() << (int)eInfo.eAtk * improve;
		}
		else if (0 != eInfo.ePD)
		{
			stream << FontChina::getInstance()->getComString("PD")->getCString() << (int)eInfo.ePD * improve;
		}
		else
		{
			stream << FontChina::getInstance()->getComString("MD")->getCString() << (int)eInfo.eMD * improve;
		}
		strProp0->appendWithFormat("%s", stream.str().c_str());
	}
	else
	{
		auto improve0 = getStrengthenImprove(eInfo.eColor, eInfo.eLevel);
		auto improve1 = getStrengthenImprove(eInfo.eColor, eInfo.eLevel + 1);

		strLevel0->appendWithFormat("%s +%d", eInfo.eChinaName, eInfo.eLevel);
		strLevel1->appendWithFormat("%s +%d", eInfo.eChinaName, eInfo.eLevel + 1);

		if (0 != eInfo.eHP)
		{
			stream << FontChina::getInstance()->getComString("HP")->getCString();
			improve0 = eInfo.eHP * improve0;
			improve1 = eInfo.eHP * improve1;
		}
		else if (0 != eInfo.eAtk)
		{
			stream << FontChina::getInstance()->getComString("Attack")->getCString();
			improve0 = eInfo.eAtk * improve0;
			improve1 = eInfo.eAtk * improve1;
		}
		else if (0 != eInfo.ePD)
		{
			stream << FontChina::getInstance()->getComString("PD")->getCString();
			improve0 = eInfo.ePD * improve0;
			improve1 = eInfo.ePD * improve1;
		}
		else
		{
			stream << FontChina::getInstance()->getComString("MD")->getCString();
			improve0 = eInfo.eMD * improve0;
			improve1 = eInfo.eMD * improve1;
		}

		strProp0->appendWithFormat("%s%d", stream.str().c_str(), (int)improve0);
		strProp1->appendWithFormat("%s%d", stream.str().c_str(), (int)improve1);
		strCoin0->appendWithFormat("%d", getStrengthenCoin(eInfo.eColor, eInfo.eLevel));

		auto total = 0.0f;
		for (int i = 0; i < 5; i++)
		{
			total += getStrengthenCoin(eInfo.eColor, eInfo.eLevel + i);
		}
		strCoin1->appendWithFormat("%d", (int)total);
	}
	_txtStr[EE_StrLv0]->setText(strLevel0->getCString());
	_txtStr[EE_StrLv1]->setText(strLevel1->getCString());
	_txtStr[EE_StrProp0]->setText(strProp0->getCString());
	_txtStr[EE_StrProp1]->setText(strProp1->getCString());
	_txtStr[EE_StrCoin0]->setText(strCoin0->getCString());
	_txtStr[EE_StrCoin1]->setText(strCoin1->getCString());
}

/* ��ʾװ��5-6��Ϣ */
void EquipEnhance::showRefEquipInfo()
{
	auto eInfo = _PointSets[_PointSetIndex].Equips[_iEquipIndex];

	auto strName0 = __String::createWithFormat("%s +%d", eInfo.eChinaName, eInfo.eLevel);
	_txtRef[EE_RefName0]->setText(strName0->getCString());
	auto strName1 = __String::createWithFormat("%s +%d", eInfo.eChinaName, eInfo.eLevel + 1);
	_txtRef[EE_RefName1]->setText(strName1->getCString());

	auto improve1 = 0;												/* ���ӱ�����ǰ�� */
	auto improve2 = 0;												/* ��������ǰ�� */
	auto improve3 = 0;												/* �������ӷ����˺����� */
	auto improve4 = 0;												/* ���ˣ��� */
	auto strProp01 = __String::create("");
	auto strProp02 = __String::create("");
	auto strProp11 = __String::create("");
	auto strProp12 = __String::create("");

	if (MaxRefineLv == eInfo.eLevel)								/* �Ѿ���������߼� */
	{
		if (EE_Equip_5 == _iEquipIndex)
		{
			improve1 = (_localRefineRule[eInfo.eLevel - 1].eGrow1[eInfo.eColor] + eInfo.eAddCrit) * 100;
			improve2 = (_localRefineRule[eInfo.eLevel - 1].eGrow1[eInfo.eColor] + eInfo.eReduceCrit) * 100;
			strProp01->appendWithFormat("%s%d%%", FontChina::getInstance()->getComString("APR")->getCString(), improve1);
			strProp02->appendWithFormat("%s%d%%", FontChina::getInstance()->getComString("RPR")->getCString(), improve2);
		}
		else
		{
			improve1 = (_localRefineRule[eInfo.eLevel - 1].eGrow2[eInfo.eColor] + 1) * eInfo.eAddRealHurt;
			improve2 = (_localRefineRule[eInfo.eLevel - 1].eGrow2[eInfo.eColor] + 1) * eInfo.eReduceHurt;
			strProp01->appendWithFormat("%s%d", FontChina::getInstance()->getComString("ARH")->getCString(), improve1);
			strProp02->appendWithFormat("%s%d", FontChina::getInstance()->getComString("RRH")->getCString(), improve2);
		}

		_lbRefineExp->setPercent(100);
	}
	else
	{
		if (EE_Equip_5 == _iEquipIndex)
		{
			auto temp = (0 == eInfo.eLevel) ? 0 : _localRefineRule[eInfo.eLevel - 1].eGrow1[eInfo.eColor];
			improve1 = (temp + eInfo.eAddCrit) * 100;
			improve2 = (temp + eInfo.eReduceCrit) * 100;
			improve3 = (_localRefineRule[eInfo.eLevel].eGrow1[eInfo.eColor] + eInfo.eAddCrit) * 100;
			improve4 = (_localRefineRule[eInfo.eLevel].eGrow1[eInfo.eColor] + eInfo.eReduceCrit) * 100;
			strProp01->appendWithFormat("%s%d%%", FontChina::getInstance()->getComString("APR")->getCString(), improve1);
			strProp02->appendWithFormat("%s%d%%", FontChina::getInstance()->getComString("RPR")->getCString(), improve2);
			strProp11->appendWithFormat("%s%d%%", FontChina::getInstance()->getComString("APR")->getCString(), improve3);
			strProp12->appendWithFormat("%s%d%%", FontChina::getInstance()->getComString("RPR")->getCString(), improve4);
		}
		else
		{
			auto temp = (0 == eInfo.eLevel) ? 0 : _localRefineRule[eInfo.eLevel - 1].eGrow2[eInfo.eColor];
			improve1 = (temp + 1) * eInfo.eAddRealHurt;
			improve2 = (temp + 1) * eInfo.eReduceHurt;
			improve3 = (_localRefineRule[eInfo.eLevel].eGrow2[eInfo.eColor] + 1) * eInfo.eAddRealHurt;
			improve4 = (_localRefineRule[eInfo.eLevel].eGrow2[eInfo.eColor] + 1) * eInfo.eReduceHurt;
			strProp01->appendWithFormat("%s%d%%", FontChina::getInstance()->getComString("ARH")->getCString(), improve1);
			strProp02->appendWithFormat("%s%d%%", FontChina::getInstance()->getComString("RPR")->getCString(), improve2);
			strProp11->appendWithFormat("%s%d%%", FontChina::getInstance()->getComString("ARH")->getCString(), improve3);
			strProp12->appendWithFormat("%s%d%%", FontChina::getInstance()->getComString("RRH")->getCString(), improve4);
		}

		auto per = eInfo.eExp * 100.0f / _localRefineRule[eInfo.eLevel].eExp[eInfo.eColor];
		per = int(per + 0.5f);
		per = (per > 100) ? 100 : per;
		_lbRefineExp->setPercent(per);
	}

	_txtRef[EE_RefProp00]->setText(strProp01->getCString());
	_txtRef[EE_RefProp10]->setText(strProp02->getCString());
	_txtRef[EE_RefProp01]->setText(strProp11->getCString());
	_txtRef[EE_RefProp11]->setText(strProp12->getCString());
	_txtRef[EE_RefCoin]->setText("0");
	_EquipUsing.clear();
	_iRefineCost = 0;
}

/* ��ʾ����װ������ */
void EquipEnhance::showEquipUsable()
{
	_svEquipList->removeAllChildrenWithCleanup(true);
	auto svSZ = _svEquipList->getInnerContainerSize();
	auto height = (_EquipList.size() / svColumnNum + 1) * (svListGap + svUnitCell) + svListGap;
	if (height < svSZ.height)
	{
		height = svSZ.height;
	}
	_svEquipList->setInnerContainerSize(Size(svSZ.width, height));

	for (unsigned int index = 0;index < _EquipList.size();index ++)
	{
		auto equip = _EquipList[index];
		auto cell = EEEquipCell::Create(equip);
		cell->setPosition(index%svColumnNum * (svListGap + svUnitCell), height - (svListGap + svUnitCell) * (index/svColumnNum + 1));
		_svEquipList->addChild(cell);
		cell->setTag(index);
		cell->setScale(50.0f / 98.0f);
	}
}

/* ��ʾ��ʾ */
void EquipEnhance::showNotice(std::string strNotice)
{
	auto notice = PromptBox::getInstance(strNotice);
	notice->setFade();
	this->addChild(notice);
}

void EquipEnhance::btnResponse(Ref* ref, TouchEventType type)
{
	if (TouchEventType::TOUCH_EVENT_ENDED != type)
	{
		return;
	}

	ToolFunc::playEffectFile(Click);

	auto btn = (Button *)ref;
	auto tag = (EEButton)btn->getTag();

	if (EE_Close == tag)
	{
		if (false == NewComer::isGuideDone(1003))
		{
			if (1 == NewComer::getCurGuideStep())					/* δ���װ�� */
			{
				NewComer::setCurGuideStep(-1);
			}
		}
		if (false == NewComer::isGuideDone(1008))					/* ����IDΪ8����δ��� */
		{
			NewComer::setCurGuideStep(0);
		}

		Director::getInstance()->replaceScene(MainScene::scene());
	}
	else
	{
		switch (tag)
		{
		case EquipEnhance::EE_RolePrev:
			_PointSetIndex = (_PointSetIndex + 1)%_PointSets.size();
			clearPanel();
			showRoleEquipInfo();
			_iEquipIndex = EE_Equip_Max;
			break;
		case EquipEnhance::EE_RoleNext:
			_PointSetIndex = (_PointSetIndex - 1 + _PointSets.size())%_PointSets.size();
			clearPanel();
			showRoleEquipInfo();
			_iEquipIndex = EE_Equip_Max;
			break;
		case EquipEnhance::EE_EquipS:
			btnEquipStrengthen();
			break;
		case EquipEnhance::EE_EquipS5:
			btnEquipStrengthen5();
			break;
		case EquipEnhance::EE_EquipR:
			btnEquipRefine();
			break;
		}
	}
}

/* װ��ǿ�� */
void EquipEnhance::btnEquipStrengthen()
{
	if ((EE_Equip_5 <= _iEquipIndex) || (_iEquipIndex >= EE_Equip_Max))/* û��ѡ��Ҫǿ����װ�� */
	{
		return;
	}

	auto eInfo = _PointSets[_PointSetIndex].Equips[_iEquipIndex];
	if (MaxStrengthenLv <= eInfo.eLevel)							/* ��ǿ������߼� */
	{
		showNotice(FontChina::getInstance()->getComString("MaxStrengthen")->getCString());
		return;
	}

	if (_PointSets[_PointSetIndex].level > eInfo.eLevel)
	{
		DataManager::getInstance()->isGetPlayerInfo();
		auto playerInfo = DataManager::getInstance()->interPlayerInfoVector();
		auto coin = getStrengthenCoin(eInfo.eColor, eInfo.eLevel);
		if (coin < playerInfo[0].coinValue)
		{
			auto result = DataManager::getInstance()->isEnhanceEquip(eInfo.ePKID, eInfo.eLevel + 1, coin);
			if (true == result)
			{
				_PointSets[_PointSetIndex].Equips[_iEquipIndex].eLevel = eInfo.eLevel + 1;
				showStrEquipInfo();									/* ˢ����Ϣ��ʾ */
				EnhanceAnimate();

				if (NULL != _StateBar)
				{
					_StateBar->refreshVaule();
				}
			}
			else
			{
				showNotice(FontChina::getInstance()->getComString("StrengthenError")->getCString());
			}
		}
		else
		{
			showNotice(FontChina::getInstance()->getComString("NoCoin")->getCString());
		}
	}
	else
	{
		showNotice(FontChina::getInstance()->getComString("MaxStrengthenLv")->getCString());
	}
}

/* װ��ǿ��5�� */
void EquipEnhance::btnEquipStrengthen5()
{
	if ((EE_Equip_5 <= _iEquipIndex) || (_iEquipIndex >= EE_Equip_Max))/* û��ѡ��Ҫǿ����װ�� */
	{
		return;
	}

	auto eInfo = _PointSets[_PointSetIndex].Equips[_iEquipIndex];
	if (MaxStrengthenLv <= eInfo.eLevel)							/* ��ǿ������߼� */
	{
		showNotice(FontChina::getInstance()->getComString("MaxStrengthen")->getCString());
		return;
	}

	if (_PointSets[_PointSetIndex].level <= eInfo.eLevel)
	{
		showNotice(FontChina::getInstance()->getComString("MaxStrengthenLv")->getCString());
	}

	int cost = 0;													/* ������� */
	auto maxEnhanceNum = 5;											/* ���5��ǿ�� */
	int level = eInfo.eLevel;
	auto playerInfo = DataManager::getInstance()->interPlayerInfoVector();
	for (;level < _PointSets[_PointSetIndex].level && maxEnhanceNum > 0;level++, maxEnhanceNum--)
	{
		cost += getStrengthenCoin(eInfo.eColor, level);
		if (playerInfo[0].coinValue < cost)							/* ��Ҳ��� */
		{
			auto strNotice = __String::create("");
			auto strNoCoin = FontChina::getInstance()->getComString("NoCoin")->getCString();
			strNotice->append(strNoCoin);
			if (level > eInfo.eLevel)								/* ����������һ�� */
			{
				auto strLevel = FontChina::getInstance()->getComString("StrengthenLvLimit")->getCString();
				auto strCoin = FontChina::getInstance()->getComString("StrengthenLvCoin")->getCString();
				strNotice->appendWithFormat("\r\n%s%d\r\n%s%d", strLevel, level, strCoin, cost);
			}
			showNotice(strNotice->getCString());
			break;
		}
	}

	if ((maxEnhanceNum > 0)	&& (level > eInfo.eLevel))				/* ǿ��������ȼ� */
	{
		auto strMaxLv = FontChina::getInstance()->getComString("MaxStrengthenLv")->getCString();
		auto strLevel = FontChina::getInstance()->getComString("StrengthenLvLimit")->getCString();
		auto strCoin = FontChina::getInstance()->getComString("StrengthenLvCoin")->getCString();
		auto strNotice = __String::createWithFormat("%s\r\n%s%d\r\n%s%d", strMaxLv, strLevel, level, strCoin, cost);

		showNotice(strNotice->getCString());
	}

	if (level > eInfo.eLevel)										/* ����������һ�� */
	{
		if (false == NewComer::isGuideDone(1003))
		{
			if (2 == NewComer::getCurGuideStep())
			{
				_comer->removeFromParentAndCleanup(true);
				NewComer::setCurGuideStep();
				_comer = NULL;
			}
		}

		auto result = DataManager::getInstance()->isEnhanceEquip(eInfo.ePKID, level, cost);
		if (true == result)
		{
			_PointSets[_PointSetIndex].Equips[_iEquipIndex].eLevel = level;
			showStrEquipInfo();										/* ˢ����Ϣ��ʾ */
			EnhanceAnimate();

			if (NULL != _StateBar)
			{
				_StateBar->refreshVaule();
			}
		}
		else
		{
			showNotice(FontChina::getInstance()->getComString("StrengthenError")->getCString());
		}
	}
}

/* װ������ */
void EquipEnhance::btnEquipRefine()
{
	if ((EE_Equip_5 > _iEquipIndex) || (_iEquipIndex >= EE_Equip_Max))/* û��ѡ��Ҫ������װ�� */
	{
		return;
	}

	auto eInfo = _PointSets[_PointSetIndex].Equips[_iEquipIndex];
	if (MaxRefineLv <= eInfo.eLevel)								/* �Ѿ�������߼� */
	{
		showNotice(FontChina::getInstance()->getComString("MaxRefine")->getCString());
		return;
	}

	if (0 == _EquipUsing.size())									/* δѡ��װ������ */
	{
		showNotice(FontChina::getInstance()->getComString("RefineEquipSelect")->getCString());
		return;
	}

	/* �ѱ���������ֵ�ӵ�װ���� */
	auto exp = 0;
	auto level = eInfo.eLevel + 1;
	auto per = _lbRefineExp->getPercent() * 1.0f / 100.0f;
	if (100 > _lbRefineExp->getPercent())							/* δ����������ǰ�������㾫����ľ���ֵ */
	{
		level = eInfo.eLevel;
		exp = per * _localRefineRule[eInfo.eLevel].eExp[eInfo.eColor];
	}

	auto playerInfo = DataManager::getInstance()->interPlayerInfoVector();
	if (playerInfo[0].coinValue >= _iRefineCost)					/* ����㹻 */
	{
		std::vector<int > equipPKID;
		for (unsigned int index = 0;index < _EquipUsing.size();index++)
		{
			equipPKID.push_back(_EquipUsing[index]);				/* ��ȡװ�����ϵ�pkid */
		}

		auto result = DataManager::getInstance()->isRefineEquip(eInfo.ePKID, level, equipPKID, exp, _iRefineCost);
		if (true == result)
		{
			removeEquipUsed();
			showEquipUsable();
			EnhanceAnimate();

			_PointSets[_PointSetIndex].Equips[_iEquipIndex].eExp = exp;
			_PointSets[_PointSetIndex].Equips[_iEquipIndex].eLevel = level;
			showRefEquipInfo();										/* ˢ����Ϣ��ʾ */

			if (NULL != _StateBar)
			{
				_StateBar->refreshVaule();
			}

			if (false == NewComer::isGuideDone(1008))				/* ����IDΪ8����δ��� */
			{
				if (3 == NewComer::getCurGuideStep())
				{
					auto cpID = NewComer::getCurGuideID();
					cpID = cpID | 0x010000;							/* ���IDΪ0������ */
					NewComer::setCurGuideID(cpID);
					NewComer::setCurGuideStep(0);					/* ����ID���� */

					_comer->removeFromParentAndCleanup(true);
				}
			}
		}
		else
		{
			showNotice(FontChina::getInstance()->getComString("RefineError")->getCString());
		}
	}
	else
	{
		showNotice(FontChina::getInstance()->getComString("NoCoin")->getCString());
	}
}

void EquipEnhance::imgResponse(Ref* ref, TouchEventType type)
{
	if (TouchEventType::TOUCH_EVENT_ENDED != type)
	{
		return;
	}

	auto img = (ImageView *)ref;
	auto tag = (EEImgEquip)img->getTag();

	auto eID = _PointSets[_PointSetIndex].Equips[tag].eID;
	if (0 == eID)													/* ��װ��������ʾ��Ϣ */
	{
		return;
	}

	_iEquipIndex = tag;

	if (false == NewComer::isGuideDone(1003))
	{
		if (tag != EE_Equip_4)
		{
			return;
		}
		if (1 == NewComer::getCurGuideStep())
		{
			_comer->removeFromParentAndCleanup(true);
			NewComer::setCurGuideStep();
			_comer = NewComer::create(this, 1003, 2);
		}
	}

	if (false == NewComer::isGuideDone(1008))					/* ����IDΪ8����δ��� */
	{
		if (tag != EE_Equip_5)
		{
			return;
		}
		if (1 == NewComer::getCurGuideStep())
		{
			_comer->removeFromParentAndCleanup(true);
			NewComer::setCurGuideStep();
			_comer = NewComer::create(this, 1008, 2);
		}
	}

	if (tag < EE_Equip_5)
	{
		_imgStrSelect->setVisible(true);
		auto strName = __String::createWithFormat("%d.png", eID);
		_imgStrSelect->loadTexture(strName->getCString(), TextureResType::UI_TEX_TYPE_PLIST);
		changeEnhanceMode(EE_Strengthen);
		showStrEquipInfo();
	}
	else
	{
		_imgRefSelect->setVisible(true);
		auto strName = __String::createWithFormat("%d.png", eID);
		_imgRefSelect->loadTexture(strName->getCString(), TextureResType::UI_TEX_TYPE_PLIST);
		changeEnhanceMode(EE_Refine);
		showRefEquipInfo();
		showEquipUsable();
	}
}

void EquipEnhance::svEquipListResponse(Ref* ref, TouchEventType type)
{
	if (TouchEventType::TOUCH_EVENT_ENDED != type)
	{
		return;
	}

	auto sv = (ui::ScrollView*)ref;
	auto sz = sv->getInnerContainerSize();
	auto ptTouch = sv->getTouchEndPos();
	ptTouch = sv->getInnerContainer()->convertToNodeSpace(ptTouch);
	ptTouch.y = sz.height - ptTouch.y;

	auto szSv = sv->getInnerContainerSize();
	if (((int)ptTouch.x % (svUnitCell + svListGap) > svUnitCell) || /* �㵽��϶ */
		((int)ptTouch.y % (svUnitCell + svListGap) < svListGap))
	{
		return;
	}

	auto indexX = (unsigned int)ptTouch.x / (svUnitCell + svListGap);
	auto indexY = (unsigned int)ptTouch.y / (svUnitCell + svListGap);
	auto cell = (EEEquipCell*)sv->getChildByTag(indexX + svColumnNum * indexY);

	if (NULL != cell)
	{
		auto info = cell->getEquipCellInfo();						/* ����װ�� */
		auto onInfo = _PointSets[_PointSetIndex].Equips[_iEquipIndex];/* Ҫ������װ�� */
		if (true == cell->changeStatus())							/* ѡ�� */
		{
			if (false == NewComer::isGuideDone(1008))				/* ����IDΪ8����δ��� */
			{
				if (2 == NewComer::getCurGuideStep())
				{
					_comer->removeFromParentAndCleanup(true);
					NewComer::setCurGuideStep();
					_comer = NewComer::create(this, 1008, 3);
				}
			}

			auto oldPer = _lbRefineExp->getPercent();
			if (100 == oldPer)										/* �����ѱ��� */
			{
				cell->changeStatus();
				return;
			}

			auto curPer = info.eExp * 100.0f / _localRefineRule[onInfo.eLevel].eExp[onInfo.eColor];
			curPer = (int)(curPer + 0.5f + oldPer);
			curPer = (curPer > 100) ? 100 : curPer;
			_lbRefineExp->setPercent(curPer);
			cell->setRealExp(curPer - oldPer);						/* ����ѡ�е�װ������ľ��� */	

			auto cost = (curPer - oldPer)/100.0f * _localRefineRule[onInfo.eLevel].eCoin[onInfo.eColor];
			_iRefineCost += (int)cost;
			auto strCoin = __String::createWithFormat("%d", _iRefineCost);
			_txtRef[EE_RefCoin]->setText(strCoin->getCString());	/* ˢ�����ĵĽ�� */

			_EquipUsing.push_back(info.ePKID);
		}
		else														/* ȡ��ѡ�� */
		{
			auto cost = cell->getRealExp() * 1.0f/100.0f * _localRefineRule[onInfo.eLevel].eCoin[onInfo.eColor];
			_iRefineCost -= (int)cost;
			auto strCoin = __String::createWithFormat("%d", _iRefineCost);
			_txtRef[EE_RefCoin]->setText(strCoin->getCString());	/* ˢ�����ĵĽ�� */

			auto oldPer = _lbRefineExp->getPercent();
			_lbRefineExp->setPercent(oldPer - cell->getRealExp());
			cell->setRealExp(0);									/* ����ѡ�е�װ������ľ��� */	

			auto pos = find(_EquipUsing.begin(), _EquipUsing.end(), info.ePKID);
			if (pos != _EquipUsing.end())
			{
				_EquipUsing.erase(pos);								/* ��ѡ��װ���б� */
			}
		}
	}
}

/* ǿ��������ģʽ�л� */
void EquipEnhance::changeEnhanceMode(EEMode mode)
{
	if (_EE_EnMode == mode)
	{
		return;														/* ��ǰ����Ҫת����ģʽ */
	}

	if (EE_Strengthen == mode)										/* ǿ��ģʽ */
	{
		_panelStr->setVisible(true);
		_panelRef->setVisible(false);
		_panelStr->setLocalZOrder(1);
		_panelRef->setLocalZOrder(0);
	}

	if (EE_Refine == mode)											/* ����ģʽ */
	{
		_panelStr->setVisible(false);
		_panelRef->setVisible(true);
		_panelStr->setLocalZOrder(0);
		_panelRef->setLocalZOrder(1);
	}

	_EE_EnMode = mode;
	_EquipUsing.clear();
	_iRefineCost = 0;
}

/*********************************************************************
** ���ܣ�		��ȡװ��ǿ����������
** ���������	EquipGradeEnum grade��װ��Ʒ��
**				int level��װ���ȼ�
** ����ֵ��		float: 
** �޸ļ�¼��	
*********************************************************************/
float EquipEnhance::getStrengthenImprove(int grade, int level)
{
	if (0 >= level)
	{
		return 1.0f;
	}

	double add[EquipGradeMax] = {0.1f, 0.2f, 0.2f, 0.3f};
	double factor[EquipGradeMax] = {0.008f, 0.01f, 0.01f, 0.01f};

	auto fRet = add[grade] + (level - 1) * factor[grade];

	return fRet + 1;
}

/*********************************************************************
** ���ܣ�		��ȡװ��ǿ���������
** ���������	EquipGradeEnum grade��װ��Ʒ��
**				int level��װ���ȼ�
** ����ֵ��		int
** �޸ļ�¼��	
*********************************************************************/
int	EquipEnhance::getStrengthenCoin(int grade, int level)
{
	int iRet = 1;

	if (level >= 50)
	{
		return 0;
	}

	int add[EquipGradeMax] = {60, 80, 100, 150};
	int factor[EquipGradeMax] = {5, 8, 14, 20};
	iRet = add[grade] + level * level * factor[grade];

	return iRet;
}

/* ���װ����Ϣ��ʾ */
void EquipEnhance::clearPanel()
{
	if (EE_Refine == _EE_EnMode)
	{
		_imgRefSelect->setVisible(false);
		_svEquipList->removeAllChildrenWithCleanup(true);
		for (int index = 0; index < EE_RefMax; index++)
		{
			_txtRef[index]->setText("");
		}
	}
	else
	{
		_imgStrSelect->setVisible(false);
		for (int index = 0; index < EE_StrMax; index++)
		{
			_txtStr[index]->setText("");
		}
	}
}

/* �Ƴ�ʹ�õ���װ�� */
void EquipEnhance::removeEquipUsed()
{
	unsigned int index = 0;
	while (index < _EquipList.size())
	{
		auto pkid = _EquipList[index].ePKID;
		auto pos = find(_EquipUsing.begin(), _EquipUsing.end(), pkid);
		if (pos != _EquipUsing.end())
		{
			_EquipList.erase(_EquipList.begin() + index);
		}
		else
		{
			index++;
		}
	}

	_EquipUsing.clear();
	_iRefineCost = 0;
}

/* ǿ������������ */
void EquipEnhance::EnhanceAnimate()
{
	auto animation = Animation::create();

	for (int index = 0;index < 12;index ++)
	{
		auto str = __String::createWithFormat("res/EquipEnhance/EnhanceAnimate%d.png", index);
		animation->addSpriteFrameWithFile(str->getCString());
	}

	animation->setDelayPerUnit(0.05f);
	animation->setRestoreOriginalFrame(true);
	animation->setLoops(3);

	auto spAni = Sprite::create();
	spAni->setPosition(ptAnimate[_EE_EnMode]);
	this->addChild(spAni);
	auto animate = Animate::create(animation);
	auto seq = Sequence::createWithTwoActions(animate, CCCallFuncN::create(CC_CALLBACK_1(EquipEnhance::EnhanceAnimateCB, this)));
	spAni->runAction(seq);
	//spAni->runAction(animate);
}

/* ǿ�������������ص����� */
void EquipEnhance::EnhanceAnimateCB(Node *who)
{
	who->removeFromParentAndCleanup(true);
}