#include "Petelffighting.h"
//技能
Attack PetElfFighting::XiLi(int l)
{
    //    g_Str_skill[i]="洗礼";
    //    g_Intro_Skill[i]="主动技能\n精灵接受圣光洗礼，立刻为自己回复一定生命。";
    //    g_Intro_Skill[i].append("\n释放概率35% 对叶系精灵效果加成30% 对暗系精灵效果减少30%");
    //    g_Intro_Skill[i].append("\n一级：回复60点生命");
    //    g_Intro_Skill[i].append("\n二级：回复100点生命");
    //    g_Intro_Skill[i].append("\n三级：回复140点生命");
    //    g_Skill_Time[i]=SKILL_TIME;
    //    g_Skill_Kind[i]=INITIATIVE;
    Attack a;
    a.happen=false;
    int i=RANDOM(100);
    if(i<=35){//概率释放
        a.special_effects=LEAF;
        int i1;
        if(l==1){
            i1=60;
        }
        else if(l==2){
            i1=100;
        }
        else{
            i1=140;
        }
        if(element==LEAF)
            i1*=1.3;
        else if(element==DARK)
            i1*=0.7;
        g_message=g_message+"\n"+name+"发动了技能:";
        g_message.append(g_Str_skill[XILI]+"！");
        QString s1=QString("立即回复了%1点生命！").arg(i1);
        g_message.append(s1);
        life+=i1;
        if(life>=life_back)
            life=life_back;
    }
    return a;
}

Attack PetElfFighting::BuQuYiZhi(int l)
{
    //    g_Str_skill[i]="不屈意志";
    //    g_Intro_Skill[i]="被动技能\n精灵拥有不屈的斗志，每受到一次伤害永久增加一定的属性(四种属性中的一种)。";
    //    g_Intro_Skill[i].append("\n释放概率100% 四种属性概率相等");
    //    g_Intro_Skill[i].append("\n一级：力量，防御增加10 生命增加20 敏捷增加2");
    //    g_Intro_Skill[i].append("\n二级：力量，防御增加20 生命增加40 敏捷增加4");
    //    g_Intro_Skill[i].append("\n三级：力量，防御增加30 生命增加60 敏捷增加6");
    //    g_Skill_Time[i]=INJURED;
    //    g_Skill_Kind[i]=PASSIVE;
    int i=RANDOM(4);
    QString s1,s2;
    int i1,i2,i3,i4;
    if(l==1){
        i1=10,i2=10,i3=20,i4=2;
    }
    else if(l==2){
        i1=20,i2=20,i3=40,i4=4;
    }
    else{
        i1=30,i2=30,i3=60,i4=6;
    }
    if(i==1){
        s1="生命";
        s2.setNum(i3);
        life+=i3;
        life_back+=i3;
    }
    else if(i==2){
        s1="力量";
        s2.setNum(i1);
        power+=i1;
        power_back+=i1;
    }
    else if(i==3){
        s1="防御";
        s2.setNum(i2);
        defence+=i2;
        defence_back+=i2;
    }
    else{
        s1="敏捷";
        s2.setNum(i4);
        agility+=i4;
        agility_back+=i4;
    }
    g_message=g_message+"\n"+name+"发动了技能:";
    g_message.append(g_Str_skill[BUQUYIZHI]+"！");
    s1=QString("永久增加了%1点%2！").arg(s2).arg(s1);
    g_message.append(s1);
    return_attack.special_effects=element;
    return return_attack;
}

Attack PetElfFighting::XianXveKeWang(int l)
{
    //    g_Str_skill[i]="鲜血渴望";
    //    g_Intro_Skill[i]="指挥技能\n精灵贪恋杀戮，进入嗜血状态。";
    //    g_Intro_Skill[i].append("\n释放概率100% 持续一回合 立即失去20点生命");
    //    g_Intro_Skill[i].append("\n一级：吸血比例30%");
    //    g_Intro_Skill[i].append("\n二级：吸血比例40%");
    //    g_Intro_Skill[i].append("\n三级：吸血比例50%");
    //    g_Skill_Time[i]=BEGIN;
    //    g_Skill_Kind[i]=COMMAND;
    int i1;
    if(l==1){
        i1=30;
    }
    else if(l==2){
        i1=40;
    }
    else {
        i1=50;
    }
    g_message=g_message+"\n"+name+"发动了技能:";
    g_message.append(g_Str_skill[XIANXVEKEWANG]+"！");
    g_message.append("立即失去20点生命！");
    GShiXve(i1,0,1);
    life-=20;
    if(life<=0)
        life=1;
    Attack a;
    a.special_effects=element;
    return a;
}

Attack PetElfFighting::XianQuTuJi(int l)
{
    //    g_Str_skill[i]="先驱突击";
    //    g_Intro_Skill[i]="主动技能\n精灵掌握先机，进行第二次普攻。";
    //    g_Intro_Skill[i].append("\n若被禁用普攻或主动都无法释放该技能");
    //    g_Intro_Skill[i].append("\n一级：释放概率35%");
    //    g_Intro_Skill[i].append("\n二级：释放概率50%");
    //    g_Intro_Skill[i].append("\n三级：释放概率65%");
    //    g_Skill_Time[i]=SKILL_TIME;
    //    g_Skill_Kind[i]=INITIATIVE;
    int i=RANDOM(100);
    int i1;
    Attack a;
    if(l==1){
        i1=35;
    }
    else if(l==2){
        i1=50;
    }
    else {
        i1=65;
    }

    if(i<=i1){
        a.special_effects=element;
        g_message=g_message+"\n"+name+"发动了技能:";
        g_message.append(g_Str_skill[XIANQUTUJI]+"！");
        if(probability_attack!=0){
            return SimpleAttack();
        }
        else{
            g_message=g_message+"\n"+name+"无法普通攻击！";
        }
    }
    return a;
}

Attack PetElfFighting::FlameAttack(int l)//火焰攻击技能
{
    Attack a;
    int probability;
    int power_add;
    switch(l){
    case 1:{
        probability=30;
        power_add=20;
        break;
    }
    case 2:{
        probability=35;
        power_add=35;
        break;
    }
    case 3:{
        probability=40;
        power_add=50;
        break;
    }
    default:
        break;
    }


    int i=RANDOM(100);
    if(i<=probability){
        a.special_effects=FLAME;
        g_message=g_message+"\n"+name+"发动了技能:"+g_Str_skill[FLAME_ATTACK]+"！";
        a.happen=1;
        int p=CriOrNot();
        a.ele_damage[FLAME]+=p;
        //massage=massage+"\n"+"元素之力由于"+Name+"的攻击提升了10%！";
        EleRatioAdd(10);
        if(i%2==0){
            GQinLve(power_add,FLAME,3);
        }
    }
    return a;
}

Attack PetElfFighting::ThunderAttack(int l)//雷电攻击技能
{
    Attack a;
    int probability;
    int power_add;
    switch(l){
    case 1:{
        probability=30;
        power_add=20;
        break;
    }
    case 2:{
        probability=35;
        power_add=35;
        break;
    }
    case 3:{
        probability=40;
        power_add=50;
        break;
    }
    default:
        break;
    }


    int i=RANDOM(100);
    if(i<=probability){
        a.special_effects=THUNDER;
        g_message=g_message+"\n"+name+"发动了技能:"+g_Str_skill[THUNDER_ATTACK]+"！";
        a.happen=1;
        int p=CriOrNot();
        a.ele_damage[THUNDER]+=p;

        //massage=massage+"\n"+"元素之力由于"+Name+"的攻击提升了10%！";
        EleRatioAdd(10);
        if(i%2==0){
            GQinLve(power_add,THUNDER,3);
        }
    }
    return a;
}

Attack PetElfFighting::IceAttack(int l)//冰冻攻击技能
{
    Attack a;
    int probability;
    int power_add;
    switch(l){
    case 1:{
        probability=30;
        power_add=20;
        break;
    }
    case 2:{
        probability=35;
        power_add=35;
        break;
    }
    case 3:{
        probability=40;
        power_add=50;
        break;
    }
    default:
        break;
    }


    int i=RANDOM(100);
    if(i<=probability){
        a.special_effects=ICE;
        g_message=g_message+"\n"+name+"发动了技能:"+g_Str_skill[ICE_ATTACK]+"！";
        a.happen=1;
        int p=CriOrNot();
        a.ele_damage[ICE]+=p;

        //massage=massage+"\n"+"元素之力由于"+Name+"的攻击提升了10%！";
        EleRatioAdd(10);
        if(i%2==0){
            GQinLve(power_add,ICE,3);
        }
    }
    return a;
}

Attack PetElfFighting::LEAFAttack(int l)//翠叶攻击技能
{
    Attack a;
    int probability;
    int power_add;
    switch(l){
    case 1:{
        probability=30;
        power_add=20;
        break;
    }
    case 2:{
        probability=35;
        power_add=35;
        break;
    }
    case 3:{
        probability=40;
        power_add=50;
        break;
    }
    default:
        break;
    }


    int i=RANDOM(100);
    if(i<=probability){
        a.special_effects=LEAF;
        g_message=g_message+"\n"+name+"发动了技能:"+g_Str_skill[LEAF_ATTACK]+"！";
        a.happen=1;
        int p=CriOrNot();
        a.ele_damage[LEAF]+=p;

        //massage=massage+"\n"+"元素之力由于"+Name+"的攻击提升了10%！";
        EleRatioAdd(10);
        if(i%2==0){
            GQinLve(power_add,LEAF,3);
        }
    }
    return a;
}

Attack PetElfFighting::DarkAttack(int l)//黑暗攻击技能
{
    Attack a;
    int probability;
    int power_add;
    switch(l){
    case 1:{
        probability=30;
        power_add=20;
        break;
    }
    case 2:{
        probability=35;
        power_add=35;
        break;
    }
    case 3:{
        probability=40;
        power_add=50;
        break;
    }
    default:
        break;
    }

    int i=RANDOM(100);
    if(i<=probability){
        a.special_effects=DARK;
        g_message=g_message+"\n"+name+"发动了技能:"+g_Str_skill[DARK_ATTACK]+"！";
        a.happen=1;
        int p=CriOrNot();
        a.ele_damage[DARK]+=p;

        //massage=massage+"\n"+"元素之力由于"+Name+"的攻击提升了10%！";
        EleRatioAdd(10);
        if(i%2==0){
            GQinLve(power_add,DARK,3);
        }
    }
    return a;
}

