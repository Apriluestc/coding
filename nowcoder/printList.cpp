#include <bits/stdc++.h>
#include "list.h"

using namespace std;

/*
 * 从尾到头打印链表
 * */

class Solution {
public:
    static void print(ListNode *head) {
        if (head != nullptr) {
            if (head->next != nullptr) {
                print(head->next);
            }
            cout << head->val << " ";
        }
        cout << endl;
    }
};

int main()
{
    return 0;
}
