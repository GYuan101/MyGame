#include "icon.h"
#include<iostream>

int ICON::GRID_SIZE = 64;

//可能暂时没用，考虑简化initobj
const char* ICON::names[36] =  {
    "Charmander1_rb_0",
    "Charmander1_rb_1",
    "Charmander1_lt_0",
    "Charmander1_lt_1",
    "Charmander2_b_0",
    "Charmander2_b_1",
    "Charmander2_t_0",
    "Charmander2_t_1",
    "Charmander2_l_0",
    "Charmander2_l_1",
    "Charmander2_r_0",
    "Charmander2_r_1",
    "Charmander2_lb_0",
    "Charmander2_lb_1",
    "Charmander2_lt_0",
    "Charmander2_lt_1",
    "Charmander2_rb_0",
    "Charmander2_rb_1",
    "Charmander2_rt_0",
    "Charmander2_rt_1",
    "Charmander3_b_0",
    "Charmander3_b_1",
    "Charmander3_t_0",
    "Charmander3_t_1",
    "Charmander3_l_0",
    "Charmander3_l_1",
    "Charmander3_r_0",
    "Charmander3_r_1",
    "Charmander3_lb_0",
    "Charmander3_lb_1",
    "Charmander3_lt_0",
    "Charmander3_lt_1",
    "Charmander3_rb_0",
    "Charmander3_rb_1",
    "Charmander3_rt_0",
    "Charmander3_rt_1"
};

pair<string,ICON> pairArray[] =
{
    //一个结构体数组存放素材信息
    //这里给的是像素哦
    make_pair("Charmander1_rb_0",ICON(Charmander1_rb_0, 180, 20, 24, 24, Charmander1)),
    make_pair("Charmander1_rb_1",ICON(Charmander1_rb_1, 159, 20, 24, 24, Charmander1)),
    make_pair("Charmander1_lt_0",ICON(Charmander1_lt_0, 181, 44, 24, 24, Charmander1)),
    make_pair("Charmander1_lt_1",ICON(Charmander1_lt_1, 159, 44, 24, 24, Charmander1)),
    make_pair("Charmander2_b_0",ICON(Charmander2_b_0, 320, 239, 26, 28, Charmander2)),
    make_pair("Charmander2_b_1",ICON(Charmander2_b_1, 346, 239, 26, 28, Charmander2)),
    make_pair("Charmander2_t_0",ICON(Charmander2_t_0, 320, 269, 26, 28, Charmander2)),
    make_pair("Charmander2_t_1",ICON(Charmander2_t_1, 346, 269, 26, 28, Charmander2)),
    make_pair("Charmander2_l_0",ICON(Charmander2_l_0, 315, 300, 26, 28, Charmander2)),
    make_pair("Charmander2_l_1",ICON(Charmander2_l_1, 342, 302, 36, 28, Charmander2)),
    make_pair("Charmander2_lb_0",ICON(Charmander2_lb_0, 318, 330, 30, 30, Charmander2)),
    make_pair("Charmander2_lb_1",ICON(Charmander2_lb_1, 348, 330, 30, 30, Charmander2)),
    make_pair("Charmander2_lt_0",ICON(Charmander2_lt_0, 315, 360, 30, 30, Charmander2)),
    make_pair("Charmander2_lt_1",ICON(Charmander2_lt_1, 345, 360, 30, 30, Charmander2)),
    make_pair("Charmander3_b_0",ICON(Charmander3_b_0, 351, 484, 32, 32, Charmander3)),
    make_pair("Charmander3_b_1",ICON(Charmander3_b_1, 381, 479, 32, 32, Charmander3)),
    make_pair("Charmander3_t_0",ICON(Charmander3_t_0, 349, 520, 32, 32, Charmander3)),
    make_pair("Charmander3_t_1",ICON(Charmander3_t_1, 380, 515, 33, 35, Charmander3)),
    make_pair("Charmander3_l_0",ICON(Charmander3_l_0, 344, 552, 32, 32, Charmander3)),
    make_pair("Charmander3_l_1",ICON(Charmander3_l_1, 374, 554, 42, 32, Charmander3)),
    make_pair("Charmander3_lb_0",ICON(Charmander3_lb_0, 349, 586, 32, 32, Charmander3)),
    make_pair("Charmander3_lb_1",ICON(Charmander3_lb_1, 381, 585, 32, 32, Charmander3)),
    make_pair("Charmander3_lt_0",ICON(Charmander3_lt_0, 350, 617, 32, 32, Charmander3)),
    make_pair("Charmander3_lt_1",ICON(Charmander3_lt_1, 380, 622, 36, 32, Charmander3)),
};

map<string,ICON> ICON::GAME_ICON_SET(pairArray,pairArray+sizeof(pairArray)/sizeof(pairArray[0]));


ICON::ICON(objstate objstate, int x, int y, int w, int h, objtype objtype){
    this->_objstate = objstate;
    this->srcX = x;
    this->srcY = y;
    this->width = w;
    this->height = h;
    this->_objtype = objtype;
}

ICON ICON::findICON(string name){
    map<string,ICON>::iterator kv;
    kv = ICON::GAME_ICON_SET.find(name);
    if (kv==ICON::GAME_ICON_SET.end()){
       // cout<<"Error: cannot find ICON"<<endl;
       return ICON();
    }
    else{
        return kv->second;
    }
}

ICON& ICON::operator=(const ICON &icon){
    if(this == &icon)
        return (*this);
    else {
        this->srcX = icon.srcX;
        this->srcY = icon.srcY;
        this->_name = icon._name;
        this->width = icon.width;
        this->height = icon.height;
        this->_objtype = icon._objtype;
        this->_objstate = icon._objstate;
        return (*this);
    }
}
