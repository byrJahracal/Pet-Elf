#include "Battle.h"

Battle::Battle()//初始化战场
{
    elf1=NULL;
    elf2=NULL;
    s="";
    attack1.Clear();
    attack2.Clear();
    turn1=0;
    turn2=0;
    state_time=NOTHING;
    state_turn=0;
}

void Battle::RandomElf(int elfi)//随机一个精灵
{
    PetNumber pet_num=(PetNumber)(RANDOM(ALLPET)-1);
    SkillType skill_1=(SkillType)(RANDOM(ALLSKILL-2)+1);
    SkillType skill_2=(SkillType)(RANDOM(ALLSKILL-2)+1);
    PetElfFighting *new_elf;
    new_elf =new PetElfFighting(pet_num,skill_1,skill_2,MAXLEVEL,3,3);
    if(elfi==1){
        if(elf1)
            delete elf1;
        elf1=new_elf;
    }
    else if(elfi==2){
        if(elf2)
            delete elf2;
        elf2=new_elf;
    }
}

void Battle::ChooseElf(int whitch,PetElf &p)//根据精灵编号选择构造函数
{
    if(whitch==1){
        if(elf1)
            delete elf1;
        switch(p.pet_num){
        case YEJINGLING:
        case HUOJINGLING:
        case LEIJINGLING:
        case BINGJINGLING:
        case HEIJINGLING:{
            elf1=new PetElfFighting(p);
            break;
        }
        case XUANWUSHOU:{
            elf1=new XuanWUShou(p);
            break;
        }
        case BAOLONGSHOU:{
            elf1=new BaoLongShou(p);
            break;
        }
        case JIALULUSHOU:{
            elf1=new JiaLuLuShou(p);
            break;
        }
        case QINGLONGSHOU:{
            elf1=new QingLongShou(p);
            break;
        }
        case YUANDUXIXVEGUI:{
            elf1=new YuanDuXiXveGui(p);
            break;
        }
        case TIANNVSHOU:{
            elf1=new TianNvShou(p);
            break;
        }
        case ZHANDOUBAOLONG:{
            elf1=new ZhanDouBaoLong(p);
            break;
        }
        case GANGTIEJIALULU:{
            elf1=new GangTieJiaLuLu(p);
            break;
        }
        case DUJIAOXIAN:{
            elf1=new DuJiaoXian(p);
            break;
        }
        case SANGSHIBAOLONG:{
            elf1=new SangShiBaoLong(p);
            break;
        }
        case XIANRENZHANG:{
            elf1=new XianRenZhang(p);
            break;
        }
        case JIANSHISHOU:{
            elf1=new JianShiShou(p);
            break;
        }
        case GANGTIEHAILONG:{
            elf1=new GangTieHaiLong(p);
            break;
        }
        case ZUDUNSHOU:{
            elf1=new ZuDunShou(p);
            break;
        }
        case EMOSHOU:{
            elf1=new EMoShou(p);
            break;
        }
        case MUOUSHOU:{
            elf1=new MuOuShou(p);
            break;
        }
        case JIALOULUOSHOU:{
            elf1=new JiaLouLuoShou(p);
            break;
        }
        case LANGRENJIALULU:{
            elf1=new LangRenJiaLuLu(p);
            break;
        }
        case AOMIJIASHOU:{
            elf1=new AoMiJiaShou(p);
            break;
        }
        case NVEMOSHOU:{
            elf1=new NvEMoShou(p);
            break;
        }
        }
    }
    else if(whitch==2){
        if(elf2)
            delete elf2;
        switch(p.pet_num){
        case YEJINGLING:
        case HUOJINGLING:
        case LEIJINGLING:
        case BINGJINGLING:
        case HEIJINGLING:{
            elf2=new PetElfFighting(p);
            break;
        }
        case XUANWUSHOU:{
            elf2=new XuanWUShou(p);
            break;
        }
        case BAOLONGSHOU:{
            elf2=new BaoLongShou(p);
            break;
        }
        case JIALULUSHOU:{
            elf2=new JiaLuLuShou(p);
            break;
        }
        case QINGLONGSHOU:{
            elf2=new QingLongShou(p);
            break;
        }
        case YUANDUXIXVEGUI:{
            elf2=new YuanDuXiXveGui(p);
            break;
        }
        case TIANNVSHOU:{
            elf2=new TianNvShou(p);
            break;
        }
        case ZHANDOUBAOLONG:{
            elf2=new ZhanDouBaoLong(p);
            break;
        }
        case GANGTIEJIALULU:{
            elf2=new GangTieJiaLuLu(p);
            break;
        }
        case DUJIAOXIAN:{
            elf2=new DuJiaoXian(p);
            break;
        }
        case SANGSHIBAOLONG:{
            elf2=new SangShiBaoLong(p);
            break;
        }
        case XIANRENZHANG:{
            elf2=new XianRenZhang(p);
            break;
        }
        case JIANSHISHOU:{
            elf2=new JianShiShou(p);
            break;
        }
        case GANGTIEHAILONG:{
            elf2=new GangTieHaiLong(p);
            break;
        }
        case ZUDUNSHOU:{
            elf2=new ZuDunShou(p);
            break;
        }
        case EMOSHOU:{
            elf2=new EMoShou(p);
            break;
        }
        case MUOUSHOU:{
            elf2=new MuOuShou(p);
            break;
        }
        case JIALOULUOSHOU:{
            elf2=new JiaLouLuoShou(p);
            break;
        }
        case LANGRENJIALULU:{
            elf2=new LangRenJiaLuLu(p);
            break;
        }
        case AOMIJIASHOU:{
            elf2=new AoMiJiaShou(p);
            break;
        }
        case NVEMOSHOU:{
            elf2=new NvEMoShou(p);
            break;
        }
        }
    }
}

StateWindow Battle::Fighting()//自动战斗
{
    special_effects_skill=TOPAN;
    switch(state_turn){
    case 0:{//精灵冲刺
        if(turn1>=TURNNEED||turn2>=TURNNEED){//有一个精灵准备好了
            state_time=BEGIN;
            state_skill=TOPAN;
            state_period=1;
            if(turn1==turn2){//同时准备好
                if(RANDOM(2)==1){//随机一个先手
                    state_turn=1;
                    turn1-=TURNNEED;
                    break;
                }
                else{
                    state_turn=2;
                    turn2-=TURNNEED;
                    break;
                }
            }
            else if(turn1>turn2){//我方精灵开始行动
                state_turn=1;
                turn1-=TURNNEED;
                break;
            }
            else if(turn1<turn2){//敌方精灵开始行动
                state_turn=2;
                turn2-=TURNNEED;
                break;
            }
        }
        else {//精灵准备进度条增加
            turn1+=elf1->agility;
            turn2+=elf2->agility;
        }
        break;
    }
    case 1:{//我方精灵行动
        switch(state_time){
        case BEGIN:{//回合开始阶段
            if(state_skill==TOPAN){//判定状态
                elf1->round++;
                s.setNum(elf1->round);
                g_message=g_message+"\n\n"+elf1->name+"开始第"+s+"次行动！";
                elf1->RoundBegin();
                AutoState();
                EndJudge();
            }
            else {
                AutoAttack();//自动释放技能
            }
            break;
        }
        case SIMPLE_ATTACK:{//普攻阶段
            state_skill=TOATT;
            if(elf1->probability_attack!=0){
                AutoAttack();//自动攻击
            }
            else{
                g_message=g_message+'\n'+elf1->name+"无法进行攻击！";
                AutoState();//跳转状态
            }
            break;
        }
        case SKILL_TIME:{//释放主动技能阶段
            if(state_skill==TOTAL){
                int i=RANDOM(100);
                if(i<=elf1->probability_initialtive){
                    AutoAttack();//自动攻击
                }
                else{
                    g_message=g_message+'\n'+elf1->name+"无法释放主动技能！";
                    state_skill=TOSK2;
                    AutoState();
                }
            }
            else
                AutoAttack();
            break;
        }
        case OVER:{//回合结束阶段
            elf1->RoundOver();
            g_message=g_message+'\n'+elf1->name+"结束行动！";
            AutoState();
            EndJudge();
            break;
        }
        }
        break;
    }
    case 2:{//敌方精灵行动
        switch(state_time){
        case BEGIN:{//回合开始
            if(state_skill==TOPAN){
                elf2->round++;
                s.setNum(elf2->round);
                g_message=g_message+"\n\n"+elf2->name+"开始第"+s+"次行动！";
                elf2->RoundBegin();
                AutoState();
                EndJudge();
            }
            else {
                AutoAttack();
            }
            break;
        }
        case SIMPLE_ATTACK:{//普攻阶段
            state_skill=TOATT;
            if(elf2->probability_attack!=0){
                AutoAttack();
            }
            else{
                g_message=g_message+'\n'+elf2->name+"无法进行攻击！";
                AutoState();
            }
            break;
        }
        case SKILL_TIME:{//释放主动技能阶段
            if(state_skill==TOTAL){
                int i=RANDOM(100);
                if(i<=elf2->probability_initialtive){
                    AutoAttack();
                }
                else{
                    g_message=g_message+'\n'+elf2->name+"无法释放主动技能！";
                    state_skill=TOSK2;
                    AutoState();
                }
            }
            else
                AutoAttack();
            break;
        }
        case OVER:{//回合结束阶段
            elf2->RoundOver();
            g_message=g_message+'\n'+elf2->name+"结束行动！";
            AutoState();
            EndJudge();
            break;
        }
        }
        break;
    }
    case -1:{//战斗结束
        if(elf1->life==0&&elf2->life==0){
            g_message=g_message+'\n'+"平局！";
            winner=0;
        }
        else if(elf1->life==0){
            g_message=g_message+'\n'+elf2->name+"获胜！";
            winner=2;
        }
        else if(elf2->life==0){
            g_message=g_message+'\n'+elf1->name+"获胜！";
            winner=1;
        }
        state_turn=-2;
        break;
    }
    default:{
        return PFIGHTOVER;
    }
    }
    return PFIGHT;
}

void Battle::Prepare()//战前准备
{
    state_period=1;
    state_skill=TOPAN;
    state_time=NOTHING;
    state_turn=0;
}

void Battle::EndJudge()//判断战斗是否结束
{
    if(elf1->life==0||elf2->life==0){
        state_time=NOTHING;
        state_turn=-1;
    }
}

void Battle::AutoState()//自动跳转自动机状态
{
    switch(state_time){
    case BEGIN:{
        AutoSkill();
        break;
    }
    case SIMPLE_ATTACK:{
        state_time=SKILL_TIME;
        state_period=1;
        state_skill=TOTAL;
        break;
    }
    case SKILL_TIME:{
        AutoSkill();
        break;
    }
    case OVER:{
        state_turn=0;
        state_time=NOTHING;
        state_period=1;
        state_skill=TOPAN;
        break;
    }
    }
}

void Battle::AutoAttack()//自动攻击
{
    special_effects_skill=state_skill;
    head_period=state_period;
    if(state_turn==1){
        if(state_period==1){//发起进攻阶段
            attack1.Clear();
            if(state_skill==TOATT){//普通攻击
                attack1=elf1->SimpleAttack();
            }
            else{
                if(state_skill==TOTAL){//天赋技能
                    if(state_time==elf1->judge_time[TALENT])
                        attack1=elf1->Talent();
                    else
                        state_skill=TOSK1;
                }
                if(state_skill==TOSK1){//技能一
                    if(state_time==elf1->judge_time[SKILL1]){
                        attack1=elf1->UseSkill1();
                        special_effects_skill=state_skill;
                    }
                    else
                        state_skill=TOSK2;
                }
                if(state_skill==TOSK2&&state_time==elf1->judge_time[SKILL2]){//技能二
                    attack1=elf1->UseSkill2();
                    special_effects_skill=state_skill;
                }
            }
            if(attack1.happen==1){
                state_period=2;
            }
            else {
                AutoState();
            }
            EndJudge();
        }
        else if(state_period==2){//反馈伤害和吸血
            attack2=elf2->Injured(attack1);
            state_period=3;
            EndJudge();
        }
        else{//接受吸血和反伤
            elf1->Injured(attack2);
            AutoState();
            EndJudge();
        }
    }
    else if(state_turn==2){
        if(state_period==1){//主动攻击阶段
            attack2.Clear();
            if(state_skill==TOATT){//普通攻击
                attack2=elf2->SimpleAttack();
            }
            else{
                if(state_skill==TOTAL){//天赋技能释放
                    if(state_time==elf2->judge_time[TALENT])
                        attack2=elf2->Talent();
                    else
                        state_skill=TOSK1;
                }
                if(state_skill==TOSK1){//技能1释放
                    if(state_time==elf2->judge_time[SKILL1]){
                        attack2=elf2->UseSkill1();
                        special_effects_skill=state_skill;
                    }
                    else
                        state_skill=TOSK2;
                }
                if(state_skill==TOSK2&&state_time==elf2->judge_time[SKILL2]){//技能2释放
                    attack2=elf2->UseSkill2();
                    special_effects_skill=state_skill;
                }
            }
            if(attack2.happen==1){
                state_period=2;
            }
            else {
                AutoState();
            }
            EndJudge();
        }
        else if(state_period==2){//计算受到伤害和反馈伤害
            attack1=elf1->Injured(attack2);
            state_period=3;
            EndJudge();
        }
        else{//接受吸血和反伤
            elf2->Injured(attack1);
            AutoState();
            EndJudge();
        }
    }
}

void Battle::AutoSkill()
{
    if(state_turn==1){
        switch(state_skill){
        case TOPAN:{//判定阶段之后跳转状态
            if(elf1->judge_time[TALENT]==state_time){
                state_skill=TOTAL;
                state_period=1;
            }
            else if(elf1->judge_time[SKILL1]==state_time){
                state_skill=TOSK1;
                state_period=1;
            }
            else if(elf1->judge_time[SKILL2]==state_time){
                state_skill=TOSK2;
                state_period=1;
            }
            else{
                state_time=(FightTime)(state_time+1);
                state_skill=TOATT;
                state_period=1;
            }
            break;
        }
        case TOTAL:{//天赋技能之后跳转状态
            if(elf1->judge_time[SKILL1]==state_time){
                state_skill=TOSK1;
                state_period=1;
            }
            else if(elf1->judge_time[SKILL2]==state_time){
                state_skill=TOSK2;
                state_period=1;
            }
            else{
                state_time=(FightTime)(state_time+1);
                state_skill=TOATT;
                state_period=1;
            }
            break;
        }
        case TOSK1:{//释放技能1之后跳转状态
            if(elf1->judge_time[SKILL2]==state_time){
                state_skill=TOSK2;
                state_period=1;
            }
            else{
                state_time=(FightTime)(state_time+1);
                state_skill=TOATT;
                state_period=1;
            }
            break;
        }
        case TOSK2:{//释放技能二之后跳转状态
            state_time=(FightTime)(state_time+1);
            state_skill=TOATT;
            state_period=1;
            break;
        }
        }
    }
    else if(state_turn==2){
        switch(state_skill){
        case TOPAN:{//判定状态之后跳转状态
            if(elf2->judge_time[TALENT]==state_time){
                state_skill=TOTAL;
                state_period=1;
            }
            else if(elf2->judge_time[SKILL1]==state_time){
                state_skill=TOSK1;
                state_period=1;
            }
            else if(elf2->judge_time[SKILL2]==state_time){
                state_skill=TOSK2;
                state_period=1;
            }
            else{
                state_time=(FightTime)(state_time+1);
                state_skill=TOATT;
                state_period=1;
            }
            break;
        }
        case TOTAL:{//释放天赋技能之后跳转状态
            if(elf2->judge_time[SKILL1]==state_time){
                state_skill=TOSK1;
                state_period=1;
            }
            else if(elf2->judge_time[SKILL2]==state_time){
                state_skill=TOSK2;
                state_period=1;
            }
            else{
                state_time=(FightTime)(state_time+1);
                state_skill=TOATT;
                state_period=1;
            }
            break;
        }
        case TOSK1:{//释放一技能之后跳转状态
            if(elf2->judge_time[SKILL2]==state_time){
                state_skill=TOSK2;
                state_period=1;
            }
            else{
                state_time=(FightTime)(state_time+1);
                state_skill=TOATT;
                state_period=1;
            }
            break;
        }
        case TOSK2:{//释放技能2之后跳转状态
            state_time=(FightTime)(state_time+1);
            state_skill=TOATT;
            state_period=1;
            break;
        }
        }
    }
}

