#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

/*
 * unique_lock
 * 
 * unique_lock 对象以独占所有权的方式管理 mutex 对象的上锁和解锁操作，
 * 即在 unique_lock 对象的生命周期内，他所管理的对象会一直保持上锁的状态，
 * 而 unique_lock 生命周期结束后，他所管理的对象会被解锁，unique_lock 具有
 * lock_guard 的所有功能，而且更为灵活，虽然二者对象都不能复制，但
 * 是 unique_lock 可以移动，因此用 unique_lock 管理互斥对象，可以作为函数
 * 返回值，也可以放到 STL 容器中
 *
 * unique_lock 还支持同时锁定多个 mutex，这避免了多道加锁时的资源死锁问题，
 * 在使用 condition_variable 时需要使用 unique_lock 而不应该使用 lock_guard
 * 
 * 其 lock try_lock 操作都是调用 mutex 对象的相应操作
 *
 * 构造函数如下：
 *
 * unique_lock() noexcept;
 *
 * explicit unique_lock(mutex_type& m);
 *
 * 调用 m.try_lock()
 * unique_lock(mutex_type& m, try_to_lock_t tag);
 *
 * m 当前没有被加锁
 * unique_lock(mutex_type& m, defer_lock_t tag) noexcept;
 *
 * m 当前应该已经被加锁
 * unque_lock(mutex_type& m, adopt_lock_t tag);
 *
 * template<class Rep, class Period>
 * unique_lock(mutex_type& m, const chrono::duration<Rep, Period>& rel_time);
 *
 * 调用 m.try_lock_until(abs_time)
 * template<class Clock, class Duration>
 * unique_lock(mutex_type& m, const chrono::time_point<Clock, Duration>& abs_time);
 *
 * unique_lock(const unique_lock&) = delete;
 *
 * unique_lock(unique_lock&& x);
 * */

mutex foo, bar;

/*
 * defer_lock、try_to_lock、adopt_lock 分别是以下三种空结构体标签类
 * 型的实例，专门用于指定锁定策略
 *
 * 不用获取 mutex 的所有权，一般用于 mutex 没有加锁前
 * struct defer_lock_t {explicite defer_lock_t() = default; };
 *
 * 尝试获取 mutex 的所有权，不阻塞
 * struct try_to_lock_t {explicite try_to_lock_t() = default; };
 *
 * 假设调用线程已经获得 mutex 的所有权，一般用于对 mutex 加锁之后
 * struct adopt_lock_t {explicite adopt_lock_t() = default; };*/

void task_a() {
    lock(foo, bar);
    unique_lock<mutex> ulock1(foo, adopt_lock);
    unique_lock<mutex> ulock2(bar, adopt_lock);
    cout << "task a" << endl;
}

void task_b() {
    unique_lock<mutex> ulock1, ulock2;
    ulock1 = unique_lock<mutex>(bar, defer_lock);
    ulock2 = unique_lock<mutex>(foo, defer_lock);
    lock(ulock1, ulock2);
    cout << "task b" << endl;
}

/*
 * lock
 * 
 * template<class Mutex1, class Mutex2, ···>
 * void lock(Mutex1& a, Mutex2& b, ···);
 * 锁住所有的 mutex，可能或阻塞，调用 mutex 对象的 lock 和 try_lock 如果不能锁住
 * 所有的 mutex(因为有一个抛出异常)，则先 unlock 加锁成功的 mutex
 * */
void unique_lock_test() {
    thread td1(task_a);
    thread td2(task_b);
    td1.join();
    td2.join();
}

void task1() {
    foo.lock();
    cout << "task a" << endl;
    bar.lock();
    foo.unlock();
    bar.unlock();
}

void task2() {
    int x = try_lock(bar, foo);
    if (x == -1) {
        cout << "task b" << endl;
        bar.unlock();
        foo.unlock();
    } else {
        cout << "[task b failed: mutex " << (x ? "foo" : "bar") << "locked]" << endl;
    }
}

/*
 * try_lock
 * 
 * template<class Mutex1, class Mutex2, ···>
 * int try_lock(Mutex& a, Mutex& b, ···);
 * 尝试对所有 mutex 进行加锁(非阻塞)，
 * 如果全部加锁成功则返回 -1，如果有一个加锁失败，则将加锁成功的 mutex 解锁
 * 并返回加锁失败的那个锁的序号*/
void try_lock_test() {
    thread td1(task1);
    thread td2(task2);
    td1.join();
    td2.join();
}

int main()
{
    unique_lock_test();
    try_lock_test();
    return 0;
}
