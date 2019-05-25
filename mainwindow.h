#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QPainter>
#include <QKeyEvent>
#include <QTimer>
#include "rpgobj.h"
#include "world.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    //宏的作用是启动QT元对象系统的特性，如支持信号和槽，故用的时候需要从QObject继承或者直接
public:
    explicit MainWindow(QWidget *parent = 0);
    //关键字将MW1构造函数声明为显示构造函数，否则只有一个参数的时候，编译器会进行缺省的操作，以隐式构造函数的形式将参数类型的变量转换成MW1对象，explicit之后就不会了
    //Mainwindow是QWidget的一个子类型，而与ui_mainwidow是不同的
    ~MainWindow();
    void paintEvent(QPaintEvent *e);
    void keyPressEvent(QKeyEvent *);
    void winOrLose();

public slots:
    void recovery();
    void attackTower();

protected slots:
    void MonsterMove();
    void MonsterCreate();
    void TowerCreate();

private:
    //https://blog.csdn.net/hebbely/article/details/79267348
    //源文件分开变异，彼此之间不受影响；头文件会放在其源文件中一起编译，因此被引用的头文件的实现发生变化，引用它的头文件需要重新编译
    //pImpl惯用手法的主要作用是解开类的使用接口和实现的耦合，若使用Ui:MW1的对象作为数据成员，每次构造MW1时，都会在栈上腾出sizeof(Ui:MW1),
    //如果这个类发生变化，则MW1的源文件会重新编译，MW1的头文件和所有包含该头文件的头文件都需要重新编译。
    //但是使用了指针的形式，一方面在用户构造或使用这个类的时候都无法触及到Ui:MW1类，因此这个指针把用户和Ui:MW1类隔离开来。
    //另一方面指针的大小时固定的（64bits），就只需要重新编译Ui:MW1的源文件（实现）
    Ui::MainWindow *ui;
    World _game;
    QTimer *timer;
    QTimer *createtimer;
    QTimer *towertimer;
};

#endif // MAINWINDOW_H
