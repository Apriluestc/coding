#include <bits/stdc++.h>

using namespace std;

/*
 * 反转单词顺序
 *
 * 输入一个英文句子，单转句子中的单词顺序，但单词内字符的顺序不变
 * 例如：I am a student. 反转之后 .student a am I
 * */

class Solution {
public:
    static void _reverse(string s) {
        if (s.empty()) {
            return ;
        }
        reverse(s.begin(), s.end());
        int left = 0;
        int right = s.size() - 1;
        _reverse(s, left, right);
    }
    static void _reverse(string s, int left, int right) {
        while (true) {
            if (s[left] != ' ') {
                ++left;
            }
            right = left;
        }
    }
};

int main()
{
    return 0;
}
