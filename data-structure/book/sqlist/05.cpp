#include "sqlist.h"
#include <unordered_set>

// 有序表去重
// 可以使用双指针法来实现有序表的去重
// 思想: 使用两个指针i和j，i遍历整个数组，j指向下一个保留元素的位置
// 当i指向的元素与j指向的元素不同时，将i指向的元素复制到j的位置，并递增j
// 最后更新顺序表的长度为j
bool Delete_Same(sqList &L)
{
    if (L.length == 0) // 处理空表
    {
        return true;
    }

    int j = 0; // 指向下一个保留元素的位置
    for (int i = 1; i < L.length; i++)
    {
        if (L.data[i] != L.data[j]) // 与前一个元素比较
        {
            j++;
            L.data[j] = L.data[i];
        }
    }
    L.length = j + 1; // 更新顺序表的长度
    return true;
}

//若是非有序表去重
// 可以使用哈希表来实现去重
// 思想: 使用一个哈希表来记录已经出现的元素   可以用数组模拟哈希
bool Delete_Same_Unordered(sqList &L)
{
    if (L.length == 0) // 处理空表
    {
        return true;
    }

    bool seen[100] = {false}; // 哈希表记录已出现的元素
    int j = 0; // 指向下一个保留元素的位置

    for (int i = 0; i < L.length; i++)
    {
        if (!seen[L.data[i]]) // 如果元素未出现过
        {
            seen[L.data[i]] = true; // 添加到哈希表
            L.data[j] = L.data[i]; // 保留该元素
            j++;
        }
    }
    L.length = j; // 更新顺序表的长度
    return true;
}

