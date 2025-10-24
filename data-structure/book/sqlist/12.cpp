#include "sqlist.h"

// 题目12：【2013统考真题】

// 已知一个整数序列A=(a₀, a₁, ···, aₙ₋₁)，
// 其中0≤aᵢ<n (0≤i<n)。若存在aₚ₁=aₚ₂=···=aₚₘ=x且m>n/2 (0≤pⱼ<n, 1≤k≤m)，
// 则称x为A的主元素。例如A=(0, 5, 5, 3, 5, 7, 5, 5)，则5为主元素；
// 又如A=(0, 5, 5, 3, 5, 1, 5, 7)，则A中没有主元素。
// 假设A中的n个元素保存在一个一维数组中，
// 请设计一个尽可能高效的算法，找出A的主元素；若不存在主元素，则输出-1。

// 要求：
// 给出算法的基本设计思想。
// 根据设计思想，采用C或C++或Java语言描述算法，关键之处给出注释。
// 说明你所设计算法的时间复杂度和空间复杂度。

//思路一 
//1.用数组模拟哈希记录每个元素出现的次数
//2.找出出现次数超过n/2的元素   
int Majority(int A[], int n)
{
    int counts[n] = {0}; // 初始化计数数组
    for (int i = 0; i < n; i++)
    {
        counts[A[i]]++; // 统计每个元素出现的次数
        if (counts[A[i]] > n / 2) // 如果出现次数超过n/2
        {
            return A[i]; // 返回该元素
        }
    }   
    return -1; // 如果没有主元素，返回-1
}


// 思路二：摩尔投票算法（更高效）
// 时间复杂度：O(n)，空间复杂度：O(1)
int MajorityVote(int A[], int n)
{
    int candidate = -1; // 候选主元素
    int count = 0;      // 计数器
    
    // 第一轮：找到候选主元素
    for (int i = 0; i < n; i++)
    {
        if (count == 0)
        {
            candidate = A[i]; // 选择新的候选元素
            count = 1;
        }
        else if (A[i] == candidate)
        {
            count++; // 相同元素，计数器加1
        }
        else
        {
            count--; // 不同元素，计数器减1
        }
    }
    
    // 第二轮：验证候选元素是否为主元素
    count = 0;
    for (int i = 0; i < n; i++)
    {
        if (A[i] == candidate)
        {
            count++;
        }
    }
    
    return (count > n / 2) ? candidate : -1;
}