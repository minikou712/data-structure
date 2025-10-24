#include <iostream>
#include <queue>
using namespace std;
typedef int ElemType;

typedef struct BiTNode
{
    ElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

void InitBiTree(BiTree &T) // 初始化二叉树
{
    T = nullptr; // 将树指针置为空
}

// 二叉树的遍历

// 1.先序遍历
void PreOrderTraverse(BiTree T)
{
    if (T != nullptr) //******一定要记得检查指针是否为空
    {
        cout << T->data << " ";      // 访问根结点
        PreOrderTraverse(T->lchild); // 先序遍历左子树
        PreOrderTraverse(T->rchild); // 先序遍历右子树
    }
}
// 2.中序遍历
void InOrderTraverse(BiTree T)
{
    if (T != nullptr)
    {
        InOrderTraverse(T->lchild); // 中序遍历左子树
        cout << T->data << " ";     // 访问根结点
        InOrderTraverse(T->rchild); // 中序遍历右子树
    }
}
// 3.后序遍历
void PostOrderTraverse(BiTree T)
{
    if (T != nullptr)
    {
        PostOrderTraverse(T->lchild); // 后序遍历左子树
        PostOrderTraverse(T->rchild); // 后序遍历右子树
        cout << T->data << " ";       // 访问根结点
    }
}

// 4.层序遍历
void LevelOrderTraverse(BiTree T)
{
    if (T == nullptr)
        return;

    queue<BiTree> q;
    q.push(T);

    while (!q.empty())
    {
        BiTree current = q.front();
        q.pop();
        cout << current->data << " ";

        if (current->lchild != nullptr)
            q.push(current->lchild);
        if (current->rchild != nullptr)
            q.push(current->rchild);
    }
}

//5.二叉树的销毁
//本质上和后序遍历类似，递归地销毁每个结点
void DestroyBiTree(BiTree &T)
{
    if (T != nullptr)
    {
        DestroyBiTree(T->lchild); // 销毁左子树
        DestroyBiTree(T->rchild); // 销毁右子树
        delete T;                 // 销毁根结点
        T = nullptr;              // 将指针置为空
    }
}

//6.二叉树的深度
//原理： 不断向下递归到叶子结点，返回最大深度加1   **返回是从空节点开始回溯
int BiTreeDepth(BiTree T)
{
    if (T == nullptr)
        return 0; // 空树深度为0

    int leftDepth = BiTreeDepth(T->lchild); // 左子树深度
    int rightDepth = BiTreeDepth(T->rchild); // 右子树深度

    return max(leftDepth, rightDepth) + 1; // 返回最大深度加1   
}