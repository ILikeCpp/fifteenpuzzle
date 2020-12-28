#ifndef MYLABEL_H
#define MYLABEL_H

#include <QPushButton>
#include <QString>

class mylabel : public QPushButton
{
    Q_OBJECT
public:
    explicit mylabel(QWidget *parent = nullptr);

    //鼠标点击
    void enterEvent(QEvent *event);
    //移动效果
    void move_next(int direction, int msec);
    //回到初始位置
    void move_init(int x);

signals:

public slots:
};

#endif // MYLABEL_H
