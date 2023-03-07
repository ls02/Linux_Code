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
            public:
                static ThreadPool<T>* GetInstance()
                {
                    static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

                    if (nullptr == ins)
                    {
                        pthread_mutex_lock(&lock);
                        if (ins == nullptr)
                        {
                            ins = new ThreadPool<T>();
                            ins->InitThreadPool();
                            std::cout << "首次加载对象" << std::endl;
                        }

                        pthread_mutex_unlock(&lock);
                    }

                    return ins;
                }

                void Lock()
                {
                    pthread_mutex_lock(&_mtx);
                }

                void UnLock()
                {
                    pthread_mutex_unlock(&_mtx);
                }

                void Wait()
                {
                    pthread_cond_wait(&_cond, &_mtx);
                }

                void WakeUp()
                {
                    pthread_cond_signal(&_cond);
                }

                bool IsEmpty()
                {
                    return task_queue.empty();
                }

            public:
                static void* Rountine(void* args)
                {
                    pthread_detach(pthread_self());

                    ThreadPool<T>* tp = (ThreadPool<T>*)args;

                    while (true)
                    {
                        tp->Lock();

                        while (tp->IsEmpty())
                        {
                            //没有任务线程进行等待
                            tp->Wait();
                        }

                        //有任务线程进行处理
                        T t;
                        tp->PopTask(&t);
                        tp->UnLock();

                        t.Run();
                    }
                }

                void InitThreadPool()
                {
                    pthread_t tid;

                    for (int i = 0; i < _num; i++)
                    {
                        pthread_create(&tid, nullptr, Rountine, (void*)this);
                    }
                }

                void PushTask(const T& in)
                {
                    Lock();
                    task_queue.push(in);
                    UnLock();
                    WakeUp();
                }

                void PopTask(T* out)
                {
                    *out = task_queue.front();
                    task_queue.pop();
                }

                ~ThreadPool()
                {
                    pthread_mutex_destroy(&_mtx);
                    pthread_cond_destroy(&_cond);
                }
        };

    template<class T>
        ThreadPool<T>* ThreadPool<T>::ins = nullptr;
}

#endif
