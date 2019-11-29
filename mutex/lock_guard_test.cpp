#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

/*
 * lock_guard
 * 
 * explicite lock_guard(mutex_type& m);
 *
 * lock_guard(mutex_type& m, adopt_lock_t tag);
 *
 * C++11 标准提供了 lock_guard 类模板做 mutex 的 RAII，采用资源分配即初始化的思想
 * 来进行加锁、解锁，这避免了在临界区中因为抛出异常或 return 等操作导致
 * 没有解锁就退出的问题
 *
 * lock_guard 类的构造函数禁用拷贝构造函数，且禁止移动构造，lock_guard 除
 * 了构造函数和析构函数没有其他函数
 *
 * 在 lock_guard 对象构造时，传入的 mutex 对象(即它所管理的 mutex 对象)会被当前线程锁住，
 * 在 lock_guard 对象析构时，它所管理的 mutex 对象会自动解锁，不需要程序员手动解锁，
 * lock_guard 对象并不负责管理 mutex 对象的生命周期，lock_guard 只是简化了 mutex 对象上的
 * 加锁和解锁操作，方便线程对互斥量上锁和解锁，在某个 lock_guard 周期内，他所管理的锁
 * 对象会一直保持上锁状态，而 lock_ausrd 的生命周期结束后，它所管理的锁对象就会被解锁，
 * */

mutex mutex_;

void print_even(int x) {
    if (x % 2 == 0) {
        cout << x << " is even " << endl;
    } else {
        throw (logic_error("not even"));
    }
}

void printID(int id) {
    try {
        lock_guard<mutex> glock(mutex_);
        print_even(id);
    } catch (logic_error&) {
        cout << "exception error" << endl;
    }
}

void lock_guard_test() {
    thread td[10];
    for (int i = 0; i < 10; ++i) {
        td[i] = thread(printID, i + 1);
    }
    for (auto& e : td) {
        e.join();
    }
}

int main()
{
    lock_guard_test();
    return 0;
}
