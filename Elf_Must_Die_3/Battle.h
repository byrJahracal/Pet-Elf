#ifndef BATTLE_H
#define BATTLE_H
#include "FightingElf/AdvanceElf.h"
#include "QVariantList"

class Battle//战场类
{
public:
    Battle();
    PetElfFighting* elf1;//我方精灵
    PetElfFighting* elf2;//敌方精灵
    QString s;//通用Qstring
    Attack attack1;//我方攻击包
    Attack attack2;//敌方攻击包
    int turn1;//我方回合进度
    int turn2;//敌方回合进度
    int winner;//记录谁赢了
    FightTime state_time;//战斗时机，用于自动机控制
    StateSkill state_skill;//技能时机，用于自动机控制
    int state_period;//记录一次攻击的时机，用于自动机控制
    int head_period;//记录上一次state_period
    int state_turn;//记录回合信息，用于自动机控制
    StateSkill special_effects_skill;//记录特效是哪个技能发起的
    int special_effects_flag;
    QString special_effects_str;//记录特效信息

    void RandomElf(int elfi);//随机生成一个精灵
    void ChooseElf(int whitch,PetElf &p);//选择不同的构造函数生成不同的子类精灵
    StateWindow Fighting();//自动战斗
    void Prepare();//战前准备
    void EndJudge();//判断是否战斗结束
    void AutoState();//自动机自动转入下一状态
    void AutoAttack();//一次攻击的三个阶段自动跳转
    void AutoSkill();//天赋技能1技能2自动跳转
};

#endif // BATTLE_H
