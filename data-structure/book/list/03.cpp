#include <iostream>
#include "list.h" //包含链表头文件
using namespace std;

// 将带头节点的单链表就地逆置，就地->辅助空间复杂度O(1)

//法一 
//使用头插法建立单链表的思想实现链表逆置

//步骤
//1. 先将头结点的next指针置为NULL，表示逆置后的链表为空
//2. 遍历原链表，将每个结点插入到头结点后面
//3. 最终得到的链表就是逆置后的链表

void ReverseList(LinkList &L) // 逆置单链表
{
    Lnode *p=L->next; // p指向首结点
    L->next=NULL; // 将头结点的next指针置为NULL，表示逆置后的链表为空
    
    while (p!=NULL)
    {
        Lnode *r=p->next; // r指向下一个结点
        p->next=L->next;  // 将p结点的next指针指向头结点原来指向的结点
        L->next=p;  // 将p结点插入到头结点后面（头插法）
        p=r; // p指向下一个结点
    }
}

//法二
//使用三个指针法实现链表逆置
//步骤
//1. 定义三个指针：prev、curr、next，分别指向前一个结点、当前结点和下一个结点
//2. 初始化prev为NULL，curr为头结点的下一个结点，next为NULL
//3. 遍历链表，将每个结点的next指针指向前一个结点
//4. 更新prev、curr和next指针，直到遍历完整个链表   

void ReverseList2(LinkList &L) // 逆置单链表
{
    Lnode *prev = NULL; // 前一个结点
    Lnode *curr = L->next; // 当前结点
    Lnode *next = NULL; // 下一个结点

    while (curr != NULL) {
        next = curr->next; // 保存下一个结点
        curr->next = prev; // 将当前结点的next指针指向前一个结点
        prev = curr; // 更新前一个结点为当前结点
        curr = next; // 更新当前结点为下一个结点
    }
    
    L->next = prev; // 将头结点的next指针指向逆置后的链表
}