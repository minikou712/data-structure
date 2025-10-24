#include <iostream>
#include "list.h" //包含链表头文件
using namespace std;

/* 题目11：设计一个算法用于判断带头结点的循环双链表是否对称。 */
// 实现思路
// 1. 使用双指针法：一个从头开始向后遍历，一个从尾开始向前遍历
// 2. 比较对应位置的数据是否相等
// 3. 当两个指针相遇或交错时，说明遍历完成
// 4. 如果所有对应位置的数据都相等，则链表对称

bool IsSymmetric(LinkList &L)
{
    // 空链表认为是对称的
    if (L->next == L)
    {
        return true;
    }

    Lnode *left = L->next;   // 从第一个数据节点开始向后遍历
    Lnode *right = L->prior; // 从最后一个数据节点开始向前遍历

    // 当left和right没有相遇或交错时继续比较   相遇奇数数据    交错偶数数据
    while (left != right && left->prior != right)
    {
        // 比较对应位置的数据
        if (left->data != right->data)
        {
            return false;
        }

        // 移动指针
        left = left->next;
        right = right->prior;
    }

    return true;
}