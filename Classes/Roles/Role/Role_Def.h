#pragma once
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

const int maxActAiLimit = 1000;					/* ��������ֵ */
const int minActAiLimit = 1;					/* �������Сֵ */
const int DamageOffset = 50;					/* �˺������� */
const int MoveSpeed = 130;						/* �ƶ��ٶȵ�λ */
const int iRegionLimit = 30;					/* ���ƶ��������ұ߽� */
const float ResourceScale = 0.7f;				/* ��Դ���ű��� */
const float ComboDuration = 0.2f;				/* Ĭ�������������ʱ�� */
const float HealthRetRate = 1.0f;				/* hp mp�ظ�Ƶ�� */
const float InvincibleDelay = 0.5f;				/* �޵�ʱ�� */
const float DownDelay = 0.6f;					/* ����ʱ�� */
const float ConfusionDuration = 8.0f;			/* ���ҳ���ʱ��8s */
const float FrozenDuration = 5.0f;				/* ��������ʱ��8s */
const float	SleepDuration = 2.5f;				/* �������ʱ */
const float MoveDuration = 2.0f;				/* �����ʱ�� */
const float DirDuration = 0.5f;					/* �ƶ�����仯CD */
const float SceneWidth = 800.0f;				/* ����ͼ��� */
const cocos2d::Point ptAtkOffset = cocos2d::Point(10, 0); /* ����ʱ����ɫ����ǰ�ƶ� */
const cocos2d::Point ptInvalid = cocos2d::Point(-1, -1); /* ��Ч�� */

/* ��ɫ����ģʽ */
enum RoleCreMode
{
	RoleCreMode_Preview = 0,					/* �佫�������Ԥ��ģʽ */
	RoleCreMode_Fighting,						/* ��ɫ����ģʽ */
	RoleCreMode_XueGong1,						/* ���ѧ����Ⱥ��buff */
	RoleCreMode_XueGong2,						/* ���ѧ����ս�Ӿ���buff */
	RoleCreMode_XueGong3,						/* ���ѧ�����佫����buff */
	RoleCreMode_XueGong4,						/* ���ѧ��������װ�� */
	RoleCreMode_Max
};

/* ����֡�¼� */
enum RoleFrameEvent
{
	FrameEvent_Begin = 0,						/* ����׼����ϣ���ʼ���壩 */
	FrameEvent_End,								/* ������ʼ���У��������壩 */
	FrameEvent_Attack,							/* �����¼��������أ� */
	FrameEvent_Attack_FD,						/* �����¼������أ� */
	FrameEvent_Shot,							/* �����¼��������أ� */
	FrameEvent_Shot_FD,							/* �����¼������أ� */
	FrameEvent_Invincible,						/* �޵��¼� */
	FrameEvent_Break,							/* �ж϶����¼� */
	FrameEvent_Left,							/* ��������: ǰ */
	FrameEvent_Middle,							/* ��������: ǰ��˫�� */
	FrameEvent_Right,							/* ��������: �� */
	FrameEvent_Max
};

/* AI��Ϊ���� */
enum RoleActAiSign
{
	RoleActAi_None = 0,							/* ����Ϊ */
	RoleActAi_Pursuit,							/* ׷�� */
	RoleActAi_ShortMove,						/* �̾����ƶ� */
	RoleActAi_Sleep,							/* ���� */
	RoleActAi_Max
};

/* ��ɫ���� */
enum RoleMode
{
	RoleMode_Main = 0,							/* ���� */
	RoleMode_Soldier,							/* ���� */
	RoleMode_Companion,							/* С��� */
	RoleMode_Boss,								/* boss */
	RoleMode_Max
};

const float roleActAiLimit[RoleMode_Max][RoleActAi_Max] = {
	{ 0, 734, 952, 1000 },						/* ���� */
	{ 0, 250, 700, 1000 },						/* ���� */
	{ 0, 657, 900, 1000 },						/* С��� */
	{ 0, 763, 950, 1000 },						/* boss */
};

/** ��ɫ�������� **/
enum RoleActSign
{
	RoleAct_Idle = 0,							/* 0������ */
	RoleAct_Attack,								/* 1����ͨһ���� */
	RoleAct_Twice_Atk,							/* 2����ͨ������ */
	RoleAct_Thrice_Atk,							/* 3����ͨ������ */
	RoleAct_Move,								/* 4���ƶ� */
	RoleAct_SkillOne,							/* 5������һ */
	RoleAct_SkillTwo,							/* 6�����ܶ� */
	RoleAct_SkillThree,							/* 7�������� */
	RoleAct_SkillFour,							/* 8�������� */
	RoleAct_Smitten,							/* 9������ */
	RoleAct_Down,								/* 10������ */
	RoleAct_Death,								/* 11������ */
	RoleAct_Max
};

/** ���ܲ���ָ��� **/
enum RoleCmdSign
{
	RoleCmdSign_Move,					/* �ƶ� */
	RoleCmdSign_Attack,					/* ���� */
	RoleCmdSign_SkillOne,				/* ����һ */
	RoleCmdSign_SkillTwo,				/* ���ܶ� */
	RoleCmdSign_SkillThree,				/* ������ */
	RoleCmdSign_SkillFour,				/* ������ */
	RoleCmdSign_Release,				/* ��ť���� */
	RoleCmdSign_Max
};

/** ��ɫ״̬���� **/
enum RoleStatus
{
	RoleStatus_Normal = 0,
	RoleStatus_Invincible,						/* �޵� */
	RoleStatus_Superarmor,						/* ���� */
	RoleStatus_Death,							/* ���� */
	RoleStatus_Max
};

/** �쳣״̬���� **/
enum RoleCondition
{
	RoleCondition_Normal = 0,					/* ���� */
	//RoleCondition_Poisoning,					/* �ж� */
	//RoleCondition_Bleeding,					/* ��Ѫ */
	//RoleCondition_Fixed,						/* ���� */
	RoleCondition_Confusion,					/* ���� */
	RoleCondition_Frozen,						/* ���� */
	RoleCondition_Max
};

/** ���Ҷ��� **/
enum RoleCamp
{
	RoleCamp_Normal = 0,
	RoleCamp_Red,								/* �Ҿ� */
	RoleCamp_Black,								/* �о� */
	RoleCamp_Max
};

/*  ������ҷ��� */
enum RoleDirSign
{
	RoleDir_Right = -1,							/* ������ */
	RoleDir_Middle = 0,
	RoleDir_Left = 1,							/* ������ */
	RoleDir_Max
};

/* ��ɫְҵ */
enum RoleRace
{
	RoleRace_Power = 1,							/* ���� */
	RoleRace_Wizard,							/* ���� */
	RoleRace_Speed,								/* ���� */
	RoleRace_Max
};

/* ������ħ���� */
enum RoleActMode
{
	RoleActMode_Normal = 0,						/* ��ͨ */
	RoleActMode_Physical,						/* ������ */
	RoleActMode_Magic,							/* ħ������ */
	RoleActMode_Super,							/* �Եй������Լ���Ѫ */
	RoleActMode_Control,						/* �س�����(��������ͷ��) */
	RoleActMode_Guard,							/* ��������(�ﵥ�����) */
	RoleActMode_Max
};

/** ��ɫ��ʱ������ **/
enum RoleScheduleType
{
	RoleSchedule_Combo = 0,						/* ������¼��ʱ�� */
	RoleSchedule_Condition,						/* ��״̬��ʱ�� */
	RoleSchedule_AiAction,						/* Ai��Ϊ��ʱ�� */
	RoleSchedule_Abnormal,						/* �쳣״̬�˺� */
	RoleSchedule_Shield,						/* ���ܼ�ʱ�� */
	RoleSchedule_HpReturn,						/* hp�ָ���ʱ�� */
	RoleSchedule_Max
};

/** ��ɫhp�仯��ʾ **/
enum RoleHealthSign
{
	RoleHealth_RedNormal = 0,					/* ������ͨ�˺� */
	RoleHealth_OppNormal,						/* �Է���ͨ�˺� */
	RoleHealth_Critical,						/* �����˺� */
	RoleHealth_Up,								/* ��Ѫ */
	RoleHealth_Max
};

/** ��ɫ�츳 **/
enum RoleTalent
{
	RoleTalent_ShiHua = 1,						/* 0ʯ��������4%����������ͷ������� */
	RoleTalent_FuSuZhiFeng,						/* 1����֮�磺����12��ÿ���Ѫ���ظ� */
	RoleTalent_GeDang,							/* 2�񵲣��������Եз����˺� */
	RoleTalent_XueYeFeiTeng,					/* 3ѪҺ���ڣ�����ֵ���ֵ����6% */
	RoleTalent_NengLiangHua,					/* 4��������ʹ�ü���ʱ����������ֵΪ3%�Ļ��ܣ�����7�� */
	RoleTalent_JuRen,							/* 5���ˣ��ϳ�����ϵ�佫�˺�����8% */
	RoleTalent_QianFeng,						/* 6ǰ�棺������������4% */
	RoleTalent_ZhengMianDuiJue,					/* 7����Ծ���������ϵ�ĵ�������˺����6% */
	RoleTalent_ZhanSha,							/* 8նɱ����ɱһ���з���λ��ظ�8%Ѫ�� */
	RoleTalent_PoZaiMeiJie,						/* 9����ü�ޣ�ÿ��ս��ʱ���ȥ20�룬���1.5%���˺� */
	RoleTalent_LiLiangBaoFa,					/* 10��������������75�㹥���� */
	RoleTalent_FuWenHuDun,						/* 11���Ļ��ܣ�����ս��ʱ�������ֵ10%�Ļ��� */
	RoleTalent_PoMoZhiRen,						/* 12��ħ֮�У��ϳ�����ϵ�佫�˺�����4% */
	RoleTalent_DunQiang,						/* 13��ǽ���з���ɵ��˺�����5% */
	RoleTalent_WuShiLieRen,						/* 14��ʦ���ˣ�������ϵ�ĵ�������˺����6% */
	RoleTalent_XiXueXiXing,						/* 15��Ѫϰ�ԣ���ͨ������6%ת��Ϊ����ֵ */
	RoleTalent_KuangNu,							/* 16��ŭ���������ӹ�����5% */
	RoleTalent_GongFaJianBei,					/* 17�����汸���ϳ�����ϵ�佫��������3% */
	RoleTalent_CaoYaoZhuanJia,					/* 18��ҩר�ң�ÿ25���������Ѫ�����ٵĶ��ѻظ�7.5%��Ѫ�� */
	RoleTalent_ZhiYu,							/* 19��������Ѫ�ٶ����1% */
	RoleTalent_GangJingJiSha,					/* 20�ɾ���ɱ����һ�����˱����ܻ��в�����ʱ������cd���� */
	RoleTalent_YinMouJia,						/* 21��ı�ң�������ϵ�ĵ�������˺����6% */
	/* ���������佫�츳 */
	RoleTalent_JingGangHuTi,					/* ��������ջ��壺ÿ�γ��ܵĹ����˺�����8% */
	RoleTalent_KuangBao,						/* ���𣺿񱩣���ͨ�����������8% */
	RoleTalent_PoJia,							/* ���������Ƽף���ͨ��������15%�Ļ���ֵ������2��. */
	RoleTalent_ShiXue,							/* ��ɣ���Ѫ���佫Ѫ������80%���˺����12% */
	RoleTalent_ZhiSi,							/* �������������з�Ѫ������25%ʱ��������ɵ��˺�����15% */
	RoleTalent_JianGuFangYu,					/* ���ģ���̷���������ȫ���佫5%���������5%�������� */
	RoleTalent_XueMoFa,							/* ������Ѫħ��������ʱ���ɻָ��˺���8%������ֵ */
	RoleTalent_ZhangKongZhanChang,				/* ��ȵ���ƿ�ս����Ѫ������35%ʱ��������������8%�����������8% */
	RoleTalent_JueShiLiShao,					/* ��ԭ��������ɧ������Ǳ�����5�㣬Ѫ��Ǳ�����25�� */
	RoleTalent_YaZhi,							/* ������ѹ�ƣ�����Ѫ������Ŀ��ʱ������˺����15% */
	RoleTalent_MoNvMiXing,						/* �����ޣ�ħŮ���У������˺���8%�˺������ճ�Ϊ���Ѫ�� */
	RoleTalent_ShuangRenJian,					/* ����˫�н�����ɵ��˺����20%���ܵ����˺����10% */
	RoleTalent_ZhongXingWuQi,					/* ���ࣺ��������������������15%�������˺����20% */
	RoleTalent_BingJiaZhiZhu,					/* ���䣺����֮����ÿ���һ�����ѣ���������3%�Ĺ�������3%�ķ��������ͻ��� */
	RoleTalent_JiLi,							/* ���尽��������������ȴʱ�����15% */
	RoleTalent_TongShuai,						/* ���ģ�ͳ˧����Ϊ�����������˺����50% */
	RoleTalent_BenNeng,							/* κ�޼ɣ����ܣ�ȫ�幥���˺�����5% */
	RoleTalent_XueSeJieXian,					/* ��ʤ��Ѫɫ���ޣ��ҷ��佫ȫ��Ѫ����������5% */
	RoleTalent_WenDingJieJie,					/* ��Ъ���ȶ���磺����ȫ��з�15%���������15%�������� */
	RoleTalent_Max
};

/** ս����Ϣ **/
enum RoleWarMsg
{
	RoleWarMsg_None = 0,						/* �� */
	RoleWarMsg_Pause,							/* ��ͣ */
	RoleWarMsg_Pass,							/* ��ͼ */
	RoleWarMsg_Over,							/* ���� */
	RoleWarMsg_Max
};

#define CREATE_ROLE_FUNC(__TYPE__) \
	static __TYPE__* create(std::string strName, RoleCreMode mode, float resScale = ResourceScale) \
	{ \
		__TYPE__ *pRet = new __TYPE__(); \
		if ((NULL != pRet) && (true == pRet->init(strName, mode, resScale))) \
		{ \
			pRet->autorelease(); \
			return pRet; \
		} \
		delete pRet; \
		pRet = NULL; \
		return NULL; \
	}

/** ��ɫ�������Խṹ **/
typedef struct tagSkillInfo
{
	int		level;								/* ���ܵȼ� */
	float	cd;									/* cd */
	float	damage;								/* �˺� */
	float	damageAddition;						/* �����˺� */
	float	xAtkDis;							/* ˮƽ�򹥻����� */
	float	yAtkDis;							/* �����򹥻����� */
	char	name[20];							/* ���ܹ������� */
	RoleActMode	model;						/* ���� */
} SkillInfo, *pSkillInfo;

/* ��ɫ������ */
typedef struct tagRoleSubInfo
{
	float				speed;					/* �߶��ٶ� */
	RoleDirSign			side;					/* ����������� */
	RoleDirSign			atkSide;				/* �������� */
	RoleDirSign			hitSide;				/* �ܻ����� */
	cocos2d::Point		anchorPoint;			/* ê�� */
} RoleSubInfo, *pRoleSubInfo;

/** �������� **/
typedef struct tagRolePanel						/* �������� */
{
	int		hpTotal;							/* ������ֵ */
	int		hpCurrent;							/* ��ǰ����ֵ */
	int		atk;								/* ������ */
	int		realAtk;							/* ��ʵ�˺� */
	int		realAtkDefend;						/* ��ʵ�˺����� */
	int		pDefend;							/* ������� */
	int		mDefend;							/* �������� */
	float	critical;							/* ���� */
	float	criDefend;							/* �������� */
	float	criExtra;							/* �����˺��ӳ� */
	int		level;								/* �ȼ� */
	/* ������ȫ��buff */
	int		hpBack;								/* hp�ظ��� */
	float	allHarm;							/* �������˺��ӳɣ��ٷֱȣ� */
	float	wizardHarm;							/* ���������˺��ӳɣ��ٷֱȣ� */
	float	speedHarm;							/* ���������˺��ӳɣ��ٷֱȣ� */
	float	powerHarm;							/* ���������˺��ӳɣ��ٷֱȣ� */
	float	lowerHarm;							/* ������ */
	int		shield;								/* ���� */
	int		talent;								/* ��ɫ�츳 */
	int		pDefendL;							/* ���Ͷ������ */
	int		mDefendL;							/* ���Ͷ���ħ�� */
} RolePanel, *pRolePanel;

/** ��ɫ��Ϣ�ṹ **/
typedef struct tagRoleInfo 
{
	RolePanel				panel;				/* �������� */
	RoleActSign				actSign;			/* ���� */
	RoleCamp				camp;				/* ��Ӫ */
	RoleMode				mode;				/* ��ɫ���ͣ����ѡ�С�֡�СͷĿ�ȣ� */
	RoleRace				race;				/* ��ɫְҵ */
	RoleStatus				status;				/* ����״̬: ��ͨ���޵С����塢���� */
	RoleCondition			condition;			/* �쳣״̬���ж�����Ѫ�� */
	cocostudio::Armature	*arAnimate;			/* ����������Դ */
} RoleInfo, *pRoleInfo;

/* ��������ʱbuff */
typedef struct tagRoleBuff
{
	int		hpLimit;							/* �������� */
	int		hpBack;								/* hp�ظ��� */
	int		atk;								/* ������ */
	float	allHarm;							/* �������˺��ӳɣ��ٷֱȣ� */
	float	wizardHarm;							/* ���������˺��ӳɣ��ٷֱȣ� */
	float	speedHarm;							/* ���������˺��ӳɣ��ٷֱȣ� */
	float	powerHarm;							/* ���������˺��ӳɣ��ٷֱȣ� */
	float	lowerHarm;							/* ������ */
	float	critical;							/* ���� */
	float	criExtra;							/* �����˺��ӳ� */
	int		pDefend;							/* ����츳 */
	int		mDefend;							/* �����츳 */
	int		shield;								/* ���� */
} RoleBuff;