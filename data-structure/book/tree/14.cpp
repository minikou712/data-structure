/*
题目14：试设计判断两棵二叉树是否相似的算法，所谓二叉树T1和T2相似，指的是T1和T2都是空的二叉树
或都只有一个根结点；或者T1的左子树和T2的左子树是相似的，且T1的右子树和T2的右子树是相似的。
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

// 判断两棵二叉树是否相似
bool isSimilar(TreeNode *T1, TreeNode *T2)
{
    // 两棵树都为空，相似
    if (T1 == nullptr && T2 == nullptr)
    {
        return true;
    }

    // 一棵为空，另一棵不为空，不相似
    if (T1 == nullptr || T2 == nullptr)
    {
        return false;
    }

    // 两棵树都只有根结点，相似（不用比较数据值）
    if (T1->left == nullptr && T1->right == nullptr &&
        T2->left == nullptr && T2->right == nullptr)
    {
        return true;
    }

    // 递归判断左子树和右子树是否相似
    return isSimilar(T1->left, T2->left) && isSimilar(T1->right, T2->right);
}

int main()
{
    // 测试代码
    return 0;
}
