#ifndef __RING_QUEUE_HPP__
#define __RING_QUEUE_HPP__

#include <pthread.h>
#include <semaphore.h>

#include <iostream>
#include <vector>

template <class T>
class RingQueue {
   public:
    RingQueue(int capacity = 5) : _capacity(capacity) {
        _ring_queue.reserve(capacity);
        sem_init(&_sem_full, 0, 0);
        // 初始化只给生产者申请信号量
        sem_init(&_sem_empty, 0, _capacity);

        pthread_mutex_init(&_producer_mutex, nullptr);
        pthread_mutex_init(&_consumer_mutex, nullptr);
    }

    void P(sem_t &sem) { sem_wait(&sem); }

    void V(sem_t &sem) { sem_post(&sem); }

    // push 相当于生产者
    void push(const T &task) {
        // 生产者先进行等待，如果缓冲区满了，那么就等待
        // 如果没有满那么一定能拿到个信号量，这个信号量获取是一个原子操作
        P(_sem_empty);
        // 加锁保证线程安全
        pthread_mutex_lock(&_producer_mutex);

        // 临界区
        // 生产者进行生产
        // 这里不需要判断，因为信号量能进来说明一定有空间可以生产
        _ring_queue[_producer_index] = task;
        _producer_index++;
        _producer_index %= _capacity;

        // 释放锁
        pthread_mutex_unlock(&_producer_mutex);

        // 生产完了之后通知消费者消费，所以消费者的信号量增加1
        V(_sem_full);
    }

    // pop 相当于消费者
    T pop() {
        // 消费者先进行等待如果有空间那么一定是没有，需要先等生产者进行生产
        P(_sem_full);
        // 由于信号量并不保证线程安全，所以我们还是需要引入mutex来进行线程安全的保障
        // 只对消费者进行加锁
        // 问题一：为什么再P操作后面加锁而不是P操作之前加锁？
        // 答：首先P操作是原子性的所以不需要加锁，其次如果再P之前加锁的话会导致性能的严重下降
        // 如果先加锁，再进行P操作的时候当信号量被拿完的时候，她会进行阻塞等待，而这个时候！！！有一个很严重的问题！！！
        // 她手上是拿着锁的！！！并没有释放锁！！其他的消费者无法进行消费，只有当她消费完之后才会释放锁让其他消费者再去竞争锁，
        // 当然并不会导致死锁，因为信号量是有限制的，所以不会出现死锁，但是性能会非常差，因为会阻塞等待
        pthread_mutex_lock(&_consumer_mutex);
        // 临界区
        //  消费者进行消费
        T task = _ring_queue[_consumer_idnex];
        _consumer_idnex++;
        _consumer_idnex %= _capacity;

        pthread_mutex_unlock(&_consumer_mutex);

        // 消费完毕通知生产者生产，生产者的信号量增加1
        V(_sem_empty);

        return task;
    }

    ~RingQueue() {
        sem_destroy(&_sem_full);
        sem_destroy(&_sem_empty);

        pthread_mutex_destroy(&_producer_mutex);
        pthread_mutex_destroy(&_consumer_mutex);
    }

   private:
    std::vector<T> _ring_queue;
    int _producer_index;  // 生产者下标, 对应着 head
    int _consumer_idnex;  // 消费者下标, 对应着 tail

    int _capacity;  // 对应着缓冲区的大小，也意味着就是信号量的个数

    sem_t _sem_full;
    sem_t _sem_empty;
    // 由于本次的信号量并不保证线程安全，所以我们需要引入 mutex
    // 来保证多线程下的线程安全问题
    pthread_mutex_t _producer_mutex;
    pthread_mutex_t _consumer_mutex;
};

#endif