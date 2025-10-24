#include <iostream>
using namespace std;

// 1. 冒泡排序
// 实现思想：通过相邻元素的比较和交换，让较大元素逐渐"冒泡"到末尾
// 步骤：
// 1. 外层循环控制轮数，需要n-1轮
// 2. 内层循环进行相邻元素比较，范围逐渐缩小
// 3. 如果前一个元素大于后一个元素，则交换
// 4. 优化：如果某轮没有交换，说明已有序，提前退出
void bubbleSort(int arr[], int n)
{
    // 外层循环：控制排序轮数，最多需要n-1轮
    for (int i = 0; i < n - 1; i++)
    {
        bool swapped = false; // 优化标志：记录本轮是否发生交换

        for (int j = 0; j < n - 1 - i; j++)
        {
            // 如果前一个元素大于后一个元素，则交换
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]); // 交换相邻元素
                swapped = true;           // 标记发生了交换
            }
        }

        // 优化：如果本轮没有发生交换，说明数组已经有序，可以提前退出
        if (!swapped)
            break;
    }
}
// 冒泡排序复杂度分析：
//
// 时间复杂度：
// - 最坏情况：O(n²) - 数组完全逆序时，需要进行 n-1 轮，每轮比较 n-1-i 次
//   总比较次数：(n-1) + (n-2) + ... + 1 = n(n-1)/2 ≈ O(n²)
//
// - 最好情况：O(n) - 数组已经有序时，第一轮遍历发现没有交换发生，
//   通过 swapped 标志直接退出，只需要 n-1 次比较
//
// - 平均情况：O(n²)
//
// 空间复杂度：O(1)
//
// 稳定性：稳定 - 相等元素的相对位置不会改变，因为只有 arr[j] > arr[j+1]
//              时才交换，相等时不交换

// 2. 快速排序
// 实现思想：分治法，选择基准元素，每次排序确定基准元素位置
// 步骤：
// 1. 选择基准元素（这里选择最后一个元素）
// 2. 分割：将小于等于基准的元素放在左边，大于基准的放在右边
// 3. 递归：对左右两部分分别进行快速排序

// 快速排序

const int N = 1e6 + 5;
int q[N];
void quick_sort(int l, int r)
{
    if (l >= r)
        return;
    int i = l - 1, j = r + 1;
    int mid = q[(l + r) / 2]; // 这里必须把判定点的值给存起来，而不是存下标，存下标可能在排序中，判定点值会发生改变
    while (i < j)
    {
        do
        {
            i++;
        } while (q[i] < mid);
        do
        {
            j--;
        } while (q[j] > mid);
        if (i < j)
        {
            swap(q[i], q[j]);
        }
    }

    quick_sort(l, j);
    quick_sort(j + 1, r); // 因为这里使用dowhile 循环，所以在最后一次循环时，q[i]>=mid  q[j]<=mid   i>=j     则推出 q[i~r]>=mid  q[l~j]<=mid   即也可得q[i-1]<=mid   q[j+1]>=mid
}

// 若选取第一个元素划分
void quick_sort_first(int low, int high)
{
    if (low >= high)
        return;

    int left = low, right = high;
    int pivot = q[low]; // 选择第一个元素作为基准

    while (left < right)
    {
        // 从右向左找第一个小于基准的元素
        while (left < right && q[right] >= pivot)
            right--;
        q[left] = q[right]; // 将小于基准的元素放到左边

        // 从左向右找第一个大于基准的元素
        while (left < right && q[left] <= pivot)
            left++;
        q[right] = q[left]; // 将大于基准的元素放到右边
    }

    q[left] = pivot; // 将基准元素放到正确位置

    // 递归排序左右子数组
    quick_sort_first(low, left - 1);
    quick_sort_first(left + 1, high);
}

// 快速排序复杂度分析：
//
// 时间复杂度：
// - 平均情况：O(nlogn) - 每次分割都能将数组大致平分，递归深度为logn，
//   每层需要O(n)时间进行分割，总时间为O(nlogn)
//
// - 最坏情况：O(n²) - 每次选择的基准都是最大或最小元素，导致极不平衡的分割
//   例如：已排序数组选择最后一个元素作为基准，递归深度为n，总时间为O(n²)
//
// - 最好情况：O(nlogn) - 每次基准都能完美平分数组，递归深度为logn
//
// 空间复杂度：
// - 平均情况：O(logn) - 递归调用栈的深度，平均为logn层
// - 最坏情况：O(n) - 退化为链式递归时，递归深度为n
//
// 稳定性：不稳定 - 分割过程中，相等元素的相对位置可能发生改变
//         例如：[3a, 2, 3b, 1] 以3b为基准，结果可能变为[2, 1, 3b, 3a]