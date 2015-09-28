#include "EquipmentCell.h"

bool EquipmentCell::init()
{
	equipmentPanel = GUIReader::getInstance()->widgetFromJsonFile("EquipCell.ExportJson");
	equipmentPanel->setTag( 99 );
	this->addChild(equipmentPanel);

	equipment = dynamic_cast<ImageView* >(Helper::seekWidgetByName(equipmentPanel, "Image_Equip"));
	

	return true;
}

void EquipmentCell::setImage(string nameString)
{
	auto name = __String::createWithFormat("%s", nameString.c_str());
	equipment->setScale(0.9f);
	equipment->loadTexture(name->getCString(), TextureResType::UI_TEX_TYPE_PLIST);
}

void EquipmentCell::setSelect()
{
	auto layer = (Layout*)this->getChildByTag( 99 );
	equipBG = dynamic_cast<ImageView* >(Helper::seekWidgetByName(layer, "Image_BG"));
	equipBG->loadTexture("TempPic/Lock.png");
	equipBG->setScale( 2.0f );
}