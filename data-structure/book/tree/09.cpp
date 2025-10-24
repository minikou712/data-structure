/*
题目09：在二叉树中查找值为x的结点，求编写算法（用C语言）打印值为x的结点的所有祖先，假设值为x的结点不多于一个。
*/

#include <iostream>
#include <stack>
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

// 打印值为x的结点的所有祖先
TreeNode *pre = NULL;
bool printAncestors(TreeNode *root, int x)
{
    // 递归终止条件
    if (root == nullptr)
        return false;

    // 找到目标节点
    if (root->data == x)
        return true;

    // 在左子树或右子树中查找
    if (printAncestors(root->left, x) || printAncestors(root->right, x))
    {
        cout << root->data << " ";
        return true;
    }

    return false;
}
// 为什么不可以使用前驱指针记录父节点，前驱指针只能记录遍历顺序的上一个结点，在二叉树遍历中，你的上一个结点不一定是父节点。














// 非递归方法：简化版栈实现
// 这里path与stack是同步变化的，为什么还要path,因为path不容易遍历，如果用数组模拟栈可以。
// 非递归方法：简化版栈实现
bool printAncestorsIterative2(TreeNode *root, int x)
{
    if (root = nullptr)
        return false;

    TreeNode *st[100];
    int top = -1;
    TreeNode *current = nullptr;
    current = root;
    while (root != nullptr || top != -1)
    {
        // 不断遍历左子树
        while (current != nullptr)
        {
            st[++top] = current;
            if (current->data == x)
            {
                // 找到目标节点，打印栈中的祖先
                for (int i = 0; i < top; i++) // 修复循环体
                {
                    cout << st[i]->data << " ";
                }
                return true;
            }
            current = current->left;
        }

        if (top == -1)
            break;

        // 出栈，遍历出战结点右子树
        TreeNode *peek = st[top];
        TreeNode *lastvisted = nullptr; // 作用防止重复访问
        if (peek->right != nullptr && peek->right != lastvisted)
        {
            current = peek->right;
        }
        else
        {
            lastvisted = peek; // 更新最后访问的结点
            top--;             // 出栈
        }
    }
}
int main()
{
    // 构建测试用的二叉树
    /*
           1
         /   \
        2     3
       / \   / \
      4   5 6   7
     /
    8
    */
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);
    root->left->left->left = new TreeNode(8);

    cout << "二叉树结构:" << endl;
    cout << "       1" << endl;
    cout << "     /   \\" << endl;
    cout << "    2     3" << endl;
    cout << "   / \\   / \\" << endl;
    cout << "  4   5 6   7" << endl;
    cout << " /" << endl;
    cout << "8" << endl
         << endl;

    // 测试递归方法
    cout << "=== 测试递归方法 ===" << endl;

    // 测试用例1：查找节点8的祖先
    cout << "查找节点8的祖先: ";
    if (!printAncestors(root, 8))
    {
        cout << "未找到节点8";
    }
    cout << endl;

    // 测试用例2：查找节点5的祖先
    cout << "查找节点5的祖先: ";
    if (!printAncestors(root, 5))
    {
        cout << "未找到节点5";
    }
    cout << endl;

    // 测试用例3：查找节点3的祖先
    cout << "查找节点3的祖先: ";
    if (!printAncestors(root, 3))
    {
        cout << "未找到节点3";
    }
    cout << endl;

    // 测试用例4：查找根节点1的祖先
    cout << "查找节点1的祖先: ";
    if (!printAncestors(root, 1))
    {
        cout << "未找到节点1";
    }
    cout << endl;

    // 测试用例5：查找不存在的节点
    cout << "查找节点9的祖先: ";
    if (!printAncestors(root, 9))
    {
        cout << "未找到节点9";
    }
    cout << endl;

    cout << endl
         << "=== 测试非递归方法 ===" << endl;

    // 测试用例1：查找节点8的祖先
    cout << "查找节点8的祖先: ";
    if (!printAncestorsIterative2(root, 8))
    {
        cout << "未找到节点8";
    }
    cout << endl;

    // 测试用例2：查找节点5的祖先
    cout << "查找节点5的祖先: ";
    if (!printAncestorsIterative2(root, 5))
    {
        cout << "未找到节点5";
    }
    cout << endl;

    // 测试用例3：查找节点3的祖先
    cout << "查找节点3的祖先: ";
    if (!printAncestorsIterative2(root, 3))
    {
        cout << "未找到节点3";
    }
    cout << endl;

    // 测试用例4：查找根节点1的祖先
    cout << "查找节点1的祖先: ";
    if (!printAncestorsIterative2(root, 1))
    {
        cout << "未找到节点1";
    }
    cout << endl;

    // 测试用例5：查找不存在的节点
    cout << "查找节点9的祖先: ";
    if (!printAncestorsIterative2(root, 9))
    {
        cout << "未找到节点9";
    }
    cout << endl;

    // 测试边界情况：空树
    cout << endl
         << "=== 测试边界情况 ===" << endl;
    cout << "空树中查找节点1的祖先: ";
    if (!printAncestors(nullptr, 1))
    {
        cout << "未找到节点1 (空树)";
    }
    cout << endl;

    cout << "空树中查找节点1的祖先(非递归): ";
    if (!printAncestorsIterative2(nullptr, 1))
    {
        cout << "未找到节点1 (空树)";
    }
    cout << endl;

    return 0;
}
