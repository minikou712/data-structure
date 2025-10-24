
// 模拟后缀表达式程序
#include <iostream>
#include "stack.h"
#include <stack>
#include <cmath> // for pow function
using namespace std;

// 模拟运算优先级
int Precedence(char op)
{
    switch (op)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    default:
        return 0; // 非运算符
    }
}

// 将给出的中缀表达式转换为后缀表达式
// 实现原理
//  1.使用栈来存储运算符和括号
//  2.遍历中缀表达式中的每个字符
//  3.如果是操作数，直接加入后缀表达式
//  4.如果是左括号，入栈
//  5.如果是右括号，出栈到左括号
//  6.如果是运算符，出栈所有优先级大于等于当前运算符的运算符，直到遇到左括号或栈空，然后将当前运算符入栈
//  7.最后将栈中剩余的运算符全部出栈
void InfixToPostfix(const string &infix, string &postfix)
{                // infix为中缀表达式，postfix为后缀表达式
    CharStack S; // 存储运算符和括号的栈
    InitStack(S, infix.length());
    for (char c : infix)
    {
        if (isdigit(c))
        { // 如果是操作数，直接加入后缀表达式
            postfix += c;
        }
        else if (c == '(')
        { // 如果是左括号，入栈
            Push(S, c);
        }
        else if (c == ')')
        { // 如果是右括号，出栈到左括号
            char top;
            while (Pop(S, top) && top != '(')
            {
                postfix += top;
            }
        }
        else
        { // 如果是运算符
            char top;
            while (Pop(S, top) && Precedence(top) >= Precedence(c))
            { // 出栈所有优先级大于等于当前运算符的运算符
                if (top == '(')
                {                 // 如果遇到左括号，停止出栈
                    Push(S, top); // 将左括号重新入栈
                    break;
                }
                postfix += top;
            }
            Push(S, c);
        }
    }
    // 将栈中剩余的运算符全部出栈
    char top;
    while (Pop(S, top))
    {
        postfix += top;
    }
    DestroyStack(S);
}

// 后缀表达式求值
// 实现原理
//  1.使用栈来存储操作数
//  2.遍历后缀表达式中的每个字符
//  3.如果是操作数，入栈
//  4.如果是运算符，出栈两个操作数进行运算，将结果入栈
int EvaluatePostfix(const string &postfix)
{
    stack<int> S; // 存储操作数的栈
    for (char c : postfix)
    {
        if (isdigit(c))
        {                    // 如果是操作数，入栈
            S.push(c - '0'); // 将字符转换为整数
        }
        else
        { // 如果是运算符
            int b = S.top();
            S.pop(); // 出栈两个操作数
            int a = S.top();
            S.pop();
            switch (c)
            {
            case '+':
                S.push(a + b);
                break;
            case '-':
                S.push(a - b);
                break;
            case '*':
                S.push(a * b);
                break;
            case '/':
                if (b == 0)
                {
                    cerr << "除数不能为零" << endl;
                    return 0; // 错误处理
                }
                S.push(a / b);
                break;
            case '^':
                S.push(pow(a, b));
                break;
            }
        }
    }
    return S.top(); // 返回栈顶元素，即最终结果
}


