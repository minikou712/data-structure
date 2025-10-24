/*
题目10：设一棵二叉树的结点结构为（LLINK,INFO,RLINK），ROOT为指向该二叉树根结点的指针，
p和q分别为指向该二叉树中任意两个结点的指针，试编写算法ANCESTOR（ROOT,p,q,r），
找到p和q的最近公共祖先结点r。
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

TreeNode *findAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
{
    // 基本情况
    if (root == nullptr || root == p || root == q)
        return root;

    // 在左右子树中分别查找
    TreeNode *left = findAncestor(root->left, p, q);
    TreeNode *right = findAncestor(root->right, p, q);

    // 如果p和q分别在左右子树中，则当前节点为最近公共祖先
    if (left != nullptr && right != nullptr)
        return root;

    // 否则返回非空的子树结果
    return left != nullptr ? left : right;
}
void ANCESTOR(TreeNode *ROOT, TreeNode *p, TreeNode *q, TreeNode *&r)
{
    r = findAncestor(ROOT, p, q);
}

int main()
{ /*
 递归过程详解：

 调用栈1: findAncestor(3, 6, 4)
 ├── 3 != nullptr, 3 != 6, 3 != 4 → 继续递归
 ├── left = findAncestor(5, 6, 4)
 │   │
 │   调用栈2: findAncestor(5, 6, 4)
 │   ├── 5 != nullptr, 5 != 6, 5 != 4 → 继续递归
 │   ├── left = findAncestor(6, 6, 4)
 │   │   │
 │   │   调用栈3: findAncestor(6, 6, 4)
 │   │   └── 6 == 6 → return 6 ✓
 │   │
 │   ├── right = findAncestor(2, 6, 4)
 │   │   │
 │   │   调用栈4: findAncestor(2, 6, 4)
 │   │   ├── 2 != nullptr, 2 != 6, 2 != 4 → 继续递归
 │   │   ├── left = findAncestor(7, 6, 4)
 │   │   │   │
 │   │   │   调用栈5: findAncestor(7, 6, 4)
 │   │   │   └── 7 != 6, 7 != 4, 左右子树为null → return nullptr
 │   │   │
 │   │   ├── right = findAncestor(4, 6, 4)
 │   │   │   │
 │   │   │   调用栈6: findAncestor(4, 6, 4)
 │   │   │   └── 4 == 4 → return 4 ✓
 │   │   │
 │   │   └── left=nullptr, right=4 → return 4
 │   │
 │   └── left=6, right=4 (都非空) → return 5 ✓
 │
 ├── right = findAncestor(1, 6, 4)
 │   └── ... (在右子树中找不到6和4) → return nullptr
 │
 └── left=5, right=nullptr → return 5

 最终结果：节点5是节点6和节点4的最近公共祖先
 */
    // 测试代码
    return 0;
}
