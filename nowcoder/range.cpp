#include <bits/stdc++.h>

using namespace std;

/*
 * 机器人的运动范围
 * 地上有一个 m 行 n 列的矩阵，一个机器人从坐标
 * 0，0 的位置开始移动，它每次可以向上下左右任一个方
 * 向移动一格，但不能进入行坐标和列坐标数位之和大于 k 的数字
 * 例如：坐标 35，37 因为 3 + 5 + 7 + 3 = 18，因此可以进入该坐标
 * 但是对于 35，38 就不可以，请问机器人能够到达多少个格子
 * */

class Solution {
public:
    static int count(vector<vector<int>>& matrix, int val) {
        if (matrix.empty()) {
            return false;
        }
        int ROW = matrix.size();
        int COL = matrix[0].size();
        vector<vector<bool>> visited(ROW, vector<bool>(COL, 0));
        return count(matrix, visited, ROW, COL, 0, 0, val);
    }
    static int count(vector<vector<int>>& matrix, vector<vector<bool>>& visited, int ROW, int COL, int row, int col, int val) {
        int count_ = 0;
        if (check(matrix, visited, ROW, COL, row, col, val)) {
            visited[row][col] = true;
            count_ = 1 + count(matrix, visited, ROW, COL, row - 1, col, val) + 
                count(matrix, visited, ROW, COL, row + 1, col, val) + 
                count(matrix, visited, ROW, COL, row, col - 1, val) + 
                count(matrix, visited, ROW, COL, row, col + 1, val);
        }
        return count_;
    }

    /*
     * check 用来判断该座标是否可以进入
     * */
    static bool check(vector<vector<int>>& matrix, vector<vector<bool>>& visited, int ROW, int COL, int row, int col, int val) {
        if (matrix.empty()) {
            return false;
        }
        if (row >= 0 && row < ROW && col >= 0 && col < COL && 
            !visited[row][col] && sumXY(row, col) <= val) {
            return true;
        }
        return false;
    }

    /*
     * 计算数位和
     * */
    static int sumXY(int X, int Y) {
        int sumX = 0;
        int sumY = 0;
        while (X) {
            sumX += (X % 10);
            X /= 10;
        }
        while (Y) {
            sumY += (Y % 10);
            Y /= 10;
        }
        return sumX + sumY;
    }
};

void test() {
    vector<vector<int>> matrix {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int val = 4;
    cout << Solution::count(matrix, val) << endl;
}

int main()
{
    test();
    return 0;
}
