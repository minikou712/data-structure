#include <iostream>
#include "list.h" //包含链表头文件
using namespace std;

/* 题目17：【2009统考真题】已知一个带有表头结点的单链表，结点结构为
   |data|link|
   假设该链表只存储了关键字list，在不改变链表的前提下，请设计一个尽可能高效的
   算法，查找链表中倒数第k个位置上的结点（k为正整数）。若查找成功，算法输出该结
   点的data域的值，并返回1；否则，只返回0。要求：
   1）描述算法的基本设计思想。
   2）描述算法的详细实现步骤。
   3）根据设计思想和实现步骤，采用你所熟悉语言（使用C、C++或Java语言
   实现），关键之处请给出注释。 */

// 带头结点的单链表结点定义
struct LNode {
    int data;
    LNode* next;
};
typedef LNode* LinkList;

/*
方法对比分析：
方法一：两次遍历法（你的思路）- 简单直观
方法二：双指针法（最优解）- 一次遍历，更高效
方法三：递归法 - 代码简洁，但有额外开销
*/

// 方法一：两次遍历法（你的实现思路）
int FindKthFromEnd_TwoPass(LinkList L, int k) {
    /*
    算法基本设计思想：
    1. 第一次遍历：计算链表长度len（不包括头结点）
    2. 第二次遍历：找到第len-k+1个结点（正数第几个）
    3. 输出结果
    */
    
    if (L == NULL || L->next == NULL || k <= 0) {
        return 0;  // 空链表或k无效
    }
    
    // 第一步：计算链表长度
    int len = 0;
    LNode* p = L->next;  // 从第一个数据结点开始
    while (p != NULL) {
        len++;
        p = p->next;
    }
    
    // 第二步：检查k是否有效
    if (k > len) {
        return 0;  // k超出链表长度
    }
    
    // 第三步：找到正数第(len-k+1)个结点，即倒数第k个结点
    p = L->next;  // 重新从第一个数据结点开始
    for (int i = 1; i < len - k + 1; i++) {
        p = p->next;
    }
    
    // 第四步：输出结果
    cout << "倒数第" << k << "个结点的值: " << p->data << endl;
    return 1;
}

// 方法二：双指针法（最优解 - 一次遍历）
int FindKthFromEnd_OnePass(LinkList L, int k) {
    /*
    算法基本设计思想：
    1. 使用两个指针fast和slow，初始都指向头结点
    2. fast指针先走k步
    3. 然后fast和slow同时向前移动，直到fast到达链表末尾
    4. 此时slow指向的就是倒数第k个结点
    */
    
    if (L == NULL || L->next == NULL || k <= 0) {
        return 0;
    }
    
    LNode* fast = L;   // 快指针
    LNode* slow = L;   // 慢指针
    
    // 第一步：快指针先走k步
    for (int i = 0; i < k; i++) {
        if (fast->next == NULL) {
            return 0;  // k超出链表长度
        }
        fast = fast->next;
    }
    
    // 第二步：两个指针同时移动，直到快指针到达末尾
    while (fast != NULL) {
        fast = fast->next;
        slow = slow->next;
    }
    
    // 第三步：slow现在指向倒数第k个结点
    cout << "倒数第" << k << "个结点的值: " << slow->data << endl;
    return 1;
}

// 方法三：递归法
int recursiveIndex = 0;  // 全局变量记录当前是倒数第几个

int FindKthFromEnd_Recursive(LNode* node, int k) {
    /*
    算法基本设计思想：
    1. 递归到链表末尾
    2. 在回溯过程中计数
    3. 当计数等于k时，找到目标结点
    */
    
    if (node == NULL) {
        recursiveIndex = 0;
        return 0;
    }
    
    // 递归到链表末尾
    int result = FindKthFromEnd_Recursive(node->next, k);
    if (result == 1) {
        return 1;  // 已找到，直接返回
    }
    
    // 回溯时计数
    recursiveIndex++;
    if (recursiveIndex == k) {
        cout << "倒数第" << k << "个结点的值: " << node->data << endl;
        return 1;
    }
    
    return 0;
}

int FindKthFromEnd_Wrapper(LinkList L, int k) {
    if (L == NULL || L->next == NULL || k <= 0) {
        return 0;
    }
    return FindKthFromEnd_Recursive(L->next, k);
}

// 辅助函数：创建带头结点的测试链表
LinkList CreateTestList(int arr[], int n) {
    LinkList L = new LNode{0, nullptr};  // 头结点，data域可以是任意值
    LNode* tail = L;
    
    for (int i = 0; i < n; i++) {
        LNode* newNode = new LNode{arr[i], nullptr};
        tail->next = newNode;
        tail = newNode;
    }
    
    return L;
}

// 辅助函数：打印链表
void PrintList(LinkList L) {
    if (L == NULL || L->next == NULL) {
        cout << "空链表" << endl;
        return;
    }
    
    LNode* p = L->next;  // 跳过头结点
    cout << "链表: ";
    while (p != NULL) {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}

// 测试函数
void TestFindKthFromEnd() {
    cout << "=== 查找倒数第k个结点测试 ===" << endl;
    
    // 创建测试链表：1 -> 2 -> 3 -> 4 -> 5
    int arr[] = {1, 2, 3, 4, 5};
    LinkList L = CreateTestList(arr, 5);
    PrintList(L);
    
    cout << "\n各种方法测试倒数第2个结点：" << endl;
    
    cout << "方法一（两次遍历）：";
    int result1 = FindKthFromEnd_TwoPass(L, 2);
    cout << "返回值: " << result1 << endl;
    
    cout << "方法二（双指针）：";
    int result2 = FindKthFromEnd_OnePass(L, 2);
    cout << "返回值: " << result2 << endl;
    
    cout << "方法三（递归）：";
    int result3 = FindKthFromEnd_Wrapper(L, 2);
    cout << "返回值: " << result3 << endl;
    
    cout << "\n边界测试 - 查找倒数第6个结点（超出范围）：" << endl;
    cout << "方法一：返回值 " << FindKthFromEnd_TwoPass(L, 6) << endl;
    cout << "方法二：返回值 " << FindKthFromEnd_OnePass(L, 6) << endl;
}

int main() {
    TestFindKthFromEnd();
    return 0;
}