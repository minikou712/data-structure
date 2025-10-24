#include <iostream>
#include "list.h" // 包含链表头文件
using namespace std;

// 在带头结点的单链表中，所有节点无序，试删除表中介于两个值之间的元素
void DeleteBetween(LinkList &L, ElemType x, ElemType y) // 删除介于x和y之间的结点
{
    Lnode *p = L->next, *q = L; // p 指向当前节点，q 指向 p 的前驱节点
    while (p != NULL)
    {
        if (p->data >= x && p->data <= y)
        {
            q->next = p->next; // 跳过当前节点
            delete p;          // 释放当前节点
            p = q->next;       // 更新 p 为下一个节点
        }
        else    //必须else
        {
            q = p;             // 前驱节点后移
            p = p->next;       // 当前节点后移
        }
    }
}