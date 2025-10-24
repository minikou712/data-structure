#include <iostream>
#include <algorithm>
using namespace std;

typedef int ElemType;
const int MAXSIZE=505;

// 固定数组
typedef struct
{
    ElemType data[MAXSIZE];
    int length;
} SqList;

void InitList(SqList &l)
{
    l.length = 0;
}

// sqlist由系统自动回收，其分配在栈内存

bool ListEmpty(SqList &l)
{
    if (l.length == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void DispList(SqList l)
{
    for (int i = 0; i < l.length; i++)
    {
        cout << l.data[i] << " ";
    }
    cout << endl;
}

ElemType GetElem(SqList l, int i)
{
    return l.data[i];
}

ElemType LocateElem(SqList l, ElemType e) // 按元素值查找
{
    for(int i=0;i<l.length;i++)
    {
        if(l.data[i]==e)
        {
            return i+1;
        }
    }
    return false;
}

bool ListInsert(SqList& l, int j, ElemType e)
{
    if(l.length>=MAXSIZE)
    {
        cout<<"超出范围"<<endl;
        return false;
    }
    
    if(j<1||j>l.length+1) //此处边界，j不能插入到表第0个位置，与表末尾之后的第二个位置   x（l） j x
    {
        cout<<"插入下标不合法"<<endl;
        return false;
    }
    for(int i=l.length;i>=j;i--)
    {
            l.data[i]=l.data[i-1];
        
    }
    l.data[j-1]=e;
    l.length++;
    return true;
}

bool DeleteElem(SqList& l, int j, ElemType &e)
{
    if(l.length==0)
    {
        cout<<"删除异常"<<endl;
        return false;
    }
    if(j<1||j>l.length) //此处边界，j不能插入到表第0个位置，与表末尾之后的第二个位置   x（l） j x
    {
        cout<<"删除下标不合法"<<endl;
        return false;
    }
    e=l.data[j-1];
    for(int i=j;i<l.length;i++)
    {
        l.data[i-1]=l.data[i];
    }
    l.length--;
    return true;
}

int main()
{
    SqList sq;
    InitList(sq);
    for(int i=1;i<10;i++)
    {
        ListInsert(sq,i,i);
    }
    DispList(sq);
    return 0;
}