#include <bits/stdc++.h>

using namespace std;

/*
 * 把数组排列成最小的数
 * 输入一个正整数数组，把数组里所有的数字拼接起来排成一个数，
 * 打印能拼接成所有数字中最小的那一个
 * 例如：输入数字 {3，32，321}，则打印最小的数字为 321323
 * */

/*
 * string API
 *
 * strcat、strcmp、to_string、strcpy、c_str、itoa、atoi、
 * to_string(10)、atoi(str.c_str)
 * */

class Solution {
public:
    static string minNumber(vector<int>& nums, int size) {
        if (nums.empty() || size <= 0) {
            return "";
        }
        sort(nums.begin(), nums.end(), cmp);
        string s;
        for (int i = 0; i < size; ++i) {
            s += to_string(nums[i]);
        }
        return s;
    }
    static bool cmp(int left, int right) {
        string A = to_string(left) + to_string(right);
        string B = to_string(right) + to_string(left);
        return A < B;
    }
};

void test() {
    vector<int> nums {3, 32, 321};
    cout << Solution::minNumber(nums, nums.size()) << endl;
}

int main()
{
    test();
    return 0;
}
