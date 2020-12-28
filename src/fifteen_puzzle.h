#ifndef FIFTEEN_PUZZLE_H
#define FIFTEEN_PUZZLE_H

#include <QMainWindow>
#include <QPushButton>
#include <vector>
#include "struct.h"
#include "mylabel.h"
using namespace std;

namespace Ui {
class fifteen_puzzle;
}

class fifteen_puzzle : public QMainWindow
{
    Q_OBJECT

public:
    explicit fifteen_puzzle(QWidget *parent = nullptr);
    ~fifteen_puzzle();
    //按钮数组
    vector<mylabel*> buttons;

    //终止状态
    status* end=new status;
    //初始状态
    status* begin=new status;

    //open表
    vector<status*> open;
    //close表
    vector<status*> close;
    //求解顺序表
    vector<status*> ll;

    //重写paintEvent事件 画背景图
    void paintEvent(QPaintEvent *);
    //检查是否合法(是否有解以及手动输入是否有误)
    int check_valid();
    //移动格子
    void step(int x,int y,int mark,status* node);
    //扩展结点
    void expand(status* node);
    //判断是否为目标状态
    int check_goal(status* node);
    //运行函数
    status* run();
    //判断是否在close表中
    status* judge_inclose(status* node,int& flag);
    //判断是否在open表中
    status* judge_inopen(status* node,int& flag);
    //计算不在正确位置点的个数
    int count_nat(status* node);
    //计算f值
    void compute_f(status* node);
    //封装修改子节点指针的步骤
    void modify_pointer(status* node,status* n1,int direction,int mark);

    void find_zeros(status* s);
    //比较函数
    //int cmp(const status*& a,const status*& b);

private slots:
    void draw_beginscence();

private:
    Ui::fifteen_puzzle *ui;
};

#endif // FIFTEEN_PUZZLE_H
