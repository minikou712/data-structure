#include <iostream>
using namespace std;
typedef int ElemType;


//循环队列定义结构

typedef struct {
    ElemType *data; // 存储队列元素的数组
    int front;      // 队头指针
    int rear;       // 队尾指针
    int maxSize;    // 队列的最大容量
} LoopQueue;

// 初始化循环队列
// 通常队尾所指向的元素是队列中最后一个元素的**下一个位置**
void InitLoopQueue(LoopQueue &Q, int size) {
    Q.data = new ElemType[size]; // 分配内存
    Q.front = 0;                 // 队头指针初始化为0
    Q.rear = 0;                  // 队尾指针初始化为0
    Q.maxSize = size;            // 设置队列的最大容量
} 

//判断队空   
bool IsEmpty(const LoopQueue &Q) {
    return Q.front == Q.rear;
}


//循环队列判断队满通常采用三种方式
// 1. 使用一个额外的变量来记录队列的大小
// 2. 队尾指针加1后取模，如果等于队头 该方法需要空出一个位置
// 3. 增加tag标志位，区分插入和删除操作，只有在插入时才判断队满

//判断队满
bool IsFull(const LoopQueue &Q) {
    return (Q.rear + 1) % Q.maxSize == Q.front;
}

// 入队操作
bool EnQueue(LoopQueue &Q, ElemType e) {
    if (IsFull(Q)) {
        cerr << "队列已满，无法入队" << endl;
        return false;
    }
    Q.data[Q.rear] = e;        // 将元素插入队尾
    Q.rear = (Q.rear + 1) % Q.maxSize; // 更新队尾指针
    return true;
}
// 出队操作
bool DeQueue(LoopQueue &Q, ElemType &e) {   
    if (IsEmpty(Q)) {
        cerr << "队列为空，无法出队" << endl;
        return false;
    }
    e = Q.data[Q.front];       // 获取队头元素
    Q.front = (Q.front + 1) % Q.maxSize; // 更新队头指针
    return true;
}