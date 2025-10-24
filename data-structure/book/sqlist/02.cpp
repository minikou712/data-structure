#include "sqlist.h"

// 设计一个算法，将顺序表L中元素逆置要求时间复杂度为O(n)，空间复杂度为O(1)
int swap(int &a, int &b)
{
    int t = a;
    a = b;
    b = t;
}
void reverse(sqList &L)
{
    int p = 0, q = L.length - 1;
    while (p != q)
    {
        swap(L.data[p], L.data[q]);
        p++;
        q--;
    }
}