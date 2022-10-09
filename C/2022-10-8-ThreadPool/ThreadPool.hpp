#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__ 

#include <iostream>
#include <queue>

#define NUM 5

template <typename T>
class ThreadPool{
    private:
        int thread_num;
        std::queue<T> task_queue;
        pthread_mutex_t lock;
        pthread_cond_t cond;
    public:
        ThreadPool(int _num = NUM)
            :thread_num(_num)
        {
            pthread_mutex_init(&lock, nullptr);
            pthread_cond_init(&cond, nullptr);
        }

        void LockQueue()
        {
            pthread_mutex_lock(&lock);
        }

        void UnlockQueue()
        {
            pthread_mutex_unlock(&lock);
        }

        bool IsQueueEmpty()
        {
            return task_queue.size() == 0 ? true : false;
        }

        void Wait()
        {
            pthread_cond_wait(&cond, &lock);
        }

        void Wakeup()
        {
            pthread_cond_signal(&cond);
        }

        static void* Routine(void* arg)
        {
            pthread_detach(pthread_self());
            ThreadPool* self = (ThreadPool*)arg;
            while (true)
            {
                self->LockQueue();
                while (self->IsQueueEmpty())
                {
                    //wait
                    self->Wait();
                }
                //任务队列一定有任务
                T t;
                self->Pop(t);
                self->UnlockQueue();

                //处理任务
                t.Run();
            }
        }

        void InitThreadPool()
        {
            pthread_mutex_init(&lock, nullptr);
            pthread_t tid;
            for (int i = 0; i < thread_num; i++)
            {
                pthread_create(&tid, nullptr, Routine, this);
                pthread_detach(tid);
            }
        }

        void Push(const T& in)
        {
            LockQueue();
            task_queue.push(in);
            UnlockQueue();
            Wakeup();
        }

        void Pop(T& out)
        {
            out = task_queue.front();
            task_queue.pop();
        }

        ~ThreadPool()
        {
            pthread_cond_destroy(&cond);
            pthread_mutex_destroy(&lock);
        }
};

#endif
