#include <bits/stdc++.h>

using namespace std;

/*
 * 礼物的最大价值
 * 在一格 m*n 的棋盘的每一格都放有一个礼物，每个礼物都有一定的价值
 * 你可以从棋盘的左上角开始拿格子里的礼物，并每次向左或向下移动一格
 * 直到到达棋盘的右下角
 *
 * 给定一个棋盘及其上面的礼物，请计算你最多能拿到多少价值的礼物
 * */


/*
 * 简单的动态规划题目
 * */
class Solution {
public:
    static int maxVal(vector<vector<int>>& matrix) {
        if (matrix.empty()) {
            return -1;
        }
        int global = INT_MIN;
        vector<vector<int>> dp(matrix.size(), vector<int>(matrix[0].size(), 0));
        
        // 初始化 dp[0][0]
        dp[0][0] = matrix[0][0];

        // 初始化 dp 数组第一列
        for (size_t i = 1; i < matrix.size(); ++i) {
            dp[i][0] = dp[i-1][0] + matrix[i][0];
        }

        // 初始化 dp 数组第一行
        for (size_t j = 1; j < matrix[0].size(); ++j) {
            dp[0][j] = dp[0][j-1] + matrix[0][j];
        }
        for (size_t i = 1; i < matrix.size(); ++i) {
            for (size_t j = 1; j < matrix[0].size(); ++j) {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]) + matrix[i][j];
                global = max(global, dp[i][j]);
            }
        }
        return global;
    }
};

void test() {
    vector<vector<int>> matrix {
        {1, 10, 3, 8}, 
        {12, 2, 9, 6}, 
        {5, 7, 4, 11}, 
        {3, 7, 16, 5}
    };
    cout << Solution::maxVal(matrix) << endl;
}

int main()
{
    test();
    return 0;
}
