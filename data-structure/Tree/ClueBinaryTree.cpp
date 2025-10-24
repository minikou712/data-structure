#include <iostream>
using namespace std;
typedef int ElemType;

// 线索二叉树
typedef struct BiThrNode
{
    ElemType data;
    struct BiThrNode *lchild, *rchild;
    int ltag, rtag; // 0表示指向孩子，1表示指向前驱或后继
} BiThrNode, *BiThrTree;

void InitBiThrTree(BiThrTree &T) // 初始化线索二叉树
{
    T = nullptr; // 将树指针置为空
}

// 1. 中序线索化二叉树
void InThreading(BiThrNode *p, BiThrNode *&pre) // p为当前结点，pre为前驱结点
{
    if (p != nullptr)
    {
        InThreading(p->lchild, pre); // 线索化左子树

        if (p->lchild == nullptr) // 如果左孩子为空 设置左线索指向前驱
        {
            p->ltag = 1;     // 设置左线索
            p->lchild = pre; // 左孩子指向前驱  ***对于第一个结点，pre为nullptr
        }
        else
        {
            p->ltag = 0; // 左孩子不是线索
        }

        if (pre != nullptr && pre->rchild == nullptr) // 如果前驱的右孩子为空 设置右线索指向当前结点
        {
            pre->rtag = 1;   // 设置右线索
            pre->rchild = p; // 前驱的右孩子指向当前结点
        }
        else
        {
            pre->rtag = 0; // 前驱的右孩子不是线索
        }

        pre = p; // 更新前驱结点为当前结点

        InThreading(p->rchild, pre); // 线索化右子树
    }
}

void CreateInThreading(BiThrTree &T) // 创建中序线索二叉树
{
    BiThrNode *pre = nullptr; // 前驱结点初始化为空
    InThreading(T, pre);      // 调用线索化函数
    if (pre != nullptr)       // 如果前驱不为空，设置最后一个结点的右线索为1
    {
        pre->rtag = 1;         // 最后一个结点的右线索指向空
        pre->rchild = nullptr; // 最后一个结点的右孩子指向空
    }
}
// 2.先序线索化二叉树
void PreThreading(BiThrNode *p, BiThrNode *&pre)
{
    if (p != nullptr)
    {
        // 处理当前节点的线索化
        if (p->lchild == nullptr)
        {
            p->ltag = 1;
            p->lchild = pre;
        }
        else
        {
            p->ltag = 0;
        }

        if (pre != nullptr && pre->rchild == nullptr)
        {
            pre->rtag = 1;
            pre->rchild = p;
        }
        else
        {
            pre->rtag = 0;
        }

        pre = p;

        // 只需要检查左子树   **注意此处一定要检查ltag防止对线索结点访问从而导致无限递归   不同于中序线索化会先处理左子树
        if (p->ltag == 0)
        {
            PreThreading(p->lchild, pre);
        }

        // 右子树可以直接递归，因为当前节点的rtag不会在本层被修改
        PreThreading(p->rchild, pre);
    }
}

void CreatePreThreading(BiThrTree &T) // 创建先序线索二叉树
{
    BiThrNode *pre = nullptr;
    PreThreading(T, pre);
    if (pre != nullptr) // 如果返回的最后一个结点不为空，对其处理右线索
    {
        pre->rtag = 1;
        pre->rchild = nullptr;
    }
}

// 3.后序线索化二叉树
void PostThreading(BiThrNode *p, BiThrNode *&pre)
{
    if (p != nullptr)
    {
        // 先处理左子树
        PostThreading(p->lchild, pre);
        // 再处理右子树
        PostThreading(p->rchild, pre);

        // 由于先处理左右子树因此当前节点的ltag和rtag一定是还未处理的状态

        // 处理当前节点的线索化
        if (p->lchild == nullptr)
        {
            p->ltag = 1;
            p->lchild = pre;
        }
        else
        {
            p->ltag = 0;
        }

        if (pre != nullptr && pre->rchild == nullptr)
        {
            pre->rtag = 1;
            pre->rchild = p;
        }
        else
        {
            pre->rtag = 0;
        }

        pre = p; // 更新前驱结点为当前结点
    }
}

void CreatePostThreading(BiThrTree &T) // 创建后序线索二叉树
{
    BiThrNode *pre = nullptr;
    PostThreading(T, pre);
    if (pre != nullptr) // 如果返回的最后一个结点不为空，对其处理右线索
    {
        pre->rtag = 1;
        pre->rchild = nullptr;
    }
}

// 4.中序遍历线索二叉树
// 找到中序遍历的第一个节点（最左下的节点）
BiThrNode *FirstNode(BiThrNode *p)
{
    while (p->ltag == 0) // 当左标志为0时，说明有左孩子
        p = p->lchild;   // 继续向左
    return p;            // 返回最左下的节点
}

// 找到节点p在中序遍历中的后继节点
BiThrNode *NextNode(BiThrNode *p)
{
    if (p->rtag == 0)                // 如果右标志为0，说明有右子树
        return FirstNode(p->rchild); // 后继是右子树的最左节点
    else                             // 如果右标志为1，说明右指针是线索
        return p->rchild;            // 直接返回右线索指向的节点（后继）
}

// 找到中序遍历的最后一个节点（最右下的节点）
BiThrNode *LastNode(BiThrNode *p)
{
    while (p->rtag == 0) // 当右标志为0时，说明有右孩子
        p = p->rchild;   // 继续向右
    return p;            // 返回最右下的节点
}

// 找到节点p在中序遍历中的前驱节点
BiThrNode *PreNode(BiThrNode *p)
{
    if (p->ltag == 0)               // 如果左标志为0，说明有左子树
        return LastNode(p->lchild); // 前驱是左子树的最右节点
    else                            // 如果左标志为1，说明左指针是线索
        return p->lchild;           // 直接返回左线索指向的节点（前驱）
}
// 中序遍历线索二叉树（非递归）
void InOrderTraverse(BiThrTree T)
{
    if (T == nullptr)
        return;

    BiThrNode *p = FirstNode(T); // 从第一个节点开始
    while (p != nullptr)
    {
        cout << p->data << " "; // 访问当前节点
        p = NextNode(p);        // 移动到后继节点
    }
    cout << endl;
}

// 中序遍历线索二叉树（逆序，非递归）
void InOrderTraverseReverse(BiThrTree T)
{
    if (T == nullptr)
        return;

    BiThrNode *p = LastNode(T); // 从最后一个节点开始
    while (p != nullptr)
    {
        cout << p->data << " "; // 访问当前节点
        p = PreNode(p);         // 移动到前驱节点
    }
    cout << endl;
}

// 综上分析原理
// 1.先序线索二叉树     根左右根左右根左右
// 因此访问当前结点(根节点)
// 对于前驱
// 1.前驱如果ltag==1，p->lchild就是前驱。 2如果ltag==0,未线索化，需要找到当前结点父结点很复杂
// 对于后继
// 若ltag==0，有左子树，根据根左右，p->lchild即为后继
// 若ltag==1,rtag==0,左结点被线索化，右节点没有，则根据根(左)右，p->rchild就是后继结点
// 若rtag==1 右节点线索化直接p->rchild即为后继，
// 2.后序线索二叉树同理先序

// 3.中序线索二叉树
//           1左2根3右
//           /      \
//       左根右   左根右
//      /    \    /   \
//  左根右         左根右
// 对于前驱
// 1.如果ltag==1,p->lchild即前驱， 
//   ltag==0,根据左根右，当前根结点(2)的前驱在左子树的最右边 
// 对于后继
// 1.如果rtag==1,p->rchild即后继， 
//   rtag==0,根据左根右，当前根结点(2)的后继在右子树的最左边 
