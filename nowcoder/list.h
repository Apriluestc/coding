#ifndef __LIST__
#define __LIST__

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x)
        : val(x), next(nullptr)
    {}
};

#endif
