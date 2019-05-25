#include "guard.h"

//direction =1,2,3,4 for 上下左右
void Guard::move(int direction, double steps){
    switch (direction){
        case 1:
            this->_pos_y -= steps;
            break;
        case 2:
            this->_pos_y += steps;
            break;
        case 3:
            this->_pos_x -= steps;
            break;
        case 4:
            this->_pos_x += steps;
            break;
    }
}

double Guard::getNextX(int direction){
    switch (direction){
        case 1:
            return this->_pos_x;
        case 2:
           return this->_pos_x;
        case 3:
           return this->_pos_x-1;
        case 4:
           return this->_pos_x+1;
        default:
            cout << "Wrong direction!" << endl;
            return this->_pos_y;
    }
}

double Guard::getNextY(int direction){
    switch (direction){
        case 1:
            return this->_pos_y - 1;
        case 2:
           return this->_pos_y + 1;
        case 3:
           return this->_pos_y;
        case 4:
           return this->_pos_y;
        default:
            cout << "Wrong direction!" << endl;
            return this->_pos_y;
    }
}

void Guard::Attack(int aim_){

}
