#ifndef ATTACK_H
#define ATTACK_H
#include "QString.h"
#include "global.h"

class Attack//精灵产生的攻击
{
public:
    bool from;//伤害来源0敌人，1无来源
    bool happen;//1伤害发生了，0伤害没有发生
    bool ignore;//1无视闪避，0不无视闪避
    bool is_back;//1是反伤的伤害，0不是反伤伤害

    int blood_sucking;//吸血反馈值
    int ele_damage[ALLELEMENT];//各种元素伤害
    int state_attack[ALLSTATE][3];//状态数组，每种状态三个参数
    int special_effects;//用于战斗时显示特效

    Attack();
    int Calculate(PElement);//根据属性克制计算伤害
    void Clear();//清空
    void operator =(Attack a);

};

#endif // ATTACK_H
