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
	enum EEMode {EE_Strengthen = 0, EE_Refine};						/* ǿ��������ģʽ */
	enum EEImgEquip {EE_Equip_1, EE_Equip_2, EE_Equip_3, EE_Equip_4, EE_Equip_5, EE_Equip_6, EE_Equip_Max};

	typedef struct _tagEERoleInfo									/* ��ɫװ����Ϣ */
	{
		int		pkID;												/* ��ɫPKID */
		char	name[20];											/* ��ɫ���� */
		char	cname[20];											/* ��ɫ���� */
		int		job;												/* ��ɫְҵ */
		int		level;												/* ��ɫ�ȼ� */
		int		exp;												/* ��ɫ������� */
		int		fight;												/* ��ɫս���� */
		EquipProptyStruct	Equips[EE_Equip_Max];					/* ��ɫװ�� */
	} EERoleInfo;

	enum EERole
	{
		EE_RoleName,
		EE_RoleLv,
		EE_RoleMax
	};

	enum EEButton
	{
		EE_RolePrev,												/* ǰһ����ɫ */
		EE_RoleNext,												/* ��һ����ɫ */
		EE_EquipS,													/* ǿ�� */
		EE_EquipS5,													/* ǿ��5 */
		EE_EquipR,													/* ���� */
		EE_Close,													/* �ر� */
		EE_Btn_Max
	};

	enum EELabelStr													/* װ��ǿ����Ϣ�ı��� */
	{
		EE_StrName,													/* ���� */
		EE_StrLv0,													/* �ȼ���ǰ�� */
		EE_StrLv1,													/* �ȼ����� */
		EE_StrProp0,												/* ���ԣ�ǰ�� */
		EE_StrProp1,												/* ���ԣ��� */
		EE_StrCoin0,												/* һ��ǿ����� */
		EE_StrCoin1,												/* 5��ǿ����� */
		EE_StrMax
	};

	enum EELableRef													/* װ��������Ϣ�ı��� */
	{
		EE_RefName0,												/* ���ƣ�ǰ�� */
		EE_RefName1,												/* ���ƣ��� */
		EE_RefProp00,												/* ����1��ǰ�� */
		EE_RefProp10,												/* ����2��ǰ�� */
		EE_RefProp01,												/* ����1���� */
		EE_RefProp11,												/* ����2���� */
		EE_RefCoin,													/* ������� */
		EE_RefMax
	};

protected:
	void initPara();												/* ������ʼ�� */
	void loadStateBar();
	void loadEnhanceFactory();										/* ����UI */
	void loadRoleEquipInfo();										/* ���ؽ�ɫװ����Ϣ */
	void loadEquipList();											/* ���ؿ���װ���б� */

	/* ��ʾ */
	void showRoleEquipInfo();										/* ��ʾ��ɫװ�� */
	void showStrEquipInfo();										/* ��ʾװ��1-4��Ϣ */
	void showRefEquipInfo();										/* ��ʾװ��5-6��Ϣ */
	void showEquipUsable();											/* ��ʾ����װ������ */
	void showNotice(std::string);									/* ��ʾ��ʾ */

	/* �¼���Ӧ */
	void btnResponse(cocos2d::Ref* , cocos2d::ui::TouchEventType ); /* Button�����Ӧ */
	void btnEquipStrengthen();										/* װ��ǿ�� */
	void btnEquipStrengthen5();										/* װ��ǿ��5�� */
	void btnEquipRefine();											/* װ������ */
	void imgResponse(cocos2d::Ref* , cocos2d::ui::TouchEventType ); /* ImageView�����Ӧ */
	void svEquipListResponse(cocos2d::Ref* , cocos2d::ui::TouchEventType );/* ScrollView�����Ӧ */

	/* ���� */
	void changeEnhanceMode(EEMode);									/* ǿ��������ģʽ�л� */
	float getStrengthenImprove(int , int);							/* ��ȡǿ����������ֵ */
	int	getStrengthenCoin(int , int);								/* ��ȡǿ�����Ľ�� */
	void clearPanel();												/* ���װ����Ϣ��ʾ */
	void removeEquipUsed();											/* �Ƴ�ʹ�õ���װ�� */
	void EnhanceAnimate();											/* ǿ������������ */
	void EnhanceAnimateCB(cocos2d::Node *);							/* ǿ�������������ص����� */

private:
	unsigned int			_PointSetIndex;							/* �佫����ID */
	int						_iEquipIndex;							/* ѡ��ǿ��/������װ������ */
	int						_iRefineCost;							/* �������� */
	EEMode					_EE_EnMode;								/* ���ǿ��������ģʽ */

	StateBarNode			*_StateBar;
	cocos2d::ui::Widget		*_EnhanceUI;
	cocos2d::ui::Layout		*_panelStr;								/* ǿ���� */
	cocos2d::ui::Layout		*_panelRef;								/* ������ */
	cocos2d::ui::ImageView	*_imgEquip[EE_Equip_Max];				/* װ����ʾ�ؼ� */
	cocos2d::ui::ImageView	*_imgJob[3];							/* ְҵͼ�� */
	cocos2d::ui::ImageView	*_imgStrSelect;							/* ѡ�е�ǿ��װ�� */
	cocos2d::ui::ImageView	*_imgRefSelect;							/* ѡ�еľ���װ�� */
	cocos2d::ui::Text		*_txtStr[EE_StrMax];					/* װ��ǿ����Ϣ�ı��� */
	cocos2d::ui::Text		*_txtRef[EE_RefMax];					/* װ��������Ϣ�ı��� */
	cocos2d::ui::Text		*_txtRole[EE_RoleMax];					/* �佫������Ϣ */
	cocos2d::ui::TextAtlas	*_txtRoleFight;							/* �佫ս���� */
	cocos2d::ui::LoadingBar	*_lbRefineExp;							/* ��������ֵ */
	cocos2d::ui::LoadingBar *_lbRoleExp;							/* �佫��������� */
	cocos2d::ui::ScrollView	*_svEquipList;							/* ��ѡ��װ���б� */

	cocos2d::Node			*_roleNode;								/* ��ɫ��ʾ�� */

	std::vector<EERoleInfo >			_PointSets;					/* �����佫װ����Ϣ */
	std::vector<int >					_EquipUsing;				/* ����ʱ��ѡ�е�װ��PKID */
	std::vector<EquipProptyStruct >		_EquipList;					/* ����װ���б� */
	std::vector<EquipRefineStruct >		_localRefineRule;

	NewComer		*_comer;
};

