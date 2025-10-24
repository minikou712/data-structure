#include "sqlist.h"

// 从顺序表中删除其值在给定值s和t之间的所有元素
bool Del_s_t(sqList &L, ElemType s, ElemType t)
{
    if (s >= t) // 修正：s应该小于t
    {
        return false;
    }
    int k = 0; // 保留元素个数
    for (int i = 0; i < L.length; i++)
    {
        if (L.data[i] < s || L.data[i] > t) // 保留小于s或大于t的元素
        {
            L.data[k] = L.data[i];
            k++;
        }
    }
    L.length = k;
    return true; // 添加返回值
}