#include <iostream>
#include "list.h" // 包含链表头文件
using namespace std;


//在一个递增有序的单链表中，删除重复元素
//思想：将p指向首结点，q指向p的下一个结点，如果p和q的data域相等，
//则删除q结点，否则p移向下一个结点

void DeleteDuplicate(LinkList &L) {
    Lnode *p = L->next; // p指向首结点
    Lnode *q;          // q指向下一个结点

    while (p != NULL && p->next != NULL) { // p不为NULL,且p的下一个结点不为NULL
        if (p->data == p->next->data) { // 如果p和p的下一个结点的data域相等
            q = p->next; // q指向p的下一个结点
            p->next = q->next; // 将p的next指针指向q的下一个结点
            delete q; // 删除q结点
        } else {
            p = p->next; // p移向下一个结点
        }
    }
}

