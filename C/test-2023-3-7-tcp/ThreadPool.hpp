#ifndef __THREAD_POOL_HPP__
#define __THREAD_POOL_HPP__ 

#include <iostream>
#include <pthread.h>
#include <string>
#include <queue>

namespace ns_threadpool
{
    const int g_num = 5;
    template <class T>
        class ThreadPool 
        {
            private:
                int _num;
                std::queue<T> task_queue;

                pthread_mutex_t _mtx;
                pthread_cond_t _cond;

                static ThreadPool<T>* ins;

            private:
                ThreadPool(int num = g_num)
                    :_num(num)
                {
                    pthread_mutex_init(&_mtx, nullptr);
                    pthread_cond_init(&_cond, nullptr);
                }
                ThreadPool(const ThreadPool<T>& tp) = delete;
                ThreadPool<T>& operator=(ThreadPool<T>& tp) = delete;
        };
}

#endif
