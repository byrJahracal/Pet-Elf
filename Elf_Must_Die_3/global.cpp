#include "global.h"

PetNumber g_PetNum[ALLPET];
QString g_Name[ALLPET];
PrimaryA g_PrimaryA_A[ALLPET];
PElement g_Element[ALLPET];
int g_Life[ALLPET];
int g_Power[ALLPET];
int g_Defence[ALLPET];
int g_Agility[ALLPET];
int g_Life_Grow[ALLPET];
int g_Power_Grow[ALLPET];
int g_Defence_Grow[ALLPET];
int g_Agility_Grow[ALLPET];
int g_Cri_Rate[ALLPET];
float g_Cri_Damage[ALLPET];
int g_Dodge_Rate[ALLPET];
SkillT g_Skill1[ALLPET];
SkillT g_Skill2[ALLPET];
FightTime g_Talent_Time[ALLPET];
SkillKind g_Talent_Kind[ALLPET];
QString g_Image[ALLPET];
QString g_Str_Attributes[ALLATTRIBUTES];
QString g_Str_element[ALLELEMENT];
QString g_Str_skill[ALLSKILL];
QString g_Str_state[ALLSTATE];
QString g_Str_talent[ALLPET];
QString g_Intro_Elf[ALLPET];
QString g_Intro_Skill[ALLSKILL];
QString g_Intro_Talent[ALLPET];

FightTime g_Skill_Time[ALLSKILL];
SkillKind g_Skill_Kind[ALLSKILL];

int g_open_texiao;
float g_ele_ratio=0.5;
QString g_message;
QString g_touxiang_pet=":/Elf/digimon/";
QString g_touxiang_user=":/User/touxiang/头像";
QString g_background=":/Background/beijing/";
QString g_background2=":/Background/beijing2/";

//YEJINGLING,HUOJINGLING,BINGJINGLING,LEIJINGLING,HEIJINGLING为比较基本的精灵。其余为高级精灵

void InitData(){
    g_Str_Attributes[LIFE]="生命";
    g_Str_Attributes[POWER]="力量";
    g_Str_Attributes[DEFENCE]="防御";
    g_Str_Attributes[AGILITY]="敏捷";

    g_Str_element[LEAF]="叶";
    g_Str_element[FLAME]="火";
    g_Str_element[THUNDER]="雷";
    g_Str_element[ICE]="冰";
    g_Str_element[DARK]="暗";

    g_Str_state[ZHONGDU]="中毒";
    g_Str_state[ZHUOSHAO]="灼烧";
    g_Str_state[BINGDONG]="冰冻";
    g_Str_state[GANDIAN]="感电";
    g_Str_state[BAOZAO]="暴躁";
    g_Str_state[XUANYUN]="眩晕";
    g_Str_state[JINGU]="禁锢";
    g_Str_state[RUOHUA]="弱化";
    g_Str_state[YOUYU]="犹豫";
    g_Str_state[HUDUN]="护盾";
    g_Str_state[FANSHANG]="反伤";
    g_Str_state[MIANYI]="免疫";
    g_Str_state[XINGFEN]="兴奋";
    g_Str_state[GUIBI]="规避";
    g_Str_state[QINLVE]="侵略";
    g_Str_state[ZHUANZHU]="专注";
    g_Str_state[SHIXVE]="嗜血";

    for(int i=0;i<ALLPET;i++){//初始化精灵数据
        switch(i){
        case YEJINGLING:{//雌性
            g_PetNum[i]=YEJINGLING;
            g_Name[i]="叶精灵";
            g_PrimaryA_A[i]=LIFE;
            g_Element[i]=LEAF;
            g_Life[i]=300;
            g_Power[i]=60;
            g_Defence[i]=60;
            g_Agility[i]=13;
            g_Life_Grow[i]=100;
            g_Power_Grow[i]=10;
            g_Defence_Grow[i]=10;
            g_Agility_Grow[i]=2;
            g_Cri_Rate[i]=20;
            g_Cri_Damage[i]=1.5;
            g_Dodge_Rate[i]=15;
            g_Skill1[i]=UNLOCKED;
            g_Skill2[i]=LOCKED;
            g_Talent_Time[i]=SIMPLE_ATTACK;
            g_Talent_Kind[i]=PASSIVE;
            g_Image[i]=g_touxiang_pet+g_Name[i];
            g_Str_talent[i]="草药注射";
            g_Intro_Elf[i]="生活在树林里的最常见的幼年期小精灵，心地善良，当她攻击你时其实只是想跟你玩耍！";
            g_Intro_Talent[i]="追击技能\n"+g_Name[i];
            g_Intro_Talent[i].append("玩耍时意外研制出一种花草毒药，在她叶攻击时可能混入这种毒药，使你陷入中毒状态，持续受伤且行动迟缓！");
            g_Intro_Talent[i].append("\n持续2回合");
            g_Intro_Talent[i].append("\n一级：释放概率20% 伤害30 敏捷降低3");
            g_Intro_Talent[i].append("\n二级：释放概率25% 伤害40 敏捷降低5");
            g_Intro_Talent[i].append("\n三级：释放概率30% 伤害50 敏捷降低7");
            break;
        }
        case HUOJINGLING:{//雄性
            g_PetNum[i]=HUOJINGLING;
            g_Name[i]="火精灵";
            g_PrimaryA_A[i]=LIFE;
            g_Element[i]=FLAME;
            g_Life[i]=300;
            g_Power[i]=60;
            g_Defence[i]=60;
            g_Agility[i]=13;
            g_Life_Grow[i]=100;
            g_Power_Grow[i]=10;
            g_Defence_Grow[i]=10;
            g_Agility_Grow[i]=2;
            g_Cri_Rate[i]=20;
            g_Cri_Damage[i]=1.5;
            g_Dodge_Rate[i]=15;
            g_Skill1[i]=UNLOCKED;
            g_Skill2[i]=LOCKED;
            g_Talent_Time[i]=SIMPLE_ATTACK;
            g_Talent_Kind[i]=PASSIVE;
            g_Image[i]=g_touxiang_pet+g_Name[i];
            g_Str_talent[i]="点燃";
            g_Intro_Elf[i]="生活在火山和熔岩周围幼年期小精灵，喜欢玩火。如果你阻止他玩火，那么你要小心了。他会点燃你！";
            g_Intro_Talent[i]="追击技能\n"+g_Name[i];
            g_Intro_Talent[i].append("酷爱玩火，即使是他的叶攻击也可以将你点燃，使你陷入灼烧状态，直接损失生命且受到火焰伤害！");
            g_Intro_Talent[i].append("\n持续2回合");
            g_Intro_Talent[i].append("\n一级：释放概率20% 损失比例3% 伤害40");
            g_Intro_Talent[i].append("\n二级：释放概率25% 损失比例4% 伤害50");
            g_Intro_Talent[i].append("\n三级：释放概率30% 损失比例5% 伤害60");
            break;
        }
        case BINGJINGLING:{//雄性
            g_PetNum[i]=BINGJINGLING;
            g_Name[i]="冰精灵";
            g_PrimaryA_A[i]=LIFE;
            g_Element[i]=ICE;
            g_Life[i]=300;
            g_Power[i]=60;
            g_Defence[i]=60;
            g_Agility[i]=13;
            g_Life_Grow[i]=100;
            g_Power_Grow[i]=10;
            g_Defence_Grow[i]=10;
            g_Agility_Grow[i]=2;
            g_Cri_Rate[i]=20;
            g_Cri_Damage[i]=1.5;
            g_Dodge_Rate[i]=15;
            g_Skill1[i]=UNLOCKED;
            g_Skill2[i]=LOCKED;
            g_Talent_Time[i]=SIMPLE_ATTACK;
            g_Talent_Kind[i]=PASSIVE;
            g_Image[i]=g_touxiang_pet+g_Name[i];
            g_Str_talent[i]="冰冻术";
            g_Intro_Elf[i]="生活在极寒地区的幼年期小精灵，喜爱低温，喜欢打雪仗，厌恶高温。如果你的体温偏高建议你远离他，不然他会帮你降温！";
            g_Intro_Talent[i]="追击技能\n"+g_Name[i];
            g_Intro_Talent[i].append("喜欢更低的温度，在他叶攻击时可能帮你降温，使你陷入冰冻状态，受到冰冻伤害，力量降低且无法叶攻击！");
            g_Intro_Talent[i].append("\n一级：释放概率20% 持续1回合 伤害10 力量降低10");
            g_Intro_Talent[i].append("\n二级：释放概率25% 持续2回合 伤害10 力量降低10");
            g_Intro_Talent[i].append("\n三级：释放概率30% 持续2回合 伤害10 力量降低50");
            break;
        }
        case LEIJINGLING:{//雄性
            g_PetNum[i]=LEIJINGLING;
            g_Name[i]="雷精灵";
            g_PrimaryA_A[i]=LIFE;
            g_Element[i]=THUNDER;
            g_Life[i]=300;
            g_Power[i]=60;
            g_Defence[i]=60;
            g_Agility[i]=13;
            g_Life_Grow[i]=100;
            g_Power_Grow[i]=10;
            g_Defence_Grow[i]=10;
            g_Agility_Grow[i]=2;
            g_Cri_Rate[i]=20;
            g_Cri_Damage[i]=1.5;
            g_Dodge_Rate[i]=15;
            g_Skill1[i]=UNLOCKED;
            g_Skill2[i]=LOCKED;
            g_Talent_Time[i]=SIMPLE_ATTACK;
            g_Talent_Kind[i]=PASSIVE;
            g_Image[i]=g_touxiang_pet+g_Name[i];
            g_Str_talent[i]="放电";
            g_Intro_Elf[i]="罕见的幼年期小精灵，长了一只像避雷针的角，喜欢雷电且自身带电。他很愿意与人亲近，不过时常放电而误伤他人！";
            g_Intro_Talent[i]="追击技能\n"+g_Name[i];
            g_Intro_Talent[i].append("只要稍微不注意或者生气就会放电，叶攻击时使你进入感电状态，受到雷电伤害增加且叶攻击时受到雷电伤害！");
            g_Intro_Talent[i].append("\n持续2回合");
            g_Intro_Talent[i].append("\n一级：释放概率20% 增伤比例10% 伤害15");
            g_Intro_Talent[i].append("\n二级：释放概率25% 增伤比例20% 伤害30");
            g_Intro_Talent[i].append("\n三级：释放概率30% 增伤比例30% 伤害45");
            break;
        }
        case HEIJINGLING:{//雌性
            g_PetNum[i]=HEIJINGLING;
            g_Name[i]="黑精灵";
            g_PrimaryA_A[i]=LIFE;
            g_Element[i]=DARK;
            g_Life[i]=300;
            g_Power[i]=60;
            g_Defence[i]=60;
            g_Agility[i]=13;
            g_Life_Grow[i]=100;
            g_Power_Grow[i]=10;
            g_Defence_Grow[i]=10;
            g_Agility_Grow[i]=2;
            g_Cri_Rate[i]=20;
            g_Cri_Damage[i]=1.5;
            g_Dodge_Rate[i]=15;
            g_Skill1[i]=UNLOCKED;
            g_Skill2[i]=LOCKED;
            g_Talent_Time[i]=SIMPLE_ATTACK;
            g_Talent_Kind[i]=PASSIVE;
            g_Image[i]=g_touxiang_pet+g_Name[i];
            g_Str_talent[i]="黑暗触摸";
            g_Intro_Elf[i]="生活在沼泽中的幼年期小精灵，黑暗的生活环境使她产生了邪恶与善良的双重性格。当你遇见她的时候，请提高警惕，她的抚摸可能是温柔的问候也可能是黑暗的触摸！";
            g_Intro_Talent[i]="追击技能\n"+g_Name[i];
            g_Intro_Talent[i].append("的邪恶人格经常作怪，在叶攻击时可能使你陷入弱化状态，防御和力量全部降低！");
            g_Intro_Talent[i].append("\n持续2回合");
            g_Intro_Talent[i].append("\n一级：释放概率20% 防御降低40 力量降低40");
            g_Intro_Talent[i].append("\n二级：释放概率25% 防御降低60 力量降低60");
            g_Intro_Talent[i].append("\n三级：释放概率30% 防御降低80 力量降低80");
            break;
        }
        case XUANWUSHOU:{//雄性
            g_PetNum[i]=XUANWUSHOU;
            g_Name[i]="玄武兽";
            g_PrimaryA_A[i]=LIFE;
            g_Element[i]=LEAF;
            g_Life[i]=600;
            g_Power[i]=113;
            g_Defence[i]=70;
            g_Agility[i]=12;
            g_Life_Grow[i]=140;
            g_Power_Grow[i]=20;
            g_Defence_Grow[i]=20;
            g_Agility_Grow[i]=3;
            g_Cri_Rate[i]=40;
            g_Cri_Damage[i]=1.5;
            g_Dodge_Rate[i]=25;
            g_Skill1[i]=UNLOCKED;
            g_Skill2[i]=LOCKED;
            g_Talent_Time[i]=BEGIN;
            g_Talent_Kind[i]=COMMAND;
            g_Image[i]=g_touxiang_pet+g_Name[i];
            g_Str_talent[i]="雾幻";
            g_Intro_Elf[i]="大自然的守护神，生命型精灵，有两只头，身体由原始森林组成的巨型神兽。";
            g_Intro_Talent[i]="指挥技能\n"+g_Name[i];
            g_Intro_Talent[i].append("利用背部的原始森林创造雾气，制造幻影，使自己进入免疫状态，使敌人进入犹豫状态");
            g_Intro_Talent[i].append("\n释放概率100% 持续2回合 消除暴击");
            g_Intro_Talent[i].append("\n一级：所有伤害降低20% 敏捷降低3");
            g_Intro_Talent[i].append("\n二级：所有伤害降低30% 敏捷降低5");
            g_Intro_Talent[i].append("\n三级：所有伤害降低40% 敏捷降低7");
            break;
        }
        case BAOLONGSHOU:{//雄性
            g_PetNum[i]=BAOLONGSHOU;
            g_Name[i]="暴龙兽";
            g_PrimaryA_A[i]=LIFE;
            g_Element[i]=FLAME;
            g_Life[i]=500;
            g_Power[i]=80;
            g_Defence[i]=50;
            g_Agility[i]=13;
            g_Life_Grow[i]=120;
            g_Power_Grow[i]=18;
            g_Defence_Grow[i]=11;
            g_Agility_Grow[i]=4;
            g_Cri_Rate[i]=20;
            g_Cri_Damage[i]=2;
            g_Dodge_Rate[i]=15;
            g_Skill1[i]=UNLOCKED;
            g_Skill2[i]=LOCKED;
            g_Talent_Time[i]=SKILL_TIME;
            g_Talent_Kind[i]=INITIATIVE;
            g_Image[i]=g_touxiang_pet+g_Name[i];
            g_Str_talent[i]="超级火焰";
            g_Intro_Elf[i]="远古巨龙，生命型精灵，口吐火焰，脾气暴躁。";
            g_Intro_Talent[i]="主动技能\n"+g_Name[i];
            g_Intro_Talent[i].append("喷射大量火焰，使敌人陷入灼烧状态，使自己进入兴奋状态");
            g_Intro_Talent[i].append("\n释放概率30% 持续3回合 伤害比例5% 敏捷增加2");
            g_Intro_Talent[i].append("\n一级：伤害20 暴击率增加10%");
            g_Intro_Talent[i].append("\n二级：伤害35 暴击率增加20%");
            g_Intro_Talent[i].append("\n三级：伤害50 暴击率增加30%");
            break;
        }
        case JIALULUSHOU:{//雄性
            g_PetNum[i]=JIALULUSHOU;
            g_Name[i]="加鲁鲁兽";
            g_PrimaryA_A[i]=LIFE;
            g_Element[i]=ICE;
            g_Life[i]=480;
            g_Power[i]=90;
            g_Defence[i]=58;
            g_Agility[i]=16;
            g_Life_Grow[i]=100;
            g_Power_Grow[i]=18;
            g_Defence_Grow[i]=12;
            g_Agility_Grow[i]=5;
            g_Cri_Rate[i]=25;
            g_Cri_Damage[i]=1.5;
            g_Dodge_Rate[i]=21;
            g_Skill1[i]=UNLOCKED;
            g_Skill2[i]=LOCKED;
            g_Talent_Time[i]=SKILL_TIME;
            g_Talent_Kind[i]=INITIATIVE;
            g_Image[i]=g_touxiang_pet+g_Name[i];
            g_Str_talent[i]="妖狐火焰";
            g_Intro_Elf[i]="加鲁鲁族成员，生命型精灵，兽形态，体质寒凉，可以喷射奇特的低温火焰。";
            g_Intro_Talent[i]="主动技能\n"+g_Name[i];
            g_Intro_Talent[i].append("喷射低温蓝火，使敌人陷入眩晕状态");
            g_Intro_Talent[i].append("\n 持续1回合 可以被免疫");
            g_Intro_Talent[i].append("\n一级：释放概率25% 防御降低30");
            g_Intro_Talent[i].append("\n二级：释放概率30% 防御降低45");
            g_Intro_Talent[i].append("\n三级：释放概率35% 防御降低60");
            break;
        }
        case QINGLONGSHOU:{//雄性
            g_PetNum[i]=QINGLONGSHOU;
            g_Name[i]="青龙兽";
            g_PrimaryA_A[i]=LIFE;
            g_Element[i]=THUNDER;
            g_Life[i]=550;
            g_Power[i]=76;
            g_Defence[i]=80;
            g_Agility[i]=14;
            g_Life_Grow[i]=130;
            g_Power_Grow[i]=15;
            g_Defence_Grow[i]=21;
            g_Agility_Grow[i]=5;
            g_Cri_Rate[i]=60;
            g_Cri_Damage[i]=1.3;
            g_Dodge_Rate[i]=21;
            g_Skill1[i]=UNLOCKED;
            g_Skill2[i]=LOCKED;
            g_Talent_Time[i]=SIMPLE_ATTACK;
            g_Talent_Kind[i]=FOLLOW;
            g_Image[i]=g_touxiang_pet+g_Name[i];
            g_Str_talent[i]="苍雷";
            g_Intro_Elf[i]="巨大的天空守护神，生命型精灵，浑身缠绕闪电与锁链。";
            g_Intro_Talent[i]="追击技能\n"+g_Name[i];
            g_Intro_Talent[i].append("召唤雷云，释放苍雷，使敌人暴躁，感电，使自己专注");
            g_Intro_Talent[i].append("\n 释放概率40% 持续2回合 禁用被动 防御增加50 受到雷电伤害增加40%");
            g_Intro_Talent[i].append("\n一级：主动概率降低6% 生命恢复30 攻击时受到雷电伤害30");
            g_Intro_Talent[i].append("\n二级：主动概率降低9% 生命恢复40 攻击时受到雷电伤害50");
            g_Intro_Talent[i].append("\n三级：主动概率降低12% 生命恢复50 攻击时受到雷电伤害70");
            break;
        }
        case YUANDUXIXVEGUI:{//雄性
            g_PetNum[i]=YUANDUXIXVEGUI;
            g_Name[i]="怨毒吸血魔兽";
            g_PrimaryA_A[i]=LIFE;
            g_Element[i]=DARK;
            g_Life[i]=688;
            g_Power[i]=100;
            g_Defence[i]=90;
            g_Agility[i]=11;
            g_Life_Grow[i]=137;
            g_Power_Grow[i]=14;
            g_Defence_Grow[i]=14;
            g_Agility_Grow[i]=4;
            g_Cri_Rate[i]=30;
            g_Cri_Damage[i]=1.7;
            g_Dodge_Rate[i]=10;
            g_Skill1[i]=UNLOCKED;
            g_Skill2[i]=LOCKED;
            g_Talent_Time[i]=INJURED;
            g_Talent_Kind[i]=PASSIVE;
            g_Image[i]=g_touxiang_pet+g_Name[i];
            g_Str_talent[i]="剧毒流注";
            g_Intro_Elf[i]="最邪恶的存在之一，生命型精灵，身体中剧毒涌动，怨念丛生。";
            g_Intro_Talent[i]="被动技能\n"+g_Name[i];
            g_Intro_Talent[i].append("受到攻击时会让攻击者沾染剧毒，进入中毒状态，自身进入嗜血状态");
            g_Intro_Talent[i].append("\n 释放概率100% 持续两回合 吸血百分比为已损失生命百分比*吸血系数 立即造成50点伤害 中毒伤害40 敏捷降低3");
            g_Intro_Talent[i].append("\n一级：吸血系数1.2 每回合扣血20");
            g_Intro_Talent[i].append("\n二级：吸血系数1.8 每回合扣血40");
            g_Intro_Talent[i].append("\n三级：吸血系数2.4 每回合扣血60");
            break;
        }
        case TIANNVSHOU:{//雌性
            g_PetNum[i]=TIANNVSHOU;
            g_Name[i]="天女兽";
            g_PrimaryA_A[i]=POWER;
            g_Element[i]=LEAF;
            g_Life[i]=400;
            g_Power[i]=90;
            g_Defence[i]=68;
            g_Agility[i]=14;
            g_Life_Grow[i]=90;
            g_Power_Grow[i]=20;
            g_Defence_Grow[i]=17;
            g_Agility_Grow[i]=5;
            g_Cri_Rate[i]=25;
            g_Cri_Damage[i]=1.8;
            g_Dodge_Rate[i]=17;
            g_Skill1[i]=UNLOCKED;
            g_Skill2[i]=LOCKED;
            g_Talent_Time[i]=SKILL_TIME;
            g_Talent_Kind[i]=INITIATIVE;
            g_Image[i]=g_touxiang_pet+g_Name[i];
            g_Str_talent[i]="神圣之箭";
            g_Intro_Elf[i]="美丽的女天使，力量型精灵，守护自然届中的一切美好事物。";
            g_Intro_Talent[i]="主动技能\n"+g_Name[i];
            g_Intro_Talent[i].append("射出神圣之箭，对暗系精灵有额外伤害，使自身免疫，使敌人禁锢无法使用普攻或主动");
            g_Intro_Talent[i].append("\n 释放概率35% 持续两回合 驱散敌人有利效果 受到元素伤害降低20%");
            g_Intro_Talent[i].append("\n一级：受到叶和暗伤害降低20%");
            g_Intro_Talent[i].append("\n二级：受到叶和暗伤害降低35%");
            g_Intro_Talent[i].append("\n三级：受到叶和暗伤害降低50%");
            break;
        }
        case ZHANDOUBAOLONG:{//雄性
            g_PetNum[i]=ZHANDOUBAOLONG;
            g_Name[i]="战斗暴龙兽";
            g_PrimaryA_A[i]=POWER;
            g_Element[i]=FLAME;
            g_Life[i]=550;
            g_Power[i]=110;
            g_Defence[i]=75;
            g_Agility[i]=13;
            g_Life_Grow[i]=88;
            g_Power_Grow[i]=32;
            g_Defence_Grow[i]=15;
            g_Agility_Grow[i]=3;
            g_Cri_Rate[i]=40;
            g_Cri_Damage[i]=2.2;
            g_Dodge_Rate[i]=20;
            g_Skill1[i]=UNLOCKED;
            g_Skill2[i]=LOCKED;
            g_Talent_Time[i]=SKILL_TIME;
            g_Talent_Kind[i]=INITIATIVE;
            g_Image[i]=g_touxiang_pet+g_Name[i];
            g_Str_talent[i]="盖亚能量炮";
            g_Intro_Elf[i]="披上铠甲的龙系精灵，力量型精灵，战斗力十足，拥有恐怖的力量与勇气。";
            g_Intro_Talent[i]="主动技能\n"+g_Name[i];
            g_Intro_Talent[i].append("发动盖亚之力，形成巨大火系能量球，砸向敌人，同时使自己进入侵略和兴奋状态");
            g_Intro_Talent[i].append("\n 释放概率25% 持续两回合 敏捷增加5 侵略元素为火");
            g_Intro_Talent[i].append("\n一级：暴击率增加20% 力量增加20");
            g_Intro_Talent[i].append("\n二级：暴击率增加40% 力量增加40");
            g_Intro_Talent[i].append("\n三级：暴击率增加60% 力量增加60");
            break;
        }
        case GANGTIEJIALULU:{//雄性
            g_PetNum[i]=GANGTIEJIALULU;
            g_Name[i]="钢铁加鲁鲁兽";
            g_PrimaryA_A[i]=POWER;
            g_Element[i]=ICE;
            g_Life[i]=500;
            g_Power[i]=98;
            g_Defence[i]=80;
            g_Agility[i]=14;
            g_Life_Grow[i]=82;
            g_Power_Grow[i]=27;
            g_Defence_Grow[i]=15;
            g_Agility_Grow[i]=5;
            g_Cri_Rate[i]=30;
            g_Cri_Damage[i]=1.6;
            g_Dodge_Rate[i]=25;
            g_Skill1[i]=UNLOCKED;
            g_Skill2[i]=LOCKED;
            g_Talent_Time[i]=BEGIN;
            g_Talent_Kind[i]=COMMAND;
            g_Image[i]=g_touxiang_pet+g_Name[i];
            g_Str_talent[i]="冰狱冷冻气";
            g_Intro_Elf[i]="极寒领域的加鲁鲁，力量型精灵，身披铠甲，加鲁鲁族之王。";
            g_Intro_Talent[i]="指挥技能\n"+g_Name[i];
            g_Intro_Talent[i].append("释放来自地狱的超低温的气压，使敌人冰冻并犹豫。");
            g_Intro_Talent[i].append("\n 释放概率100% 持续一回合 伤害30 敏捷降低2 消除暴击");
            g_Intro_Talent[i].append("\n一级：力量降低0");
            g_Intro_Talent[i].append("\n二级：力量降低30");
            g_Intro_Talent[i].append("\n三级：力量降低60");
            break;
        }
        case DUJIAOXIAN:{//雄性
            g_PetNum[i]=DUJIAOXIAN;
            g_Name[i]="独角仙兽";
            g_PrimaryA_A[i]=POWER;
            g_Element[i]=THUNDER;
            g_Life[i]=480;
            g_Power[i]=92;
            g_Defence[i]=76;
            g_Agility[i]=13;
            g_Life_Grow[i]=103;
            g_Power_Grow[i]=23;
            g_Defence_Grow[i]=16;
            g_Agility_Grow[i]=4;
            g_Cri_Rate[i]=50;
            g_Cri_Damage[i]=1.5;
            g_Dodge_Rate[i]=17;
            g_Skill1[i]=UNLOCKED;
            g_Skill2[i]=LOCKED;
            g_Talent_Time[i]=SKILL_TIME;
            g_Talent_Kind[i]=INITIATIVE;
            g_Image[i]=g_touxiang_pet+g_Name[i];
            g_Str_talent[i]="百万冲击波";
            g_Intro_Elf[i]="昆虫系精灵，力量型精灵，意外的获得了雷电的力量，成为精灵中的强者。";
            g_Intro_Talent[i]="主动技能\n"+g_Name[i];
            g_Intro_Talent[i].append("发射紫色雷球，使敌人感电，并且自己进入规避状态");
            g_Intro_Talent[i].append("\n 释放概率35% 持续两回合 感电伤害比例30% 闪避率增加10%");
            g_Intro_Talent[i].append("\n一级：伤害40 抵挡1次伤害");
            g_Intro_Talent[i].append("\n二级：伤害60 抵挡2次伤害");
            g_Intro_Talent[i].append("\n三级：伤害80 抵挡3次伤害");
            break;
        }
        case SANGSHIBAOLONG:{//雄性
            g_PetNum[i]=SANGSHIBAOLONG;
            g_Name[i]="丧尸暴龙兽";
            g_PrimaryA_A[i]=POWER;
            g_Element[i]=DARK;
            g_Life[i]=370;
            g_Power[i]=130;
            g_Defence[i]=72;
            g_Agility[i]=15;
            g_Life_Grow[i]=92;
            g_Power_Grow[i]=21;
            g_Defence_Grow[i]=19;
            g_Agility_Grow[i]=5;
            g_Cri_Rate[i]=20;
            g_Cri_Damage[i]=1.5;
            g_Dodge_Rate[i]=15;
            g_Skill1[i]=UNLOCKED;
            g_Skill2[i]=LOCKED;
            g_Talent_Time[i]=SIMPLE_ATTACK;
            g_Talent_Kind[i]=FOLLOW;
            g_Image[i]=g_touxiang_pet+g_Name[i];
            g_Str_talent[i]="湮灭猎鸟";
            g_Intro_Elf[i]="堕落的龙系精灵，力量型精灵，获得了地狱的力量，代价是只能以丧尸形态存活。";
            g_Intro_Talent[i]="追击技能\n"+g_Name[i];
            g_Intro_Talent[i].append("发射骨刺，聚集为湮灭猎鸟，改技能无法被闪避，使敌人弱化，使自己进入反伤状态");
            g_Intro_Talent[i].append("\n 释放概率50% 持续两回合 反弹伤害40 力量降低40");
            g_Intro_Talent[i].append("\n一级：反伤比例40% 防御降低20");
            g_Intro_Talent[i].append("\n二级：反伤比例50% 防御降低35");
            g_Intro_Talent[i].append("\n三级：反伤比例60% 防御降低50");
            break;
        }
        case XIANRENZHANG:{//雄性
            g_PetNum[i]=XIANRENZHANG;
            g_Name[i]="仙人掌兽";
            g_PrimaryA_A[i]=DEFENCE;
            g_Element[i]=LEAF;
            g_Life[i]=520;
            g_Power[i]=56;
            g_Defence[i]=100;
            g_Agility[i]=12;
            g_Life_Grow[i]=100;
            g_Power_Grow[i]=16;
            g_Defence_Grow[i]=20;
            g_Agility_Grow[i]=3;
            g_Cri_Rate[i]=30;
            g_Cri_Damage[i]=1.5;
            g_Dodge_Rate[i]=13;
            g_Skill1[i]=UNLOCKED;
            g_Skill2[i]=LOCKED;
            g_Talent_Time[i]=INJURED;
            g_Talent_Kind[i]=PASSIVE;
            g_Image[i]=g_touxiang_pet+g_Name[i];
            g_Str_talent[i]="尖尖碰碰拳";
            g_Intro_Elf[i]="沙漠中的精灵，防御型精灵，浑身带刺，建议你不要轻易触碰他！";
            g_Intro_Talent[i]="被动技能\n"+g_Name[i];
            g_Intro_Talent[i].append("利用身上的尖刺给敌人最痛的反击，受到攻击时立刻反击(伤害：防御*防御系数)，并且进入反伤状态。");
            g_Intro_Talent[i].append("\n 释放概率100% 持续1回合 反伤伤害20");
            g_Intro_Talent[i].append("\n一级：防御系数0.4 反伤比例20%");
            g_Intro_Talent[i].append("\n二级：防御系数0.7 反伤比例30%");
            g_Intro_Talent[i].append("\n三级：防御系数1.0 反伤比例40%");
            break;
        }
        case JIANSHISHOU:{//雄性
            g_PetNum[i]=JIANSHISHOU;
            g_Name[i]="剑狮兽";
            g_PrimaryA_A[i]=DEFENCE;
            g_Element[i]=FLAME;
            g_Life[i]=490;
            g_Power[i]=96;
            g_Defence[i]=88;
            g_Agility[i]=14;
            g_Life_Grow[i]=88;
            g_Power_Grow[i]=20;
            g_Defence_Grow[i]=25;
            g_Agility_Grow[i]=4;
            g_Cri_Rate[i]=40;
            g_Cri_Damage[i]=1.8;
            g_Dodge_Rate[i]=20;
            g_Skill1[i]=UNLOCKED;
            g_Skill2[i]=LOCKED;
            g_Talent_Time[i]=SKILL_TIME;
            g_Talent_Kind[i]=INITIATIVE;
            g_Image[i]=g_touxiang_pet+g_Name[i];
            g_Str_talent[i]="粉碎之爪";
            g_Intro_Elf[i]="浑身金黄的狮子，防御型精灵，鬃毛如利剑，獠牙如长钉。";
            g_Intro_Talent[i]="主动技能\n"+g_Name[i];
            g_Intro_Talent[i].append("的利爪有粉碎一切的力量包括敌人的攻击，使敌人进入禁锢状态无法使用主动技能，使自己进入规避状态。");
            g_Intro_Talent[i].append("\n 释放概率30% 持续2回合 50%概率驱散敌人有利效果 无规避伤害次数");
            g_Intro_Talent[i].append("\n一级：闪避率增加20%");
            g_Intro_Talent[i].append("\n二级：闪避率增加35%");
            g_Intro_Talent[i].append("\n三级：闪避率增加50%");
            break;
        }
        case GANGTIEHAILONG:{//雄性
            g_PetNum[i]=GANGTIEHAILONG;
            g_Name[i]="钢铁海龙兽";
            g_PrimaryA_A[i]=DEFENCE;
            g_Element[i]=ICE;
            g_Life[i]=512;
            g_Power[i]=70;
            g_Defence[i]=110;
            g_Agility[i]=12;
            g_Life_Grow[i]=100;
            g_Power_Grow[i]=18;
            g_Defence_Grow[i]=22;
            g_Agility_Grow[i]=5;
            g_Cri_Rate[i]=30;
            g_Cri_Damage[i]=2;
            g_Dodge_Rate[i]=25;
            g_Skill1[i]=UNLOCKED;
            g_Skill2[i]=LOCKED;
            g_Talent_Time[i]=SKILL_TIME;
            g_Talent_Kind[i]=INITIATIVE;
            g_Image[i]=g_touxiang_pet+g_Name[i];
            g_Str_talent[i]="究极波浪炮";
            g_Intro_Elf[i]="海中霸王，防御型精灵，浑身包裹着金属，力量强大，行动敏捷，坚不可摧。";
            g_Intro_Talent[i]="主动技能\n"+g_Name[i];
            g_Intro_Talent[i].append("汇聚大海的力量，发射究极波浪炮，使敌人眩晕，使自己进入侵略状态属性变为暗");
            g_Intro_Talent[i].append("\n 持续2回合 无视免疫 防御降低40");
            g_Intro_Talent[i].append("\n一级：释放概率20% 力量增加20");
            g_Intro_Talent[i].append("\n二级：释放概率25% 力量增加40");
            g_Intro_Talent[i].append("\n三级：释放概率30% 力量增加60");
            break;
        }
        case ZUDUNSHOU:{//雄性
            g_PetNum[i]=ZUDUNSHOU;
            g_Name[i]="祖顿兽";
            g_PrimaryA_A[i]=DEFENCE;
            g_Element[i]=THUNDER;
            g_Life[i]=580;
            g_Power[i]=80;
            g_Defence[i]=92;
            g_Agility[i]=11;
            g_Life_Grow[i]=93;
            g_Power_Grow[i]=16;
            g_Defence_Grow[i]=21;
            g_Agility_Grow[i]=3;
            g_Cri_Rate[i]=10;
            g_Cri_Damage[i]=2.1;
            g_Dodge_Rate[i]=15;
            g_Skill1[i]=UNLOCKED;
            g_Skill2[i]=LOCKED;
            g_Talent_Time[i]=BEGIN;
            g_Talent_Kind[i]=COMMAND;
            g_Image[i]=g_touxiang_pet+g_Name[i];
            g_Str_talent[i]="重锤火花";
            g_Intro_Elf[i]="防御力极强的防御型精灵，手握重锤，身背坚壳。";
            g_Intro_Talent[i]="指挥技能\n"+g_Name[i];
            g_Intro_Talent[i].append("挥舞重锤，锤击大地，迸溅火花，造成伤害的同时给自身添加护盾");
            g_Intro_Talent[i].append("\n 释放概率30% 持续两回合");
            g_Intro_Talent[i].append("\n一级：伤害降低20% 添加100的护盾");
            g_Intro_Talent[i].append("\n二级：伤害降低30% 添加150的护盾");
            g_Intro_Talent[i].append("\n三级：伤害降低40% 添加200的护盾");
            break;
        }
        case EMOSHOU:{//雄性
            g_PetNum[i]=EMOSHOU;
            g_Name[i]="恶魔兽";
            g_PrimaryA_A[i]=DEFENCE;
            g_Element[i]=DARK;
            g_Life[i]=464;
            g_Power[i]=76;
            g_Defence[i]=97;
            g_Agility[i]=15;
            g_Life_Grow[i]=95;
            g_Power_Grow[i]=16;
            g_Defence_Grow[i]=20;
            g_Agility_Grow[i]=4;
            g_Cri_Rate[i]=20;
            g_Cri_Damage[i]=1.7;
            g_Dodge_Rate[i]=18;
            g_Skill1[i]=UNLOCKED;
            g_Skill2[i]=LOCKED;
            g_Talent_Time[i]=SIMPLE_ATTACK;
            g_Talent_Kind[i]=FOLLOW;
            g_Image[i]=g_touxiang_pet+g_Name[i];
            g_Str_talent[i]="死亡之爪";
            g_Intro_Elf[i]="来自地狱的使者，防御型精灵，享受屠戮。";
            g_Intro_Talent[i]="追击技能\n"+g_Name[i];
            g_Intro_Talent[i].append("发动死亡之爪，撕裂敌人伤口，使自己进入嗜血状态");
            g_Intro_Talent[i].append("\n 释放概率80% 持续1回合 无每回合扣血");
            g_Intro_Talent[i].append("\n一级：吸血百分比50%");
            g_Intro_Talent[i].append("\n二级：吸血百分比75%");
            g_Intro_Talent[i].append("\n三级：吸血百分比100%");
            break;
        }
        case MUOUSHOU:{//雄性
            g_PetNum[i]=MUOUSHOU;
            g_Name[i]="木偶兽";
            g_PrimaryA_A[i]=AGILITY;
            g_Element[i]=LEAF;
            g_Life[i]=420;
            g_Power[i]=55;
            g_Defence[i]=60;
            g_Agility[i]=16;
            g_Life_Grow[i]=100;
            g_Power_Grow[i]=18;
            g_Defence_Grow[i]=15;
            g_Agility_Grow[i]=4;
            g_Cri_Rate[i]=30;
            g_Cri_Damage[i]=1.8;
            g_Dodge_Rate[i]=22;
            g_Skill1[i]=UNLOCKED;
            g_Skill2[i]=LOCKED;
            g_Talent_Time[i]=INJURED;
            g_Talent_Kind[i]=PASSIVE;
            g_Image[i]=g_touxiang_pet+g_Name[i];
            g_Str_talent[i]="顽劣之剧";
            g_Intro_Elf[i]="来源不明的木偶，敏捷型精灵，拥有操纵他人的能力，天性顽劣。";
            g_Intro_Talent[i]="被动技能\n"+g_Name[i];
            g_Intro_Talent[i].append("放出木偶线，控制敌人攻击自身，同时使其暴躁。");
            g_Intro_Talent[i].append("\n 持续2回合 禁用被动 不降低主动概率 反弹本次伤害 回复本次受到的伤害");
            g_Intro_Talent[i].append("\n一级：释放概率30%");
            g_Intro_Talent[i].append("\n二级：释放概率45%");
            g_Intro_Talent[i].append("\n三级：释放概率60%");
            break;
        }
        case JIALOULUOSHOU:{//雌性
            g_PetNum[i]=JIALOULUOSHOU;
            g_Name[i]="迦楼罗兽";
            g_PrimaryA_A[i]=AGILITY;
            g_Element[i]=FLAME;
            g_Life[i]=580;
            g_Power[i]=88;
            g_Defence[i]=88;
            g_Agility[i]=16;
            g_Life_Grow[i]=100;
            g_Power_Grow[i]=15;
            g_Defence_Grow[i]=17;
            g_Agility_Grow[i]=6;
            g_Cri_Rate[i]=20;
            g_Cri_Damage[i]=2;
            g_Dodge_Rate[i]=20;
            g_Skill1[i]=UNLOCKED;
            g_Skill2[i]=LOCKED;
            g_Talent_Time[i]=SKILL_TIME;
            g_Talent_Kind[i]=INITIATIVE;
            g_Image[i]=g_touxiang_pet+g_Name[i];
            g_Str_talent[i]="影翼斩";
            g_Intro_Elf[i]="来自神域的火焰使者，敏捷型精灵，兽人形态，可化身火焰，驭火飞天。";
            g_Intro_Talent[i]="主动技能\n"+g_Name[i];
            g_Intro_Talent[i].append("化身为火焰雕，俯冲敌人，使其灼烧并且用火焰给自身添加护盾");
            g_Intro_Talent[i].append("\n 释放概率50% 灼烧持续1回合 护盾持续2回合 护盾吸收伤害80 灼烧伤害30");
            g_Intro_Talent[i].append("\n一级：灼烧伤害比例4% 伤害降低20%");
            g_Intro_Talent[i].append("\n二级：灼烧伤害比例6% 伤害降低25%");
            g_Intro_Talent[i].append("\n三级：灼烧伤害比例8% 伤害降低30%");
            break;
        }
        case LANGRENJIALULU:{//雄性
            g_PetNum[i]=LANGRENJIALULU;
            g_Name[i]="狼人加鲁鲁兽";
            g_PrimaryA_A[i]=AGILITY;
            g_Element[i]=ICE;
            g_Life[i]=488;
            g_Power[i]=99;
            g_Defence[i]=80;
            g_Agility[i]=15;
            g_Life_Grow[i]=101;
            g_Power_Grow[i]=19;
            g_Defence_Grow[i]=16;
            g_Agility_Grow[i]=6;
            g_Cri_Rate[i]=30;
            g_Cri_Damage[i]=2.0;
            g_Dodge_Rate[i]=25;
            g_Skill1[i]=UNLOCKED;
            g_Skill2[i]=LOCKED;
            g_Talent_Time[i]=SIMPLE_ATTACK;
            g_Talent_Kind[i]=FOLLOW;
            g_Image[i]=g_touxiang_pet+g_Name[i];
            g_Str_talent[i]="凯撒锐爪";
            g_Intro_Elf[i]="兽人形态加鲁鲁，敏捷型精灵，行动极为敏捷，喜欢独自行动，无拘无束。";
            g_Intro_Talent[i]="追击技能\n"+g_Name[i];
            g_Intro_Talent[i].append("将凯撒之力注入双爪，撕裂敌人，并且使自己兴奋，嗜血");
            g_Intro_Talent[i].append("\n 释放概率40% 持续两回合 暴击率加20% 每回合扣血30");
            g_Intro_Talent[i].append("\n一级：吸血百分比20% 敏捷增加5");
            g_Intro_Talent[i].append("\n二级：吸血百分比30% 敏捷增加10");
            g_Intro_Talent[i].append("\n三级：吸血百分比40% 敏捷增加15");
            break;
        }
        case AOMIJIASHOU:{//雄性
            g_PetNum[i]=AOMIJIASHOU;
            g_Name[i]="欧米伽兽";
            g_PrimaryA_A[i]=AGILITY;
            g_Element[i]=THUNDER;
            g_Life[i]=500;
            g_Power[i]=105;
            g_Defence[i]=90;
            g_Agility[i]=15;
            g_Life_Grow[i]=80;
            g_Power_Grow[i]=16;
            g_Defence_Grow[i]=18;
            g_Agility_Grow[i]=7;
            g_Cri_Rate[i]=5;
            g_Cri_Damage[i]=4;
            g_Dodge_Rate[i]=18;
            g_Skill1[i]=UNLOCKED;
            g_Skill2[i]=LOCKED;
            g_Talent_Time[i]=BEGIN;
            g_Talent_Kind[i]=COMMAND;
            g_Image[i]=g_touxiang_pet+g_Name[i];
            g_Str_talent[i]="暴龙加鲁鲁";
            g_Intro_Elf[i]="战斗暴龙兽与钢铁加鲁鲁的合体，敏捷型精灵，皇家骑士之一。";
            g_Intro_Talent[i]="指挥技能\n"+g_Name[i];
            g_Intro_Talent[i].append("拥有两大杀器暴龙剑与加鲁鲁炮，发动技能可以造成大规模杀伤，使敌人禁锢，使自己专注。");
            g_Intro_Talent[i].append("\n 释放概率35% 持续2回合 禁用普攻或主动 驱散有利效果");
            g_Intro_Talent[i].append("\n一级：防御增加40 生命回复40");
            g_Intro_Talent[i].append("\n二级：防御增加60 生命回复60");
            g_Intro_Talent[i].append("\n三级：防御增加80 生命回复80");
            break;
        }
        case NVEMOSHOU:{//雌性
            g_PetNum[i]=NVEMOSHOU;
            g_Name[i]="女恶魔兽";
            g_PrimaryA_A[i]=AGILITY;
            g_Element[i]=DARK;
            g_Life[i]=508;
            g_Power[i]=80;
            g_Defence[i]=76;
            g_Agility[i]=20;
            g_Life_Grow[i]=105;
            g_Power_Grow[i]=15;
            g_Defence_Grow[i]=10;
            g_Agility_Grow[i]=5;
            g_Cri_Rate[i]=25;
            g_Cri_Damage[i]=2;
            g_Dodge_Rate[i]=21;
            g_Skill1[i]=UNLOCKED;
            g_Skill2[i]=LOCKED;
            g_Talent_Time[i]=INJURED;
            g_Talent_Kind[i]=PASSIVE;
            g_Image[i]=g_touxiang_pet+g_Name[i];
            g_Str_talent[i]="暗黑波动";
            g_Intro_Elf[i]="来自地狱的女恶魔，敏捷型精灵，曾今是女天使兽，堕落之后化身恶魔。";
            g_Intro_Talent[i]="被动技能\n"+g_Name[i];
            g_Intro_Talent[i].append("受到攻击后释放暗黑波动，使敌人弱化，使自己侵略");
            g_Intro_Talent[i].append("\n 释放概率30% 持续两回合 元素为暗 力量增加50");
            g_Intro_Talent[i].append("\n一级：防御降低50 力量降低50");
            g_Intro_Talent[i].append("\n二级：防御降低75 力量降低75");
            g_Intro_Talent[i].append("\n三级：防御降低100 力量降低100");
            break;
        }
        }
    }
    for(int i=0;i<ALLSKILL;i++){//初始化技能数据
        switch(i){
        case FLAME_ATTACK:{
            g_Str_skill[i]="火焰攻击";
            g_Intro_Skill[i]="主动技能\n精灵获取大自然中火焰的力量，进入侵略状态，改变自身主属性为火属性并且提升力量。";
            g_Intro_Skill[i].append("\n持续3回合");
            g_Intro_Skill[i].append("\n一级：释放概率30% 力量提升20");
            g_Intro_Skill[i].append("\n二级：释放概率35% 力量提升35");
            g_Intro_Skill[i].append("\n三级：释放概率40% 力量提升50");
            g_Skill_Time[i]=SKILL_TIME;
            g_Skill_Kind[i]=INITIATIVE;
            break;
        }
        case THUNDER_ATTACK:{
            g_Str_skill[i]="雷电攻击";
            g_Intro_Skill[i]="主动技能\n精灵获取大自然中雷电的力量，进入侵略状态，改变自身主属性为雷属性并且提升力量。";
            g_Intro_Skill[i].append("\n持续3回合");
            g_Intro_Skill[i].append("\n一级：释放概率30% 力量提升20");
            g_Intro_Skill[i].append("\n二级：释放概率35% 力量提升35");
            g_Intro_Skill[i].append("\n三级：释放概率40% 力量提升50");
            g_Skill_Time[i]=SKILL_TIME;
            g_Skill_Kind[i]=INITIATIVE;
            break;
        }
        case ICE_ATTACK:{
            g_Str_skill[i]="冰冻攻击";
            g_Intro_Skill[i]="主动技能\n精灵获取大自然中冰雪的力量，进入侵略状态，改变自身主属性为冰属性并且提升力量。";
            g_Intro_Skill[i].append("\n持续3回合");
            g_Intro_Skill[i].append("\n一级：释放概率30% 力量提升20");
            g_Intro_Skill[i].append("\n二级：释放概率35% 力量提升35");
            g_Intro_Skill[i].append("\n三级：释放概率40% 力量提升50");
            g_Skill_Time[i]=SKILL_TIME;
            g_Skill_Kind[i]=INITIATIVE;
            break;
        }
        case LEAF_ATTACK:{
            g_Str_skill[i]="翠叶攻击";
            g_Intro_Skill[i]="主动技能\n精灵获取大自然的力量，进入侵略状态，改变自身主属性为叶属性并且提升力量。";
            g_Intro_Skill[i].append("\n持续3回合");
            g_Intro_Skill[i].append("\n一级：释放概率30% 力量提升20");
            g_Intro_Skill[i].append("\n二级：释放概率35% 力量提升35");
            g_Intro_Skill[i].append("\n三级：释放概率40% 力量提升50");
            g_Skill_Time[i]=SKILL_TIME;
            g_Skill_Kind[i]=INITIATIVE;
            break;
        }
        case DARK_ATTACK:{
            g_Str_skill[i]="黑暗攻击";
            g_Intro_Skill[i]="主动技能\n精灵获取大自然中黑暗的力量，进入侵略状态，改变自身主属性为暗属性并且提升力量。";
            g_Intro_Skill[i].append("\n持续3回合");
            g_Intro_Skill[i].append("\n一级：释放概率30% 力量提升20");
            g_Intro_Skill[i].append("\n二级：释放概率35% 力量提升35");
            g_Intro_Skill[i].append("\n三级：释放概率40% 力量提升50");
            g_Skill_Time[i]=SKILL_TIME;
            g_Skill_Kind[i]=INITIATIVE;
            break;
        }
        case XILI:{
            g_Str_skill[i]="洗礼";
            g_Intro_Skill[i]="主动技能\n精灵接受圣光洗礼，立刻为自己回复一定生命。";
            g_Intro_Skill[i].append("\n释放概率35% 对叶系精灵效果加成30% 对暗系精灵效果减少30%");
            g_Intro_Skill[i].append("\n一级：回复60点生命");
            g_Intro_Skill[i].append("\n二级：回复100点生命");
            g_Intro_Skill[i].append("\n三级：回复140点生命");
            g_Skill_Time[i]=SKILL_TIME;
            g_Skill_Kind[i]=INITIATIVE;
            break;
        }
        case BUQUYIZHI:{
            g_Str_skill[i]="不屈意志";
            g_Intro_Skill[i]="被动技能\n精灵拥有不屈的斗志，每受到一次伤害永久增加一定的属性(四种属性中的一种)。";
            g_Intro_Skill[i].append("\n释放概率100% 四种属性概率相等");
            g_Intro_Skill[i].append("\n一级：力量，防御增加10 生命增加20 敏捷增加2");
            g_Intro_Skill[i].append("\n二级：力量，防御增加20 生命增加40 敏捷增加4");
            g_Intro_Skill[i].append("\n三级：力量，防御增加30 生命增加60 敏捷增加6");
            g_Skill_Time[i]=INJURED;
            g_Skill_Kind[i]=PASSIVE;
            break;
        }
        case XIANXVEKEWANG:{
            g_Str_skill[i]="鲜血渴望";
            g_Intro_Skill[i]="指挥技能\n精灵贪恋杀戮，进入嗜血状态。";
            g_Intro_Skill[i].append("\n释放概率100% 持续一回合 立即失去20点生命");
            g_Intro_Skill[i].append("\n一级：吸血比例30%");
            g_Intro_Skill[i].append("\n二级：吸血比例40%");
            g_Intro_Skill[i].append("\n三级：吸血比例50%");
            g_Skill_Time[i]=BEGIN;
            g_Skill_Kind[i]=COMMAND;
            break;
        }
        case XIANQUTUJI:{
            g_Str_skill[i]="先驱突击";
            g_Intro_Skill[i]="主动技能\n精灵掌握先机，进行第二次普攻。";
            g_Intro_Skill[i].append("\n若被禁用普攻或主动都无法释放该技能");
            g_Intro_Skill[i].append("\n一级：释放概率35%");
            g_Intro_Skill[i].append("\n二级：释放概率50%");
            g_Intro_Skill[i].append("\n三级：释放概率65%");
            g_Skill_Time[i]=SKILL_TIME;
            g_Skill_Kind[i]=INITIATIVE;
            break;
        }
        default:{
            if(i==LOCKED){
                g_Str_skill[i]="未解锁";
                g_Intro_Skill[i]="你可以通过交钱或者联系作者解锁第二个技能！";
            }
            if(i==UNLOCKED){
                g_Str_skill[i]="可学习";
                g_Intro_Skill[i]="快点给你的精灵学习一个技能吧！";
            }
            g_Skill_Time[i]=NOTHING;
            g_Skill_Kind[i]=INITIATIVE;
        }
        }
    }
}


void EleRatioAdd(int r){
    if(g_ele_ratio<1){
    g_ele_ratio+=r/100.0;
    if(g_ele_ratio>1)
        g_ele_ratio=1;
    int i=g_ele_ratio*100;
    QString s=QString::number(i);
    g_message=g_message+"\n"+"元素之力变为"+s+"！";
    }
}
