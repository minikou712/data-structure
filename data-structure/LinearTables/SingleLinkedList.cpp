#include <iostream>
#include <cstdlib>
using namespace std;
typedef char ElemType;


typedef struct Lnode
{
    ElemType data;
    Lnode *next;    // c中必须struct Lnode *next也对
} Lnode, *LinkList; // 此处Lnode* 等价于LinkListed 只不过Lnode强调结点，LinkList强调链表

bool InitList(LinkList &L) // 初始化线性表 初始化此处就是带头结点的单链表  &即传入该变量的地址，这里是linklist指针的地址，可以对指针本身修改
{
    L = (Lnode *)malloc(sizeof(Lnode));
    L->next = NULL;
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
    while (p != NULL)   // p不为NULL,输出p结点的data域
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
    return NULL;
}
Lnode *LocateElem(LinkList L, ElemType e)
{
    Lnode *p = L->next; // p指向首结点
    while (p != NULL && p->data != e)
    {
        p = p->next; // p移向下一个结点
    }
    if (p != NULL && p->data == e)
        return p;
    return NULL;
}

bool ListInsert(LinkList &L, int i, ElemType e)
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
        cout << "插入异常" << endl;
        return false;
    }
    Lnode *s = (Lnode *)malloc(sizeof(Lnode));
    s->data = e;
    s->next = p->next;
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
    if (p == NULL || p->next == NULL)
    {
        cout << "删除异常" << endl;
        return false;
    }
    Lnode *q = p->next;
    e = q->data;
    p->next = q->next;
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
        L->next = s;
    }
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
        r = s;
    }
    r->next = NULL;
}

int main()
{
    LinkList L1;
    InitList(L1);

    cout << "=== 单链表功能测试 ===" << endl;

    // 使用头插法建立链表
    cout << "1. 使用头插法建立链表：" << endl;
    List_HeadInsert(L1);

    cout << "2. 当前链表内容：";
    DispList(L1);

    cout << "3. 链表长度：" << ListLength(L1) << endl;

    // 测试插入
    cout << "4. 在位置1插入字符'X'：" << endl;
    ListInsert(L1, 1, 'X');
    cout << "插入后链表内容：";
    DispList(L1);

    // 测试查找
    cout << "5. 查找第3个元素：";
    Lnode *node = GetElem(L1, 3);
    if (node != NULL)
        cout << "找到元素：" << node->data << endl;
    else
        cout << "未找到元素" << endl;

    // 测试删除
    cout << "6. 删除第2个元素：";
    ElemType e;
    if (ListDelete(L1, 2, e))
        cout << "删除的元素是：" << e << endl;
    cout << "删除后链表内容：";
    DispList(L1);

    cout << "7. 最终链表长度：" << ListLength(L1) << endl;

    // 销毁链表
    DestroyList(L1);

    return 0;
}