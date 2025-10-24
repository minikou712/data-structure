#include <iostream>
#include "list.h" //包含链表头文件
using namespace std;

/* 题目20：【2019统考真题】设线性表L=(a1,a2,a3,...,an-2,an-1,an)采用带头结点的单链表保存，链
   表中的结点定义如下：
   typedef struct node
   {   int data;
       struct node*next;
   }NODE;
   请设计一个空间复杂度为O(1)且时间上 尽可能高效的算法，重新排列L中的各结点，得
   到线性表L'=(a1,an,a2,an-1,a3,an-2,...)。要求：
   1）给出算法的基本设计思想。
   2）根据设计思想，采用C或C++语言描述算法，关键之处给出注释。
   3）说明你所设计算法的时间复杂度。 */

// 1.将链表分为两部分，前半部分和后半部分
// 2.将后半部分逆置，在遍历前半部分的同时，在间隔内插入后半部分结点

// 逆置链表函数
Lnode *reverseList(Lnode *head)
{
    Lnode *prev = nullptr;
    Lnode *curr = head;
    Lnode *next = nullptr;

    while (curr != nullptr)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

// 重新排列链表算法
void rearrangeList(LinkList L)
{
    if (L == nullptr || L->next == nullptr || L->next->next == nullptr)
    {
        return; // 空链表或只有一个结点，无需处理
    }

    // 步骤1：使用快慢指针找到链表中点，将链表分为两部分
    Lnode *slow = L->next; // 慢指针，从第一个数据结点开始
    Lnode *fast = L->next; // 快指针
    Lnode *prevSlow = L;   // 记录慢指针的前一个结点

    // 找到中点
    while (fast != nullptr && fast->next != nullptr)
    {
        prevSlow = slow;
        slow = slow->next;
        fast = fast->next->next;
    }

    // 断开链表，分为两部分
    prevSlow->next = nullptr;
    Lnode *secondHalf = slow;

    // 步骤2：逆置后半部分
    secondHalf = reverseList(secondHalf);

    // 步骤3：交替合并两部分
    Lnode *first = L->next;     // 前半部分的第一个结点
    Lnode *second = secondHalf; // 后半部分的第一个结点
    Lnode *curr = L;            // 当前插入位置

    while (first != nullptr && second != nullptr)
    {
        // 插入前半部分的结点
        curr->next = first;
        first = first->next;
        curr = curr->next;

        // 插入后半部分的结点
        curr->next = second;
        second = second->next;
        curr = curr->next;
    }

    // 如果前半部分还有剩余结点（当总长度为奇数时）
    if (first != nullptr)
    {
        curr->next = first;
    }
}
