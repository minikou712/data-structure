/*
题目12：设有一棵满二叉树（所有结点值均不同），已知其先序序列为pre，设计一个算法求其后序序列post。
*/

#include <iostream>
#include <vector>
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
 * 实现思想：利用满二叉树的性质，先序遍历的左子树和右子树的节点数相等。
 * 因此可以通过先序序列的根节点和左右子树的节点数来划分后序序列。
 * 具体步骤如下：
 * 1. 先序序列的第一个元素是根节点。
 * 2. 计算左子树的节点数，然后递归处理左子树和右子树。
 * 3. 将左子树的后序序列和右子树的后序序列拼接起来，最后加上根节点。
 */
// 根据满二叉树的先序序列构建后序序列
/**
 * @preStart: 先序序列的起始索引
 * @preEnd: 先序序列的结束索引
 * @postStart: 后序序列的起始索引
 * @postEnd: 后序序列的结束索引
 */
void preToPost(vector<int> &pre, int preStart, int preEnd, vector<int> &post, int postStart, int postEnd)
{
    if (preStart > preEnd)
    {
        return;
    }

    // 3. 合并（Combine）
    // 先序序列的第一个元素是根节点，是后序序列的最后一个元素
    post[postEnd] = pre[preStart];

    // 处理叶子节点的情况
    if (preStart == preEnd)
    {
        return;
    }

    // 对于满二叉树，左子树和右子树的结点数相等
    // 1. 分解（Divide）
    int leftSize = (preEnd - preStart) / 2;

    // 2. 解决（Conquer）
    // 递归处理左子树
    preToPost(pre, preStart + 1, preStart + leftSize, post, postStart, postStart + leftSize - 1);

    // 递归处理右子树
    preToPost(pre, preStart + leftSize + 1, preEnd, post, postStart + leftSize, postEnd - 1);
}

// 将先序序列转换为后序序列
vector<int> preorderToPostorder(vector<int> &preorder)
{
    int n = preorder.size();
    vector<int> postorder(n); // 后序序列
    preToPost(preorder, 0, n - 1, postorder, 0, n - 1);
    return postorder;
}

int main()
{
    //     // 第1层：处理整棵树 [1,2,4,5,3,6,7]
    // post[6] = 1  // 根节点先占位！
    // 递归左子树 [2,4,5] → post[0-2]
    // 递归右子树 [3,6,7] → post[3-5]
    
    // // 第2层左：处理左子树 [2,4,5]
    // post[2] = 2  // 左子树根占位！
    // 递归左子树 [4] → post[0]
    // 递归右子树 [5] → post[1]
    
    // // 第3层左左：处理叶子 [4]
    // post[0] = 4  // 叶子节点直接填入
    
    // // 第3层左右：处理叶子 [5]
    // post[1] = 5  // 叶子节点直接填入
    
    // // 第2层右：处理右子树 [3,6,7]
    // post[5] = 3  // 右子树根占位！
    // 递归左子树 [6] → post[3]
    // 递归右子树 [7] → post[4]
    
    // // 第3层右左：处理叶子 [6]
    // post[3] = 6  // 叶子节点直接填入
    
    // // 第3层右右：处理叶子 [7]
    // post[4] = 7  // 叶子节点直接填入
    
    return 0;
}
