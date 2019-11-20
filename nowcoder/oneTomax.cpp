#include <bits/stdc++.h>

using namespace std;

/*
 * 打印 1 到最大的 n 位数
 * 例如：输入 3，打印出 1，2，3，···，999
 * */

class Solution {
public:

    /*
     * 简单的做法，先求出最大的 n 位数
     * 在设定循环打印
     * 此种方法不考虑数的溢出问题
     * */
    static void printOneToMax(int n) {
        int val = 1;
        for (int i = 0; i < n; ++i) {
            val *= 10;
        }
        for (int i = 1; i <= val; ++i) {
            cout << i << " ";
        }
        cout << endl;
    }
    static void func(int n) {
        vector<int> nums(n + 1, 0);
        int index = 1;
        while (nums[0] != 1) {
            inc(nums, index, nums.size());
            print(nums, nums.size());
            // 数组加一
            ++index;
        }
    }
    static void inc(vector<int>& nums, int index, int size) {
        for (int i = size - 1; i >= 0; --i) {
            if (nums[i] + index >= 9) {
                nums[i] = 0;
                nums[i-1] += 1;
            }
        }
    }
    static void print(vector<int>& nums, int size) {
        if (nums.empty()) {
            return ;
        }
        for (int i = 0; i < size; ++i) {
            if (nums[i] != 0) {
                cout << nums[i];
            }
        }
    }
};

void test() {
    Solution::printOneToMax(2);
    Solution::func(2);
}

int main()
{
    test();
    return 0;
}
