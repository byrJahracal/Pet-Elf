#include "Attack.h"

Attack::Attack()
{
    from=0;//伤害来源0敌人，1无来源
    happen=0;//1伤害发生了，0伤害没有发生
    ignore=0;//1无视闪避，0不无视闪避
    is_back=0;//1是反伤的伤害，0不是反伤伤害
    special_effects=-1;

    blood_sucking=0;//吸血反馈值
    for(int i=0;i<ALLELEMENT;i++)
        ele_damage[i]=0;
    for(int i=0;i<ALLSTATE;i++){
        state_attack[i][0]=0;
        state_attack[i][1]=0;
        state_attack[i][2]=0;
    }
}

int Attack::Calculate(PElement pe)//属性克制计算伤害
{
    float r[ALLELEMENT];
    switch (pe) {
    case FLAME:
        r[FLAME]=1;
        r[THUNDER]=0.8;
        r[ICE]=1.2;
        r[LEAF]=0.9;
        r[DARK]=1.1;
        break;
    case THUNDER:
        r[FLAME]=1.2;
        r[THUNDER]=1;
        r[ICE]=0.8;
        r[LEAF]=0.9;
        r[DARK]=1.1;
        break;
    case ICE:
        r[FLAME]=0.8;
        r[THUNDER]=1.2;
        r[ICE]=1;
        r[LEAF]=0.9;
        r[DARK]=1.1;
        break;
    case LEAF:
        r[FLAME]=1.1;
        r[THUNDER]=1.1;
        r[ICE]=1.1;
        r[LEAF]=1;
        r[DARK]=0.7;
        break;
    case DARK:
        r[FLAME]=0.9;
        r[THUNDER]=0.9;
        r[ICE]=0.9;
        r[LEAF]=1.3;
        r[DARK]=1;
        break;
    default:
        break;
    }
    int sum=ele_damage[FLAME]*r[FLAME]+ele_damage[THUNDER]*r[THUNDER]+ele_damage[ICE]*r[ICE]+ele_damage[LEAF]*r[LEAF]+ele_damage[DARK]*r[DARK];
    return sum;
}

void Attack::Clear()
{
    from=0;//伤害来源0敌人，1无来源
    happen=0;//1伤害发生了，0伤害没有发生
    ignore=0;//1无视闪避，0不无视闪避
    is_back=0;//1是反伤的伤害，0不是反伤伤害
    special_effects=-1;

    blood_sucking=0;//吸血反馈值
    for(int i=0;i<ALLELEMENT;i++)
        ele_damage[i]=0;
    for(int i=0;i<ALLSTATE;i++){
        state_attack[i][0]=0;
        state_attack[i][1]=0;
        state_attack[i][2]=0;
    }
}

void Attack::operator =(Attack a)//赋值伤害包
{
    from=a.from;
    happen=a.happen;
    ignore=a.ignore;
    is_back=a.is_back;
    special_effects=a.special_effects;

    blood_sucking=a.blood_sucking;
    for(int i=0;i<ALLELEMENT;i++){
        ele_damage[i]=a.ele_damage[i];
    }
    for(int i=0;i<ALLSTATE;i++){
        state_attack[i][0]=a.state_attack[i][0];
        state_attack[i][1]=a.state_attack[i][1];
        state_attack[i][2]=a.state_attack[i][2];
    }
}
