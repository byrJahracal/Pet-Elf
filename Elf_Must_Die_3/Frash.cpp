#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::Frash()//刷新页面
{
    if(load_success==false){//未登录跳转到用户界面
        if(state_main!=PUSER)
            PageChange(PUSER);
    }
    switch(state_main){
    case PFIGHT:{//战斗界面
        if(count_special!=0)
            wait_count++;//等待用户阅读中
        if(wait_count>0)
            wait_count--;
        else{//自动战斗
            ShowState();
            if(battle_field.Fighting()==PFIGHTOVER)//自动战斗函数调用
                PageChange(PFIGHTOVER);
            ui->TextbrowserFElf1->setText(battle_field.elf1->ShowState());
            ui->TextbrowserFElf2->setText(battle_field.elf2->ShowState());
            int i=ui->ProgressBarFLife1->value()-battle_field.elf1->life;
            if(i>0)//判断谁掉血了
                battle_field.special_effects_flag=1;
            ui->ProgressBarFLife1->setValue(battle_field.elf1->life);
            i=ui->ProgressBarFLife2->value()-battle_field.elf2->life;
            if(i>0)
                battle_field.special_effects_flag=2;
            ui->ProgressBarFLife2->setValue(battle_field.elf2->life);
            //更新各种ui
            ui->labelFEle_retio->setText("元素之力:"+s.setNum(g_ele_ratio*100));
            if(battle_field.state_turn==1){//我方精灵行动中
                while(ui->ProgressBarFTurn1->value()<200){
                    ui->ProgressBarFTurn1->setValue(ui->ProgressBarFTurn1->value()+1);
                    if(ui->ProgressBarFTurn2->value()<battle_field.turn2)
                        ui->ProgressBarFTurn2->setValue(ui->ProgressBarFTurn2->value()+1);
                }
                ui->labelFTurn->setStyleSheet("QLabel{background-color :rgb(35, 123, 255)}");
                ui->labelFTurn->setText(battle_field.elf1->name+"发起进攻！");
                ui->ProgressBarFTurn1->setTextVisible(true);
                ui->ProgressBarFTurn2->setValue(battle_field.turn2);
            }
            else if(battle_field.state_turn==2){//敌方精灵行动中
                while(ui->ProgressBarFTurn2->value()<200){
                    ui->ProgressBarFTurn2->setValue(ui->ProgressBarFTurn2->value()+1);
                    if(ui->ProgressBarFTurn1->value()<battle_field.turn1)
                        ui->ProgressBarFTurn1->setValue(ui->ProgressBarFTurn1->value()+1);
                }
                ui->labelFTurn->setStyleSheet("QLabel{background-color :rgb(255, 83, 26)}");
                ui->labelFTurn->setText(battle_field.elf2->name+"发起进攻！");
                ui->ProgressBarFTurn1->setValue(battle_field.turn1);
                ui->ProgressBarFTurn2->setTextVisible(true);
            }
            else{//双方精灵准备中
                bool f1=true,f2=true;
                ui->labelFTurn->setStyleSheet("QLabel{background-color :rgb(224, 255, 164)}");
                ui->labelFTurn->setText("精灵准备中");
                ui->ProgressBarFTurn1->setTextVisible(false);
                ui->ProgressBarFTurn2->setTextVisible(false);

                if(ui->ProgressBarFTurn1->value()==200)
                    ui->ProgressBarFTurn1->setValue(0);
                if(ui->ProgressBarFTurn2->value()==200)
                    ui->ProgressBarFTurn2->setValue(0);

                while(f1||f2){//刷新进度条
                    if(ui->ProgressBarFTurn1->value()<battle_field.turn1){
                        ui->ProgressBarFTurn1->setValue(ui->ProgressBarFTurn1->value()+1);
                    }
                    else
                        f1=false;
                    if(ui->ProgressBarFTurn1->value()==200)
                        f1=false;
                    if(ui->ProgressBarFTurn2->value()<battle_field.turn2){
                        ui->ProgressBarFTurn2->setValue(ui->ProgressBarFTurn2->value()+1);
                    }
                    else
                        f2=false;
                    if(ui->ProgressBarFTurn2->value()==200)
                        f2=false;
                }
            }
            if(!g_message.isEmpty()){//有信息输出
                if(g_open_texiao==1)//弹窗特效
                    TeXiao1();
                wait_count=g_message.length()*1.5;//给用户阅读时间
                g_message.remove(0,1);
                ui->LabelFFight->setText(g_message);
                ui->TextbrowserFighting->append(g_message);
                g_message.clear();
                TeXiao2();//抖动特效
            }
        }
        break;
    }
    case PFIGHTOVER:{//战斗结束
        if(battle_field.winner>=0){
            ui->PushButtonFReturn->setEnabled(true);
            winner=battle_field.winner;
            battle_field.winner=-1;
            ui->labelFTurn->setText("战斗结束！");
            if(fight_mode==SHOULIE){//发送结果计算胜率
                if(winner==1){
                    SendTcp(QChar('V'));
                }
                else if(winner==2){
                    SendTcp(QChar('D'));
                }
            }
        }
        break;
    }
    case PUSER:{
        if(load_timer>0&&load_success==false){//计算是否连接超时
            load_timer--;
            if(load_timer==0)
                QMessageBox::critical(NULL,"错误","连接服务器失败！",QMessageBox::Ok);
        }
        break;
    }
    default:{
        break;
    }
    }
}

void MainWindow::PageChange(StateWindow new_state)//切换页面
{
    switch(new_state){
    case PMAIN:{//切换主界面
        ui->ButtonMYonghu->setText(master.name);
        ui->labelMElfName->setText(show_pet.name);
        ui->labelMElfTouxiang->setPixmap(show_pet.image);
        ui->labelMPetnum->setNum(master.count_pet);
        ui->LabelMTouxiang->setPixmap(master.head_picture);
        SendTcp(QChar('R'));
        state_main=PMAIN;

        ui->StackedWidgetQiehuan->setCurrentIndex(0);
        break;
    }
    case PUSER:{//切换用户界面
        InitTcp();
        state_main=PUSER;
        InitSpeed();
        load_timer=0;
        ui->StackedWidgetQiehuan->setCurrentIndex(1);
        break;
    }
    case PFIGHT:{//切换战斗界面
        state_main=PFIGHT;
        ui->StackedWidgetQiehuan->setCurrentIndex(2);
        break;
    }
    case PFIGHTOVER:{//切换战斗结束页面
        state_main=PFIGHTOVER;
        if(fight_mode==YANWU)
            ui->StackedWidgetQiehuan->setCurrentIndex(2);
        break;
    }
    case PYANWU:{//切换演武页面
        state_main=PYANWU;
        fight_mode=YANWU;
        InitYanwu();
        ui->StackedWidgetQiehuan->setCurrentIndex(3);
        break;
    }
    case PTOUXIANG:{//切换选择头像页面
        state_main=PTOUXIANG;
        ui->StackedWidgetQiehuan->setCurrentIndex(4);
        break;
    }
    case PCHONGWU:{//切换查看宠物页面
        state_main=PCHONGWU;
        InitChongwu();
        ui->StackedWidgetQiehuan->setCurrentIndex(5);
        break;
    }
    case POTHERUSER:{//切换查看所有用户页面
        state_main=POTHERUSER;
        ui->StackedWidgetQiehuan->setCurrentIndex(6);
        break;
    }
    case PSHOULIE:{//切换狩猎界面
        state_main=PSHOULIE;
        fight_mode=SHOULIE;
        ui->StackedWidgetQiehuan->setCurrentIndex(7);
        break;
    }
    case PJVEDOU:{//切换决斗界面
        state_main=PJVEDOU;
        fight_mode=JVEDOU;
        ui->StackedWidgetQiehuan->setCurrentIndex(7);
        break;
    }
    }
    flag_back=true;
    update();
}

void MainWindow::paintEvent(QPaintEvent *event)//根据页面绘制不同背景
{
    QPainter painter(this);
    if(flag_back){
    switch(state_main){
    case PMAIN:{
        pixmap = QPixmap(g_background+"背景3").scaled(this->size());
        break;
    }
    case PUSER:{
        pixmap = QPixmap(g_background+"背景4").scaled(this->size());
        break;
    }
    case PFIGHT:{
        pixmap = QPixmap(g_background+"战斗1").scaled(this->size());
        break;
    }
    case PFIGHTOVER:{
        break;
    }
    case PYANWU:{
        pixmap = QPixmap(g_background+"战斗2").scaled(this->size());
        break;
    }
    case PTOUXIANG:{
        pixmap = QPixmap(g_background+"背景4").scaled(this->size());
        break;
    }
    case PCHONGWU:{
        pixmap = QPixmap(g_background+"背景2").scaled(this->size());
        break;
    }
    case POTHERUSER:{
        pixmap = QPixmap(g_background+"背景1").scaled(this->size());
        break;
    }
    case PSHOULIE:{
        pixmap = QPixmap(g_background+"战斗2").scaled(this->size());
        break;
    }
    case PJVEDOU:{
        pixmap = QPixmap(g_background+"战斗2").scaled(this->size());
        break;
    }
    }
    painter.drawPixmap(this->rect(), pixmap);
    flag_back=false;
    }
    else
        painter.drawPixmap(this->rect(), pixmap);
}



