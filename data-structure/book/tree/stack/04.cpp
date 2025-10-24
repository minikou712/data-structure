#include <iostream>
#include"list.h"
#include<stack>
using namespace std;
// 题目内容： 设单链表的头节点指针为L，结点结构由data和next两个域构成，其中data域为字符型。
//试设计算法判断该链表的全部n个字符是否中心对称，
//例如xyx、xyyx都是中心对称。

//思想： 如果是中心对称的，那么入栈的字符和出栈的字符应该是相同的。 

bool IsSymmetric(LinkList L)
{
    if (L == nullptr || L->next == nullptr) // 空链表或只有头结点
        return true;

    stack<ElemType> S;
    Lnode *slow = L->next; // 慢指针，从第一个数据节点开始
    Lnode *fast = L->next; // 快指针，从第一个数据节点开始

    // 快慢指针找中点，同时将前半部分入栈
    while (fast != nullptr && fast->next != nullptr)
    {
        S.push(slow->data); // 将慢指针指向的字符入栈
        slow = slow->next;   // 慢指针走一步
        fast = fast->next->next; // 快指针走两步
    }

    // 如果链表长度为奇数，跳过中间字符
    if (fast != nullptr) // fast不为空说明链表长度为奇数
    {
        slow = slow->next;
    }

    // 检查后半部分字符是否与栈中字符匹配
    while (slow != nullptr && !S.empty())
    {
        if (S.top() != slow->data)
            return false;
        S.pop();
        slow = slow->next;
    }

    return S.empty(); // 栈为空说明完全匹配
}
