#ifndef WORLD_H
#define WORLD_H
#include "rpgobj.h"
#include "effect.h"
#include "guard.h"
#include "monster.h"
#include "tower.h"
#include <vector>
#include <QList>
#include <string>
#include <QPainter>
#include <QImage>

struct Road{
    string name;
    double startX;
    double startY;
    double endX;
    double endY;
    int length;
};

struct Monstertype{
    objtype type_;
    objstate state_;
    string name_;
};

class World
{
public:
    World(){this->_guard = new Guard;}
    ~World();
    void initWorld(string mapFile);
        //输入的文件中定义了初始状态下游戏世界有哪些对象，出生点在哪
        /*e.g.
           player 5 5
           stone 3 3
           fruit 7 8
         */
    void show(QPainter * painter);
        //显示游戏世界所有对象
    void handlePlayerMove(int direction, double steps);
        //假定只有一个玩家

    void handleMonsterMove();
        //控制全体怪物

    void eraseObj(int x, int y);

    void freemonUpdate();

    void allmonUpdate();

    void ourmonsterUpdate();

    static vector<Road> getRoute();

    void initMonster();

    void initTower();

    void towersetUpdate();

    void towerAttack();

    void towerRecover();

    bool ifNoMonster() const{return ((this->_monster_set.size() == 0) && (this->_tower_set.size() != 0));}

    int ifFullMonster() const{return Monster::getLoss();}

    static void initpiclib();

    static RPGObj getpic(int i){return _piclib[i];}

    static void initFireEffect(FireEffect p);

private:
    vector<RPGObj *> _objs;
    vector<Tower *> _tower_set;
    QImage _map;
    Guard * _guard;

    vector<Monster> _monster_set;

    const static vector<Road> Route;

    const QList<QList<double> > Tower_base = {
        QList<double>{3.5, 4.5},
        QList<double>{3.5, 8},
        QList<double>{3.5, 11.5},
        QList<double>{11, 12},
        QList<double>{16, 12},
        QList<double>{21, 12},
        QList<double>{26, 12},
        QList<double>{6, 17},
        QList<double>{11, 17},
        QList<double>{16, 17},
        QList<double>{21, 17},
        QList<double>{26, 17},
        QList<double>{8, 5.5},
        QList<double>{14, 6.5},
        QList<double>{19, 6.5},
        QList<double>{24, 6.5},
        QList<double>{29, 6.5}
    };

    QList<Monster *> freemonster_;

    static vector<RPGObj> _piclib;

    static vector<FireEffect> _effectlib;

    static const int MAXMONSTER = 100;
};
#endif // WORLD_H
