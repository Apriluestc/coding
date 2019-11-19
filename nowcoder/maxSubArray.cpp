#include <bits/stdc++.h>

using namespace std;

/*
 * 连续子数组的最大和
 * 输入一个整形数组，数组中有正数也有负数，数组中的一个或者连
 * 续多个数组成一个子数组，求所有子数组的和的最大值
 * */

class Solution {
public:
    static int subArray(vector<int>& nums, int size) {
        if (nums.empty()) {
            return -1;
        }
        vector<int> dp(size, 0);
        int global = INT_MIN;
        for (int i = 0; i < size; i++) {
            dp[i] = max(dp[i-1] + nums[i], nums[i]);
            global = max(global, dp[i]);
        }
        return global;
    }
    static int subArray(vector<int>& nums) {
        int size = nums.size();
        if (nums.empty()) {
            return -1;
        }
        
        // curSum 记录临时最大和
        int curSum = 0;

        // 全局最优解
        int global = INT_MIN;
        for (int i = 0; i < size; ++i) {
            // 临时最大和小于等于 0，将之前数字摒弃
            if (curSum <= 0) {
                curSum = nums[i];
            } else {
                curSum += nums[i];
            }
            global = max(global, curSum);
        }
        return global;
    }
};

void test() {
    vector<int> nums {1, 2, -3, 5, -6, 5, 7};
    // 1, 2, -3, 5, -6, 5, 7
    // 1, 3, 0, 5, -1, 5, 12
    cout << Solution::subArray(nums, nums.size()) << endl;
    cout << Solution::subArray(nums) << endl;
}

int main()
{
    test();
    return 0;
}
