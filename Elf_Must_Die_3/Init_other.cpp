#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::InitTouxiang()//初始化所有头像
{
    AddTouxiang("1","亚古兽头像",1);
    AddTouxiang("2","加布兽头像",1);
    AddTouxiang("3","哥玛兽头像",1);
    AddTouxiang("4","巴鲁兽头像",1);
    AddTouxiang("5","甲虫兽头像",1);
    AddTouxiang("6","比丘兽头像",1);
    AddTouxiang("7","巴达兽头像",1);
    AddTouxiang("8","迪露兽头像",1);
    ui->listWidgetTouxiang->setCurrentRow(0);
}

void MainWindow::InitOther()//初始化其他所有东西
{
    my_timer=new QTimer(this);
    connect(my_timer,SIGNAL(timeout()),this,SLOT(Frash()));
    special_timer=new QTimer(this);
    connect(special_timer,SIGNAL(timeout()),this,SLOT(OverTexiao()));//初始化定时器
    wait_count=0;
    load_success=false;
    load_count=true;
    flag_chongwu=false;
    tcp_socket=NULL;
    send_stream_ptr=NULL;
    receive_stream_ptr=NULL;
    winner=0;
    flag_back=false;
    pixmap = QPixmap(g_background+"背景3").scaled(this->size());
    back=new QLabel(this);
    teword=new QLabel(this);
    back->setScaledContents(true);
    teword->setScaledContents(true);
    back->hide();
    teword->hide();
    count_special=0;
    g_open_texiao=1;
    sug=new suggestion(NULL);
    connect(ui->ButtonMShezhi,SIGNAL(clicked(bool)),sug,SLOT(show()));
    sug->hide();//初始化一些参数的初始值

    /*主页面*/
    ui->LabelMTouxiang->setPixmap(master.head_picture);
    ui->labelMElfName->setText(show_pet.name);
    ui->labelMElfTouxiang->setPixmap(show_pet.image);
    ui->labelMPetnum->setNum(master.count_pet);
    ui->ButtonMYonghu->setText(master.name);
    /*用户页面*/
    ui->labelUTouxiang->setPixmap(master.head_picture);
    /*宠物页面*/
    ui->textBrowserCJieshao->setWordWrapMode(QTextOption::WordWrap);
    /*头像页面*/
    InitTouxiang();
    /*更新速度*/
    speed_fight=55;
    InitSpeed();
    /*演武页面*/
    for(int i=0;i<MAXLEVEL;i++){
        s.setNum(i+1);
        ui->comboBoxYWoLevel->addItem(s);
        ui->comboBoxYDiLevel->addItem(s);
    }
    ui->comboBoxYWoLevel->setEnabled(false);
    /*狩猎和决斗页面*/
    for(int i=0;i<MAXLEVEL;i++){
        s.setNum(i+1);
        ui->comboBoxSWoLevel->addItem(s);
        ui->comboBoxSDiLevel->addItem(s);
    }
    ui->comboBoxSWoLevel->setEnabled(false);
    ui->labelShoulie->setAlignment(Qt::AlignHCenter);
    ui->labelSShuoming->setWordWrap(true);
}

void MainWindow::AddTouxiang(QString i, QString text, int flag)
{
    QListWidgetItem *item=new QListWidgetItem;
    if(flag==1){//用户头像
        item->setIcon(QIcon(g_touxiang_user+i));
        item->setText(text);
        ui->listWidgetTouxiang->addItem(item);
    }
    else if(flag==2){//精灵头像
        item->setIcon(QIcon(g_touxiang_pet+text));
        item->setText(text+"\nLV"+i);
        ui->listWidgetOPetshow->addItem(item);
    }
    else{//其他用户头像
        item->setIcon(QIcon(g_touxiang_user+i));
        item->setText(text);
        ui->listWidgetOWanjia->addItem(item);
    }
}
