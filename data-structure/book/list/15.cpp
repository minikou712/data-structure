#include <iostream>
#include "list.h" //包含链表头文件
using namespace std;

/* 题目15：单链表有环，是指单链表的最后一个结点的指针指向了链表中的某个结点（通常单链表
   的最后一个结点的指针域是空的）。试编写算法判断单链表是否存在环。
   1）给出算法的基本设计思想。
   2）根据设计思想，采用C或C++语言描述算法，关键之处给出注释。
   3）说明你所设计算法的时间复杂度和空间复杂度。 */

// 算法基本设计思想：
// 方法一：快慢指针法（Floyd判环算法）
// - 使用两个指针：slow（慢指针）每次走一步，fast（快指针）每次走两步
// - 如果链表有环，快指针最终会追上慢指针
// - 如果链表无环，快指针会先到达NULL
bool HasCycle1(LinkList L)
{
   if (L == NULL || L->next == NULL)
   {
      return false; // 空链表或只有一个结点，无环
   }

   Lnode *slow = L; // 慢指针，每次走一步
   Lnode *fast = L; // 快指针，每次走两步

   while (fast != NULL && fast->next != NULL)
   {
      slow = slow->next;       // 慢指针走一步
      fast = fast->next->next; // 快指针走两步

      if (slow == fast)
      { // 快慢指针相遇，说明有环
         return true;
      }
   }

   return false; // 快指针到达NULL，说明无环
}