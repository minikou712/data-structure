//根据题目要求，需要利用两个栈 S1 和 S2 来模拟队列的操作。#include <iostream>
#include <stack>
using namespace std;

// 利用两个栈模拟队列的三个操作
stack<int> S1, S2;  // S1用于入队，S2用于出队

// 入队操作
void Enqueue(int x) {
    S1.push(x);
}

// 出队操作
bool Dequeue(int &x) {
    if (S2.empty()) {
        if (S1.empty()) return false;  // 队列为空
        // 将S1所有元素转移到S2
        while (!S1.empty()) {
            S2.push(S1.top());
            S1.pop();
        }
    }
    x = S2.top();
    S2.pop();
    return true;
}

// 判断队列是否为空
bool QueueEmpty() {
    return S1.empty() && S2.empty();
}