#include <bits/stdc++.h>

using namespace std;

/*
 * 不用加减乘除做加法
 * 写一个函数，求两个整数的和，要求不能使用加减乘除
 * */

class Solution {
public:

    /*
     * 分析十进制整数可知
     * 15 + 5 = 20
     * 分三步：各位相加，进位计算，把前两者加起来
     * 
     *
     * 异或得到的是不计进位所得的结果
     * 与运算再左移得到的是进位
     * 两者相加即可
     * */
    static int add(int left, int right) {
        int sum = 0;
        int carry = 0;
        while (right) {
            sum = left ^ right;

            // 进位
            carry = (left & right) << 1;

            // 迭代，直到不存在进位
            left = sum;
            right = carry;
        }
        return sum;
    }
};

void test() {
    cout << Solution::add(1, 2) << endl;
    cout << Solution::add(10, 2) << endl;
    cout << Solution::add(3, 2) << endl;
}

int main()
{
    test();
    return 0;
}
