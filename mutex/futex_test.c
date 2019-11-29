#include <stdio.h>
#include <linux/futex.h>
#include <sys/time.h>

#if 0

int futex(int *uaddr, int futex_op, int val,
          const struct timespec *timeout, 
          /* or: uint32_t val2 */
          int *uaddr2, int val3);

uaddr : 指向 futex 值，在所有平台上，futex 值是一个 4 字节的整数并且
必须是 4 字节对齐

对于某些阻塞操作，timeout 参数是一个指向 timespec 结构的指针，表明了操作的超时时间，
然而，在其他的某些操作下，它的最低 4 字节被作为一个整数值，这个整数值的含义因 futex 的
操作不同而不同，对于这些操作来说，内核会将 timeout 值转换为 unsigned long，
然后转换为 uint32_t，

futex_op 参数包含两个部分，操作类型、标志选项
1、FUTEX_PRIVATE_FLAG : 这个标志选项可以用在所有的 futex 操作中，它告诉内核这个
futex 是进程内的，不和其他进程共享(它只能用来同步同一个进程内的线程)，这样内核可以做一些优化

2、FUTEX_CLOCK_REALTIME : 这个标志选项只能用在 FUTEX_WAIT_BITSET 和 FUTEX_WAIT_REQUEUE_PI 操作中，
如果设置了这个标志选项，内核会将 timeout 视作基于 CLOCK_REALTIME 的绝对时间，如果
没有这个标志，则内核将它视作就 CLOCK_MONOTONIC 的相对时间

futex 操作如下：
1、FUTEX_WAIT : 本操作会检查 *uaddr 是否等于 val，则睡眠等待在 uaddr 上的
FUTEX_WAKE 操作，如果线程开始睡眠，则它被认为是这个 futex 值上的一个等待着，
如果两者不相等，则操作失败并返回 error EAGAIN，比较 *uaddr 和 val 的目的是为了避免丢失唤醒

如果 timeout 参数不为 NULL，则它制定了等待的超时时间(根据 CLOCK_MONOTONIC 测量得出)

2、FUTEX_WAKE : 本操作会唤醒最多 val 个等待者，绝大部分情况下，val 的值
为 1 (只唤醒一个等待者)或者 INT_MAN(唤醒所有等待者)，注意没有任何机制保证一定唤醒某些特定的等待者(比如认为是优先级高的)。

参数 timeout、uaddr2、val3 将被忽略

3、FUTEX_REQUEUE : 本操作和下面的 FUTEX_CMP_REQUEUE 完成相同
的功能，除了不检查 val3 。(参数val3被忽略)

4、FUTEX_CMP_REQUEUE : 本操作首先检查 *uaddr 是否等于 val3，如果不相等，则
返回 error EAGAIN。否则的话，将唤醒最多 val 个等待者，如果等待者的
数量大于 val，则剩下的等待者则从 uaddr 的等待队列中移除，添加到 uaddr2 的
等待队列中。val2 参数指定了移动到 uaddr2 的等待者的最大数量。

val 的典型值为 0 或 1，指定为 INT_MAX 是没有任何用处的，这将
会使得 FUTEX_CMP_REQUEUE 操作和 FUTEX_WAKE 操作相同。同样，val2 的值
通常为 1 或 INT_MAX，指定为 0 是没有用的，这样将使得 FUTEX_CMP_REQUEUE 操
作和 FUTEX_WAIT 操作相同。

5、FUTEX_CMP_REQUEUE : 是用来代替 FUTEX_REQUEUE 的，两者的不
同点在于是否检查 uaddr 的值，这个检查操作可用来确保移除添加操作只
在特定的条件下发生，这样就避免了某些 race condition。

6、FUTEX_CMP_REQUEUE 和 FUTEX_REQUEUE 都可以用来避免 FUTEX_WAKE 可能产生的“线程惊群”现
象。考虑下面的情况，多个线程在等待 B(使用 futex 实现的等待队列)

#endif

/*
 * futex 系统调用提供了一种方法用于等待某个特定条件的发生
 * */

int main()
{
    return 0;
}
