#include "sqlist.h"

// 题目10：【2010统考真题】

// 设将n(n>1)个整数存放到一维数组R中。设计一个在时间和空间两方面都尽可能高效的算法，
// 将R中保存的序列循环左移p(0<p<n)个位置，即将R中的数据由(X₀, X₁, ···, Xₙ₋₁)
// 变换为(Xₚ, Xₚ₊₁, ···, Xₙ₋₁, X₀, X₁, ···, Xₚ₋₁)。

// 要求：
// 给出算法的基本设计思想。
// 根据设计思想，采用C或C++或Java语言描述算法，关键之处给出注释。
// 说明你所设计算法的时间复杂度和空间复杂度。


//法一 构建辅助数组
// 时间复杂度O(n)，空间复杂度O(n)
void Converse(int R[], int n,int p)
{
    int *temp = new int[n]; // 构建辅助数组
    for(int i=0;i<p;i++)
    {   
        temp[i] = R[i]; // 将前p个元素存入辅助数组
    }
    for(int i=0;i<n-p;i++)  
    {
        R[i] = R[i + p]; // 将后n-p个元素左移p个位置
    }
    for(int i=n-p;i<n;i++)
    {
        R[i] = temp[i - (n - p)]; // 将辅助数组中的元素放回到R的后面
    }   
}

//法二 交换
void Reverse(int R[], int start, int end)
{
    while (start < end)
    {
        swap(R[start], R[end]); // 交换首尾元素
        start++;
        end--;
    }
}
void Rotate(int R[], int n, int p)
{
    Reverse(R, 0, n - 1); // 先将整个数组逆序
    Reverse(R, 0, p - 1); // 再将前p个元素逆序
    Reverse(R, p, n - 1); // 最后将后n-p个元素逆序
}