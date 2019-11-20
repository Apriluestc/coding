#include <bits/stdc++.h>

using namespace std;

/*
 * 二进制中 1 的个数
 * 给定一个二进制数，求出该数二进制中含 1 的个数
 * */

class Solution {
public:

    /*
     * 按位与运算求数的二进制中一的个数
     * */
    static int numberOf1(int n) {
        int count_ = 0;
        while (n) {
            if ((n & 1) == 1) {
                ++count_;
            }
            n = n >> 1;
        }
        return count_;
    }
};

void test() {
    int n = 5;
    cout << "5 : " << Solution::numberOf1(n) << endl;
    cout << "1 : " << Solution::numberOf1(1) << endl;
    cout << "3 : " << Solution::numberOf1(3) << endl;
}

int main()
{
    test();
    return 0;
}
