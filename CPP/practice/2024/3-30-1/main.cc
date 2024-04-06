#include <pthread.h>
#include <time.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <vector>

#include "BlockQueue.hpp"
#include "RingQueue.hpp"
#include "Task.hpp"
#include "Thread.hpp"

// 生产者
void* Producer(void* args) {
    // 拿到 BlockQueue
    BlockQueue<Task>* bq = static_cast<BlockQueue<Task>*>(args);
    // 开始生产任务

    std::string oper("+-*/%");
    while (true) {
        Task task(rand() % 100, rand() % 100, oper[rand() % 5]);

        bq->push(task);

        std::cout << "生产者线程-ID:" << pthread_self()
                  << "\t生产了一个任务， Task: " << task.GetTask() << std::endl;
        sleep(1);
    }

    return nullptr;
}

// 消费者
void* Consumer(void* args) {
    // 拿到 BlockQueue
    BlockQueue<Task>* bq = static_cast<BlockQueue<Task>*>(args);

    // 开始消费数据
    while (true) {
        sleep(3);
        Task task = bq->pop();

        task();
        std::cout << "消费者线程-ID:" << pthread_self()
                  << "\t消费了一个任务， Task: " << task.GetReslut()
                  << std::endl;
    }

    return nullptr;
}

// 单生产者单消费者
// 普通数据
void Test1() {
    // 建立缓冲区
    BlockQueue<int>* bq = new BlockQueue<int>();
    // 开始创建线程

    // 创建生产者线程
    pthread_t producere_tid;
    pthread_create(&producere_tid, nullptr, Producer, bq);

    // 创建消费者线程
    pthread_t consumer_tid;
    pthread_create(&consumer_tid, nullptr, Consumer, bq);

    // 创建完了，主线程需要等待，所以需要jion
    pthread_join(producere_tid, nullptr);
    pthread_join(consumer_tid, nullptr);
}

// 单生产者 AND 单消费者
// Task 数据
void Test2() {
    // 建立缓冲区
    BlockQueue<Task>* bq = new BlockQueue<Task>(5);

    // 创建生产者
    pthread_t producere_tid;
    pthread_create(&producere_tid, nullptr, Producer, bq);

    // 创建消费者
    pthread_t consumer_tid;
    pthread_create(&consumer_tid, nullptr, Consumer, bq);

    // 创建完了，主线程需要等待，所以需要jion
    pthread_join(producere_tid, nullptr);
    pthread_join(consumer_tid, nullptr);
}

// 多生产者 AND 多消费者
// Task 数据
void Test3() {
    // 建立缓冲区
    BlockQueue<Task>* bq = new BlockQueue<Task>(5);

    // 创建生产者
    pthread_t producere_tid[5];
    for (int i = 0; i < 5; i++) {
        pthread_create(&producere_tid[i], nullptr, Producer, bq);
    }

    // 创建消费者
    pthread_t consumer_tid[5];
    for (int i = 0; i < 5; i++) {
        pthread_create(&consumer_tid[i], nullptr, Consumer, bq);
    }

    // 创建完了，主线程需要等待，所以需要jion
    for (int i = 0; i < 5; i++) {
        pthread_join(producere_tid[i], nullptr);
        pthread_join(consumer_tid[i], nullptr);
    }
}

// 生产者
void* ProducerSem(void* args) {
    // 拿到 BlockQueue
    RingQueue<Task>* bq = static_cast<RingQueue<Task>*>(args);
    // 开始生产任务

    std::string oper("+-*/%");
    while (true) {
        Task task(rand() % 100, rand() % 100, oper[rand() % 5]);

        bq->push(task);

        std::cout << "生产者线程-ID:" << pthread_self()
                  << "\t生产了一个任务， Task: " << task.GetTask() << std::endl;
        sleep(3);
    }

    return nullptr;
}

// 消费者
void* ConsumerSem(void* args) {
    // 拿到 BlockQueue
    RingQueue<Task>* bq = static_cast<RingQueue<Task>*>(args);

    // 开始消费数据
    while (true) {
        // sleep(3);
        Task task = bq->pop();

        task();
        std::cout << "消费者线程-ID:" << pthread_self()
                  << "\t消费了一个任务， Task: " << task.GetReslut()
                  << std::endl;
    }

    return nullptr;
}

// RingQueue 单生产者和单消费者模型
void Test4() {
    RingQueue<Task>* rq = new RingQueue<Task>(5);

    pthread_t producere_tid;
    pthread_create(&producere_tid, nullptr, ProducerSem, rq);

    pthread_t consumer_tid;
    pthread_create(&consumer_tid, nullptr, ConsumerSem, rq);

    pthread_join(producere_tid, nullptr);
    pthread_join(consumer_tid, nullptr);
}

// RingQueue 多生产者多消费者模型
void Test5() {
    RingQueue<Task>* rq = new RingQueue<Task>(5);

    pthread_t producere_tid[5];
    for (int i = 0; i < 5; i++) {
        pthread_create(&producere_tid[i], nullptr, ProducerSem, rq);
    }

    pthread_t consumer_tid[5];
    for (int i = 0; i < 5; i++) {
        pthread_create(&consumer_tid[i], nullptr, ConsumerSem, rq);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(producere_tid[i], nullptr);
        pthread_join(consumer_tid[i], nullptr);
    }
}

struct Work {
    RingQueue<Task>* rq;
    int id;
};

// 生产者 线程封装版本
void* ThreadProducerSem(void* args) {
    // 拿到 BlockQueue
    Work* work = static_cast<Work*>(args);
    RingQueue<Task>* bq = work->rq;
    int id = work->id;
    // 开始生产任务

    std::string oper("+-*/%");
    while (true) {
        Task task(rand() % 100, rand() % 100, oper[rand() % 5]);

        bq->push(task);

        std::cout << "生产者线程-ID:" << id
                  << "\t生产了一个任务， Task: " << task.GetTask() << std::endl;
        sleep(3);
    }

    return nullptr;
}

// 消费者线程封装版本
void* ThreadConsumerSem(void* args) {
    // 拿到 BlockQueue
    Work* work = static_cast<Work*>(args);
    RingQueue<Task>* bq = work->rq;
    int id = work->id;

    // 开始消费数据
    while (true) {
        sleep(2);
        Task task = bq->pop();

        task();
        std::cout << "消费者线程-ID:" << id
                  << "\t消费了一个任务， Task: " << task.GetReslut()
                  << std::endl;
    }

    return nullptr;
}

void Test6() {
    std::vector<Work*> works;
    RingQueue<Task>* rq = new RingQueue<Task>(5);
    for (int i = 0; i < 5; i++) {
        Work* work = new Work();
        work->rq = rq;
        work->id = i;
        works.push_back(work);
    }

    Thread* producere_thread_arr[5];
    Thread* consumer_thread_arr[5];

    // RingQueue<Task>* rq = new RingQueue<Task>(5);
    for (int i = 0; i < 5; i++) {
        producere_thread_arr[i] = new Thread(ThreadProducerSem, works[i]);
        consumer_thread_arr[i] = new Thread(ThreadConsumerSem, works[i]);
    }

    for (int i = 0; i < 5; i++) {
        producere_thread_arr[i]->Start();
        consumer_thread_arr[i]->Start();
    }

    for (int i = 0; i < 5; i++) {
        producere_thread_arr[i]->Join();
        consumer_thread_arr[i]->Join();

        delete works[i];
        delete producere_thread_arr[i];
        delete consumer_thread_arr[i];
    }

    delete rq;
}

int main() {
    srand(time(nullptr));
    // Test1();
    // Test2();
    // Test3();
    // Test4();
    // Test5();
    Test6();
    return 0;
}