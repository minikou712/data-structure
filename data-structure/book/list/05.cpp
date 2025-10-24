#include <iostream>
#include "list.h" // 包含链表头文件
using namespace std;


//给定两个单链表，试找出它们的公共结点
//公共结点是指两个链表中相同的结点，要求时间复杂度为O(n)，空间复杂度为O(1)
//思路：先求出两个链表的长度，假设L1的长度为m，L2的长度为n，m>n，

//则先让L1走m-n步，然后同时让L1和L2走，直到相遇  核心为了让L1和L2的指针在同一位置上开始比较
//如果相遇，则返回相遇的结点，否则返回NULL

//注意：******此处的相遇是指两个链表中相同的结点，而不是值相同的结点


Lnode *findCommonNode(LinkList L1, LinkList L2) {
    if (L1 == NULL || L2 == NULL) return NULL; // 如果链表为空，返回NULL
    int len1 = ListLength(L1); // 求L1的长度
    int len2 = ListLength(L2); // 求L2的长度
    int len = len1 - len2; // 求长度差
    if (len < 0) { // 如果L1的长度小于L2的长度，则交换L1和L2
        LinkList temp = L1;
        L1 = L2;
        L2 = temp;
        len = -len; // 重新计算长度差
    }
    for (int i = 0; i < len; i++) { // 让L1走len步
        L1 = L1->next;
    }
    while (L1 != NULL && L2 != NULL) { // 同时让L1和L2走，直到相遇
        if (L1 == L2) return L1; // 如果相遇，则返回相遇的结点
        L1 = L1->next;
        L2 = L2->next;
    }
    return NULL; // 如果没有相遇，则返回NULL
}




