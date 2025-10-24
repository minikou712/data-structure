#include <iostream>
#include <algorithm>
using namespace std;

#define MAX_SIZE 100

// 二叉树的存储结构定义
typedef struct
{
    int SqBiTNode[MAX_SIZE]; // 存储二叉树结点的数组
    int ElemNum;             // 实际占用的数组元素个数
} SqBiTree;

/*
题目17：【2022统考真题】已知非空二叉树T的线索结构为正常线索，表用顺序存储结构，数据
结构定义如下：

T1的存储结构如下：
T1.SqBiTNode: 40 25 60 -1 30 -1 80 -1 -1 27
T1.ElemNum = 10

T2的存储结构如下：
T2.SqBiTNode: 40 50 60 -1 30 -1 -1 -1 -1 -1 35
T2.ElemNum = 11

请设计一个高效的算法，判定一棵表示这种存储结构的二叉树是否为二叉搜索树。
要求：
1) 给出算法的基本设计思想。
2) 根据设计思想，采用C或C++语言描述算法，关键之处给出注释。
*/

// 使用pmax和pmin数组的方法判断BST
bool isBST(SqBiTree sqBiTree)
{
    int length = sqBiTree.ElemNum;
    int pmax[MAX_SIZE], pmin[MAX_SIZE];

    // 初始化pmax和pmin数组
    for (int i = 0; i < length; i++)
    {
        pmax[i] = INT_MAX; // 初始化为最大值
        pmin[i] = INT_MIN; // 初始化为最小值
    }

    // 从后向前扫描，更新pmax和pmin数组
    for (int i = length - 1; i >= 0; i--)
    {
        if (sqBiTree.SqBiTNode[i] == -1)
        {
            continue; // 跳过空节点
        }

        int leftChild = 2 * i + 1;  // 左子节点索引
        int rightChild = 2 * i + 2; // 右子节点索引

        // 更新左子树的最大值约束
        if (leftChild < length)
        {
            pmax[leftChild] = sqBiTree.SqBiTNode[i];
        }

        // 更新右子树的最小值约束
        if (rightChild < length)
        {
            pmin[rightChild] = sqBiTree.SqBiTNode[i];
        }
    }

    // 验证每个节点是否满足BST性质
    for (int i = 0; i < length; i++)
    {
        if (sqBiTree.SqBiTNode[i] == -1)
        {
            continue; // 跳过空节点
        }

        // 检查当前节点是否在允许的范围内
        if (sqBiTree.SqBiTNode[i] >= pmax[i] || sqBiTree.SqBiTNode[i] <= pmin[i])
        {
            return false;
        }
    }

    return true;
}
/**
 * 递归 + 范围约束：每个节点都必须在一个特定的数值范围内。

关键要点：
递归终止条件：

索引越界 → 返回true（空子树是合法的）
节点为空(-1) → 返回true
范围检查：

每个节点值必须严格在 (minVal, maxVal) 范围内
注意是开区间，不能等于边界值
递归调用：

左子树：继承下界minVal，上界更新为current
右子树：下界更新为current，继承上界maxVal
逻辑与操作：

只有左右子树都是BST，整棵树才是BST
 */
// 递归判断BST的辅助函数
// index: 当前节点索引, minVal: 允许的最小值, maxVal: 允许的最大值
bool isBSTHelper(SqBiTree &tree, int index, int minVal, int maxVal)
{
    // 越界或空节点，返回true
    if (index >= tree.ElemNum || tree.SqBiTNode[index] == -1)
        return true;

    int current = tree.SqBiTNode[index];

    // 当前节点必须在(minVal, maxVal)范围内
    if (current <= minVal || current >= maxVal)
        return false;

    // 递归检查左子树和右子树
    // 左子树：上界更新为current，下界保持不变
    // 右子树：下界更新为current，上界保持不变
    return isBSTHelper(tree, 2 * index + 1, minVal, current) && // 左子树
           isBSTHelper(tree, 2 * index + 2, current, maxVal);   // 右子树
}

// 主函数：判断是否为BST
bool isBST(SqBiTree sqBiTree)
{
    return isBSTHelper(sqBiTree, 0, INT_MIN, INT_MAX);
}
// 测试函数
int main()
{
    // 测试用例1：T1
    SqBiTree T1;
    T1.SqBiTNode[0] = 40;
    T1.SqBiTNode[1] = 25;
    T1.SqBiTNode[2] = 60;
    T1.SqBiTNode[3] = -1;
    T1.SqBiTNode[4] = 30;
    T1.SqBiTNode[5] = -1;
    T1.SqBiTNode[6] = 80;
    T1.SqBiTNode[7] = -1;
    T1.SqBiTNode[8] = -1;
    T1.SqBiTNode[9] = 27;
    T1.ElemNum = 10;

    cout << "T1 is BST: " << (isBST(T1) ? "Yes" : "No") << endl;

    // 测试用例2：T2
    SqBiTree T2;
    T2.SqBiTNode[0] = 40;
    T2.SqBiTNode[1] = 50;
    T2.SqBiTNode[2] = 60;
    T2.SqBiTNode[3] = -1;
    T2.SqBiTNode[4] = 30;
    T2.SqBiTNode[5] = -1;
    T2.SqBiTNode[6] = -1;
    T2.SqBiTNode[7] = -1;
    T2.SqBiTNode[8] = -1;
    T2.SqBiTNode[9] = -1;
    T2.SqBiTNode[10] = 35;
    T2.ElemNum = 11;

    cout << "T2 is BST: " << (isBST(T2) ? "Yes" : "No") << endl;

    return 0;
}
