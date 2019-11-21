#include <bits/stdc++.h>

using namespace std;

/*
 * 剪绳子
 * 给你一个长度为 n 的绳子，请把绳子剪成 m 段
 * m，n 都是整数，并且 M > 1，每段绳子的长度记为 k[0]，k[1]，等等
 * 请问连续乘积最大是多少
 * 例如：当绳子的长度是 8 时，我们把它剪成长度为 2、3、3 三段，此刻的乘积是 18
 * */

class Solution {
public:
    static int maxlen(int n) {

        // dp[n] 表示把长度为 n 的绳子剪成若干段后，产生的最大乘积
        // 当我们剪第一刀的时候，我们有 n - 1，种选择
        // 并且，剪出来的绳长可能是 1，2，···，n-1 等
        // 因此 dp[n] = dp[i]*dp[n-i]
        vector<int> dp(n + 1, 0);
        dp[0] = 0;
        dp[1] = 1;
        dp[2] = 2;
        dp[3] = 3;
        int global = INT_MIN;
        for (int i = 4; i <= n; ++i) {
            for (int j = 1; j <= i / 2; ++j) {
                dp[i] = dp[j]*dp[i-j];
                global = max(global, dp[i]);
            }
        }
        return global;
    }
};

void test() {
    int n = 8;
    cout << Solution::maxlen(n) << endl;
}

int main()
{
    test();
    return 0;
}
