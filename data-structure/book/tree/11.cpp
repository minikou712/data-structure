/*
题目11：假设二叉树采用二叉链表存储结构，设计一个算法，求非空二叉树b的宽度
（具有结点数最多的那一层的结点个数）。
*/

#include <iostream>
#include <queue>
using namespace std;

// 二叉树节点结构
struct TreeNode
{
    int data;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : data(x), left(nullptr), right(nullptr) {}
};

// 求二叉树的宽度
int getWidth(TreeNode *root)
{
    if (root == nullptr)
    {
        return 0;
    }

    TreeNode *queue[100];
    int front=0,rear=0;
    queue[rear++] = root; // 根节点入队
    int maxWidth = 1;
    
    while (front < rear)
    {
        int currentLevelSize = rear-front;
        maxWidth = max(maxWidth, currentLevelSize);

        // 处理当前层的所有结点
        for (int i = 0; i < currentLevelSize; i++)
        {
            TreeNode *node = queue[front++]; // 出队

            if (node->left)
               queue[rear++] = node->left; // 左子节点入队
            if (node->right)
               queue[rear++] = node->right; // 右子节点入队
        }
    }

    return maxWidth;
}

int main()
{
    // 测试代码
    return 0;
}
