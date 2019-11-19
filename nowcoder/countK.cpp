#include <bits/stdc++.h>

using namespace std;

/*
 * 统计排序数组中数字出现的次数，找到初始位置即可，
 * 二分查找
 * 排序数组中查找数字
 * 统计一个数字在排序数组中出现的次数，
 * 例如：输入数组 {1，2，3，3，3，3，4，5}，和数字 3，由于
 * 3 在数组中出现次数为 4，则输出 4
 * */

/*
 * 利用二分查找的特性
 * 分别找到第一个出现的位置和最后一次出现的位置
 * 统计出现次数
 * */
class Solution {
public:
    static int countK(vector<int>& nums, int size, int target) {
        if (nums.empty()) {
            return -1;
        }
        int first = getFirstK(nums, nums.size(), 0, size, target);
        int last = getLastK(nums, nums.size(), 0, size, target);
        return last - first + 1;
    }
protected:
    static int getFirstK(vector<int>& nums, int size, int start, int end, int target) {
        if (nums.empty() || start > end || size <= 0) {
            return -1;
        }
        int mid = start + ((end - start) >> 1);
        if (nums[mid] == target) {
            if ((nums[mid-1] != target && mid > 0) || mid == 0) {
                return mid;
            } else {
                end = mid - 1;
            }
        } else if (nums[mid] < target) {
            start = mid + 1;
        } else {
            end = mid - 1;
        }
        return getFirstK(nums, size, start, end, target);
    }
    static int getLastK(vector<int>& nums, int size, int start, int end, int target) {
        if (nums.empty() || size <= 0 || start > end) {
            return -1;
        }
        int mid = start + ((end - start) >> 1);
        if (nums[mid] == target) {
            if ((nums[mid+1] != target && mid < size - 1) || mid == size - 1) {
                return mid;
            } else {
                start = mid + 1;
            }
        } else if (nums[mid] < target) {
            start = mid + 1;
        } else {
            end = mid - 1;
        }
        return getLastK(nums, size, start, end, target);
    }
};

void test() {
    vector<int> nums {1, 2, 3, 3, 3, 3, 4, 6};
    int target = 3;
    cout << Solution::countK(nums, nums.size(), target) << endl;
}

#if 0

void testIndex() {
    vector<int> nums {1, 2, 3, 3, 3, 3, 4, 6};
    int target = 3;
    int first = Solution::getFirstK(nums, nums.size(), 0, nums.size() - 1, target);
    int last = Solution::getLastK(nums, nums.size(), 0, nums.size() - 1, target);
    cout << "first : " << first << endl;
    cout << "last : " << last << endl;
}

#endif

int main()
{
    test();
    // testIndex();
    return 0;
}
