#include "AdvanceElf.h"
//防御型精灵
Attack XianRenZhang::Talent()
{
//    g_Str_talent[i]="尖尖碰碰拳";
//    g_Intro_Elf[i]="沙漠中的精灵，防御型精灵，浑身带刺，建议你不要轻易触碰他！";
//    g_Intro_Talent[i]="被动技能\n"+g_Name[i];
//    g_Intro_Talent[i].append("利用身上的尖刺给敌人最痛的反击，受到攻击时立刻反击(伤害：防御*防御系数)，并且进入反伤状态。");
//    g_Intro_Talent[i].append("\n 释放概率100% 持续1回合 反伤伤害20");
//    g_Intro_Talent[i].append("\n一级：防御系数0.4 反伤比例20%");
//    g_Intro_Talent[i].append("\n二级：防御系数0.7 反伤比例30%");
//    g_Intro_Talent[i].append("\n三级：防御系数1.0 反伤比例40%");
    return_attack.happen=true;
    return_attack.is_back=true;
    return_attack.ignore=true;
    return_attack.special_effects=element;

    float i1;
    int i2;
    if(tal_level==1){
        i1=0.4;
        i2=20;
    }
    else if(tal_level==2){
        i1=0.7;
        i2=30;
    }
    else{
        i1=1.0;
        i2=40;
    }
    int i3=i1*defence;
    g_message=g_message+"\n"+name+"发动了天赋技能:";
    g_message.append(g_Str_talent[pet_num]+"！");
    GFanShang(i2,20,1);
    return_attack.ele_damage[element]+=i3;
    return return_attack;
}

Attack JianShiShou::Talent()
{
//    g_Str_talent[i]="粉碎之爪";
//    g_Intro_Elf[i]="浑身金黄的狮子，防御型精灵，鬃毛如利剑，獠牙如长钉。";
//    g_Intro_Talent[i]="主动技能\n"+g_Name[i];
//    g_Intro_Talent[i].append("的利爪有粉碎一切的力量包括敌人的攻击，使敌人进入禁锢状态无法使用主动技能，使自己进入规避状态。");
//    g_Intro_Talent[i].append("\n 释放概率30% 持续2回合 50%概率驱散敌人有利效果 无规避伤害次数");
//    g_Intro_Talent[i].append("\n一级：闪避率增加20%");
//    g_Intro_Talent[i].append("\n二级：闪避率增加35%");
//    g_Intro_Talent[i].append("\n三级：闪避率增加50%");
    Attack a;
    int i=RANDOM(100);
    if(i<=30){//概率释放
        int p=CriOrNot();//计算总伤害
        int e=p*g_ele_ratio;//元素伤害
        a.ele_damage[element]+=e;
        a.ele_damage[LEAF]+=p-e;
        a.happen=true;
        a.special_effects=element;
        int i1;
        if(tal_level==1){
            i1=20;
        }
        else if(tal_level==2){
            i1=35;
        }
        else{
            i1=50;
        }
        int i2=i%2;
        g_message=g_message+"\n"+name+"发动了天赋技能:";
        g_message.append(g_Str_talent[pet_num]+"！");
        GGuiBi(i1,0,2);
        GJinGu(a,1,i2,2);
    }
    return a;
}

Attack GangTieHaiLong::Talent()
{
//    g_Str_talent[i]="究极波浪炮";
//    g_Intro_Elf[i]="海中霸王，防御型精灵，浑身包裹着金属，力量强大，行动敏捷，坚不可摧。";
//    g_Intro_Talent[i]="主动技能\n"+g_Name[i];
//    g_Intro_Talent[i].append("汇聚大海的力量，发射究极波浪炮，使敌人眩晕，使自己进入侵略状态属性变为暗");
//    g_Intro_Talent[i].append("\n 持续2回合 无视免疫 防御降低40");
//    g_Intro_Talent[i].append("\n一级：释放概率20% 力量增加20");
//    g_Intro_Talent[i].append("\n二级：释放概率25% 力量增加40");
//    g_Intro_Talent[i].append("\n三级：释放概率30% 力量增加60");
    Attack a;
    int i1,i2;
    if(tal_level==1){
        i1=20,i2=20;
    }
    else if(tal_level==2){
        i1=25,i2=40;
    }
    else{
        i1=30,i2=60;
    }
    int i=RANDOM(100);
    if(i<=i1){//概率释放
        g_message=g_message+"\n"+name+"发动了天赋技能:";
        g_message.append(g_Str_talent[pet_num]+"！");
        GXuanYun(a,40,1,2);
        GQinLve(i2,DARK,2);
        int p=CriOrNot();//计算总伤害
        int e=p*g_ele_ratio;//元素伤害
        a.ele_damage[DARK]+=e;
        a.ele_damage[LEAF]+=p-e;
        a.happen=true;
        a.special_effects=element;

    }
    return a;
}

Attack ZuDunShou::Talent()
{
//    g_Str_talent[i]="重锤火花";
//    g_Intro_Elf[i]="防御力极强的防御型精灵，手握重锤，身背坚壳。";
//    g_Intro_Talent[i]="指挥技能\n"+g_Name[i];
//    g_Intro_Talent[i].append("挥舞重锤，锤击大地，迸溅火花，造成伤害的同时给自身添加护盾");
//    g_Intro_Talent[i].append("\n 释放概率30% 持续两回合");
//    g_Intro_Talent[i].append("\n一级：伤害降低20% 添加100的护盾");
//    g_Intro_Talent[i].append("\n二级：伤害降低30% 添加150的护盾");
//    g_Intro_Talent[i].append("\n三级：伤害降低40% 添加200的护盾");
    Attack a;
    int i=RANDOM(100);
    if(i<=30){
        int p=CriOrNot();//计算总伤害
        int e=p*g_ele_ratio;//元素伤害
        a.ele_damage[element]+=e;
        a.ele_damage[LEAF]+=p-e;
        a.happen=true;
        a.special_effects=element;
        int i1,i2;
        if(tal_level==1){
            i1=20;
            i2=100;
        }
        else if(tal_level==2){
            i1=30;
            i2=150;
        }
        else{
            i1=40;
            i2=200;
        }
        g_message=g_message+"\n"+name+"发动了天赋技能:";
        g_message.append(g_Str_talent[pet_num]+"！");
        GHuDun(i1,i2,2);
    }
    return a;
}

Attack EMoShou::SimpleAttack()
{
//    g_Str_talent[i]="死亡之爪";
//    g_Intro_Elf[i]="来自地狱的使者，防御型精灵，享受屠戮。";
//    g_Intro_Talent[i]="追击技能\n"+g_Name[i];
//    g_Intro_Talent[i].append("发动死亡之爪，撕裂敌人伤口，使自己进入嗜血状态");
//    g_Intro_Talent[i].append("\n 释放概率80% 持续1回合 无每回合扣血");
//    g_Intro_Talent[i].append("\n一级：吸血百分比50%");
//    g_Intro_Talent[i].append("\n二级：吸血百分比75%");
//    g_Intro_Talent[i].append("\n三级：吸血百分比100%");

    Attack a;
    g_message=g_message+'\n'+name+"发动了普通攻击！";
    int p=CriOrNot();//计算总伤害
    int e=p*g_ele_ratio;//元素伤害
    a.ele_damage[element]+=e;
    a.ele_damage[LEAF]+=p-e;
    a.happen=true;

    int i=RANDOM(100);

    if(i<=80){//概率释放
        a.special_effects=element;
        int i1;
        if(tal_level==1){
            i1=50;
        }
        else if(tal_level==2){
            i1=75;
        }
        else{
            i1=100;
        }

        g_message=g_message+"\n"+name+"发动了天赋技能:";
        g_message.append(g_Str_talent[pet_num]+"！");
        GShiXve(i1,0,1);
    }
    if(state_fighting[GANDIAN][1]>0){
        JGanDian(a,SIMPLE_ATTACK);
    }
    return a;
}
