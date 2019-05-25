#ifndef TOWER_H
#define TOWER_H
#include "rpgobj.h"
#include "effect.h"
#include "monster.h"
#include <QList>

enum direct{
    t,
    l,
    b,
    r,
    lt,
    lb,
    rt,
    rb
};

class Tower: public RPGObj{
public:
    Tower(){}
    ~Tower(){}
    int Redirect();
    void Attack(int aim_);
    void Recover();
    void ListUpdate();
    bool attackable(double x, double y);
    static int getNum(){return Tower::count_;}
    static void addNum(){Tower::count_++;}
    int getAim(){return this->attack_aim_;}
    void addMymonster(Monster *p){this->mymonster_.push_back(p);}
    void setRange(double n){this->range_ = n;}
    void setAttackAim(int n){this->attack_aim_ = n;}
    bool haveMonsterCode(int code);
    void updateMyTower();
    friend void setICON(Tower &rpgobj, objstate allo_objstate){setTypeState(rpgobj._icon, allo_objstate);}
private:
    direct direct_;
    int attack_aim_;
    QList<Monster *> mymonster_;
    static int count_;
    double range_;  //考虑不同的值2.5一个九宫格，5两个九宫格
};

#endif // TOWER_H
