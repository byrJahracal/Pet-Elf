#include "User.h"

User::User()//创建默认未登录的用户
{
    count_pet=0;
    count_skill=0;
    name="请登录";
    for(int i=YEJINGLING;i<ALLPET;i=i+1){
        my_pet[i]=NULL;
    }
    for(int i=LEAF_ATTACK;i<ALLSKILL;i=i+1){
        my_skill[i]=NULL;
    }
    head_number=1;
    head_picture.load(g_touxiang_user+"1");
}

void User::AddPet(PetNumber new_pet)//添加一个宠物
{
    if(my_pet[new_pet]==NULL){
        my_pet[new_pet]=new PetOwn(new_pet);
    }
}

void User::AddSkill(SkillType new_skill)//添加一个技能
{
    if(my_skill[new_skill]==NULL){
        my_skill[new_skill]=new SkillOwn(new_skill);
        count_skill++;
    }
}

void User::SuperUser(int l)//获得等级为l的所有宠物和技能
{
    count_pet=0;
    count_skill=0;
    for(PetNumber i=YEJINGLING;i<ALLPET;i=(PetNumber)(i+1)){
        if(my_pet[i]!=NULL)
            delete my_pet[i];
        my_pet[i]=new PetOwn(i);
        my_pet[i]->own_elf.s2=UNLOCKED;
        my_pet[i]->own_elf.l=l;
        count_pet++;
    }
    for(SkillType i=LEAF_ATTACK;i<ALLSKILL;i=(SkillType)(i+1)){
        if(my_skill[i]==NULL)
            my_skill[i]=new SkillOwn(i);
        my_skill[i]->learn_remain=SKILLREMAIN;
    }
}

void User::Distribute(PetNumber the_pet, SkillType the_skill, int flag)//分配技能flag代表是1/2技能
{
    if(my_pet[the_pet]!=NULL){//拥有该宠物
        if(my_skill[the_skill]!=NULL){//拥有该技能
            if(my_skill[the_skill]->learn_remain>0){//有剩余学习点
                if(flag==1&&the_skill!=my_pet[the_pet]->own_elf.s1){//一技能
                    SkillType i=my_pet[the_pet]->own_elf.s1;
                    if(i!=UNLOCKED&&i!=LOCKED)
                        my_skill[i]->learn_remain++;//归还原学习点
                    my_pet[the_pet]->own_elf.s1=my_skill[the_skill]->own_skill;
                    my_skill[the_skill]->learn_remain--;
                    my_pet[the_pet]->own_elf.l1=1;
                }
                else if(flag==2&&my_pet[the_pet]->own_elf.s2!=LOCKED&&the_skill!=my_pet[the_pet]->own_elf.s2){//2技能必须解锁
                    SkillType i=my_pet[the_pet]->own_elf.s2;
                    if(i!=UNLOCKED)
                        my_skill[i]->learn_remain++;//归还原学习点
                    my_pet[the_pet]->own_elf.s2=my_skill[the_skill]->own_skill;
                    my_skill[the_skill]->learn_remain--;
                    my_pet[the_pet]->own_elf.l2=1;
                }
            }
        }
    }
}

void User::Forget(PetNumber the_pet, int choose_skill)
{//遗忘技能
    if(my_pet[the_pet]!=NULL){//拥有该宠物
        if(choose_skill==1){
            SkillType i=my_pet[the_pet]->own_elf.s1;
            if(i!=UNLOCKED&&i!=LOCKED)
                my_skill[i]->learn_remain++;//归还原学习点
            my_pet[the_pet]->own_elf.s1=UNLOCKED;
            my_pet[the_pet]->own_elf.l1=1;
        }
        else{
            SkillType i=my_pet[the_pet]->own_elf.s2;
            if(i!=UNLOCKED&&i!=LOCKED)
                my_skill[i]->learn_remain++;//归还原技能点
            if(my_pet[the_pet]->own_elf.s2!=LOCKED)
                my_pet[the_pet]->own_elf.s2=UNLOCKED;
            my_pet[the_pet]->own_elf.l2=1;
        }
    }
}

void User::Deal(QuickUser new_user)
{//登陆时收到用户信息
    name=new_user.name;
    head_number=new_user.head_number;
    ChangeTouxiang();
}

void User::Deal(PetOwn new_pet)
{//登陆时收到宠物信息
    int i=new_pet.own_elf.your_elf;
    if(my_pet[i]){
        delete my_pet[i];
        count_pet--;
    }
    my_pet[i]=new PetOwn(new_pet);
    count_pet++;
}

void User::Deal(SkillOwn new_skill)
{//登陆时收到技能信息
    int i=new_skill.own_skill;
    if(my_skill[i]){
        delete my_skill[i];
        count_skill--;
    }
    my_skill[i]=new SkillOwn(new_skill);
    count_skill++;
}

void User::ChangeTouxiang()
{//修改头像
    QString s;
    s.setNum(head_number);
    head_picture.load(g_touxiang_user+s);
}

void User::Clear()
{//登出
    name="请登录";
    head_picture.load(g_touxiang_user+"1");
    head_number=1;
    count_pet=0;
    count_skill=0;
    for(int i=YEJINGLING;i<ALLPET;i=i+1){
        if(my_pet[i])
            delete my_pet[i];
        my_pet[i]=NULL;
    }
    for(int i=LEAF_ATTACK;i<ALLSKILL;i=i+1){
        if(my_skill[i])
            delete my_skill[i];
        my_skill[i]=NULL;
    }
}

void User::DeletePet(PetNumber which)
{//丢掉一个宠物
    if(my_pet[which]!=NULL){
        if(my_pet[which]->own_elf.s1!=UNLOCKED){
            my_skill[my_pet[which]->own_elf.s1]->learn_remain++;
        }
        if(my_pet[which]->own_elf.s2!=LOCKED&&my_pet[which]->own_elf.s2!=UNLOCKED){
            my_skill[my_pet[which]->own_elf.s2]->learn_remain++;
        }
        delete my_pet[which];
        my_pet[which]=NULL;
        count_pet--;
    }
}

PetOwn::PetOwn()
{
    own_elf={YEJINGLING,UNLOCKED,LOCKED,1,1,1,0};
}

PetOwn::PetOwn(PetNumber new_pet)
{
    own_elf={new_pet,UNLOCKED,LOCKED,1,1,1,0};
}

PetOwn::PetOwn(PetOwn& new_pet)
{
    own_elf=new_pet.own_elf;
}//用户的宠物的构造

void PetOwn::SetValue(PetElf &show_pet)
{//为用户宠物设置值
    own_elf={show_pet.pet_num,
            show_pet.skill1,
            show_pet.skill2,
            show_pet.level,
            show_pet.sk1_level,
            show_pet.sk2_level,
            show_pet.experience};
}

SkillOwn::SkillOwn()
{//默认技能为未解锁
    own_skill=LOCKED;
    learn_remain=0;
}

SkillOwn::SkillOwn(SkillType new_skill)
{//新技能
    own_skill=new_skill;
    learn_remain=SKILLREMAIN;
}

SkillOwn::SkillOwn(SkillOwn& new_skill)
{
    own_skill=new_skill.own_skill;
    learn_remain=new_skill.learn_remain;
}

bool QuickUser::operator ==(QuickUser new_user)
{//判断是否是同一用户
    if(new_user.name==name)
        return true;
    else return false;
}
