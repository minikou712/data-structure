/*
题目08：已知二叉树以二叉链表存储，编写算法完成：对于树中每个元素值为x的结点，删除以它为根的子树，并释放相应的空间。
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
/**
 * 方法1（先删除）：
 *
 * 遍历到第一个值为3的节点
 * 删除以该节点为根的整个子树（包括子树中的所有3节点）
 * 继续处理右子树...
 *
 * 方法2（先递归）：
 *
 * 先递归到最深层的3节点，逐个删除
 * 回溯时删除上层的3节点
 */

// 上述两种结构最后得到的结果都正确，但是通常法一可以减少不必要的递归与回溯，效率更高。

// 删除以root为根的整个子树
void deleteSubtree(TreeNode *root) // 这段代码会删除传入的root节点本身。 因此不需要回到deleteNodeX函数再对根节点进行特殊处理
{
    if (root == nullptr)
        return;

    deleteSubtree(root->left); // 后序遍历
    deleteSubtree(root->right);
    delete root;
}

// 删除所有值为x的结点及其子树
void deleteNodeX(TreeNode *&root, int x)
{
    if (root == nullptr)
        return;

    if (root->data == x)
    {
        deleteSubtree(root);
        root = nullptr; // 重要：将指针设为nullptr  将当前删除的子树的根节点指针设为nullptr
        return;         // 删除后停止递归
    }

    deleteNodeX(root->left, x);
    deleteNodeX(root->right, x);
}







// 非递归算法
void deleteNodeXIterative2(TreeNode *&root, int x)
{
    if (root == nullptr)
        return;

    // 特殊处理根节点
    if (root->data == x)
    {
        deleteSubtree(root);
        root = nullptr;
        return;
    }

    queue<TreeNode *> q;
    q.push(root);

    while (!q.empty())
    {
        TreeNode *current = q.front();
        q.pop();

        // 检查并处理左子树
        if (current->left != nullptr)
        {
            if (current->left->data == x)
            {
                deleteSubtree(current->left);
                current->left = nullptr;
            }
            else
            {
                q.push(current->left);
            }
        }

        // 检查并处理右子树
        if (current->right != nullptr)
        {
            if (current->right->data == x)
            {
                deleteSubtree(current->right);
                current->right = nullptr;
            }
            else
            {
                q.push(current->right);
            }
        }
    }
}
int main()
{
    // 测试代码
    return 0;
}
