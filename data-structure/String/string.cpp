#include <iostream>
#include <string>
using namespace std;


//暴力匹配串模式串
// 实现原理
// 1.遍历主串的每个字符
// 2.对于每个字符，遍历模式串的每个字符进行匹配
// 3.如果匹配成功，返回匹配的起始位置
int BruteForceMatch(const string &text, const string &pattern)
{
    int i=0, j=0; // i为主串索引，j为模式串索引
    while (i < text.length() && j < pattern.length())
    {
        if (text[i] == pattern[j]) // 如果字符匹配
        {
            i++;
            j++;
        }
        else // 如果字符不匹配，回溯主串索引
        {
            i = i - j + 1; // 回溯到下一个可能的匹配位置
            j = 0;         // 重置模式串索引
        }
    }
    return (j == pattern.length()) ? (i - j) : -1; // 如果匹配成功，返回起始位置，否则返回-1
    // 注意：这里的i-j是匹配成功时的起始位置
}

// KMP算法
// 实现原理
// 1. 预处理模式串，构建部分匹配表,next数组
// 2. 在主串中查找模式串时，利用部分匹配表来避免不必要的比较
// 3. 如果发生不匹配，根据部分匹配表移动模式串


//next数组的构建
// 实现原理
// 1. 初始化next数组，next[0] = -1
// 2. 遍历模式串，比较当前字符与前一个字符是否相等
// 3. 如果相等，next[i] = j + 1；如果不相等，j = next[j]，直到找到相等的字符或j为-1
int nextp[10001]; // 全局变量，存储next数组
<<<<<<< Updated upstream

void BuildNext(const string &pattern)
{
    int i=1,j=0;
    nextp[1] = 0; // 初始化next数组
    while (i < pattern.length())
    {
        if (j==0 || pattern[i] == pattern[j]) // 如果当前字符与前一个字符相等
=======
//next[j]表示模式串前j个字符的最长公共前后缀长度  本质是记录模式串的前缀和后缀的最长公共部分
void BuildNext(const string &pattern)
{
    int i=1,j=0;  // i为模式串索引 为什么从i=1开始？因为 j=0表示第一个字符没有前缀
    nextp[0] = 0; // 初始化next数组
    nextp[1] = 0; // 初始化next数组
    while (i < pattern.length())
    {
        if (j==0 || pattern[i] == pattern[j]) // 如果当前字符与前一个字符相等   如果j为0，说明没有前缀
>>>>>>> Stashed changes
        {
            i++;
            j++;
            nextp[i] = j; // 更新next数组
        }
        else // 如果不相等，回溯j
        {
            j = nextp[j]; // 回溯到前一个匹配位置
        }
    }
}

<<<<<<< Updated upstream
// KMP算法实现
=======
// KMP算法实现   text,pattern从1开始
>>>>>>> Stashed changes
int KMPMatch(const string &text, const string &pattern)
{
    BuildNext(pattern); // 构建next数组
    int i=1, j=1; // i为主串索引，j为模式串索引
    while (i <= text.length() && j <= pattern.length())
    {
<<<<<<< Updated upstream
        if (j == 0 || text[i - 1] == pattern[j - 1]) // 如果字符匹配
=======
        if (j == 0 || text[i] == pattern[j]) // 如果字符匹配 
>>>>>>> Stashed changes
        {
            i++;
            j++;
        }
        else // 如果字符不匹配，根据next数组回溯
        {
<<<<<<< Updated upstream
            j = nextp[j-1]; // 回溯到前一个匹配位置
=======
            j = nextp[j]; // 回溯到前一个匹配位置
>>>>>>> Stashed changes
        }
    }
    return (j == pattern.length()) ? (i - j) : -1; // 如果匹配成功，返回起始位置，否则返回-1
}
