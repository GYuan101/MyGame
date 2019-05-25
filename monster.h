#ifndef MONSTER_H
#define MONSTER_H
#include "rpgobj.h"

class Monster: public RPGObj{
public:
    Monster(){}
    ~Monster(){}
    void move();
    void Redirect(int d_);
    int ifErase();
    void Attack(int aim_);
    void setDist(int dist){this->dist_ = dist;}
    int getDist() const{return this->dist_;}
    int getCode() const{return this->code;}
    static int getLoss(){return loss_;}
    void setCode(int code_){this->code = code_;}
    static void addNum(){Monster::count_++;}
    static int getCount(){return Monster::count_;}
    friend void setICON(Monster &rpgobj, objstate allo_objstate){setTypeState(rpgobj._icon, allo_objstate);}
private:
    static int count_;
    static int loss_;
    int dist_;
    int code;
};

#endif // MONSTER_H
