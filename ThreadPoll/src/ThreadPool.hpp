#ifndef __THREAD_POLL_H__
#define __THREAD_POLL_H__

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <functional>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <stdexcept>

class ThreadPool
{
public:
    ThreadPool(int thread_num = 4)
        : _stop(false)
    {
        if (thread_num <= 0)
        {
            thread_num = 4;
        }

        for (int i = 0; i < thread_num; i++)
        {
            _workers.emplace_back(
                [this]
                {
                    while(true){
                        std::function<void()> task;
                        {
                            std::unique_lock<std::mutex> lock(_mutex);
                            _condition.wait(lock,
                                            [this]
                                            {
                                                return _stop || !_task_queue.empty();
                                            });

                            // 如果都停止了并且里面也没有任务了，那么就没必要继续循环了
                            if (_stop && _task_queue.empty()) {
                                return;
                            }

                            // 走到这里说明需要从task_queue当中取出任务并且执行任务
                            task = std::move(_task_queue.front());
                            _task_queue.pop();
                        }

                        // 执行任务
                        task();
                    } });
        }
    }

    /// @brief 这是一个添加任务的一个接口，主要用来往任务队列当中添加task
    /// @tparam F
    /// @tparam ...Args
    /// @param f
    /// @param ...args
    /// @return
    template <class F, class... Args>
    auto EnQueue(F &&f, Args &&...args) -> std::future<typename std::result_of<F(Args...)>::type>
    {
        using return_type = typename std::result_of<F(Args...)>::type;
        // 绑定任务函数异步移交到任务队列当中
        // auto task = std::make_shared<std::packaged_task<return_type()>>(
        //     std::bind(std::forward<F>(f), std::forward<Args>(args)...));
        auto task = std::make_shared<std::packaged_task<return_type()>>([&]()
                                                                        { return std::forward<F>(f)(std::forward<Args>(args)...); });

        std::future<return_type> res = task->get_future();
        {
            std::unique_lock<std::mutex> lock(_mutex);

            if (_stop)
            {
                throw std::runtime_error("enqueue on stopped ThreadPool");
            }

            _task_queue.emplace([task]()
                                { (*task)(); });
        }

        // 唤醒所有线程
        _condition.notify_one();

        return res;
    }

    ~ThreadPool()
    {
        {
            std::unique_lock<std::mutex> lock(_mutex);
            _stop = true;
        }

        // 为了防止在停止之前任务队列里面还有任务，这一次全部唤醒再次处理
        _condition.notify_all();

        for (std::thread &worker : _workers)
        {
            worker.join();
        }
    }

private:
    // 需要：线程池、任务队列、条件变量和互斥锁

    /// @brief 线程管理器
    std::vector<std::thread> _workers;
    /// @brief 任务队列
    std::queue<std::function<void()>> _task_queue;

    /// @brief 互斥锁
    std::mutex _mutex;
    /// @brief 条件变量
    std::condition_variable _condition;

    /// @brief 线程停止标志位
    bool _stop;
};

#endif