#ifndef GUARD_H
#define GUARD_H
#include "rpgobj.h"
#include "monster.h"
#include <iostream>

class Guard: public RPGObj
{
public:
    Guard(){Level = 1;}
    ~Guard(){}
    double getNextX(int direction);
    double getNextY(int direction);
    void Attack(int aim_);
    void move(int direction, double steps=0.5);
        //direction =1,2,3,4 for 上下左右
private:
    int Level;
    int attack_aim_;
};

#endif // GUARD_H
