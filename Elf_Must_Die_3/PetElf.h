#ifndef PETELF_H
#define PETELF_H

#include "Attack.h"

typedef struct QuickPet{//一些简单的精灵信息，在服务器存储的精灵信息
    PetNumber your_elf;
    SkillT s1;
    SkillT s2;
    int l;
    int l1;
    int l2;
    int experience;
}QuickElf;

class PetElf//精灵属性信息
{
public:
    PetNumber pet_num;//编号
    QString name;//名字
    PrimaryA primarya_a;//主元素
    PElement element;//精灵元素
    QPixmap image;//精灵图片

    int life;//生命
    int power;//力量
    int defence;//防御
    int agility;//敏捷
    int life_grow;
    int power_grow;
    int defence_grow;
    int agility_grow;//对应属性的成长值
    int cri_rate;//暴击率
    float cri_damage;//暴击伤害倍率
    int dodge_rate;//闪避率
    SkillT skill1;
    SkillT skill2;//两个可学习技能
    int level;//等级
    int sk1_level;
    int sk2_level;
    int tal_level;//三个技能的等级
    int up_skill;//剩余技能点
    int experience;//经验值

    PetElf();
    PetElf(PetNumber your_elf);
    PetElf(PetNumber your_elf,SkillT s1,SkillT s2, int l,int l1,int l2);
    void UpGrade(int new_level);//升到指定等级
    void UpGrade();//根据经验值自动升级
    void DownGrade();//降级
    void Distribute(int select_skill);//分配技能点
    QString ShowAttributes();//宠物界面显示精灵属性
    void SetValue(QuickElf q);//赋值函数
};

#endif // PETELF_H
