#include <iostream>
using namespace std;
typedef int ElemType;

// 循环双链表的插入删除皆和双链表一样，但在创建初始化链表时记得保证首尾相连，同时遍历结束条件为 末结点后继为头结点
typedef struct Lnode
{
    ElemType data;
    Lnode *prior;
    Lnode *next;    // c中必须struct Lnode *next也对
} Lnode, *LinkList; // 此处Lnode* 等价于LinkListed 只不过Lnode强调结点，LinkList强调链表

bool InitList(LinkList &L) // 初始化线性表 初始化此处就是带头结点的单链表  &即传入该变量的地址，这里是linklist指针的地址，可以对指针本身修改
{
    L = (Lnode *)malloc(sizeof(Lnode));
    L->prior = L;
    L->next = L;
    return true;
}

void DestroyList(LinkList &L) // 销毁线性表 要扫描全表把每个结点销毁
{
    Lnode *p = L, *q = NULL;
    while (p != NULL)
    {
        q = p->next;
        free(p);
        p = q;
    }
    L = NULL; // 表头置空
    cout << "销毁成功" << endl;
}

bool ListEmpty(LinkList &L) // 判断线性表是否为空表
{
    return (L->next == NULL);
}

int ListLength(LinkList L) // 求线性表的长度
{
    int i = 0;
    Lnode *p = L->next;
    while (p != NULL) // 从首结点开始
    {
        i++;
        p = p->next;
    }
    return i;
}

void DispList(LinkList L) // 输出线性表
{
    Lnode *p = L->next; // p指向首结点
    while (p != L)      // p不为NULL,输出p结点的data域
    {
        cout << p->data << " ";
        p = p->next; // p移向下一个结点
    }
    cout << endl;
}

Lnode *GetElem(LinkList L, int i)
{
    Lnode *p = L;
    int j = 0;
    while (p != NULL && j < i)
    {
        p = p->next; // p移向下一个结点
        j++;
    }
    if (i == j)
        return p;
}
Lnode *LocateElem(LinkList L, ElemType e)
{
    Lnode *p = L->next; // p指向首结点
    while (p != NULL && p->data != e)
    {
        p = p->next; // p移向下一个结点
    }
    if (p->data == e)
        return p;
}

bool ListInsert(LinkList &L, int i, ElemType e)
{
    if (i < 0)
        return false; // 插入位置无效
    Lnode *p = L, *s;
    int j = 0;
    while (p->next != L && j < i)
    { // 寻找第i个节点的前一个节点
        p = p->next;
        ++j;
    }
    s = (Lnode *)malloc(sizeof(Lnode));
    if (s == NULL)
        return false;
    s->data = e;
    s->next = p->next;
    s->prior = p;
    p->next->prior = s;
    p->next = s;
    return true;
}

bool ListDelete(LinkList &L, int i, ElemType &e)
{
    Lnode *p = L;
    int j = 0;
    while (p != NULL && j < i - 1)
    {
        p = p->next;
        j++;
    }
    if (p == NULL)
    {
        cout << "删除异常" << endl;
        return false;
    }
    Lnode *q = p->next;
    e = q->data;
    p->next = q->next;
    if (q->next != NULL)
        q->next->prior = p; // p->next->prior=p
    free(q);
    return true;
}

void List_HeadInsert(LinkList &L) // 头插法建立单链表，即找到头结点，在头结点后不断插入
{
    cout << "请输入元素建立链表! 输入0终止输入" << endl;
    ElemType e;
    L->next = NULL; // 初始化为带头结点的空表
    while (1)
    {
        ElemType e;
        cin >> e;
        if (e == 0)
        {
            break;
        }
        Lnode *s = (Lnode *)malloc(sizeof(Lnode));
        s->data = e;
        s->next = L->next;
        if (L->next != NULL)
            L->next->prior = s;
        L->next = s;
        s->prior = L;
    }
    // 头插法遍历首尾相连
    Lnode *p = L;
    while (p->next != NULL)
    {
        p = p->next;
    }
    p->next = L;
    L->prior = p;
}

void List_TailInsert(LinkList &L) // 头插法建立单链表，即找到头结点，在头结点后不断插入
{
    cout << "请输入元素建立链表! 输入0终止输入" << endl;
    ElemType e;
    L->next = NULL; // 初始化为带头结点的空表
    Lnode *r = L;
    while (1)
    {
        ElemType e;
        cin >> e;
        if (e == 0)
        {
            break;
        }
        Lnode *s = (Lnode *)malloc(sizeof(Lnode));
        s->data = e;
        r->next = s;
        s->prior = r;
        r = s;
    }
    // 尾插借助r直接连
    r->next = L;
    L->prior = r;
}

int main()
{
    LinkList L1;
    InitList(L1);
    L1->data = 3;
    cout << L1->prior->data << endl;
    for (int i = 0; i < 5; i++)
    {
        ListInsert(L1, i, i);
    }
    // List_HeadInsert(L1);
    cout << L1->prior->data << endl;
    DispList(L1);
}