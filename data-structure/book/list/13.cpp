#include <iostream>
#include "list.h" //包含链表头文件
using namespace std;

/* 题目13：设有一个带头结点的非循环双链表L，其每个结点中除有pre、data和next域外，
   还有一个访问频度域freq，其值均初始化为零。每当在链表中进行一次Locate(L,x)
   运算时，令值为x的结点中freq域的值增1，并使此链表中的结点保持按访问频度递
   减的顺序排列，且最近访问的结点排在频度相同的结点之前，以使被频繁访问的结点总
   是靠近表头。试编写符合上述要求的Locate(L,x)函数，返回找到结点的地址，类型。 */

// 双链表结点结构定义
struct DLnode
{
   int data;
   int freq;     // 访问频度域
   DLnode *pre;  // 前驱指针
   DLnode *next; // 后继指针
};
typedef DLnode *DLinkList;

DLinkList Locate(DLinkList &L, int x)
{
   DLnode *p = L->next, *q; // p为工作指针，q为p的前驱，用于查找插入位置

   while (p && p->data != x) // 查找值为x的结点
      p = p->next;

   if (!p)
   {           // 不存在值为x的结点
      exit(0); // 或者return NULL;
   }
   else
   {
      p->freq++; // 令元素值为x的结点的freq域加1

      // 如果p是表首结点，或者freq值小于前驱   前驱结点的频度大于等于当前结点
      // 原本该结点是符合顺序的，现在访问频度增加只可能向前
      // 则不需要调整位置，直接返回
      if (p->pre == L || p->pre->freq >= p->freq)
         return p; // p是链表表首，或freq值小于前驱

      // 否则将p结点从链表中删除
      if (p->next != NULL)
         p->next->pre = p->pre;
      p->pre->next = p->next; // 将p结点从链表上摘下

      q = p->pre; // 以下查找p结点的插入位置
      while (q != L && q->freq < p->freq)
         q = q->pre;

      // 将p结点插入到q结点之后
      p->next = q->next;
      if (q->next != NULL)
         q->next->pre = p; // 将p结点排在同频率的第一个
      p->pre = q;
      q->next = p;
   }
   return p; // 返回值为x的结点的指针
}