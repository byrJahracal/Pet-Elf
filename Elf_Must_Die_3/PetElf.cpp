#include "PetElf.h"

PetElf::PetElf()//默认精灵为叶精灵
{
    int i=YEJINGLING;
    pet_num=g_PetNum[i];
    name=g_Name[i];
    primarya_a=g_PrimaryA_A[i];
    element=g_Element[i];
    life=g_Life[i];
    power=g_Power[i];
    defence=g_Defence[i];
    agility=g_Agility[i];
    life_grow=g_Life_Grow[i];
    power_grow=g_Power_Grow[i];
    defence_grow=g_Defence_Grow[i];
    agility_grow=g_Agility_Grow[i];
    cri_rate=g_Cri_Rate[i];
    cri_damage=g_Cri_Damage[i];
    dodge_rate=g_Dodge_Rate[i];
    skill1=g_Skill1[i];
    skill2=g_Skill2[i];
    level=1;
    sk1_level=1;
    sk2_level=1;
    tal_level=1;
    up_skill=0;
    experience=0;
    image.load(g_Image[i]);
}

PetElf::PetElf(PetNumber your_elf)//创建指定精灵
{
    int i=your_elf;
    pet_num=g_PetNum[i];
    name=g_Name[i];
    primarya_a=g_PrimaryA_A[i];
    element=g_Element[i];
    life=g_Life[i];
    power=g_Power[i];
    defence=g_Defence[i];
    agility=g_Agility[i];
    life_grow=g_Life_Grow[i];
    power_grow=g_Power_Grow[i];
    defence_grow=g_Defence_Grow[i];
    agility_grow=g_Agility_Grow[i];
    cri_rate=g_Cri_Rate[i];
    cri_damage=g_Cri_Damage[i];
    dodge_rate=g_Dodge_Rate[i];
    skill1=g_Skill1[i];
    skill2=g_Skill2[i];
    level=1;
    sk1_level=1;
    sk2_level=1;
    tal_level=1;
    up_skill=0;
    experience=0;
    image.load(g_Image[i]);
}

PetElf::PetElf(PetNumber your_elf, SkillT s1, SkillT s2, int l, int l1, int l2)
{//细节化创建精灵
    int i=your_elf;
    pet_num=g_PetNum[i];
    name=g_Name[i];
    primarya_a=g_PrimaryA_A[i];
    element=g_Element[i];
    life=g_Life[i];
    power=g_Power[i];
    defence=g_Defence[i];
    agility=g_Agility[i];
    life_grow=g_Life_Grow[i];
    power_grow=g_Power_Grow[i];
    defence_grow=g_Defence_Grow[i];
    agility_grow=g_Agility_Grow[i];
    cri_rate=g_Cri_Rate[i];
    cri_damage=g_Cri_Damage[i];
    dodge_rate=g_Dodge_Rate[i];
    skill1=s1;
    skill2=s2;
    level=1;
    sk1_level=l1;
    sk2_level=l2;
    tal_level=1;
    up_skill=0;
    UpGrade(l);
    up_skill-=l1-1;
    up_skill-=l2-1;
    experience=0;
    image.load(g_Image[i]);
}

void PetElf::UpGrade(int new_level)
{//精灵升级到指定等级
    if(new_level<=MAXLEVEL&&new_level>=1)//不能超过最高等级
    while(level<new_level){
        level++;
        life+=life_grow;
        power+=power_grow;
        defence+=defence_grow;
        agility+=agility_grow;
        if(level==LEVEL_1||level==LEVEL_2||level==LEVEL_3||level==LEVEL_4)
            up_skill+=1;
        else if(level==TAL_1)
            tal_level=2;
        else if(level==TAL_2)
            tal_level=3;
    }
}

void PetElf::UpGrade()//根据经验值自动升级
{
    if(level<15){
        int l=level;
        while(experience>=(level+1)*100){
            experience-=(level+1)*100;
            l++;
            UpGrade(l);
        }
    }
}

void PetElf::DownGrade()//重置时降级
{
    int i,all_e=experience;//all_e为从一级开始的全部经验
    for(i=1;i<level;i++){
        all_e+=(i+1)*100;
    }
    all_e/=2;
    QuickElf quick_elf;
    quick_elf.experience = all_e;
    quick_elf.your_elf=pet_num;
    quick_elf.l=1;
    quick_elf.l1=1;
    quick_elf.l2=1;
    quick_elf.s1=UNLOCKED;
    if(skill2==LOCKED)
        quick_elf.s2=LOCKED;
    else
        quick_elf.s2=UNLOCKED;
    this->SetValue(quick_elf);
    UpGrade();//重新计算经验后从一级开始升级
}

void PetElf::Distribute(int select_skill)//分配技能点
{
    if(up_skill>0){
    if(select_skill==1&&sk1_level<3&&skill1!=LOCKED&&skill1!=UNLOCKED){
        sk1_level++;
        up_skill--;
    }
    else if(select_skill==2&&sk2_level<3&&skill2!=LOCKED&&skill2!=UNLOCKED){
        sk2_level++;
        up_skill--;
    }
    }
}

QString PetElf::ShowAttributes()//显示精灵数据
{
    QString s;
    QString s1;

    s=name+"\n";
    s.append(g_Str_Attributes[primarya_a]+"型精灵");
    s.append("\n精灵元素:"+g_Str_element[element]);
    s1.setNum(life);
    s.append("\n生命:"+s1);
    s1.setNum(life_grow);
    s.append("    生命成长"+s1);
    s1.setNum(power);
    s.append("\n力量:"+s1);
    s1.setNum(power_grow);
    s.append("    力量成长:"+s1);
    s1.setNum(defence);
    s.append("\n防御:"+s1);
    s1.setNum(defence_grow);
    s.append("    防御成长:"+s1);
    s1.setNum(agility);
    s.append("\n敏捷:"+s1);
    s1.setNum(agility_grow);
    s.append("    敏捷成长:"+s1);
    s1.setNum(cri_rate);
    s.append("\n暴击率:"+s1);
    s1.setNum(cri_damage);
    s.append("%    暴击伤害倍率:"+s1);
    s1.setNum(dodge_rate);
    s.append("\n闪避率:"+s1+"%");
    return s;
}

void PetElf::SetValue(QuickElf q)//拷贝精灵数据
{
    int i=q.your_elf;
    pet_num=g_PetNum[i];
    name=g_Name[i];
    primarya_a=g_PrimaryA_A[i];
    element=g_Element[i];
    life=g_Life[i];
    power=g_Power[i];
    defence=g_Defence[i];
    agility=g_Agility[i];
    life_grow=g_Life_Grow[i];
    power_grow=g_Power_Grow[i];
    defence_grow=g_Defence_Grow[i];
    agility_grow=g_Agility_Grow[i];
    cri_rate=g_Cri_Rate[i];
    cri_damage=g_Cri_Damage[i];
    dodge_rate=g_Dodge_Rate[i];
    skill1=q.s1;
    skill2=q.s2;
    level=1;
    sk1_level=q.l1;
    sk2_level=q.l2;
    tal_level=1;
    up_skill=0;
    UpGrade(q.l);
    up_skill-=q.l1-1;
    up_skill-=q.l2-1;
    experience=q.experience;
    image.load(g_Image[i]);
}


