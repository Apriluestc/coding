#include <bits/stdc++.h>

using namespace std;

/*
 * 找出数组中重复的数字
 *
 * 在一个长度为 n 的数组里的所有数字都在 0 ~ n-1 范围内。数组中某些数字
 * 是重复的，但不知道几个数字重复了，也不知道每个数字重复了几次。
 * 请找出数组中任意重复的数字
 * 例如：如果输入长度为 7 的数组 {2, 3, 1, 0, 2, 5, 3}，那么对应输出的
 * 重复数字是 2 或者 3
 * */

class Solution {
public:
    static bool duplicate(vector<int>& nums, int size, int& duplicates) {
        if (nums.empty()) {
            return false;
        }
        for (int i = 0; i < size; ++i) {
            if (nums[i] < 0 || nums[i] > size - 1) {
                return false;
            }
        }
        /*
         * 扫描整个数组，当我们扫描到下标为 i 的元素 m 时，首先比较
         * 这个数字 m 是否等于 i，如果是继续扫描，否则把 m 拿去与下
         * 标为 m 的数字比较，如果相等，则找到重复数字，如果不相等，则
         * 把 m 放到属于它的位置
         * */
        for (int i = 0; i < size; ++i) {
            while (nums[i] != i) {
                if (nums[i] == nums[nums[i]]) {
                    duplicates = nums[i];
                    return true;
                }
                swap(nums[i], nums[nums[i]]);
            }
        }
        return false;
    }

    /*
     * 哈希表解法 : 时间复杂度，空间复杂度均为 O(n)
     * */
    static bool duplicateHashMap(vector<int>& nums, int size, int& duplicates) {
        if (nums.empty()) {
            return false;
        }
        for (int i = 0; i < size; ++i) {
            if (nums[i] < 0 || nums[i] > size - 1) {
                return false;
            }
        }
        unordered_map<int, int> hashmap;
        for (int i = 0; i < size; ++i) {
            hashmap[nums[i]]++;
        }
        for (int i = 0; i < size; ++i) {
            if (hashmap[nums[i]]) {
                duplicates = nums[i];
                return true;
            }
        }
        return false;
    }

    /*
     * 不修改数组找出重复数字
     *
     * 可以把 1 ~ n 的数字从中间的数字 m 划分为 1 ~ m 和 m+1 ~ n 两部分
     * 如果说，这 1 ~ m 区间的数字个数超过 m 那么就一定有重复数字出现在前半区间
     * ···
     * */
    static int duplicate(const vector<int>& nums, int size) {
        if (nums.empty()) {
            return false;
        }
        for (int i = 0; i < size; ++i) {
            if (nums[i] < 0 || nums[i] > size - 1) {
                return false;
            }
        }

        // [left, right] 区间上下限
        int left = 1;
        int right = size - 1;
        while (left <= right) {
            int mid = left + ((right - left) >> 1);
            int count_ = countRange(nums, size, left, mid);
            if (left == right) {
                if (count_ > 1) {
                    return left;
                } else {
                    break;
                }
            }
            if (count_ > (mid - left + 1)) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return -1;
    }
protected:

    /*
     * 统计区间内满足条件数字个数
     * */
    static int countRange(const vector<int>& nums, int size, int left, int right) {
        if (nums.empty()) {
            return 0;
        }
        int count_ = 0;
        for (int i = 0; i < size; i++) {
            if (nums[i] >= left && nums[i] <= right) {
                ++count_;
            }
        }
        return count_;
    }
};

void test1() {
    const vector<int> numbers {2, 1, 3, 1, 4};
    int size = numbers.size();
    int duplicates = 0;
    duplicates = Solution::duplicate(numbers, size);
    cout << "repeating number : " << duplicates << endl;
}

void test2() {
    vector<int> numbers {2, 1, 3, 1, 4};
    int size = numbers.size();
    int duplicates = 0;
    if (Solution::duplicate(numbers, size, duplicates)) {
        cout << "repeating number : " << duplicates << endl;
    } else {
        cout << "not exist!" << endl;
    }
}

int main()
{
    test1();
    test2();
    return 0;
}
