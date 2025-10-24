/*
题目05：假设二叉树采用二叉链表存储结构，计算二叉树所有双分支节点的个数。
--- IGNORE ---
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
//实现思想：
//判断一个节点是否为双分支节点，只需检查其左右子节点是否均不为空。

//递归实现
int countDoubleBranchNodes(TreeNode *root)
{
    if (root == nullptr)
        return 0;

    int count = 0;
    if (root->left != nullptr && root->right != nullptr)
        count = 1;

    return count + countDoubleBranchNodes(root->left) + countDoubleBranchNodes(root->right);
}

int main()
{
    // 测试代码
    return 0;
}
