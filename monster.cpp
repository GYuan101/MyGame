#include "monster.h"
#include "world.h"

int Monster::loss_ = 0;
int Monster::count_ = 0;


void Monster::Redirect(int _d){
    //direction =1,2,3,4 for 上下左右
    //考虑重新生成
    objstate state_ = this->getObjState();
    objtype type_ = this->getObjType();
    string name_;
    int distance = this->getDist();
    switch(_d){
    case 1:
        //向上重定位
        switch (state_) {
        case Charmander2_r_0:
            state_ = Charmander2_t_0;
            name_ = "Charmander2_t_0";
            break;
        case Charmander3_r_0:
            state_ = Charmander3_t_0;
            name_ = "Charmander3_t_0";
            break;
        }
        break;
    case 3:
        //向下重定位
        switch (state_) {
        case Charmander2_t_0:
            state_ = Charmander2_l_0;
            name_ = "Charmander2_l_0";
            break;
        case Charmander3_t_0:
            state_ = Charmander3_l_0;
            name_ = "Charmander3_l_0";
            break;
        }
        break;
    case 4:
        //向右重定位
        switch (state_) {
        case Charmander2_b_0:
            state_ = Charmander2_r_0;
            name_ = "Charmander2_r_0";
            break;
        case Charmander3_b_0:
            state_ = Charmander3_r_0;
            name_ = "Charmander3_r_0";
            break;
        }
        break;
    default:
        cout << "Wrong Direction!" <<endl;
        break;
    }

    this->initObj(type_, state_, name_);
    setICON(*this, state_);
    this->setDist(distance);
}

void Monster::move(){
    //判断在哪条路上
    if(this->getPosX() == World::getRoute()[0].startX &&
       this->getPosY() < World::getRoute()[0].endY)
        //在Column1
        this->setPosY(this->getPosY() + 0.5);
    else if(this->getPosX() == World::getRoute()[1].startX &&
            this->getPosY() < World::getRoute()[1].endY)
        //在Column2
        this->setPosY(this->getPosY() + 0.5);
    else if(this->getPosX() == World::getRoute()[2].startX &&
            this->getPosY() < World::getRoute()[2].endY)
        //在Column3
        this->setPosY(this->getPosY() + 0.5);
    else if ((this->getPosX() == World::getRoute()[0].startX ||
              this->getPosX() == World::getRoute()[1].startX) &&
             this->getPosY() == World::getRoute()[0].endY) {
        //在Column1或Column2和Row1交点
        this->setPosX(this->getPosX() + 0.5);
        if(this->getObjState() != Charmander2_r_0 &&
                this->getObjState() != Charmander3_r_0)
            this->Redirect(4);
    }
    else if (this->getPosX() == World::getRoute()[2].startX &&
             this->getPosY() == World::getRoute()[2].endY) {
        //在Column3和Row2交点
        this->setPosX(this->getPosX() + 0.5);
        this->Redirect(4);
    }
    else if (this->getPosX() >= World::getRoute()[4].startX &&
             this->getPosX() < World::getRoute()[4].endX &&
             this->getPosY() == World::getRoute()[4].endY)
        //在Row1上
        this->setPosX(this->getPosX() + 0.5);
    else if (this->getPosX() >= World::getRoute()[5].startX &&
             this->getPosX() < World::getRoute()[5].endX &&
             this->getPosY() == World::getRoute()[5].endY)
        //在Row2上
        this->setPosX(this->getPosX() + 0.5);
    else if (this->getPosX() == World::getRoute()[3].endX &&
             (this->getPosY() == World::getRoute()[4].endY ||
             this->getPosY() == World::getRoute()[5].endY)) {
        //在Column4和Row1或Row2交点
        this->setPosY(this->getPosY() - 0.5);
        if(this->getObjState() != Charmander2_t_0 &&
           this->getObjState() != Charmander3_t_0)
            this->Redirect(1);
    }
    else if (this->getPosX() == World::getRoute()[3].endX &&
             this->getPosY() < World::getRoute()[3].startY &&
             this->getPosY() > World::getRoute()[3].endY)
        //在column4上
        this->setPosY(this->getPosY() - 0.5);
    else if (this->getPosX() == World::getRoute()[3].startX &&
             this->getPosY() == World::getRoute()[3].endY) {
        //在Column4和Row3交点
        this->setPosX(this->getPosX() - 0.5);
        this->Redirect(3);
    }
    else if (this->getPosX() > World::getRoute()[6].endX &&
             this->getPosX() < World::getRoute()[6].startX &&
             this->getPosY() == World::getRoute()[6].startY)
        //在Row3上
        this->setPosX(this->getPosX() - 0.5);
    else if (this->getPosX() == World::getRoute()[6].endX &&
             this->getPosY() == World::getRoute()[6].endY){
        //到达终点  还会发生什么呢？
        this->onErase();
    }
}

int Monster::ifErase(){
    if(this->getHealth() <= 0 || this->getDist() == 0){
        //this->count_--;
        cout << "Monster" << this->getCode()+1 << " Erased!" << endl;
        if(this->getDist() == 0){
            this->loss_++;
            cout << this->loss_ << "Monsters Survive!" << endl;
        }
        return this->getCode();
    }
    else return -1;
}

void Monster::Attack(int aim_){

}
