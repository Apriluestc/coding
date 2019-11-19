#include <bits/stdc++.h>

using namespace std;

/*
 * 两个栈实现一个队列
 *
 * 用两个栈模拟实现一个队列，如果栈的容量分别是 O 和 P(O > P)，那么
 * 模拟实现的队列最大容量是多少
 *
 * 分析：假设有栈 s1 和 s2，容量分别是 O 和 P
 * 那么，O 将作为存储空间，P 将作为缓冲空间
 * 1、将 P 个元素 push 到 s1 中
 * 2、再将该 P 个元素 pop 到 s2 中
 * 3、将 P+1 个元素 push 到 s1 中
 * 4、将 P 个元素 pop 到 s2 中，先将 s1 中剩余的元素 pop，然后依
 * 次 pop 出 s2 中元素，所以最终容量大小为 2P + 1
 * */

template<typename T>
class Queue {
public:
    void push(const T& val) {
        s1.push(val);
        ++count_;
    }
    T pop() {
        if (s2.empty()) {
            while (!s1.empty()) {
                int data = s1.top();
                s1.pop();
                s2.push(data);
            }
        }
        int pop_element = s2.top();
        s2.pop();
        return pop_element;
    }
    int size() {
        return count_;;
    }
    bool empty() {
        return s1.empty() && s2.empty();
    }
private:
    stack<T> s1;
    stack<T> s2;
    static int count_;
};

template<typename T>
int Queue<T>::count_;

void test() {
    Queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    for (int i = 0; i < q.size(); ++i) {
        cout << q.pop() << " ";
    }
    cout << endl;
}

int main()
{
    test();
    return 0;
}
