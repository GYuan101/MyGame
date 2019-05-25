#include "tower.h"
#include "world.h"

int Tower::count_ = 0;

void Tower::ListUpdate(){
    //遍历，删除超出攻击范围或者死亡的
    QList<Monster *>::iterator i;
    double X_, Y_;
    i = mymonster_.begin();
    while(i != mymonster_.end()){
        if((*i)->getHealth() >= 0){
            X_ = (*i)->getPosX();
            Y_ = (*i)->getPosY();
            if(this->attackable(X_, Y_)){
                i++;
                continue;
            }
            else i = mymonster_.erase(i);
        }
        else i = mymonster_.erase(i);
    }
}

int Tower::Redirect(){
    //当前monster死亡或者脱离攻击区域的时候进行重定位
    //找到当前链表之中length最大的
    int minindex = -1;
    if(this->mymonster_.size() != 0){
        QList<Monster *>::iterator i;
        int minlength = 1000;
        minindex = 1000;
        for (i = mymonster_.begin(); i != mymonster_.end(); i++){
            if((*i)->getDist() < minlength){
                minlength = (*i)->getDist();
                minindex = i - mymonster_.begin();
            }
            else continue;
        }
        //根据相对位置判断redirect的方向
        double X_ = mymonster_[minindex]->getPosX();
        double Y_ = mymonster_[minindex]->getPosY();
        objstate aimState_ = objstate(-1);
        objtype type_ = this->getObjType();
        if(X_ == this->getPosX() && Y_ < this->getPosY()){
            this->direct_ = t;
            switch(type_){
            case Charmander1:
                aimState_ = Charmander1_lt_0;
                break;
            case Charmander2:
                aimState_ = Charmander2_t_0;
                break;
            case Charmander3:
                aimState_ = Charmander3_t_0;
                break;
            default:
                cout << "Wrong Type!" << endl;
                break;
            }
        }
        else if(X_ == this->getPosX() && Y_ > this->getPosY()){
            this->direct_ = b;
            switch(type_){
            case Charmander1:
                aimState_ = Charmander1_rb_0;
                break;
            case Charmander2:
                aimState_ = Charmander2_b_0;
                break;
            case Charmander3:
                aimState_ = Charmander3_b_0;
                break;
            default:
                cout << "Wrong Type!" << endl;
                break;
            }
        }
        else if(X_ < this->getPosX() && Y_ == this->getPosY()){
            this->direct_ = l;
            switch(type_){
            case Charmander1:
                aimState_ = Charmander1_lt_0;
                break;
            case Charmander2:
                aimState_ = Charmander2_l_0;
                break;
            case Charmander3:
                aimState_ = Charmander3_l_0;
                break;
            default:
                cout << "Wrong Type!" << endl;
                break;
            }
        }
        else if(X_ > this->getPosX() && Y_ == this->getPosY()){
            this->direct_ = r;
            switch(type_){
            case Charmander1:
                aimState_ = Charmander1_rb_0;
                break;
            case Charmander2:
                aimState_ = Charmander2_r_0;
                break;
            case Charmander3:
                aimState_ = Charmander3_r_0;
                break;
            default:
                cout << "Wrong Type!" << endl;
                break;
            }
        }
        else if(X_ < this->getPosX() && Y_ < this->getPosY()){
            this->direct_ = lt;
            switch(type_){
            case Charmander1:
                aimState_ = Charmander1_lt_0;
                break;
            case Charmander2:
                aimState_ = Charmander2_lt_0;
                break;
            case Charmander3:
                aimState_ = Charmander3_lt_0;
                break;
            default:
                cout << "Wrong Type!" << endl;
                break;
            }
        }
        else if(X_ < this->getPosX() && Y_ > this->getPosY()){
            this->direct_ = lb;
            switch(type_){
            case Charmander1:
                aimState_ = Charmander1_rb_0;
                break;
            case Charmander2:
                aimState_ = Charmander2_lb_0;
                break;
            case Charmander3:
                aimState_ = Charmander3_lb_0;
                break;
            default:
                cout << "Wrong Type!" << endl;
                break;
            }
        }
        else if(X_ > this->getPosX() && Y_ < this->getPosY()){
            this->direct_ = rt;
            switch(type_){
            case Charmander1:
                aimState_ = Charmander1_lt_0;
                break;
            case Charmander2:
                aimState_ = Charmander2_rt_0;
                break;
            case Charmander3:
                aimState_ = Charmander3_rt_0;
                break;
            default:
                cout << "Wrong Type!" << endl;
                break;
            }
        }
        else if(X_ > this->getPosX() && Y_ > this->getPosY()){
            this->direct_ = rb;
            switch(type_){
            case Charmander1:
                aimState_ = Charmander1_rb_0;
                break;
            case Charmander2:
                aimState_ = Charmander2_rb_0;
                break;
            case Charmander3:
                aimState_ = Charmander3_rb_0;
                break;
            default:
                cout << "Wrong Type!" << endl;
                break;
            }
        }
        //考虑只更新pic和icon，icon赋值重载了，不知道这个QImage行不行
        this->_icon = World::getpic(aimState_).getIcon();
        this->_pic = World::getpic(aimState_).getImage();
    }
    return minindex;
}

bool Tower::haveMonsterCode(int code){
    QList<Monster *>::iterator i;
    i = mymonster_.begin();
    while(i != mymonster_.end()){
        if(code == (*i)->getCode())
                return true;
        else i++;
    }
    return false;
}

bool Tower::attackable(double x, double y){
    if(abs(this->getPosX() - x) <= this->range_ && abs(this->getPosY() - y) <= this->range_)
        return true;
    else return false;
}

void Tower::Attack(int aim_){
    //完成特效制作
    if(aim_ != -1){
        double Current_PosX = this->mymonster_[aim_]->getPosX();
        double Current_PosY = this->mymonster_[aim_]->getPosY();
        int Current_Health = this->mymonster_[aim_]->getHealth();
        objstate Current_State = this->getObjState();
        if(1){
            this->_icon = World::getpic(Current_State+1).getIcon();
            this->_pic = World::getpic(Current_State+1).getImage();
        }//show 0.2s
        this->mymonster_[aim_]->setHealth(Current_Health-this->getDamage());
        FireEffect fire = FireEffect(Fire1);
        fire.setPosX(Current_PosX);
        fire.setPosY(Current_PosY);
        World::initFireEffect(fire);
    }
}

void Tower::Recover(){
    if(this->getAim() != -1){
        objstate Current_State = this->getObjState();
        if(Current_State > 0){
            this->_icon = World::getpic(Current_State-1).getIcon();
            this->_pic = World::getpic(Current_State-1).getImage();
        }
    }
}

void Tower::updateMyTower(){
    objtype currentType = this->getObjType();
    //还要增加血量攻击力等
    switch(currentType){
    case Charmander1:
        this->_icon = World::getpic(Charmander2_b_0).getIcon();
        this->_pic = World::getpic(Charmander2_b_0).getImage();
        this->range_ += 2.5;
        this->setAttack(this->getDamage()+500);
        break;
    case Charmander2:
        this->_icon = World::getpic(Charmander3_b_0).getIcon();
        this->_pic = World::getpic(Charmander3_b_0).getImage();
        this->range_ += 2.5;
        this->setAttack(this->getDamage()+500);
        break;
    default:
        cout << "Cannot Upgrade!" << endl;
        break;
    }
}
