#include<iostream>
#include "list.h" //包含链表头文件
using namespace std;

//在带头结点的单链表中，删除所有值为x的结点,假设x的值不唯一

void DeleteX(LinkList& L,ElemType x) //删除值为x的结点
{
    Lnode* p = L->next; // p指向首结点
    Lnode* q = L;       // q指向头结点

    while (p != NULL) { // 当p不为NULL时
        if (p->data == x) { // 如果p结点的data域等于x
            q->next = p->next; // 删除p结点，将q的next指向p的下一个结点
            delete p; // 释放p结点的内存
            p = q->next; // p移向下一个结点
        } else {
            q = p; // q指向当前的p结点
            p = p->next; // p移向下一个结点
        }
    }
}
