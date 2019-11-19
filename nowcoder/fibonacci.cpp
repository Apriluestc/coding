#include <bits/stdc++.h>

using namespace std;

/*
 * 斐波那契数列
 *
 * 0、1、1、2、3、5、···、
 * */

class Solution {
public:
    static int fibonacci(unsigned int n) {
        if (n == 0) {
            return 0;
        } else if (n == 1) {
            return 1;
        } else {
            return fibonacci(n-1) + fibonacci(n-2);
        }
    }
    static int fibonacciDp(unsigned int n) {
        vector<int> dp(n + 1, 0);
        dp[1] = 1;
        for (unsigned int i = 2; i <= n; ++i) {
            dp[i] = dp[i-1] + dp[i-2];
        }
        return dp[n];
    }
    static int fibonacciW(unsigned int n) {
        int first = 0;
        int second = 1;
        int res;
        for (unsigned int i = 2; i <= n; ++i) {
            res = first + second;
            first = second;
            second = res;
        }
        return res;
    }
};

void test1() {
    unsigned int n = 6;
    cout << Solution::fibonacci(n) << endl;
}

void test2() {
    unsigned int n = 6;
    cout << Solution::fibonacciDp(n) << endl;
}

void test3() {
    unsigned int n = 6;
    cout << Solution::fibonacciW(n) << endl;
}

int main()
{
    test1();
    test2();
    test3();
    return 0;
}
