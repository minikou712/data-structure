#include "sqlist.h"

// 对长度为n的顺序表L,编写一个时间复杂度为O(n)的算法，空间复杂度为O(1)，该算法删除顺序表中所有值为x的元素
//思想: 遍历顺序表，将等于x的元素删除，最后更新顺序表长度
void del_x_1(sqList &L, ElemType x)
{
    int k = 0; // 当前元素为x的个数
    for (int i = 0; i < L.length; i++)
    {
        if (L.data[i] == x)
        {
            k++;
        }
        else
        {
            L.data[i - k] = L.data[i];
        }
    }
    L.length -= k;  // 修正：更新顺序表长度
}
//解法二(推荐)  
// 思想: 这是经典的"快慢双指针"思想：
// i（快指针）: 遍历整个数组
// k（慢指针）: 指向下一个保留元素的存放位置
// 只有当元素不等于x时，才将其复制到位置k，并递增k

void del_x_2(sqList &L, ElemType x)
{
    int k = 0; //保留元素的下标
    for (int i = 0; i < L.length; i++)
    {
        if (L.data[i] != x)
        {
            L.data[k] = L.data[i];
            k++;
        }
    }
    L.length = k;  
}