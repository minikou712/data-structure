/*
题目13：设计一个算法将二叉树的叶结点按从左到右的顺序连成一个单链表，表头指针为head，
二叉树按二叉链表方式存储，链接时用叶结点的右指针域来充当链表指针。
*/

#include <iostream>
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
 * 实现思想：利用深度优先搜索（DFS）遍历二叉树，找到所有叶子节点并将其连接成链表。
 * 具体步骤如下：
 * 1. 递归遍历左子树，找到所有叶子节点并连接。
 * 2. 递归遍历右子树，找到所有叶子节点并连接。
 * 3. 在连接过程中，维护一个指向当前链表尾部的指针。
 */

// 全局变量，用于维护链表
TreeNode *head = nullptr;
TreeNode *tail = nullptr;

// 将叶结点按从左到右顺序连成链表
void connectLeaves(TreeNode *root)
{
    if (root == nullptr)
    {
        return;
    }

    // 如果是叶结点
    if (root->left == nullptr && root->right == nullptr)
    {
        if (head == nullptr)
        {
            head = root;
            tail = root;
        }
        else
        {
            tail->right = root;
            tail = root;
        }
        root->right = nullptr; // 链表结尾
        return;
    }

    // 递归处理左子树和右子树
    connectLeaves(root->left);
    connectLeaves(root->right);
}

int main()
{
    // 测试代码
    return 0;
}
