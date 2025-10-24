#include <iostream>
#include "list.h" //包含链表头文件
using namespace std;

/* 题目09：已知两个链表A和B分别表示两个集合，其元素递增排列，编制函数，求A与B的交集，
   并存放于A链表中。 */

// 实现思路
// 1. 使用两个指针pa和pb分别遍历链表A和B
// 2. 使用尾插法将交集元素存储到新的结果链表中
// 3. 比较pa和pb指向节点的数据：
//    - 相等：加入交集，两指针都后移
//    - pa < pb：pa后移
//    - pa > pb：pb后移
// 4. 释放原链表A和B中不在交集中的节点

LinkList Union(LinkList &LA, LinkList &LB)
{
   Lnode *pa = LA->next; // 指向链表A的第一个数据节点
   Lnode *pb = LB->next; // 指向链表B的第一个数据节点
   Lnode *tail = LA;     // 尾指针，用于尾插法构建结果链表
   LA->next = NULL;      // 重新初始化LA作为结果链表

   while (pa != NULL && pb != NULL)
   {
      if (pa->data == pb->data)
      {
         // 找到交集元素，使用尾插法加入结果链表
         tail->next = pa;
         tail = pa;
         Lnode *temp = pa;
         pa = pa->next;
         // 释放链表B中对应的节点
         Lnode *tempB = pb;
         pb = pb->next;
         delete tempB;
         temp->next = NULL; // 断开原链接
      }
      else if (pa->data < pb->data)
      {
         // pa指向的元素较小，pa后移，释放当前节点
         Lnode *temp = pa;
         pa = pa->next;
         delete temp;
      }
      else
      {
         // pb指向的元素较小，pb后移，释放当前节点
         Lnode *temp = pb;
         pb = pb->next;
         delete temp;
      }
   }

   // 释放链表A中剩余的节点（这些节点不在交集中）
   while (pa != NULL)
   {
      Lnode *temp = pa;
      pa = pa->next;
      delete temp;
   }
   
   // 释放链表B中剩余的节点
   while (pb != NULL)
   {
      Lnode *temp = pb;
      pb = pb->next;
      delete temp;
   }
   
   // 释放链表B的头节点
   delete LB;
   LB = NULL;

   return LA; // 返回存储交集的链表A
}