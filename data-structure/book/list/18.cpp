#include <iostream>
#include "list.h" //包含链表头文件
using namespace std;

/* 题目18：【2012统考真题】假定采用带头结点的单链表保存单词，当两个单词有相同的后缀时，
   可共享相同的后缀存储空间，例如，loading和being的存储映像如下图所示。

   设str1和str2分别指向两个单词所在链表的头结点，链表结点结构为|data|next|，
   请设计一个时间上尽可能高效的算法，找出由str1和str2所指向的两个链表共同后缀
   的起始位置（如图中字符d所在结点的位置P）。要求：
   1）给出算法的基本设计思想。
   2）根据设计思想，采用C或C++或Java语言描述算法，关键之处给出注释。
   3）说明你所设计算法的时间复杂度。 */

// 带头结点的单链表结点定义
struct LNode
{
   char data;
   LNode *next;
};
typedef LNode *LinkList;

/*
算法基本设计思想（你的思路）：
1. 分别遍历两个链表，计算长度len1和len2
2. 让较长的链表先走|len1-len2|步，使两个指针到达相同的相对位置
3. 两个指针同时向前移动，第一次相遇的结点就是共同后缀的起始位置
4. 关键：相同后缀意味着从某个位置开始，两个链表共享相同的物理结点
*/

// 方法一：长度差法（你的实现思路）
LNode *FindCommonSuffix1(LinkList str1, LinkList str2)
{
   if (str1 == NULL || str2 == NULL)
   {
      return NULL;
   }

   // 第一步：计算两个链表的长度
   int len1 = 0, len2 = 0;
   LNode *p1 = str1->next; // 跳过头结点
   LNode *p2 = str2->next; // 跳过头结点

   while (p1 != NULL)
   {
      len1++;
      p1 = p1->next;
   }

   while (p2 != NULL)
   {
      len2++;
      p2 = p2->next;
   }

   // 第二步：重新设置指针到第一个数据结点
   p1 = str1->next;
   p2 = str2->next;

   // 第三步：让较长的链表先走，消除长度差
   if (len1 > len2)
   {
      // str1较长，让p1先走len1-len2步
      for (int i = 0; i < len1 - len2; i++)
      {
         p1 = p1->next;
      }
   }
   else
   {
      // str2较长，让p2先走len2-len1步
      for (int i = 0; i < len2 - len1; i++)
      {
         p2 = p2->next;
      }
   }

   // 第四步：两个指针同时移动，寻找第一个相同的结点
   while (p1 != NULL && p2 != NULL)
   {
      if (p1 == p2)
      {             // 注意：比较的是结点地址，不是数据
         return p1; // 找到共同后缀的起始位置
      }
      p1 = p1->next;
      p2 = p2->next;
   }

   return NULL; // 没有共同后缀
}

// 方法二：双指针交替法（更优雅的实现）
LNode *FindCommonSuffix2(LinkList str1, LinkList str2)
{
   /*
   算法思想：
   两个指针分别从两个链表开始遍历，当到达末尾时跳转到另一个链表的开头
   这样两个指针走过的总路径长度相同，会在交点相遇
   */
   if (str1 == NULL || str2 == NULL)
   {
      return NULL;
   }

   LNode *p1 = str1->next; // 跳过头结点
   LNode *p2 = str2->next; // 跳过头结点

   while (p1 != p2)
   {
      // 如果p1到达末尾，跳转到str2的开头；否则继续前进
      p1 = (p1 == NULL) ? str2->next : p1->next;
      // 如果p2到达末尾，跳转到str1的开头；否则继续前进
      p2 = (p2 == NULL) ? str1->next : p2->next;
   }

   return p1; // p1和p2相遇的位置（可能是NULL，表示没有交点）
}