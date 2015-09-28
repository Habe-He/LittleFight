#include "SelectRoleCell.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;

const cocos2d::Size szImage = cocos2d::Size(80, 80);
const char *uiSelectRoleCellRoot = "UI/All/RoleFrame.ExportJson";
const char *imageSelectRoleCellName = "Image";
const char *nameSelectRoleCellText = "Name_Label";
const char *levelSelectRoleCellText = "Level_Label";
const char *starSelectRoleCellText = "Star_Label";
const float img_scale_down = 0.8f;
const float img_scale_up = 1.0f;
const char *imageExtension_S = ".png";

SelectRoleCell::SelectRoleCell(void)
{
	m_WidgetTrainCell = NULL;
	m_fRateX = 0.0f;
	m_fRateY = 0.0f;
}


SelectRoleCell::~SelectRoleCell(void)
{
	if ( NULL != m_WidgetTrainCell )
	{
		//delete m_WidgetTrainCell;
	}
}

static SelectRoleCell* create()
{
	SelectRoleCell *pRet = new SelectRoleCell();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool SelectRoleCell::init()
{
	do 
	{
		m_WidgetTrainCell = GUIReader::getInstance()->widgetFromJsonFile(uiSelectRoleCellRoot);
		CC_BREAK_IF( NULL == m_WidgetTrainCell );
		this->addChild(m_WidgetTrainCell);

		roleImage = static_cast<ImageView* >(Helper::seekWidgetByName(m_WidgetTrainCell, imageSelectRoleCellName));

	} while ( 0 );

	setContentSize( m_WidgetTrainCell->getContentSize() );
	return true;
}

/*********************************************************************
** 功能：		设置单元项姓名
** 输入参数：	const char *name：设置的名字
** 返回值： 	无
** 修改记录：	
*********************************************************************/
void SelectRoleCell::setCellName(const char *name)
{
	if ( NULL == m_WidgetTrainCell )
	{
		return;
	}

	auto txtName = dynamic_cast<Text* >(Helper::seekWidgetByName(m_WidgetTrainCell, nameSelectRoleCellText));
	std::string str(name);	
	txtName->setText(str);
	txtName->setFontSize(12.0f);
}

/*********************************************************************
** 功能：		设置单元项等级
** 输入参数：	const char *country：设置的国籍
** 返回值： 	无
** 修改记录：	
*********************************************************************/
void SelectRoleCell::setCellLevel(const int Level)
{
	if ( NULL == m_WidgetTrainCell )
	{
		return;
	}

	auto txtCountry = dynamic_cast<Text* >(Helper::seekWidgetByName(m_WidgetTrainCell, levelSelectRoleCellText));
	std::stringstream stream;
	stream << Level;
	std::string str = stream.str();
	txtCountry->setText(str);
}

/*********************************************************************
** 功能：		设置单元项星级
** 输入参数：	const int star：设置的星级
** 返回值： 	无
** 修改记录：	
*********************************************************************/
void SelectRoleCell::setCellStar(const int star)
{
	if ( NULL == m_WidgetTrainCell )
	{
		return;
	}

	auto txtStar= dynamic_cast<Text* >(Helper::seekWidgetByName(m_WidgetTrainCell, starSelectRoleCellText));
	std::stringstream stream;
	stream << star;
	std::string str = stream.str();
	txtStar->setText(str);
}

/*********************************************************************
** 功能：		设置人物编号
** 输入参数：	const int star：设置的编号
** 返回值： 	无
** 修改记录：	
*********************************************************************/
void SelectRoleCell::setCellNum(const int star)
{
	if ( NULL == m_WidgetTrainCell )
	{
		return;
	}

	strNum = star;
}

int SelectRoleCell::getCellNum()
{
	int Num = 0;
	
	switch (Num)
	{
	case 1:
		Num = 1;
		break;
	case 2:
		Num = 2;
		break;
	default:
		break;
	}

	return Num;
}

/*********************************************************************
** 功能：		设置单元项图片
** 输入参数：	const char *imgRoot：图片路径
** 返回值： 	无
** 修改记录：	
*********************************************************************/
void SelectRoleCell::setCellImage(const char *imgRoot)
{
	if ( NULL == m_WidgetTrainCell )
	{
		return;
	}

	std::string str(imgRoot);

	auto isExist = FileUtils::getInstance()->isFileExist(str);
	if ( (true == isExist) && (-1 != str.find(imageExtension_S)) )			/* 文件是否存在，且为png图片 */
	{
		roleImage->loadTexture(str);
		roleImage->setTouchEnabled(true);

		Size sz = roleImage->getContentSize();
		if ( sz.width != szImage.width )
		{
			m_fRateX = szImage.width / sz.width;
			roleImage->setScaleX(m_fRateX);
		}
		if ( sz.height != szImage.height )
		{
			m_fRateY = szImage.height / sz.height;
			roleImage->setScaleY(m_fRateY);
		}
	}
}

/*********************************************************************
** 功能：		显示已上阵
** 输入参数：	
** 返回值： 	无
** 修改记录：	
*********************************************************************/
void SelectRoleCell::setSelected()
{
// 	auto isSelected = dynamic_cast<Text* >(Helper::seekWidgetByName(m_WidgetTrainCell, isSelectedRoleCellText));
// 
// 	isSelected->setVisible(true);
}