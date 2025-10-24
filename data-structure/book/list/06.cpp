#include <iostream>
#include "list.h" // 包含链表头文件
using namespace std;
// 现有一个线性表{a1,b1,a2,b2......an,bn}，将其拆分为两个线性表{a1,a2,......an}和{bn, bn-1, ..., b2, b1}
// 思路：
// 1. L1采用尾插法，保持a1,a2,...,an的顺序
// 2. L2采用头插法，实现bn,bn-1,...,b2,b1的倒序

void SplitList(LinkList &L, LinkList &L1, LinkList &L2) {
    Lnode *p = L->next; // p指向首结点
    L1 = new Lnode; // 创建L1的头结点
    L2 = new Lnode; // 创建L2的头结点
    L1->next = NULL; // 初始化L1为空
    L2->next = NULL; // 初始化L2为空
    Lnode *tail1 = L1; // L1的尾指针，用于尾插法
    
    while (p != NULL) {
        // 处理a元素：用尾插法插入L1，保持原顺序
        Lnode *next = p->next; // 保存下一个节点
        tail1->next = p; // 将a元素插入L1末尾
        tail1 = p; // 更新尾指针
        p = next; // 移动到b元素
        
        if (p != NULL) {
            // 处理b元素：用头插法插入L2，实现倒序
            next = p->next; // 保存下一个节点
            p->next = L2->next; // 将b元素的next指向L2原来的第一个节点
            L2->next = p; // 将b元素插入L2头部
            p = next; // 移动到下一个a元素
        }
    }
    
    tail1->next = NULL; // 将L1的末尾置为NULL
}   