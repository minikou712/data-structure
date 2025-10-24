#include <iostream>
using namespace std;
typedef int ElemType;

//链式队列  
//相比于循环队列，链式队列不需要预先定义大小，可以动态扩展，队列的大小仅受限于系统内存。
typedef struct Node {
    ElemType data;          // 存储队列元素
    struct Node *next;     // 指向下一个节点
} Node;
typedef struct {
    Node *front;           // 队头指针
    Node *rear;            // 队尾指针
} ChainedQueue;

// 初始化链式队列   带头结点的链式队列     队头指针指向头结点，队尾指针指向最后一个元素的next指针(不同于循环队列)
void InitChainedQueue(ChainedQueue &Q) {
    Q.front = new Node;     // 创建头结点
    Q.front->next = nullptr; // 头结点的next指针初始化为nullptr
    Q.rear = Q.front;       // 队尾指针指向头结点
}


// 判断链式队列是否为空
bool IsEmpty(const ChainedQueue &Q) {
    return Q.front == Q.rear; // 如果队头和队尾指针相同，则队列为空
}

// 入队操作
bool EnQueue(ChainedQueue &Q, ElemType e) {
    Node *newNode = new Node; // 创建新节点
    newNode->data = e;        // 设置新节点的数据
    newNode->next = nullptr;  // 新节点的next指针初始化为nullptr

    Q.rear->next = newNode;   // 将新节点链接到队尾
    Q.rear = newNode;          // 更新队尾指针为新节点
    return true;
}
// 出队操作  
//注意：判断最后一个元素出队后，队尾指针需要指向头结点
bool DeQueue(ChainedQueue &Q, ElemType &e) {
    if (IsEmpty(Q)) {
        cerr << "队列为空，无法出队" << endl;
        return false;
    }
    Node *temp = Q.front->next; // 获取队头元素
    e = temp->data;              // 取出队头元素的数据
    Q.front->next = temp->next;  // 更新队头指针
    if (Q.rear == temp) {        // 如果队列只有一个元素
        Q.rear = Q.front;        // 队尾指针也指向头结点
    }
    delete temp;                // 释放原队头节点
    return true;
}