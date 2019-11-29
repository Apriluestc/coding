#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

mutex mutex_;
condition_variable cond_;
int cargo = 0;
bool ready = false;

void consumer() {
    unique_lock<mutex> ulock(mutex_);
    while (cargo == 0) {
        cond_.wait(ulock);
    }
    cout << cargo << endl;
    cargo = 0;
}

void producer(int id) {
    unique_lock<mutex> ulock(mutex_);
    cargo = id;
    cond_.notify_one();
}

/*
 * notify_one
 * 
 * 唤醒某个等待线程，如果当前没有线程等待，则该函数什么都不用做，如果同时
 * 存在多个等待线程，则唤醒某个线程是不确定的
 * */

void test_notify_one() {
    thread consumers[10], producers[10];
    for (int i = 0; i < 10; ++i) {
        consumers[i] = thread(consumer);
        producers[i] = thread(producer, i + 1);
    }
    for (int i = 0; i < 10; ++i) {
        producers[i].join();
        consumers[i].join();
    }
}

/*
 * notify_all
 * 
 * 唤醒所有等待的线程，如果当前没有等待线程，则该函数什么也不做
 * */

void printID(int id) {
    unique_lock<mutex> ulock(mutex_);
    while (!ready) {
        cond_.wait(ulock);
    }
    cout << "thread" << id << endl;
}

void go() {
    unique_lock<mutex> ulock(mutex_);
    ready = true;
    cond_.notify_all();
}

void test_notify_all() {
    thread td[10];
    for (int i = 0; i < 10; ++i) {
        td[i] = thread(printID, i);
    }
    cout << "10 threads ready race" << endl;
    go();
    for (auto& e : td) {
        e.join();
    }
}

int main()
{
    test_notify_one();
    test_notify_all();
    return 0;
}
