#ifndef __RING_H__
#define __RING_H__ 

#include <iostream>
#include <vector>
#include <pthread.h>
#include <semaphore.h>

#define NUM 5

template<typename T>
class RingQueue{
    private:
        std::vector<T> q;
        int cap;
        int c_pos;
        int p_pos;

        sem_t blank_sem;
        sem_t data_sem;

    private:
        void P(sem_t &s)
        {
            sem_wait(&s);
        }

        void V(sem_t &s)
        {
            sem_post(&s);
        }
    public:
        RingQueue(int _cap = NUM)
            :cap(_cap)
             ,c_pos(0)
             ,p_pos(0)
        {
            q.resize(cap);
            sem_init(&blank_sem, 0, cap);
            sem_init(&data_sem, 0, 0);
        }

        //生产者调用，生产数据，关心blank
        void Push(const T& in)
        {
            P(blank_sem);
            q[p_pos] = in;
            V(data_sem);

            p_pos++;
            p_pos %= cap;
        }

        //消费者调用，消费数据，关心 data 资源
        void Pop(T& out)
        {
            P(data_sem);
            out = q[c_pos];
            V(blank_sem);

            c_pos++;
            c_pos %= cap;
        }

        ~RingQueue()
        {
            sem_destroy(&blank_sem);
            sem_destroy(&data_sem);
        }
};

#endif
