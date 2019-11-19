#include <bits/stdc++.h>

using namespace std;

/*
 * 数组中的逆序对
 * 在数组中的两个数字，如果前面一个数字大于后面的数字，
 * 则这两个数字组成一个逆序对，输入一个数组，求出这个数
 * 组中的逆序对的总数
 * 例如：给定数组 {7，5，6，4}，一共存在 5 个逆序对，
 * 分别是
 * 7，6，
 * 7，5，
 * 7，4，
 * 6，4，
 * 5，4
 * */

class Solution {
public:
    static int countReverPairs(vector<int>& nums, int size) {
        int count_ = 0;
        if (nums.empty() || size <= 0) {
            return -1;
        }
        for (int i = size - 1; i >= 0; --i) {
            for (int j = i - 1; j >= 0; --j) {
                if (nums[i] < nums[j]) {
                    ++count_;
                }
            }
        }
        return count_;
    }

    /*
     * 暴力穷举，时间复杂度 O(n^2)
     * 不理想
     * */
    static vector<vector<int>> countReverPair(vector<int>& nums, int size) {
        vector<vector<int>> res;
        if (nums.empty() || size <= 0) {
            return res;
        }
        for (int i = size - 1; i >= 0; --i) {
            for (int j = i - 1; j >= 0; --j) {
                if (nums[i] < nums[j]) {
                    res.push_back(vector<int> {nums[j], nums[i]});
                }
            }
        }
        return res;
    }
};

void test() {
    vector<int> nums {7, 5, 6, 4};
    cout << Solution::countReverPairs(nums, nums.size()) << endl;
    vector<vector<int>> res = Solution::countReverPair(nums, nums.size());
    for (size_t i = 0; i < res.size(); ++i) {
        for (size_t j = 0; j < res[0].size(); ++j) {
            cout << res[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    test();
    return 0;
}
