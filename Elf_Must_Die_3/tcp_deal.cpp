#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::InitTcp()//初始化tcp连接
{
    //服务器信息
    if(tcp_socket==NULL)
        tcp_socket = new QTcpSocket(this);
    if(tcp_socket->state()!=QTcpSocket::ConnectedState){
        QString ip = "127.0.0.1";
        qint16 port = 5211;

        //主动连接
        connect(tcp_socket,&QTcpSocket::connected,this,ConnectSuccess);
        tcp_socket->connectToHost(QHostAddress(ip),port);
        tcp_socket->connect(tcp_socket,&QTcpSocket::readyRead,this,SolveTcp);
    }
    if(send_stream_ptr==NULL){
        send_stream_ptr=new QDataStream(&send_array,QIODevice::WriteOnly);
        send_stream_ptr->setByteOrder(QDataStream::BigEndian);
        send_stream_ptr->setVersion(QDataStream::Qt_5_8);
    }
    if(receive_stream_ptr==NULL){
        receive_stream_ptr=new QDataStream(&receive_array,QIODevice::ReadOnly);
        receive_stream_ptr->setByteOrder(QDataStream::BigEndian);
        receive_stream_ptr->setVersion(QDataStream::Qt_5_8);
    }
}

void MainWindow::DealQ()//确认登录
{
    RECEIVESTREAM>>ss;
    new_user.name=ss;
    RECEIVESTREAM>>new_user.head_number;
    load_count=!load_count;
    load_success=load_count;
    if(load_success==true){
        master.Deal(new_user);
        InitChongwu();
        ui->lineEditUMimaNew->clear();
        ui->lineEditUMimaOld->clear();
        ui->lineEditUNameNew->clear();
        ui->lineEditUNameOld->clear();
        PageChange(PMAIN);
    }
    else{
        master.Clear();
    }
}

void MainWindow::DealP()//收到一个宠物
{
    int i;
    RECEIVESTREAM>>i;
    new_pet.own_elf.your_elf=(PetNumber)i;
    RECEIVESTREAM>>i;
    new_pet.own_elf.s1=(SkillType)i;
    RECEIVESTREAM>>i;
    new_pet.own_elf.s2=(SkillType)i;
    RECEIVESTREAM>>new_pet.own_elf.l;
    RECEIVESTREAM>>new_pet.own_elf.l1;
    RECEIVESTREAM>>new_pet.own_elf.l2;
    RECEIVESTREAM>>new_pet.own_elf.experience;
    master.Deal(new_pet);
    if(load_success){
        PageChange(PMAIN);
        ui->StackedWidgetQiehuan->show();
        s="恭喜你获得新的宠物小精灵:"+g_Name[new_pet.own_elf.your_elf];
        QMessageBox::information(NULL,"提示",s,QMessageBox::Ok);
    }
}

void MainWindow::DealS()//收到一个技能
{
    int i;
    RECEIVESTREAM>>i;
    new_skill.own_skill=(SkillType)i;
    RECEIVESTREAM>>new_skill.learn_remain;
    master.Deal(new_skill);
}

void MainWindow::DealW()//收到一个其他用户的信息
{
    RECEIVESTREAM>>ss;
    new_user.name=ss;
    RECEIVESTREAM>>new_user.head_number;
    s.setNum(new_user.head_number);
    QListWidgetItem *item=new QListWidgetItem;
    item->setIcon(QIcon(g_touxiang_user+s));
    item->setText(new_user.name);
    ui->listWidgetMWorld->addItem(item);
}

void MainWindow::DealR()//刷新世界列表
{
    RECEIVESTREAM>>ss;
    new_user.name=ss;
    QListWidgetItem *item;
    int n=ui->listWidgetMWorld->count();
    for(int i=0;i<n;i++){
        item=ui->listWidgetMWorld->takeItem(0);
        delete item;
    }
}

void MainWindow::DealL()//系统给你法别的用户的精灵
{
    int i;
    RECEIVESTREAM>>i;
    s=g_Name[i];
    QString l;
    RECEIVESTREAM>>i;
    l.setNum(i);
    AddTouxiang(l,s,2);
    count_total++;
    if(i==MAXLEVEL)
        count_gaoji++;
}

void MainWindow::DealK()//系统给你发别的用户信息
{
    int i;
    RECEIVESTREAM>>i;
    if(i!=0){//进入世界列表
        s.setNum(i);
        QString l;
        RECEIVESTREAM>>ss;
        l=ss;
        AddTouxiang(s,l,3);
    }
    else{//计算胜率，奖牌
        int t,w;
        RECEIVESTREAM>>t;
        RECEIVESTREAM>>w;
        if(t>0)
            count_shenglv=(float)w/(float)t;
        else
            count_shenglv=0;

        s.setNum(count_shenglv*100,'f',2);
        ui->labelOShenglv->setText(s+"%");
        if(count_shenglv<0.3)
            ui->labelOHui1->setText("木牌菜鸡");
        else if(count_shenglv<0.5)
            ui->labelOHui1->setText("铜牌大师");
        else if(count_shenglv<0.6)
            ui->labelOHui1->setText("银牌大师");
        else
            ui->labelOHui1->setText("金牌大师");

        ui->labelOZongshu->setNum(count_total);
        if(count_total<3)
            ui->labelOHui2->setText("木牌收集者");
        else if(count_total<4)
            ui->labelOHui2->setText("铜牌收集者");
        else if(count_total<10)
            ui->labelOHui2->setText("银牌收集者");
        else
            ui->labelOHui2->setText("金牌收集者");

        ui->labelOGaoji->setNum(count_gaoji);
        if(count_gaoji<1)
            ui->labelOHui3->setText("木牌战力");
        else if(count_gaoji<2)
            ui->labelOHui3->setText("铜牌战力");
        else if(count_gaoji<10)
            ui->labelOHui3->setText("银牌战力");
        else
            ui->labelOHui3->setText("金牌战力");
    }
}

void MainWindow::DealH()//系统分发你的战斗对手
{
    static int count_e=0;
    int i;
    RECEIVESTREAM>>i;
    enemy[count_e].your_elf=(PetNumber)i;
    RECEIVESTREAM>>i;
    enemy[count_e].s1=(SkillType)i;
    RECEIVESTREAM>>i;
    enemy[count_e].s2=(SkillType)i;
    count_e=(count_e+1)%3;
}

void MainWindow::DealC()//允许决斗赛和升级赛
{
    QChar c;
    RECEIVESTREAM>>c;
    if(c=='S'){
        InitShoulie();
        PageChange(PSHOULIE);
    }
    else if(c=='J'){
        InitJvedou();
        PageChange(PJVEDOU);
    }
    ui->StackedWidgetQiehuan->show();
}

void MainWindow::SendTcp(QChar cc,int flag)//发送tcp包
{
    send_array.clear();
    send_stream_ptr->device()->seek(0);//空出发送包的长度位
    SENDSTREAM<<ushort(0);
    SENDSTREAM<<cc;
    char c=cc.unicode();
    switch(c){
    case 'N':{
        SENDSTREAM<<new_user.name.toUtf8()<<new_user.password.toUtf8()<<new_user.head_number;
        break;
    }
    case 'O':{
        SENDSTREAM<<new_user.name.toUtf8()<<new_user.password.toUtf8();
        break;
    }
    case 'T':{
        SENDSTREAM<<master.head_number;
        break;
    }
    case 'R':{
        break;
    }
    case 'P':{//发送一个修改后的精灵信息,以及所有技能剩余情况
        int i=new_pet.own_elf.your_elf;
        SENDSTREAM<<i;
        i=new_pet.own_elf.s1;
        SENDSTREAM<<i;
        i=new_pet.own_elf.s2;
        SENDSTREAM<<i;
        SENDSTREAM<<new_pet.own_elf.l<<new_pet.own_elf.l1<<new_pet.own_elf.l2;
        SENDSTREAM<<new_pet.own_elf.experience;
        for(int i=LEAF_ATTACK;i<ALLSKILL;i++){
            if(master.my_skill[i]!=NULL){
                SENDSTREAM<<master.my_skill[i]->learn_remain;
            }
            else
                SENDSTREAM<<-1;
        }
        break;
    }
    case 'L':{
        SENDSTREAM<<s.toUtf8();
        break;
    }
    case 'K':{
        break;
    }
    case 'H':{//狩猎请求
        break;
    }
    case 'J':{//决斗请求
        SENDSTREAM<<flag;
        break;
    }
    case 'M':{//返回主菜单
        break;
    }
    case 'V':{
        break;
    }
    case 'D':{
        break;
    }
    case 'X':{//解锁2技能
        break;
    }
    case 'U':{//宠物升级
        int i=show_pet_wo.pet_num;
        SENDSTREAM<<i<<show_pet_wo.level<<show_pet_wo.experience;
        break;
    }
    case 'G':{//决斗战胜后获得新的东西
        if(flag==1){//获得新宠物
            SENDSTREAM<<QChar('P');
            int i=new_pet.own_elf.your_elf;
            SENDSTREAM<<i;
            SENDSTREAM<<new_pet.own_elf.l;
        }
        else if(flag==2){//获得新技能
            SENDSTREAM<<QChar('S');
            int i=new_skill.own_skill;
            SENDSTREAM<<i;
        }
        else if(flag==3){
            SENDSTREAM<<QChar('E');
            int i=show_pet_wo.pet_num;
            SENDSTREAM<<i<<show_pet_wo.level<<show_pet_wo.experience;
        }
        break;
    }
    case 'F':{
        SENDSTREAM<<flag;
        for(int i=LEAF_ATTACK;i<ALLSKILL;i++){
            if(master.my_skill[i]!=NULL){
                SENDSTREAM<<master.my_skill[i]->learn_remain;
            }
            else
                SENDSTREAM<<-1;
        }
        break;
    }
    }
    send_stream_ptr->device()->seek(0);
    send_length=send_array.size();
    SENDSTREAM<<send_length;//统计发送长度并且符加在发送数据中
    tcp_socket->write(send_array);
}

void MainWindow::ConnectSuccess()//成功连接切换到主界面
{
    ui->StackedWidgetQiehuan->setCurrentIndex(1);
}

void MainWindow::SolveTcp()//接收到tcp包处理
{
    load_timer=0;
    receive_stream_ptr->device()->seek(0);//粘包处理
    receive_array.append(tcp_socket->readAll());
    receive_length=receive_array.size();
    if(receive_length>=least_length){//可以读取该包的长度
        QChar cc;
        RECEIVESTREAM>>total_length;
        while(receive_length>=total_length){//收到至少一个完整包
            RECEIVESTREAM>>cc;
            char c=cc.unicode();
            switch(c){//根据第一个标志位辨别数据类型，区别处理
            case 'Q':{
                DealQ();
                break;
            }
            case 'E':{
                RECEIVESTREAM>>ss;
                s=ss;
                QMessageBox::critical(NULL,"错误",s,QMessageBox::Ok);
                break;
            }
            case 'P':{
                DealP();
                break;
            }
            case 'S':{
                DealS();
                break;
            }
            case 'W':{
                DealW();
                break;
            }
            case 'R':{
                DealR();
                break;
            }
            case 'L':{
                DealL();
                break;
            }
            case 'K':{
                DealK();
                break;
            }
            case 'J'://添加决斗精灵
            case 'H':{//添加狩猎精灵
                DealH();
                break;
            }
            case 'C':{
                DealC();
                break;
            }
            }
            receive_array=receive_array.right(receive_length-total_length);
            receive_length=receive_array.size();
            if(receive_length>=least_length){//可能有多个包
                receive_stream_ptr->device()->seek(0);
                RECEIVESTREAM>>total_length;
            }
            else{
                break;
            }
        }
    }
}


