/*
题目16：【2017统考真题】请设计一个算法，将给定的表达式树（二叉树）转换为等价的中缀表达式
（通过括号反映操作的优先级）并输出。
二叉树结点定义如下：
typedef struct node{
    char data[10];        //假设存储数或操作符
    struct node *left, *right;
}BTree;
*/

#include <iostream>
#include <string>
#include <cstring>
using namespace std;

// 二叉树节点结构
struct BTree
{
    char data[10]; // 存储数或操作符
    BTree *left;
    BTree *right;
};

// 创建节点的辅助函数
BTree *createNode(const char *value)
{
    BTree *node = new BTree;
    strcpy(node->data, value);
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

// 表达式树转中缀表达式
void convertToInfix(BTree *root)
{
    if (root == nullptr)
    {
        return;
    }

    // 如果是叶子节点（操作数），直接输出
    if (root->left == nullptr && root->right == nullptr)
    {
        cout << root->data;
        return;
    }

    // 如果是操作符节点，需要加括号
    cout << "(";
    convertToInfix(root->left);  // 先遍历左子树
    cout << root->data;          // 输出操作符
    convertToInfix(root->right); // 再遍历右子树
    cout << ")";
}

int main()
{
    // 测试用例1: 构建表达式树 (a+b)*c
    //       *
    //      / \
    //     +   c
    //    / \
    //   a   b

    BTree *root1 = createNode("*");
    root1->left = createNode("+");
    root1->right = createNode("c");
    root1->left->left = createNode("a");
    root1->left->right = createNode("b");

    cout << "测试1 - 表达式树转中缀: ";
    convertToInfix(root1);
    cout << endl;

    // 测试用例2: 构建表达式树 a+(b*c)
    //       +
    //      / \
    //     a   *
    //        / \
    //       b   c

    BTree *root2 = createNode("+");
    root2->left = createNode("a");
    root2->right = createNode("*");
    root2->right->left = createNode("b");
    root2->right->right = createNode("c");

    cout << "测试2 - 表达式树转中缀: ";
    convertToInfix(root2);
    cout << endl;

    // 测试用例3: 构建表达式树 (a*b)+(-(c-d))
    //         +
    //        / \
    //       *   -
    //      / \   \
    //     a   b   -
    //            / \
    //           c   d

    BTree *root3 = createNode("+");
    root3->left = createNode("*");
    root3->right = createNode("-"); // 负号（一元运算符）
    root3->left->left = createNode("a");
    root3->left->right = createNode("b");
    root3->right->right = createNode("-"); // 减法（二元运算符）
    root3->right->right->left = createNode("c");
    root3->right->right->right = createNode("d");

    cout << "测试3 - 表达式树转中缀: ";
    convertToInfix(root3);
    cout << endl;

    // 测试用例4: 单个节点
    BTree *root4 = createNode("x");
    cout << "测试4 - 单个节点: ";
    convertToInfix(root4);
    cout << endl;

    return 0;
}