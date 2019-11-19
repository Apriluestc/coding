#include <bits/stdc++.h>

using namespace std;

/*
 * 数组中出现次数超过一般的数字
 *
 * 给定一个数字，输出出现次数超过数组长度一般的元素
 * */

class Solution {
public:

    /*
     * 简单做法 : 散列表统计元素出现次数，将次数满足条件的输出
     * */
    static int moreThanHalf(vector<int>& nums, int size) {
        if (nums.empty()) {
            return -1;
        }
        unordered_map<int, int> hashmap;
        for (int i = 0; i < size; ++i) {
            ++hashmap[nums[i]];
        }
        for (int i = 0; i < size; ++i) {
            if (hashmap[nums[i]] >= (size + 1) / 2) {
                return nums[i];
            }
        }
        return -1;
    }

    /*
     * 根据数组的特性，我们在遍历数组的时候，需要保存两个值
     * 一是数组中的某一个数字，另一个是次数
     * 当前仅当我们遍历到下一个元素的时候，如果下一个元素与我
     * 们刚才保存的值相等，那么次数加 1，否则次数减 1
     * 由于我们所要求的数字出现的次数大于数组长度的一半
     * 要找的数字肯定是最后一次把次数设定为 1 时对应的数字
     * */
    static int moreThanHalf(vector<int>& nums) {
        if (nums.empty()) {
            return -1;
        }
        int count_ = 1;
        int result = nums[0];
        for (size_t i = 1; i < nums.size(); ++i) {
            if (count_ == 0) {
                result = nums[i];
                count_ = 1;
            } else if (nums[i] == result) {
                ++count_;
            } else {
                --count_;
            }
        }
        if (checkMoreThanHalf(nums, nums.size(), result)) {
            return result;
        } else {
            return -1;
        }
    }
    
#if 0
    /*
     * 排序，输出中位数
     * */
    static int moreThanHalf(vector<int>& nums) {
        if (nums.empty()) {
            return -1;
        }
        sort(nums.begin(), nums.end());
        if ((nums.size() & 1) == 0) {
            return nums[nums.size() / 2 - 1];
        } else {
            return nums[nums.size() / 2];
        }
    }

#endif

protected:
    static bool checkMoreThanHalf(vector<int>& nums, int size, int number) {
        if (nums.empty()) {
            return false;
        }
        int count_ = 0;
        for (int i = 0; i < size; ++i) {
            if (nums[i] == number) {
                ++count_;
            }
        }
        if (count_ * 2 >= size) {
            return true;
        }
        return false;
    }
};

void test1() {
    vector<int> nums {1, 2, 1, 2, 1};
    cout << Solution::moreThanHalf(nums, nums.size()) << endl;
    cout << Solution::moreThanHalf(nums) << endl;
}

void test2() {
    vector<int> nums {1, 2, 1, 1, 1, 3, 4, 5, 6};
    cout << Solution::moreThanHalf(nums, nums.size()) << endl;
}

int main()
{
    test1();
    test2();
    return 0;
}
