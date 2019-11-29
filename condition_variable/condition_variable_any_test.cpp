#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

mutex mutex_;
condition_variable cond_;
bool ready = false;

/*
 * condition_variable_any
 * 
 * 与 condition_variable 类似，只不过 condition_variable_any 的 wait 方法
 * 可以接受任何类型的 lockable 参数，而 condition_variable 只能接受
 * unique_lock 类型的参数，除此以外几乎一样
 *
 * cv_status 枚举类型*/

void printID(int id) {
    unique_lock<mutex> ulock(mutex_);
    while (!ready) {
        cond_.wait(ulock);
    }
    cout << "thread" << id << endl;
}

void go() {
    unique_lock<mutex> ulock(mutex_);
    notify_all_at_thread_exit(cond_, move(ulock));
    ready = true;
}

void test() {
    thread td[10];
    for (int i = 0; i < 10; ++i) {
        td[i] = thread(printID, i);
    }
    cout << "10 threads ready to race" << endl;
    thread(go).detach();
    for (auto& e : td) {
        e.join();
    }
}

int main()
{
    test();
    return 0;
}
