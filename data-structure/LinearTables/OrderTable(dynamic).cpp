#include <iostream>
using namespace std;
const int MAXSIZE=505;
typedef int ElemType;

// 动态分配，但每次重新分配需要将原数组的元素重新复制到新数组

typedef struct
{
    ElemType *data;
    int length;
} SqList;

void InitList(SqList &l, int size)
{
    l.data = (ElemType *)malloc(sizeof(ElemType) * size);
    l.length = 0;
}

// sqlist1由系统自动回收，其分配在栈内存
void DestroyList(SqList &l)
{
    free(l.data);
}

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
    return l.data[i-1];
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
    return false;
    if(j<1||j>l.length+1) //此处边界，j不能插入到表第0个位置，与表末尾之后的第二个位置   x j（l） j x
    return false;
    for(int i=l.length;i>=j;i--)
    {
        l.data[i]=l.data[i-1];
    }
    l.data[j-1]=e;
    l.length++;
    return true;
}

bool ListDelete(SqList& l, int j, ElemType &e)
{
    if(j<1||j>l.length)    //删除不可删掉  x（l）x
    {
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
    InitList(sq,10);
    for(int i=1;i<10;i++)
    {
        ListInsert(sq,i,i);
    }
    ElemType e;
    ListDelete(sq,1,e);
    cout<<GetElem(sq,1)<<" "<<LocateElem(sq,2)<<endl;
    DispList(sq);
    return 0;
}