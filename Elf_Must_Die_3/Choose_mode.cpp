#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::InitYanwu()//初始化演武战斗，本地的虚拟对战
{
    flag_chongwu=false;//禁止切换精灵槽函数触发
    ui->ComboBoxYWofang->clear();
    ui->ComboBoxYDifang->clear();
    for(int i=0;i<ALLPET;i++){
        if(master.my_pet[i]!=NULL){
            ui->ComboBoxYWofang->addItem(g_Name[i]);
            ui->ComboBoxYDifang->addItem(g_Name[i]);
        }
    }
    ui->ComboBoxYWofang->setCurrentIndex(-1);
    ui->ComboBoxYDifang->setCurrentIndex(-1);
    ui->comboBoxYWoLevel->setCurrentIndex(0);
    ui->comboBoxYDiLevel->setCurrentIndex(0);
    flag_chongwu=true;//初始化之后可以切换精灵
    ui->ComboBoxYWofang->setCurrentIndex(0);
    ui->ComboBoxYDifang->setCurrentIndex(0);
}

void MainWindow::InitShoulie()//初始化狩猎战斗，升级赛
{
    flag_chongwu=false;
    ui->ComboBoxSWofang->clear();
    ui->ComboBoxSDifang->clear();
    for(int i=0;i<ALLPET;i++){
        if(master.my_pet[i]!=NULL){
            ui->ComboBoxSWofang->addItem(g_Name[i]);
        }
    }
    for(int i=0;i<3;i++){
        ui->ComboBoxSDifang->addItem(g_Name[enemy[i].your_elf]);
    }
    ui->ComboBoxSWofang->setCurrentIndex(-1);
    ui->ComboBoxSDifang->setCurrentIndex(-1);
    ui->comboBoxSWoLevel->setCurrentIndex(0);
    ui->comboBoxSDiLevel->setCurrentIndex(0);
    ui->labelShoulie->setText("狩\n猎");//设置各种ui
    ui->pushButtonSSend->hide();
    ui->buttonBoxShoulie->show();
    ui->comboBoxSDiLevel->setEnabled(true);
    ui->FrameSEnemy->show();
    flag_chongwu=true;
    ui->ComboBoxSDifang->setCurrentIndex(0);
    ui->ComboBoxSWofang->setCurrentIndex(0);
    ui->comboBoxSDiLevel->setCurrentIndex(show_pet_wo.level-1);
    ui->labelSShuoming->setText("精灵总部给你发了3个被通缉的精灵，你可以派你的任意一个宠物去狩猎。当然精灵总部并不知道这些精灵是多少级，你可以随意挑选。狩猎胜利后你的精灵会获得一定的经验。");
}

void MainWindow::InitJvedou()//初始化决斗战斗，决斗赛
{
    flag_chongwu=false;
    ui->ComboBoxSWofang->clear();
    ui->ComboBoxSDifang->clear();
    for(int i=0;i<ALLPET;i++){
        if(master.my_pet[i]!=NULL){
            ui->ComboBoxSWofang->addItem(g_Name[i]);
        }
    }
    for(int i=0;i<3;i++){
        ui->ComboBoxSDifang->addItem(g_Name[enemy[i].your_elf]);
    }
    ui->ComboBoxSWofang->setCurrentIndex(-1);
    ui->ComboBoxSDifang->setCurrentIndex(-1);
    ui->comboBoxSWoLevel->setCurrentIndex(0);
    ui->comboBoxSDiLevel->setCurrentIndex(0);
    ui->labelShoulie->setText("决\n斗");
    ui->pushButtonSSend->hide();
    ui->buttonBoxShoulie->show();
    ui->comboBoxSDiLevel->setEnabled(false);
    ui->FrameSEnemy->show();
    flag_chongwu=true;
    ui->ComboBoxSDifang->setCurrentIndex(0);
    ui->ComboBoxSWofang->setCurrentIndex(0);
    ui->comboBoxSDiLevel->setCurrentIndex(show_pet_wo.level-1);
    ui->labelSShuoming->setText("决斗是实力的象征。精灵总部给你分配了三个强大的对手，战胜其中任意一个你将获得该精灵，若你已拥有该精灵，你将随机获得一个该精灵的技能，若你已拥有该技能，你将获得额外经验。但是，若你没能战胜对手，你必须从自己的三个精灵中挑选一个上交精灵总部。");
}

void MainWindow::JveDouPower()//决斗赛敌人小小加强
{
    if(show_pet_di.level<15)//满级前直接高一级
        show_pet_di.UpGrade(show_pet_di.level+1);
    else{
        show_pet_di.life+=100;
        show_pet_di.agility+=2;
        show_pet_di.power+=10;
        show_pet_di.defence+=10;
    }
}

void MainWindow::UpLevel()//获取经验
{
    int ex=50;
    int i=show_pet_di.level-show_pet_wo.level;
    if(i==0){
        ex+=30;
    }
    else if(i>0){//战胜比自己等级高的敌人获得更多经验
        ex+=50;
    }
    ex+=i*10;
    if(show_pet_di.skill2==LOCKED)
        ex/=2;
    if(ex<=1)
        ex=1;
    if(fight_mode==JVEDOU)//决斗双倍经验
        show_pet_wo.experience+=ex;
    show_pet_wo.experience+=ex;
    show_pet_wo.UpGrade();//自动升级
    master.my_pet[show_pet_wo.pet_num]->own_elf.experience=show_pet_wo.experience;
    master.my_pet[show_pet_wo.pet_num]->own_elf.l=show_pet_wo.level;
    s=QString("恭喜你获得胜利！%1获得%2点经验。\n宠物等级为%3，宠物经验为%4！")
            .arg(g_Name[show_pet_wo.pet_num]).arg(ex)
            .arg(show_pet_wo.level).arg(show_pet_wo.experience);
    SendTcp(QChar('U'));//汇报服务器升级情况
    QMessageBox::information(NULL,"提示",s,QMessageBox::Ok);
}

void MainWindow::GetMore()//决斗胜利获得宠物，技能。经验
{
    int i=show_pet_di.pet_num;
    if(master.my_pet[i]==NULL){//没有该宠物获得该宠物
        new_pet.own_elf={
            (PetNumber)i,UNLOCKED,LOCKED,show_pet_di.level/2,1,1,0
        };
        master.Deal(new_pet);
        SendTcp(QChar('G'),1);//Get新宠物
        s=QString("恭喜你获得新的精灵："+g_Name[i]+"!");
        QMessageBox::information(NULL,"提示",s,QMessageBox::Ok);
    }
    else {
        i=RANDOM(2);
        SkillType k;
        if(i==1){
            k=show_pet_di.skill1;
        }
        else if(i==2){
            k=show_pet_di.skill2;
        }
        if(master.my_skill[k]==NULL){//已经拥有该宠物，获得新技能
            new_skill.learn_remain=SKILLREMAIN;
            new_skill.own_skill=k;
            master.Deal(new_skill);
            SendTcp(QChar('G'),2);//Get新技能
            s=QString("恭喜你获得新的技能："+g_Str_skill[k]+"!");
            QMessageBox::information(NULL,"提示",s,QMessageBox::Ok);
        }
        else{//该技能也有了，获得额外经验
            show_pet_wo.experience+=100;
            show_pet_wo.UpGrade();
            master.my_pet[show_pet_wo.pet_num]->own_elf.experience=show_pet_wo.experience;
            master.my_pet[show_pet_wo.pet_num]->own_elf.l=show_pet_wo.level;
            s=QString("恭喜你的宠物%1获得额外100点经验！").arg(show_pet_wo.name);
            SendTcp(QChar('G'),3);//Get额外经验
            QMessageBox::information(NULL,"提示",s,QMessageBox::Ok);
        }
    }
}

void MainWindow::Failed()//决斗失败送出宠物
{
    flag_chongwu=false;
    ui->ComboBoxSWofang->clear();
    if(master.count_pet<=3){//宠物数量小于三个全部出列
        for(int i=0;i<ALLPET;i++){
            if(master.my_pet[i]!=NULL){
                ui->ComboBoxSWofang->addItem(g_Name[i]);
            }
        }
    }
    else{
        int count1,count2,count3;
        count1=RANDOM(ALLPET)-1;
        while(master.my_pet[count1]==NULL){
            count1=(count1+1)%ALLPET;
        }
        count2=RANDOM(ALLPET)-1;
        while(master.my_pet[count2]==NULL||count2==count1){
            count2=(count2+1)%ALLPET;
        }
        count3=RANDOM(ALLPET)-1;
        while(master.my_pet[count3]==NULL||count3==count2||count3==count1){
            count3=(count3+1)%ALLPET;
        }//随机选了三个精灵
        ui->ComboBoxSWofang->addItem(g_Name[count1]);
        ui->ComboBoxSWofang->addItem(g_Name[count2]);
        ui->ComboBoxSWofang->addItem(g_Name[count3]);
    }

    ui->ComboBoxSWofang->setCurrentIndex(-1);
    ui->comboBoxSWoLevel->setCurrentIndex(0);
    ui->labelShoulie->setText("败\n北");
    ui->pushButtonSSend->show();
    ui->buttonBoxShoulie->hide();
    ui->FrameSEnemy->hide();
    flag_chongwu=true;
    ui->ComboBoxSWofang->setCurrentIndex(0);
    s="决斗失败后，精灵总部会从你的精灵中任意挑选三个，你将决定送走其中的一个精灵。";
    ui->labelSShuoming->setText(s);
    QMessageBox::information(NULL,"提示",s,QMessageBox::Ok);
}


