#include <iostream>
#include "list.h" //包含链表头文件
using namespace std;

/* 题目10：两个整数序列A = a1, a2, a3, ..., am和B = b1, b2, b3, ..., bn已经存入两个单链表中，设计一
   个算法，判断序列B是否是序列A的连续子序列。 */

// 实现思路
// 1. 遍历链表A，对于A中的每个节点作为起始点
// 2. 从该起始点开始，同时遍历A和B，比较对应元素
// 3. 如果B的所有元素都匹配成功，则B是A的连续子序列
// 4. 如果某个元素不匹配，则从A的下一个节点重新开始匹配
// 5. 如果A遍历完都没有找到完整匹配，则B不是A的连续子序列

bool IsSubsequence(LinkList LA, LinkList LB)
{
   // 如果B为空，认为是任何序列的子序列
   if (LB->next == NULL)
   {
      return true;
   }

   // 如果A为空但B不为空，则B不是A的子序列
   if (LA->next == NULL)
   {
      return false;
   }

   Lnode *pa = LA->next; // 指向A的当前起始位置

   while (pa != NULL)
   {
      Lnode *tempA = pa;    // 从pa开始匹配
      Lnode *pb = LB->next; // 从B的第一个元素开始

      // 尝试从当前位置开始匹配整个序列B
      while (tempA != NULL && pb != NULL && tempA->data == pb->data)
      {
         tempA = tempA->next;
         pb = pb->next;
      }

      // 如果B的所有元素都匹配成功（pb为NULL），则找到了连续子序列
      if (pb == NULL)
      {
         return true;
      }

      // 如果匹配失败，从A的下一个位置重新开始
      pa = pa->next;
   }

   // 遍历完A都没有找到匹配，返回false
   return false;
}