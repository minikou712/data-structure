//定义栈的头文件  
#ifndef STACK_H
#define STACK_H
#include <iostream>
using namespace std;
typedef char ElemType;

//动态栈
typedef struct {
    ElemType *data; // 存储栈元素的数组
    int top;        // 栈顶指针
    int maxSize;   // 栈的最大容量
} CharStack;

// 初始化栈
void InitStack(CharStack &S, int size) {
    S.data = new ElemType[size]; // 分配内存
    S.top = -1;                  // 栈顶指针初始化为-1，表示栈为空
    S.maxSize = size;            // 设置栈的最大容量
}
// 判断栈是否为空
bool IsEmpty(const CharStack &S) {
    return S.top == -1; // 栈顶指针为-1表示栈为空
}

// 判断栈是否已满
bool IsFull(const CharStack &S) {
    return S.top == S.maxSize - 1; // 栈顶指针等于最大容量-1表示栈已满
}

// 入栈操作
bool Push(CharStack &S, ElemType e) {
    if (IsFull(S)) {
        cerr << "栈已满，无法入栈" << endl;
        return false;
    }
    S.data[++S.top] = e; // 将元素压入栈顶
    return true;
}

// 出栈操作
bool Pop(CharStack &S, ElemType &e) {
    if (IsEmpty(S)) {
        cerr << "栈为空，无法出栈" << endl;
        return false;
    }
    e = S.data[S.top--]; // 将栈顶元素弹出并返回
    return true;
}
// 获取栈顶元素
bool GetTop(const CharStack &S, ElemType &e) {
    if (IsEmpty(S)) {
        cerr << "栈为空，无法获取栈顶元素" << endl;
        return false;
    }
    e = S.data[S.top]; // 返回栈顶元素
    return true;
} 
// 销毁栈  要释放栈的内存
void DestroyStack(CharStack &S) {
    delete[] S.data; // 释放栈的内存
    S.top = -1;      // 重置栈顶指针
    S.maxSize = 0;   // 重置栈的最大容量
}
// 清空栈  只需将栈顶指针重置为-1即可
void ClearStack(CharStack &S) {
    S.top = -1; // 重置栈顶指针，清空栈
}   

#endif // STACK_H
// xunh --- IGNORE ---