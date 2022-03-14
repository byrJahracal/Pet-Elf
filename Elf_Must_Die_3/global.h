#ifndef GLOBAL_H
#define GLOBAL_H

#include <QDebug>
#include <QString.h>
#include<time.h>
#include <QPixmap>
#define RANDOM(x) ((rand()%(x))+1)

#define ALLSTATE 17//17种状态
#define ALLELEMENT 5//5中元素
#define ALLPET 25//25种精灵
#define ALLTIME 6//6种战斗时机
#define MAXLEVEL 15//最高15级
#define LEVEL_1 3
#define LEVEL_2 8
#define LEVEL_3 12
#define LEVEL_4 15//以上4个等级时可以增加技能点
#define TAL_1 5
#define TAL_2 10//以上两个等级天赋技能升级
#define ALLSKILLKIND 4//技能种类，主动被动指挥追击
#define ALLATTACKTYPE 3//除普攻外的攻击方式，天赋，技能一，技能二
#define ALLSKILL 11//11种可学习技能
#define ALLATTRIBUTES 4//共4种主属性
#define DEFENCECONST 400//防御参数
#define SKILLREMAIN 6//一个技能可学习次数
#define TURNNEED 200//精灵敏捷加载到该值后方可行动

enum StateWindow{//界面切换
    PMAIN,PFIGHT,PFIGHTOVER,PUSER,PTOUXIANG,PYANWU,PCHONGWU,POTHERUSER,PSHOULIE,PJVEDOU
};

enum StateSkill{//战场时机：判定状态，普攻，释放天赋，释放技能1，释放技能2
    TOPAN,TOATT,TOTAL,TOSK1,TOSK2
};

enum FightMode{//三种战斗模式
    YANWU,JVEDOU,SHOULIE
};

enum PElement{//精灵元素
    LEAF,FLAME,THUNDER,ICE,DARK
};

enum State{//精灵战斗时的状态
    ZHONGDU,ZHUOSHAO,BINGDONG,GANDIAN,BAOZAO,XUANYUN,JINGU,RUOHUA,YOUYU,HUDUN,FANSHANG,MIANYI,XINGFEN,GUIBI,QINLVE,ZHUANZHU,SHIXVE
};

typedef enum PrimaryAttribute{//精灵的4种属性
    LIFE,POWER,DEFENCE,AGILITY
}PrimaryA;

typedef enum SkillType{//可学习技能编号，还有未学习和未解锁
    LOCKED,UNLOCKED,
    LEAF_ATTACK,FLAME_ATTACK,THUNDER_ATTACK,ICE_ATTACK,DARK_ATTACK,
    XILI,BUQUYIZHI,XIANXVEKEWANG,XIANQUTUJI
}SkillT;

enum PetNumber{//精灵编号
    YEJINGLING,HUOJINGLING,BINGJINGLING,LEIJINGLING,HEIJINGLING,
    XUANWUSHOU,BAOLONGSHOU,JIALULUSHOU,QINGLONGSHOU,YUANDUXIXVEGUI,
    TIANNVSHOU,ZHANDOUBAOLONG,GANGTIEJIALULU,DUJIAOXIAN,SANGSHIBAOLONG,
    XIANRENZHANG,JIANSHISHOU,GANGTIEHAILONG,ZUDUNSHOU,EMOSHOU,
    MUOUSHOU,JIALOULUOSHOU,LANGRENJIALULU,AOMIJIASHOU,NVEMOSHOU
};

enum FightTime{//精灵一回合中的时机
    BEGIN,SIMPLE_ATTACK,SKILL_TIME,OVER,INJURED,NOTHING
};

enum AttackType{//三种技能存在方式
    TALENT,SKILL1,SKILL2
};

enum SkillKind{//四种技能类型，指挥，被动，主动，追击
    COMMAND,PASSIVE,INITIATIVE,FOLLOW
};

extern PetNumber g_PetNum[ALLPET];
extern QString g_Name[ALLPET];
extern PrimaryA g_PrimaryA_A[ALLPET];
extern PElement g_Element[ALLPET];
extern int g_Life[ALLPET];
extern int g_Power[ALLPET];
extern int g_Defence[ALLPET];
extern int g_Agility[ALLPET];
extern int g_Life_Grow[ALLPET];
extern int g_Power_Grow[ALLPET];
extern int g_Defence_Grow[ALLPET];
extern int g_Agility_Grow[ALLPET];
extern int g_Cri_Rate[ALLPET];
extern float g_Cri_Damage[ALLPET];
extern int g_Dodge_Rate[ALLPET];
extern SkillT g_Skill1[ALLPET];
extern SkillT g_Skill2[ALLPET];
extern QString g_Image[ALLPET];//以上为各个精灵的属性参数
extern QString g_Str_Attributes[ALLATTRIBUTES];
extern QString g_Str_element[ALLELEMENT];
extern QString g_Str_skill[ALLSKILL];
extern QString g_Str_state[ALLSTATE];
extern QString g_Str_talent[ALLPET];//g_str代表文字信息
extern QString g_Intro_Elf[ALLPET];
extern QString g_Intro_Skill[ALLSKILL];
extern QString g_Intro_Talent[ALLPET];//g_intro代表介绍信息

extern FightTime g_Talent_Time[ALLPET];
extern SkillKind g_Talent_Kind[ALLPET];//天赋技能的释放时机和种类

extern FightTime g_Skill_Time[ALLSKILL];
extern SkillKind g_Skill_Kind[ALLSKILL];//可学习技能释放时机和种类

extern int g_open_texiao;//特效开关
extern float g_ele_ratio;//战场元素之力
extern QString g_message;//战斗过程中的信息输出
extern QString g_touxiang_pet;//宠物图片路径
extern QString g_touxiang_user;//用户头像路径
extern QString g_background;//背景图片路径
extern QString g_background2;//战斗特效背景图片路径

void InitData();//初始化全局变量，精灵数据
void EleRatioAdd(int r);//改变元素之力
#endif // GLOBAL_H
