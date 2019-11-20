#include <bits/stdc++.h>

using namespace std;

/*
 * 数值的整数次方
 * 实现函数 power 求 base 的 exp 次方
 * */

class Solution {
public:
    static double power(double base, int exp) {
        if (exp == 0) {
            return 1;
        }
        if (exp == 1) {
            return base;
        }

        /*
         * 如果 exp 是偶数，那么 res 表示的是 base^(exp/2)
         * 如果 exp 是奇数，那么 res 表示的是 base^[(exp-1)/2]
         * 
         * 这是由于计算机的向下取整
         * */
        double res = power(base, exp >> 1);
        res *= res;

        // 在这里需要我们自己进行判定 exp 是奇数或偶数
        if ((exp & 1) == 1) {
            res *= base;
        }
        return res;
    }
};

void test() {
    cout << Solution::power(2, 3) << endl;
    cout << Solution::power(0, 0) << endl;
    cout << Solution::power(2, 1) << endl;
}

int main()
{
    test();
    return 0;
}
