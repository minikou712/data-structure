#include <iostream>
#include <algorithm>
using namespace std;
#include <vector>

const int N = 1e6 + 5;
int q[N], temp[N];

// 归并排序
// 1.分治，找到分治点，数组即（l+r)/2 ,链表快慢指针确定
// 2.递归 以分治点分割
// 3.合并 保证每一段是有序的
void merge_sort(int l, int r)
{
    if (l >= r)
        return;

    int mid = l + (r - l) / 2; // 防止整数溢出    mid=(l+r)/2  一样正确
    merge_sort(l, mid);
    merge_sort(mid + 1, r);

    int i = l, j = mid + 1, k = 0;

    // 归并两个有序数组
    while (i <= mid && j <= r)
    {
        if (q[i] <= q[j]) // 使用 <= 保证稳定性
            temp[k++] = q[i++];
        else
            temp[k++] = q[j++];
    }

    // 处理剩余元素
    while (i <= mid)
        temp[k++] = q[i++];
    while (j <= r)
        temp[k++] = q[j++];

    // 将排序好的片段复制回原数组
    for (int i = l, j = 0; i <= r; i++, j++)
        q[i] = temp[j];
}

// 归并排序复杂度分析：
//
// 时间复杂度：
// - 最好情况：O(n log n) - 即使数组已经完全有序，仍需要执行完整的分治过程
//   因为归并排序的分治是基于位置而非元素大小，无法提前终止
//   递归深度始终为 log n，每层都需要 O(n) 时间进行合并操作
//
// - 最坏情况：O(n log n) - 数组完全逆序时，每次合并都需要处理所有元素
//   但由于分治结构固定，时间复杂度仍然保持 O(n log n)
//   这是归并排序的优势：性能稳定，不受数据初始状态影响
//
// - 平均情况：O(n log n) - 无论输入数据如何分布，时间复杂度都是 O(n log n)
//
// 详细分析：
// - 分治深度：log₂ n 层（每次将问题规模减半）
// - 每层合并：需要遍历当前层的所有 n 个元素
// - 总操作数：n × log₂ n ≈ O(n log n)
//
// 空间复杂度：
// - 辅助空间：O(n) - 需要与原数组同等大小的临时数组 temp[]
// - 递归栈空间：O(log n) - 递归调用栈的最大深度为 log n
// - 总空间复杂度：O(n) - 主要由临时数组决定
//
// 稳定性：稳定
// - 在合并过程中，当 q[i] == q[j] 时，我们总是先取左半部分的元素 q[i]
// - 这保证了相等元素的相对位置不会改变
// - 例如：[3a, 1, 3b] → [1, 3a, 3b]，3a 仍然在 3b 前面