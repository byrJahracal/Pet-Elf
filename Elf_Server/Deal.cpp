#include "Mythread.h"

void MyThread::DealTcp()//处理收到的tcp包
{
    receive_stream_ptr->device()->seek(0);//粘包处理
    receive_array.append(tcp_socket->readAll());
    receive_length=receive_array.size();
    if(receive_length>=least_length){//接收数据长度大于最小帧长度
        QChar cc;
        RECEIVESTREAM>>total_length;
        while(receive_length>=total_length){
            RECEIVESTREAM>>cc;
            char c=cc.unicode();
            switch(c){//根据标志位分别处理
            case 'O':{//老用户登陆
                DealO();
                break;
            }
            case 'N':{//新用户注册
                DealN();
                break;
            }
            case 'T':{
                if(load_success==true){
                    DealT();
                }
                break;
            }
            case 'R':{
                DealR();
                break;
            }
            case 'P':{
                DealP();
                break;
            }
            case 'L':{//查看该用户所有精灵
                DealL();
                break;
            }
            case 'K':{//查看所有用户
                DealK();
                break;
            }
            case 'H':{//狩猎请求
                DealH();
                break;
            }
            case 'J':{
                DealJ();
                break;
            }
            case 'U':{//宠物升级
                DealU();
                break;
            }
            case 'G':{//奖励给用户
                DealG();
                break;
            }
            case 'F':{//收回一个宠物
                DealF();
                break;
            }
            case 'M':{
                state_mode=MNORMAL;
                break;
            }
            case 'D':{//失败一局
                DealD();
                break;
            }
            case 'V':{//胜利一局
                DealV();
                break;
            }
            case 'X':{//解锁二技能
                DealX();
                break;
            }
            }
            receive_array=receive_array.right(receive_length-total_length);
            receive_length=receive_array.size();
            if(receive_length>=least_length){//可能还有别的包粘在后面
                receive_stream_ptr->device()->seek(0);
                RECEIVESTREAM>>total_length;
            }
            else{
                break;
            }
        }
    }
}

void MyThread::DealO()//老用户登录
{
    RECEIVESTREAM>>ss;
    new_user.name=ss;
    RECEIVESTREAM>>ss;
    new_user.password=ss;
    s=QString("select * from ElfMaster where Name = '%1'").arg(new_user.name);
    ReadStart();
    query->exec(s);//查找数据库
    query->first();
    if(query&&query->value(NAMEUSER).toString()==new_user.name){
        if(query->value(PASSWORD).toString()==new_user.password){//用户名密码正确
            new_user.head_number=query->value(TOUXIANG).toInt();
            SendMassage(QChar('Q'));//开始确认
            count_pet=0;
            YourPet();//发送宠物
            YourSkill();//发送技能
            SendMassage(QChar('Q'));//登陆完成
            load_success=true;
            AddList();//添加用户表表项
            ReadOver();

            return;
        }
    }

    ReadOver();
    s="用户名或密码错误！";
    SendMassage(QChar('E'));//登陆失败反馈
}

void MyThread::DealN()//新用户注册
{
    RECEIVESTREAM>>ss;
    new_user.name=ss;

    RECEIVESTREAM>>ss;
    new_user.password=ss;
    RECEIVESTREAM>>new_user.head_number;
    s=QString("select * from ElfMaster where Name = '%1'").arg(new_user.name);

    s_Write.acquire();

    query->exec(s);//查找表
    query->first();
    if(query->value(NAMEUSER).toString()!=new_user.name){//没有使用该名字
        s=QString("insert into ElfMaster values('%1','%2',%3,0,0)")
                .arg(new_user.name).arg(new_user.password)
                .arg(new_user.head_number);
        query->exec(s);//插入数据库

        RandomPet(1);
        AddPet();
        SendMassage(QChar('Q'));//开始确认
        SendMassage(QChar('P'));
        RandomPet(2);
        AddPet();
        SendMassage(QChar('P'));
        RandomPet(3);
        AddPet();
        SendMassage(QChar('P'));//发送三个宠物
        count_pet=3;
        RandomSkill(0);
        AddSkill();
        SendMassage(QChar('S'));//发送技能，三个要不一样
        int i=RANDOM(ALLSKILL-3);
        new_skill.own_skill=(SkillType)(new_skill.own_skill+i);
        if(new_skill.own_skill>=ALLSKILL)
            new_skill.own_skill=(SkillType)(new_skill.own_skill-ALLSKILL+2);
        AddSkill();
        SendMassage(QChar('S'));
        new_skill.own_skill=(SkillType)(new_skill.own_skill+i);
        if(new_skill.own_skill>=ALLSKILL)
            new_skill.own_skill=(SkillType)(new_skill.own_skill-ALLSKILL+2);
        AddSkill();
        SendMassage(QChar('S'));//发送三个技能

        s_Write.release();

        SendMassage(QChar('Q'));//注册并登陆完成
        load_success=true;

        AddList();

        return;
    }
    else{
        s="该用户名已存在！";
        SendMassage(QChar('E'));//用户名已存在
    }

    s_Write.release();
}

void MyThread::DealT()//换头像
{
    RECEIVESTREAM>>new_user.head_number;
    s.setNum(new_user.head_number);
    item->setIcon(QIcon(":/User/touxiang/头像"+s));
    item->setText(new_user.name+s);

    s=QString("update ElfMaster set Touxiang=%1 where Name='%2'").arg(new_user.head_number).arg(new_user.name);
    s_Write.acquire();
    query->exec(s);
    s_Write.release();
}

void MyThread::DealR()//请求更新在线列表
{
    SendMassage(QChar('R'));
    ListStart();

    int i=g_Online_List->count();
    for(;i>0;i--){//读用户列表并发送
        other_item=g_Online_List->item(i-1);
        s=other_item->text();
        other_user.name=s.left(s.length()-1);
        other_user.head_number=s.right(1).toInt();
        SendMassage(QChar('W'));
    }

    ListOver();
}

void MyThread::DealP()//用户反馈精灵技能信息，更新数据库
{
    int i,k,s1,s2;
    RECEIVESTREAM>>i;
    RECEIVESTREAM>>s1;
    RECEIVESTREAM>>s2;
    RECEIVESTREAM>>new_pet.own_elf.l;
    RECEIVESTREAM>>new_pet.own_elf.l1;
    RECEIVESTREAM>>new_pet.own_elf.l2;
    RECEIVESTREAM>>new_pet.own_elf.experience;
    s=QString("update ElfPet set "
              "skill1=%1,"
              "skill2=%2,"
              "l=%3,"
              "l1=%4,"
              "l2=%5,"
              "experience=%6"
              " where Master='%7' and your_elf=%8")
            .arg(s1).arg(s2).arg(new_pet.own_elf.l)
            .arg(new_pet.own_elf.l1).arg(new_pet.own_elf.l2)
            .arg(new_pet.own_elf.experience)
            .arg(new_user.name).arg(i);

    s_Write.acquire();

    query->exec(s);//更新宠物信息

    for(i=LEAF_ATTACK;i<ALLSKILL;i++){//更新技能信息
        RECEIVESTREAM>>k;
        if(k>=0){
            s=QString("update ElfSkill set Remain=%1 where Master='%2' and Skill=%3")
                    .arg(k)
                    .arg(new_user.name)
                    .arg(i);
            query->exec(s);
        }
    }

    s_Write.release();
}

void MyThread::DealL()//查看其他用户的精灵
{
    RECEIVESTREAM>>ss;
    other_user.name=ss;
    s=QString("select * from ElfPet where Master = '%1'").arg(other_user.name);

    ReadStart();

    query->exec(s);
    query->first();
    int i=query->value(PYOUR_ELF).toInt();
    new_pet.own_elf.your_elf=(PetNumber)i;
    new_pet.own_elf.l=query->value(PL).toInt();
    SendMassage(QChar('L'));//读取其他用户的精灵并且一一发送
    while(query->next()){
        i=query->value(PYOUR_ELF).toInt();
        new_pet.own_elf.your_elf=(PetNumber)i;
        new_pet.own_elf.l=query->value(PL).toInt();
        SendMassage(QChar('L'));
    }
    s=QString("select * from ElfMaster where Name='%1'").arg(other_user.name);
    query->exec(s);
    query->first();

    count_total=query->value(TOTAL).toInt();//读取胜率信息
    count_win=query->value(WIN).toInt();

    ReadOver();

    other_user.head_number=0;
    SendMassage(QChar('K'));//发送徽章和胜率信息
}

void MyThread::DealK()//请求查看用户列表
{
    s=QString("select * from ElfMaster");

    ReadStart();

    query->exec(s);
    query->first();
    other_user.head_number = query->value(TOUXIANG).toInt();
    other_user.name = query->value(NAMEUSER).toString();
    SendMassage(QChar('K'));
    while(query->next()){//读取其他用户信息一一发送
        other_user.head_number = query->value(TOUXIANG).toInt();
        other_user.name = query->value(NAMEUSER).toString();
        SendMassage(QChar('K'));
    }

    ReadOver();
}

void MyThread::DealH()//狩猎请求
{
    RandomSPet(1);
    SendMassage(QChar('H'));
    RandomSPet(2);
    SendMassage(QChar('H'));
    RandomSPet(3);
    SendMassage(QChar('H'));//随机发送三个对手
    SendMassage(QChar('C'));//允许狩猎
}

void MyThread::DealJ()//决斗请求
{
    int i;
    RECEIVESTREAM>>i;//判断是进入决斗画面还是开始决斗战斗
    if(i==1){
        state_mode=MPREPARE;//进入决斗准备模式
        RandomJPet(1);
        SendMassage(QChar('J'));
        RandomJPet(2);
        SendMassage(QChar('J'));
        RandomJPet(3);
        SendMassage(QChar('J'));//随机发送三个对手
        SendMassage(QChar('C'));//允许决斗
    }
    else if(i==2){//开始决斗赛，防止用户丢弃宠物时关闭游戏
        state_mode=MJVEDOU;
    }
}

void MyThread::DealU()//处理升级信息
{
    int i;
    RECEIVESTREAM>>i;
    new_pet.own_elf.your_elf=(PetNumber)i;
    RECEIVESTREAM>>new_pet.own_elf.l>>new_pet.own_elf.experience;

    s=QString("update ElfPet set l=%1,experience=%2 where Master='%3' and your_elf=%4")
            .arg(new_pet.own_elf.l)
            .arg(new_pet.own_elf.experience)
            .arg(new_user.name)
            .arg((int)new_pet.own_elf.your_elf);

    s_Write.acquire();

    query->exec(s);//更细经验

    s_Write.release();

    DealH();//使用户返回狩猎界面
}

void MyThread::DealG()
{//胜利获得一些宠物或者技能或者经验
    QChar cc;
    RECEIVESTREAM>>cc;
    state_mode=MNORMAL;

    s_Write.acquire();

    if(cc=='P'){//获得新宠物
        int i,l;
        RECEIVESTREAM>>i>>l;
        new_pet.own_elf={
            (PetNumber)i,UNLOCKED,LOCKED,l,1,1,0
        };
        AddPet();
        count_pet++;
    }
    else if(cc=='S'){//获得新技能
        int i;
        RECEIVESTREAM>>i;
        new_skill.own_skill=(SkillType)i;
        new_skill.learn_remain=SKILLREMAIN;
        AddSkill();
    }
    else if(cc=='E'){//获得额外经验
        int i;
        RECEIVESTREAM>>i;
        new_pet.own_elf.your_elf=(PetNumber)i;
        RECEIVESTREAM>>new_pet.own_elf.l>>new_pet.own_elf.experience;
        s=QString("update ElfPet set l=%1,experience=%2 where Master='%3' and your_elf=%4")
                .arg(new_pet.own_elf.l)
                .arg(new_pet.own_elf.experience)
                .arg(new_user.name)
                .arg((int)new_pet.own_elf.your_elf);
        query->exec(s);
    }
    s=QString("update ElfMaster set Total=Total+1,Win=Win+1 where Name='%1'").arg(new_user.name);
    query->exec(s);

    s_Write.release();
}

void MyThread::DealF()
{//失败送出宠物
    int i,k;
    RECEIVESTREAM>>i;
    state_mode=MNORMAL;
    s=QString("delete from ElfPet where Master='%1' and your_elf=%2").arg(new_user.name).arg(i);
    count_pet--;

    s_Write.acquire();

    query->exec(s);

    if(count_pet==0){//一个宠物也没有
        RandomPet(1);
        AddPet();
        SendMassage(QChar('P'));
        count_pet++;
    }

    for(i=LEAF_ATTACK;i<ALLSKILL;i++){//更新技能信息
        RECEIVESTREAM>>k;
        if(k>=0){
            s=QString("update ElfSkill set Remain=%1 where Master='%2' and Skill=%3")
                    .arg(k)
                    .arg(new_user.name)
                    .arg(i);
            query->exec(s);
        }
    }
    s=QString("update ElfMaster set Total=Total+1 where Name='%1'").arg(new_user.name);
    query->exec(s);

    s_Write.release();
}

void MyThread::DealD()
{//失败一局
    s=QString("update ElfMaster set Total=Total+1 where Name='%1'").arg(new_user.name);

    s_Write.acquire();

    query->exec(s);

    s_Write.release();
}

void MyThread::DealV()
{//胜利一局
    s=QString("update ElfMaster set Total=Total+1,Win=Win+1 where Name='%1'").arg(new_user.name);

    s_Write.acquire();

    query->exec(s);

    s_Write.release();
}

void MyThread::DealX()
{//输入密钥更新精灵二技能
    s=QString("update ElfPet set Skill2=1 where Master='%1' and Skill2=0").arg(new_user.name);

    s_Write.acquire();

    query->exec(s);

    s_Write.release();
}



