#ifndef STRUCT_H
#define STRUCT_H

typedef struct status
{
    int in[4][4];
    int g;
    int h;
    int f;
    struct status *pre;
    int x; //空格x坐标
    int y; //空格y坐标
    int direction; //上一个状态到达此状态移动的方向
    int mark; //上一个状态移动的数码序号(方便作图)
}status;

bool cmp(const status* a,const status* b);

#endif // STRUCT_H
