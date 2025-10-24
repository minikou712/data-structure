#include<iostream>
#include "list.h" //包含链表头文件
using namespace std;




//编写在带头结点的单链表中，删除最小值结点的高效算法
//在遍历过程中不断记录最小节点与其前驱

void DeleteMin(LinkList& L) //删除最小值结点
{
    if (L->next == NULL) return; // 如果链表为空，直接返回
    
    Lnode* p = L->next; // p指向首结点
    Lnode* q = L;       // q指向头结点 前驱

    Lnode* minNode = p; // 初始化最小结点为首结点
    Lnode* minPrev = q; // 初始化最小结点的前驱为头结点
    
    while (p != NULL) { // 当p不为NULL时
        if (p->data < minNode->data) { // 如果当前结点的data域小于最小结点的data域
            minNode = p; // 更新最小结点
            minPrev = q; // 更新最小结点的前驱
        }
        q = p; // q指向当前结点
        p = p->next; // p移向下一个结点
    }   

    // 删除最小值结点
    if (minNode != NULL) {
        minPrev->next = minNode->next; // 将前驱的next指向最小结点的下一个结点
        delete minNode;                // 释放最小结点的内存
    }
}   