#include "TrainCell.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;

const char *imageExtension = ".png";
const float imgScale = 0.5f;

TrainCell::TrainCell(void):cellSelectFlag( -1 )
{
}

TrainCell::~TrainCell(void)
{
}

bool TrainCell::init()
{
	bool bRet = false;
	do 
	{

		localGeneralUpgradeVector = DataManager::getInstance()->localGeneralUpgradeVector();
		if (localGeneralUpgradeVector.size() == 0)
		{
			DataManager::getInstance()->generalUpgradeDataParser();
			localGeneralUpgradeVector = DataManager::getInstance()->localGeneralUpgradeVector();
		}
		m_hRole = 0;
		m_hRoleName = "";
		m_ptOriginleLoc = Point(0.0f, 0.0f);
		m_ptTouchLoc = Point(0.0f, 0.0f);

		trainCellUI = GUIReader::getInstance()->widgetFromJsonFile("UI/All/RoleFrame.ExportJson");
		CC_BREAK_IF( NULL == trainCellUI );
		setContentSize( trainCellUI->getContentSize() );
		this->addChild(trainCellUI);
		
		imageType = dynamic_cast<ImageView* >(trainCellUI->getChildByName("Image_Job"));
		progressBar = dynamic_cast<LoadingBar *>(Helper::seekWidgetByName(trainCellUI, "RF_ProgressBar_EXP"));
		imageSelectSign = dynamic_cast<ImageView* >(Helper::seekWidgetByName(trainCellUI, "Image_RoleChoose"));
		txtName = dynamic_cast<Text* >(trainCellUI->getChildByName("Label_Name"));
		curStarLevel = dynamic_cast<Text* >(trainCellUI->getChildByName("Label_PSStarNum"));
		level_Label = dynamic_cast<Text* >(Helper::seekWidgetByName(trainCellUI, "Label_PSrolelevel"));
		for (int i = 0; i < 6; i ++)
		{
			auto nameString = __String::createWithFormat("Image_Equip_%d", i + 1);
			imageWeapon[ i ] = dynamic_cast<ImageView* >(trainCellUI->getChildByName(nameString->getCString()));
		}
		for (int i = 0; i < 3; i ++)
		{
			auto jobString = __String::createWithFormat("Image_Job_%d", i + 1);
			typeImageView[ i ] = dynamic_cast<ImageView* >(trainCellUI->getChildByName(jobString->getCString()));
		}		
		
		bRet = true;

	} while ( 0 );

	return bRet;
}

void TrainCell::setCellName(const char *name, const int starLevel)
{
	auto nameString = __String::createWithFormat("%s+%d", name, starLevel);
	txtName->setText(nameString->getCString());
}

void TrainCell::setEquip(int index, int nameID)
{
// 	auto nameString = __String::createWithFormat("%d.png", nameID);
// 	imageWeapon[ index ]->loadTexture(nameString->getCString(), TextureResType::UI_TEX_TYPE_PLIST);
// 	imageWeapon[ index ]->setScale(0.3f);
}

void TrainCell::setCellLevel(const int level)
{
	auto starString = __String::createWithFormat("%d", level);
	level_Label->setColor(Color3B(223, 229, 135));
	level_Label->setText(starString->getCString());
}

void TrainCell::setCurStar(const int star, const int maxStar)
{
	ImageView* starImage[ 5 ];
	ImageView* starDarkImage[ 5 ];

	for (int i = 0; i < 5; i ++)
	{
		auto starString = __String::createWithFormat("GS_Star_%d", i + 1);
		auto starDarkString = __String::createWithFormat("GS_DarkStar_%d", i + 1);
		starImage[ i ] = dynamic_cast<ImageView* >(Helper::seekWidgetByName(trainCellUI, starString->getCString()));
		starDarkImage[ i ] = dynamic_cast<ImageView* >(Helper::seekWidgetByName(trainCellUI, starDarkString->getCString()));
		starImage[ i ]->setVisible(false);
		starDarkImage[ i ]->setVisible(false);
	}
	if ( maxStar == 3 )
	{
		for (int i = 0; i < 1; i ++)
		{
			starImage[ i ]->setVisible(false);
			starDarkImage[ i ]->setVisible(false);
		}

		for (int i = 1; i < 5; i++)
		{
			if ( i < star + 1 )
			{
				starImage[ i ]->setVisible(true);
			}
			else if ( i < maxStar + 1 )
			{
				starDarkImage[ i ]->setVisible(true);
			}	
		}
	}
	else
	{
		for (int i = 0; i < 5; i ++)
		{
			if ( i < star )
			{
				starImage[ i ]->setVisible(true);
			}
			else if ( i < maxStar )
			{
				starDarkImage[ i ]->setVisible(true);
			}
		}
	}		
}

void TrainCell::setCellUp(int id)
{
	cellSelectFlag = id;
	if (id != 0)
	{
		imageSelectSign->setVisible(true);
	}
	else
	{
		imageSelectSign->setVisible(false);
	}	
}

int TrainCell::getCellUp()
{
	return cellSelectFlag;
}

void TrainCell::setCellImage(const char *imgRoot, int maxStar)
{
// 	auto panelString = __String::createWithFormat("Panel_RF%dRole", maxStar);
// 	auto panelRole = dynamic_cast<Layout* >(Helper::seekWidgetByName(trainCellUI, panelString->getCString()));
	// 	panelRole->setVisible(true);
	auto nameString = __String::createWithFormat("%s.png", imgRoot);
	image = dynamic_cast<ImageView* >(Helper::seekWidgetByName(trainCellUI, "Image_RoleBG"));
	image->loadTexture(nameString->getCString(), TextureResType::UI_TEX_TYPE_PLIST);
	image->setScale( 75.0f / 95.0f );
}

void TrainCell::setCellGeneralIndex(int index)
{
	this->m_hRole = index;
}

void TrainCell::setType(int type)
{
// 	for (int i = 0; i < 3; i ++)
// 	{
// 		typeImageView[ i ]->setVisible(false);
// 	}
// 	typeImageView[ type - 1 ]->setVisible(true);
}

void TrainCell::setExp(int level, int exp)
{
	int curExp = calcGeneralExp(level, exp);
	int maxExp = localGeneralUpgradeVector[ level - 1 ].gNeedExp;
	float expPercnet = curExp * 1.0f / maxExp * 100;
	progressBar->setPercent(expPercnet);
}

void TrainCell::setCellGeneralName(const char *name)
{
	std::string str(name);	
	this->m_hRoleName = str;
}

int TrainCell::calcGeneralExp(int level, int exp)
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
