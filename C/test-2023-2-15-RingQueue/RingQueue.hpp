#ifndef  __RING_QUEUE_HPP__
#define __RING_QUEUE_HPP__

#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <vector>

const int g_cap_default = 10;

template<class T>
class RingQueue 
{
    private:
        //生产者关心有没有空位置
        sem_t _blank_sem;
        //消费者关心有没有数据
        sem_t _data_sem;

        //环形队列
        std::vector<T> _ring_queue;
        //环形队列的大小
        int _cap;

        int _v_step;
        int _p_step;

        pthread_mutex_t _v_mtx;
        pthread_mutex_t _p_mtx;
    public:
        RingQueue(int cap = g_cap_default)
            :_cap(cap)
             ,_ring_queue(cap)
    {
        sem_init(&_blank_sem, 0, cap);
        sem_init(&_data_sem, 0, 0);
        _v_step = _p_step = 0;
    }

        ~RingQueue()
        {
            sem_destroy(&_blank_sem);
            sem_destroy(&_data_sem);
        }

    public:
        void Push(const T& in)
        {
            //生产前需要先申请一个信号量也就是P操作才能开始生产
            sem_wait(&_blank_sem);//P（空位置）

            pthread_mutex_lock(&_p_mtx);
            //开始生产
            _ring_queue[_p_step] = in;
            _p_step++;
            _p_step %= _cap;
            pthread_mutex_unlock(&_p_mtx);
            sem_post(&_data_sem);//V（数据）
        }

        void Pop(T* out)
        {
            //消费接口
            sem_wait(&_data_sem);//P

            pthread_mutex_lock(&_v_mtx);
            *out = _ring_queue[_v_step];

            _v_step++;
            _v_step %= _cap;

            pthread_mutex_unlock(&_v_mtx);

            sem_post(&_blank_sem);//V
        }
};

#endif
