#include "AdvanceElf.h"
//生命型精灵
Attack XuanWUShou::Talent()
{
//    g_Str_talent[i]="雾幻";
//    g_Intro_Elf[i]="大自然的守护神，生命型精灵，有两只头，身体由原始森林组成的巨型神兽。";
//    g_Intro_Talent[i]="指挥技能\n"+g_Name[i];
//    g_Intro_Talent[i].append("利用背部的原始森林创造雾气，制造幻影，使自己进入免疫状态，使敌人进入犹豫状态");
//    g_Intro_Talent[i].append("\n释放概率100% 持续2回合 消除暴击");
//    g_Intro_Talent[i].append("\n一级：所有伤害降低20% 敏捷降低3");
//    g_Intro_Talent[i].append("\n二级：所有伤害降低30% 敏捷降低5");
//    g_Intro_Talent[i].append("\n三级：所有伤害降低40% 敏捷降低7");
    Attack a;
    a.happen=true;
    a.ignore=true;
    a.special_effects=element;

    int i1,i2;
    if(tal_level==1){
        i1=20;
        i2=3;
    }
    else if(tal_level==2){
        i1=30;
        i2=5;
    }
    else{
        i1=40;
        i2=7;
    }
    g_message=g_message+"\n"+name+"发动了天赋技能:";
    g_message.append(g_Str_talent[pet_num]+"！");
    GYouYu(a,i2,1,2);
    GMianYi(i1,i1,2);
    return a;
}

Attack BaoLongShou::Talent()
{
//    g_Str_talent[i]="超级火焰";
//    g_Intro_Elf[i]="远古巨龙，生命型精灵，口吐火焰，脾气暴躁。";
//    g_Intro_Talent[i]="主动技能\n"+g_Name[i];
//    g_Intro_Talent[i].append("喷射大量火焰，使敌人陷入灼烧状态，使自己进入兴奋状态");
//    g_Intro_Talent[i].append("\n释放概率30% 持续3回合 伤害比例5% 敏捷增加2");
//    g_Intro_Talent[i].append("\n一级：伤害20 暴击率增加10%");
//    g_Intro_Talent[i].append("\n二级：伤害35 暴击率增加20%");
//    g_Intro_Talent[i].append("\n三级：伤害50 暴击率增加30%");
    Attack a;
    int i=RANDOM(100);
    if(i<=30){//概率释放
        int i1,i2;
        if(tal_level==1){
            i1=20,i2=10;
        }
        else if(tal_level==2){
            i1=35,i2=20;
        }
        else{
            i1=50,i2=30;
        }
        g_message=g_message+"\n"+name+"发动了天赋技能:";
        g_message.append(g_Str_talent[pet_num]+"！");
        GZhuoShao(a,5,i1,3);
        GXingFen(2,i2,3);
        int p=CriOrNot();//计算总伤害
        int e=p*g_ele_ratio;//元素伤害
        a.ele_damage[element]+=e;
        a.ele_damage[LEAF]+=p-e;
        a.happen=true;
        a.special_effects=element;

    }
    return a;
}

Attack JiaLuLuShou::Talent()
{
//    g_Str_talent[i]="妖狐火焰";
//    g_Intro_Elf[i]="加鲁鲁族成员，生命型精灵，兽形态，体质寒凉，可以喷射奇特的低温火焰。";
//    g_Intro_Talent[i]="主动技能\n"+g_Name[i];
//    g_Intro_Talent[i].append("喷射低温蓝火，使敌人陷入眩晕状态");
//    g_Intro_Talent[i].append("\n 持续1回合 可以被免疫");
//    g_Intro_Talent[i].append("\n一级：释放概率25% 防御降低30");
//    g_Intro_Talent[i].append("\n二级：释放概率30% 防御降低45");
//    g_Intro_Talent[i].append("\n三级：释放概率35% 防御降低60");
    Attack a;
    int i=RANDOM(100);
    int i1,i2;
    if(tal_level==1){
        i1=25,i2=30;
    }
    else if(tal_level==2){
        i1=30,i2=45;
    }
    else{
        i1=35,i2=60;
    }
    if(i<=i1){//概率释放
        int p=CriOrNot();//计算总伤害
        int e=p*g_ele_ratio;//元素伤害
        a.ele_damage[element]+=e;
        a.ele_damage[LEAF]+=p-e;
        a.happen=true;
        a.special_effects=element;

        g_message=g_message+"\n"+name+"发动了天赋技能:";
        g_message.append(g_Str_talent[pet_num]+"！");
        GXuanYun(a,i2,0,1);
    }
    return a;
}

Attack QingLongShou::SimpleAttack()
{
//    g_Str_talent[i]="苍雷";
//    g_Intro_Elf[i]="巨大的天空守护神，生命型精灵，浑身缠绕闪电与锁链。";
//    g_Intro_Talent[i]="追击技能\n"+g_Name[i];
//    g_Intro_Talent[i].append("召唤雷云，释放苍雷，使敌人暴躁，感电，使自己专注");
//    g_Intro_Talent[i].append("\n 释放概率40% 持续2回合 禁用被动 防御增加50 受到雷电伤害增加40%");
//    g_Intro_Talent[i].append("\n一级：主动概率降低6% 生命恢复30 攻击时受到雷电伤害30");
//    g_Intro_Talent[i].append("\n二级：主动概率降低9% 生命恢复40 攻击时受到雷电伤害50");
//    g_Intro_Talent[i].append("\n三级：主动概率降低12% 生命恢复50 攻击时受到雷电伤害70");
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
        int i1,i2,i3;
        if(tal_level==1){
            i1=6,i2=30,i3=30;
        }
        else if(tal_level==2){
            i1=9,i2=40,i3=50;
        }
        else{
            i1=12,i2=50,i3=70;
        }

        g_message=g_message+"\n"+name+"发动了天赋技能:";
        g_message.append(g_Str_talent[pet_num]+"！");
        GBaoZao(a,i1,1,2);
        GGanDian(a,40,i3,2);
        GZhuanZhu(i2,50,2);
    }
    if(state_fighting[GANDIAN][1]>0){
        JGanDian(a,SIMPLE_ATTACK);
    }
    return a;
}

Attack YuanDuXiXveGui::Talent()
{
//    g_Str_talent[i]="剧毒流注";
//    g_Intro_Elf[i]="最邪恶的存在之一，生命型精灵，身体中剧毒涌动，怨念丛生。";
//    g_Intro_Talent[i]="被动技能\n"+g_Name[i];
//    g_Intro_Talent[i].append("受到攻击时会让攻击者沾染剧毒，进入中毒状态，自身进入嗜血状态");
//    g_Intro_Talent[i].append("\n 释放概率100% 持续两回合 吸血百分比为已损失生命百分比*吸血系数 立即造成50点伤害 中毒伤害40 敏捷降低3");
//    g_Intro_Talent[i].append("\n一级：吸血系数1.2 每回合扣血20");
//    g_Intro_Talent[i].append("\n二级：吸血系数1.8 每回合扣血40");
//    g_Intro_Talent[i].append("\n三级：吸血系数2.4 每回合扣血60");
    return_attack.happen=true;
    return_attack.is_back=true;
    return_attack.ignore=true;
    return_attack.special_effects=element;
    return_attack.ele_damage[DARK]+=50;

    int i1,i2;
    if(tal_level==1){
        i1=120;
        i2=20;
    }
    else if(tal_level==2){
        i1=180;
        i2=40;
    }
    else{
        i1=240;
        i2=60;
    }
    float i3=(float)(life_back-life)/life_back;
    i1*=i3;
    g_message=g_message+"\n"+name+"发动了天赋技能:";
    g_message.append(g_Str_talent[pet_num]+"！");
    GShiXve(i1,i2,2);
    GZhongDu(return_attack,40,3,2);
    return return_attack;
}

