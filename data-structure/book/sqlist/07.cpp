#include "sqlist.h"

typedef int DataType;

// 已知在一维数组A[m+n]中存放两个线性表分别有m, n个元素，
// 线性表A[0..m-1]和A[m..m+n-1]，
// 交换这两个线性表的元素位置，要求空间复杂度为O(1)。

// 辅助函数：逆置数组中指定范围的元素
void Reverse(DataType A[], int start, int end)
{
    while (start < end)
    {
        DataType temp = A[start];
        A[start] = A[end];
        A[end] = temp;
        start++;
        end--;
    }
}

void Exchange(DataType A[], int m, int n, int arraySize)
{
    // 方法：三次逆置
    // 1. 逆置整个数组 A[0..m+n-1]
    Reverse(A, 0, m + n - 1);
    
    // 2. 逆置前n个元素 A[0..n-1] 
    Reverse(A, 0, n - 1);
    
    // 3. 逆置后m个元素 A[n..m+n-1]
    Reverse(A, n, m + n - 1);
}


//法二 允许空间复杂度为O(n)
void Exchange2(DataType A[], int m, int n, int arraySize)
{
    // 方法：使用辅助数组
    DataType *temp = new DataType[m + n];
    
    // 将前m个元素复制到temp中
    for (int i = 0; i < m; i++)
    {
        temp[i] = A[i];
    }
    
    // 将后n个元素复制到A的前m个位置
    for (int i = 0; i < n; i++)
    {
        A[i] = A[m + i];
    }
    
    // 将temp中的元素复制到A的后n个位置
    for (int i = 0; i < m; i++)
    {
        A[n + i] = temp[i];
    }
    
    delete[] temp; // 释放临时数组
}