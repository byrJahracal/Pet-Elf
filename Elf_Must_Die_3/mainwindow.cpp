#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    srand((unsigned)time(NULL));
    InitData();//初始化精灵数据
    InitOther();//程序初始化
    PageChange(PUSER);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::test()
{

}

void MainWindow::on_ButtonMYonghu_clicked()//用户按钮切换界面
{
    ui->labelUTouxiang->setPixmap(master.head_picture);
    ui->labelUName->setText(master.name);
    PageChange(PUSER);
}

void MainWindow::on_ButtonMYanwu_clicked()//演武按钮
{
    PageChange(PYANWU);
}

void MainWindow::on_PushButtonFReturn_clicked()//战斗结束返回按钮
{
    teword->hide();
    if(fight_mode==YANWU)//演武结束
        PageChange(PYANWU);
    else if(fight_mode==SHOULIE){//狩猎结束
        ui->PushButtonFReturn->setText("与精灵总部联络中...");
        ui->PushButtonFReturn->setEnabled(false);
        if(winner==1){
            UpLevel();
        }
        else{
            QMessageBox::information(NULL,"提示","很遗憾，你的精灵没能战胜对手！",QMessageBox::Ok);
            PageChange(PSHOULIE);
        }
    }
    else if(fight_mode==JVEDOU){//决斗结束
        ui->PushButtonFReturn->setText("与精灵总部联络中...");
        ui->PushButtonFReturn->setEnabled(false);
        if(winner==1){
            UpLevel();
            GetMore();
            PageChange(PMAIN);
        }
        else{
            QMessageBox::information(NULL,"提示","很遗憾，你的精灵没能战胜对手！",QMessageBox::Ok);
            Failed();
            PageChange(PJVEDOU);
            fight_mode=YANWU;
        }
    }
    InitSpeed();
}

void MainWindow::on_PushButtonFJIasu_clicked()//加快战斗速度
{
    JiaSpeed();
    ui->LabelFSpeed->setNum(speed);
}

void MainWindow::on_PushButtonFJiansu_clicked()//减慢战斗速度
{
    JianSpeed();
    ui->LabelFSpeed->setNum(speed);
}

void MainWindow::on_pushButtonULoad_clicked()//按下登陆按钮
{
    if(!(ui->lineEditUNameOld->text().isEmpty())){
        if(!(ui->lineEditUMimaOld->text().isEmpty())){//用户名密码不能为空
            InitTcp();
            new_user.name=ui->lineEditUNameOld->text();
            new_user.password=ui->lineEditUMimaOld->text();
            SendTcp(QChar('O'));//发送老用户登录消息
            load_timer=30;
        }
    }
}

void MainWindow::on_pushButtonYnew_clicked()//创建新用户
{
    if(!(ui->lineEditUNameNew->text().isEmpty())){
        if(!(ui->lineEditUMimaNew->text().isEmpty())){//用户名密码不能为空
            InitTcp();
            new_user.name=ui->lineEditUNameNew->text();
            new_user.password=ui->lineEditUMimaNew->text();
            new_user.head_number=master.head_number;
            SendTcp(QChar('N'));//发送创建新用户消息
            load_timer=30;
        }
    }
}

void MainWindow::on_pushButtonUTou_clicked()//选择自定义头像
{
    PageChange(PTOUXIANG);
}

void MainWindow::on_buttonBoxTouxiang_clicked(QAbstractButton *button)
{
    if(button==ui->buttonBoxTouxiang->button(QDialogButtonBox::Ok)){//确定选择头像
        master.head_number=ui->listWidgetTouxiang->currentRow()+1;
        master.ChangeTouxiang();
        SendTcp(QChar('T'));
        ui->LabelMTouxiang->setPixmap(master.head_picture);
        ui->labelUTouxiang->setPixmap(master.head_picture);
        PageChange(PUSER);
    }
    else//取消选择
        PageChange(PUSER);
}

void MainWindow::on_pushButtonMGengxing_clicked()
{
    SendTcp(QChar('R'));//请求更新在线列表
    ui->listWidgetMWorld->setCurrentRow(-1);
}

void MainWindow::on_comboBoxCChooseelf_currentIndexChanged(const QString &arg1)
{//宠物界面显示宠物切换
    if(flag_chongwu){
        if(ui->comboBoxCChooseelf->currentIndex()>=0){
            for(int i=0;i<ALLPET;i++){
                if(g_Name[i]==arg1){
                    new_pet.own_elf=master.my_pet[i]->own_elf;
                    break;
                }
            }
            show_pet.SetValue(new_pet.own_elf);
            ShowElf();//更新显示
            InitLearnedSkill();//更新技能显示
        }
    }
}

void MainWindow::on_comboBoxCSkill1_currentIndexChanged(const QString &arg1)
{//刷新用户拥有的技能1
    if(flag_chongwu==true){
    int i;
    for(i=0;i<ALLSKILL;i++){
        if(g_Str_skill[i]==arg1){
            break;
        }
    }
    ui->textBrowserCSkill1Jieshao->setText(g_Intro_Skill[i]);
    }
}

void MainWindow::on_comboBoxCSkill2_currentIndexChanged(const QString &arg1)
{//刷新用户拥有的技能2
    if(flag_chongwu==true){
    int i;
    for(i=0;i<ALLSKILL;i++){
        if(g_Str_skill[i]==arg1){
            break;
        }
    }
    ui->textBrowserCSkill2Jieshao->setText(g_Intro_Skill[i]);
    }
}

void MainWindow::on_pushButtonMChongwu_clicked()
{//切换到宠物界面
    if(load_success){
        InitChongwu();
        PageChange(PCHONGWU);
    }
    else
        QMessageBox::information(NULL,"提示","请先登录再查看宠物！",QMessageBox::Ok);
}

void MainWindow::on_pushButtonCSkill1Learn_clicked()
{//学习1技能按钮
    if(ui->comboBoxCSkill1->currentIndex()>=0){
        s=ui->comboBoxCSkill1->currentText();
        bool flag=false;
        SkillType skill;
        for(int i=0;i<ALLSKILL;i++){
            if(g_Str_skill[i]==s){
                flag=true;
                skill=(SkillType)i;
            }
        }
        if(flag){
            if(skill==UNLOCKED){//遗忘技能
                master.Forget(show_pet.pet_num,1);
                show_pet.SetValue(master.my_pet[show_pet.pet_num]->own_elf);

                new_pet.SetValue(show_pet);
                SendTcp(QChar('P'));
                InitLearnedSkill();
                QMessageBox::information(NULL,"提示","遗忘技能成功！",QMessageBox::Ok);
            }
            else if(skill!=LOCKED){
                if(skill!=master.my_pet[show_pet.pet_num]->own_elf.s2){
                    if(skill!=master.my_pet[show_pet.pet_num]->own_elf.s1){
                        master.Distribute(show_pet.pet_num,skill,1);
                        show_pet.SetValue(master.my_pet[show_pet.pet_num]->own_elf);

                        new_pet.SetValue(show_pet);
                        SendTcp(QChar('P'));//向服务器报告
                        InitLearnedSkill();
                        QMessageBox::information(NULL,"提示","技能学习成功！",QMessageBox::Ok);
                    }
                }
                else//同一个精灵不能重复学习
                    QMessageBox::critical(NULL,"错误","同一个精灵不能学习重复的技能！",QMessageBox::Ok);
            }
        }
    }
}

void MainWindow::on_pushButtonCSkill2Learn_clicked()
{//学习2技能
    if(ui->comboBoxCSkill2->currentIndex()>=0){
        s=ui->comboBoxCSkill2->currentText();
        bool flag=false;
        SkillType skill;
        for(int i=0;i<ALLSKILL;i++){
            if(g_Str_skill[i]==s){
                flag=true;
                skill=(SkillType)i;
            }
        }
        if(flag){
            if(skill==UNLOCKED){//遗忘技能
                master.Forget(show_pet.pet_num,2);
                show_pet.SetValue(master.my_pet[show_pet.pet_num]->own_elf);

                new_pet.SetValue(show_pet);
                SendTcp(QChar('P'));
                InitLearnedSkill();
                QMessageBox::information(NULL,"提示","遗忘技能成功！",QMessageBox::Ok);
            }
            else if(skill!=LOCKED){//学习技能
                if(skill!=master.my_pet[show_pet.pet_num]->own_elf.s1){
                    if(skill!=master.my_pet[show_pet.pet_num]->own_elf.s2){
                        master.Distribute(show_pet.pet_num,skill,2);
                        show_pet.SetValue(master.my_pet[show_pet.pet_num]->own_elf);

                        new_pet.SetValue(show_pet);
                        SendTcp(QChar('P'));
                        InitLearnedSkill();
                        QMessageBox::information(NULL,"提示","技能学习成功！",QMessageBox::Ok);
                    }
                }
                else
                    QMessageBox::critical(NULL,"错误","同一个精灵不能学习重复的技能！",QMessageBox::Ok);
            }
        }
    }
}

void MainWindow::on_pushButtonCSkill1destribute_clicked()
{//分配技能点给一技能
    if(show_pet.sk1_level<=3&&show_pet.up_skill>0){
        show_pet.Distribute(1);
        master.my_pet[show_pet.pet_num]->own_elf.l1=show_pet.sk1_level;

        new_pet.SetValue(show_pet);
        SendTcp(QChar('P'));
        ui->labelCRemainskill->setNum(show_pet.up_skill);
        ui->labelCSkill1level->setNum(show_pet.sk1_level);
    }
}

void MainWindow::on_pushButtonCSkill2destribute_clicked()
{//分配技能点给2技能
    if(show_pet.sk2_level<=3&&show_pet.up_skill>0){
        show_pet.Distribute(2);
        master.my_pet[show_pet.pet_num]->own_elf.l2=show_pet.sk2_level;

        new_pet.SetValue(show_pet);
        SendTcp(QChar('P'));
        ui->labelCRemainskill->setNum(show_pet.up_skill);
        ui->labelCSkill2Level->setNum(show_pet.sk2_level);
    }
}

void MainWindow::on_pushButtonCChongzhi_clicked()
{//重置当前显示的宠物
    if(show_pet.level>=10){
        if(QMessageBox::Yes==QMessageBox::information(NULL,"提示","重置宠物会降低宠物等级，确认要重置宠物吗？",QMessageBox::Yes|QMessageBox::No,QMessageBox::No)){
            show_pet.DownGrade();
            master.my_pet[show_pet.pet_num]->own_elf.l=show_pet.level;
            master.my_pet[show_pet.pet_num]->own_elf.l1=1;
            master.my_pet[show_pet.pet_num]->own_elf.l2=1;
            master.my_pet[show_pet.pet_num]->own_elf.experience=show_pet.experience;
            master.my_pet[show_pet.pet_num]->own_elf.s1=show_pet.skill1;
            master.my_pet[show_pet.pet_num]->own_elf.s2=show_pet.skill2;

            new_pet.SetValue(show_pet);
            SendTcp(QChar('P'));
            ShowElf();
            InitLearnedSkill();
        }
    }
    else
        QMessageBox::information(NULL,"提示","宠物未到10级不能重置！",QMessageBox::Ok);
}

void MainWindow::on_pushButtonCBack_clicked()
{//宠物界面返回
    PageChange(PMAIN);
}

void MainWindow::on_pushButtonUQveren_clicked()
{//用户界面返回
    if(load_success){
        ui->lineEditUMimaNew->clear();
        ui->lineEditUMimaOld->clear();
        ui->lineEditUNameNew->clear();
        ui->lineEditUNameOld->clear();
        PageChange(PMAIN);
    }
    else
        QMessageBox::information(NULL,"提示","请先登录！",QMessageBox::Ok);
}

void MainWindow::on_pushButtonMSendlook_clicked()
{//请求查看世界列表
    ui->listWidgetOPetshow->clear();
    ui->listWidgetOWanjia->setCurrentRow(-1);
    ui->listWidgetOWanjia->clear();
    SendTcp(QChar('K'));
    PageChange(POTHERUSER);
}

void MainWindow::on_pushButtonOBack_clicked()
{//查看所有用户界面返回
    ui->listWidgetOPetshow->clear();
    ui->listWidgetOWanjia->clear();
    PageChange(PMAIN);
}

void MainWindow::on_pushButtonUDengchu_clicked()
{//用户界面登出
    if(load_success){
        tcp_socket->disconnectFromHost();
        master.Clear();
        load_count=true;
        load_success=false;
        ui->labelUName->setText(master.name);
        ui->labelUTouxiang->setPixmap(master.head_picture);
    }
}

void MainWindow::on_listWidgetOWanjia_currentRowChanged(int currentRow)
{//在查看所有用户界面切换查看用户
    if(currentRow>=0){
        count_gaoji=0;
        count_shenglv=0;
        count_total=0;
        ui->listWidgetOPetshow->clear();
        s=ui->listWidgetOWanjia->currentItem()->text();
        SendTcp(QChar('L'));
    }
}

void MainWindow::on_ComboBoxYWofang_currentIndexChanged(const QString &arg1)
{//改变我方出战精灵
    if(flag_chongwu){
        if(ui->ComboBoxYWofang->currentIndex()>=0){
            int i;
            for(i=0;i<ALLPET;i++){
                if(g_Name[i]==arg1)
                    break;
            }
            QString l;
            show_pet_wo.SetValue(master.my_pet[i]->own_elf);
            ui->labelYWoTou->setPixmap(g_touxiang_pet+g_Name[i]);
            s=g_Str_talent[i];
            l.setNum(show_pet_wo.tal_level);
            s.append(" LV"+l);
            ui->labelYWoTalent->setText(s);
            s=g_Str_skill[show_pet_wo.skill1];
            l.setNum(show_pet_wo.sk1_level);
            s.append(" LV"+l);
            ui->labelYWoSkill1->setText(s);
            s=g_Str_skill[show_pet_wo.skill2];
            l.setNum(show_pet_wo.sk2_level);
            s.append(" LV"+l);
            ui->labelYWoSkill2->setText(s);
            s.setNum(show_pet_wo.level);
            ui->comboBoxYWoLevel->setCurrentText(s);
            ui->textBrowserYWoXianshi->setText(show_pet_wo.ShowAttributes());
        }
    }
}

void MainWindow::on_ComboBoxYDifang_currentIndexChanged(const QString &arg1)
{//改变敌方出战精灵
    if(flag_chongwu){
        if(ui->ComboBoxYDifang->currentIndex()>=0){
            int i;
            for(i=0;i<ALLPET;i++){
                if(g_Name[i]==arg1)
                    break;
            }
            QString l=ui->comboBoxYDiLevel->currentText();
            int level=l.toInt();
            QuickElf quick_elf;
            quick_elf.experience=0;
            quick_elf.l=1;
            quick_elf.l1=1;
            quick_elf.l2=1;
            quick_elf.your_elf=(PetNumber)i;
            quick_elf.s1=(SkillType)(RANDOM(ALLSKILL-2)+1);
            int skill2=RANDOM(ALLSKILL-2)+1;
            while(skill2==quick_elf.s1){
                skill2=RANDOM(ALLSKILL-2)+1;
            }
            quick_elf.s2=(SkillType)skill2;

            show_pet_di.SetValue(quick_elf);
            show_pet_di.UpGrade(level);
            show_pet_di.Distribute(1);
            show_pet_di.Distribute(1);
            show_pet_di.Distribute(2);
            show_pet_di.Distribute(2);

            ui->labelYDiTou->setPixmap(g_touxiang_pet+g_Name[i]);
            s=g_Str_talent[i];
            l.setNum(show_pet_di.tal_level);
            s.append(" LV"+l);
            ui->labelYDiTalent->setText(s);
            s=g_Str_skill[show_pet_di.skill1];
            l.setNum(show_pet_di.sk1_level);
            s.append(" LV"+l);
            ui->labelYDiSkill1->setText(s);
            s=g_Str_skill[show_pet_di.skill2];
            l.setNum(show_pet_di.sk2_level);
            s.append(" LV"+l);
            ui->labelYDiSkill2->setText(s);
            s.setNum(show_pet_di.level);
            ui->comboBoxYDiLevel->setCurrentText(s);
            ui->textBrowserYDiXianshi->setText(show_pet_di.ShowAttributes());
        }
    }
}

void MainWindow::on_comboBoxYDiLevel_currentIndexChanged(const QString &arg1)
{//改变敌方等级
    QString elf=ui->ComboBoxYDifang->currentText();
    on_ComboBoxYDifang_currentIndexChanged(elf);
}

void MainWindow::on_buttonBoxYanwu_clicked(QAbstractButton *button)
{//演武按钮
    if(button==ui->buttonBoxYanwu->button(QDialogButtonBox::Ok)){
        PrepareToFight();
    }
    else
        PageChange(PMAIN);
}

void MainWindow::on_ButtonMShoulie_clicked()
{//狩猎按钮
    SendTcp(QChar('H'));
    ui->StackedWidgetQiehuan->hide();
}

void MainWindow::on_ComboBoxSWofang_currentIndexChanged(const QString &arg1)
{//我方出战精灵该变
    if(flag_chongwu){
        if(ui->ComboBoxSWofang->currentIndex()>=0){
            int i;
            for(i=0;i<ALLPET;i++){
                if(g_Name[i]==arg1)
                    break;
            }
            QString l;
            show_pet_wo.SetValue(master.my_pet[i]->own_elf);
            ui->labelSWoTou->setPixmap(g_touxiang_pet+g_Name[i]);
            s=g_Str_talent[i];
            l.setNum(show_pet_wo.tal_level);
            s.append(" LV"+l);
            ui->labelSWoTalent->setText(s);
            s=g_Str_skill[show_pet_wo.skill1];
            l.setNum(show_pet_wo.sk1_level);
            s.append(" LV"+l);
            ui->labelSWoSkill1->setText(s);
            s=g_Str_skill[show_pet_wo.skill2];
            l.setNum(show_pet_wo.sk2_level);
            s.append(" LV"+l);
            ui->labelSWoSkill2->setText(s);
            s.setNum(show_pet_wo.level);
            ui->comboBoxSWoLevel->setCurrentText(s);
            ui->textBrowserSWoXianshi->setText(show_pet_wo.ShowAttributes());

            if(fight_mode==JVEDOU){
                ui->comboBoxSDiLevel->setCurrentIndex(show_pet_wo.level-1);
            }
        }
    }
}

void MainWindow::on_ComboBoxSDifang_currentIndexChanged(int index)
{//敌方出战精灵改变
    if(flag_chongwu){
        if(index>=0){
            int k=index;
            QString l=ui->ComboBoxSDifang->currentText();
            int i;
            for(i=0;i<ALLPET;i++){
                if(g_Name[i]==l)
                    break;
            }
            enemy[k].l=ui->comboBoxSDiLevel->currentIndex()+1;
            enemy[k].l1=1;
            enemy[k].l2=1;
            enemy[k].experience=0;

            show_pet_di.SetValue(enemy[k]);
            if(fight_mode==JVEDOU)
                JveDouPower();//决斗的宠物要加强
            show_pet_di.Distribute(1);
            show_pet_di.Distribute(1);
            show_pet_di.Distribute(2);
            show_pet_di.Distribute(2);

            ui->labelSDiTou->setPixmap(g_touxiang_pet+g_Name[i]);
            s=g_Str_talent[i];
            l.setNum(show_pet_di.tal_level);
            s.append(" LV"+l);
            ui->labelSDiTalent->setText(s);
            s=g_Str_skill[show_pet_di.skill1];
            l.setNum(show_pet_di.sk1_level);
            s.append(" LV"+l);
            ui->labelSDiSkill1->setText(s);
            s=g_Str_skill[show_pet_di.skill2];
            l.setNum(show_pet_di.sk2_level);
            s.append(" LV"+l);
            ui->labelSDiSkill2->setText(s);
            ui->textBrowserSDiXianshi->setText(show_pet_di.ShowAttributes());
        }
    }
}

void MainWindow::on_comboBoxSDiLevel_currentIndexChanged(int index)
{//敌方等级改变
    if(flag_chongwu){
        if(index>=0){
            int k=ui->ComboBoxSDifang->currentIndex();
            QString l=ui->ComboBoxSDifang->currentText();
            int i;
            for(i=0;i<ALLPET;i++){
                if(g_Name[i]==l)
                    break;
            }
            enemy[k].l=index+1;
            enemy[k].l1=1;
            enemy[k].l2=1;
            enemy[k].experience=0;

            show_pet_di.SetValue(enemy[k]);
            if(fight_mode==JVEDOU)
                JveDouPower();//决斗精灵要加强
            show_pet_di.Distribute(1);
            show_pet_di.Distribute(1);
            show_pet_di.Distribute(2);
            show_pet_di.Distribute(2);

            ui->labelSDiTou->setPixmap(g_touxiang_pet+g_Name[i]);
            s=g_Str_talent[i];
            l.setNum(show_pet_di.tal_level);
            s.append(" LV"+l);
            ui->labelSDiTalent->setText(s);
            s=g_Str_skill[show_pet_di.skill1];
            l.setNum(show_pet_di.sk1_level);
            s.append(" LV"+l);
            ui->labelSDiSkill1->setText(s);
            s=g_Str_skill[show_pet_di.skill2];
            l.setNum(show_pet_di.sk2_level);
            s.append(" LV"+l);
            ui->labelSDiSkill2->setText(s);
            ui->textBrowserSDiXianshi->setText(show_pet_di.ShowAttributes());
        }
    }
}

void MainWindow::on_buttonBoxShoulie_clicked(QAbstractButton *button)
{//狩猎和决斗界面开始战斗或者返回主界面
    if(button==ui->buttonBoxShoulie->button(QDialogButtonBox::Ok)){
        if(fight_mode==JVEDOU)
            SendTcp(QChar('J'),2);
        PrepareToFight();
    }
    else{
        SendTcp(QChar('M'));//报告服务器并没还有开始决斗
        PageChange(PMAIN);
    }
}

void MainWindow::on_ButtonMJvedou_clicked()
{//决斗按钮
    SendTcp(QChar('J'),1);
    ui->StackedWidgetQiehuan->hide();
}

void MainWindow::on_pushButtonSSend_clicked()
{//送出宠物
    QString l=ui->ComboBoxSWofang->currentText();
    s=QString("请确认你将要送出的宠物:"+l);
    int i=QMessageBox::information(NULL,"提示",s,QMessageBox::Yes|QMessageBox::No,QMessageBox::No);
    if(i==QMessageBox::Yes){
        int count;
        for(count=0;count<ALLPET;count++){
            if(show_pet_wo.name==g_Name[count]){
                break;
            }
        }
        master.DeletePet((PetNumber)count);
        SendTcp(QChar('F'),count);
        PageChange(PMAIN);
        QMessageBox::information(NULL,"提示","你的宠物已被送出！\n不过不要灰心再接再厉，你还可以赢回来更多！",QMessageBox::Ok);
        if(master.count_pet==0){
            ui->StackedWidgetQiehuan->hide();
            QMessageBox::information(NULL,"提示","你已经送出了你的所有宠物！精灵总部决定免费送你一个新的宠物小精灵！",QMessageBox::Ok);
        }
    }
}

void MainWindow::on_lineEditMmiyao_editingFinished()
{//输入正确密钥解锁二技能
    if(ui->lineEditMmiyao->text()=="王苑亨大帅哥"){
        SendTcp(QChar('X'));
        for(int i=0;i<ALLPET;i++){
            if(master.my_pet[i]!=NULL){
                master.my_pet[i]->own_elf.s2=UNLOCKED;
            }
        }
        QMessageBox::information(NULL,"提示","说实话的孩子总会有好运气！",QMessageBox::Ok);
        ui->lineEditMmiyao->clear();
    }
}


