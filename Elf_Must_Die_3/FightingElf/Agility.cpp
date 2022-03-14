#include "AdvanceElf.h"
//敏捷型精灵
Attack MuOuShou::Talent()
{
//    g_Str_talent[i]="顽劣之剧";
//    g_Intro_Elf[i]="来源不明的木偶，敏捷型精灵，拥有操纵他人的能力，天性顽劣。";
//    g_Intro_Talent[i]="主动技能\n"+g_Name[i];
//    g_Intro_Talent[i].append("放出木偶线，控制敌人攻击自身，同时使其暴躁。");
//    g_Intro_Talent[i].append("\n 持续2回合 禁用被动 不降低主动概率 反弹本次伤害 回复本次受到的伤害");
//    g_Intro_Talent[i].append("\n一级：释放概率30%");
//    g_Intro_Talent[i].append("\n二级：释放概率45%");
//    g_Intro_Talent[i].append("\n三级：释放概率60%");

    int i=RANDOM(100);
    int i1;
    if(tal_level==1){
        i1=30;
    }
    else if(tal_level==2){
        i1=45;
    }
    else{
        i1=60;
    }
    if(i<=i1){
        return_attack.happen=true;
        return_attack.is_back=true;
        return_attack.ignore=true;
        return_attack.special_effects=element;

        life+=return_attack.blood_sucking;
        if(life>life_back)
            life=life_back;
        return_attack.ele_damage[element]+=return_attack.blood_sucking;
        g_message=g_message+"\n"+name+"发动了天赋技能:";
        g_message.append(g_Str_talent[pet_num]+",反弹受到的伤害！");
        GBaoZao(return_attack,0,1,2);
    }
    return return_attack;
}

Attack JiaLouLuoShou::Talent()
{
//    g_Str_talent[i]="影翼斩";
//    g_Intro_Elf[i]="来自神域的火焰使者，敏捷型精灵，兽人形态，可化身火焰，驭火飞天。";
//    g_Intro_Talent[i]="主动技能\n"+g_Name[i];
//    g_Intro_Talent[i].append("化身为火焰雕，俯冲敌人，使其灼烧并且用火焰给自身添加护盾");
//    g_Intro_Talent[i].append("\n 释放概率50% 灼烧持续1回合 护盾持续2回合 护盾吸收伤害80 灼烧伤害30");
//    g_Intro_Talent[i].append("\n一级：灼烧伤害比例4% 伤害降低20%");
//    g_Intro_Talent[i].append("\n二级：灼烧伤害比例6% 伤害降低25%");
//    g_Intro_Talent[i].append("\n三级：灼烧伤害比例8% 伤害降低30%");
    Attack a;
    int i=RANDOM(100);
    if(i<=50){//概率释放
        int p=CriOrNot();//计算总伤害
        int e=p*g_ele_ratio;//元素伤害
        a.ele_damage[element]+=e;
        a.ele_damage[LEAF]+=p-e;
        a.happen=true;
        a.special_effects=element;
        int i1,i2;
        if(tal_level==1){
            i1=4,i2=20;
        }
        else if(tal_level==2){
            i1=6,i2=25;
        }
        else{
            i1=8,i2=30;
        }
        g_message=g_message+"\n"+name+"发动了天赋技能:";
        g_message.append(g_Str_talent[pet_num]+"！");
        GZhuoShao(a,i1,30,1);
        GHuDun(i2,80,2);
    }
    return a;
}

Attack LangRenJiaLuLu::SimpleAttack()
{
//    g_Str_talent[i]="凯撒锐爪";
//    g_Intro_Elf[i]="兽人形态加鲁鲁，敏捷型精灵，行动极为敏捷，喜欢独自行动，无拘无束。";
//    g_Intro_Talent[i]="追击技能\n"+g_Name[i];
//    g_Intro_Talent[i].append("将凯撒之力注入双爪，撕裂敌人，并且使自己兴奋，嗜血");
//    g_Intro_Talent[i].append("\n 释放概率40% 持续两回合 暴击率加20% 每回合扣血30");
//    g_Intro_Talent[i].append("\n一级：吸血百分比20% 敏捷增加5");
//    g_Intro_Talent[i].append("\n二级：吸血百分比30% 敏捷增加10");
//    g_Intro_Talent[i].append("\n三级：吸血百分比40% 敏捷增加15");
    Attack a;
    g_message=g_message+'\n'+name+"发动了普通攻击！";
    int p=CriOrNot();//计算总伤害
    int e=p*g_ele_ratio;//元素伤害
    a.ele_damage[element]+=e;
    a.ele_damage[LEAF]+=p-e;
    a.happen=true;

    int i=RANDOM(100);

    if(i<=40){//概率释放
        a.special_effects=element;
        int i1,i2;
        if(tal_level==1){
            i1=20,i2=5;
        }
        else if(tal_level==2){
            i1=30,i2=10;
        }
        else{
            i1=40,i2=15;
        }

        g_message=g_message+"\n"+name+"发动了天赋技能:";
        g_message.append(g_Str_talent[pet_num]+"！");
        GShiXve(i1,30,2);
        GXingFen(i2,20,2);
    }
    if(state_fighting[GANDIAN][1]>0){
        JGanDian(a,SIMPLE_ATTACK);
    }
    return a;
}

Attack AoMiJiaShou::Talent()
{
//    g_Str_talent[i]="暴龙加鲁鲁";
//    g_Intro_Elf[i]="战斗暴龙兽与钢铁加鲁鲁的合体，敏捷型精灵，皇家骑士之一。";
//    g_Intro_Talent[i]="指挥技能\n"+g_Name[i];
//    g_Intro_Talent[i].append("拥有两大杀器暴龙剑与加鲁鲁炮，发动技能可以造成大规模杀伤，使敌人禁锢，使自己专注。");
//    g_Intro_Talent[i].append("\n 释放概率35% 持续2回合 禁用普攻或主动 驱散有利效果");
//    g_Intro_Talent[i].append("\n一级：防御增加40 生命回复40");
//    g_Intro_Talent[i].append("\n二级：防御增加60 生命回复60");
//    g_Intro_Talent[i].append("\n三级：防御增加80 生命回复80");
    Attack a;

    int i=RANDOM(100);
    if(i<=35){
        a.happen=true;
        a.special_effects=element;
        int i1,i2;
        if(tal_level==1){
            i1=40;
            i2=40;
        }
        else if(tal_level==2){
            i1=60;
            i2=60;
        }
        else{
            i1=80;
            i2=80;
        }
        int i3=i%2;
        g_message=g_message+"\n"+name+"发动了天赋技能:";
        g_message.append(g_Str_talent[pet_num]+"！");
        GJinGu(a,i3,1,2);
        GZhuanZhu(i2,i1,2);
    }
    return a;
}

Attack NvEMoShou::Talent()
{
//    g_Str_talent[i]="暗黑波动";
//    g_Intro_Elf[i]="来自地狱的女恶魔，敏捷型精灵，曾今是女天使兽，堕落之后化身恶魔。";
//    g_Intro_Talent[i]="被动技能\n"+g_Name[i];
//    g_Intro_Talent[i].append("受到攻击后释放暗黑波动，使敌人弱化，使自己侵略");
//    g_Intro_Talent[i].append("\n 释放概率30% 持续两回合 元素为暗 力量增加50");
//    g_Intro_Talent[i].append("\n一级：防御降低50 力量降低50");
//    g_Intro_Talent[i].append("\n二级：防御降低75 力量降低75");
//    g_Intro_Talent[i].append("\n三级：防御降低100 力量降低100");

    int i=RANDOM(100);
    if(i<=30){
        return_attack.happen=true;
        return_attack.is_back=true;
        return_attack.ignore=true;
        return_attack.special_effects=element;
        int i1,i2;
        if(tal_level==1){
            i1=50;
            i2=50;
        }
        else if(tal_level==2){
            i1=75;
            i2=75;
        }
        else{
            i1=100;
            i2=100;
        }
        g_message=g_message+"\n"+name+"发动了天赋技能:";
        g_message.append(g_Str_talent[pet_num]+"！");
        GQinLve(50,DARK,2);
        GRuoHua(return_attack,i1,i2,2);
    }
    return return_attack;
}

