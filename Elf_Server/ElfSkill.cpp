#include "Mythread.h"

void MyThread::RandomSkill(int flag)//0代表前五个，1代表所有,2代表可能未解锁技能
{//随机一个技能
    int i;
    if(flag==0){
        i=RANDOM(5)+1;
        new_skill.own_skill=(SkillType)i;
    }
    else if(flag==1){
        i=RANDOM(ALLSKILL-2)+1;
        new_skill.own_skill=(SkillType)i;
    }
    else if(flag==2){
        i=RANDOM(5);
        if(i<3){
            new_skill.own_skill=LOCKED;
        }
        else {
            i=RANDOM(ALLSKILL-2)+1;
            new_skill.own_skill=(SkillType)i;
        }
    }
    else{
        new_skill.own_skill=LOCKED;
    }
    new_skill.learn_remain=SKILLREMAIN;
}

void MyThread::YourSkill()
{//发送用户所有技能
    s=QString("select * from ElfSkill where Master = '%1'").arg(new_user.name);
    query->exec(s);
    query->first();
    SendOneSkill();
    while(query->next()){
        SendOneSkill();
    }
}

void MyThread::SendOneSkill()
{//发送一个技能
    new_skill.own_skill=(SkillType)(query->value(SSKILL).toInt());
    new_skill.learn_remain=query->value(SREMAIN).toInt();
    SendMassage(QChar('S'));
}

void MyThread::AddSkill()
{//用户新增一个技能
    s=QString("insert into ElfSkill values('%1',%2,%3)")
            .arg(new_user.name)
            .arg((int)new_skill.own_skill)
            .arg((int)new_skill.learn_remain);
    query->exec(s);
}


