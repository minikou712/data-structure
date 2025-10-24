/*
题目15：【2014统考真题】二叉树的带权路径长度（WPL）是二叉树中所有叶结点的带权路径长度之和。
给定一棵二叉树T，采用二叉链表存储，结点结构为
| left | weight | right |
其中叶结点的weight域保存该结点的非负权值，设root为指向T的根结点的指针。
请设计求T的WPL的算法。
*/

#include <iostream>
using namespace std;

// 二叉树节点结构（带权值）
struct TreeNode
{
    int weight;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int w) : weight(w), left(nullptr), right(nullptr) {}
};

//实现思路，对二叉树进行深度搜索，记录搜索到当前结点所在的层次，如果是叶子结点则记录带权路径长度
int caculateWpl(TreeNode *root,int depth)
{
    if(root==nullptr)
    {
        return 0;   
    }

    if(root->left==nullptr&&root->right==nullptr)
    {
        return root->weight*depth;
    }
    return caculateWpl(root->left,depth+1)+caculateWpl(root->right,depth+1);
}

int main()
{
    // 测试代码
    return 0;
}
