#include "FontGuard.h"

USING_NS_CC;

FontGuard::FontGuard(void)
{
}

FontGuard::~FontGuard(void)
{
}

/*********************************************************************
** ���ܣ�		���÷��е�����Ӫ���˺�����
** ���������	Role *owner: �����ͷ���
**				const std::string& strImg: ��Դͼ
**				FlightPropInfo propInfo: ��������
** ����ֵ��		
** �޸ļ�¼��	
*********************************************************************/
FontGuard* FontGuard::create(Role *owner, const std::string& strImg, FlightPropInfo propInfo)
{
	auto sprite = new FontGuard();
	if (sprite && sprite->initWithFile(strImg + "0" + sprite->getImgSuffix()))
	{
		sprite->InitParam(owner, propInfo, strImg);
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

void FontGuard::fontOver()
{
	std::stringstream stream;
	auto strImg = stream.str();

	Animation* animation = Animation::create();  
	for(int i = 4; i < 9; i ++)  
	{
		stream.str("");
		stream << m_strImg << i << getImgSuffix();
		strImg = stream.str();

		animation->addSpriteFrameWithFile(strImg);
	}  
	animation->setDelayPerUnit(m_stPropInfo.dur);  
	animation->setRestoreOriginalFrame(true);  
	auto animate = Animate::create(animation);

	this->runAction(Sequence::create(animate, CallFuncN::create(CC_CALLBACK_1(FontGuard::fontOverCallBack, this)), NULL));
}

/*********************************************************************
** ���ܣ�		����������ϻص�
** ���������	Node *who
** ����ֵ��		��
** �޸ļ�¼��	
*********************************************************************/
void FontGuard::fontOverCallBack(Node *who)
{
	who->removeFromParentAndCleanup(true);
}