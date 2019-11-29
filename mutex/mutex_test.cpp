#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

volatile int counter(0);
mutex mutex_;

void attempt_10k_increases() {
    for (int i = 0; i < 10000; ++i) {
        if (mutex_.try_lock()) {
            ++counter;
            mutex_.unlock();
        }
    }
}

/*
 * mutex 成员函数
 *
 * 构造函数：mutex 不允许拷贝构造，也不允许 move 构造，最初产生的  mutex 是
 * unlock 状态的
 *
 * lock()，调用线程将锁住该互斥量，线程调用该函数会发发生以下三种情况：
 *
 * 1、如果该互斥量当前没有被锁住，则调用线程将该互斥量所著，直到 unlock 之前，
 * 该线程一直拥有锁
 *
 * 2、如果当前互斥量被其他线程锁住，则当前的调用线程被阻塞
 *
 * 3、如果当前互斥量被当前独、调用线程锁柱，则会产生死锁
 *
 * unlock()，解锁，释放对互斥量的所有权
 *
 * try_lock()，尝试锁住互斥量，如果互斥量被其他线程占有，则当前线程也不会被阻塞，线程调用该函数也会出现下面三种情况：
 *
 * 1、如果当前互斥量没有被其他线程占有，则该线程锁住互斥量，直到该线程调用 unlock 释放互斥量
 *
 * 2、如果当前互斥量被其他线程锁住，则当前调用线程返回 false，而并不会被阻塞掉
 *
 * 3、如果当前互斥量被当前线程锁住，则会产生死锁
 * */

void mutex_test()
{
    thread td[10];
    for (int i = 0; i < 10; ++i) {
        td[i] = thread(attempt_10k_increases);
    }
    for (auto& e : td) {
        e.join();
    }
    cout << counter << " successful increases " << endl;
}

/*
 * recursive_mutex
 * 
 * 与 mutex 一样，也是一种可以被上锁的对象，但是与 mutex 不同的是，
 * recursive_mutex 允许同一个线程对一个互斥量多次上锁(即递归上锁)，
 * 来获得对互斥量对象的多层所有权，recursive_mutex 释放互斥量时需
 * 要调用该锁层次深度相同的 unlock() 可以理解为 lock() 次数
 * 和 unlock() 次数相同*/

int main()
{
    mutex_test();
    return 0;
}
