#include "AdvanceElf.h"
//力量型精灵
Attack TianNvShou::Talent()
{
//    g_Str_talent[i]="神圣之箭";
//    g_Intro_Elf[i]="美丽的女天使，力量型精灵，守护自然届中的一切美好事物。";
//    g_Intro_Talent[i]="主动技能\n"+g_Name[i];
//    g_Intro_Talent[i].append("射出神圣之箭，对暗系精灵有额外伤害，使自身免疫，使敌人禁锢无法使用普攻或主动");
//    g_Intro_Talent[i].append("\n 释放概率35% 持续两回合 驱散敌人有利效果 受到元素伤害降低20%");
//    g_Intro_Talent[i].append("\n一级：受到叶和暗伤害降低20%");
//    g_Intro_Talent[i].append("\n二级：受到叶和暗伤害降低35%");
//    g_Intro_Talent[i].append("\n三级：受到叶和暗伤害降低50%");
    Attack a;
    int i=RANDOM(100);
    if(i<=35){//概率释放
        int p=CriOrNot();//计算总伤害
        a.ele_damage[LEAF]+=p;
        a.happen=true;
        a.special_effects=element;
        int i1,i2;
        if(tal_level==1){
            i1=20;
        }
        else if(tal_level==2){
            i1=35;
        }
        else{
            i1=50;
        }
        i2=i%2;
        g_message=g_message+"\n"+name+"发动了天赋技能:";
        g_message.append(g_Str_talent[pet_num]+"！");
        GJinGu(a,i2,1,2);
        GMianYi(20,i1,2);
    }
    return a;
}

Attack ZhanDouBaoLong::Talent()
{
//    g_Str_talent[i]="盖亚能量炮";
//    g_Intro_Elf[i]="披上铠甲的龙系精灵，力量型精灵，战斗力十足，拥有恐怖的力量与勇气。";
//    g_Intro_Talent[i]="主动技能\n"+g_Name[i];
//    g_Intro_Talent[i].append("发动盖亚之力，形成巨大火系能量球，砸向敌人，同时使自己进入侵略和兴奋状态");
//    g_Intro_Talent[i].append("\n 释放概率25% 持续两回合 敏捷增加5 侵略元素为火");
//    g_Intro_Talent[i].append("\n一级：暴击率增加20% 力量增加20");
//    g_Intro_Talent[i].append("\n二级：暴击率增加40% 力量增加40");
//    g_Intro_Talent[i].append("\n三级：暴击率增加60% 力量增加60");
    Attack a;
    int i=RANDOM(100);
    if(i<=25){//概率释放
        int i1,i2;
        if(tal_level==1){
            i1=20,i2=20;
        }
        else if(tal_level==2){
            i1=40,i2=40;
        }
        else{
            i1=60,i2=60;
        }
        g_message=g_message+"\n"+name+"发动了天赋技能:";
        g_message.append(g_Str_talent[pet_num]+"！");
        GQinLve(i2,FLAME,2);
        GXingFen(5,i1,2);
        int p=CriOrNot();//计算总伤害
        a.ele_damage[FLAME]+=p;
        a.happen=true;
        a.special_effects=FLAME;
    }
    return a;
}

Attack GangTieJiaLuLu::Talent()
{
//    g_Str_talent[i]="冰狱冷冻气";
//    g_Intro_Elf[i]="极寒领域的加鲁鲁，力量型精灵，身披铠甲，加鲁鲁族之王。";
//    g_Intro_Talent[i]="指挥技能\n"+g_Name[i];
//    g_Intro_Talent[i].append("释放来自地狱的超低温的气压，使敌人冰冻并犹豫。");
//    g_Intro_Talent[i].append("\n 释放概率100% 持续一回合 伤害30 敏捷降低2 消除暴击");
//    g_Intro_Talent[i].append("\n一级：力量降低0");
//    g_Intro_Talent[i].append("\n二级：力量降低30");
//    g_Intro_Talent[i].append("\n三级：力量降低60");
    Attack a;
    a.happen=true;
    a.ignore=true;
    a.special_effects=ICE;

    int i1;
    if(tal_level==1){
        i1=0;
    }
    else if(tal_level==2){
        i1=30;
    }
    else{
        i1=60;
    }
    g_message=g_message+"\n"+name+"发动了天赋技能:";
    g_message.append(g_Str_talent[pet_num]+"！");
    GBingDong(a,30,i1,1);
    GYouYu(a,2,1,1);
    return a;
}

Attack DuJiaoXian::Talent()
{
//    g_Str_talent[i]="百万冲击波";
//    g_Intro_Elf[i]="昆虫系精灵，力量型精灵，意外的获得了雷电的力量，成为精灵中的强者。";
//    g_Intro_Talent[i]="主动技能\n"+g_Name[i];
//    g_Intro_Talent[i].append("发射紫色雷球，使敌人感电，并且自己进入规避状态");
//    g_Intro_Talent[i].append("\n 释放概率35% 持续两回合 感电伤害比例30% 闪避率增加10%");
//    g_Intro_Talent[i].append("\n一级：伤害40 抵挡1次伤害");
//    g_Intro_Talent[i].append("\n二级：伤害60 抵挡2次伤害");
//    g_Intro_Talent[i].append("\n三级：伤害80 抵挡3次伤害");
    Attack a;
    int i=RANDOM(100);
    if(i<=35){//概率释放
        int p=CriOrNot();//计算总伤害
        int e=p*g_ele_ratio;//元素伤害
        a.ele_damage[element]+=e;
        a.ele_damage[LEAF]+=p-e;
        a.happen=true;
        a.special_effects=element;
        int i1,i2;
        if(tal_level==1){
            i1=40,i2=1;
        }
        else if(tal_level==2){
            i1=60,i2=2;
        }
        else{
            i1=80,i2=3;
        }
        g_message=g_message+"\n"+name+"发动了天赋技能:";
        g_message.append(g_Str_talent[pet_num]+"！");
        GGanDian(a,30,i1,2);
        GGuiBi(10,i2,2);
    }
    return a;
}

Attack SangShiBaoLong::SimpleAttack()
{
//    g_Str_talent[i]="湮灭猎鸟";
//    g_Intro_Elf[i]="堕落的龙系精灵，力量型精灵，获得了地狱的力量，代价是只能以丧尸形态存活。";
//    g_Intro_Talent[i]="追击技能\n"+g_Name[i];
//    g_Intro_Talent[i].append("发射骨刺，聚集为湮灭猎鸟，改技能无法被闪避，使敌人弱化，使自己进入反伤状态");
//    g_Intro_Talent[i].append("\n 释放概率50% 持续两回合 反弹伤害40 力量降低40");
//    g_Intro_Talent[i].append("\n一级：反伤比例40% 防御降低20");
//    g_Intro_Talent[i].append("\n二级：反伤比例50% 防御降低35");
//    g_Intro_Talent[i].append("\n三级：反伤比例60% 防御降低50");
    Attack a;
    g_message=g_message+'\n'+name+"发动了普通攻击！";
    int p=CriOrNot();//计算总伤害
    int e=p*g_ele_ratio;//元素伤害
    a.ele_damage[element]+=e;
    a.ele_damage[LEAF]+=p-e;
    a.happen=true;

    int i=RANDOM(100);

    if(i<=50){//概率释放
        a.special_effects=element;
        a.ignore=true;
        int i1,i2;
        if(tal_level==1){
            i1=40,i2=20;
        }
        else if(tal_level==2){
            i1=50,i2=35;
        }
        else{
            i1=60,i2=50;
        }

        g_message=g_message+"\n"+name+"发动了天赋技能:";
        g_message.append(g_Str_talent[pet_num]+"！");
        GRuoHua(a,i2,40,2);
        GFanShang(i1,40,2);
    }
    if(state_fighting[GANDIAN][1]>0){
        JGanDian(a,SIMPLE_ATTACK);
    }
    return a;
}



