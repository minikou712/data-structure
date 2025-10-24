/*
题目07：假设二叉树采用二叉链存储结构存储，设计一个算法，求先序遍历序列中第k（1≤k≤二叉树中结点个数）个结点的值。
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

// 全局计数器
int count = 0;

int findKthPreorderHelper(TreeNode *root, int k)
{
    if (root == nullptr)
    {
        return -1; // 修复：返回int值
    }

    // 先序遍历：根-左-右
    count++;
    if (count == k)
    {
        return root->data;
    }

    /** 
     * 递归搜索左子树
     * 如果左子树找到了（返回值≠-1），立即返回结果
     * 这是先序遍历的**"左"**部分
     */
    int result = findKthPreorderHelper(root->left, k);
    if (result != -1)
        return result; // 在左子树找到就返回

    return findKthPreorderHelper(root->right, k); // 在右子树中找
}
int main()
{
    // 测试代码
    return 0;
}
