#include "rpgobj.h"
#include <iostream>
//#include <QMediaPlayer>

void RPGObj::initObj(objtype objtype, objstate objstate, string name)
{
    //所支持的对象类型应定义为枚举
    //TODO 进行不同对象的数据赋值
    //cout << objtype << objstate << name << endl;
    QImage all;
    switch (objtype){
    case Charmander1: case Charmander2: case Charmander3:
        this->_attackable = false;
        all.load("D:\\C++\\QT\\source\\pic\\Charmander2.png");

        this->_icon = ICON::findICON(name);

        // 直接截取了像素，暂时不用乘,用scaled调整规范为32*32像素
        if(this->_icon.getTypeState() != -1){
            this->_pic = all.copy(QRect(_icon.getSrcX(), _icon.getSrcY(), _icon.getWidth(), _icon.getHeight()));
            this->_pic = this->_pic.scaled(ICON::GRID_SIZE, ICON::GRID_SIZE);
        }
        else {
            // 考虑到有些形象需要镜像
            bool horizontal = true;
            bool vertical = false;
            ICON tempicon;
            switch (objstate) {
            case Charmander2_r_0:
                tempicon = ICON::findICON("Charmander2_l_0");
                this->_icon = ICON(Charmander2_r_0, tempicon.getSrcX(), tempicon.getSrcY(), tempicon.getWidth(), tempicon.getHeight(), Charmander2);
                break;
            case Charmander2_r_1:
                tempicon = ICON::findICON("Charmander2_l_1");
                this->_icon = ICON(Charmander2_r_1, tempicon.getSrcX(), tempicon.getSrcY(), tempicon.getWidth(), tempicon.getHeight(), Charmander2);
                break;
            case Charmander2_rb_0:
                tempicon = ICON::findICON("Charmander2_lb_0");
                this->_icon = ICON(Charmander2_rb_0, tempicon.getSrcX(), tempicon.getSrcY(), tempicon.getWidth(), tempicon.getHeight(), Charmander2);
                break;
            case Charmander2_rb_1:
                tempicon = ICON::findICON("Charmander2_lb_1");
                this->_icon = ICON(Charmander2_rb_1, tempicon.getSrcX(), tempicon.getSrcY(), tempicon.getWidth(), tempicon.getHeight(), Charmander2);
                break;
            case Charmander2_rt_0:
                tempicon = ICON::findICON("Charmander2_lt_0");
                this->_icon = ICON(Charmander2_rt_0, tempicon.getSrcX(), tempicon.getSrcY(), tempicon.getWidth(), tempicon.getHeight(), Charmander2);
                break;
            case Charmander2_rt_1:
                tempicon = ICON::findICON("Charmander2_lt_1");
                this->_icon = ICON(Charmander2_rt_1, tempicon.getSrcX(), tempicon.getSrcY(), tempicon.getWidth(), tempicon.getHeight(), Charmander2);
                break;
            case Charmander3_r_0:
                tempicon = ICON::findICON("Charmander3_l_0");
                this->_icon = ICON(Charmander3_r_0, tempicon.getSrcX(), tempicon.getSrcY(), tempicon.getWidth(), tempicon.getHeight(), Charmander3);
                break;
            case Charmander3_r_1:
                tempicon = ICON::findICON("Charmander3_l_1");
                this->_icon = ICON(Charmander3_r_1, tempicon.getSrcX(), tempicon.getSrcY(), tempicon.getWidth(), tempicon.getHeight(), Charmander3);
                break;
            case Charmander3_rb_0:
                tempicon = ICON::findICON("Charmander3_lb_0");
                this->_icon = ICON(Charmander3_rb_0, tempicon.getSrcX(), tempicon.getSrcY(), tempicon.getWidth(), tempicon.getHeight(), Charmander3);
                break;
            case Charmander3_rb_1:
                tempicon = ICON::findICON("Charmander3_lb_1");
                this->_icon = ICON(Charmander3_rb_1, tempicon.getSrcX(), tempicon.getSrcY(), tempicon.getWidth(), tempicon.getHeight(), Charmander3);
                break;
            case Charmander3_rt_0:
                tempicon = ICON::findICON("Charmander3_lt_0");
                this->_icon = ICON(Charmander3_rt_0, tempicon.getSrcX(), tempicon.getSrcY(), tempicon.getWidth(), tempicon.getHeight(), Charmander3);
                break;
            case Charmander3_rt_1:
                tempicon = ICON::findICON("Charmander3_lt_1");
                this->_icon = ICON(Charmander3_rt_1, tempicon.getSrcX(), tempicon.getSrcY(), tempicon.getWidth(), tempicon.getHeight(), Charmander3);
                break;
            default:
                cout<<"invalid RPGObj type."<<endl;
            }
            this->_pic = all.copy(QRect(_icon.getSrcX(), _icon.getSrcY(), _icon.getWidth(), _icon.getHeight()));
            this->_pic = this->_pic.mirrored(horizontal, vertical);
            this->_pic = this->_pic.scaled(ICON::GRID_SIZE, ICON::GRID_SIZE);
        }

        break;
    case Effect:
        //提取特效信息并模仿上面生成相应obj
        all.load("D:\\C++\\QT\\source\\pic\\effect.png");
        switch (objstate) {
        case Fire1:
            this->_icon = ICON(objstate, 360, 1740, 60, 100, Effect);
            break;
        case Fire2:
            this->_icon = ICON(objstate, 490, 1740, 50, 100, Effect);
            break;
        case Fire3:
            this->_icon = ICON(objstate, 600, 1740, 40, 100, Effect);
            break;
        default:
            cout << "Wrong Objstate!" << endl;
            break;
        } //endswitch
        this->_pic = all.copy(QRect(_icon.getSrcX(), _icon.getSrcY(), _icon.getWidth(), _icon.getHeight()));
        this->_pic = this->_pic.scaled(ICON::GRID_SIZE, ICON::GRID_SIZE);
        break;
    default:
        //TODO 应由专门的错误日志文件记录
        cout<<"invalid ICON type."<<endl;
        break;
    }
}


void RPGObj::show(QPainter * pa){
    int gSize = ICON::GRID_SIZE/2;
    pa->drawImage(this->_pos_x*gSize,this->_pos_y*gSize,this->_pic);
}


void RPGObj::onErase(){
    /*
    QMediaPlayer * player = new QMediaPlayer;
    //player->setMedia(":/sounds/2953.mp3");
    player->setMedia(QUrl("qrc:/sounds/2953.mp3"));
    player->setVolume(30);
    player->play();
    */
}

