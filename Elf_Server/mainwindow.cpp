#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    g_Tcp_Server.listen(QHostAddress::Any,5211);
    g_Database = QSqlDatabase::addDatabase("QSQLITE","ElfData");
    g_Database.setDatabaseName("ElfData.db");//使用哪个数据库
    g_Database.open();//打开数据库

    QSqlQuery query(g_Database);
    query.exec("create table ElfMaster(Name String primary key,Password String,Touxiang int,Total int,Win int)");
    query.exec("create table ElfPet(Master String,your_elf int,skill1 int,skill2 int,l int,l1 int,l2 int,experience int)");
    query.exec("create table ElfSkill(Master String ,Skill int,Remain int)");
    //创建表
    connect(&g_Tcp_Server,&QTcpServer::newConnection,this,OpenThread);//关联线程槽函数

    g_Online_List=new QListWidget(this);
    ui->gridLayout->addWidget(g_Online_List);
    g_Online_List->show();//设置用户表显示格式
    g_Online_List->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    g_Online_List->setIconSize(QSize(20,20));
    g_Online_List->setWrapping(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::OpenThread()
{
    MyThread* my_thread=new MyThread(0);//来一个用户新开一个线程
    my_thread->start();
}

