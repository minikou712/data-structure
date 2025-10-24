// 创建顺序表头文件
#ifndef LIST_H
#define LIST_H

#include <iostream>
using namespace std;

typedef int ElemType;

// 定义顺序表结构
typedef struct Lnode {
    ElemType *data; // 数据域
    int length; // 顺序表的长度
} sqList;


#endif // LIST_H
