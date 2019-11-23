#include <bits/stdc++.h>

using namespace std;

/*
 * 两个队列实现栈
 * */

/*
 * 栈的成员函数详解
 *
 * void push(const value_type& val);
 * void pop()
 * value_type& top();
 * */

/*
 * 队列成员函数详解
 *
 * void push(const value_type& val);
 * void pop()
 * value_type& front();
 * value_type& back();
 * */

template<typename T>
class Stack {
public:
    void push(const T& x) {
        q1.push(x);
    }
    T pop();
private:
    static queue<T> q1;
    static queue<T> q2;
};

int main()
{
    return 0;
}
