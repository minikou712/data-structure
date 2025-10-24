#include <iostream>
#include "list.h" //包含链表头文件
using namespace std;

/* 题目14：设有n(n>1)个整数存放到不带头结点的单链表L中，设计算法将L中存储的序列循环
   右移k(0<k<n)个位置。例如，若k=1，则将链表{0,1,2,3}变为{3,0,1,2}。要求：
   1）给出算法的基本设计思想。
   2）根据设计思想，采用C或C++语言描述算法，关键之处给出注释。
   3）说明你所设计算法的时间复杂度和空间复杂度。 */

// 实现思路，遍历链表找到第L.length-k个元素，
// 从这里开始用尾插法插入链表头部，实际直接将此处断开插入头部
Lnode *Converse(Lnode *L, int k)
{
   int n = 1;    // n用来保存链表的长度
   Lnode *p = L; // p为工作指针

   while (p->next != NULL)
   { // 计算链表的长度
      p = p->next;
      n++;
   }
   // 循环执行完后，p指向链表尾结点

   p->next = L; // 将链表连成一个环

   for (int i = 1; i <= n - k; i++) // 寻找链表的第n-k个结点
      p = p->next;

   L = p->next;    // 令L指向新链表尾结点的下一个结点
   p->next = NULL; // 将环断开

   return L;
}
