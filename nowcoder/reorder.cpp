#include <bits/stdc++.h>

using namespace std;

/*
 * 调整数组中奇数位于偶数前面
 *
 * 输入一个整数数组，实现一个函数来调整该数组内的数字顺序，
 * 使得奇数位于数组的前半部分，偶数位于数组的后半部分
 * */

class Solution {
public:
    static void reorder(vector<int>& nums, int size) {
        if (nums.empty()) {
            return ;
        }
        int left = 0;
        int right = size - 1;
        while (left < right) {
            while (left < right && nums[left] % 2 == 1) {
                ++left;
            }
            while (left < right && nums[right] % 2 == 0) {
                --right;
            }
            if (left < right) {
                swap(nums[left], nums[right]);
            }
        }
    }

    static void reorder(vector<int>& nums, int size, bool (*CallBack)(int)) {
        if (nums.empty()) {
            return ;
        }
        int left = 0;
        int right = size - 1;
        while (left < right) {
            while (left < right && !CallBack(nums[left])) {
                ++left;
            }
            while (left < right && CallBack(nums[right])) {
                --right;
            }
            if (left < right) {
                swap(nums[left], nums[right]);
            }
        }
    }
protected:
    bool iseven(int n) {
        return (n & 1) == 0;
    }
};

void test() {
    vector<int> nums {1, 2, 4, 5, 6, 7, 9, 0};
    Solution::reorder(nums, nums.size());
    for (auto& e : nums) {
        cout << e << " ";
    }
    cout << endl;
}

int main()
{
    test();
    return 0;
}
