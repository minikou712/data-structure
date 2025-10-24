#include <iostream>
#include "list.h" //包含链表头文件
using namespace std;

/* 题目12：有两个循环单链表，链表头指针分别为h1和h2，编写一个函数将链表h2链接到链表
   h1之后，要求链接后的链表仍保持循环链表的形式。 */
   
// 实现思路
// 1. 找到h1的尾结点（指向h1的节点）
// 2. 找到h2的尾结点（指向h2的节点）
// 3. 将h1的尾结点指向h2的第一个数据节点
// 4. 将h2的尾结点指向h1，形成新的循环链表
// 5. 释放h2头结点（可选，取决于需求）

void LinkCircularLists(LinkList &h1, LinkList &h2)
{
   // 如果h1为空，直接将h2赋给h1
   if (h1 == NULL || h1->next == h1)
   {
      h1 = h2;
      return;
   }

   // 如果h2为空或只有头结点，无需操作
   if (h2 == NULL || h2->next == h2)
   {
      return;
   }

   // 找到h1的尾结点（指向h1的节点）
   Lnode *tail1 = h1;
   while (tail1->next != h1)
   {
      tail1 = tail1->next;
   }

   // 找到h2的尾结点（指向h2的节点）
   Lnode *tail2 = h2;
   while (tail2->next != h2)
   {
      tail2 = tail2->next;
   }

   // 连接两个循环链表
   tail1->next = h2->next; // h1的尾结点指向h2的第一个数据节点
   tail2->next = h1;       // h2的尾结点指向h1的头结点

   // 释放h2的头结点
   delete h2;
   h2 = NULL;
}

// 方法二：保留h2头结点的版本
void LinkCircularLists2(LinkList &h1, LinkList &h2)
{
   // 如果h1为空，直接将h2赋给h1
   if (h1 == NULL || h1->next == h1)
   {
      h1 = h2;
      return;
   }

   // 如果h2为空或只有头结点，无需操作
   if (h2 == NULL || h2->next == h2)
   {
      return;
   }

   // 找到h1的尾结点
   Lnode *tail1 = h1;
   while (tail1->next != h1)
   {
      tail1 = tail1->next;
   }

   // 找到h2的尾结点
   Lnode *tail2 = h2;
   while (tail2->next != h2)
   {
      tail2 = tail2->next;
   }

   // 连接：h1尾->h2头->h2数据节点们->h2尾->h1头
   tail1->next = h2; // h1的尾结点指向h2的头结点
   tail2->next = h1; // h2的尾结点指向h1的头结点
}

// 辅助函数：打印循环链表（用于测试）
void PrintCircularList(LinkList L)
{
   if (L == NULL || L->next == L)
   {
      cout << "空链表" << endl;
      return;
   }

   Lnode *p = L->next; // 从第一个数据节点开始
   cout << "循环链表: ";
   do
   {
      cout << p->data << " ";
      p = p->next;
   } while (p != L->next); // 回到起始的数据节点
   cout << endl;
}

// 辅助函数：创建循环链表（用于测试）
LinkList CreateCircularList(int arr[], int n)
{
   if (n <= 0)
      return NULL;

   LinkList L = new Lnode; // 创建头结点
   L->next = L;            // 初始为空的循环链表

   Lnode *tail = L;
   for (int i = 0; i < n; i++)
   {
      Lnode *newNode = new Lnode;
      newNode->data = arr[i];
      newNode->next = L;    // 新节点指向头结点
      tail->next = newNode; // 尾结点指向新节点
      tail = newNode;       // 更新尾结点
   }

   return L;
}