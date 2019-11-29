#include <bits/stdc++.h>
#include "list.h"
#include <list>

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
    static void printList(ListNode* head) {
        if (head == nullptr) {
            return ;
        }
        stack<ListNode*> s;
        while (head->next) {
            s.push(head);
            head = head->next;
        }
        while (s.empty()) {
            cout << s.top() << " ";
            s.pop();
        }
    }
};

void test() {
    list<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);
    l.push_back(5);
    list<int>::iterator iter = l.begin();
    stack<int> s;
    for (; iter != l.end(); ++iter) {
        s.push(*iter);
    }
    while (s.empty()) {
        cout << s.top() << " ";
        s.pop();
    }
}

int main()
{
    test();
    return 0;
}
