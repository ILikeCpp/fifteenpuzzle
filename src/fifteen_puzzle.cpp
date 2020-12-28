#include <QPainter>
#include <QMessageBox>
#include <QDebug>
#include <QPushButton>
#include <vector>
#include <QTimer>
#include "fifteen_puzzle.h"
#include "ui_fifteen_puzzle.h"
#include "mylabel.h"
using namespace std;

fifteen_puzzle::fifteen_puzzle(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::fifteen_puzzle)
{
    ui->setupUi(this);
    setWindowTitle("15数码游戏");

    buttons.push_back(ui->f1);
    buttons.push_back(ui->f2);
    buttons.push_back(ui->f3);
    buttons.push_back(ui->f4);
    buttons.push_back(ui->f5);
    buttons.push_back(ui->f6);
    buttons.push_back(ui->f7);
    buttons.push_back(ui->f8);
    buttons.push_back(ui->f9);
    buttons.push_back(ui->f10);
    buttons.push_back(ui->f11);
    buttons.push_back(ui->f12);
    buttons.push_back(ui->f13);
    buttons.push_back(ui->f14);
    buttons.push_back(ui->f15);
    buttons.push_back(ui->f16);

    //初始输入点击确认，绘制初始15数码图
    connect(ui->yes1,&QPushButton::clicked,[=](){
        //qDebug()<<"按下"<<endl;
        this->draw_beginscence();
        //qDebug()<<begin->x<<" "<<begin->y<<endl;

        //重新全部显示
        for(int i=0;i<16;i++)
            buttons[i]->show();
        //让所有按钮位置复原
        for(int i=0;i<16;i++)
            buttons[i]->move_init(i);
        /*ui->f1->show();
        ui->f2->show();
        ui->f3->show();
        ui->f4->show();
        ui->f5->show();
        ui->f6->show();
        ui->f7->show();
        ui->f8->show();
        ui->f9->show();
        ui->f10->show();
        ui->f11->show();
        ui->f12->show();
        ui->f13->show();
        ui->f14->show();
        ui->f15->show();
        ui->f16->show();*/

        std::vector<QPixmap> res_pix;
        for(int i=0;i<4;i++)
        {
            for(int j=0;j<4;j++)
            {
                QString str;
                if(begin->in[i][j]!=0) str=QString(":/res/%1.png").arg(begin->in[i][j]);
                else str=QString(":/res/1.png");
                //qDebug()<<str<<" "<<begin->in[i][j]<<endl;
                QPixmap pix;
                bool ret = pix.load(str);
                if(!ret)
                {
                    qDebug() << "图片加载失败";
                    return;
                }
                pix.scaled(60,60);
                res_pix.push_back(pix);
            }
        }
        int zeros_position=begin->x*4+begin->y;
        //qDebug()<<"position:"<<zeros_position<<endl;

        //qDebug()<<endl;
        for(int i=0;i<16;i++)
        {
            if(i!=zeros_position)
            {
                buttons[i]->setIcon(res_pix[i]);
                buttons[i]->setIconSize(QSize(62,60));
            }
            else
            {
                buttons[i]->hide();
            }
        }
        /*
        if(begin->x!=0||begin->y!=0) {ui->f1->setIcon(res_pix[0]);ui->f1->setIconSize(QSize(62,60));} else ui->f1->hide();
        if(begin->x!=0||begin->y!=1) {ui->f2->setIcon(res_pix[1]);ui->f2->setIconSize(QSize(62,60));} else ui->f2->hide();
        if(begin->x!=0||begin->y!=2) {ui->f3->setIcon(res_pix[2]);ui->f3->setIconSize(QSize(62,60));} else ui->f3->hide();
        if(begin->x!=0||begin->y!=3) {ui->f4->setIcon(res_pix[3]);ui->f4->setIconSize(QSize(62,60));} else ui->f4->hide();
        if(begin->x!=1||begin->y!=0) {ui->f5->setIcon(res_pix[4]);ui->f5->setIconSize(QSize(62,60));} else ui->f5->hide();
        if(begin->x!=1||begin->y!=1) {ui->f6->setIcon(res_pix[5]);ui->f6->setIconSize(QSize(62,60));} else ui->f6->hide();
        if(begin->x!=1||begin->y!=2) {ui->f7->setIcon(res_pix[6]);ui->f7->setIconSize(QSize(62,60));} else ui->f7->hide();
        if(begin->x!=1||begin->y!=3) {ui->f8->setIcon(res_pix[7]);ui->f8->setIconSize(QSize(62,60));} else ui->f8->hide();
        if(begin->x!=2||begin->y!=0) {ui->f9->setIcon(res_pix[8]);ui->f9->setIconSize(QSize(62,60));} else ui->f9->hide();
        if(begin->x!=2||begin->y!=1) {ui->f10->setIcon(res_pix[9]);ui->f10->setIconSize(QSize(62,60));} else ui->f10->hide();
        if(begin->x!=2||begin->y!=2) {ui->f11->setIcon(res_pix[10]);ui->f11->setIconSize(QSize(62,60));} else ui->f11->hide();
        if(begin->x!=2||begin->y!=3) {ui->f12->setIcon(res_pix[11]);ui->f12->setIconSize(QSize(62,60));} else ui->f12->hide();
        if(begin->x!=3||begin->y!=0) {ui->f13->setIcon(res_pix[12]);ui->f13->setIconSize(QSize(62,60));} else ui->f13->hide();
        if(begin->x!=3||begin->y!=1) {ui->f14->setIcon(res_pix[13]);ui->f14->setIconSize(QSize(62,60));} else ui->f14->hide();
        if(begin->x!=3||begin->y!=2) {ui->f15->setIcon(res_pix[14]);ui->f15->setIconSize(QSize(62,60));} else ui->f15->hide();
        if(begin->x!=3||begin->y!=3) {ui->f16->setIcon(res_pix[15]);ui->f16->setIconSize(QSize(62,60));} else ui->f16->hide();*/
        //res_pix.clear();

        //开始求解
        status* last=NULL;
        int check=check_valid();
        if(check==1)
        {
            last=run();
            open.clear();
            close.clear();
        }
        else
        {
            QMessageBox::critical(this, "无解", "此问题状态下无解~换一组数据试一试吧~", QMessageBox::Yes, QMessageBox::Yes);
        }

        //将求解顺序加入列表中
        //qDebug()<<last->mark<<" "<<last->direction<<endl;
        while(last)
        {
            ll.insert(ll.begin(),last);
            last=last->pre;
       }

        for(int i=0;i<ll.size()-1;i++)
        {
            ll[i]->direction=ll[i+1]->direction;
            ll[i]->mark=ll[i+1]->mark;
            //qDebug()<<ll[i]->mark<<" "<<ll[i]->direction<<endl;
        }
        ll[ll.size()-1]->direction=-1;
        ll[ll.size()-1]->mark=-1;
    });

    //如果按下自动生成，则自动显示步骤
    connect(ui->go,&QPushButton::clicked,[=](){
        for(int i=0;i<ll.size();i++)
        {
            qDebug()<<"mark:"<<ll[i]->mark<<"direction:"<<ll[i]->direction<<endl;
            if(ll[i]->mark!=-1)
            {
                buttons[ll[i]->mark]->move_next(ll[i]->direction, (i+1)*500);
            }
        }
        ll.clear();
    });




    //int num=begin->x*4+begin->y+1;
    //QString str=QString(":/res/%1.png").arg(num);

    /*for(int i=0;i<16;i++)
    {

    }
    mylabel* x=new mylabel(":/res/1.png");
    x->setParent(this);
    x->move(100,100);*/
}

void fifteen_puzzle::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/big_beijing.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    pix.load(":/res/beijing.png");
    painter.drawPixmap(413,16,245,219,pix);

    pix.load(":/res/beijing.png");
    painter.drawPixmap(413,286,245,219,pix);

    pix.load(":/res/beijing.png");
    painter.drawPixmap(40,125,290,290,pix);
}

int fifteen_puzzle::check_valid()
{
    //判断是否有解
    int sum1=0;
    int sum2=0;
    int arr1[16]={0},arr2[16]={0};
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            arr1[i*4+j]=end->in[i][j];
            arr2[i*4+j]=begin->in[i][j];
        }
    }
    for(int i=0;i<16;i++)
    {
        for(int j=0;j<i;j++)
        {
            if(arr1[i]&&arr1[i]<arr1[j]) sum1++;
            if(arr2[i]&&arr2[i]<arr2[j]) sum2++;
        }
    }
    int x=begin->x;
    int y=end->x;

    //判断输入状态与目标状态是否有误(输入了重复数据)
    int flag=0;
    int signal1[16]={0},signal2[16]={0};
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            signal1[begin->in[i][j]]++;
            signal2[end->in[i][j]]++;
        }
    }
    for(int i=0;i<16;i++)
    {
        if(!signal1[i]||signal1[i]>1)
            flag=1;
        if(!signal2[i]||signal2[i]>1)
            flag=1;
    }

    //输出错误信息
    if(flag!=0)
    {
        QMessageBox::information(NULL, "Waring", "目标状态有误~", QMessageBox::Yes, QMessageBox::Yes);
        return 0;
    }
    if(abs(y-x)%2==0&&(sum1%2)!=(sum2%2))
    {
        return 0;
    }
    else if(abs(y-x)%2==1&&(sum1%2)==(sum2%2))
    {
        return 0;
    }
    return 1;
}

/*
void fifteen_puzzle::on_automatic_clicked()
{
    //获取初始状态文本中的数据
    begin->in[0][0]=ui->in1->toPlainText().toInt();
    begin->in[0][1]=ui->in2->toPlainText().toInt();
    begin->in[0][2]=ui->in3->toPlainText().toInt();
    begin->in[0][3]=ui->in4->toPlainText().toInt();
    begin->in[1][0]=ui->in5->toPlainText().toInt();
    begin->in[1][1]=ui->in6->toPlainText().toInt();
    begin->in[1][2]=ui->in7->toPlainText().toInt();
    begin->in[1][3]=ui->in8->toPlainText().toInt();
    begin->in[2][0]=ui->in9->toPlainText().toInt();
    begin->in[2][1]=ui->in10->toPlainText().toInt();
    begin->in[2][2]=ui->in11->toPlainText().toInt();
    begin->in[2][3]=ui->in12->toPlainText().toInt();
    begin->in[3][0]=ui->in13->toPlainText().toInt();
    begin->in[3][1]=ui->in14->toPlainText().toInt();
    begin->in[3][2]=ui->in15->toPlainText().toInt();
    begin->in[3][3]=ui->in16->toPlainText().toInt();

    //获取目标状态文本中的数据
    end->in[0][0]=ui->end1->toPlainText().toInt();
    end->in[0][1]=ui->end2->toPlainText().toInt();
    end->in[0][2]=ui->end3->toPlainText().toInt();
    end->in[0][3]=ui->end4->toPlainText().toInt();
    end->in[1][0]=ui->end5->toPlainText().toInt();
    end->in[1][1]=ui->end6->toPlainText().toInt();
    end->in[1][2]=ui->end7->toPlainText().toInt();
    end->in[1][3]=ui->end8->toPlainText().toInt();
    end->in[2][0]=ui->end9->toPlainText().toInt();
    end->in[2][1]=ui->end10->toPlainText().toInt();
    end->in[2][2]=ui->end11->toPlainText().toInt();
    end->in[2][3]=ui->end12->toPlainText().toInt();
    end->in[3][0]=ui->end13->toPlainText().toInt();
    end->in[3][1]=ui->end14->toPlainText().toInt();
    end->in[3][2]=ui->end15->toPlainText().toInt();
    end->in[3][3]=ui->end16->toPlainText().toInt();

    qDebug()<<end->in[3][0]<<endl;

}*/

void fifteen_puzzle::draw_beginscence()
{
    //获取初始状态文本中的数据
    begin->in[0][0]=ui->in1->toPlainText().toInt();
    begin->in[0][1]=ui->in2->toPlainText().toInt();
    begin->in[0][2]=ui->in3->toPlainText().toInt();
    begin->in[0][3]=ui->in4->toPlainText().toInt();
    begin->in[1][0]=ui->in5->toPlainText().toInt();
    begin->in[1][1]=ui->in6->toPlainText().toInt();
    begin->in[1][2]=ui->in7->toPlainText().toInt();
    begin->in[1][3]=ui->in8->toPlainText().toInt();
    begin->in[2][0]=ui->in9->toPlainText().toInt();
    begin->in[2][1]=ui->in10->toPlainText().toInt();
    begin->in[2][2]=ui->in11->toPlainText().toInt();
    begin->in[2][3]=ui->in12->toPlainText().toInt();
    begin->in[3][0]=ui->in13->toPlainText().toInt();
    begin->in[3][1]=ui->in14->toPlainText().toInt();
    begin->in[3][2]=ui->in15->toPlainText().toInt();
    begin->in[3][3]=ui->in16->toPlainText().toInt();
    find_zeros(begin);
    //qDebug()<<"0的位置："<<begin->x<<" "<<begin->y<<endl;
    begin->g=0;
    compute_f(begin);
    begin->pre=NULL;
    //qDebug()<<begin->in[0][0]<<endl;

    //获取目标状态文本中的数据
    end->in[0][0]=ui->end1->toPlainText().toInt();
    end->in[0][1]=ui->end2->toPlainText().toInt();
    end->in[0][2]=ui->end3->toPlainText().toInt();
    end->in[0][3]=ui->end4->toPlainText().toInt();
    end->in[1][0]=ui->end5->toPlainText().toInt();
    end->in[1][1]=ui->end6->toPlainText().toInt();
    end->in[1][2]=ui->end7->toPlainText().toInt();
    end->in[1][3]=ui->end8->toPlainText().toInt();
    end->in[2][0]=ui->end9->toPlainText().toInt();
    end->in[2][1]=ui->end10->toPlainText().toInt();
    end->in[2][2]=ui->end11->toPlainText().toInt();
    end->in[2][3]=ui->end12->toPlainText().toInt();
    end->in[3][0]=ui->end13->toPlainText().toInt();
    end->in[3][1]=ui->end14->toPlainText().toInt();
    end->in[3][2]=ui->end15->toPlainText().toInt();
    end->in[3][3]=ui->end16->toPlainText().toInt();
    find_zeros(end);

}

fifteen_puzzle::~fifteen_puzzle()
{
    delete ui;
}
