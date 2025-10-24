#include "sqlist.h"


// 题目14：【2020统考真题】

// 定义三元组(a, b, c)(a, b, c均为正数)的距离
// D=|a-b|+|b-c|+|c-a|。给定3个非空整数集合S₁, S₂和S₃，
// 请设计一个尽可能高效的算法，计算并输出所有可能的三元组
// (a, b, c)(a∈S₁, b∈S₂, c∈S₃)中的最小距离。
// 例如S₁={-1, 0, 9}, S₂={-25, -10, 10, 11}, S₃={2, 9, 17, 30, 41}，
// 则最小距离为2，相应的三元组为(9, 10, 9)。

// 要求：
// 给出算法的基本设计思想。
// 根据设计思想，采用C语言或C++语言描述算法，关键之处给出注释。
// 说明你所设计算法的时间复杂度和空间复杂度。

//磁体给的是有序序列

// 思路：
// 1. 对三个集合进行排序。
// 2. 使用三个指针分别指向三个集合的当前元素，计算距离。
// 3. 比较当前距离与最小距离，更新最小距离。
#include <algorithm>

int minDistance(int S1[], int S2[], int S3[], int n1, int n2, int n3) {
    // 对三个集合进行排序
    sort(S1, S1 + n1);
    sort(S2, S2 + n2);
    sort(S3, S3 + n3);

    int i = 0, j = 0, k = 0;
    int minDist = INT_MAX; // 初始化最小距离为最大整数

    while (i < n1 && j < n2 && k < n3) {
        // 计算当前三元组的距离
        int a = S1[i], b = S2[j], c = S3[k];
        int dist = abs(a - b) + abs(b - c) + abs(c - a);

        // 更新最小距离
        if (dist < minDist) {
            minDist = dist;
        }

        // 移动指针
        int minValue = min(a, min(b, c));
        if (minValue == a) {
            i++;
        } else if (minValue == b) {
            j++;
        } else {
            k++;
        }
    }

    return minDist; // 返回最小距离
}


