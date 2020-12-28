#include <QString>
#include <QDebug>
#include <QPropertyAnimation>
#include <QTimer>
#include "mylabel.h"

mylabel::mylabel(QWidget *parent) : QPushButton (parent)
{
    /*QPixmap pix;
    bool ret = pix.load(Img);
    if(!ret)
    {
       qDebug() << "图片加载失败";
       return;
    }
    //设置图片固定大小
    this->setFixedSize(70,70);
    //设置不规则图片样式
    this->setStyleSheet("QPushButton{border:0px;}");
    //设置图标
    this->setIcon(pix);
    //设置图标大小
    this->setIconSize(QSize(70,70));*/
}

void mylabel::enterEvent(QEvent *event)
{

}

void mylabel::move_next(int direction, int msec)
{
    QTimer::singleShot(msec,this,[=](){
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");
    animation->setDuration(400);
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    if(direction==1)
        animation->setEndValue(QRect(this->x(),this->y()-70,this->width(),this->height()));
    else if(direction==2)
        animation->setEndValue(QRect(this->x(),this->y()+70,this->width(),this->height()));
    else if(direction==3)
        animation->setEndValue(QRect(this->x()-70,this->y(),this->width(),this->height()));
    else if(direction==4)
        animation->setEndValue(QRect(this->x()+70,this->y(),this->width(),this->height()));
     animation->start();
    });
}

void mylabel::move_init(int x)
{
    int i=x/4;
    int j=x-i*4;
    this->move((50+70*j),(120+70*i));
    //qDebug()<<50+70*j<<" "<<120+70*i<<endl;
}

