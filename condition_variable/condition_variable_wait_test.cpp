#include <iostream>
#include <thread>
#include <condition_variable>
#include <chrono>
#include <mutex>

using namespace std;

mutex mutex_;
condition_variable cond_;
bool ready = false;
int cargo = 0;
int value;

void read_value() {
    cin >> value;
    cond_.notify_one();
}

/*
 * wait_for()
 *
 * cv_status wait_for(unique_lock<mutex>& lok, const chrono::duration<rep, period>& rel_time);
 * bool wait_for(unique_lock<mutex>& lok, const chrono::duration<rep, period>& rel_time, Predicate pred);
 * 
 * 与 wait 类似，不过 wait_for 可以指定一个时间段，在当前线程收到通知
 * 或者指定时间 rel_time 超时之前，该线程都会处于阻塞状态，而一旦超时
 * 或者收到了其他线程的通知，wait_for 返回，剩下的处理步骤和 wait 类似
 *
 * 另外 wait_for 的重载版本的最后一个参数 pred 表示 wait_for 的预测条件，
 * 只有当 pred 条件为 false 时调用 wait 才会阻塞当前线程，并且在收到其他线
 * 程的通知后只有当 pred 为 true 时，才会被解除阻塞 */

void test3() {
    cout << "please enter an integer" << endl;
    thread td(read_value);
    mutex mtx;
    unique_lock<mutex> ulock(mtx);
    while (cond_.wait_for(ulock, chrono::seconds(1)) == cv_status::timeout) {
        cout << '.';
        cout.flush();
    }
    cout << "you entered : " << value << endl;
    td.join();
}

bool shipment_available() {
    return cargo != 0;
}

/*
 * wait()
 *
 * void wait(unique_lock<mutex>&);
 *
 * template<class Predicate>
 * void wait(unique_lock<mutex>&, Predicate);
 *
 * 当前线程调用了 wait() 后将被阻塞(此时当前线程获得了锁(mutex)，不妨
 * 设获得 ulock)，直到另外某个线程调用了 notify_* 唤醒了当前函数
 *
 * 在线程被阻塞时，该函数会自动调用 ulock.unlock() 来释放锁，使得其他被
 * 阻塞在锁竞争上的线程得以继续运行，另外，一旦当前线程获得通知 notify，
 * 通常是某个线程调用 notify_* 唤醒了当前线程，wait() 也是自动调
 * 用 ulock.lock()，使得 ulock 的状态和 wait() 被调用时相同
 *
 * 第二种情况下，即设置了 Predicate，只有当 Predicate 条件为 false 时调用
 * wait() 才会阻塞当前线程，并且在收到其他线程的通知后只有
 * 当 Predicate 为 true 时才会被阻塞
 * */

void consume(int n) {
    for (int i = 0; i < n; ++i) {
        unique_lock<mutex> ulock(mutex_);
        cond_.wait(ulock, shipment_available);
        cout << cargo << endl;
        cargo = 0;
    }
}

/*
 * 情况二
 * */
void test2() {
    thread consumer_td(consume, 10);
    for (int i = 0; i < 10; ++i) {
        while (shipment_available()) {
            this_thread::yield();
        }
        unique_lock<mutex> ulock(mutex_);
        cargo = i + 1;
        cond_.notify_one();
    }
    consumer_td.join();
}

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

void test1()
{
    thread td[10];
    for (int i = 0; i < 10; ++i) {
        td[i] = thread(printID, i);
    }
    cout << "10 threads ready to race" << endl;
    go();
    for (auto& e : td) {
        e.join();
    }
}

/*
 * wait_until
 * 
 * 与 wait_for 类似，但是 wait_until 可以指定一个时间点，在当前线程
 * 收到通知或者指定时间点 abs_time 超时之前，该线程都处于阻塞模式，
 * 而一旦超过该超时时间或者收到了其他线程的通知，wait_until 返回，
 *
 * 另外，wait_until 的重载版本的最后一个参数 pred 表示 wait_until 的预测条件，
 * 只有当 pred 的条件为 false 时调用 wait 才会阻塞当前线程，并且在收到其他线程的通
 * 知后只有当 pred 为 true 时才会被解除阻塞
 *
 * 相当于：
 *
 * if (wait_until(lok, abs_time) == cv_status::timeout) {
 *     return pred();
 * }
 * return true;
 * */

int main()
{
    test1();
    test2();
    test3();
    return 0;
}
