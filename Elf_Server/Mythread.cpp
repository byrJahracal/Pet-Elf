#include "Mythread.h"

MyThread::MyThread(QThread *parent) : QThread(parent)
{
    srand(time(NULL));
    tcp_socket=g_Tcp_Server.nextPendingConnection();//建立新的用户连接
    load_success=false;
    state_mode=MNORMAL;
    count_pet=0;
    query=new QSqlQuery(g_Database);//数据库连接
    send_stream_ptr=new QDataStream(&send_array,QIODevice::WriteOnly);
    send_stream_ptr->setByteOrder(QDataStream::BigEndian);
    send_stream_ptr->setVersion(QDataStream::Qt_5_8);//初始化发送流
    receive_stream_ptr=new QDataStream(&receive_array,QIODevice::ReadOnly);
    receive_stream_ptr->setByteOrder(QDataStream::BigEndian);
    receive_stream_ptr->setVersion(QDataStream::Qt_5_8);//初始化接受流
    item=new QListWidgetItem(Q_NULLPTR,QListWidgetItem::Type);
}

void MyThread::SendMassage(QChar cc)//发送消息
{
    send_array.clear();
    send_stream_ptr->device()->seek(0);
    SENDSTREAM<<ushort(0);
    SENDSTREAM<<cc;
    char c=cc.unicode();
    switch(c){//根据标志为发送不同的消息
    case 'Q':{
        SENDSTREAM<<new_user.name.toUtf8()<<new_user.head_number;
        break;
    }
    case 'P':{
        int i=new_pet.own_elf.your_elf;
        SENDSTREAM<<i;
        i=new_pet.own_elf.s1;
        SENDSTREAM<<i;
        i=new_pet.own_elf.s2;
        SENDSTREAM<<i;
        SENDSTREAM<<new_pet.own_elf.l<<new_pet.own_elf.l1<<new_pet.own_elf.l2;
        SENDSTREAM<<new_pet.own_elf.experience;
        break;
    }
    case 'E':{
        SENDSTREAM<<s.toUtf8();
        break;
    }
    case 'S':{
        int i=new_skill.own_skill;
        qDebug()<<i<<new_skill.learn_remain;
        SENDSTREAM<<i<<new_skill.learn_remain;
        break;
    }
    case 'W':{
        SENDSTREAM<<other_user.name.toUtf8()<<other_user.head_number;
        break;
    }
    case 'R':{
        break;
    }
    case 'L':{
        int i=new_pet.own_elf.your_elf;
        SENDSTREAM<<i<<new_pet.own_elf.l;
        break;
    }
    case 'K':{
        if(other_user.head_number!=0){
            SENDSTREAM<<other_user.head_number;
            SENDSTREAM<<other_user.name.toUtf8();
        }
        else{
            SENDSTREAM<<other_user.head_number;
            SENDSTREAM<<count_total;
            SENDSTREAM<<count_win;
        }
        break;
    }
    case 'H'://返回狩猎精灵
    case 'J':{//返回决斗精灵
        int i=new_pet.own_elf.your_elf;
        SENDSTREAM<<i;
        i=new_pet.own_elf.s1;
        SENDSTREAM<<i;
        i=new_pet.own_elf.s2;
        SENDSTREAM<<i;
        break;
    }
    case 'C':{
        if(state_mode==MNORMAL){
            cc='S';
            SENDSTREAM<<cc;
        }
        else if(state_mode==MPREPARE){
            cc='J';
            SENDSTREAM<<cc;
        }
        else {
            cc='E';
            SENDSTREAM<<cc;
        }
    }
    }
    send_stream_ptr->device()->seek(0);
    send_length=send_array.size();
    SENDSTREAM<<send_length;//加入消息长度信息
    tcp_socket->write(send_array);
}

void MyThread::ReadStart()//开始读数据库信号量
{
    s_Count.acquire();
    if(++g_Count==1)
        s_Write.acquire();
    s_Count.release();
}

void MyThread::ReadOver()//结束读数据库信号量
{
    s_Count.acquire();
    if(--g_Count==0)
        s_Write.release();
    s_Count.release();
}

void MyThread::ListStart()//读用户表开始
{
    s_Count_List.acquire();
    if(++g_Count_List==1)
        s_List.acquire();
    s_Count_List.release();
}

void MyThread::ListOver()//度用户表结束
{
    s_Count_List.acquire();
    if(--g_Count_List==0)
        s_List.release();
    s_Count_List.release();
}

void MyThread::AddList()//在用户表中加入新的表项
{
    s.setNum(new_user.head_number);
    item->setIcon(QIcon(":/User/touxiang/头像"+s));
    item->setText(new_user.name+s);
    s_List.acquire();
    g_Online_List->addItem(item);
    s_List.release();
}

void MyThread::QuitDeal()//退出处理
{
    if(state_mode==MJVEDOU){//防止用户送出宠物时退出

        ReadStart();

        int i=RANDOM(ALLPET)-1;
        s=QString("select * from ElfPet where Master='%1' and your_elf=%2")
                .arg(new_user.name)
                .arg(i);
        query->exec(s);
        while(!query->first()){
            i=(i+1)%ALLPET;
            s=QString("select * from ElfPet where Master='%1' and your_elf=%2")
                    .arg(new_user.name)
                    .arg(i);
            query->exec(s);
        }
        int s1,s2;
        s1=query->value(PSKILL1).toInt();
        s2=query->value(PSKILL2).toInt();

        ReadOver();

        s=QString("delete from ElfPet where Master='%1' and your_elf=%2")
                .arg(new_user.name)
                .arg(i);//随便丢一个宠物

        s_Write.acquire();

        query->exec(s);
        count_pet--;
        if(count_pet==0){
            RandomPet(1);
            AddPet();
        }
        if(s1!=UNLOCKED){
            s=QString("update ElfSkill set Remain=Remain+1 where Master='%1' and Skill=%2")
                    .arg(new_user.name)
                    .arg(s1);
            query->exec(s);
        }
        if(s2!=UNLOCKED&&s2!=LOCKED){
            s=QString("update ElfSkill set Remain=Remain+1 where Master='%1' and Skill=%2")
                    .arg(new_user.name)
                    .arg(s2);
            query->exec(s);
        }

        s_Write.release();
    }

    s_List.acquire();
    delete item;
    s_List.release();
    this->quit();
    this->wait();
}

void MyThread::run()
{
    connect(tcp_socket, &QTcpSocket::disconnected, this, &MyThread::QuitDeal, Qt::DirectConnection);//接收消息处理
    connect(tcp_socket, &QTcpSocket::readyRead,this,&MyThread::DealTcp);//推出处理连接
    this->exec();
}



