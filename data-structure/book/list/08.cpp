#include <iostream>
#include "list.h" // 包含链表头文件
using namespace std;

//已知A,B是两个带头结点的单链表，元素有序递增有序。
//设计一个算法从A,B中公共元素产生单链表C.

//思想：将p指向A的首结点，q指向B的首结点，r指向C的头结点，
//如果p和q的data域相等，则将p结点插入到C中，p和q都移向下一个结点；
//如果不等，则将data域小的结点移向下一个结点。

void MergeList(LinkList &A, LinkList &B, LinkList &C) {
    Lnode *p = A->next; // p指向A的首结点
    Lnode *q = B->next; // q指向B的首结点
    Lnode *r = C;       // r指向C的头结点

    while (p != NULL && q != NULL) { // p和q都不为NULL
        if (p->data == q->data) { // 如果p和q的data域相等
            r->next = p; // 将p结点插入到C中
            r = r->next; // r指向下一个结点
            p = p->next; // p移向下一个结点
            q = q->next; // q移向下一个结点
        } else if (p->data < q->data) { // 如果p的data域小于q的data域
            p = p->next; // p移向下一个结点
        } else { // 如果p的data域大于q的data域
            q = q->next; // q移向下一个结点
        }
    }
    r->next = NULL; // 将C的末尾置为NULL，表示C的末尾
}