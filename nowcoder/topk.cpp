#include <bits/stdc++.h>

using namespace std;

/*
 * 最小的 k 个数字
 * 即排序数组的前 k 个数字
 *
 * 输入 n 个整数，找出其中最小的 k 个数，
 * 例如输入 4、5、1、6、2、7、3、8 这 8 个数字，最小的 4 个数
 * 依次为 1、2、3、4
 * */

class Solution {
public:
    static vector<int> topk(vector<int>& nums, int k) {
        vector<int> res;
        if (nums.empty()) {
            return res;
        }
        sort(nums.begin(), nums.end());
        for (int i = 0; i < k; ++i) {
            res.push_back(nums[i]);
        }
        return res;
    }
    static vector<int> topk(vector<int>& nums, int k, int size) {
        vector<int> result;
        if (nums.empty()) {
            return result;
        }
        int left = 0;
        int right = size - 1;
        int index = partition(nums, size, left, right);
        while (index != k) {
            if (index > k - 1) {
                // 左半数组 partition
                right = index - 1;
                index = partition(nums, size, left, right);
            } else {
                // 右半数组 partition
                left = index + 1;
                index = partition(nums, size, left, right);
            }
        }
        for (int i = 0; i < k; ++i) {
            // result[i] = nums[i];
            result.push_back(nums[i]);
        }
        return result;
    }
protected:

    /*
     * partition 思想
     *
     * 如果 index + 1 == k，返回 array[index]
     * 如果 index + 1 > k，对数组左半部分进行 partition
     * 如果 index + 1 < k，对数组右半部分进行 partition
     * */
    static int partition(vector<int>& nums, int size, int start, int end) {
        if (nums.empty() || size <= 0 || start < 0 || end >= size) {
            return -1;
        }
        int index = start;
        swap(nums[index], nums[end]);
        int small = start - 1;
        for (index = start; index < end; ++index) {
            if (nums[index] < nums[end]) {
                ++small;
                if (small != index) {
                    swap(nums[index], nums[small]);
                }
            }
        }
        ++small;
        swap(nums[small], nums[end]);
        return small;
    }

    static int partition(vector<int>& nums, int left, int right) {
        int base = nums[left];
        while (left < right) {
            while (left < right && nums[right] >= base) {
                --right;
            }
            if (left < right) {
                nums[++left] = nums[right];
            }
            while (left < right && nums[left] <= base) {
                ++left;
            }
            if (left < right) {
                nums[--right] = nums[left];
            }
        }
        return left;
    }
};

void test() {
    vector<int> nums {1, 3, 5, 8, 9, 7};
    int k = 5;
    vector<int> tmp = Solution::topk(nums, k);
    vector<int> tmpp = Solution::topk(nums, k, (int)nums.size());
    for (auto& e : tmp) {
        cout << e << " ";
    }
    cout << endl;
    for (auto& e : tmpp) {
        cout << e << " ";
    }
    cout << endl;
}

int main()
{
    test();
    return 0;
}
