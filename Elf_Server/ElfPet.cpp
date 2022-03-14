#include "Mythread.h"

void MyThread::RandomPet(int count)
{//随机生成一个宠物
    int i=RANDOM(ALLPET)-1;
    new_pet3=new_pet2;
    new_pet2=new_pet.own_elf.your_elf;
    if(count==3){//第三个和前两个不一样
        while(i==new_pet2||i==new_pet3){
            i=RANDOM(ALLPET)-1;
        }
    }
    else if(count==2){//第二个和第一个不一样
        while(i==new_pet2){
            i=RANDOM(ALLPET)-1;
        }
    }
    new_pet.own_elf.your_elf=(PetNumber)i;
    new_pet.own_elf.s1=UNLOCKED;
    new_pet.own_elf.s2=LOCKED;
    new_pet.own_elf.l=1;
    new_pet.own_elf.l1=1;
    new_pet.own_elf.l2=1;
    new_pet.own_elf.experience=0;
}

void MyThread::YourPet()
{
    s=QString("select * from ElfPet where Master = '%1'").arg(new_user.name);

    query->exec(s);
    query->first();
    SendOnePet();
    count_pet++;
    while(query->next()){//发送所有精灵
        count_pet++;
        SendOnePet();
    }
}

void MyThread::SendOnePet()
{//发送一个精灵的信息
    new_pet.own_elf.your_elf=(PetNumber)(query->value(PYOUR_ELF).toInt());
    new_pet.own_elf.s1=(SkillType)(query->value(PSKILL1).toInt());
    new_pet.own_elf.s2=(SkillType)(query->value(PSKILL2).toInt());
    new_pet.own_elf.l=query->value(PL).toInt();
    new_pet.own_elf.l1=query->value(PL1).toInt();
    new_pet.own_elf.l2=query->value(PL2).toInt();
    new_pet.own_elf.experience=query->value(PEXPERIENCE).toInt();
    SendMassage(QChar('P'));
}

void MyThread::AddPet()
{//新增一个宠物
    s=QString("insert into ElfPet values('%1',%2,%3,%4,%5,%6,%7,%8)")
            .arg(new_user.name)
            .arg((int)new_pet.own_elf.your_elf)
            .arg((int)new_pet.own_elf.s1)
            .arg((int)new_pet.own_elf.s2)
            .arg(new_pet.own_elf.l)
            .arg(new_pet.own_elf.l1)
            .arg(new_pet.own_elf.l2)
            .arg(new_pet.own_elf.experience);
    query->exec(s);
}

void MyThread::RandomSPet(int count)
{//生成狩猎的三个精灵，三个精灵不一样，二技能可能不解锁
    int i=RANDOM(ALLPET)-1;
    new_pet3=new_pet2;
    new_pet2=new_pet.own_elf.your_elf;
    if(count==3){
        while(i==new_pet2||i==new_pet3){
            i=RANDOM(ALLPET)-1;
        }
    }
    else if(count==2){
        while(i==new_pet2){
            i=RANDOM(ALLPET)-1;
        }
    }
    new_pet.own_elf.your_elf=(PetNumber)i;
    RandomSkill(1);
    new_pet.own_elf.s1=new_skill.own_skill;
    RandomSkill(2);
    new_pet.own_elf.s2=new_skill.own_skill;
    new_pet.own_elf.l=1;
    new_pet.own_elf.l1=1;
    new_pet.own_elf.l2=1;
    new_pet.own_elf.experience=0;
}

void MyThread::RandomJPet(int count)
{//生成决斗的三个不一样的精灵，两个技能
    int i=RANDOM(ALLPET)-1;
    new_pet3=new_pet2;
    new_pet2=new_pet.own_elf.your_elf;
    if(count==3){
        while(i==new_pet2||i==new_pet3){
            i=RANDOM(ALLPET)-1;
        }
    }
    else if(count==2){
        while(i==new_pet2){
            i=RANDOM(ALLPET)-1;
        }
    }
    new_pet.own_elf.your_elf=(PetNumber)i;
    RandomSkill(1);
    new_pet.own_elf.s1=new_skill.own_skill;
    RandomSkill(1);
    new_pet.own_elf.s2=new_skill.own_skill;
    new_pet.own_elf.l=1;
    new_pet.own_elf.l1=1;
    new_pet.own_elf.l2=1;
    new_pet.own_elf.experience=0;
}
