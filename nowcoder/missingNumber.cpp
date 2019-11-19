#include <bits/stdc++.h>

using namespace std;

/*
 * 0 ~ n-1 中缺失的数字
 * 一个长度为 n-1 的递增排序数组中所有数字都是唯一的，
 * 并且每个数字都是 0 ~ n-1 范围内，在这个范围内只有一
 * 个数字不在这个范围内，要求找出这个数字
 * */

/*
 * 二分查找思想
 *
 * 注意 : start 和 end 分别为 0 和 size
 * 判断条件为 start <= end*/

class Solution {
public:
    static int missingNumber(vector<int>& nums) {
        if (nums.empty()) {
            return -1;
        }
        int start = 0;
        int end = nums.size();
        while (start <= end) {
            int mid = start + ((end - start) >> 1);

            // 找到第一个值与下标不对应的下标返回
            if (nums[mid] != mid) {
                if ((nums[mid-1] == mid - 1 && mid > 0) || mid == 0) {
                    return mid;
                }
                end = mid - 1;
            } else {
                start = mid + 1;
            }
        }
        int size = nums.size();
        if (start == size) {
            return size;
        }
        return -1;
    }
    static int misssingNumber(vector<int>& nums, int size) {
        if (nums.empty() || size <= 0) {
            return -1;
        }
        return size * (size + 1) / 2 - Sum(nums, size);
    }
protected:
    static int Sum(vector<int>& nums, int size) {
        if (nums.empty() || size <= 0) {
            return -1;
        }
        int sum_ = 0;
        for (int i = 0; i < size; ++i) {
            sum_ += nums[i];
        }
        return sum_;
    }
};

void test() {
    vector<int> nums {0, 1, 2, 4, 5};
    cout << Solution::misssingNumber(nums, nums.size()) << endl;
    cout << Solution::missingNumber(nums) << endl;
}

int main()
{
    test();
    return 0;
}
