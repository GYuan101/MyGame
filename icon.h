#ifndef ICON_H
#define ICON_H
#include <string>
#include <map>

using namespace std;

//将一类图标定位到素材图片上的具体区域

enum objtype {
    Charmander1,
    Charmander2,
    Charmander3,
    Effect
};

enum objstate {
    Charmander1_rb_0,
    Charmander1_rb_1,
    Charmander1_lt_0,
    Charmander1_lt_1,
    Charmander2_b_0,
    Charmander2_b_1,
    Charmander2_t_0,
    Charmander2_t_1,
    Charmander2_l_0,
    Charmander2_l_1,
    Charmander2_r_0,
    Charmander2_r_1,
    Charmander2_lb_0,
    Charmander2_lb_1,
    Charmander2_lt_0,
    Charmander2_lt_1,
    Charmander2_rb_0,
    Charmander2_rb_1,
    Charmander2_rt_0,
    Charmander2_rt_1,
    Charmander3_b_0,
    Charmander3_b_1,
    Charmander3_t_0,
    Charmander3_t_1,
    Charmander3_l_0,
    Charmander3_l_1,
    Charmander3_r_0,
    Charmander3_r_1,
    Charmander3_lb_0,
    Charmander3_lb_1,
    Charmander3_lt_0,
    Charmander3_lt_1,
    Charmander3_rb_0,
    Charmander3_rb_1,
    Charmander3_rt_0,
    Charmander3_rt_1,
    Fire1,
    Fire2,
    Fire3
};

class ICON
{
public:
    static int GRID_SIZE;//游戏中一格，相当于图片中多少像素
    static map<string,ICON> GAME_ICON_SET;
        //确定各类物体子素材图片的位置，高、宽等数据
    static ICON findICON(string name);
        //根据物体类型名找到图标

    ICON(){this->_objstate = objstate(-1);}
    ICON(objstate objstate, int x, int y, int w, int h, objtype objtype);
    int getSrcX() const{return this->srcX;}
    int getSrcY() const{return this->srcY;}
    int getWidth() const{return this->width;}
    int getHeight() const{return this->height;}
    objstate getTypeState() const{return this->_objstate;}
    objtype getTypeName() const{return this->_objtype;}
    string getName() const{return this->_name;}
    ICON &operator=(const ICON &icon);
    friend void setTypeState(ICON &icon, objstate allo_objstate){icon._objstate = allo_objstate;}
    //我也不知道用不用强制转换，可能可以不加
    static string getStateName(objstate state){return names[static_cast<int>(state)];}
private:
    string _name;
    objstate _objstate;
    objtype _objtype;
    int srcX, srcY, width, height; //素材图片的位置，高、宽等数据
    static const char* names[36];
};
#endif // ICON_H
