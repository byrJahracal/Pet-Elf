#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::InitChongwu()//初始化宠物界面
{
    flag_chongwu=false;
    ui->comboBoxCChooseelf->clear();
    ui->comboBoxCChooseelf->setCurrentIndex(-1);
    for(int i=0;i<ALLPET;i++){//把用户拥有的精灵都加进去
        if(master.my_pet[i]){
            ui->comboBoxCChooseelf->addItem(g_Name[master.my_pet[i]->own_elf.your_elf]);
        }
    }
    ui->comboBoxCChooseelf->setCurrentIndex(-1);
    flag_chongwu=true;
    ui->comboBoxCChooseelf->setCurrentIndex(0);
}

void MainWindow::InitLearnedSkill(){//初始化show_pet的技能
    flag_chongwu=false;
    ui->comboBoxCSkill1->clear();
    if(show_pet.skill1==UNLOCKED){//一技能还没学习
        for(int i=LEAF_ATTACK;i<ALLSKILL;i++){
            if(master.my_skill[i]&&master.my_skill[i]->learn_remain>0){
                ui->comboBoxCSkill1->addItem(g_Str_skill[i]);
            }
        }
        if(ui->comboBoxCSkill1->count()==0){
            ui->comboBoxCSkill1->addItem("没有可学习的技能！");
            ui->comboBoxCSkill1->setCurrentIndex(0);
            ui->comboBoxCSkill1->setEnabled(false);
        }
        else{
            ui->comboBoxCSkill1->addItem(g_Str_skill[UNLOCKED]);
            ui->comboBoxCSkill1->setCurrentText(g_Str_skill[show_pet.skill1]);
            ui->comboBoxCSkill1->setEnabled(true);
        }
    }
    else if(show_pet.level>=TAL_2){//等级达到TAL_2将不能随意更改技能
        ui->comboBoxCSkill1->addItem(g_Str_skill[show_pet.skill1]);
        ui->comboBoxCSkill1->setCurrentIndex(0);
        ui->comboBoxCSkill1->setEnabled(true);
    }
    else{//等级较低时可以随意修改技能
        ui->comboBoxCSkill1->setCurrentIndex(-1);
        for(int i=LEAF_ATTACK;i<ALLSKILL;i++){
            if(master.my_skill[i]){
                if(master.my_skill[i]->learn_remain>0||show_pet.skill1==master.my_skill[i]->own_skill){
                    ui->comboBoxCSkill1->addItem(g_Str_skill[i]);
                }
            }
        }
        ui->comboBoxCSkill1->addItem(g_Str_skill[UNLOCKED]);
        ui->comboBoxCSkill1->setCurrentText(g_Str_skill[show_pet.skill1]);
        ui->comboBoxCSkill1->setEnabled(true);
    }

    ui->comboBoxCSkill2->clear();
    if(show_pet.skill2==UNLOCKED){//二技能还没学习
        for(int i=LEAF_ATTACK;i<ALLSKILL;i++){
            if(master.my_skill[i]&&master.my_skill[i]->learn_remain>0){
                ui->comboBoxCSkill2->addItem(g_Str_skill[i]);
            }
        }
        if(ui->comboBoxCSkill2->count()==0){
            ui->comboBoxCSkill2->addItem("没有可学习的技能！");
            ui->comboBoxCSkill2->setCurrentIndex(0);
            ui->comboBoxCSkill2->setEnabled(false);
        }
        else{
            ui->comboBoxCSkill2->addItem(g_Str_skill[UNLOCKED]);
            ui->comboBoxCSkill2->setCurrentText(g_Str_skill[show_pet.skill2]);
            ui->comboBoxCSkill2->setEnabled(true);
        }
    }
    else if(show_pet.skill2==LOCKED){//二技能未解锁
        ui->comboBoxCSkill2->addItem(g_Str_skill[LOCKED]);
        ui->comboBoxCSkill2->setCurrentIndex(0);
        ui->comboBoxCSkill2->setEnabled(false);
    }
    else if(show_pet.level>=TAL_2){//等级达到TAL_2将不能随意更改技能
        ui->comboBoxCSkill2->addItem(g_Str_skill[show_pet.skill2]);
        ui->comboBoxCSkill2->setCurrentIndex(0);
        ui->comboBoxCSkill2->setEnabled(true);
    }
    else{//等级较低时可以随意修改技能
        ui->comboBoxCSkill2->setCurrentIndex(-1);
        for(int i=LEAF_ATTACK;i<ALLSKILL;i++){
            if(master.my_skill[i]){
                if(master.my_skill[i]->learn_remain>0||show_pet.skill2==master.my_skill[i]->own_skill){
                    ui->comboBoxCSkill2->addItem(g_Str_skill[i]);
                }
            }
        }
        ui->comboBoxCSkill2->addItem(g_Str_skill[UNLOCKED]);
        ui->comboBoxCSkill2->setCurrentText(g_Str_skill[show_pet.skill2]);
        ui->comboBoxCSkill2->setEnabled(true);
    }
    ui->labelCRemainskill->setNum(show_pet.up_skill);
    ui->labelCSkill1level->setNum(show_pet.sk1_level);
    ui->labelCSkill2Level->setNum(show_pet.sk2_level);
    flag_chongwu=true;
    ui->textBrowserCSkill1Jieshao->setText(g_Intro_Skill[show_pet.skill1]);
    ui->textBrowserCSkill2Jieshao->setText(g_Intro_Skill[show_pet.skill2]);
}

void MainWindow::ShowElf()//在宠物界面显示该宠物的信息
{
    int i=show_pet.pet_num;
    ui->labelCTouxiang->setPixmap(show_pet.image);
    ui->labelCExperience->setNum(show_pet.experience);
    ui->labelCLevel->setNum(show_pet.level);
    ui->labelCTalent->setText(g_Str_talent[i]);
    ui->labelCTalentLevel->setNum(show_pet.tal_level);

    ui->textBrowserCJieshao->setText(g_Intro_Elf[i]);
    ui->textBrowserCShuxin->setText(show_pet.ShowAttributes());
    ui->textBrowserCTalentJieshao->setText(g_Str_talent[i]);
    ui->textBrowserCTalentJieshao->append(g_Intro_Talent[i]);
}



