/*
题目06：设树B是一棵采用链式结构存储的二叉树，编写一个把树B中所有结点的左、右子树进行交换的函数。
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

// 方法1：先交换当前节点，再递归处理子树
void swapLeftRight1(TreeNode *root)
{
    if (root == nullptr)
    {
        return;
    }
    
    // 先交换当前节点的左右子树
    TreeNode *temp = root->left;
    root->left = root->right;
    root->right = temp;
    
    // 再递归处理左右子树
    swapLeftRight1(root->left);
    swapLeftRight1(root->right);
}

// 方法2：先递归处理子树，再交换当前节点
void swapLeftRight2(TreeNode *root)
{
    if (root == nullptr)
    {
        return;
    }
    
    // 先递归处理左右子树
    swapLeftRight2(root->left);
    swapLeftRight2(root->right);
    
    // 再交换当前节点的左右子树
    TreeNode *temp = root->left;
    root->left = root->right;
    root->right = temp;
}
//无论使用哪种方法，最终都会得到相同的结果：二叉树中所有结点的左右子树都被交换。


int main()
{
    // 测试代码
    return 0;
}
