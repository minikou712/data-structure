#include <iostream>
using namespace std;

#define MAXSIZE 100

// 共享栈结构定义
typedef struct {
    int data[MAXSIZE];  // 共享存储空间
    int top1;           // S1栈顶指针
    int top2;           // S2栈顶指针
} SharedStack;

// 初始化共享栈
void InitStack(SharedStack &S) {
    S.top1 = -1;         // S1栈顶初始化为-1，从左向右增长
    S.top2 = MAXSIZE;    // S2栈顶初始化为MAXSIZE，从右向左增长
}

// 判断栈满
bool IsStackFull(SharedStack S) {
    return S.top1 + 1 == S.top2;  // 两个栈顶相遇时栈满
}

// S1入栈
bool Push1(SharedStack &S, int x) {
    if (IsStackFull(S)) {
        cout << "栈满，无法入栈" << endl;
        return false;
    }
    S.data[++S.top1] = x;  // S1从左向右增长
    return true;
}

// S2入栈
bool Push2(SharedStack &S, int x) {
    if (IsStackFull(S)) {
        cout << "栈满，无法入栈" << endl;
        return false;
    }
    S.data[--S.top2] = x;  // S2从右向左增长
    return true;
}

// S1出栈
bool Pop1(SharedStack &S, int &x) {
    if (S.top1 == -1) {  // S1栈空
        cout << "S1栈空，无法出栈" << endl;
        return false;
    }
    x = S.data[S.top1--];
    return true;
}

// S2出栈
bool Pop2(SharedStack &S, int &x) {
    if (S.top2 == MAXSIZE) {  // S2栈空
        cout << "S2栈空，无法出栈" << endl;
        return false;
    }
    x = S.data[S.top2++];
    return true;
}

// 获取S1栈顶元素
bool GetTop1(SharedStack S, int &x) {
    if (S.top1 == -1) {
        return false;
    }
    x = S.data[S.top1];
    return true;
}

// 获取S2栈顶元素
bool GetTop2(SharedStack S, int &x) {
    if (S.top2 == MAXSIZE) {
        return false;
    }
    x = S.data[S.top2];
    return true;
}