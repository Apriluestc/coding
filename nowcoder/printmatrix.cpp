#include <bits/stdc++.h>

using namespace std;

/*
 * 顺时针打印矩阵
 *
 * 输入一个矩阵，按照从外向里顺时针一次打印每一个数字
 * */

class Solution {
public:
    static void print(vector<vector<int>>& nums, int rows, int cols) {
        if (nums.empty()) {
            return ;
        }
        int start = 0;
        while (rows > start * 2 && cols > start * 2) {
            print(nums, rows, cols, start);
            ++start;
        }
        cout << endl;
    }
protected:

    /*
     * 仅仅打印一圈的功能
     * */
    static void print(vector<vector<int>>& nums, int rows, int cols, int start) {
        if (nums.empty()) {
            return ;
        }
        int endX = cols - start - 1;
        int endY = rows - start - 1;

        // 从左往右打印
        for (int i = start; i <= endX; ++i) {
            cout << nums[start][i] << " ";
        }

        // 从上往下打印
        if (start < endY) {
            for (int i = start + 1; i <= endY; ++i) {
                cout << nums[i][endX] << " ";
            }
        }

        // 从右往左打印
        if (start < endX && start < endY) {
            for (int i = endX - 1; i >= start; --i) {
                cout << nums[endY][i] << " ";
            }
        }

        // 从下往上打印
        if (start < endX && start < endY - 1) {
            for (int i = endY - 1; i >= start + 1; --i) {
                cout << nums[i][start] << " ";
            }
        }
    }
};

void test() {
    vector<vector<int>> nums {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int rows = nums.size();
    int cols = nums[0].size();
    Solution::print(nums, rows, cols);
}

int main()
{
    test();
    return 0;
}
