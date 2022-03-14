#include "Petelffighting.h"

PetElfFighting::PetElfFighting():PetElf()//默认构造一个叶精灵
{
    int i=YEJINGLING;
    ChooseFunction();
    round=0;
    for(int i=0;i<ALLSTATE;i++){
        state_fighting[i][0]=0;
        state_fighting[i][1]=0;
        state_fighting[i][2]=0;
    }
    judge_time[TALENT]=g_Talent_Time[i];
    judge_time[SKILL1]=g_Skill_Time[skill1];
    judge_time[SKILL2]=g_Skill_Time[skill2];
    skill_kind[TALENT]=g_Talent_Kind[i];
    skill_kind[SKILL1]=g_Skill_Kind[skill1];
    skill_kind[SKILL2]=g_Skill_Kind[skill2];
    life_back=life;
    cri_back=cri_rate;
    power_back=power;
    defence_back=defence;
    agility_back=agility;
    dofge_back=dodge_rate;
    ele_back=element;
    probability_attack=100;
    probability_initialtive=100;//记录主动技能释放概率
    probability_passitive=100;//记录被动技能释放概率
}

PetElfFighting::PetElfFighting(PetElf your_elf)//构造一个指定精灵
{
    pet_num=your_elf.pet_num;
    name=your_elf.name;
    primarya_a=your_elf.primarya_a;
    element=your_elf.element;
    life=your_elf.life;
    power=your_elf.power;
    defence=your_elf.defence;
    agility=your_elf.agility;
    life_grow=your_elf.life_grow;
    power_grow=your_elf.power_grow;
    defence_grow=your_elf.defence_grow;
    agility_grow=your_elf.agility_grow;
    cri_rate=your_elf.cri_rate;
    cri_damage=your_elf.cri_damage;
    dodge_rate=your_elf.dodge_rate;
    skill1=your_elf.skill1;
    skill2=your_elf.skill2;
    level=your_elf.level;
    sk1_level=your_elf.sk1_level;
    sk2_level=your_elf.sk2_level;
    ChooseFunction();
    tal_level=your_elf.tal_level;
    up_skill=your_elf.up_skill;
    round=0;
    for(int i=0;i<ALLSTATE;i++){//初始化状态
        state_fighting[i][0]=0;
        state_fighting[i][1]=0;
        state_fighting[i][2]=0;
    }
    judge_time[TALENT]=g_Talent_Time[pet_num];
    judge_time[SKILL1]=g_Skill_Time[skill1];
    judge_time[SKILL2]=g_Skill_Time[skill2];
    skill_kind[TALENT]=g_Talent_Kind[pet_num];
    skill_kind[SKILL1]=g_Skill_Kind[skill1];
    skill_kind[SKILL2]=g_Skill_Kind[skill2];
    life_back=life;
    cri_back=cri_rate;
    power_back=power;
    defence_back=defence;
    agility_back=agility;
    dofge_back=dodge_rate;
    ele_back=element;
    probability_attack=100;
    probability_initialtive=100;//记录主动技能释放概率
    probability_passitive=100;//记录被动技能释放概率
    image=your_elf.image;
    experience=0;
}

PetElfFighting::PetElfFighting(PetNumber your_elf, SkillT s1, SkillT s2, int l, int l1, int l2)
{
    int i=your_elf;
    pet_num=g_PetNum[i];
    name=g_Name[i];
    primarya_a=g_PrimaryA_A[i];
    element=g_Element[i];
    life=g_Life[i];
    power=g_Power[i];
    defence=g_Defence[i];
    agility=g_Agility[i];
    life_grow=g_Life_Grow[i];
    power_grow=g_Power_Grow[i];
    defence_grow=g_Defence_Grow[i];
    agility_grow=g_Agility_Grow[i];
    cri_rate=g_Cri_Rate[i];
    cri_damage=g_Cri_Damage[i];
    dodge_rate=g_Dodge_Rate[i];
    skill1=s1;
    skill2=s2;
    ChooseFunction();
    level=1;
    sk1_level=l1;
    sk2_level=l2;
    tal_level=1;
    UpGrade(l);
    up_skill-=l1-1;
    up_skill-=l2-1;
    round=0;
    for(int i=0;i<ALLSTATE;i++){//初始化状态
        state_fighting[i][0]=0;
        state_fighting[i][1]=0;
        state_fighting[i][2]=0;
    }
    judge_time[TALENT]=g_Talent_Time[i];
    judge_time[SKILL1]=g_Skill_Time[skill1];
    judge_time[SKILL2]=g_Skill_Time[skill2];
    skill_kind[TALENT]=g_Talent_Kind[i];
    skill_kind[SKILL1]=g_Skill_Kind[skill1];
    skill_kind[SKILL2]=g_Skill_Kind[skill2];
    life_back=life;
    cri_back=cri_rate;
    power_back=power;
    defence_back=defence;
    agility_back=agility;
    dofge_back=dodge_rate;
    ele_back=element;
    probability_attack=100;
    probability_initialtive=100;//记录主动技能释放概率
    probability_passitive=100;//记录被动技能释放概率
    experience=0;
    image.load(g_Image[i]);
}

Attack PetElfFighting::SimpleAttack()//普通攻击
{
    Attack a;
    a.happen=1;
    g_message=g_message+'\n'+name+"发动了普通攻击！";
    int p=CriOrNot();//计算总伤害
    int e=p*g_ele_ratio;//元素伤害

    a.ignore=false;
    a.ele_damage[element]+=e;//元素伤害
    a.ele_damage[LEAF]+=p-e;//普通伤害
    a.special_effects=-1;//普攻无特效

    int probability=15+tal_level*5;
    int i=RANDOM(100);
    if(i<=probability&&pet_num<=HEIJINGLING){//基本精灵释放追击天赋
        g_message=g_message+"\n"+name+"发动了天赋技能:";
        g_message.append(g_Str_talent[pet_num]+"！");
        switch(pet_num){
        case YEJINGLING:{
            a.special_effects=LEAF;
            GZhongDu(a,20+tal_level*10,1+tal_level*2,2);
            break;
        }
        case HUOJINGLING:{
            a.special_effects=FLAME;
            GZhuoShao(a,2+tal_level,30+tal_level*10,2);
            break;
        }
        case BINGJINGLING:{
            a.special_effects=ICE;
            GBingDong(a,10,10+40*(tal_level/3),1+tal_level/2);
            break;
        }
        case LEIJINGLING:{
            a.special_effects=THUNDER;
            GGanDian(a,10*tal_level,15*tal_level,2);
            break;
        }
        case HEIJINGLING:{
            a.special_effects=DARK;
            GRuoHua(a,20+20*tal_level,20+20*tal_level,2);
            break;
        }
        default:{
            break;
        }
        }
    }
    if(state_fighting[GANDIAN][1]>0){
        JGanDian(a,SIMPLE_ATTACK);
    }
    return a;
}

Attack PetElfFighting::Talent()
{
    return return_attack;
}

Attack PetElfFighting::Injured(Attack attack)//受伤函数
{
    return_attack.Clear();
    int real_dodge;//真实闪避率
    int i=RANDOM(100);
    if(attack.blood_sucking!=0&&state_fighting[SHIXVE][0]!=0){//吸血处理
        JShiXve(attack.blood_sucking);
    }
    if(attack.happen!=0){//这是一个由伤害或符加不良状态的攻击包
        if(attack.ignore!=1){
            real_dodge=JGuiBi();//处于规避状态的闪避率
        }
        else real_dodge=0;
        if(i>real_dodge){//没有闪避
            if(state_fighting[MIANYI][2]>0){//处于免疫状态
                JMianYi(attack);
                g_message=g_message+"\n"+name+"免疫一切不良状态！";
                if(attack.state_attack[XUANYUN][1]==1){//受到无视免疫的眩晕
                    state_fighting[XUANYUN][0]=attack.state_attack[XUANYUN][0];
                    state_fighting[XUANYUN][1]=attack.state_attack[XUANYUN][1];
                    state_fighting[XUANYUN][2]=attack.state_attack[XUANYUN][2];
                    g_message=g_message+"\n"+name+"受到无视免疫的眩晕攻击！";
                    QString s=QString::number(state_fighting[XUANYUN][0]);
                    defence-=state_fighting[XUANYUN][0];
                    probability_attack=0;
                    probability_initialtive=0;
                    probability_passitive=0;//无法释放普攻主动被动技能
                    state_fighting[MIANYI][0]=0;
                    state_fighting[MIANYI][1]=0;
                    state_fighting[MIANYI][2]=0;
                    g_message=g_message+"\n"+name+"的免疫状态被破除了！";
                    g_message=g_message+"\n"+name+"陷入了眩晕状态，无法行动，防御降低了"+s+"！";
                }
            }
            else
                Refresh(attack);//刷新精灵状态
            if(state_fighting[GANDIAN][2]>0)
                JGanDian(attack,INJURED);//感电状态增加雷电伤害

            int damage=attack.Calculate(element);//根据属性克制计算伤害
            if(state_fighting[HUDUN][2]>0)
                JHuDun(damage);//护盾吸收伤害

            damage*=DEFENCECONST;
            damage/=(DEFENCECONST+defence);//根据防御计算最终伤害
            life-=damage;

            QString s=QString::number(damage);
            g_message=g_message+"\n"+name+"受到了"+s+"点伤害！";
            if(life<=0){
                life=0;
                g_message=g_message+"\n"+name+"无法再坚持战斗！";
            }
            else {
                if(state_fighting[FANSHANG][2]>0&&attack.is_back==0&&attack.from==0){
                    return_attack=JFanShang(attack,damage);//反伤状态
                }
                return_attack.blood_sucking=damage;
                if(attack.from==0&&attack.is_back==0){//触发被动技能
                    if(probability_passitive!=0){
                        if(judge_time[TALENT]==INJURED){
                            Talent();
                        }
                        if(judge_time[SKILL1]==INJURED){
                            UseSkill1();
                        }
                        if(judge_time[SKILL2]==INJURED){
                            UseSkill2();
                        }
                    }
                    else{
                        g_message=g_message+'\n'+name+"无法使用被动技能！";
                    }
                }
            }
        }
        else{
            g_message=g_message+'\n'+name+"躲开了攻击！";
        }
    }
    return return_attack;
}

void PetElfFighting::ChooseFunction()//选择精灵的可学习技能对应函数
{
    switch(skill1){
    case FLAME_ATTACK:
        Function1=FlameAttack;
        break;
    case ICE_ATTACK:
        Function1=IceAttack;
        break;
    case THUNDER_ATTACK:
        Function1=ThunderAttack;
        break;
    case LEAF_ATTACK:
        Function1=LEAFAttack;
        break;
    case DARK_ATTACK:
        Function1=DarkAttack;
        break;
    case XILI:
        Function1=XiLi;
        break;
    case BUQUYIZHI:
        Function1=BuQuYiZhi;
        break;
    case XIANXVEKEWANG:
        Function1=XianXveKeWang;
        break;
    case XIANQUTUJI:
        Function1=XianQuTuJi;
        break;
    default:
        Function1=NULL;
        break;
    }
    switch(skill2){
    case FLAME_ATTACK:
        Function2=FlameAttack;
        break;
    case ICE_ATTACK:
        Function2=IceAttack;
        break;
    case THUNDER_ATTACK:
        Function2=ThunderAttack;
        break;
    case LEAF_ATTACK:
        Function2=LEAFAttack;
        break;
    case DARK_ATTACK:
        Function2=DarkAttack;
        break;
    case XILI:
        Function2=XiLi;
        break;
    case BUQUYIZHI:
        Function2=BuQuYiZhi;
        break;
    case XIANXVEKEWANG:
        Function2=XianXveKeWang;
        break;
    case XIANQUTUJI:
        Function2=XianQuTuJi;
        break;
    default:
        Function2=NULL;
        break;
    }
}

void PetElfFighting::JGanDian(Attack& attack,FightTime time)//判定感电状态
{
    int i=GANDIAN;

    if(time==INJURED){//受伤时受到雷电伤害增加
        attack.ele_damage[THUNDER]*=(1+state_fighting[i][0]/100.0);
    }
    else if(time==SIMPLE_ATTACK){//普通攻击时受到雷电伤害
        Attack a;
        a.ele_damage[THUNDER]+=state_fighting[i][1];
        a.happen=1;
        a.ignore=1;
        a.from=1;
        QString s=QString::number(state_fighting[i][1]);
        g_message=g_message+'\n'+name+"处于感电状态，攻击时受到雷电伤害！";
        Injured(a);
    }
}

void PetElfFighting::JHuDun(int& damage)//判定护盾吸收伤害
{
    int i=HUDUN;
    if(state_fighting[i][0]!=0){
        damage*=(1-state_fighting[i][0]/100.0);
    }
    if(damage>=state_fighting[i][1]&&state_fighting[i][1]!=0){//护盾被完全破坏
        QString s=QString::number(state_fighting[i][1]);
        g_message=g_message+"\n"+name+"由于护盾状态吸收了"+s+"伤害！";
        damage-=state_fighting[i][1];
        state_fighting[i][1]=0;
    }
    else if(state_fighting[i][1]>damage){//护盾没有被完全破坏
        QString s=QString::number(damage);
        g_message=g_message+"\n"+name+"由于护盾状态吸收了"+s+"伤害！";
        state_fighting[i][1]-=damage;
        damage=0;
    }
}

Attack PetElfFighting::JFanShang(Attack attack,int damage)
{
    Attack a;
    a.happen=1;
    a.ignore=1;//无视闪避
    a.is_back=1;//反伤标志
    a.blood_sucking=damage;
    int i;
    int j=FANSHANG;
    int sum=0;
    damage=damage*state_fighting[j][0]/100+state_fighting[j][1];
    for(i=0;i<ALLELEMENT;i++){//反伤总伤害
        sum+=attack.ele_damage[i];
    }
    if(sum!=0){
        for(i=0;i<ALLELEMENT;i++){//反伤伤害分配元素
            a.ele_damage[i]+=damage*attack.ele_damage[i]/sum;
        }
    }
    g_message=g_message+"\n"+name+"处于反伤状态！";
    return a;
}

void PetElfFighting::JMianYi(Attack& attack)
{
    int i=MIANYI;
    attack.ele_damage[FLAME]*=1-state_fighting[i][0]/100.0;//受到伤害减少
    attack.ele_damage[ICE]*=1-state_fighting[i][0]/100.0;
    attack.ele_damage[THUNDER]*=1-state_fighting[i][0]/100.0;
    attack.ele_damage[LEAF]*=1-state_fighting[i][1]/100.0;
    attack.ele_damage[DARK]*=1-state_fighting[i][1]/100.0;
}

int PetElfFighting::JGuiBi()
{
    int i=GUIBI;
    if(state_fighting[i][1]>0){//规避次数
        state_fighting[i][1]--;
        g_message=g_message+"\n"+name+"由于规避状态免疫了这次伤害！";
        return 100;
    }
    else{//闪避率增加
        int b=dodge_rate;
        return b;
    }
}

void PetElfFighting::JShiXve(int blood)
{
    int i=blood*state_fighting[SHIXVE][0]/100;//吸血
    life+=i;
    if(life>life_back)
        life=life_back;
    QString s=QString::number(i);
    g_message=g_message+"\n"+name+"由于嗜血状态回复了"+s+"点生命！";
}

void PetElfFighting::GZhongDu(Attack &last_attack,int v1,int v2,int v3)
{//伤害，敏捷降低
    int i=ZHONGDU;
    if(last_attack.state_attack[i][2]==0||(last_attack.state_attack[i][0]+last_attack.state_attack[i][1])*last_attack.state_attack[i][2]<(v1+v2)*v3){
        last_attack.state_attack[i][0]=v1;
        last_attack.state_attack[i][1]=v2;
        last_attack.state_attack[i][2]=v3;
    }
}

void PetElfFighting::GZhuoShao(Attack &last_attack,int v1,int v2,int v3)
{//伤害比例，伤害
    int i=ZHUOSHAO;
    if(last_attack.state_attack[i][2]==0||(last_attack.state_attack[i][0]*12+last_attack.state_attack[i][1])*last_attack.state_attack[i][2]<(v1*12+v2)*v3){
        last_attack.state_attack[i][0]=v1;
        last_attack.state_attack[i][1]=v2;
        last_attack.state_attack[i][2]=v3;
    }
}

void PetElfFighting::GBingDong(Attack &last_attack,int v1,int v2,int v3)
{//伤害，力量降低
    int i=BINGDONG;
    if(last_attack.state_attack[i][2]<v3||(((last_attack.state_attack[i][0]+last_attack.state_attack[i][1])<(v1+v2))&&v3==last_attack.state_attack[i][2])){
        last_attack.state_attack[i][0]=v1;
        last_attack.state_attack[i][1]=v2;
        last_attack.state_attack[i][2]=v3;
    }
}

void PetElfFighting::GGanDian(Attack &last_attack,int v1,int v2,int v3)
{//伤害比例，普攻后受到伤害
    int i=GANDIAN;
    if(last_attack.state_attack[i][2]==0||(last_attack.state_attack[i][0]+last_attack.state_attack[i][1])*last_attack.state_attack[i][2]<(v1+v2)*v3){
        last_attack.state_attack[i][0]=v1;
        last_attack.state_attack[i][1]=v2;
        last_attack.state_attack[i][2]=v3;
    }
}

void PetElfFighting::GBaoZao(Attack &last_attack,int v1,int v2,int v3)
{//主动技能释放概率降低，是否禁止被动技能
    int i=BAOZAO;
    if(last_attack.state_attack[i][2]==0||(last_attack.state_attack[i][0]+last_attack.state_attack[i][1]*100)*last_attack.state_attack[i][2]<(v1+v2*100)*v3){
        last_attack.state_attack[i][0]=v1;
        last_attack.state_attack[i][1]=v2;
        last_attack.state_attack[i][2]=v3;
    }
}

void PetElfFighting::GXuanYun(Attack &last_attack,int v1,int v2,int v3)
{//护甲降低，是否无视免疫
    int i=XUANYUN;
    if(last_attack.state_attack[i][2]==0||(last_attack.state_attack[i][0]+last_attack.state_attack[i][1]*200)*last_attack.state_attack[i][2]<(v1+v2*200)*v3){
        last_attack.state_attack[i][0]=v1;
        last_attack.state_attack[i][1]=v2;
        last_attack.state_attack[i][2]=v3;
    }
}

void PetElfFighting::GJinGu(Attack &last_attack,int v1,int v2,int v3)
{//禁锢普攻或主动0/1，是否驱散有利分析
    int i=JINGU;
    if(last_attack.state_attack[i][2]==0||(last_attack.state_attack[i][1]*2+1)*last_attack.state_attack[i][2]<(v2*2+1)*v3){
        last_attack.state_attack[i][0]=v1;
        last_attack.state_attack[i][1]=v2;
        last_attack.state_attack[i][2]=v3;
    }
}

void PetElfFighting::GRuoHua(Attack &last_attack,int v1,int v2,int v3)
{//防御降低，力量降低
    int i=RUOHUA;
    if(last_attack.state_attack[i][2]==0||(last_attack.state_attack[i][0]+last_attack.state_attack[i][1])*last_attack.state_attack[i][2]<(v1+v2)*v3){
        last_attack.state_attack[i][0]=v1;
        last_attack.state_attack[i][1]=v2;
        last_attack.state_attack[i][2]=v3;
    }
}

void PetElfFighting::GYouYu(Attack &last_attack,int v1,int v2,int v3)
{//敏捷降低，是否消除暴击
    int i=YOUYU;
    if(last_attack.state_attack[i][2]==0||(last_attack.state_attack[i][0]+last_attack.state_attack[i][1]*20)*last_attack.state_attack[i][2]<(v1+v2*20)*v3){
        last_attack.state_attack[i][0]=v1;
        last_attack.state_attack[i][1]=v2;
        last_attack.state_attack[i][2]=v3;
    }
}

void PetElfFighting::GHuDun(int v1,int v2,int v3)
{//伤害降低比例，伤害吸收量
    int i=HUDUN;
    if(state_fighting[i][2]==0||(state_fighting[i][0]*2+state_fighting[i][1])*state_fighting[i][2]<(v1*2+v2)*v3){
        state_fighting[i][0]=v1;
        state_fighting[i][1]=v2;
        state_fighting[i][2]=v3;
        QString s=QString::number(v1);
        QString s1=QString::number(v2);
        g_message=g_message+"\n"+name+"进入了护盾状态，受到伤害减少"+s+"%，可以吸收"+s1+"点伤害！";
    }
}

void PetElfFighting::GFanShang(int v1,int v2,int v3)
{//反伤比例，反伤值
    int i=FANSHANG;
    if(state_fighting[i][2]==0||(state_fighting[i][0]*2+state_fighting[i][1])*state_fighting[i][2]<(v1*2+v2)*v3){
        state_fighting[i][0]=v1;
        state_fighting[i][1]=v2;
        state_fighting[i][2]=v3;
        QString s=QString::number(v1);
        QString s1=QString::number(v2);
        g_message=g_message+"\n"+name+"进入了反伤状态，反弹受到伤害的"+s+"%加"+s1+"点伤害！";
    }
}

void PetElfFighting::GMianYi(int v1,int v2,int v3)
{//元素降低比例，叶和黑暗伤害降低比例
    int i=MIANYI;
    if(state_fighting[i][2]==0||(state_fighting[i][0]+state_fighting[i][1])*state_fighting[i][2]<(v1+v2)*v3){
        state_fighting[i][0]=v1;
        state_fighting[i][1]=v2;
        state_fighting[i][2]=v3;
        for(int j=0;j<ALLSTATE;j++){
            if(j==ZHONGDU||j==ZHUOSHAO||j==BINGDONG||j==GANDIAN||j==BAOZAO||j==XUANYUN||j==JINGU||j==RUOHUA||j==YOUYU){
                state_fighting[j][0]=0;
                state_fighting[j][1]=0;
                state_fighting[j][2]=0;
            }
        }
        Calculate();
        QString s=QString::number(v1);
        QString s1=QString::number(v2);
        g_message=g_message+"\n"+name+"进入了免疫状态，免疫一切不良状态，受到冰，火，雷属性伤害减少"+s+"%，受到叶和暗属性伤害减少"+s1+"%！";
    }
}

void PetElfFighting::GXingFen(int v1,int v2,int v3)
{//敏捷增加，暴击率增加
    int i=XINGFEN;
    if(state_fighting[i][2]==0||(state_fighting[i][0]+state_fighting[i][1])*state_fighting[i][2]<(v1+v2)*v3){
        agility-=state_fighting[i][0];
        cri_rate-=state_fighting[i][1];
        state_fighting[i][0]=v1;
        state_fighting[i][1]=v2;
        state_fighting[i][2]=v3;
        agility+=state_fighting[i][0];
        cri_rate+=state_fighting[i][1];
        QString s=QString::number(v1);
        QString s1=QString::number(v2);
        g_message=g_message+"\n"+name+"进入了兴奋状态，敏捷增加"+s+"，暴击率变为"+s1+"！";
    }
}

void PetElfFighting::GGuiBi(int v1,int v2,int v3)
{//闪避加成，免疫伤害次数
    int i=GUIBI;
    dodge_rate-=state_fighting[i][0];
    if(state_fighting[i][2]==0||(state_fighting[i][0]+state_fighting[i][1]*12)*state_fighting[i][2]<(v1+v2*12)*v3){
        dodge_rate-=state_fighting[i][0];
        state_fighting[i][0]=v1;
        state_fighting[i][1]=v2;
        state_fighting[i][2]=v3;
        dodge_rate+=state_fighting[i][0];
        if(dodge_rate>100)
            dodge_rate=100;
        QString s=QString::number(v1);
        QString s1=QString::number(v2);
        g_message=g_message+"\n"+name+"进入了规避状态，闪避率增加了"+s+"%，可以规避"+s1+"次伤害！";
    }
}


void PetElfFighting::GQinLve(int v1,int v2,int v3)
{//力量增加，元素变化
    int i=QINLVE;
    if(state_fighting[i][2]==0||state_fighting[i][0]*state_fighting[i][2]<v1*v3){
        power-=state_fighting[i][0];
        state_fighting[i][0]=v1;
        state_fighting[i][1]=v2;
        state_fighting[i][2]=v3;
        power+=state_fighting[i][0];
        element=(PElement)state_fighting[i][1];
        QString s;
        QString s1=QString::number(v1);
        s=g_Str_element[state_fighting[i][1]];
        g_message=g_message+"\n"+name+"进入了侵略状态，主要元素变为"+s+",力量提升了"+s1+"！";
    }
}

void PetElfFighting::GZhuanZhu(int v1,int v2,int v3)
{//生命恢复量，防御增加量
    int i=ZHUANZHU;
    if(state_fighting[i][2]==0||(state_fighting[i][0]+state_fighting[i][1])*state_fighting[i][2]<(v1+v2)*v3){
        defence-=state_fighting[i][1];
        state_fighting[i][0]=v1;
        state_fighting[i][1]=v2;
        state_fighting[i][2]=v3;
        life+=state_fighting[i][0];
        if(life>life_back)
            life=life_back;
        defence+=state_fighting[i][1];
        QString s=QString::number(v1);
        QString s1=QString::number(v2);
        g_message=g_message+"\n"+name+"进入了专注状态，每回合恢复"+s+"点生命，防御提升了"+s1+"！";
    }
}

void PetElfFighting::GShiXve(int v1, int v2, int v3)
{//增加吸血，每回合扣血
    int i=SHIXVE;
    if(state_fighting[i][2]==0||(state_fighting[i][0]*power_back-state_fighting[i][1]*life)*state_fighting[i][2]<(v1*power_back-v2*life)*v3){
        state_fighting[i][0]=v1;
        state_fighting[i][1]=v2;
        state_fighting[i][2]=v3;
        QString s=QString::number(v1);
        QString s1=QString::number(v2);
        g_message=g_message+"\n"+name+"进入了嗜血状态，增加"+s+"%的吸血，但是每回合损失"+s1+"点生命！";
    }
}

void PetElfFighting::Refresh(Attack &last_attack)
{
    QString s;
    QString s1;
    for(int i=0;i<ALLSTATE;i++){
        switch(i){
        case ZHONGDU:{//伤害，敏捷降低
            if(last_attack.state_attack[i][2]!=0&&(last_attack.state_attack[i][0]+last_attack.state_attack[i][1])*last_attack.state_attack[i][2]>(state_fighting[i][0]+state_fighting[i][1])*state_fighting[i][2]){
                agility+=state_fighting[i][1];
                state_fighting[i][0]=last_attack.state_attack[i][0];
                state_fighting[i][1]=last_attack.state_attack[i][1];
                state_fighting[i][2]=last_attack.state_attack[i][2];
                s.setNum(state_fighting[i][1]);
                agility-=state_fighting[i][1];
                if(agility<10)
                    agility=10;
                g_message=g_message+"\n"+name+"陷入了中毒状态，敏捷降低了"+s+"！";
            }
            break;
        }
        case ZHUOSHAO:{//伤害比例，伤害
            if(last_attack.state_attack[i][2]!=0&&(last_attack.state_attack[i][0]*12+last_attack.state_attack[i][1])*last_attack.state_attack[i][2]>(state_fighting[i][0]*12+state_fighting[i][1])*state_fighting[i][2]){
                state_fighting[i][0]=last_attack.state_attack[i][0];
                state_fighting[i][1]=last_attack.state_attack[i][1];
                state_fighting[i][2]=last_attack.state_attack[i][2];
                g_message=g_message+"\n"+name+"陷入了灼烧状态！";
            }
            break;
        }
        case BINGDONG:{//伤害，力量降低
            if(last_attack.state_attack[i][2]>state_fighting[i][2]||((last_attack.state_attack[i][0]+last_attack.state_attack[i][1])>(state_fighting[i][0]+state_fighting[i][1])&&last_attack.state_attack[i][2]==state_fighting[i][2])){
                power+=state_fighting[i][0];
                state_fighting[i][0]=last_attack.state_attack[i][0];
                state_fighting[i][1]=last_attack.state_attack[i][1];
                state_fighting[i][2]=last_attack.state_attack[i][2];
                s.setNum(state_fighting[i][1]);
                power-=state_fighting[i][1];
                if(power<0)
                    power=0;
                probability_attack=0;
                g_message=g_message+"\n"+name+"陷入了冰冻状态，无法普通攻击，力量降低了"+s+"！";
            }
            break;
        }
        case GANDIAN:{//受到雷电伤害增加，释放主动技能受雷电伤害
            if(last_attack.state_attack[i][2]!=0&&(last_attack.state_attack[i][0]+last_attack.state_attack[i][1])*last_attack.state_attack[i][2]>(state_fighting[i][0]+state_fighting[i][1])*state_fighting[i][2]){
                state_fighting[i][0]=last_attack.state_attack[i][0];
                state_fighting[i][1]=last_attack.state_attack[i][1];
                state_fighting[i][2]=last_attack.state_attack[i][2];
                s.setNum(state_fighting[i][0]);
                g_message=g_message+"\n"+name+"陷入了感电状态，受到雷电伤害增加"+s+"%！";
            }
            break;
        }
        case BAOZAO:{//主动技能释放概率降低，是否禁止被动技能
            if(last_attack.state_attack[i][2]!=0&&(last_attack.state_attack[i][0]+last_attack.state_attack[i][1]*100)*last_attack.state_attack[i][2]>(state_fighting[i][0]+state_fighting[i][1]*100)*state_fighting[i][2]){
                probability_initialtive+=state_fighting[i][0];
                state_fighting[i][0]=last_attack.state_attack[i][0];
                state_fighting[i][1]=last_attack.state_attack[i][1];
                state_fighting[i][2]=last_attack.state_attack[i][2];
                s.setNum(state_fighting[i][0]);
                probability_initialtive-=state_fighting[i][0];
                if(probability_initialtive<0)
                    probability_initialtive=0;
                if(state_fighting[i][1]==1){
                    probability_passitive=0;
                    g_message=g_message+"\n"+name+"陷入了暴躁状态，释放主动技能的概率降低了"+s+"%，并且无法使用被动技能！";
                }
                else {
                    g_message=g_message+"\n"+name+"陷入了暴躁状态，释放主动技能的概率降低了"+s+"%！";
                }
            }
            break;
        }
        case XUANYUN:{//护甲降低，是否破除免疫
            if(last_attack.state_attack[i][2]!=0&&(last_attack.state_attack[i][0]+last_attack.state_attack[i][1]*200)*last_attack.state_attack[i][2]>(state_fighting[i][0]+state_fighting[i][1]*200)*state_fighting[i][2]){
                defence+=state_fighting[i][0];
                state_fighting[i][0]=last_attack.state_attack[i][0];
                state_fighting[i][1]=last_attack.state_attack[i][1];
                state_fighting[i][2]=last_attack.state_attack[i][2];
                s.setNum(state_fighting[i][0]);
                defence-=state_fighting[i][0];
                probability_attack=0;
                probability_initialtive=0;
                probability_passitive=0;
                g_message=g_message+"\n"+name+"陷入了眩晕状态，无法行动，防御降低了"+s+"！";
            }
            break;
        }
        case JINGU:{//禁锢普攻或主动0/1，是否驱散有利状态
            if(last_attack.state_attack[i][2]!=0&&(1+last_attack.state_attack[i][1]*2)*last_attack.state_attack[i][2]>(1+state_fighting[i][1]*2)*state_fighting[i][2]){
                state_fighting[i][0]=last_attack.state_attack[i][0];
                state_fighting[i][1]=last_attack.state_attack[i][1];
                state_fighting[i][2]=last_attack.state_attack[i][2];
                if(state_fighting[i][1]==1){
                    for(int j=0;j<ALLSTATE;j++){
                        if(j==HUDUN||j==FANSHANG||j==MIANYI||j==XINGFEN||j==GUIBI||j==QINLVE||j==ZHUANZHU||j==SHIXVE){
                            state_fighting[j][0]=0;
                            state_fighting[j][1]=0;
                            state_fighting[j][2]=0;
                        }
                    }
                    Calculate();
                    g_message=g_message+"\n"+name+"陷入了禁锢状态，所有有利效果被驱散了！";
                }
                if(state_fighting[i][0]==0){
                    probability_attack=0;
                    g_message=g_message+"\n"+name+"陷入了禁锢状态，无法普通攻击！";
                }
                else{
                    probability_initialtive=0;
                    g_message=g_message+"\n"+name+"陷入了禁锢状态，无法释放主动技能！";
                }
            }
            break;
        }
        case RUOHUA:{//防御降低，力量降低
            if(last_attack.state_attack[i][2]!=0&&(last_attack.state_attack[i][0]+last_attack.state_attack[i][1])*last_attack.state_attack[i][2]>(state_fighting[i][0]+state_fighting[i][1])*state_fighting[i][2]){
                defence+=state_fighting[i][0];
                power+=state_fighting[i][1];
                state_fighting[i][0]=last_attack.state_attack[i][0];
                state_fighting[i][1]=last_attack.state_attack[i][1];
                state_fighting[i][2]=last_attack.state_attack[i][2];
                s.setNum(state_fighting[i][0]);
                s1.setNum(state_fighting[i][1]);
                defence-=state_fighting[i][0];
                power-=state_fighting[i][1];
                if(power<0)
                    power=0;
                if(defence+DEFENCECONST<0)
                    defence=-DEFENCECONST+1;
                g_message=g_message+"\n"+name+"陷入了弱化状态，防御降低了"+s+"，力量降低了"+s1+"！";
            }
            break;
        }
        case YOUYU:{//敏捷降低，是否消除暴击
            if(last_attack.state_attack[i][2]!=0&&(last_attack.state_attack[i][0]+last_attack.state_attack[i][1]*20)*last_attack.state_attack[i][2]>(state_fighting[i][0]+state_fighting[i][1]*20)*state_fighting[i][2]){
                agility+=state_fighting[i][0];
                state_fighting[i][0]=last_attack.state_attack[i][0];
                state_fighting[i][1]=last_attack.state_attack[i][1];
                state_fighting[i][2]=last_attack.state_attack[i][2];
                s.setNum(state_fighting[i][0]);
                agility-=state_fighting[i][0];
                if(agility<10)
                    agility=10;
                if(state_fighting[i][1]==0){
                    g_message=g_message+"\n"+name+"陷入了犹豫状态，敏捷降低了"+s+"！";
                }
                else{
                    g_message=g_message+"\n"+name+"陷入了犹豫状态，敏捷降低了"+s+",并且无法暴击！";
                    cri_rate=0;
                }
            }
            break;
        }
        default:
            break;
        }
    }
}

void PetElfFighting::RoundBegin()//回合开始判定一些不良状态
{
    if(state_fighting[MIANYI][2]>0){//免疫状态直接去除不良状态
        for(int j=0;j<ALLSTATE;j++){
            if(j==ZHONGDU||j==ZHUOSHAO||j==BINGDONG||j==GANDIAN||j==BAOZAO||j==XUANYUN||j==JINGU||j==RUOHUA||j==YOUYU){
                state_fighting[j][0]=0;
                state_fighting[j][1]=0;
                state_fighting[j][2]=0;
            }
        }
    }
    Calculate();//刷新属性值
    QString s;
    if(state_fighting[ZHUANZHU][0]>0){
        s.setNum(state_fighting[ZHUANZHU][0]);
        g_message=g_message+"\n"+name+"处于专注状态,恢复"+s+"点生命！";
        life+=state_fighting[ZHUANZHU][0];
        if(life>life_back)
            life=life_back;
    }

    if(state_fighting[ZHONGDU][0]>0){
        Attack a;
        a.happen=1;
        a.from=1;
        a.ignore=1;
        a.ele_damage[LEAF]=state_fighting[ZHONGDU][0];
        g_message=g_message+"\n"+name+"处于中毒状态！";
        Injured(a);
    }
    if(state_fighting[ZHUOSHAO][2]>0&&life!=0){
        Attack a;
        a.happen=1;
        a.from=1;
        a.ignore=1;
        a.ele_damage[FLAME]=state_fighting[ZHUOSHAO][1];
        s.setNum(state_fighting[ZHUOSHAO][0]);
        g_message=g_message+"\n"+name+"处于灼烧状态，直接损失"+s+"%的最大生命值！";
        life-=life_back*state_fighting[ZHUOSHAO][0]/100.0;
        if(life<0)
            life=0;
        Injured(a);
    }
    if(state_fighting[BINGDONG][0]>0&&life!=0){
        Attack a;
        a.happen=1;
        a.from=1;
        a.ignore=1;
        a.ele_damage[ICE]=state_fighting[BINGDONG][0];
        g_message=g_message+"\n"+name+"处于冰冻状态！";
        Injured(a);
    }
    if(state_fighting[SHIXVE][1]>0&&life!=0){
        s.setNum(state_fighting[SHIXVE][1]);
        g_message=g_message+"\n"+name+"处于嗜血状态，直接损失"+s+"点生命！";
        life-=state_fighting[SHIXVE][1];
        if(life==0)
            life=1;
    }
}

void PetElfFighting::RoundOver()//回合结束，判断状态是否消失
{
    for(int i=0;i<ALLSTATE;i++){
        if(state_fighting[i][2]>0){
            state_fighting[i][2]--;
            if(state_fighting[i][2]==0){
                state_fighting[i][0]=0;
                state_fighting[i][1]=0;
                state_fighting[i][2]=0;
            }
        }
    }
    Calculate();
}

void PetElfFighting::Calculate()//根据状态计算属性值
{
    element=ele_back;
    power=power_back;
    cri_rate=cri_back;
    defence=defence_back;
    agility=agility_back;
    dodge_rate=dofge_back;
    probability_attack=100;//普攻概率
    probability_initialtive=100;//记录主动技能释放概率
    probability_passitive=100;//记录被动技能释放概率
    power+=state_fighting[QINLVE][0]-state_fighting[BINGDONG][1]-state_fighting[RUOHUA][1];
    if(power<0)
        power=0;
    defence+=state_fighting[ZHUANZHU][1]-state_fighting[XUANYUN][0]-state_fighting[RUOHUA][0];
    if(defence+DEFENCECONST<0)
        defence=-DEFENCECONST+1;
    agility+=state_fighting[XINGFEN][0]-state_fighting[YOUYU][0]-state_fighting[ZHONGDU][1];
    if(agility<10)
        agility=10;
    cri_rate+=state_fighting[XINGFEN][1];
    if(state_fighting[YOUYU][1]==1)
        cri_rate=0;
    dodge_rate+=state_fighting[GUIBI][0];
    if(dodge_rate>100)
        dodge_rate=100;
    if(state_fighting[XUANYUN][2]>0){
        probability_attack=0;//普攻概率
        probability_initialtive=0;//记录主动技能释放概率
        probability_passitive=0;//记录被动技能释放概率
    }
    else {
        if(state_fighting[JINGU][0]==1)
            probability_initialtive=0;
        else {
            probability_initialtive-=state_fighting[BAOZAO][0];
            if(probability_initialtive<0)
                probability_initialtive=0;
        }
        if(state_fighting[BAOZAO][1]==1)
            probability_passitive=0;
        if(state_fighting[JINGU][2]>0&&state_fighting[JINGU][0]==0)
            probability_attack=0;
        if(state_fighting[BINGDONG][2]>0)
            probability_attack=0;
    }
    if(state_fighting[QINLVE][2]>0){
        element=(PElement)state_fighting[QINLVE][1];
    }
}

int PetElfFighting::CriOrNot()//计算暴击伤害
{
    int i=RANDOM(100);
    if(i<=cri_rate){
        g_message=g_message+"\n"+name+"暴击了！！！";
        return power*cri_damage;
    }
    else return power;
}

QString PetElfFighting::ShowState()//战斗时显示状态信息
{
    QString s=name;
    QString s1;
    s=s+'\n'+"生命值:"+s1.setNum(life);
    s=s+'\n'+"力量:"+s1.setNum(power);
    s=s+"\n防御:"+s1.setNum(defence);
    s=s+"\n敏捷:"+s1.setNum(agility)+"\n精灵元素:";
    s1=g_Str_element[element];
    s=s+s1;
    s=s+"\n状态:";
    for(int i=0;i<ALLSTATE;i++){
        if(state_fighting[i][2]>0){
            s=s+g_Str_state[i]+" ";
        }
    }
    return s;
}





