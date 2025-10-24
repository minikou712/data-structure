#include "sqlist.h"

// 线性表中元素递增有序，设计一个算法完成用最少时间在表中查找值为x的元素
// 如果找到则将其与后继元素交换位置
// 如果没有找到则将x插入到表中，仍然保持递增有序

// 时间最少使用折半查找

int find(ElemType A[], ElemType x, int n)
{
    int left = 0, right = n - 1;
    while (left <= right)
    {
        int mid = (left + right) / 2;
        if (A[mid] == x)
        {
            return mid; // 找到x，返回其位置
        }
        else if (A[mid] < x)
        {
            left = mid + 1; // x在右半部分
        }
        else
        {
            right = mid - 1; // x在左半部分
        }
    }
    return -1; // 没有找到x
}
void SearchExchangeInsert(ElemType A[], ElemType x, int n)
{
    int pos = find(A, x, n);
    if (pos != -1)
    {
        // 找到x，将其与后继元素交换位置
        if (pos < n - 1) // 确保后继元素存在
        {
            swap(A[pos], A[pos + 1]);
        }
    }
    else
    {

        // 没有找到x，插入x到合适的位置
        //这里因为要插入x，所以直接从后面遍历开始后移，为x留下位置
        int i = n - 1;
        while (i >= 0 && A[i] > x)
        {
            A[i + 1] = A[i]; // 将大于x的元素向后移动
            i--;
        }
        //A[i]<x 在i+1的位置插入x
        A[i + 1] = x; // 插入x
    }
}