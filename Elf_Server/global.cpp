#include "global.h"

QListWidget* g_Online_List;//在线用户数量
QTcpServer g_Tcp_Server;//tcp服务器
QSemaphore s_Count(1);
QSemaphore s_Write(1);//读写信号量
QSemaphore s_List(1);
QSemaphore s_Count_List(1);//用户表信号量
int g_Count=0;//在读数据库的用户数量
int g_Count_List=0;//在线用户数量
QSqlDatabase g_Database;//数据库

PetOwn::PetOwn()//用户精灵
{
    own_elf={YEJINGLING,UNLOCKED,LOCKED,1,1,1,0};
}

SkillOwn::SkillOwn()//用户技能
{
    own_skill=LOCKED;
    learn_remain=0;
}
