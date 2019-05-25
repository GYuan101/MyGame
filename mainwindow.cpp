#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "icon.h"
#include <map>
#include <QTimer>
#include <QMessageBox>
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //这个ui继承自ui_Qmainwidow,可以用QMainWidow初始化，之后可通过ui关联qt designer的各种控件
    this->setFixedSize(1080, 720);
    //init game world
    _game.initpiclib();
    _game.initWorld("");//TODO 应该是输入有效的地图文件

    timer = new QTimer(this);

    createtimer = new QTimer(this);

    towertimer = new QTimer(this);

    connect(createtimer,SIGNAL(timeout()),this,SLOT(MonsterCreate()));//timeoutslot()为自定义槽
    //MonsterCreate();
    connect(timer,SIGNAL(timeout()),this,SLOT(MonsterMove()));//timeoutslot()为自定义槽

    connect(towertimer,SIGNAL(timeout()),this,SLOT(TowerCreate()));//timeoutslot()为自定义槽

    timer->start(1000);

    towertimer->start(4000);

    createtimer->start(2000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *e){
    QPainter *pa;
    pa = new QPainter();
    pa->begin(this);
    this->_game.show(pa);
    pa->end();
    delete pa;
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    //direction = 1,2,3,4 for 上下左右
    if(e->key() == Qt::Key_A)
    {
        this->_game.handlePlayerMove(3,0.5);
    }
    else if(e->key() == Qt::Key_D)
    {
        this->_game.handlePlayerMove(4,0.5);
    }
    else if(e->key() == Qt::Key_W)
    {
        this->_game.handlePlayerMove(1,0.5);
    }
    else if(e->key() == Qt::Key_S)
    {
         this->_game.handlePlayerMove(2,0.5);
    }
    this->repaint();
}

void MainWindow::MonsterMove(){
    this->winOrLose();
    this->_game.handleMonsterMove();       //怪兽移动一次
    //this->_game.freemonUpdate();         //离开攻击范围的怪兽更新
    this->_game.allmonUpdate();            //所有塔可攻击的怪兽更新
    this->_game.ourmonsterUpdate();        //每座塔的攻击范围更新
    this->_game.towersetUpdate();          //每座塔的攻击方向（形态）更新
    this->update();
    QTimer::singleShot(300,this,SLOT(attackTower())); //攻击形态0.2s
    QTimer::singleShot(700,this,SLOT(recovery()));    //回复正常状态0.1s
}

void MainWindow::MonsterCreate(){
    this->_game.initMonster();
}

void MainWindow::TowerCreate(){
    this->_game.initTower();
}

void MainWindow::attackTower(){
    //塔切换到攻击状态
    this->_game.towerAttack();
    this->update();
}

void MainWindow::recovery(){
    //塔切换到正常状态
    this->_game.towerRecover();
    this->update();
}

void MainWindow::winOrLose(){
    if(this->_game.ifNoMonster()){
        cout << "You Win!" << endl;
        // 创建一个对话框对象
        QMessageBox::about(NULL, "About", "You Win!");
        exit(1);
    }
    else if (this->_game.ifFullMonster() == 20){
        cout << "You Lose!" << endl;
        QMessageBox::about(NULL, "About", "You Lose!");
        exit(1);
    }
}
