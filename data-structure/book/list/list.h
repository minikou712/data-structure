// 创建链表头文件
#ifndef LIST_H
#define LIST_H

#include <iostream>
using namespace std;

typedef int ElemType;

// 定义链表节点结构
typedef struct Lnode {
    ElemType data;
    Lnode *next; // 指向下一个节点的指针
    Lnode *prior;
} Lnode, *LinkList;


// 链表操作函数声明
LinkList InitList();                     // 初始化链表
bool IsEmpty(LinkList L);                // 判断链表是否为空
bool InsertNode(LinkList &L, int pos, ElemType e); // 在指定位置插入节点
bool DeleteNode(LinkList &L, int pos);   // 删除指定位置的节点
void PrintList(LinkList L);              // 打印链表
void DestroyList(LinkList &L);           // 销毁链表
int  ListLength(LinkList &L);
#endif // LIST_H
