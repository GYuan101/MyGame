#include "world.h"
#include "icon.h"
#include "rpgobj.h"
#include <QTime>
//#include <QMediaPlayer>

World::~World(){
    delete this->_guard;
}

vector<RPGObj> World::_piclib = {};

vector<FireEffect> World::_effectlib = {};

const vector<Road> World::Route = {
    {"Column1", 0.5, 0, 0.5, 14.5, 29},
    {"Column2", 6, 0, 6, 14.5, 29},
    {"Column3", 11.5, 0, 11.5, 8.5, 17},
    {"Column4", 31.5, 14.5, 31.5, 3, 23},
    {"Row1", 0.5, 14.5, 31.5, 14.5, 62},
    {"Row2", 11.5, 8.5, 31.5, 8.5, 40},
    {"Row3", 31.5, 3, 16, 3, 31}
};

void World::initFireEffect(FireEffect p){
    _effectlib.push_back(p);
}

void World::initMonster(){
    if(Monster::getCount() != MAXMONSTER){
        vector<Monstertype> Monstertype_ {
            {Charmander2, Charmander2_b_0, "Charmander2_b_0"},
            {Charmander3, Charmander3_b_0, "Charmander3_b_0"},
        };
        Monstertype Mtype_;
        int StartRoad_;
        Monster *p = new Monster;
        qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));//设置随机种子为系统初始时间到当前时间的秒数
        Mtype_ = Monstertype_[qrand()%2];
        qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));//设置随机种子为系统初始时间到当前时间的秒数
        StartRoad_ = qrand()%3;
        p->initObj(Mtype_.type_, Mtype_.state_, Mtype_.name_);
        //init不会将icon._name赋值！但是不影响!不知道为啥这个state就是不对
        setICON(*p, Mtype_.state_);
        p->setPosY(0);
        p->setPosX(Route[StartRoad_].startX);
        switch (StartRoad_) {
        case 0:
            //p->setDist(Route[0].length + Route[5].length + 2*(Route[6].startY - Route[5].startY) + Route[6].length);
            p->setDist(Route[0].length + Route[4].length + Route[3].length + Route[6].length);
            break;
        case 1:
            p->setDist(Route[1].length + 2*(Route[3].startX - Route[1].startX) + Route[3].length + Route[6].length);
            break;
        case 2:
            p->setDist(Route[2].length + Route[4].length + Route[3].length + Route[6].length);
            break;
        default:
            cout << "Wrong Initial Route!";
            break;
        }
        p->setCode(Monster::getCount()+1);
        p->setHealth((Mtype_.state_==Charmander2_b_0)? 3000: 6000);
        p->addNum();

        _monster_set.push_back(*p);
        freemonster_.push_back(&_monster_set[_monster_set.size()-1]); //最新的元素进入链表
        delete p;
    }
}

vector<Road> World:: getRoute(){
    return World::Route;
}

void World::initWorld(string mapFile){
    //下面这部分逻辑应该是读入地图文件，生成地图上的对象
    //设定最大容量，避免每次动态分配内存
    this->_monster_set.reserve(MAXMONSTER);
    this->_tower_set.reserve(this->Tower_base.size());
    this->_effectlib.reserve(this->Tower_base.size());

    this->_map.load("D:\\C++\\QT\\source\\pic\\map.jpeg");
    //_guard 5 5
    this->_guard->initObj(Charmander3, Charmander3_r_0, "Charmander3_r_0");
    this->_guard->setPosX(16);
    this->_guard->setPosY(3);

    /*
    RPGObj *p1 = new RPGObj;
    p1->initObj(Charmander, Charmander2_b_0, "Charmander2_b_0");
    p1->setPosX(6);
    p1->setPosY(3);

    RPGObj *p2 = new RPGObj;
    p2->initObj(Charmander, Charmander3_b_0, "Charmander3_b_0");
    p2->setPosX(0.5);
    p2->setPosY(5);

    RPGObj *p3 = new RPGObj;
    p3->initObj(Charmander, Charmander3_lb_1, "Charmander3_lb_1");
    p3->setPosX(11.5);
    p3->setPosY(8.5);

    RPGObj *p4 = new RPGObj;
    p4->initObj(Charmander, Charmander1_rb_1, "Charmander1_rb_1");
    p4->setPosX(31.5);
    p4->setPosY(14.5);

    RPGObj *p5 = new RPGObj;
    p5->initObj(Charmander, Charmander1_rb_0, "Charmander1_rb_0");
    p5->setPosX(3.5);
    p5->setPosY(4.5);

    RPGObj *p6 = new RPGObj;
    p6->initObj(Charmander, Charmander2_rb_1, "Charmander2_rb_1");
    p6->setPosX(3.5);
    p6->setPosY(8);

    RPGObj *p7 = new RPGObj;
    p7->initObj(Charmander, Charmander2_rb_0, "Charmander2_rb_0");
    p7->setPosX(3.5);
    p7->setPosY(11.5);

    RPGObj *p9 = new RPGObj;
    p9->initObj(Charmander, Charmander3_rb_0, "Charmander3_rb_0");
    p9->setPosX(0.5);
    p9->setPosY(14.5);

    RPGObj *p10 = new RPGObj;
    p10->initObj(Charmander, Charmander3_rb_1, "Charmander3_rb_1");
    p10->setPosX(11);
    p10->setPosY(12);

    RPGObj *p11 = new RPGObj;
    p11->initObj(Charmander, Charmander2_lt_0, "Charmander2_lt_0");
    p11->setPosX(16);
    p11->setPosY(12);

    RPGObj *p12 = new RPGObj;
    p12->initObj(Charmander, Charmander2_lt_1, "Charmander2_lt_1");
    p12->setPosX(26);
    p12->setPosY(12);

    RPGObj *p13 = new RPGObj;
    p13->initObj(Charmander, Charmander3_lt_1, "Charmander3_lt_1");
    p13->setPosX(21);
    p13->setPosY(12);

    RPGObj *p8 = new RPGObj;
    p8->initObj(Charmander, Charmander2_rb_0, "Charmander2_rb_0");
    p8->setPosX(6);
    p8->setPosY(17);

    RPGObj *p14 = new RPGObj;
    p14->initObj(Charmander, Charmander3_t_1, "Charmander3_t_1");
    p14->setPosX(11);
    p14->setPosY(17);

    RPGObj *p16 = new RPGObj;
    p16->initObj(Charmander, Charmander3_l_1, "Charmander3_l_1");
    p16->setPosX(16);
    p16->setPosY(17);

    RPGObj *p15 = new RPGObj;
    p15->initObj(Charmander, Charmander3_t_0, "Charmander3_t_0");
    p15->setPosX(21);
    p15->setPosY(17);

    RPGObj *p17 = new RPGObj;
    p17->initObj(Charmander, Charmander3_r_0, "Charmander3_r_0");
    p17->setPosX(26);
    p17->setPosY(17);

    RPGObj *p18 = new RPGObj;
    p18->initObj(Charmander, Charmander2_r_1, "Charmander2_r_1");
    p18->setPosX(8);
    p18->setPosY(5.5);

    RPGObj *p19 = new RPGObj;
    p19->initObj(Charmander, Charmander2_r_1, "Charmander2_r_1");
    p19->setPosX(14);
    p19->setPosY(6.5);

    RPGObj *p20 = new RPGObj;
    p20->initObj(Charmander, Charmander2_r_1, "Charmander2_r_1");
    p20->setPosX(19);
    p20->setPosY(6.5);

    RPGObj *p21 = new RPGObj;
    p21->initObj(Charmander, Charmander2_r_1, "Charmander2_r_1");
    p21->setPosX(24);
    p21->setPosY(6.5);

    RPGObj *p22 = new RPGObj;
    p22->initObj(Charmander, Charmander2_r_1, "Charmander2_r_1");
    p22->setPosX(29);
    p22->setPosY(6.5);

    this->_objs.push_back(p1);
    this->_objs.push_back(p2);
    this->_objs.push_back(p3);
    this->_objs.push_back(p4);
    this->_objs.push_back(p5);
    this->_objs.push_back(p6);
    this->_objs.push_back(p7);
    this->_objs.push_back(p8);
    this->_objs.push_back(p9);
    this->_objs.push_back(p10);
    this->_objs.push_back(p11);
    this->_objs.push_back(p12);
    this->_objs.push_back(p13);
    this->_objs.push_back(p14);
    this->_objs.push_back(p15);
    this->_objs.push_back(p16);
    this->_objs.push_back(p17);
    this->_objs.push_back(p18);
    this->_objs.push_back(p19);
    this->_objs.push_back(p20);
    this->_objs.push_back(p21);
    this->_objs.push_back(p22);
    */
    /*
    QMediaPlayer * player = new QMediaPlayer;
    player->setMedia(QUrl("qrc:/sounds/hdl.mp3"));
    player->setVolume(30);
    player->play();
*/

}

void World::initpiclib(){
    //导入全部素材的icon和pic，以便tower的redirect
    for (objstate i = Charmander1_rb_0; i <= Charmander1_lt_1; i=objstate(i+1)) {
        RPGObj p;//安全的吧结束了创建副本送到vector里然后析构p
        p.initObj(Charmander1, i, ICON::getStateName(i));
        _piclib.push_back(p);
    }
    for (objstate i = Charmander2_b_0; i <= Charmander2_rt_1; i=objstate(i+1)) {
        RPGObj p;
        p.initObj(Charmander2, i, ICON::getStateName(i));
        _piclib.push_back(p);
    }
    for (objstate i = Charmander3_b_0; i <= Charmander3_rt_1; i=objstate(i+1)) {
        RPGObj p;
        p.initObj(Charmander3, i, ICON::getStateName(i));
        _piclib.push_back(p);
    }
}

void World::show(QPainter * painter){
    QRect target(0, 0, 1080, 720); //建立目标矩形，该区域是显示图像的目的地
    QRect source(0, 0, 1080, 720); //建立源矩形，用来划定来自外部的源图像文件中需要显示的区域
    painter->drawImage(target, this->_map, source);
    int n = this->_tower_set.size();
    for (int i=0;i<n;i++){
        this->_tower_set[i]->show(painter);
    }
    this->_guard->show(painter);
    n = this->_monster_set.size();
    for (int i=0;i<n;i++){
        this->_monster_set[i].show(painter);
    }
    int m = this->_effectlib.size();
    for (int i=0;i<m;i++){
        this->_effectlib[i].show(painter);
    }
}

void World::eraseObj(int x, int y){
    vector<RPGObj *>::iterator it;
    vector<Monster *>::iterator it_M;
    for(it=this->_objs.begin();it!=this->_objs.end();it++){
       if (((*it)->getPosX() == x) && ((*it)->getPosY()==y) ){
            (*it)->onErase();
            this->_objs.erase(it);
            delete (*it);
            break;
        }
    }
    /*
    for(it_M=this->_monster_set.begin();it_M!=this->_monster_set.end();it_M++){
       if (((*it_M)->getPosX() == x) && ((*it_M)->getPosY()==y) ){
            (*it_M)->onErase();
            this->_monster_set.erase(it_M);
            delete (*it_M);
            break;
        }
    }
    */
}

void World::handlePlayerMove(int direction, double steps){
    int x =  this->_guard->getNextX(direction);
    int y = this->_guard->getNextY(direction);
    //this->eraseObj(x,y);
    this->_guard->move(direction, steps);
}

void World::handleMonsterMove(){
    //先清空effectlib
    vector<FireEffect>::iterator it;
    for (it = _effectlib.begin(); it != _effectlib.end();)
        it = _effectlib.erase(it);
    vector<Monster>::iterator i;
    for (i = _monster_set.begin(); i != _monster_set.end();){
        (*i).move();
        (*i).setDist((*i).getDist() - 1);
        if((*i).ifErase() != -1){
            //清除元素
            i = _monster_set.erase(i);
            continue;
            //需要将包含这个怪兽的塔的mymonster进行修改
            //先放在listupdate里面试试，这里先假设每个怪被删除后，内存清楚，指向这个内存的指针变成null
        }
        i++;
    }
}

void World::initTower(){
    //要把这个放在tower之下；
    int size = Tower_base.size();
    cout << Tower::getNum() << '/' << size << endl;
    if(size > Tower::getNum()){
        Tower *p = new Tower;
        p->initObj(Charmander1, Charmander1_rb_0, "Charmander1_rb_0");
        //按顺序生成塔
        p->setPosX(Tower_base[p->getNum()][0]);
        p->setPosY(Tower_base[p->getNum()][1]);
        p->setRange(2.5);
        p->setAttackAim(-1);
        p->setAttack(500);
        Tower::addNum();
        this->_tower_set.push_back(p);
    }
    else {
        qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));//设置随机种子为系统初始时间到当前时间的秒数
        int updateCode = qrand()%size;
        this->_tower_set[updateCode]->updateMyTower();
    }
}

void World::freemonUpdate(){
    double X_, Y_;
    QList<Monster *>::Iterator i;
    for (i = freemonster_.begin(); i != freemonster_.end(); i++) {
        X_ = (*i)->getPosX();
        Y_ = (*i)->getPosY();
        vector<Tower *>::iterator j;
        for (j = _tower_set.begin(); j != _tower_set.end(); j++) {
            //判断XY是否在每一个塔的攻击范围内
            if((*j)->attackable(X_, Y_)){
                //在的话就把它从free中删除，加到这个塔的mymonster里
                (*j)->addMymonster(*i);
                i = freemonster_.erase(i);
                i--;
                break;
            }
            else continue;
        }
    }
}

void World::allmonUpdate(){
    double X_, Y_, C_;
    vector<Monster>::iterator i;
    for (i = _monster_set.begin(); i != _monster_set.end(); i++) {
        X_ = (*i).getPosX();
        Y_ = (*i).getPosY();
        C_ = (*i).getCode();
        vector<Tower *>::iterator j;
        for (j = _tower_set.begin(); j != _tower_set.end(); j++) {
            //判断这个塔里是否包含这个怪兽
            if((*j)->attackable(X_, Y_)){
                //在的话就把它从加到这个塔的mymonster里
                if( ! ((*j)->haveMonsterCode(C_)) ){
                    (*j)->addMymonster(&(*i));
                    break;
                }
                else continue;
            }//endif
        }//endfor
    }//endfor
}

void World::ourmonsterUpdate(){
    vector<Tower *>::iterator i;
    for (i = _tower_set.begin(); i != _tower_set.end(); i++)
        (*i)->ListUpdate();
}

void World::towersetUpdate(){
    if(_tower_set.size() > 0){
        int _attackAim = -1;
        vector<Tower *>::iterator i;
        for (i = _tower_set.begin(); i != _tower_set.end(); i++){
            _attackAim = (*i)->Redirect();
            (*i)->setAttackAim(_attackAim);
        }
    }
}

void World::towerAttack(){
    if(_tower_set.size() > 0){
        vector<Tower *>::iterator i;
        for (i = _tower_set.begin(); i != _tower_set.end(); i++)
            (*i)->Attack((*i)->getAim());
    }
}

void World::towerRecover(){
    if(_tower_set.size() > 0){
        vector<Tower *>::iterator i;
        for (i = _tower_set.begin(); i != _tower_set.end(); i++)
            (*i)->Recover();
    }
}

