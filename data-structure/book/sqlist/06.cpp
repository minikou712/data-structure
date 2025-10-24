#include "sqlist.h"


// 合并两个有序表La和Lb为一个新的有序表Lc
// 思想: 使用两个指针i和j分别遍历La和Lb，比较当前元素，将较小的元素放入Lc中
// 最后将剩余的元素直接复制到Lc中
// 即类似于归并排序的合并过程
bool Merge(sqList &La, sqList &Lb, sqList &Lc)
{   
    int i = 0, j = 0, k = 0; // i和j分别指向La和Lb的当前元素，k指向Lc的下一个位置
    while (i < La.length && j < Lb.length)
    {
        if (La.data[i] < Lb.data[j])
        {
            Lc.data[k++] = La.data[i++];
        }
        else
        {
            Lc.data[k++] = Lb.data[j++];
        }
    }
    // 将剩余元素复制到Lc中
    while (i < La.length)
    {
        Lc.data[k++] = La.data[i++];
    }
    while (j < Lb.length)
    {
        Lc.data[k++] = Lb.data[j++];
    }
    Lc.length = k; // 更新Lc的长度
    return true;
}