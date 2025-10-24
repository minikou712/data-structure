#include <iostream>
#include "list.h" //包含链表头文件
using namespace std;

/* 题目19：【2015统考真题】用单链表保存m个整数，结点的结构为|data||link|，且|data|≤
   n（n为正整数）。现要求设计一个时间复杂度尽可能高效的算法，对于链表中data的
   绝对值相等的结点，仅保留第一次出现的结点而删除其余绝对值相等的结点。例如，若
   给定的单链表head如下：
   head -> 21 -> -15 -> -15 -> -7 -> 15
   则删除结点后的head为：
   head -> 21 -> -15 -> -7
   要求：
   1）给出算法的基本设计思想。
   2）使用C或C++语言，给出单链表结点的数据类型定义。
   3）根据设计思想，采用C或C++语言描述算法，关键之处给出注释。
   4）说明你所设计算法的时间复杂度和空间复杂度。 */

// 2）单链表结点数据类型定义
struct LNode
{
   int data;    // 数据域，存储整数
   LNode *next; // 指针域，指向下一个结点
};
typedef LNode *LinkList;

/*
1）算法基本设计思想：
利用题目条件|data| ≤ n，使用数组模拟哈希表来记录已出现的绝对值：
- 创建大小为n+1的布尔数组visited，下标表示绝对值，值表示是否已出现
- 遍历链表，对每个结点计算data的绝对值
- 如果绝对值首次出现，标记为已访问并保留结点
- 如果绝对值已出现过，删除当前结点
- 使用前驱指针简化删除操作
*/

// 3）算法实现
LinkList RemoveDuplicatesByAbs(LinkList head, int n)
{
   // 边界条件检查
   if (head == NULL)
   {
      return NULL;
   }

   // 创建访问标记数组，大小为n+1（因为绝对值范围是0到n）
   bool *visited = new bool[n + 1];
   // 初始化所有元素为false，表示都未访问过
   for (int i = 0; i <= n; i++)
   {
      visited[i] = false;
   }

   LinkList prev = NULL; // 前驱指针，用于删除操作
   LinkList curr = head; // 当前指针，用于遍历

   // 遍历链表
   while (curr != NULL)
   {
      int absValue = abs(curr->data); // 计算当前结点data的绝对值

      if (visited[absValue])
      {
         // 该绝对值已经出现过，删除当前结点
         if (prev != NULL)
         {
            prev->next = curr->next; // 前驱结点跳过当前结点
         }
         else
         {
            head = curr->next; // 删除的是头结点，更新头指针
         }

         LNode *nodeToDelete = curr; // 保存要删除的结点
         curr = curr->next;          // 移动到下一个结点
         delete nodeToDelete;        // 释放内存
      }
      else
      {
         // 该绝对值首次出现，标记为已访问并保留结点
         visited[absValue] = true;
         prev = curr;       // 更新前驱指针
         curr = curr->next; // 移动到下一个结点
      }
   }

   delete[] visited; // 释放动态分配的数组内存
   return head;      // 返回处理后的链表头指针
}

// 方法二：使用哈希表实现（适用于n很大的情况）
#include <unordered_set>
LinkList RemoveDuplicatesByAbs_Hash(LinkList head)
{
   if (head == NULL)
   {
      return NULL;
   }

   unordered_set<int> visited; // 使用STL的哈希表
   LinkList prev = NULL;
   LinkList curr = head;

   while (curr != NULL)
   {
      int absValue = abs(curr->data);

      if (visited.find(absValue) != visited.end())
      {
         // 绝对值已存在，删除结点
         if (prev != NULL)
         {
            prev->next = curr->next;
         }
         else
         {
            head = curr->next;
         }

         LNode *nodeToDelete = curr;
         curr = curr->next;
         delete nodeToDelete;
      }
      else
      {
         // 绝对值首次出现，加入哈希表
         visited.insert(absValue);
         prev = curr;
         curr = curr->next;
      }
   }

   return head;
}