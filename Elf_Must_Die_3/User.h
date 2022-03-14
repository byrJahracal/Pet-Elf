#ifndef USER_H
#define USER_H
#include "PetElf.h"

class PetOwn{//用户拥有的宠物类
public:
    PetOwn();
    PetOwn(PetNumber new_pet);
    PetOwn(PetOwn&);
    void SetValue(PetElf& show_pet);//赋值函数

    QuickElf own_elf;
};

class SkillOwn{//用户拥有的技能类
public:
    SkillOwn();
    SkillOwn(SkillType new_skill);
    SkillOwn(SkillOwn&);
    SkillType own_skill;//技能编号
    int learn_remain;//剩余可学习次数
};

class QuickUser{//基本用户信息类
public:
    bool operator ==(QuickUser new_user);
    QString name;//用户名
    QString password;//密码
    int head_number;//头像
};

class User//用户类
{
public:
    User();
    QString name;//昵称
    QPixmap head_picture;//头像
    int head_number;//头像序号
    int count_pet;//宠物数
    int count_skill;//技能数
    PetOwn* my_pet[ALLPET];//所有宠物
    SkillOwn* my_skill[ALLSKILL];//所有技能
    void AddPet(PetNumber new_pet);//新增一个宠物
    void AddSkill(SkillType new_skill);//新增一个技能
    void SuperUser(int l);//超级用户，获得所有l等级的宠物，和所有技能
    void Distribute(PetNumber the_pet,SkillType the_skill,int choose_skill);//分配技能
    void Forget(PetNumber the_pet,int choose_skill);//遗忘某一个技能
    void Deal(QuickUser new_user);//登录时处理用户信息
    void Deal(PetOwn new_pet);//登陆时处理精灵信息
    void Deal(SkillOwn new_skill);//登录时处理技能信息
    void ChangeTouxiang();//改变头像
    void Clear();//清空用户信息
    void DeletePet(PetNumber which);//失去宠物
};

#endif // USER_H
