#ifndef __BLOCK_QUEUE_HPP__
#define __BLOCK_QUEUE_HPP__

#include <pthread.h>

#include <iostream>
#include <queue>

template <class T>
class BlockQueue {
   public:
    static const int defalut_num = 20;

    // 因为他是阻塞队列，所以她的所有操作必须是原子的。
    // 他在生产者消费者模型当中充当的角色是缓冲区
    // 问题1： 我们需要保证线程一致性吗？
    // 答案：We need protect The lock
    // 我们期望的结果应该是生产者先生产，等生产到指定数量的时候，消费者再消费。
    // 生产者生产的时候，我们不允许消费，因为缓冲区当中的资源是临界资源我们需要保护她的安全
    // 消费者再进行消费的时候，我们生产者不允许生产，只有当他再次消费完了才能开始生产工作
    BlockQueue(int max_capacity = defalut_num) : _max_capacity(max_capacity) {
        // 对锁和条件变量进行初始化
        pthread_mutex_init(&_mutex, nullptr);
        pthread_cond_init(&_producer_cond, nullptr);
        pthread_cond_init(&_consumer_cond, nullptr);
    }

    // 问题2：
    // 我生产者怎么知道消费者消费完了呢？我消费者如何知道生产者生产完了呢？（重点）
    // 答：其实他们双方没法知道，所以这个时候我们引入一个叫
    // 条件变量的东西，如果生产者生产完了，我们通知消费者，如果消费者消费完了，我们通知生产者
    // 条件变量可以理解成用来通知对方的一个工具，然后她也是保证线程同步的一个工作工具

    // @brief
    // 生产者生产的时候，我们不允许消费，因为缓冲区当中的资源是临界资源我们需要保护她的安全
    // 消费者再进行消费的时候，我们生产者不允许生产，只有当他再次消费完了才能开始生产工作
    void push(const T &task) {
        // 再push之前我们需要先加锁，来保证她的线程安全
        pthread_mutex_lock(&_mutex);
        // 临界区
        // 在生产之前我们是不是需要看看这个缓冲区是否满了？是否还可以生产呢？
        // 我们判断缓冲区为满的条件是不是看看_capytice 是否满了
        // 为什么使用while？while的作用是用来防止伪唤醒，其实她不应该开始生产的但是意外的被唤醒了
        // 如果是if的话又直接生产了导致缓冲区多了个数据,
        // 从而导致了线程安全的问题
        while (_max_capacity == _buffer.size()) {
            // 生产这人进行等待
            // 你在等待的同时，你还要干嘛？是不是需要把“锁”
            // 给释放出来让消费者线程去消费对吧。
            pthread_cond_wait(&_producer_cond, &_mutex);
        }

        // 生产数据
        _buffer.push(task);

        // 我生产完了，我就需要进行
        // 通知消费者，你赶紧消费吧
        // 唤醒单个线程
        // pthread_cond_signal(&_consumer_cond);
        // 唤醒所有线程
        pthread_cond_broadcast(&_consumer_cond);

        pthread_mutex_unlock(&_mutex);
    }

    // @brief
    // 消费者消费的时候，我们不允许生产，因为缓冲区当中的资源是临界资源我们需要保护她的安全
    // 生产者再进行生产的时候，我们消费者不允许消费，只有当他再次生产完了才能开始消费工作
    T pop() {
        // 与生产者同理，在pop之前需要先加锁来保证线程安全。
        pthread_mutex_lock(&_mutex);

        // 在消费之前我是不是需要看看，我的缓冲区是否有东西可以消费
        // 如果没有我就应该进行等待生产者进行消费。
        // 使用while
        // 是用来防止伪唤醒的情况，导致线程不安全，因为使用if的话被伪唤醒就会直接去消费数据，这是不合理的。
        while (_buffer.empty()) {
            // 消费者进行等待
            // 消费者等待的时候，我们要把锁释放出来，让生产者进行生产。
            pthread_cond_wait(&_consumer_cond, &_mutex);
        }

        // 临界区
        // 能走到这肯定是有数据可以消费的
        T task = _buffer.front();
        _buffer.pop();

        // 取出数据之后干嘛？唤醒生产者进行生产
        // 唤醒一个线程
        // pthread_cond_signal(&_producer_cond);
        // 唤醒所有线程
        pthread_cond_broadcast(&_producer_cond);

        // 消费完了释放锁
        pthread_mutex_unlock(&_mutex);

        return task;
    }

    ~BlockQueue() {
        // 需要把锁和条件变量进行销毁
        pthread_mutex_destroy(&_mutex);
        pthread_cond_destroy(&_consumer_cond);
        pthread_cond_destroy(&_producer_cond);
    }

   private:
    std::queue<T> _buffer;  // 缓冲区
    int _max_capacity;      // 缓冲区的大小
    pthread_mutex_t _mutex;
    pthread_cond_t _consumer_cond;  // 通知消费者
    pthread_cond_t _producer_cond;  // 通知生产者
};

#endif