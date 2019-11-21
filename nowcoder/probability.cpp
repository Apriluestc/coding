#include <bits/stdc++.h>

using namespace std;

/*
 * n 骰子的点数
 * 求出每个可能值的概率
 * */

class Solution {
public:
    static void print(int numbers) {
        vector<int> nums(6 * numbers - numbers + 1, 0);
        int total = pow(6.0, numbers);
        print(numbers, numbers, 1, nums);
        for (int i = numbers; i < 6 * numbers + 1; ++i) {
            cout << nums[i-numbers] / total << " ";
        }
    }
    static void print(int numbers, int current, int sum, vector<int>& nums) {
        for (int i = numbers; i < 6 * numbers + 1; ++i) {
            if (current == 1) {
                nums[i-numbers]++;
            } else {
                for (int i = 1; i <= 6; ++i) {
                    print(numbers, current - 1, i + sum, nums);
                }
            }
        }
    }
};

void test() {}

int main()
{
    test();
    return 0;
}
