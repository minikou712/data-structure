#include "sqlist.h"

// 从顺序表中删除元素最小的元素，并返回元素删除的值，空出位置由最后一位填补

bool deleteMin(sqList &L, ElemType &e)
{
    if (L.length == 0)
    {
        return false;
    }

    ElemType minValue = L.data[0];     // 修复：改变量名避免冲突
    int minIndex = 0;                  // 修复：初始化为0而不是-1
    for (int i = 1; i < L.length; i++) // 修复：从1开始，因为0已经作为初始最小值
    {
        if (L.data[i] < minValue)
        {
            minIndex = i;
            minValue = L.data[i];
        }
    }
    e = minValue;                            // 修复：将删除的最小值返回给调用者
    L.data[minIndex] = L.data[L.length - 1]; // 用最后一个元素填补空位
    L.length--;                              // 修复：减少长度
    return true;
}
