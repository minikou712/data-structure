#include <iostream>
using namespace std;

// 选择排序
void selectSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[minIndex])
            {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}

// 选择排序复杂度分析：
//
// 时间复杂度：
// - 最好情况：O(n²) - 即使数组已经有序，仍需要进行所有比较操作
//   比较次数：(n-1) + (n-2) + ... + 1 = n(n-1)/2 次
//   交换次数：n-1 次（每轮都会执行swap，即使是与自己交换）
//
// - 最坏情况：O(n²) - 数组完全逆序时
//   比较次数：n(n-1)/2 次（与最好情况相同）
//   交换次数：n-1 次（每轮都需要真正的交换操作）   移动元素次数3(n-1)
//
// - 平均情况：O(n²) - 选择排序的时间复杂度不受输入数据影响
//   无论什么情况，都需要进行相同次数的比较和交换
//
// 空间复杂度：O(1) - 只使用了常数个额外变量（minIndex）
//
// 稳定性：不稳定 - 相等元素的相对位置可能发生改变
// 例如：[5a, 3, 5b, 1] 第一轮会将 1 与 5a 交换，
//       变成 [1, 3, 5b, 5a]，5a 和 5b 的相对位置改变了
//
// 特点：
// - 交换次数最少：最多进行 n-1 次交换，适合交换代价很高的场景
// - 运行时间与输入无关：无论数组初始状态如何，运行时间都相同
// - 不适合大数据量：O(n²) 的时间复杂度在大数据量时效率很低



// 堆排序
// 实现思想：利用堆这种数据结构来进行排序
// 堆是一个近似完全二叉树的结构，并同时满足堆积的性质：
// - 大顶堆：每个节点的值都大于或等于其子节点的值
// - 小顶堆：每个节点的值都小于或等于其子节点的值

// 步骤：
// 1. 构建最大堆（大顶堆）
// 2. 将堆顶元素（最大值）与末尾元素交换
// 3. 调整剩余元素重新构成最大堆
// 4. 重复步骤2-3，直到堆的大小为1

// 调整堆的函数（向下调整）
// 功能：将以 root 为根的子树调整为最大堆
// 参数：arr[] - 数组，n - 堆的大小，root - 根节点索引
void heapify(int arr[], int n, int root)
{
    int largest = root;       // 假设根节点是最大的
    int left = 2 * root + 1;  // 左子节点的索引  下标从 0 开始
    int right = 2 * root + 2; // 右子节点的索引

    // 如果左子节点存在且大于根节点
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // 如果右子节点存在且大于当前最大值
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // 如果最大值不是根节点，则交换并继续向下调整
    if (largest != root)
    {
        swap(arr[root], arr[largest]); // 交换的是根节点和最大子节点的值

        // 递归调整受影响的子树
        heapify(arr, n, largest); // 此时largest是交换后的子节点索引即原根节点，继续向下调整子树
    }
}

// 构建最大堆
// 功能：将无序数组调整为最大堆
void buildMaxHeap(int arr[], int n)
{
    // 从最后一个非叶子节点开始，向上调整
    // 最后一个非叶子节点的索引为 (n/2 - 1)
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(arr, n, i);
    }
}

// 堆排序主函数
void heapSort(int arr[], int n)
{
    // 步骤1：构建最大堆
    buildMaxHeap(arr, n);

    // 步骤2：逐个提取堆顶元素进行排序
    for (int i = n - 1; i > 0; i--)
    {
        // 将堆顶元素（最大值）与末尾元素交换  末尾是排好序的部分
        swap(arr[0], arr[i]);

        // 重新调整堆（堆的大小减1）
        heapify(arr, i, 0); // 每次都是从根节点开始调整
    }
}

// 打印数组
void printArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

// 测试函数
int main()
{
    int n;
    cout << "请输入数组大小: ";
    cin >> n;

    int *arr = new int[n];
    cout << "请输入 " << n << " 个数字: ";
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    cout << "排序前: ";
    printArray(arr, n);

    heapSort(arr, n);

    cout << "排序后: ";
    printArray(arr, n);

    delete[] arr;
    return 0;
}

// 堆排序复杂度分析：
//
// 时间复杂度：
// - 构建最大堆：O(n)
//   * 从最后一个非叶子节点开始向上调整
//   * 虽然单次 heapify 最坏为 O(log n)，但总体分析为 O(n)
//   * 这是因为大部分节点都在树的下层，调整距离较短
//
// - 排序过程：O(n log n)
//   * 需要进行 n-1 次提取最大值操作
//   * 每次提取后需要调用 heapify，时间复杂度为 O(log n)
//   * 总时间：(n-1) × O(log n) = O(n log n)
//
// - 总时间复杂度：O(n) + O(n log n) = O(n log n)

// - 最好情况：O(n log n) - 即使数组已经有序，仍需要完整的堆化过程
// - 最坏情况：O(n log n) - 数组完全逆序时
// - 平均情况：O(n log n) - 性能稳定，不受输入数据影响
//
// 空间复杂度：O(1)
// - 只使用了常数个额外变量
// - 是原地排序算法，不需要额外的存储空间
// - heapify 的递归深度最多为 O(log n)，但可以改写为迭代版本
//
// 稳定性：不稳定
// - 在构建堆和调整堆的过程中，相等元素的相对位置可能发生改变
// - 例如：[4a, 4b, 3] 构建最大堆时，4a 和 4b 的位置可能会交换
//
