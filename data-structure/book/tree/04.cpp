/*
题目04：二叉树按二叉链表存储，给出判断一个二叉树是否是完全二叉树的算法。
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

// 在这里实现解答代码
// 实现思想
// 按照eg3的层次遍历，使用队列来存储节点。
// 如果在遍历过程中遇到一个节点的右子树不为空而左子树为空，则该二叉树不是完全二叉树。
bool isCompleteTreeArray(TreeNode *root)
{
    if (root == nullptr)
        return true; // 空树是满二叉树

    queue<TreeNode *> queue;
    queue.push(root);
    bool flag = false; // 标志是否遇到第一个缺失子节点

    while (!queue.empty())
    {
        TreeNode *current = queue.front();
        queue.pop();

        if (current->left)
        {
            if (flag) // 如果之前遇到过缺失子节点，则不是完全二叉树
                return false;
            queue.push(current->left);
        }
        else
        {
            flag = true; // 遇到第一个缺失子节点
        }

        if (current->right)
        {
            if (flag) // 如果之前遇到过缺失子节点，则不是完全二叉树
                return false;
            queue.push(current->right);
        }
        else
        {
            flag = true; // 遇到第一个缺失子节点
        }
    }
    


    return true;
}

int main()
{
    // 测试代码
    return 0;
}
