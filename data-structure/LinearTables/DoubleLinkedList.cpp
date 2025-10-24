#include <iostream>
using namespace std;
typedef int ElemType;

typedef struct Lnode
{
    ElemType data;
    Lnode *prior;
    Lnode *next;   //c中必须struct Lnode *next也对
}Lnode,*LinkList;       //此处Lnode* 等价于LinkListed 只不过Lnode强调结点，LinkList强调链表

bool InitList(LinkList& L) //初始化线性表 初始化此处就是带头结点的单链表  &即传入该变量的地址，这里是linklist指针的地址，可以对指针本身修改
{
    L=(Lnode*)malloc(sizeof(Lnode));
    L->next=NULL;
    L->prior=NULL;
    return true;
} 

void DestroyList(LinkList& L) //销毁线性表 要扫描全表把每个结点销毁
{
    Lnode *p=L,*q=NULL;   
    while(p!=NULL)
    {
        q=p->next;
        free(p);
        p=q;
    }
    L=NULL; //表头置空
    cout<<"销毁成功"<<endl;
}

bool ListEmpty(LinkList& L) //判断线性表是否为空表
{
	return(L->next == NULL);
}

int ListLength(LinkList L) //求线性表的长度
{
	int i = 0;
    Lnode *p=L->next;
    while(p!=NULL) //从首结点开始
    {
        i++;
        p=p->next;
    }
    return i;
}

void DispList(LinkList L) //输出线性表
{
	Lnode *p = L->next; //p指向首结点
	while (p != NULL) //p不为NULL,输出p结点的data域
	{
		cout<<p->data<<" ";
		p = p->next; //p移向下一个结点
	}
    cout<<endl;
}

Lnode* GetElem(LinkList L, int i) 
{
    Lnode *p = L; 
    int j=0;
	while (p != NULL&&j<i) 
	{
		p = p->next; //p移向下一个结点
        j++;
	}
    if(i==j)
    return p;
}
Lnode* LocateElem(LinkList L, ElemType e) 
{
    Lnode *p = L->next; //p指向首结点
	while (p != NULL&&p->data!=e) 
	{
		p = p->next; //p移向下一个结点
	}
    if(p->data==e)
    return p;
}

bool ListInsert(LinkList& L, int i, ElemType e)
{
    Lnode *p=L;
    int j=0;
    while(p!=NULL&&j<i-1)
    {
        p=p->next;
        j++;
    }
    if(p==NULL)
    {
        cout<<"插入异常"<<endl;
        return false;
    }
    Lnode *s=(Lnode*)malloc(sizeof(Lnode));
    s->data=e;
    s->next=p->next;
    if(p->next!=NULL)
    p->next->prior=s;
    p->next=s;
    s->prior=p;
    return true;
}

bool ListDelete(LinkList& L, int i, ElemType& e)
{
    Lnode *p=L;
    int j=0;
    while(p!=NULL&&j<i-1)
    {
        p=p->next;
        j++;
    }
    if(p==NULL)
    {
        cout<<"删除异常"<<endl;
        return false;
    }
    Lnode *q=p->next;
    e=q->data;
    p->next=q->next;
    if(q->next!=NULL)
    q->next->prior=p; // p->next->prior=p
    free(q);
    return true;
}

void List_HeadInsert(LinkList& L)    //头插法建立单链表，即找到头结点，在头结点后不断插入
{
    cout<<"请输入元素建立链表! 输入0终止输入"<<endl; 
    ElemType e;
    L->next=NULL; //初始化为带头结点的空表
    while(1)
    {
        ElemType e;
        cin>>e;
        if(e==0)
        {
            break;
        }
        Lnode *s=(Lnode*)malloc(sizeof(Lnode));
        s->data=e;
        s->next=L->next;
        if(L->next!=NULL)
        L->next->prior=s;
        L->next=s;
        s->prior=L;
    }
}

void List_TailInsert(LinkList& L)    //头插法建立单链表，即找到头结点，在头结点后不断插入
{
    cout<<"请输入元素建立链表! 输入0终止输入"<<endl; 
    ElemType e;
    L->next=NULL; //初始化为带头结点的空表
    Lnode *r=L;
    while(1)
    {
        ElemType e;
        cin>>e;
        if(e==0)
        {
            break;
        }
        Lnode *s=(Lnode*)malloc(sizeof(Lnode));
        s->data=e;
        r->next=s;
        s->prior=r;
        r=s;
    }
    r->next=NULL;
}


int main()
{
    LinkList L1;
    InitList(L1);
    List_HeadInsert(L1);
    ListInsert(L1,1,3);
    ElemType e;
    ListDelete(L1,6,e);
    DestroyList(L1);
    DispList(L1);
}