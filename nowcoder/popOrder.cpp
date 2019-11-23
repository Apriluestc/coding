#include <bits/stdc++.h>

using namespace std;

/*
 * 栈的压入弹出序列
 * 输入两个整数序列，第一个序列表示栈的入栈顺序
 * 请判断第二个序列是第一个序列的出栈序列
 * 例如：1，2，3，4，5 是某个栈的入栈序列，序列 4，5，3，2，1 是出栈序列
 * 但是 4，3，5，1，2 就不可能是该序列的出栈序列
 * 
 *
 * 思路：创建辅助栈，将第一个序列中的元素依次压入该辅助栈
 * 并且按照第二个序列的顺序依次出栈
 * */
class Solution {
public:
    static bool isPopOrder(const vector<int>& push, const vector<int>& pop) {
        if (push.empty() || pop.empty()) {
            return false;
        }

        // 创建辅助栈
        stack<int> s;
        for (size_t i = 0, j = 0; i < push.size(); ++i) {
            
            // 模拟入栈序列入栈
            s.push(push[i]);

            // 当且仅当栈顶元素等于出栈序列元素是出栈
            // 直到栈为空返回 true
            while (j < pop.size() && s.top() == pop[j]) {
                s.pop();
                ++j;
            }
        }

        // 栈空则为 true，否则 false
        return s.empty();
    }
};

void test() {
    vector<int> push {1, 2, 3, 4, 5};
    vector<int>pop {4, 5, 3, 2, 1};
    if (Solution::isPopOrder(push, pop)) {
        cout << "true" << endl;
    } else {
        cout << "false" << endl;
    }
}

int main()
{
    test();
    return 0;
}
