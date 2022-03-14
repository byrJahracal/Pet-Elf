#ifndef PETELFFIGHTING_H
#define PETELFFIGHTING_H
#include "PetElf.h"
//战场上小精灵类，包含战斗时的状态等信息，继承自PetElf
class PetElfFighting : public PetElf
{
public:
    int cri_back;
    int life_back;
    int power_back;
    int defence_back;
    int agility_back;
    int dofge_back;
    PElement ele_back;//Back表示战斗时精灵属性的基础值，精灵处于不同状态时在基础值上加减，状态结束后回归基础值
    int round;//回合数
    int probability_attack;//普攻概率
    int probability_initialtive;//记录主动技能释放概率
    int probability_passitive;//记录被动技能释放概率
    FightTime judge_time[ALLATTACKTYPE];//记录天赋和两个技能的释放时机
    SkillKind skill_kind[ALLATTACKTYPE];//记录天赋和两个技能的技能种类
    int state_fighting[ALLSTATE][3];//记录状态，三个参数
    Attack return_attack;//反伤
    Attack (PetElfFighting::*Function1)(int);//技能一函数
    Attack (PetElfFighting::*Function2)(int);//技能二函数

    PetElfFighting();
    PetElfFighting(PetElf your_elf);
    PetElfFighting(PetNumber your_elf,SkillT s1,SkillT s2, int l,int l1,int l2);
    virtual Attack SimpleAttack();//普通攻击
    virtual Attack Talent();//天赋技能
    Attack Injured(Attack attack);//受伤函数
    void ChooseFunction();//初始化两个技能对应的函数

    Attack UseSkill1(){//释放一技能
        return (this->*Function1)(sk1_level);
    }

    Attack UseSkill2(){//释放二技能
        return (this->*Function2)(sk2_level);
    }

    Attack FlameAttack(int l);
    Attack ThunderAttack(int l);
    Attack IceAttack(int l);
    Attack LEAFAttack(int l);
    Attack DarkAttack(int l);
    Attack XiLi(int l);
    Attack BuQuYiZhi(int l);
    Attack XianXveKeWang(int l);
    Attack XianQuTuJi(int l);//精灵的可学习的技能

    void JGanDian(Attack& attack,FightTime time);
    void JHuDun(int& damage);
    Attack JFanShang(Attack attack,int damage);
    void JMianYi(Attack& attack);
    int JGuiBi();//判定规避状态
    void JShiXve(int blood);//J代表Judge，J后跟一个状态，表示状态生效时的判断函数

    void GZhongDu(Attack &last_attack,int v1,int v2,int v3);
    void GZhuoShao(Attack &last_attack,int v1,int v2,int v3);
    void GBingDong(Attack &last_attack,int v1,int v2,int v3);
    void GGanDian(Attack &last_attack,int v1,int v2,int v3);
    void GBaoZao(Attack &last_attack,int v1,int v2,int v3);
    void GXuanYun(Attack &last_attack,int v1,int v2,int v3);
    void GJinGu(Attack &last_attack,int v1,int v2,int v3);
    void GRuoHua(Attack &last_attack,int v1,int v2,int v3);
    void GYouYu(Attack &last_attack,int v1,int v2,int v3);//G表示Go以上函数表示给last_attack加入不良状态信息，传给对手
    void GHuDun(int v1,int v2,int v3);
    void GFanShang(int v1,int v2,int v3);
    void GMianYi(int v1,int v2,int v3);//进入免疫状态
    void GXingFen(int v1,int v2,int v3);
    void GGuiBi(int v1,int v2,int v3);
    void GQinLve(int v1,int v2,int v3);
    void GZhuanZhu(int v1,int v2,int v3);
    void GShiXve(int v1,int v2,int v3);//以上函数表示让自己进入有利状态
    //所有状态函数的参数为三个，第三个参数代表持续回合，前两个间具体函数定义

    void Refresh(Attack &last_attack);//根据受到攻击中的状态信息更新精灵状态和属性
    void RoundBegin();//回合开始准备
    void RoundOver();//回合结束更新状态
    void Calculate();//有状态变化时计算精灵属性值
    int CriOrNot();//判断是否暴击，返回伤害值
    QString ShowState();//用于战斗界面显示精灵信息
};

#endif // PETELFFIGHTING_H
