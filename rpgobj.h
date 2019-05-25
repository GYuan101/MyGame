#ifndef RPGOBJ_H
#define RPGOBJ_H
#include <QImage>
#include <QPainter>
#include "icon.h"

using namespace std;

class RPGObj
{
public:
    RPGObj(){}

    void initObj(objtype objtype, objstate objstate, string name);
    void show(QPainter * painter);

    void setPosX(double x){this->_pos_x=x;}
    void setPosY(double y){this->_pos_y=y;}
    void setHealth(int h){this->Health_point = h;}
    void setAttack(int d){this->Damge_per_second = d;}

    double getPosX() const{return this->_pos_x;}
    double getPosY() const{return this->_pos_y;}
    int getHeight() const{return this->_icon.getHeight();}
    int getWidth() const{return this->_icon.getWidth();}
    int getHealth(){return this->Health_point;}
    int getDamage(){return this->Damge_per_second;}

    bool canAttack() const{return this->_attackable;}

    virtual void onErase();

    virtual void move(){}

    virtual void Attack(int aim_){}

    objstate getObjState() const{return this->_icon.getTypeState();}//返回类名

    objtype getObjType() const{return this->_icon.getTypeName();}//返回类名

    string getName() const{return this->_icon.getName();}

    ICON getIcon() const{return this->_icon;}

    QImage getImage() const{return this->_pic;}

    virtual ~RPGObj(){}

protected:
    //所有坐标，单位均为游戏中的格
    QImage _pic;  //图片资源
    double _pos_x, _pos_y;//该物体在游戏中当前位置（左上角坐标）
    ICON _icon;//可以从ICON中获取对象的素材，尺寸等信息

private:
    bool _attackable;
    int Damge_per_second;
    int Health_point;
    double Critical_prob;
    double Miss_Prob;
};
#endif // RPGOBJ_H
