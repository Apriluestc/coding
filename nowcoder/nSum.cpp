#include <bits/stdc++.h>

using namespace std;

/*
 * 求 1 + 2 + 3 + ··· + n 的和
 * 要求不能使用乘除法、循环、if 等语句
 * */

/*
 * 根据循环做文章
 * 让相同的代码块重复执行即可
 * */
class Inc {
public:

    /*
     * 调用一次构造函数相当于执行一次循环
     * */
    Inc() {
        ++n;
        sum += n;
    }
    static void reset() {
        n = 0;
        sum = 0;
    }
    static int getsum() {
        return sum;
    }
private:
    static int n;
    static int sum;
};

int Inc::n;
int Inc::sum;

int nsum(int n) {
    Inc::reset();
    Inc array[n];
    return Inc::getsum();
}

class A {
public:
    virtual int func(int) {
        return 0;
    }
    static A* array[2];
};

A* A::array[2];

class B : public A {
public:
    int func(int n) {
        return array[!!n]->func(n-1) + n;
    }
};

int sum(int n) {
    A a;
    B b;
    A::array[0] = &a;
    A::array[1] = &b;
    int val = A::array[1]->func(n);
    return val;
}

void test() {
    int n = 10;
    cout << nsum(n) << endl;
    cout << sum(n) << endl;
}

int main()
{
    test();
    return 0;
}
