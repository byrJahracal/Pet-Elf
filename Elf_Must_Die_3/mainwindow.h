#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Qtimer>
#include "Battle.h"
#include "User.h"
#include <time.h>
#include <QMessageBox>
#include <QTcpSocket>
#include <QHostAddress>
#include <QByteArray>
#include <QMessageBox>
#include <QListWidget>
#include <QListWidgetItem>
#include <QAbstractButton>
#include <QDataStream>
#include <QPainter>
#include <QPaintEvent>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QLabel>
#include "suggestion.h"

#define  SENDSTREAM  *send_stream_ptr
#define RECEIVESTREAM *receive_stream_ptr

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTimer* my_timer;//战斗的基本时间单位
    QTimer* special_timer;//特效控制时钟
    Battle battle_field;//战场
    User master;//用户
    StateWindow state_main;//页面，程序状态
    bool load_success;//登录成功记录
    bool load_count;//用于登录逻辑控制
    int load_timer;//用于连接超时提醒
    FightMode fight_mode;//战斗模式
    QString s;
    char *ss;//通用
    QByteArray receive_array;//TCP接受数据
    QByteArray send_array;//TCP发送数据
    QuickUser new_user;//简单的用户信息，可存别的用户的信息
    PetOwn new_pet;//通用宠物的信息
    QuickElf enemy[3];//决斗赛和升级赛的系统分发的三个精灵
    SkillOwn new_skill;//临时技能信息
    PetElf show_pet;//宠物界面展示的宠物
    PetElf show_pet_wo;//战斗时的我方宠物
    PetElf show_pet_di;//战斗时的敌方精灵
    int wait_count;//战斗时的留给用户反应的时间
    int speed;//程序循环频率
    int speed_fight;//战斗时的循环频率
    ushort send_length;//发送数据长度
    ushort receive_length;//接受一个包的长度
    ushort total_length;//接受全部数据的长度
    QTcpSocket *tcp_socket;
    QDataStream *send_stream_ptr;//发送数据流
    QDataStream *receive_stream_ptr;//接受数据流
    const int least_length = sizeof(ushort);//最小帧长度
    bool flag_chongwu;//防止宠物切换时触发槽函数
    int winner;//记录战斗胜利者
    float count_shenglv;//用户胜率
    int count_total;//精灵总数
    int count_gaoji;//高级精灵数
    bool flag_back;//切换界面时控制切换背景
    QPixmap pixmap;//通用pixmap
    QLabel *back;//特效背景
    QLabel *teword;//特效文字
    QPropertyAnimation *pAnimation1;//弹窗特效，抖动特效
    QPropertyAnimation *pAnimation2;//文字特效
    int count_special;//特效控制
    suggestion *sug;//游戏说明窗口

    void JiaSpeed();
    void JianSpeed();
    void InitSpeed();
    void SetSpeed();//游戏速度控制

    void InitTcp();
    void InitTouxiang();
    void InitOther();
    void InitChongwu();
    void InitLearnedSkill();
    void InitYanwu();
    void InitShoulie();
    void InitJvedou();//各种初始化

    void JveDouPower();//决斗时对敌方精灵适当加强

    void AddTouxiang(QString i,QString text,int flag);//初始化加入头像
    /*处理TCP发来的各种消息类型*/
    void DealQ();//登陆成功
    void DealP();//获得宠物
    void DealS();//获得技能
    void DealW();//添加在线列表
    void DealR();//刷新在线列表
    void DealL();//查看其他用户的精灵
    void DealK();//查看所有用户
    void DealH();//添加升级赛和决斗赛的对手
    void DealC();//允许决斗赛和升级赛

    void PageChange(StateWindow new_state);//页面切换
    void SendTcp(QChar c,int flag=0);//发送tcp消息
    void test();//写代码过程中的测试
    void ShowElf();//宠物界面展示宠物信息
    void UpLevel();//战斗胜利后计算经验和升级信息
    void GetMore();//决斗赛胜利获得额外精灵技能经化奖励
    void Failed();//失败后丢弃宠物处理
    void paintEvent(QPaintEvent *event);//绘画背景
    void TeXiao1();//弹窗特效判定
    void TeXiao2();//抖动特效判定
    void TeXiaoBack();//弹窗特效实现
    void TeXiaoLabel(int dir);//抖动特效
    void ShowState();//战斗时显示精灵状态

public slots:
    void Frash();//QTIMER控制的刷新函数，主要用于战斗
    void OverTexiao();//特效结束处理
private slots://所有槽函数
    void on_ButtonMYonghu_clicked();
    void on_ButtonMYanwu_clicked();
    void on_PushButtonFReturn_clicked();
    void PrepareToFight();//战前准备
    void on_PushButtonFJIasu_clicked();
    void on_PushButtonFJiansu_clicked();
    void ConnectSuccess();//连接服务器成功
    void SolveTcp();//受到tcp消息处理
    void on_pushButtonULoad_clicked();
    void on_pushButtonYnew_clicked();
    void on_pushButtonUTou_clicked();
    void on_buttonBoxTouxiang_clicked(QAbstractButton *button);
    void on_pushButtonMGengxing_clicked();
    void on_comboBoxCChooseelf_currentIndexChanged(const QString &arg1);
    void on_comboBoxCSkill1_currentIndexChanged(const QString &arg1);
    void on_comboBoxCSkill2_currentIndexChanged(const QString &arg1);
    void on_pushButtonMChongwu_clicked();
    void on_pushButtonCSkill1Learn_clicked();
    void on_pushButtonCSkill2Learn_clicked();
    void on_pushButtonCSkill1destribute_clicked();
    void on_pushButtonCSkill2destribute_clicked();
    void on_pushButtonCChongzhi_clicked();
    void on_pushButtonCBack_clicked();
    void on_pushButtonUQveren_clicked();
    void on_pushButtonMSendlook_clicked();
    void on_pushButtonOBack_clicked();
    void on_pushButtonUDengchu_clicked();
    void on_listWidgetOWanjia_currentRowChanged(int currentRow);
    void on_ComboBoxYWofang_currentIndexChanged(const QString &arg1);
    void on_ComboBoxYDifang_currentIndexChanged(const QString &arg1);
    void on_comboBoxYDiLevel_currentIndexChanged(const QString &arg1);
    void on_buttonBoxYanwu_clicked(QAbstractButton *button);
    void on_ButtonMShoulie_clicked();
    void on_ComboBoxSWofang_currentIndexChanged(const QString &arg1);
    void on_ComboBoxSDifang_currentIndexChanged(int index);
    void on_comboBoxSDiLevel_currentIndexChanged(int index);
    void on_buttonBoxShoulie_clicked(QAbstractButton *button);
    void on_ButtonMJvedou_clicked();
    void on_pushButtonSSend_clicked();
    void on_lineEditMmiyao_editingFinished();
};

#endif // MAINWINDOW_H
