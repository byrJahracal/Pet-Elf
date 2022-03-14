#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::PrepareToFight()//准备战斗
{
    g_ele_ratio=(RANDOM(100))/100.0;
    battle_field.ChooseElf(1,show_pet_wo);
    battle_field.ChooseElf(2,show_pet_di);//初始化战斗双方的精灵
    battle_field.Prepare();//战场自动机准备
    switch (fight_mode){
    case SHOULIE:{
        ui->LabelFMode->setText("狩猎");
        break;
    }
    case YANWU:{
        ui->LabelFMode->setText("演武");
        break;
    }
    case JVEDOU:{
        ui->LabelFMode->setText("决斗");
        break;
    }
    }//显示战斗模式
    ui->LabelFSpeed->setNum(speed_fight);
    ui->labelFName1->setText(battle_field.elf1->name);
    ui->labelFName2->setText(battle_field.elf2->name);
    ui->labelFTou1->setPixmap(master.head_picture);
    int i=RANDOM(8);
    s.setNum(i);
    ui->labelFTou2->setPixmap(QPixmap(g_touxiang_user+s));
    ui->labelFUser1->setText(master.name);
    ui->labelFPicture1->setPixmap(battle_field.elf1->image);
    ui->labelFPicture2->setPixmap(battle_field.elf2->image);
    ui->labelFUser2->setText("Enemy");
    ui->ProgressBarFLife1->setMaximum(battle_field.elf1->life);
    ui->ProgressBarFLife2->setMaximum(battle_field.elf2->life);
    ui->LabelFFight->clear();
    ui->TextbrowserFighting->clear();
    ui->PushButtonFReturn->setEnabled(false);//ui各种显示
    ui->PushButtonFReturn->setText("返回");
    battle_field.turn1=0;
    battle_field.turn2=0;
    battle_field.special_effects_flag=0;//特效初始化
    teword->show();

    SetSpeed();//初始化播放速度
    PageChange(PFIGHT);//切换界面
}

void MainWindow::TeXiao1()//判断特效是否释放
{
    if(battle_field.special_effects_skill!=TOPAN){//战场中发生了特效
        if(battle_field.attack1.special_effects>=0||battle_field.attack2.special_effects>=0){
            count_special=1;
            TeXiaoBack();//调用特效
            battle_field.attack2.special_effects=-1;
            battle_field.attack1.special_effects=-1;
            battle_field.special_effects_flag=0;
        }
    }
}

void MainWindow::TeXiao2()//抖动特效判定
{
    if(count_special==0){
        if(battle_field.special_effects_flag==1){
            TeXiaoLabel(1);//精灵1抖动
            battle_field.special_effects_flag=0;
        }
        else if(battle_field.special_effects_flag==2){
            TeXiaoLabel(2);//精灵2抖动
            battle_field.special_effects_flag=0;
        }
    }
}

void MainWindow::TeXiaoBack()
{
    int ele;
    int x=this->width();
    int y=this->height();

    back->move(-x,0);

    pAnimation1 = new QPropertyAnimation(back,"geometry",this);//设置动画
    if(battle_field.state_turn==1){//我方回合
        if(battle_field.head_period==1||battle_field.head_period==3){//我自己放技能
            if(battle_field.special_effects_skill==TOTAL||battle_field.special_effects_skill==TOATT)
                battle_field.special_effects_str=g_Str_talent[battle_field.elf1->pet_num];
            else if(battle_field.special_effects_skill==TOSK1)
                battle_field.special_effects_str=g_Str_skill[battle_field.elf1->skill1];
            else if(battle_field.special_effects_skill==TOSK2)
                battle_field.special_effects_str=g_Str_skill[battle_field.elf1->skill2];
            ele=battle_field.attack1.special_effects;
            back->setPixmap(QPixmap(g_background+g_Str_element[ele]));
            pAnimation1->setStartValue(QRect(-x, 0, x, y));
            pAnimation1->setEndValue(QRect(0, 0, x, y));
        }
        else{//敌人放被动技能
            if(battle_field.elf2->judge_time[TALENT]==INJURED)
                battle_field.special_effects_str=g_Str_talent[battle_field.elf2->pet_num];
            else if(battle_field.elf2->judge_time[SKILL1]==INJURED)
                battle_field.special_effects_str=g_Str_skill[battle_field.elf2->skill1];
            else if(battle_field.elf2->judge_time[SKILL2]==INJURED)
                battle_field.special_effects_str=g_Str_skill[battle_field.elf2->skill2];
            ele=battle_field.attack2.special_effects;
            back->setPixmap(QPixmap(g_background2+g_Str_element[ele]));
            pAnimation1->setStartValue(QRect(x, 0, x, y));
            pAnimation1->setEndValue(QRect(0, 0, x, y));
        }
    }
    else if(battle_field.state_turn==2){//敌人回合
        if(battle_field.head_period==1||battle_field.head_period==3){//敌人放技能
            if(battle_field.special_effects_skill==TOTAL||battle_field.special_effects_skill==TOATT)
                battle_field.special_effects_str=g_Str_talent[battle_field.elf2->pet_num];
            else if(battle_field.special_effects_skill==TOSK1)
                battle_field.special_effects_str=g_Str_skill[battle_field.elf2->skill1];
            else if(battle_field.special_effects_skill==TOSK2)
                battle_field.special_effects_str=g_Str_skill[battle_field.elf2->skill2];
            ele=battle_field.attack2.special_effects;
            back->setPixmap(QPixmap(g_background2+g_Str_element[ele]));
            pAnimation1->setStartValue(QRect(x, 0, x, y));
            pAnimation1->setEndValue(QRect(0, 0, x, y));
        }
        else{//我方放被动技能
            if(battle_field.elf1->judge_time[TALENT]==INJURED)
                battle_field.special_effects_str=g_Str_talent[battle_field.elf1->pet_num];
            else if(battle_field.elf1->judge_time[SKILL1]==INJURED)
                battle_field.special_effects_str=g_Str_skill[battle_field.elf1->skill1];
            else if(battle_field.elf1->judge_time[SKILL2]==INJURED)
                battle_field.special_effects_str=g_Str_skill[battle_field.elf1->skill2];
            ele=battle_field.attack1.special_effects;
            back->setPixmap(QPixmap(g_background+g_Str_element[ele]));
            pAnimation1->setStartValue(QRect(-x, 0, x, y));
            pAnimation1->setEndValue(QRect(0, 0, x, y));
        }
    }
    switch(ele){//特效背景颜色
    case LEAF:{
        battle_field.s="green";
        break;
    }
    case FLAME:{
        battle_field.s="red";
        break;
    }
    case THUNDER:{
        battle_field.s="yellow";
        break;
    }
    case ICE:{
        battle_field.s="blue";
        break;
    }
    case DARK:{
        battle_field.s="rgb(122, 3, 195)";
        break;
    }
    }
    s=QString("QLabel{color: %1;"
              "background: transparent;"
              "font: 32pt \"华文行楷\";}").arg(battle_field.s);
    teword->setStyleSheet(s);
    teword->move(x/2-64,y/4);

    pAnimation1->setDuration(1500-speed_fight*2);//设置特效速度
    pAnimation1->setEasingCurve(QEasingCurve::OutQuint);

    back->show();
    special_timer->start(1500-speed_fight*2);//特效定时清除
    pAnimation1->start(QAbstractAnimation::DeleteWhenStopped);
}

void MainWindow::ShowState()//展示宠物状态
{
    int j=1;
    ui->label1state1->clear();
    ui->label1state2->clear();
    ui->label1state3->clear();
    ui->label1state4->clear();
    ui->label1state5->clear();
    ui->label1state6->clear();
    ui->label1state7->clear();
    ui->label1state8->clear();
    for(int i=0;i<ALLSTATE&&j<9;i++){
        if(battle_field.elf1->state_fighting[i][2]>0){
            switch (j) {
            case 1:{
                ui->label1state1->setText(g_Str_state[i]);
                break;
            }
            case 2:{
                ui->label1state2->setText(g_Str_state[i]);
                break;
            }
            case 3:{
                ui->label1state3->setText(g_Str_state[i]);
                break;
            }
            case 4:{
                ui->label1state4->setText(g_Str_state[i]);
                break;
            }
            case 5:{
                ui->label1state5->setText(g_Str_state[i]);
                break;
            }
            case 6:{
                ui->label1state6->setText(g_Str_state[i]);
                break;
            }
            case 7:{
                ui->label1state7->setText(g_Str_state[i]);
                break;
            }
            case 8:{
                ui->label1state8->setText(g_Str_state[i]);
                break;
            }
            }
            j++;
        }
    }
    j=1;
    ui->label2state1->clear();
    ui->label2state2->clear();
    ui->label2state3->clear();
    ui->label2state4->clear();
    ui->label2state5->clear();
    ui->label2state6->clear();
    ui->label2state7->clear();
    ui->label2state8->clear();
    for(int i=0;i<ALLSTATE&&j<9;i++){
        if(battle_field.elf2->state_fighting[i][2]>0){
            switch (j) {
            case 1:{
                ui->label2state1->setText(g_Str_state[i]);
                break;
            }
            case 2:{
                ui->label2state2->setText(g_Str_state[i]);
                break;
            }
            case 3:{
                ui->label2state3->setText(g_Str_state[i]);
                break;
            }
            case 4:{
                ui->label2state4->setText(g_Str_state[i]);
                break;
            }
            case 5:{
                ui->label2state5->setText(g_Str_state[i]);
                break;
            }
            case 6:{
                ui->label2state6->setText(g_Str_state[i]);
                break;
            }
            case 7:{
                ui->label2state7->setText(g_Str_state[i]);
                break;
            }
            case 8:{
                ui->label2state8->setText(g_Str_state[i]);
                break;
            }
            }
            j++;
        }
    }
}

void MainWindow::TeXiaoLabel(int dir)//抖动特效，dir为1是我方，2是敌方
{
    int x,y;
    if(dir==1){
        x=ui->labelFPicture1->pos().x();
        y=ui->labelFPicture1->pos().y();
        pAnimation1 = new QPropertyAnimation(ui->labelFPicture1,"pos",this);
    }
    else{
        x=ui->labelFPicture2->pos().x();
        y=ui->labelFPicture2->pos().y();
        pAnimation1 = new QPropertyAnimation(ui->labelFPicture2,"pos",this);
    }
    pAnimation1->setDuration(550-speed_fight);
    pAnimation1->setLoopCount(2);
    pAnimation1->setKeyValueAt(0, QPoint(x - 3, y - 3));
    pAnimation1->setKeyValueAt(0.1, QPoint(x + 6, y + 6));
    pAnimation1->setKeyValueAt(0.2, QPoint(x - 6, y + 6));
    pAnimation1->setKeyValueAt(0.3, QPoint(x + 6, y - 6));
    pAnimation1->setKeyValueAt(0.4, QPoint(x - 6, y - 6));
    pAnimation1->setKeyValueAt(0.5, QPoint(x + 6, y + 6));
    pAnimation1->setKeyValueAt(0.6, QPoint(x - 6, y + 6));
    pAnimation1->setKeyValueAt(0.7, QPoint(x + 6, y - 6));
    pAnimation1->setKeyValueAt(0.8, QPoint(x - 6, y - 6));
    pAnimation1->setKeyValueAt(0.9, QPoint(x + 6, y + 6));
    pAnimation1->setKeyValueAt(1, QPoint(x - 3, y - 3));
    pAnimation1->start(QAbstractAnimation::DeleteWhenStopped);
    count_special=3;
    special_timer->start(1100-speed_fight*2);
}

void MainWindow::OverTexiao()//特效结束
{
    if(count_special==1){//弹窗特效
        count_special=2;
        teword->setText(battle_field.special_effects_str);
        teword->adjustSize();
        pAnimation2 = new QPropertyAnimation(teword,"windowOpacity",this);//开启二段特效
        pAnimation2->setDuration(1500-speed_fight*2);
        pAnimation2->setKeyValueAt(0, 1);
        pAnimation2->setKeyValueAt(0.5, 0);
        pAnimation2->setKeyValueAt(1, 1);
        pAnimation2->start(QAbstractAnimation::DeleteWhenStopped);
    }
    else if(count_special==2){//弹窗特效后显示文字结束
        teword->clear();
        back->hide();
        count_special=0;
        special_timer->stop();
    }
    else if(count_special==3){//抖动结束
        count_special=0;
        special_timer->stop();
    }
}


