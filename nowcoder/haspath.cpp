#include <bits/stdc++.h>

using namespace std;

/*
 * 请设计一个函数，用来判断在一个矩阵中是否存
 * 在一条包含某字符串所有字符的路径，路径可以从矩阵中的任
 * 意一格开始，每一步可以向上、下、左、右，四个方向移动
 * 如果一条路径经过了矩阵的某一格，那么该路径不能再次进入该
 * 格子
 * */

class Solution {
public:
    static bool hasPath(vector<vector<int>>& matrix, vector<int>& nums) {
        if (matrix.empty() || nums.empty()) {
            return false;
        }
        int ROW = matrix.size();
        int COL = matrix[0].size();
        int pathlen = 0;
        vector<vector<bool>> visited(ROW, vector<bool>(COL, 0));
        for (int i = 0; i < ROW; ++i)  {
            for (int j = 0; i < COL; ++j) {
                if (hasPath(matrix, nums, pathlen, ROW, COL, i, j, visited)) {
                    return true;
                }
            }
        }
        return false;
    }
    static bool hasPath(vector<vector<int>>& matrix, vector<int>& nums, int pathlen, int ROW, int COL, int row, int col, vector<vector<bool>>& visited) {
        if (matrix.empty() || nums.empty()) {
            return false;
        }

        // 如果路径长度已经达到所给字符串的长度
        // 返回 true
        if (nums[pathlen] == nums[nums.size() - 1]) {
            return true;
        }
        bool has = false;
        if (row >= 0 && row < ROW && col >= 0 && col < COL
            && matrix[row][col] == nums[pathlen] && !visited[row][col]) {

            // 如果迷宫当前坐标的值等于字符串内容，那么路径长度加 1
            ++pathlen;

            // 设置当前点位已访问
            visited[row][col] = true;

            // 递归找上下左右四个点是否满足
            has = hasPath(matrix, nums, pathlen, ROW, COL, row - 1, col, visited) ||
                hasPath(matrix, nums, pathlen, ROW, COL, row + 1, col, visited) ||
                hasPath(matrix, nums, pathlen, ROW, COL, row, col - 1, visited) ||
                hasPath(matrix, nums, pathlen, ROW, COL, row, col + 1, visited);

            // 如果不满足，回退到当前坐标
            if (!has) {
                // 不满足，回退
                // visited 数组更新
                --pathlen;
                visited[row][col] = false;
            }
        }
        return has;
    }
};

template<typename T>
class Inc {
public:
    static bool isTrue(vector<vector<T>>& matrix, vector<T>& nums) {
        if (matrix.empty() || nums.empty()) {
            return false;
        }
        int ROW = matrix.size();
        int COL = matrix[0].size();
        vector<vector<bool>> visited(ROW, vector<bool>(COL, 0));
        stack<T> s;
        for (int i = 0; i < ROW; ++i) {
            for (int j = 0; j < COL; ++j) {
                if (hasPath(matrix, nums, visited, s, ROW, COL, i, j)) {
                    return true;
                }
            }
        }
        return false;
    }
    static bool hasPath(vector<vector<T>>& matrix, vector<T>& nums, 
                        vector<vector<bool>>& visited, stack<T>& s, 
                        int ROW, int COL, int row, int col) {
        if (matrix.empty() || nums.empty()) {
            return false;
        }
        if (s.size() == nums.size()) {
            return true;
        }
        bool has = false;
        if (row >= 0 && row < ROW && col >= 0 
            && col < COL && matrix[row][col] == nums[s.size() - 1] 
            && !visited[row][col]) {
            s.push(matrix[row][col]);
            visited[row][col] = true;
        }
        has = hasPath(matrix, nums, visited, s, ROW, COL, row - 1, col) || 
            hasPath(matrix, nums, visited, s, ROW, COL, row + 1, col) || 
            hasPath(matrix, nums, visited, s, ROW, COL, row, col - 1) || 
            hasPath(matrix, nums, visited, s, ROW, COL, row, col + 1);
        if (!has) {
            s.pop();
            visited[row][col] = false;
        }
        return has;
    }
};

void test() {
    vector<vector<int>> matrix {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    vector<int> nums {2, 5, 6, 9};
    if (Solution::hasPath(matrix, nums)) {
        cout << "true" << endl;
    } else {
        cout << "false" << endl;
    }

    /*
    if (Inc<int>::isTrue(matrix, nums)) {
        cout << "true" << endl;
    } else {
        cout << "false" << endl;
    }
    */
}

int main()
{
    test();
    return 0;
}
