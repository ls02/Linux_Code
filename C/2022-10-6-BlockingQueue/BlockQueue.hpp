#ifndef __BLOCK_QUEUE_H__
#define __BLOCK_QUEUE_H__

#include <iostream>
#include <queue>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <pthread.h>

#define NUM 32

template<typename T>
class BlockQueue 
{
    private:
        bool IsFull()
        {
            return q.size() == cap;
        }

        bool IsEmpty()
        {
            return q.empty();
        }
    public:
        BlockQueue(int _cap = NUM)
            :cap(_cap)
        {
            pthread_mutex_init(&lock, nullptr);
            pthread_cond_init(&full, nullptr);
            pthread_cond_init(&empty, nullptr);
        }

        void Push(const T& in)
        {
            pthread_mutex_lock(&lock);
            while (IsFull()) 
            {
                //不能进行生产数据，需要等待，等待q可以容纳新的数据
                pthread_cond_wait(&full, &lock);
                
            }

            q.push(in);

            if (q.size() >= cap / 2)
            {
                std::cout << "数据已经很多了，消费者快来消费吧" << std::endl;
                pthread_cond_signal(&empty);
            }

            pthread_mutex_unlock(&lock);
        }

        void Pop(T& out)
        {
            pthread_mutex_lock(&lock);
            
            while (IsEmpty())
            {
                //不能进行消费，需要等待，等待q有新的数据的时候
                pthread_cond_wait(&empty, &lock);
            }

            out = q.front();
            q.pop();

            if (q.size() <= cap / 2)
            {
                std::cout << "空间已经很多了，生产者快来生产吧!" << std::endl;
                pthread_cond_signal(&full);
            }

            pthread_mutex_unlock(&lock);
        }

        ~BlockQueue()
        {
            pthread_mutex_destroy(&lock);
            pthread_cond_destroy(&full);
            pthread_cond_destroy(&empty);
        }

    private:
        std::queue<T> q;
        int cap;
        pthread_mutex_t lock;
        pthread_cond_t full;
        pthread_cond_t empty;
};

#endif
