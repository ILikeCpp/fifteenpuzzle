#include <QMessageBox>
#include <algorithm>
#include <algorithm>
#include <QDebug>
#include "fifteen_puzzle.h"
#include "struct.h"

status* fifteen_puzzle::run()
{
    open.push_back(begin);
    while(1)
    {
        if(open.empty())
        {
            QMessageBox::critical(this, "无解", "为什么会无解呢= =", QMessageBox::Yes, QMessageBox::Yes);
            return NULL;
        }
        status* node=open[0];
        if(check_goal(node))
        {
            //qDebug()<<"node:"<<node->mark<<" "<<node->direction<<endl;
            return node;
        }
        open.erase(open.begin());
        close.push_back(node);
        expand(node);
        sort(open.begin(),open.end(),cmp);
    }
}

bool cmp(const status* a, const status* b)
{
    return a->f < b->f;
}


void fifteen_puzzle::expand(status* node)
{
    //空格向上移动产生的子结点
    if (node->x != 0)
    {
        status* n1 = new status;
        *n1 = *node;
        swap(n1->in[n1->x][n1->y], n1->in[n1->x - 1][n1->y]);
        int num=(node->x-1)*4+node->y;
        modify_pointer(node, n1,2,num);
    }
    //空格向下移动产生的子结点
    if (node->x != 3)
    {
        status* n2 = new status;
        *n2 = *node;
        swap(n2->in[n2->x][n2->y], n2->in[n2->x + 1][n2->y]);
        int num=(node->x+1)*4+node->y;
        modify_pointer(node, n2,1,num);
    }
    //空格向左移动产生的子结点
    if (node->y != 0)
    {
        status* n3 = new status;
        *n3 = *node;
        swap(n3->in[n3->x][n3->y], n3->in[n3->x][n3->y - 1]);
        int num=(node->x)*4+node->y-1;
        modify_pointer(node, n3,4,num);
    }
    //空格向右移动产生的子结点
    if (node->y != 3)
    {
        status* n4 = new status;
        *n4 = *node;
        swap(n4->in[n4->x][n4->y], n4->in[n4->x][n4->y + 1]);
        int num=(node->x)*4+node->y+1;
        modify_pointer(node, n4,3,num);
    }
}


void fifteen_puzzle::find_zeros(status* s)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (s->in[i][j] == 0)
            {
                s->x = i;
                s->y = j;
            }
        }
    }
}

void fifteen_puzzle::compute_f(status* node)
{
    node->h = count_nat(node);
    node->f = node->h + node->g;
}

int fifteen_puzzle::count_nat(status* node)
{
    int re = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (node->in[i][j] && node->in[i][j] != end->in[i][j])
            {
                re++;
            }
        }
    }
    return re;
}

int fifteen_puzzle::check_goal(status* node)
{
    int i, flag = 0;
    for (i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (node->in[i][j] != end->in[i][j])
            {
                flag = 1;
                break;
            }
        }
        if (flag == 1) break;
    }
    if (i == 4) return 1;
    else return 0;
}

void fifteen_puzzle::modify_pointer(status* node, status* n1,int direction,int mark)
{
    int flag1 = 0, flag2 = 0;
    status* x = judge_inclose(n1, flag1);
    status* y = judge_inopen(n1, flag2);
    if (flag1 == 0 && flag2 == 0) //不在open表也不在close表中
    {
        find_zeros(n1);
        n1->g = node->g + 1;
        compute_f(n1);
        n1->pre = node;
        n1->direction=direction;
        n1->mark=mark;
        open.push_back(n1);
    }
    else if (flag2 == 1 && flag1 == 0) //在open表中
    {
        if (node->g + 1 < y->g) //不用生成新的结点了，舍弃n1
        {
            y->g = node->g + 1;
            y->pre = node;
            y->direction=direction;
            y->mark=mark;
        }
    }
    else if (flag2 == 0 && flag1 == 1) //在close表中
    {
        if (node->g + 1 < x->g)
        {
            x->g = node->g + 1;
            x->pre = node;
            close.erase(remove(close.begin(), close.end(), x), close.end());
            x->direction=direction;
            x->mark=mark;
            open.push_back(x);
        }
    }
}

status* fifteen_puzzle::judge_inclose(status* node, int& flag2)
{
    int k;
    for (k = 0; k < close.size(); k++)
    {
        int flag = 0;
        //判断状态是否相同
        int i;
        for (i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (node->in[i][j] != close[k]->in[i][j])
                {
                    flag = 1;
                    break;
                }
            }
            if (flag == 1) break;
        }
        if (i == 4) //找到了
        {
            flag2 = 1;
            break;
        }
    }
    if (flag2 == 1) return close[k];  //记得测试找到了
    else return NULL;
}

status* fifteen_puzzle::judge_inopen(status* node, int& flag2)
{
    int k;
    for (k = 0; k < open.size(); k++)
    {
        int flag = 0;
        //判断状态是否相同
        int i;
        for (i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (node->in[i][j] != open[k]->in[i][j])
                {
                    flag = 1;
                    break;
                }
            }
            if (flag == 1) break;
        }
        if (i == 4) //找到了
        {
            flag2 = 1;
            break;
        }
    }
    if (flag2 == 1) return open[k];
    else return NULL;
}
