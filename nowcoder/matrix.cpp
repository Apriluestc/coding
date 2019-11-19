#include <bits/stdc++.h>

using namespace std;

/*
 * 二维数组的查找
 * 在一个二维数组中，每一行都是按照从左至右递增的顺序排序，
 * 每一列都是按照从上到下递增的顺序排列，请完成一个函数，输入这样的一
 * 个数组，判断数组中是否有这样的数字
 * */

class Solution {
public:

    /*
     * 根据数组特点求解
     * 从右上角开始查找
     * */
    static bool find(const vector<vector<int>>& matrix, int target) {
        if (matrix.empty()) {
            return false;
        }
        int ROW = matrix.size();
        int COL = matrix[0].size();
        int row = 0;
        int col = COL - 1;
        while (row < ROW && col >= 0) {
            if (matrix[row][col] == target) {
                return true;
            } else if (matrix[row][col] < target) {
                ++row;
            } else {
                --col;
            }
        }
        return false;
    }

    /*
     * 根据数组特性每一行都可用二分查找
     * 总时间复杂度O(nlog(n))
     * */
    static bool find(const vector<vector<int>>& matrix, int size, int target) {
        if (matrix.empty()) {
            return false;
        }
        for (int i = 0; i < size; ++i) {
            if (binarySearch(matrix[i], size, target)) {
                return true;
            }
        }
        return false;
    }
protected:

    /*
     * 二分查找时间复杂度 O(logn)
     * 注意二分查找：left、right 分别为 0 和 size
     * */
    static bool binarySearch(const vector<int>& nums, int size, int target) {
        if (nums.empty()) {
            return false;
        }
        int left = 0;
        int right = size;
        while (left <= right) {
            int mid = left + ((right - left) >> 1);
            if (nums[mid] == target) {
                return true;
            } else if (nums[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return false;
    }
};

void test1() {
    const vector<vector<int>> matrix {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    if (Solution::find(matrix, 5)) {
        cout << "true" << endl;
    } else {
        cout << "false" << endl;
    }
}

void test2() {
    const vector<vector<int>> matrix {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    if (Solution::find(matrix, matrix.size(), 5)) {
        cout << "true" << endl;
    } else {
        cout << "false" << endl;
    }
}

int main()
{
    test1();
    test2();
    return 0;
}
