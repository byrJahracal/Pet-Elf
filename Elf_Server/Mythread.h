#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include "global.h"

#define  SENDSTREAM  *send_stream_ptr
#define RECEIVESTREAM *receive_stream_ptr

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QThread *parent = 0);
    QTcpSocket* tcp_socket;//tcp连接
    QuickUser new_user;//用户信息
    QuickUser other_user;//其他用户信息
    PetOwn new_pet;
    PetNumber new_pet2;
    PetNumber new_pet3;//宠物信息
    SkillOwn new_skill;//技能信息
    QListWidgetItem *item;//在线用户表中的一项
    QListWidgetItem *other_item;//读取其他用户信息
    QString s;
    char *ss;//通用
    QByteArray receive_array;//接受数据
    QByteArray send_array;//发送数据
    QSqlQuery *query;//数据库操作
    QDataStream *send_stream_ptr;//发送流
    QDataStream *receive_stream_ptr;//接受流
    ushort send_length;//发送数据长度
    ushort receive_length;//接收数据长度
    ushort total_length;//接收数据总长度
    const int least_length = sizeof(ushort);//最小帧长度
    StateMode state_mode;//用户状态
    int count_pet;//统计精灵个数
    int count_total;//统计战斗常场数
    int count_win;//统计胜利场数
    bool load_success;//登陆成功标志

    void DealTcp();//处理tcp包
    void DealO();//老用户登录
    void DealN();//新用户注册
    void DealT();//更换头像
    void DealR();//刷新在线列表
    void DealP();//更新用户精灵技能状态
    void DealL();//查看其他用户宠物
    void DealK();//查看其他用户
    void DealH();//狩猎请求
    void DealJ();//决斗请求
    void DealU();//宠物升级
    void DealG();//获得新的东西
    void DealF();//收回宠物
    void DealD();//失败一局
    void DealV();//胜利一局
    void DealX();//解锁二技能
    void RandomPet(int count);//随机发一个精灵
    void RandomSkill(int flag);//随机发一个技能
    void YourPet();//发送用户所有宠物
    void YourSkill();//发送用户所有技能
    void SendOnePet();//发送一个宠物信息
    void SendOneSkill();//发送一个技能信息
    void SendMassage(QChar c);//给用户发送消息
    void ReadStart();//开始读数据库信号量处理
    void ReadOver();//结束读数据库信号量处理
    void ListStart();//开始读用户列表信号量处理
    void ListOver();//结束读用户列表信号量处理
    void AddList();//在表中加一个item
    void AddPet();//用户加一个精灵
    void AddSkill();//用户加一个技能
    void RandomSPet(int count);//随机生成狩猎的三个精灵
    void RandomJPet(int count);//随机生成决斗的三个精灵

protected:
    void run();

signals:

public slots:
    void QuitDeal();//退出处理
};

#endif // MYTHREAD_H
