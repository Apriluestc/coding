#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    static vector<int> twoSum(vector<int>& nums, int size, int target) {
        if (nums.empty() || size <= 0) {
            return vector<int> {};
        }
        unordered_map<int, int> hashmap;
        for (int i = 0; i < size; ++i) {
            // A + B = X
            // A = X - B
            // 如果登记了直接输出
            // 否则重新登记
            if (hashmap.count(nums[i]) != 0) {
                return vector<int> {nums[i], hashmap[nums[i]]};
            } else {
                hashmap[target - nums[i]] = nums[i];
            }
        }
        return vector<int> {};
    }
    static vector<int> twoSum(vector<int>& nums, int target) {
        if (nums.empty()) {
            return vector<int> {};
        }
        int left = 0;
        int right = nums.size() - 1;
        while (left < right) {
            if (nums[left] + nums[right] == target) {
                return vector<int> {nums[left], nums[right]};
            } else if (nums[left] + nums[right] < target) {
                ++left;
            } else {
                --right;
            }
        }
        return vector<int> {};
    }
};

/*
 * hashmap.count(val) 只返回集合当中有没有该元素
 * 而不是返回元素出现次数
 * */

void test() {
    vector<int> nums {1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 1, 2, 3};
    int target = 11;
    vector<int> res = Solution::twoSum(nums, target);
    vector<int> res1 = Solution::twoSum(nums, nums.size(), target);
    cout << res[0] << " " << res[1] << endl;
    cout << res1[0] << " " << res1[1] << endl;
    unordered_map<int, int> hashmap;
    for (size_t i = 0; i < nums.size(); ++i) {
        ++hashmap[nums[i]];
    }
    cout << hashmap.count(1) << endl;
    cout << hashmap.count(3) << endl;
    cout << hashmap.count(2) << endl;
    cout << hashmap.count(9) << endl;
    cout << hashmap.count(0) << endl;
}

int main()
{
    test();
    return 0;
}
