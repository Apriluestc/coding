#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/sysinfo.h>
#include <sched.h>
#include <ctype.h>
#include <fcntl.h>
#include <malloc.h>

#if 0

/*
 * 互斥：对临界资源同一时间的唯一访问性
 * 同步：对临界资源的顺序访问性
 * */

struct mutex {
    atomic_t count;             // 表示互斥锁的状态
    spinlock_t wait_lock;       // 等待获取互斥锁中使用的自旋锁，在获取的过程中
                                // 操作会在自旋锁的保护中进行，初始化为锁定
    struct list_head wait_list; // 等待互斥锁的进程队列
#ifndef CONFIG_DEBUG_MUTEXES
    struct thread_info *owner;
    const char *name;
    void *magic;
#endif
#ifndef CONFIG_DEBUG_LOCK_ALLOC
    struct lockdep_map dep_map;
#endif
};

#endif

/*
 * Linux 内核互斥锁 mutex 原理
 *
 * 1、互斥锁 mutex 结构体成员
 *
 * count : atomict_t
 * 互斥锁变量，0 表示被占用(表示已经获取锁)，1 表示没被占用(空闲可获取)
 *
 * osq : struct optimistic_spin_queue
 *
 * owner : struct task_struct*
 * 当前获取该锁的任务
 *
 * wait_list : struct list_head
 * 等待获取互斥锁的任务链表，互斥锁释放时会唤醒 wait_list 表头任务
 * 
 * wait_lock : spinlock_t
 * 多任务共享，需要采用自旋锁互斥访问，自旋锁会不停循环检查且不会阻塞
 * 任务的执行，适合短时间的加锁
 * */

pthread_mutex_t mutex_;
int value = 0;

void *threadFunc(void *arg) {
    (void)arg;
    while (1) {
        pthread_mutex_lock(&mutex_);
        for (int i = 0; i < 10000; ++i) {
            value++;
        }
        printf("value = %d\n", value);
        pthread_mutex_unlock(&mutex_);
        usleep(20);
    }
    return 0;
}

void test_mutex_linux() {
    void *resVal;
    pthread_mutex_init(&mutex_, NULL);
    pthread_t td1, td2;
    pthread_create(&td1, NULL, threadFunc, NULL);
    pthread_create(&td2, NULL, threadFunc, NULL);
    pthread_join(td1, &resVal);
    pthread_join(td2, &resVal);
}

/*
 * pthread_mutex_init() : 初始化一个互斥锁
 * pthread_mutex_lock() : 加锁
 * 使用此函数进行加锁时，若此时已经被加锁，则尝试加锁的线程将处于阻塞
 * 状态，直到互斥锁被其他线程释放，当 pthread_mutex_lock() 有返回值时，说明加锁成功
 *
 * pthread_mutex_trylock() : 尝试加锁
 * 若此时已经被锁，则会返回 EBUSY 的所悟码
 *
 * 同时，解锁的过程中，也需要满足两个条件
 * 1、解锁前，互斥锁必须处于锁定状态
 * 2、必须由加锁的线程进行解锁
 *
 * pthread_mutex_unlock() : 解锁
 * pthread_mutex_destroy() : 注销互斥锁
 * */

const char filename[] = "hello";

void *callback(void *id) {
    if (pthread_mutex_lock(&mutex_) != 0) {
        fprintf(stdout, "lock err\n");
    }
    FILE *fp = fopen(filename, "a+");
    int start = *((int *)id);
    int end = start + 1;
    setbuf(fp, NULL);
    fprintf(stdout, "%d\n", start);
    for (int i = (start * 10); i < (end * 10); ++i) {
        fprintf(fp, "%d\n", i);
    }
    fprintf(fp, "\n");
    fclose(fp);
    return 0;
}

int mutex_test() {
    int num_threads = 5;
    pthread_t *pt = (pthread_t *)malloc(sizeof(pthread_t) * num_threads);
    int *id = (int *)malloc(sizeof(int) * num_threads);
    if (pthread_mutex_init(&mutex_, NULL) != 0) {
        free(pt);
        free(id);
        return 1;
    }
    for (int i = 0; i < num_threads; ++i) {
        id[i] = i;
        if (pthread_create(&pt[i], NULL, callback, &id[i]) != 0) {
            printf("thread error\n");
            return 1;
        }
    }
    for (int i = 0; i < num_threads; ++i) {
        pthread_join(pt[i], NULL);
    }
    pthread_mutex_destroy(&mutex_);
    free(pt);
    free(id);
    return 0;
}

/*
 * linux mutex API
 *
 * pthread_mutex_init(pthread_mutex_t* restrict mutex, const pthread_mutexattr * restrict attr);
 * attr 互斥锁属性
 * 1、PTHREAD_MUTEX_TIMED_NP，缺省值，也就是普通锁，当一个线程加锁以后，
 * 其余请求锁的线程形成一个等待队列，并在解锁后按优先级获得锁，这种锁保
 * 证了资源分匹配的公平性
 * 2、PTHREAD_MUTEX_RECURSIVE_NP，嵌套锁，递归所，允许一个线程对一个锁对象获得
 * 多次，并通过多次 unlock 解锁，如果是不同线程请求，则在加锁线程解锁时重新竞争
 * 3、PTHREAD_MUTEX_ERRORCHECK_NP，检查锁，如果同一个线程请求同一个锁，则返回 EDEADLK，
 * 否则与 PTHREAD_MUTEX_TIMED_NP 类型动作相同，这样就保证当不允许多次加锁时不会出现最简单
 * 情况下的死锁
 * 4、PTHREAD_MUTEX_ADAPTIVE_NP，适应锁，动作最简单的锁类型，仅仅等待解锁后重新竞争
 * pthread_mutex_lock(pthread_mutex_t *mutex);
 * pthread_mutex_trylock(pthread_mutex_t *mutex);
 * pthread_mutex_unlock(pthread_mutex_t *mutex);
 * pthread_mutex_destroy(pthread_mutex_t *mutex);
 * */

int main()
{
    // test_mutex_linux();
    mutex_test();
    return 0;
}
