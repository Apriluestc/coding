#include <bits/stdc++.h>

using namespace std;

/*
 * 打印 1 到最大的 n 位数
 * 例如：输入 3，打印出 1，2，3，···，999
 * */

class Solution {
public:

    /*
     * 简单的做法，先求出最大的 n 位数
     * 在设定循环打印
     * */
    static void printOneToMax(int n) {
        int max_ = 10 * (n + 1) - 1;
        for (int i = 0; i < max_; ++i) {
            cout << i << " ";
        }
        cout << endl;
    }

    static void print(int n);
};

void test() {
    Solution::printOneToMax(5);
    Solution::printOneToMax(10);
    Solution::printOneToMax(99);
    Solution::printOneToMax(30);
    Solution::printOneToMax(100);
}

int main()
{
    test();
    return 0;
}
