#ifndef GLOBAL_H
#define GLOBAL_H

#include <QDebug>
#include <QString>
#include <time.h>
#include <QSemaphore>
#include <QsqlDatabase>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QTcpServer>
#include <QTcpSocket>
#include <QListWidgetItem>
#include <QListWidget>
#include <QHostAddress>
#include <QByteArray>
#include <QDataStream>
#define RANDOM(x) ((rand()%(x))+1)

#define ALLPET 25
#define ALLTIME 6
#define ALLSKILL 11
#define SKILLREMAIN 6

enum ItemUser{//用户表中的表项
    NAMEUSER,PASSWORD,TOUXIANG,TOTAL,WIN
};

enum ItemPet{//精灵表中的表项
    PMASTER,PYOUR_ELF,PSKILL1,PSKILL2,PL,PL1,PL2,PEXPERIENCE
};

enum ItemSkill{//技能表中的表项
    SMASTER,SSKILL,SREMAIN
};

enum StateMode{//控制状态
    MNORMAL,MJVEDOU,MPREPARE
};

typedef enum SkillType{//技能种类
    LOCKED,UNLOCKED,
    LEAF_ATTACK,FLAME_ATTACK,THUNDER_ATTACK,ICE_ATTACK,DARK_ATTACK,
    XILI,BUQUYIZHI,XIANXVEKEWANG,XIANQUTUJI
}SkillT;

enum PetNumber{//精灵种类
    YEJINGLING,HUOJINGLING,BINGJINGLING,LEIJINGLING,HEIJINGLING,
    XUANWUSHOU,BAOLONGSHOU,JIALULUSHOU,QINGLONGSHOU,YUANDUXIXVEGUI,
    TIANNVSHOU,ZHANDOUBAOLONG,GANGTIEJIALULU,DUJIAOXIAN,SANGSHIBAOLONG,
    XIANRENZHANG,JIANSHISHOU,GANGTIEHAILONG,ZUDUNSHOU,EMOSHOU,
    MUOUSHOU,JIALOULUOSHOU,LANGRENJIALULU,AOMIJIASHOU,NVEMOSHOU
};

typedef struct QuickPet{//快速记录宠物信息结构
    PetNumber your_elf;
    SkillT s1;
    SkillT s2;
    int l;
    int l1;
    int l2;
    int experience;
}QuickElf;

class PetOwn{//用户拥有的精灵类
public:
    PetOwn();
    QuickElf own_elf;
};

class SkillOwn{//用户拥有的技能类
public:
    SkillOwn();
    SkillType own_skill;
    int learn_remain;
};

class QuickUser{//快速记录用户信息
public:
    QString name;
    QString password;
    int head_number;
};

extern QListWidget* g_Online_List;//在线用户表
extern QTcpServer g_Tcp_Server;//tcp服务器
extern QSemaphore s_Count;
extern QSemaphore s_Write;//读写信号量
extern QSemaphore s_List;
extern QSemaphore s_Count_List;//用户列表信号量
extern int g_Count;//再读数据库的用户数量
extern int g_Count_List;//用户数量
extern QSqlDatabase g_Database;//数据库

#endif // GLOBAL_H
