#include <iostream>
#include "list.h" //包含链表头文件
using namespace std;

/* 题目16：设有一个长度为n(n为偶数)的不带头结点的单链表，且结点值都大于0。设计算法求这
    个单链表的最大孪生和。孪生和定义为一个结点值与其孪生结点值之和，对于第i个结点
    (从0开始)，其孪生结点为第n - i - 1个结点。要求：
    1）给出算法的基本设计思想。
    2）根据设计思想，采用C或C++语言描述算法，关键之处给出注释。
    3）说明你的算法的时间复杂度和空间复杂度。 */
// 单链表结点定义
struct LNode
{
    int data;
    LNode *next;
};
typedef LNode *LinkList;

/*
算法基本设计思想：
方法一：数组辅助法
1. 遍历链表，将所有结点值存入数组
2. 通过数组下标直接计算孪生和：arr[i] + arr[n-1-i]
3. 找出所有孪生和中的最大值

方法二：双指针 + 栈法
1. 使用栈存储前半部分结点的值
2. 用指针遍历后半部分，与栈中元素配对计算孪生和
3. 找出最大值

方法三：链表反转法
1. 找到链表中点，将后半部分反转
2. 用两个指针分别从前半部分和反转后的后半部分开始遍历
3. 计算孪生和并找出最大值
*/

// 方法一：数组辅助法（最直观）
int FindMaxTwinSum1(LinkList L)
{
    if (L == NULL)
        return 0;

    // 第一步：计算链表长度并存储到数组
    int n = 0;
    LNode *p = L;
    while (p != NULL)
    {
        n++;
        p = p->next;
    }

    // 创建数组存储结点值
    int *arr = new int[n];
    p = L;
    for (int i = 0; i < n; i++)
    {
        arr[i] = p->data;
        p = p->next;
    }

    // 第二步：计算所有孪生和，找出最大值
    int maxSum = 0;
    for (int i = 0; i < n / 2; i++)
    {
        int twinSum = arr[i] + arr[n - 1 - i]; // 第i个与第n-1-i个的孪生和
        if (twinSum > maxSum)
        {
            maxSum = twinSum;
        }
    }

    delete[] arr; // 释放内存
    return maxSum;
}

// 方法二：栈辅助法
#include <stack>
int FindMaxTwinSum2(LinkList L)
{
    if (L == NULL)
        return 0;

    // 第一步：计算链表长度
    int n = 0;
    LNode *p = L;
    while (p != NULL)
    {
        n++;
        p = p->next;
    }

    // 第二步：将前半部分压入栈
    stack<int> st;
    p = L;
    for (int i = 0; i < n / 2; i++)
    {
        st.push(p->data);
        p = p->next;
    }

    // 第三步：遍历后半部分，与栈中元素配对
    int maxSum = 0;
    for (int i = n / 2; i < n; i++)
    {
        int twinSum = st.top() + p->data; // 栈顶元素与当前元素的孪生和
        st.pop();
        if (twinSum > maxSum)
        {
            maxSum = twinSum;
        }
        p = p->next;
    }

    return maxSum;
}

// 方法三：链表反转法（空间最优）
// 辅助函数：反转链表
LNode *ReverseList(LNode *head)
{
    LNode *prev = NULL;
    LNode *curr = head;

    //不带头结点的链表反转 
    while (curr != NULL)
    {
        LNode *nextTemp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nextTemp;
    }

    return prev;//
}

int FindMaxTwinSum3(LinkList L)
{
    if (L == NULL)
        return 0;

    // 第一步：找到链表中点
    LNode *slow = L;
    LNode *fast = L;
    LNode *prevSlow = NULL;

    while (fast != NULL && fast->next != NULL)
    {
        prevSlow = slow;
        slow = slow->next;
        fast = fast->next->next;
    }

    // 第二步：断开链表，反转后半部分
    prevSlow->next = NULL;                 // 断开前后两部分
    LNode *secondHalf = ReverseList(slow); // 反转后半部分

    // 第三步：双指针遍历，计算孪生和
    int maxSum = 0;
    LNode *p1 = L;          // 前半部分指针
    LNode *p2 = secondHalf; // 后半部分指针

    while (p1 != NULL && p2 != NULL)
    {
        int twinSum = p1->data + p2->data;
        if (twinSum > maxSum)
        {
            maxSum = twinSum;
        }
        p1 = p1->next;
        p2 = p2->next;
    }

    // 第四步：恢复链表结构（可选）
    secondHalf = ReverseList(secondHalf);
    prevSlow->next = secondHalf;

    return maxSum;
}