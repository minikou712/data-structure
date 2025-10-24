/*
题目03：设计一个非递归算法，求二叉树高度
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
    TreeNode(int x) : data(x), left(nullptr), right(nullptr) {}   // 构造函数初始化节点
};

// 实现思想
// 二叉树的高度是指从根节点到最深叶子节点的最长路径上的节点数。
// 非递归算法可以使用层序遍历（队列）来计算每一层，统计层数即为高度。
int getHeight(TreeNode *root)
{
    if (root == nullptr)
        return 0; // 空树高度为0

    // 使用数组模拟队列
    const int MAX_SIZE = 10000; // 假设最大节点数
    TreeNode* queue[MAX_SIZE];
    int front = 0, rear = 0; // 队头和队尾指针
    
    // 根节点入队
    queue[rear++] = root;
    int height = 0;

    while (front < rear) // 队列不为空
    {
        int levelSize = rear - front; // 当前层的节点数
        height++;                     // 层数加1

        // 处理当前层的所有节点
        for (int i = 0; i < levelSize; i++)
        {
            TreeNode *current = queue[front++]; // 出队

            // 将下一层的节点加入队列
            //不为空才入队
            if (current->left)
                queue[rear++] = current->left;
            if (current->right)
                queue[rear++] = current->right;
        }
    }

    return height;
}
// 递归算法
int getHeightRecursive(TreeNode *root)
{
    if (root == nullptr)
        return 0;                                                                    // 空树高度为0
    return 1 + max(getHeightRecursive(root->left), getHeightRecursive(root->right)); // 递归计算左右子树高度
}

int main()
{
    // 测试代码
    // 构建一个测试二叉树
    //       1
    //      / \
    //     2   3
    //    / \
    //   4   5
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    cout << "非递归算法计算的树高度: " << getHeight(root) << endl;
    cout << "递归算法计算的树高度: " << getHeightRecursive(root) << endl;

    return 0;
}
